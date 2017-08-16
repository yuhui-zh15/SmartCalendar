#ifndef CALENDAR_H
#define CALENDAR_H

#include <QCalendarWidget>
#include <QPainter>
#include <qcolor>
#include <qdate>
#include <qpen>
#include <qbrush>
#include <QVector>
#include <QTableView>
#include <QMap>
#include "thing.h"
#include "file.h"
#include "usermanager.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class Calendar: public QCalendarWidget
{
    Q_OBJECT
public:
    friend class UserManager;
    Calendar(const QString& username);
    virtual ~Calendar();

protected:
    virtual void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

public slots:
    void addNote(const QDate &);
//    void setBackgroundColor(const QDate &, const QColor &);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

signals:
//    void backgroundColorChanged(const QDate &, const QColor &) const;

private:
    QString m_userName;
    QDate m_currentDate;
    QPen m_outlinePen;
    QBrush m_transparentBrush;

    QVector<QDate> m_dates;
    QVector<QColor> m_colors;
    QList<File> m_files;
    QList<Thing> m_things;

    QTableView* c_tableView;
    bool m_acceptDrops;
};

#endif // CALENDAR_H
