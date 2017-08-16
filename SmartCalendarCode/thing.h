#ifndef THING_H
#define THING_H

#include <QString>
#include <QDate>

class Thing
{
public:
    Thing() { }
    Thing(const QDate &startDate, const QString &todoThing, int repeatMode, int repeatPeriod);
    ~Thing() { }
    QDate getStartDate() const { return m_startDate; }
    QDate getEndDate() const { return m_endDate; }
    QString getTodoThing() const { return m_todoThing; }
    int getRepeatMode() const { return m_repeatMode; }
    int getRepeatPeriod() const { return m_repeatPeriod; }
    bool isValidToday(const QDate& today) const;
    void addException(const QDate& today) { m_exception.append(today); }

private:
    int m_repeatPeriod;
    int m_repeatMode; // 0 for not repeat
    QDate m_startDate;
    QDate m_endDate;
    QString m_todoThing;
    QList<QDate> m_exception;
};

#endif // THING_H
