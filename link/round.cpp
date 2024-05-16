#include"round.h"
#include<QDialog>
#include <QPushButton>
#include<QPointer>
#include <QPainterPath>
#include <QSettings>
#include <QVBoxLayout>
Round::Round(QString indexString,int num,QString masterName,QWidget *parent)
    :QWidget(parent),
    player_number(-1),
    direction(true),
    turnwheel(new QTimer(this)),
    player_count(num),
    display(new class scroll()),
    skill_display(new QWidget),
    slayout(new QStackedLayout)
{
    this->setAttribute(Qt::WA_AcceptTouchEvents);
    explianer(indexString,num);
    init_circleCenter();
    initPosdatas(masterName);
    init_Slayout();

    roundHander=new heroHander;
    auto bt=new QPushButton("zhan!",this);
    auto bts=new QPushButton("change",this);
    bts->move(100,0);
    turnwheel->setInterval(1000/60);
    pix=new QPixmap("://icon/prepare.png");


    auto vbox=new QVBoxLayout;
    this->setLayout(vbox);

    vbox->addWidget(display);
    vbox->addWidget(skill_display);
    vbox->setAlignment(skill_display,Qt::AlignBottom);
    display->setVisible(false);
    skill_display->setVisible(false);

    //1.排位置
    //2.开启定时器
    //3.装填本局hero





















    connect(bt,&QPushButton::clicked,this,[=]()
    {
        turnwheel->start();
    });
    connect(bts,&QPushButton::clicked,this,[=]()
            {
        if(direction)direction=false;
        else direction=true;
        display->setVisible(true);
            });
    connect(this,&Round::timeout,this,[=]()
            {
                turnwheel->stop();
            });
    connect(turnwheel,&QTimer::timeout,this,&Round::on_timeout);
    connect(display,&scroll::hide,this,[=]()
            {
        display->setVisible(false);
            });
    connect(display,&scroll::button_index,this,[=](int index)
            {
        emit skillSelected(index);
        if(status==choosing)
        { }
        int heroNum=0;
        int skillNum=0;
            if(index<100)
            {
                heroNum=index/10;
                skillNum=index%10;

            }
            else
            {

            }
            qDebug()<<player_number;
            display->btns->button(index)->setEnabled(false);
            Posdatas.at(player_number)->player_skills->append(get_skill(heroNum)->at(skillNum));
            update_SD(player_number);
            qDebug()<<get_skill(heroNum)->at(skillNum)->btn->text();
            });

}

