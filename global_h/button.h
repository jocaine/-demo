#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QTouchEvent>
class button:public QPushButton
{
public:
    button(QString str=nullptr,QWidget* parent=nullptr);
public:
    void touchUpdateEvent(QTouchEvent *event);
protected:
    bool event(QEvent *ev)override;
private:
    bool dumpTouch_updateEvent(QEvent *ev);
    bool dumpTouch_endEvent(QEvent *ev);
};
#endif // BUTTON_H
