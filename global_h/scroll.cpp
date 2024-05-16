#include"scroll.h"
#include<QScreen>
#include <QEvent>
#include <QTouchEvent>
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include<QFile>


scroll::scroll(QWidget *parent)
    :QWidget(parent)
    ,index(0),
    slayout(new QStackedLayout)
    ,btns(new QButtonGroup(this))

{
    this->setAttribute(Qt::WA_AcceptTouchEvents);
    QFile* file=new QFile("://qss/round.css"); // 替换为您的CSS文件路径

    if (file->open(QIODevice::ReadOnly)) {
        setStyleSheet(file->readAll());
        file->close();
    } else {
        qWarning() << "Failed to load CSS file";
    }
    //this->setStyleSheet("QWidget{background-color: rgba(0, 0, 0, 100);border-radius: 30px; }QLabel{background-color: rgba(0, 0, 0, 0);}");
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedWidth(350);
    auto vbox=new QVBoxLayout;
    this->setLayout(vbox);
    vbox->setContentsMargins(0,0,0,0);
    vbox->addLayout(slayout);
    connect(btns,&QButtonGroup::idClicked,this,[=](int index)
    {
        qDebug()<<"按钮"<<index<<"被点击";
        emit button_index(index);
    });
}


void scroll::append_hero(QPixmap *pix,QList<skill*>* skills)
{
    auto wid=new QWidget;
    auto label=new QLabel;
    auto vbox=new QVBoxLayout;
    vbox->setContentsMargins(0,0,0,0);
    label->setFixedSize(QSize(350,476));
    label->setScaledContents(true);
    label->setPixmap(*pix);

    vbox->addWidget(label);
    for(int i=0;i<skills->count();i++)
    {
        auto v_box=new QVBoxLayout;
        QHBoxLayout* hbox=new QHBoxLayout;
        button* btn=skills->at(i)->btn;
        auto label=skills->at(i)->label;

        btns->addButton(btn,(QString::number(num)+QString::number(i)).toInt());
        hbox->addWidget(btn);

        auto blood=new QLabel;
        blood->setPixmap(QPixmap("://figpic/rBlood.png"));
        hbox->addWidget(blood);
        auto count=new QLabel("x"+QString::number(skills->at(i)->point));
        hbox->addWidget(count);
        hbox->addStretch();
        qDebug()<<"skills->at(i)->point"<<skills->at(i)->point;
        v_box->addLayout(hbox);

        v_box->addWidget(skills->at(i)->label);
        vbox->addStretch();
        vbox->addLayout(v_box);
        vbox->addStretch();

    }
    wid->setLayout(vbox);
    wids.append(wid);
    slayout->addWidget(wid);
    num++;
}

bool scroll::event(QEvent *ev)
{
    QEvent::Type type=ev->type();
    switch(type)
    {
    case QEvent::TouchBegin:
        ev->accept();
        return true;
    case QEvent::TouchUpdate:
        ev->accept();
        return true;
    case QEvent::TouchEnd:
        ev->accept();
        dumpTouch_updateEvent(ev);
        return true;
    case QEvent::TouchCancel:
        ev->accept();
        return true;
    default:
        break;
    }
    return QWidget::event(ev);
}

bool scroll::dumpTouch_updateEvent(QEvent *ev)
{
    if (QTouchEvent* te = static_cast<QTouchEvent*>(ev)) {

        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int screenWidth = screenGeometry.width();
        int screenHeight = screenGeometry.height();
        auto point = te->points().at(0);
        qreal deltaX = point.lastPosition().x() - point.pressPosition().x();
        qreal deltaY = point.lastPosition().y() - point.pressPosition().y();
        qreal press_distance_ = QLineF(point.lastPosition(), point.pressPosition()).length();
        if(qAbs(deltaY)>screenWidth/5)
        {

            if(deltaY<0)emit hide();

        }
        else{
            qDebug()<<"切换";
        if(deltaX>0)
        {
            index=(index-1+num)%num;
            slayout->setCurrentIndex(index);
        }
        else
        {
            index=(index+1)%num;
            slayout->setCurrentIndex(index);
        }
        }
    }
    return false;
}

