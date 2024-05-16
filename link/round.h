#ifndef ROUND_H
#define ROUND_H
#include"message.h"
#include <QWidget>
#include<QPainter>
#include<QPaintEvent>
#include<QScreen>
#include <QGuiApplication>
#include <QMouseEvent>
#include<QTimer>
#include<QImage>
#include<QBrush>
#include <QLabel>
#include"herohander.h"
#include"scroll.h"
struct positiondata
{
    int positionnum;
    QString playername;
    player_status posStatus;
    QList<skill*>* player_skills;

};
class Round:public QWidget
{
    Q_OBJECT
public:
    Round(QString,int num,QString masterName,QWidget* parent=nullptr);
public slots:
    void on_timeout();
public:
    void explianer(QString,int);
    int speaker();
signals:
    void imKing();
    void notKing();
    void timeout();
    void PositionSelected(int);
    void status_change(player_status);
    void skillSelected(int index);
protected:
    bool event(QEvent* ev)override;
    void mousePressEvent(QMouseEvent *event)override;
    void paintEvent(QPaintEvent *event) override;
private:  //explainer

    int player_count;
    bool myturn;
    int heroRange_num;
    int hero_num;
    int prepareTime_num;
    int selectTime_num;
    int baseCount_num;
    int extraCount_num;
    int skillCheckable_num;
    int direction_num;

private: //painter

    bool direction;
    int outerRadius;
    int innerRadius;
    int circleRadius;
    QTimer* turnwheel;
    QPixmap* pix;
    double angleIncrement=0;
    QList<QPointF*> circleCenters;
    int s=0;
    int heronum=0;
public:
    QList<positiondata*> Posdatas;
    player_status status=pre_posed;

public:
    QStringList random_seq;
    bool isAllstatus(int status);
    void update_SD(int playerNum);
    int player_number;
    class scroll* display;
    QWidget* skill_display;
    QStackedLayout* slayout;
    QPixmap* get_Pic(int,int);
    QList<skill*>* get_skill(int);

private:
    void init_circleCenter();
    void turn_circleCenter(bool);
    void initPosdatas(QString);
    void selectPosition(int serial);

    void init_Slayout();
    heroHander* roundHander;


private:
    void dump_touchBegin(QEvent* ev);
    void dump_touchUpdate(QEvent* ev);
    void dump_touchEnd(QEvent* ev);
};

#endif // ROUND_H
