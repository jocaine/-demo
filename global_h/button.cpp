#include"button.h"

#include <QApplication>
#include <QEvent>

button::button(QString str,QWidget *parent)
    :QPushButton(str,parent)
{
      setAttribute(Qt::WA_AcceptTouchEvents);
}

bool button::event(QEvent *ev)
{
        QEvent::Type type=ev->type();
        switch(type)
        {
        case QEvent::TouchBegin:
        {
            ev->accept();
            return true;

        }
        case QEvent::TouchUpdate:
        {

        }
        case QEvent::TouchEnd:
        {
            qDebug()<<"按钮end";

            if (QTouchEvent* te = static_cast<QTouchEvent*>(ev)) {
                auto point = te->points().at(0);

                QScreen *primaryScreen = QApplication::primaryScreen();
                QRect screenSize = primaryScreen->geometry();
                qreal screenheight = screenSize.height();
                qreal deltaY = point.lastPosition().y() - point.pressPosition().y();

                QMouseEvent pressEvent(QEvent::MouseButtonPress,
                point.position(),  // localPos
                point.globalPressPosition(),  // globalPos
                Qt::LeftButton,  // button
                Qt::LeftButton,  // buttons
                Qt::NoModifier); // modifiers
                QMouseEvent releaseEvent(QEvent::MouseButtonRelease,
                point.position(),  // localPos
                point.globalPressPosition(),  // globalPos
                Qt::LeftButton,  // button
                Qt::LeftButton,  // buttons
                Qt::NoModifier); // modifiers
                //if(abs(deltaY)<screenheight/8)
                //{// 发送鼠标事件
                QApplication::sendEvent(this, &pressEvent);
                // 发送鼠标事件
                QApplication::sendEvent(this, &releaseEvent);
                //}
            }
            return true;
        }
        default:
            break;
        }
        return QWidget::event(ev);

}
