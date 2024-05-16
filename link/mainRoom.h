#ifndef MAINROOM_H
#define MAINROOM_H

#include <QWidget>

namespace Ui {
class mainRoom;
}

class mainRoom : public QWidget
{
    Q_OBJECT

public:
    explicit mainRoom(QWidget *parent = nullptr);
    ~mainRoom();

private slots:
    void on_createRoom_clicked();

    void on_joinRoom_clicked();

private:
    Ui::mainRoom *ui;
};

#endif // MAINROOM_H
