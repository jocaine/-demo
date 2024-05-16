#ifndef HEROHANDER_H
#define HEROHANDER_H
#include<QPixmap>
#include<QDebug>
#include <QPushButton>
#include <QLabel>
#include"button.h"
struct skill
{
    skill(QString name,QString descr,int num)
    {
        btn=new button(name);
        point=num;
        label=new QLabel(descr);
        label->setWordWrap(true);
        btn->setFixedSize(QSize(80,45));
    }
    int point;
    button* btn;
    QLabel* label;
};
struct heroData
{
    QPixmap heroPic;
    QPixmap heroCard;
    QList<skill*> skills{};

};
class heroHander
{
public:
    heroHander();
public:
   QList<heroData*> heroLib;
private:

};
#endif // HEROHANDER_H