void Round::explianer(QString indexString,int num)
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
            connect(this,&Round::notKing,this,[=]()
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
            connect(this,&Round::notKing,this,[=]()
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

bool Round::event(QEvent *ev)
{
    QEvent::Type type=ev->type();
    switch(type)
    {
    case QEvent::TouchBegin:
        ev->accept();
        dump_touchBegin(ev);
        return true;
    case QEvent::TouchUpdate:
        ev->accept();

        return true;
    case QEvent::TouchEnd:
        ev->accept();
        dump_touchEnd(ev);
        return true;
    case QEvent::TouchCancel:
        ev->accept();
        return true;
    default:
        break;
    }
    return QWidget::event(ev);
}

void Round::mousePressEvent(QMouseEvent *event)
{

        QPointF touchPoint = event->position(); // 获取触摸点的坐标
        // 内圆的边界框
        int innerCircleX = width() / 2 ;
        int innerCircleY = height() / 2 ;
        QPointF inner_center(innerCircleX,innerCircleY);
        qreal inner_distance = QLineF(inner_center, touchPoint).length();

        // 检查触摸点是否在内圆的边界框内
        if (inner_distance<innerRadius) {
            // 触摸到了内圆，执行相应的操作
            if(status==pre_posed)
            {

            }
            else if(status==unprepared)
            {
                status=prepared;
                qDebug()<<player_number;
                Posdatas[player_number]->posStatus=prepared;
                update();
                emit status_change(status);

            }
            else if(status==prepared)
            {


            }
            else if(status==wait_for_choose)
            {


            }
            else if(status==choosing)
            {

            }
            qDebug() << "点击内圆"<<innerCircleX<<innerCircleY<<inner_distance<<innerRadius;
            qDebug()<<"当前状态："<<status;
            return;
        }


        // 八个圆的边界框
        for(int i=0;i<circleCenters.count();i++) {
            qreal circle_distance = QLineF(circleCenters[i]->toPoint(), touchPoint).length();
            if (circle_distance<circleRadius) {
                // 触摸到了八个圆中的一个，执行相应的操作
                selectPosition(i);
                qDebug() << "点击圆 " << i<<circle_distance<<circleRadius;
            }
        }
        QWidget::mousePressEvent(event);
}



void Round::paintEvent(QPaintEvent *event)
{

        Q_UNUSED(event);       //如果参数没有被用到会发出警告
        QPainter painter(this);
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int screenWidth = screenGeometry.width();
        int screenHeight = screenGeometry.height();
        innerRadius = 0.6*outerRadius; // 内圆半径
        // 计算大圆半径
        outerRadius = qMin(screenWidth, screenHeight) / 2;
        circleRadius = 0.275*outerRadius; // 圆的半径
        // 设置画笔
        painter.setPen(QPen(Qt::black,4));

        // 绘制外圆
        painter.drawEllipse(QPointF(screenWidth/2, screenHeight/2), outerRadius,outerRadius);
        // 绘制内圆
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(QPointF(screenWidth/2, screenHeight/2), innerRadius , innerRadius);
        // 绘制八个圆
        painter.setPen(QPen(Qt::black,4));
        double angleIncrement = 2 * 3.14159265 /player_count;
        for (int i = 0; i < player_count; ++i) {
            if(Posdatas[i]->posStatus==pre_posed)
            {
               painter.drawEllipse(circleCenters[i]->toPoint(), circleRadius, circleRadius);

            }
            else if(Posdatas[i]->posStatus==unprepared)
            {
                painter.setPen(QPen(Qt::yellow,4));
                painter.drawEllipse(circleCenters[i]->toPoint(), circleRadius, circleRadius);
                painter.setPen(QPen(Qt::black,4));
                painter.setFont(QFont("LiSu",20));
                painter.drawText(circleCenters[i]->toPoint().x()-(5*circleRadius)/9,circleCenters[i]->toPoint().y()+(circleRadius)/5,Posdatas[i]->playername);
            }
            else if(Posdatas[i]->posStatus==prepared)
            {
                painter.setPen(QPen(Qt::yellow,4));
                painter.drawEllipse(circleCenters[i]->toPoint(), circleRadius, circleRadius);
                painter.setPen(QPen(Qt::black,4));
                painter.setFont(QFont("LiSu",20));
                painter.drawText(circleCenters[i]->toPoint().x()-(5*circleRadius)/9,circleCenters[i]->toPoint().y()+(circleRadius)/5,Posdatas[i]->playername);
                painter.drawPixmap(circleCenters[i]->x()-circleRadius,circleCenters[i]->y()-circleRadius,2*circleRadius,2*circleRadius,QPixmap("://icon/ok.png"));
            }
            else if(Posdatas[i]->posStatus==wait_for_choose)
            {
                painter.setPen(QPen(Qt::yellow,4));
                painter.drawEllipse(circleCenters[i]->toPoint(), circleRadius, circleRadius);
                painter.setPen(QPen(Qt::black,4));
                painter.setFont(QFont("LiSu",20));
                painter.drawText(circleCenters[i]->toPoint().x()-(5*circleRadius)/9,circleCenters[i]->toPoint().y()+(circleRadius)/5,Posdatas[i]->playername);
            }
        }

        QPixmap pix_(pix->width(),pix->height());
        pix_.fill(Qt::transparent);

        QPainter picPainter(&pix_);
        picPainter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
        QPainterPath path;
        // 设置圆形半径，取源图片宽度和高度中，较大者的一半作为裁切半径
        int radius = pix->height() < pix->width() ? pix->height() / 2 : pix->width() / 2;
        path.addEllipse(QPoint(pix_.rect().center().x(),radius), radius, radius);  // 绘制裁切区域的大小
        picPainter.setClipPath(path);
        if(status==wait_for_choose)
        {
            qDebug()<<"update";
            pix=get_Pic(heronum,0);
        }
        picPainter.drawPixmap(pix_.rect(), *pix);

        painter.drawPixmap(screenWidth/2-innerRadius, screenHeight/2-innerRadius,innerRadius*2,innerRadius*3,pix_);



}
void Round::init_circleCenter()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    innerRadius = 0.6*outerRadius; // 内圆半径
    // 计算大圆半径
    outerRadius = qMin(screenWidth, screenHeight) / 2;
    circleRadius = 0.275*outerRadius; // 圆的半径
    for (int i = 0; i < player_count; ++i) {
        circleCenters.append(new QPointF(screenWidth/2,screenHeight/2));
    }
    turn_circleCenter(direction);
}

void Round::turn_circleCenter(bool direction)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    int numCircles = player_count; // 圆的数量
    double angleDefault = 2 * 3.14159265 /numCircles; // 圆之间的角度增量
    for (int i = 0; i < numCircles; ++i) {
        double angle;
        if(direction){ //true顺时针转动
            angle= i * angleDefault+angleIncrement;
        }
        else            //false逆时针转动
        {
            angle = i * angleDefault-angleIncrement;
        }
        QPointF* circle_center=new QPointF(screenWidth/2 - (outerRadius - circleRadius) * sin(angle),screenHeight/2 + (outerRadius - circleRadius) * cos(angle));

        circleCenters[i]->setX(screenWidth/2 - (outerRadius - circleRadius) * sin(angle));
        circleCenters[i]->setY(screenHeight/2 + (outerRadius - circleRadius) * cos(angle));
    }

}

void Round::initPosdatas(QString mn)
{
    for(int i=0;i<player_count;i++)
    {
        Posdatas.append(new positiondata{i,NULL,pre_posed,new QList<skill*>});
    }
    Posdatas[0]->posStatus=unprepared;
    Posdatas[0]->playername=mn;
}

