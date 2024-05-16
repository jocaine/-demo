#include "gameSetting.h"
#include<QGroupBox>
#include "ui_gameSetting.h"
#include<QCheckBox>
#include<QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QFile>
gameSetting::gameSetting(int b_s,QString appName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameSetting)
{

    qDebug()<<appName;
    ui->setupUi(this);
    comboBoxes.append(ui->Box_1);
    comboBoxes.append(ui->Box_2);
    comboBoxes.append(ui->Box_3);
    comboBoxes.append(ui->Box_4);
    comboBoxes.append(ui->Box_5);
    comboBoxes.append(ui->Box_6);
    comboBoxes.append(ui->Box_7);
    comboBoxes.append(ui->Box_8);
    comboBoxes.append(ui->Box_9);
    comboBoxes.append(ui->Box_10);
    QFile* g_file=new QFile("://qss/g_s.css"); // 替换为您的CSS文件路径

    if (g_file->open(QIODevice::ReadOnly)) {
        setStyleSheet(g_file->readAll());
        g_file->close();
    } else {
        qWarning() << "Failed to load CSS file";
    }

    ui->advanced_content->setVisible(false);
    btn_status(b_s);
    ui->advanced_content->setMaximumWidth(this->width()/1.5);
    ui->base_setting->setMaximumWidth(this->width()/1.5);
    set=new QSettings("tlr",appName);
    if(appName=="default_set")
    {

        set->setValue("base/游戏模式",0);
        set->setValue("base/英雄范围",0);
        set->setValue("base/武将数目",0);
        set->setValue("time/准备时长",0);
        set->setValue("time/选择时长",0);
        set->setValue("game/基础血量点数",0);
        set->setValue("game/主公额外点数",0);
        set->setValue("game/技能可复选",0);
        set->setValue("turn/方向",0);
        set->setValue("turn/主公优先级",0);
    }
    ui->Box_1->setCurrentIndex(set->value("base/游戏模式").toInt());
    ui->Box_2->setCurrentIndex(set->value("base/英雄范围").toInt());
    ui->Box_3->setCurrentIndex(set->value("base/武将数目").toInt());
    ui->Box_4->setCurrentIndex(set->value("time/准备时长").toInt());
    ui->Box_5->setCurrentIndex(set->value("time/选择时长").toInt());
    ui->Box_6->setCurrentIndex(set->value("game/基础血量点数").toInt());
    ui->Box_7->setCurrentIndex(set->value("game/主公额外点数").toInt());
    ui->Box_8->setCurrentIndex(set->value("game/技能可复选").toInt());
    ui->Box_9->setCurrentIndex(set->value("turn/方向").toInt());
    ui->Box_10->setCurrentIndex(set->value("turn/主公优先级").toInt());




    connect(ui->advanced_setting, &QCheckBox::stateChanged, this, [=](int state) {
        if (state == Qt::Checked) {
            ui->advanced_content->setVisible(true);
        } else {
            ui->advanced_content->setVisible(false);
        }
    });

}

gameSetting::gameSetting(QString indexString, QWidget *parent)
    :QWidget(parent),
    ui(new Ui::gameSetting)
{
    ui->setupUi(this);
    comboBoxes.append(ui->Box_1);
    comboBoxes.append(ui->Box_2);
    comboBoxes.append(ui->Box_3);
    comboBoxes.append(ui->Box_4);
    comboBoxes.append(ui->Box_5);
    comboBoxes.append(ui->Box_6);
    comboBoxes.append(ui->Box_7);
    comboBoxes.append(ui->Box_8);
    comboBoxes.append(ui->Box_9);
    comboBoxes.append(ui->Box_10);
    QFile* g_file=new QFile("://qss/g_s.css"); // 替换为您的CSS文件路径

    if (g_file->open(QIODevice::ReadOnly)) {
        setStyleSheet(g_file->readAll());
        g_file->close();
    } else {
        qWarning() << "Failed to load CSS file";
    }
    ui->advanced_setting->setChecked(true);
    ui->advanced_content->setVisible(true);
    ui->save_widget->setVisible(0);
    ui->ok_widget->setVisible(0);
    ui->base_setting->setDisabled(true);
    ui->advanced_setting->setDisabled(true);
    ui->advanced_content->setDisabled(true);

    for (int i = 0; i < 9; ++i) {
        int index = indexString.mid(i, 1).toInt();
        comboBoxes[i]->setCurrentIndex(index);
    }

}



gameSetting::~gameSetting()
{
    delete ui;
}

void gameSetting::btn_status(int b)
{
    if(b==0)
    {
        ui->save_widget->setVisible(1);
        ui->ok_widget->setVisible(0);
    }
    else if(b==1)
    {
        ui->save_widget->setVisible(false);
        ui->ok_widget->setVisible(true);
    }
    //else
    //{

    //    ui->advanced_setting->setChecked(true);
    //    ui->advanced_content->setVisible(true);
    //    ui->save_widget->setVisible(0);
    //    ui->ok_widget->setVisible(0);
    //    ui->base_setting->setDisabled(true);
    //    ui->advanced_setting->setDisabled(true);
    //    ui->advanced_content->setDisabled(true);
    //}
}



void gameSetting::on_save_clicked()
{
    set->setValue("base/游戏模式",ui->Box_1->currentIndex());
    set->setValue("base/英雄范围",ui->Box_2->currentIndex());
    set->setValue("base/武将数目",ui->Box_3->currentIndex());
    set->setValue("time/准备时长",ui->Box_4->currentIndex());
    set->setValue("time/选择时长",ui->Box_5->currentIndex());
    set->setValue("game/基础血量点数",ui->Box_6->currentIndex());
    set->setValue("game/主公额外点数",ui->Box_7->currentIndex());
    set->setValue("game/技能可复选",ui->Box_8->currentIndex());
    set->setValue("turn/方向",ui->Box_9->currentIndex());
    set->setValue("turn/主公优先级",ui->Box_10->currentIndex());
    emit close_to();
}


void gameSetting::on_save_as_clicked()
{
    auto dia=new QDialog(this);
    auto le=new QLineEdit();
    auto v=new QVBoxLayout(dia);
    auto button=new QPushButton("另存为");
    auto newsetting=new QSettings("tlr",le->text());
    newsetting->setValue("base/游戏模式",ui->Box_1->currentIndex());
    newsetting->setValue("base/英雄范围",ui->Box_2->currentIndex());
    newsetting->setValue("base/武将数目",ui->Box_3->currentIndex());
    newsetting->setValue("time/准备时长",ui->Box_4->currentIndex());
    newsetting->setValue("time/选择时长",ui->Box_5->currentIndex());
    newsetting->setValue("game/基础血量点数",ui->Box_6->currentIndex());
    newsetting->setValue("game/主公额外点数",ui->Box_7->currentIndex());
    newsetting->setValue("game/技能可复选",ui->Box_8->currentIndex());
    newsetting->setValue("turn/方向",ui->Box_9->currentIndex());
    newsetting->setValue("turn/主公优先级",ui->Box_10->currentIndex());
    v->addWidget(le);
    v->addWidget(button);
    dia->setLayout(v);
    dia->show();
    connect(button,&QPushButton::clicked,this,[=]
    {
        emit appName(le->text());
        dia->close();
    });


}


void gameSetting::on_ok_btn_clicked()
{

    emit ok();
}

void gameSetting::reset_index(QString indexString)
{

    qDebug()<<indexString<<"receive";
    for (int i = 0; i < 10; ++i) {
        int index = indexString.mid(i, 1).toInt();
        comboBoxes[i]->setCurrentIndex(index);
    }
}

