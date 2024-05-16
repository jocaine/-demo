#include "mainRoom.h"
#include "ui_mainRoom.h"
#include"joinRoom.h"
#include"createRoom.h"
mainRoom::mainRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainRoom)
{
    ui->setupUi(this);

    //设置创建房间按钮和加入房间按钮，并且连接槽
    ui->createRoom->setIcon(QPixmap("://Resources/pic/croom.png"));
    ui->createRoom->setIconSize(QSize(this->width()/2.3,this->width()/2.3));
    ui->createRoom->setFixedSize(QSize(this->width()/2.8,this->width()/2.8));
    ui->createRoom->setFlat(true);
    ui->createRoom->setObjectName("link");

    ui->joinRoom->setFixedSize(QSize(this->width()/2.8,this->width()/2.8));
    ui->joinRoom->setIconSize(QSize(this->width()/2.6,this->width()/2.6));
    ui->joinRoom->setIcon(QPixmap("://Resources/pic/join.png"));
    ui->joinRoom->setFlat(true);
    ui->joinRoom->setObjectName("link");
}

mainRoom::~mainRoom()
{
    delete ui;
}

void mainRoom::on_createRoom_clicked()
{
    createRoom* server=new createRoom(this);
    server->show();
}


void mainRoom::on_joinRoom_clicked()
{
    joinRoom* client=new joinRoom(this);
    client->show();
}

