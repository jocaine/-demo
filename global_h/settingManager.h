#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H
#include <QSettings>
class SettingsManager

{
public:
    static SettingsManager& instance();

    QString load(int);
    void append_newSetting(const QString);
    QSettings setting_list;

private:
    SettingsManager();
    ~SettingsManager();


};
#endif // SETTINGMANAGER_H
