#ifndef USERMANAGER_H
#define USERMANAGER_H
#include "calendar.h"
#include <QFile>
#include <QTextStream>
#include <QString>

class Calendar;
class UserManager
{
public:
    UserManager(const QString &userName, Calendar *calendar) { m_userName = userName; m_calendar = calendar; }
    ~UserManager() { }
    void readUserData();
    void saveUserData();
private:
    QString m_userName;
    Calendar* m_calendar;
};

#endif // USERMANAGER_H
