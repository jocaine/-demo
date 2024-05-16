#include"archive.h"
#include <QFile>
#include<QStackedLayout>
archiev_list::archiev_list(int b_s)
{



    auto g_s_Model=new QStandardItemModel(qApp);
    auto slayout=new QStackedLayout(this);
    auto list=new QListView;
    auto* delegate=new MyItemDelegate();
    list->setItemDelegate(delegate);
    auto default_set=new QStandardItem;
    slayout->addWidget(list);
    list->setModel(g_s_Model);
    default_set->setData("默认游戏设置",Qt::ItemDataRole::DisplayRole);
    g_s_Model->appendRow(default_set);
    for(int i=0;i<SettingsManager::instance().setting_list.childKeys().count();i++)
    {
        auto newset=new QStandardItem;
        newset->setData(SettingsManager::instance().load(i),Qt::ItemDataRole::DisplayRole);
        g_s_Model->appendRow(newset);

    }
    QFile* l_file=new QFile("://qss/arch.css"); // 替换为您的CSS文件路径

    if (l_file->open(QIODevice::ReadOnly)) {
        list->setStyleSheet(l_file->readAll());
        l_file->close();
    } else {
        qWarning() << "Failed to load CSS file";
    }

    connect(list,&QListView::clicked,list,[=](const QModelIndex &index)
            {
                qDebug()<<index.row();

                if(index.row()==0)
                    g_s=new gameSetting(b_s);
                else
                    g_s=new gameSetting(b_s,SettingsManager::instance().load(index.row()-1));//3
                slayout->addWidget(g_s);
                slayout->setCurrentIndex(1);
                connect(g_s,&gameSetting::ok,list,[=]()
                        {
                            emit l_ok();
                        });
                connect(g_s,&gameSetting::close_to,list,[=]()
                        {
                            slayout->setCurrentIndex(0);
                            g_s->deleteLater();

                        });
                connect(g_s,&gameSetting::appName,list,[=](QString name)
                        {
                            SettingsManager::instance().append_newSetting(name);
                            qDebug()<<name;
                            auto item=new QStandardItem;
                            item->setData(name,Qt::ItemDataRole::DisplayRole);
                            g_s_Model->appendRow(item);
                            slayout->setCurrentIndex(1);
                            g_s->deleteLater();
                        });

            });
}

