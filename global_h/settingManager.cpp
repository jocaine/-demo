#include"settingManager.h"
#include<QList>
SettingsManager::SettingsManager()
    : setting_list("tlr", "list")
{}

SettingsManager& SettingsManager::instance()
{
    static SettingsManager instance;
    return instance;
}

QString SettingsManager::load(int index)
{
    return setting_list.value(QString::number(index)).toString();
}

void SettingsManager::append_newSetting(const QString name)
{
     int num=setting_list.childKeys().count();
    qDebug()<<"num:"<<name;
    setting_list.setValue(QString::number(num),name);
}

SettingsManager::~SettingsManager() {}
