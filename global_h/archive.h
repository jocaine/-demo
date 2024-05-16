#ifndef ARCHIVE_H
#define ARCHIVE_H
#include"gameSetting.h"
#include"delegate.h"
class archiev_list:public QWidget
{
Q_OBJECT
public:
    archiev_list(int);
    gameSetting* g_s;
signals:
    void l_ok();
};
#endif // ARCHIVE_H
