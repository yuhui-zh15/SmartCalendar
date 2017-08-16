#include "thing.h"

Thing::Thing(const QDate &startDate, const QString &todoThing, int repeatMode, int repeatPeriod) {
    m_startDate = startDate;
    m_todoThing = todoThing;
    m_repeatMode = repeatMode;
    m_repeatPeriod = repeatPeriod;
}

bool Thing::isValidToday(const QDate& today) const {
    if(today < m_startDate || m_exception.contains(today)) return false;
    switch(m_repeatMode) {
    case 0: if (today == m_startDate) return true; else return false;
    case 1: return true;
    case 2: if (today.daysTo(m_startDate) % 7 == 0) return true; else return false;
    case 3: if (today.day() == m_startDate.day()) return true; else return false;
    case 4: if (today.day() == m_startDate.day() && today.month() == m_startDate.month()) return true; else return false;
    case 5: if (today.daysTo(m_startDate) % m_repeatPeriod == 0) return true; else return false;
    }
}