void Round::selectPosition(int serial)
{
    qDebug()<<"当前playernumber："<<player_number<<"选择位置："<<serial<<"当前状态"<<status;
    //判断是否已被占用
    if(Posdatas[serial]->posStatus==0)
    {
        if(status!=0)
        {
            Posdatas[player_number]->posStatus=pre_posed;
        }
        player_number=serial;
        Posdatas[serial]->posStatus=unprepared;
        QSettings name("tlr","name");
        Posdatas[serial]->playername=name.value("name").toString();
        foreach(positiondata* pos,Posdatas)
        {
            qDebug()<<pos->positionnum<<pos->posStatus<<pos->playername;
        }
        emit PositionSelected(serial);
        status=unprepared;
        update();

    }
    else
    {
        return;
    }
}

void Round::update_SD(int playerNum)
{
    qDebug()<<"更新玩家"<<playerNum;
    auto vbox=slayout->widget(playerNum)->layout();
    QString str=(Posdatas[playerNum]->player_skills->constLast()->btn->text())+":"+(Posdatas[playerNum]->player_skills->constLast()->label->text());
    vbox->addWidget(new QLabel(str));

}



void Round::init_Slayout()
{
    skill_display->setLayout(slayout);
    for(int i=0;i<player_count;i++)
    {
        auto vbox=new QVBoxLayout;
        auto sWid=new QWidget;
        sWid->setLayout(vbox);
        slayout->addWidget(sWid);
    }
}

QPixmap* Round::get_Pic(int index,int type)
{
    int num=random_seq[index].toInt();
    if(type==0){

    return &roundHander->heroLib[num]->heroPic;
    }
    else if(type==1)
    {
         return &roundHander->heroLib[num]->heroCard;
    }
}

QList<skill *>* Round::get_skill(int index)
{
    int num=random_seq[index].toInt();
    return &roundHander->heroLib[num]->skills;
}

void Round::dump_touchBegin(QEvent *ev)
{
    if (QTouchEvent* te = static_cast<QTouchEvent*>(ev))
    {
        QPointF touchPoint = te->points().at(0).position();
        int innerCircleX = width() / 2 ;
        int innerCircleY = height() / 2 ;
        QPointF inner_center(innerCircleX,innerCircleY);
        qreal inner_distance = QLineF(inner_center, touchPoint).length();

        // 检查触摸点是否在内圆的边界框内
        if (inner_distance<innerRadius) {
            // 触摸到了内圆，执行相应的操作
            if(status==pre_posed)
            {

            }
            else if(status==unprepared)
            {
                status=prepared;
                qDebug()<<player_number;
                Posdatas[player_number]->posStatus=prepared;
                update();
                emit status_change(status);

            }
            else if(status==prepared)
            {


            }
            else if(status>=3)
            {

            }
            return;
        }
        if (inner_distance>outerRadius) {

            if(status>=3)
            {
                skill_display->setVisible(false);
            }
        }

        // 八个圆的边界框
        for(int i=0;i<circleCenters.count();i++) {
            qreal circle_distance = QLineF(circleCenters[i]->toPoint(), touchPoint).length();
            if (circle_distance<circleRadius) {
                // 触摸到了八个圆中的一个，执行相应的操作
                if(status<=unprepared)
                {
                    selectPosition(i);
                }
                else if(status>=wait_for_choose)
                {
                    skill_display->setVisible(true);

                    slayout->setCurrentIndex(i);
                }
            }

        }
    }
}

void Round::dump_touchEnd(QEvent *ev)
{
    if (QTouchEvent* te = static_cast<QTouchEvent*>(ev))
    {
        QPointF pressPoint = te->points().at(0).pressPosition();
        QPointF endPoint=te->points().at(0).lastPosition();
        int innerCircleX = width() / 2 ;
        int innerCircleY = height() / 2 ;
        QPointF inner_center(innerCircleX,innerCircleY);
        qreal innerPress_distance_ = QLineF(inner_center, pressPoint).length();
        qreal delta = pressPoint.x()-endPoint.x();
        qreal DELTA=qAbs(delta);
        if (innerPress_distance_<innerRadius&&DELTA>innerRadius/6)
        {
            if(status>=wait_for_choose)
            {
                if(delta>0)heronum=(heronum+1)%random_seq.count();
                else heronum=(heronum-1)<0?(heronum-1+random_seq.count()):heronum-1;
                qDebug()<<"heronum"<<heronum;
                update();
            }
        }
        else if(innerPress_distance_<innerRadius&&DELTA<innerRadius/6) {
            if(status>=wait_for_choose)
            {

                display->setVisible(true);

            }
        }







    }

}

bool Round::isAllstatus(int status)
{
    foreach (positiondata* user, Posdatas) {
        if(user->posStatus!=status)return false;
    }
    return true;
}


void Round::on_timeout()
{
    s+=1;
    if(s>=30)
    {
        s=0;
        emit Round::timeout();
    }
    double angle = 2 * 3.14159265 /(30*player_count);

    angleIncrement+=angle;
    turn_circleCenter(direction);
    update();

}
