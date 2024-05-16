#ifndef JOINROOM_H
#define JOINROOM_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QTcpSocket>
#include"message.h"
#include"delegate.h"
#include"gameSetting.h"
#include"round.h"
namespace Ui {
class joinRoom;
}

class joinRoom : public QMainWindow
{
    Q_OBJECT

public:
    explicit joinRoom(QWidget *parent = nullptr);
    ~joinRoom();

private:
    Ui::joinRoom *ui;
    QUdpSocket *m_udp;
    QTcpSocket *m_tcp;
    QStandardItemModel* model;
    gameSetting* g_s;
    QString ruleCode;
    Round* thisRound;
    int playernum;
private:
    void tab_1();
    void tab_2();
    void receiveMessage(QTcpSocket* socket);
    void sendMessage(QTcpSocket* socket, const Message& message);
private:
    void recive_update(QVariant);
    void recive_setting(QVariant);
    void recive_gamestart();
    void recive_pos(QVariant);
    void recive_status(QVariant);
    void recive_heroSeq(QVariant);
    void receive_skillSelect(QVariant);
};

#endif // JOINROOM_H
