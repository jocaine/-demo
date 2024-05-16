#include "gameRound.h"
#include "ui_gameRound.h"
#include<QDialog>
#include <QPushButton>



gameRound::gameRound(QString indexString,int num,int myNumber,QWidget *parent)
    :QWidget(parent),
    player_number(myNumber),
    ui(new Ui::gameRound)
{
    ui->setupUi(this);
    explianer(indexString,num);
    //1.排位置
    //2.开启定时器
    //3.装填本局hero


}

void gameRound::explianer(QString indexString,int num)
{
    int gamePattern=indexString.mid(0,1).toInt();
    int heroRange=indexString.mid(1,1).toInt();
    int heroNum=indexString.mid(2,1).toInt();
    int prepareTime=indexString.mid(3,1).toInt();
    int selectTime=indexString.mid(4,1).toInt();
    int baseCount=indexString.mid(5,1).toInt();
    int extraCount=indexString.mid(6,1).toInt();
    int skillCheckable=indexString.mid(7,1).toInt();
    int direction=indexString.mid(8,1).toInt();
    int priority=indexString.mid(9,1).toInt();

    switch(gamePattern)                     //游戏模式
    {
    case 0: //身份模式
        switch(priority)                   //主公优先级
        {
        case 0:  //主公最优先
        {auto king=new QDialog(this);
            auto btn=new QPushButton("我是主公",king);
            connect(btn,&QPushButton::clicked,this,[=]()
                    {
                        myturn=true;
                        emit imKing();
                        king->close();

                    });
            connect(this,&gameRound::notKing,this,[=]()
                    {
                        myturn=false;
                        king->close();
                    });

            break;
        }
        case 1:  //主公最不优先
        {
            auto king=new QDialog(this);
            auto btn=new QPushButton("我是主公",king);
            btn->setFixedSize(80,80);
            connect(btn,&QPushButton::clicked,this,[=]()
                    {
                        myturn=true;
                        emit imKing();
                        king->close();

                    });
            connect(this,&gameRound::notKing,this,[=]()
                    {
                        myturn=false;
                        king->close();
                    });

            break;
        }
        case 2:  //随机
        {

        }
        break;
        }
        break;
    case 1://阵营模式
        break;
    }

    switch(heroRange)                       //英雄范围
    {
    case 0:   //经典
        heroRange_num=25;
        break;
    case 1:   //烽火山岭
        break;
    case 2:   //混合
        break;
    }
    switch(heroNum)                         //英雄数量
    {
    case 0:   //num
        heroNum=num;
        break;
    case 1:   //num+1
        heroNum=num+1;
        break;
    case 2:   //num+2
        heroNum=num+2;
        break;
    }
    switch(prepareTime)                         //准备时长
    {
    case 0:   //15N
        prepareTime_num=heroNum*15000;
        break;
    case 1:   //1min
        prepareTime_num=60000;
        break;
    case 2:   //1.5min
        prepareTime_num=90000;
        break;
    case 3:   //2min
        prepareTime_num=120000;
        break;
    case 4:   //2.5min
        prepareTime_num=150000;
        break;
    case 5:   //3min
        prepareTime_num=180000;
        break;
    }
    switch(selectTime)                         //选择时长
    {
    case 0:   //5s
        selectTime_num=5000;
        break;
    case 1:   //10s
        selectTime_num=10000;
        break;
    case 2:   //15s
        selectTime_num=15000;
        break;
    case 3:   //20s
        selectTime_num=20000;
        break;
    }
    switch(baseCount)                         //基础点数
    {
    case 0:   //7
        baseCount_num=7;
        break;
    case 1:   //6
        baseCount_num=6;
        break;
    case 2:   //8
        baseCount_num=8;
        break;
    case 3:   //9
        baseCount_num=9;
        break;
    }
    switch(extraCount)                         //额外点数
    {
    case 0:   //1
        extraCount_num=baseCount_num+1;
        break;
    case 1:   //0
        extraCount_num=baseCount_num+0;
        break;
    case 2:   //2
        extraCount_num=baseCount_num+2;
        break;
    case 3:   //3
        extraCount_num=baseCount_num+3;
        break;
    }
    switch(skillCheckable)                         //技能可复选
    {
    case 0:   //不可
        skillCheckable_num=999;
        break;
    case 1:   //无代价
        skillCheckable=0;
        break;
    case 2:   //代价1
        skillCheckable_num=1;
        break;
    case 3:   //代价2
        skillCheckable_num=2;
        break;
    case 4:   //代价3
        skillCheckable_num=3;
        break;
    }
    switch(direction)                         //方向
    {
    case 0:   //顺时针
        direction_num=0;
        break;
    case 1:   //逆时针
        direction_num=1;
        break;
    }
}
gameRound::~gameRound()
{
    delete ui;
}
