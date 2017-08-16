#include "classitem.h"

ClassItem::ClassItem(const QString& className, const QString& teacherName, const QString &classRoom, int classDay, int classTime, int startWeek, int endWeek, QColor color) {
    m_className = className;
    m_teacherName = teacherName;
    m_classRoom = classRoom;
    m_classDay = classDay;
    m_classTime = classTime;
    m_startWeek = startWeek;
    m_endWeek = endWeek;
    m_color = color;
}

bool ClassItem::isValid(int week, int row, int column) const {
    if (week >= m_startWeek && week <= m_endWeek) {
        if (m_classDay == column && m_classTime == row) {
            return true;
        }
    }
    return false;
}
