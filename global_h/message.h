#ifndef MESSAGE_H
#define MESSAGE_H
#include<QTcpSocket>
#include<QDataStream>
#include<QVariant>
enum MessageType
{
    NameMessage,//客户端向服务器发送自己的用户名
    settingMessage,//服务器向客户端发送本局游戏配置信息
    ListUpdateMessage,//每当有新加入的用户，服务器再收到NameMessage后，向所有用户发送，更新列表；或用户交换位置后发送给服务器更新列表
    gameStatusMessage,//bool类型，1表示游戏开始，0表示游戏结束
    posSelected,
    nowStatus,
    herorandom,
    skillSelected,
};
enum player_status
{
    pre_posed,//未选择位置状态
    unprepared,//未准备状态
    prepared,//准备状态
    wait_for_choose,//等待选择技能状态
    choosing,//正在选择状态
};
struct Message
{
    MessageType type;
    QVariant data;
};

struct Link_user
{
    Link_user();
    Link_user(QTcpSocket* tcp,int num ,QString str,player_status ps)
        :userSocket(tcp)
        ,PositionNum(num)
        ,userName(str)
        ,user_status(ps)
    {

    }
    QTcpSocket* userSocket;
    int PositionNum;
    QString userName;
    player_status user_status;

};

#endif // MESSAGE_H
