#ifndef GAMEROUND_H
#define GAMEROUND_H

#include <QWidget>
#include"message.h"
namespace Ui {
class gameRound;
}

class gameRound : public QWidget
{
    Q_OBJECT

public:
    gameRound(QString,int num,int myNumber,QWidget* parent=nullptr);
    ~gameRound();
public:
    void explianer(QString,int);
    int speaker();
signals:
    void imKing();
    void notKing();
private:
    int player_number;
    bool myturn;
    int heroRange_num;
    int hero_num;
    int prepareTime_num;
    int selectTime_num;
    int baseCount_num;
    int extraCount_num;
    int skillCheckable_num;
    int direction_num;
private:
    Ui::gameRound *ui;
};

#endif // GAMEROUND_H
