#ifndef SCROLL_H
#define SCROLL_H
#include <QMouseEvent>
#include<QWidget>
#include <QStackedLayout>
#include<QButtonGroup>
#include"herohander.h"
class scroll:public QWidget
{
    Q_OBJECT
public:
    scroll(QWidget* parent=nullptr);
public:
    void append_hero(QPixmap*,QList<skill*>*);
    QList<QWidget*> wids;
    QButtonGroup* btns;
signals:
    void hide();
    void button_index(int);
protected:
    bool event(QEvent* ev)override;
    void mousePressEvent(QMouseEvent* ev)override
    {
        qDebug()<<"鼠标点击";
        qDebug()<<ev->pos();
        QWidget::mousePressEvent(ev);
    }
private:
    int index;
    int num=0;
    QStackedLayout* slayout;
    bool dumpTouch_updateEvent(QEvent* ev);
    bool dumpTouch_endEvent(QEvent* ev);
};
#endif // SCROLL_H
