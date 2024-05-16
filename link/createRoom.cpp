#include "createRoom.h"
#include "ui_createRoom.h"
#include <QHostAddress>
#include<QDebug>
#include<QHostInfo>
#include <QNetworkInterface>
#include<QTabBar>
#include<QRandomGenerator>

#include <QHostAddress>
#include <QLabel>
#include<QListView>
createRoom::createRoom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::createRoom),
    model(new QStandardItemModel(qApp)),
    start(new QPushButton("开始游戏",this))
{
    this->setWindowTitle("server");
    ui->setupUi(this);
    tab_1();
    tab_2();
    init_Linkusers();
    auto server=new QTcpServer(this);
    m_udp = new QUdpSocket(this);
    //启动udp像广播过来的客户端发送回复，使得客户端确定服务器的ip地址和端口再通过tcp连接
    m_udp->bind(45454, QUdpSocket::ShareAddress);
    connect(m_udp, &QUdpSocket::readyRead, this,[=]
    {

        while (m_udp->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(m_udp->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;
            m_udp->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

            if (datagram == "RoomRequest") {
                // Reply with room information

                QString roomResponse = "RoomResponse " + QHostInfo::localHostName().toUtf8();
                m_udp->writeDatagram(roomResponse.toUtf8(),sender,senderPort);

            }
        }
    });
    QHostAddress add;
    for(int i=0;i<QNetworkInterface().allAddresses().count();i++)
    {
        if(QNetworkInterface().allAddresses().at(i).toString()=="127.0.0.1"||QNetworkInterface().allAddresses().at(i).toString()=="::1")continue;
        add=QNetworkInterface().allAddresses().at(i);
    }
    server->listen(add,3366);


    connect(server,&QTcpServer::newConnection,this,[=]()
    {

        auto newclient= server->nextPendingConnection();
        clients.append(newclient);
        qDebug()<<newclient;
        connect(newclient,&QTcpSocket::readyRead,this,[=]()
        {
            receiveMessage(newclient);
        });
    });

    connect(start,&QPushButton::clicked,this,[=]()
    {

        Message start{gameStatusMessage,"0"};
        thisRound=new Round(rulecode,model->rowCount(),model->item(0)->data(Qt::DisplayRole).toString());
        thisRound->status=unprepared;
        thisRound->player_number=0;
        thisRound->show();

       for(int i=1;i<model->rowCount();i++)
       {
            Link_users.append(new Link_user(clients[i-1],-1,model->item(i)->data(Qt::DisplayRole).toString(),pre_posed));
           Link_users[i]->userName=model->item(i)->data(Qt::DisplayRole).toString();
           start.data=i;
           sendMessage(clients[i-1],start);
           qDebug()<<"link-user"<<i<<Link_users[i]->userSocket<<Link_users[i]->userName<<Link_users[i]->PositionNum;
       }

       connect(thisRound,&Round::status_change,this,[=](player_status p_s)
               {
                   int symbol;
                   switch (p_s)
                   {
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
                   if(thisRound->isAllstatus(2))
                   {
                       foreach (positiondata* pos, thisRound->Posdatas) {
                           pos->posStatus=wait_for_choose;
                       }
                       foreach (Link_user* user, Link_users) {
                           user->user_status=wait_for_choose;
                       }
                       randomProducter();
                       thisRound->status=wait_for_choose;
                       for(int i=0;i<thisRound->random_seq.count();i++)
                       {
                           thisRound->display->append_hero(thisRound->get_Pic(i,1),thisRound->get_skill(i));
                       }
                       thisRound->update();

                   }
                   else
                   {
                   Message msg{nowStatus,"0"+QString::number(symbol)};
                   sendToAll(msg);
                   }

                });
       connect(thisRound,&Round::skillSelected,this,[=](int index)
               {
                Message msg{skillSelected,QString::number(0)+QString::number(index)};
                sendToAll(msg);
               });

    });
}
createRoom::~createRoom()
{
    delete ui;
    foreach(QTcpSocket* tcp,clients)
    {
        tcp->close();
        tcp->deleteLater();
    }
}

void createRoom::tab_1()
{
    ui->tabWidget->tabBar()->setExpanding(true);
    auto vbox=new QVBoxLayout;
    auto delegate=new MyItemDelegate;
    auto list=new QListView;
    list->setModel(model);
    list->setItemDelegate(delegate);
    ui->tab->setLayout(vbox);
    vbox->addWidget(list);
    vbox->addWidget(start);
    auto me=new QStandardItem();
    auto name=new QSettings{"tlr","name"};
    me->setData(name->value("name"),Qt::ItemDataRole::DisplayRole);
    model->appendRow(me);
}

void createRoom::tab_2()
{
    auto arch=new archiev_list(1);
    ui->verticalLayout_3->addWidget(arch);
    connect(arch,&archiev_list::l_ok,this,[=]()
    {
        QString indexString;


        for(int i=0;i<arch->g_s->comboBoxes.count();i++)
        {
            indexString+=QString::number(arch->g_s->comboBoxes[i]->currentIndex());

        }
        rulecode=indexString;
        Message msg{settingMessage,indexString};
        sendToAll(msg);
    });

}


void createRoom::receiveMessage(QTcpSocket* socket) {
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

    // 处理接收到的消息
    switch (message.type) {
    case NameMessage:
        recive_name(message.data);

        break;
    case settingMessage:

        break;
    case ListUpdateMessage:

        break;
    case posSelected:
    {
        int index=clients.indexOf(socket)+1;
        receive_pos(index,message.data);
        break;
    }
    case nowStatus:
    {
        int index=clients.indexOf(socket)+1;
        receive_status(index,message.data);
        break;
    }
    case skillSelected:
    {
        int index=clients.indexOf(socket)+1;
        receive_skillSelected(index,message.data);
    }
    default:

        break;
    }
}

void createRoom::sendMessage(QTcpSocket* socket, const Message& message)
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

void createRoom::init_Linkusers()
{
    Link_users.append(new Link_user{nullptr,-1,model->item(0)->data(Qt::DisplayRole).toString(),pre_posed});
}

void createRoom::sendToAll(const Message &message)
{
    foreach(QTcpSocket* tcp,clients)
    {
        sendMessage(tcp,message);
    }
}

void createRoom::sendToOthers(int index, const Message &message)
{
    for(int i=0;i<clients.count();i++)
    {
        if(index==i)continue;
        sendMessage(clients[i],message);
    }
}

void createRoom::recive_name(QVariant data)
{
    QStandardItem* newplayer=new QStandardItem;
    model->appendRow(newplayer);
    newplayer->setData(data.toString(),Qt::ItemDataRole::DisplayRole);
    QStringList nameList;
    for(int i=0;i<model->rowCount();i++)
    {
        nameList.append(model->item(i)->data(Qt::DisplayRole).toString());
    }
    QString allnames=nameList.join(",");
    Message update_msg{ListUpdateMessage,allnames};
    sendToAll(update_msg);

}

void createRoom::receive_pos(int index,QVariant data)
{
    qDebug()<<"recive:"<<Link_users[index]->PositionNum<<Link_users[index]->userName;
    //1.判断这个用户是否占用了某个位置
    if(Link_users[index]->PositionNum!=-1)
    {
        thisRound->Posdatas[Link_users[index]->PositionNum]->posStatus=pre_posed;
        Message repos={posSelected,QString::number(Link_users[index]->PositionNum)+data.toString()};
        qDebug()<<"send"<<repos.data;
        sendToOthers(index-1,repos);
    }
    else{
        Message Pos={posSelected,data.toString()+Link_users[index]->userName};
        sendToOthers(index-1,Pos);
    }
    Link_users[index]->PositionNum=data.toInt();
    thisRound->Posdatas[data.toInt()]->posStatus=unprepared;
    thisRound->Posdatas[data.toInt()]->playername=Link_users[index]->userName;
    thisRound->update();
    qDebug()<<data.toString()+Link_users[index]->userName;
}

void createRoom::receive_status(int index, QVariant status)
{
    int statusint=status.toInt();
    switch (statusint) {
    case 1:
    {
        Link_users[index]->user_status=prepared;
        thisRound->Posdatas[Link_users[index]->PositionNum]->posStatus=prepared;
        if(thisRound->isAllstatus(2))
        {
            foreach (positiondata* pos, thisRound->Posdatas) {
                pos->posStatus=wait_for_choose;
            }
            foreach (Link_user* user, Link_users) {
                user->user_status=wait_for_choose;
            }
            thisRound->status=wait_for_choose;
            for(int i=0;i<thisRound->random_seq.count();i++)
            {
                thisRound->display->append_hero(thisRound->get_Pic(i,1),thisRound->get_skill(i));
            }
            //for(int i=0;i<thisRound->Posdatas.count();i++)
            //{
            //    thisRound->skill_layout->addWidget();
            //}
            randomProducter();
        }
        else
        {
        Message msg{nowStatus,QString::number(Link_users[index]->PositionNum)+QString::number(statusint)};
        sendToOthers(index-1,msg);
        }
        thisRound->update();
        break;
    }
    case 2:
    {
        Link_users[index]->user_status=wait_for_choose;
        thisRound->Posdatas[Link_users[index]->PositionNum]->posStatus=wait_for_choose;
        Message msg{nowStatus,QString::number(Link_users[index]->PositionNum)+QString::number(statusint)};
        sendToOthers(index-1,msg);
        break;
    }
    case 3:
    {
        Link_users[index]->user_status=choosing;
        thisRound->Posdatas[Link_users[index]->PositionNum]->posStatus=choosing;
        Message msg{nowStatus,QString::number(Link_users[index]->PositionNum)+QString::number(statusint)};
        sendToOthers(index-1,msg);
        break;
    }
    default:
        break;
    }
}

void createRoom::receive_skillSelected(int index, QVariant data)
{
    int pos=data.toString().mid(0,1).toInt();
    int buttonId=data.toString().remove(0,1).toInt();

    int heroNum=0;
    int skillNum=0;
    if(buttonId<100)
    {
        int heroNum=buttonId/10;
        int skillNum=buttonId%10;
        qDebug()<<"heronum"<<heroNum<<"skillnum"<<skillNum;
    }
    else
    {

    }
    thisRound->display->btns->button(buttonId)->setEnabled(false);
    thisRound->Posdatas[pos]->player_skills->append(thisRound->get_skill(heroNum)->at(skillNum));
    thisRound->update_SD(pos);

    Message msg{skillSelected,data};
    sendToOthers(index-1,msg);
}

void createRoom::randomProducter()
{
    int N;
    int set=rulecode.mid(2,1).toInt();
    switch (set) {
    case 0:
        N=Link_users.count();
        break;
    case 1:
        N=Link_users.count()+1;
        break;
    case 2:
        N=Link_users.count()+2;
        break;
    default:
        break;
    }
    QSet<int> intset;
    QStringList str_l;
    while (intset.size() < N)
    {
        int randomNumber = QRandomGenerator::global()->bounded(25); // 生成0-25之间的随机数
        if (!intset.contains(randomNumber)) {
            intset.insert(randomNumber);
        }
    }
    foreach (int num, intset) {
        str_l.append(QString::number(num));
    }
    QString randomNumber=str_l.join(",");
    thisRound->random_seq=str_l;
    Message msg{herorandom,randomNumber};
    qDebug()<<"send:"<<randomNumber;
    qDebug()<<thisRound->random_seq;
    sendToAll(msg);

}
