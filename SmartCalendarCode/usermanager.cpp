#include "usermanager.h"
#include <QDebug>

void UserManager::readUserData() {
    QString thingsName = m_userName + QString("_things.ini");
    QString filesName = m_userName + QString("_files.ini");
    QString colorsName = m_userName + QString("_colors.ini");

    QFile thingsFile(thingsName);
    if(!thingsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Open failed." << endl;
    }
    QTextStream thingsStream(&thingsFile);
    while (1) {
        QString line = thingsStream.readLine();
        if (line.length() == 0) break;
        QList<QString> splitline = line.split('$');
        QList<QString> splitdate = splitline.at(0).split('|');
        QDate date(splitdate.at(0).toInt(), splitdate.at(1).toInt(), splitdate.at(2).toInt());
        int repeatMode = splitline.at(1).toInt();
        int repeatPeriod = splitline.at(2).toInt();
        QString todoThing = splitline.at(3);
        m_calendar->m_things.append(Thing(date, todoThing, repeatMode, repeatPeriod));
    }
    thingsFile.close();

    QFile filesFile(filesName);
    if(!filesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Open failed." << endl;
    }
    QTextStream filesStream(&filesFile);
    while (1) {
        QString line = filesStream.readLine();
        if (line.length() == 0) break;
        QList<QString> splitline = line.split('$');
        QList<QString> splitdate = splitline.at(0).split('|');
        QDate date(splitdate.at(0).toInt(), splitdate.at(1).toInt(), splitdate.at(2).toInt());
        QString filename = splitline.at(1);
        m_calendar->m_files.append(File(filename, date));
    }
    filesFile.close();

    QFile colorsFile(colorsName);
    if(!colorsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Open failed." << endl;
    }
    QTextStream colorsStream(&colorsFile);
    while (1) {
        QString line = colorsStream.readLine();
        if (line.length() == 0) break;
        QList<QString> splitline = line.split('$');
        QList<QString> splitdate = splitline.at(0).split('|');
        QList<QString> splitrgb = splitline.at(1).split('|');
        QDate date(splitdate.at(0).toInt(), splitdate.at(1).toInt(), splitdate.at(2).toInt());
        QColor color(splitrgb.at(0).toInt(), splitrgb.at(1).toInt(), splitrgb.at(2).toInt(), splitrgb.at(3).toInt());
        m_calendar->m_dates.append(date);
        m_calendar->m_colors.append(color);
    }
    colorsFile.close();
}

void UserManager::saveUserData() {
    QString thingsName = m_userName + QString("_things.ini");
    QString filesName = m_userName + QString("_files.ini");
    QString colorsName = m_userName + QString("_colors.ini");

    QFile colorsFile(colorsName);
    if(!colorsFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open failed." << endl;
    }
    QTextStream colorsStream(&colorsFile);
    for (int i = 0; i < m_calendar->m_dates.count(); i++) {
        colorsStream << m_calendar->m_dates.at(i).year() << '|' << m_calendar->m_dates.at(i).month() << '|' << m_calendar->m_dates.at(i).day() << '$';
        colorsStream << m_calendar->m_colors.at(i).red() << '|' << m_calendar->m_colors.at(i).green() << '|' << m_calendar->m_colors.at(i).blue() << '|' << m_calendar->m_colors.at(i).alpha() << endl;
    }
    colorsFile.close();

    QFile thingsFile(thingsName);
    if(!thingsFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open failed." << endl;
    }
    QTextStream thingsStream(&thingsFile);
    for (int i = 0; i < m_calendar->m_things.count(); i++) {
        thingsStream << m_calendar->m_things.at(i).getStartDate().year() << '|' << m_calendar->m_things.at(i).getStartDate().month() << '|' << m_calendar->m_things.at(i).getStartDate().day() << '$';
        thingsStream << m_calendar->m_things.at(i).getRepeatMode() << '$' << m_calendar->m_things.at(i).getRepeatPeriod() << '$';
        thingsStream << m_calendar->m_things.at(i).getTodoThing() << endl;
    }
    thingsFile.close();

    QFile filesFile(filesName);
    if(!filesFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open failed." << endl;
    }
    QTextStream filesStream(&filesFile);
    for (int i = 0; i < m_calendar->m_files.count(); i++) {
        filesStream << m_calendar->m_files.at(i).getDate().year() << '|' << m_calendar->m_files.at(i).getDate().month() << '|' << m_calendar->m_files.at(i).getDate().day() << '$';
        filesStream << m_calendar->m_files.at(i).getFileName() << endl;
    }
    filesFile.close();

    QFile languageFile(QString("language.ini"));
    if(!languageFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open failed." << endl;
    }
    QTextStream ts(&languageFile);
    ts << (m_calendar->locale().language() == QLocale::Chinese);
    languageFile.close();
}
