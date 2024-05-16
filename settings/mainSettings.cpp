#include "mainSettings.h"
#include "ui_mainSettings.h"
#include<QLabel>
#include<QColor>
#include"archive.h"
#include<QStackedLayout>
#include<QVBoxLayout>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
mainSettings::mainSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainSettings)
{
    ui->setupUi(this);
    //1.设置slayout，声明化个人设置和主界面，游戏设置不包含在slayout中。
    auto slayout=new QStackedLayout(this);
    ui->vbox->addLayout(slayout);

    auto list=new QListView(this);  //0
    slayout->addWidget(list);

    auto u_s=new QWidget;           //1
    slayout->addWidget(u_s);

    slayout->setCurrentIndex(0);

    //2.声明游戏设置界面
     auto g_s_Save=new archiev_list(0);
    //3.初始化主设置界面的mvc，并为其添加个人设置项和游戏设置项
    auto model=new QStandardItemModel(qApp);
    auto* delegate=new MyItemDelegate();
    list->setItemDelegate(delegate);
    list->setModel(model);

    auto user=new QStandardItem();
    auto game=new QStandardItem();

    user->setData(QPixmap("://res/user.png").scaled(48,48),Qt::ItemDataRole::DecorationRole);
    game->setData(QPixmap("://res/game.png").scaled(48,48),Qt::ItemDataRole::DecorationRole);
    user->setData("个人信息",Qt::ItemDataRole::DisplayRole);
    game->setData("游戏设置",Qt::ItemDataRole::DisplayRole);
    model->appendRow(user);
    model->appendRow(game);



    //4.设置"List"的信号逻辑
        connect(list,&QListView::clicked,this,[=](const QModelIndex &index)
        {
            //4.1当第0行被点击时（个人设置）
            if(index.row()==0)
            {
                //1.创建dialog并设置v为主要layout
                auto dia=new QDialog(this);
                auto v=new QVBoxLayout(dia);
                dia->setLayout(v);
                //2.v的第一行：将用户名从setting中取出，放在name的Label中，设置中心对齐
                auto user_name=new QSettings("tlr","name");
                auto name=new QLabel(user_name->value("name").toString());
                name->setAlignment(Qt::AlignCenter);
                //3.v的第二行：供用户输入新用户名的lineEdit输入框
                auto le=new QLineEdit();
                //4.v的第四行：初始化两个button，更改和取消更改，并放入hbox中
                auto h=new QHBoxLayout(dia);
                auto button=new QPushButton("更改用户名");
                auto cancel=new QPushButton("取消");
                h->addWidget(button);
                h->addWidget(cancel);
                //5.将以上控件加入到v中并且显示dialog
                v->addWidget(name);
                v->addWidget(le);
                v->addLayout(h);
                dia->show();


                //6.设置信号逻辑
                    //6.1设置“更改用户名”按钮逻辑
                    connect(button,&QPushButton::clicked,this,[=]
                            {
                                //从lineEidt中取出字符串更改setting中的内容，然后关闭
                                user_name->setValue("name",le->text());
                                dia->close();
                                dia->deleteLater();
                            });
                    //6.2设置“取消”信号逻辑
                    connect(cancel,&QPushButton::clicked,this,[=]
                            {
                                //直接关闭即可
                                dia->close();
                                dia->deleteLater();
                            });
            }
            //4.2点击第二行显示游戏设置界面
            else
            {
                g_s_Save->show();

            }
        });



}

mainSettings::~mainSettings()
{
    delete ui;
}
