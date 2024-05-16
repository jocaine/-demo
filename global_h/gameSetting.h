#ifndef GAMESETTING_H
#define GAMESETTING_H

#include <QWidget>
#include"settingManager.h"
#include<QComboBox>
namespace Ui {
class gameSetting;
}

class gameSetting : public QWidget
{
    Q_OBJECT

public:
    //构造函数的重载一：在游戏设置界面中启用该界面时使用的构造函数
    //b_s:调用“btn_status(int);”函数——控制按钮组的显示
        //b_s==0显示保存和另存为按钮组
        //b_s==1显示确认按钮组
    //appName:据此来加载保存好的游戏设置，默认为default_set；
    explicit gameSetting(int b_s,QString appName="default_set",QWidget *parent = nullptr);
    //构造函数的重载二：在加入游戏界面启用该界面时使用的构造函数
    //QString:作为客户端的主机会收到规则码，根据规则码调整combox的显示——在功能上作为客户端了解本局规则的展示
    explicit gameSetting(QString,QWidget* parent=nullptr);
    ~gameSetting();
public:
    void btn_status(int);
    void reset_index(QString);
public:
    QSettings* set;
    QList<QComboBox*> comboBoxes;
signals:
    void appName(QString);
    void close_to();
    void ok();
private slots:
    void on_save_clicked();

    void on_save_as_clicked();

    void on_ok_btn_clicked();

private:
    Ui::gameSetting *ui;
private:

};

#endif // GAMESETTING_H
