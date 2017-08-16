#ifndef CLASSITEM_H
#define CLASSITEM_H

#include <QString>
#include <QVector>
#include <QColor>
#include "classmanager.h"
#include "classtable.h"

class ClassItem
{
public:
    ClassItem(const QString& className, const QString& teacherName, const QString& classRoom, int classDay, int classTime, int startWeek, int endWeek, QColor color = Qt::black);
private:
    friend class ClassManager;
    friend class ClassTable;
    QString m_className;
    QString m_teacherName;
    QString m_classRoom;
    int m_classDay;
    int m_classTime;
    int m_startWeek;
    int m_endWeek;
    QColor m_color;
public:
    bool isValid(int week, int row, int column) const;

};

#endif // CLASSITEM_H
