#include "joinRoom.h"
#include "ui_joinroom.h"
#include <QNetworkInterface>
#include <QHostInfo>
#include <QSettings>
#include <QVBoxLayout>
#include<QTabBar>
joinRoom::joinRoom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::joinRoom),
    model(new QStandardItemModel(qApp)),
    g_s(new gameSetting(2)),
    playernum(-1)
{
    ui->setupUi(this);
     ui->tabWidget->tabBar()->setExpanding(true);
    tab_1();
    tab_2();
    m_udp=new QUdpSocket(this);
    QByteArray datagram = "RoomRequest";
    m_udp->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
    m_tcp=new QTcpSocket(this);
    connect(m_udp,&QUdpSocket::readyRead,this,[=]
    {
        while (m_udp->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(m_udp->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            m_udp->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
           if (datagram.startsWith("RoomResponse")) {
                // Server replied with RoomResponse
                // 'sender' contains the server's IP address

                QString serverAddress = sender.toString();
                //输出的格式形如::ffff:192.168.0.101需要去掉前面的::ffff:七位
                serverAddress.remove(0, 7);

                m_tcp->connectToHost(QHostAddress(serverAddress), 3366);
                qDebug()<<QHostAddress(serverAddress);
                break;

           }
        }
        QSettings name("tlr","name");
        Message name_msg{NameMessage,name.value("name")};
        sendMessage(m_tcp,name_msg);
        connect(m_tcp,&QTcpSocket::readyRead,this,[=]()
        {
            receiveMessage(m_tcp);
        });














    });

}
void joinRoom::tab_1()
{

    auto vbox=new QVBoxLayout;
    auto delegate=new MyItemDelegate;
    auto list=new QListView;
    list->setModel(model);
    list->setItemDelegate(delegate);
    ui->tab->setLayout(vbox);
    vbox->addWidget(list);

}

void joinRoom::tab_2()
{
    ui->verticalLayout_3->addWidget(g_s);

}
void joinRoom::receiveMessage(QTcpSocket* socket) {
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    if (socket->bytesAvailable() < sizeof(quint16))
        return;

    quint16 blockSize;
    in >> blockSize;

    if (socket->bytesAvailable() < blockSize)
        return;

    quint8 type;
    QVariant data;
    in >> type >> data;

    Message message;
    message.type = static_cast<MessageType>(type);
    message.data = data;
    qDebug()<<"joinRoom:收到消息"<<message.type;
    // 处理接收到的消息
    switch (message.type) {
    case NameMessage:
        break;
    case settingMessage:
        recive_setting(message.data);
        break;
    case ListUpdateMessage:
        recive_update(message.data);
        break;
    case gameStatusMessage:
        recive_gamestart();
        break;
    case posSelected:
    {
        recive_pos(message.data);
        break;
    }
    case nowStatus:
    {
        recive_status(message.data);
        break;
    }
    case herorandom:
    {
        qDebug()<<"receive:hero";
        recive_heroSeq(message.data);
        break;
    }
    case skillSelected:
    {
        qDebug()<<"receive:skill";
        receive_skillSelect(message.data);
        break;
    }
    default:

        break;
    }
}

void joinRoom::sendMessage(QTcpSocket* socket, const Message& message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    out << static_cast<quint16>(0); // 占位符
    out << static_cast<quint8>(message.type);
    out << message.data;

    out.device()->seek(0);
    out << static_cast<quint16>(block.size() - sizeof(quint16));

    socket->write(block);
}

void joinRoom::recive_update(QVariant data)
{
    QString allNamesString = data.toString();
    QStringList allNames = allNamesString.split(',');
    qDebug()<<allNames;
    // 更新客户端的列表
    model->clear();

    foreach (const QString &name, allNames) {
        auto item=new QStandardItem;
        item->setData(name,Qt::ItemDataRole::DisplayRole);
        model->appendRow(item);
    }
}

void joinRoom::recive_setting(QVariant data)
{
    QString indexString=data.toString();
    ruleCode=indexString;
    qDebug()<<"rulecode:"<<ruleCode;
    g_s->reset_index(indexString);

}

void joinRoom::recive_gamestart()
{
    thisRound= new Round(ruleCode,model->rowCount(),model->item(0)->data(Qt::DisplayRole).toString());
    thisRound->show();
    connect(thisRound,&Round::PositionSelected,this,[=](int serialnum)
            {
                playernum=serialnum;
                Message pos={posSelected,serialnum};
                sendMessage(m_tcp,pos);
            });
    connect(thisRound,&Round::status_change,this,[=](player_status p_s)
            {
        int symbol;
        switch (p_s) {
        case prepared:
            symbol=1;
            break;
        case wait_for_choose:
            symbol=2;
            break;
        case choosing:
            symbol=3;
            break;
        default:
            break;
        }
        Message msg{nowStatus,QString::number(symbol)};
        sendMessage(m_tcp,msg);
        });
    connect(thisRound,&Round::skillSelected,this,[=](int index)
    {
        Message msg{skillSelected,QString::number(playernum)+QString::number(index)};
        sendMessage(m_tcp,msg);
    });
}

void joinRoom::recive_pos(QVariant data)
{
    qDebug()<<data;
    int pos=data.toString().mid(0,1).toInt();
    QString name=data.toString().remove(0,1);
    if(thisRound->Posdatas[pos]->posStatus==1)
    {
        thisRound->Posdatas[pos]->posStatus=pre_posed;

        thisRound->Posdatas[name.toInt()]->posStatus=unprepared;
        thisRound->Posdatas[name.toInt()]->playername=thisRound->Posdatas[pos]->playername;
    }
    else
    {
        qDebug()<<"joinroom收到位置确认消息";

        thisRound->Posdatas[pos]->posStatus=unprepared;
        thisRound->Posdatas[pos]->playername=name;

    }
    thisRound->update();
}

void joinRoom::recive_status(QVariant data)
{
    qDebug()<<"joinroom收到status:"<<data;
    int pos=data.toString().mid(0,1).toInt();
    int status=data.toString().mid(1,1).toInt();
    switch (status) {
    case 1:
    {
        thisRound->Posdatas[pos]->posStatus=prepared;

        thisRound->update();
        break;
    }
    case 2:
    {
        thisRound->Posdatas[pos]->posStatus=wait_for_choose;
        break;
    }
    case 3:
    {
       thisRound->Posdatas[pos]->posStatus=choosing;
        break;
    }
    default:
        break;
    }

}

void joinRoom::recive_heroSeq(QVariant data)
{
    foreach (positiondata* pos, thisRound->Posdatas) {
        pos->posStatus=wait_for_choose;
    }
    thisRound->status=wait_for_choose;
    thisRound->random_seq=data.toString().split(",");
    for(int i=0;i<thisRound->random_seq.count();i++)
    {
        thisRound->display->append_hero(thisRound->get_Pic(i,1),thisRound->get_skill(i));
    }
    thisRound->update();





}

void joinRoom::receive_skillSelect(QVariant data)
{
    int pos=data.toString().mid(0,1).toInt();
    int buttonId=data.toString().remove(0,1).toInt();

    int heroNum=0;
    int skillNum=0;
    if(buttonId<100)
    {
         heroNum=buttonId/10;
         skillNum=buttonId%10;
    }
    else
    {

    }
    thisRound->display->btns->button(buttonId)->setEnabled(false);
    thisRound->Posdatas[pos]->player_skills->append(thisRound->get_skill(heroNum)->at(skillNum));
    thisRound->update_SD(pos);
}
joinRoom::~joinRoom()
{
    delete ui;
    m_tcp->close();
    m_tcp->deleteLater();
}
