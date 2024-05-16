#ifndef CREATEROOM_H
#define CREATEROOM_H

#include <QMainWindow>
#include<QTcpServer>
#include<QTcpSocket>
#include<QUdpSocket>

#include"delegate.h"
#include"message.h"
#include"archive.h"
#include"round.h"

namespace Ui {
class createRoom;
}

class createRoom : public QMainWindow
{
    Q_OBJECT

public:
    explicit createRoom(QWidget *parent = nullptr);
    ~createRoom();

private:
    Ui::createRoom *ui;
    QTcpSocket* m_tcp;
    QUdpSocket* m_udp;
    QList<QTcpSocket*> clients;
    QList<Link_user*> Link_users;
    QStandardItemModel* model;
    QPushButton* start;
    QString rulecode;
    Round* thisRound;
    void tab_1();
    void tab_2();
    void receiveMessage(QTcpSocket* socket);
    void sendMessage(QTcpSocket* socket, const Message& message);
private:
    void init_Linkusers();
    void sendToAll(const Message& message);
    void sendToOthers(int index,const Message& message);
    void recive_name(QVariant);
    void receive_pos(int index,QVariant);
    void receive_status(int index,QVariant);
    void receive_skillSelected(int index,QVariant);
    void randomProducter();


};

#endif // CREATEROOM_H
