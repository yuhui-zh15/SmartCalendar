#ifndef CLASSTABLE_H
#define CLASSTABLE_H

#include <QWidget>
#include <QList>
#include <QString>
#include "classlabel.h"
#include "classitem.h"

namespace Ui {
class ClassTable;
}

class ClassItem;

class ClassTable : public QWidget
{
    Q_OBJECT

public:
    explicit ClassTable(QWidget *parent = 0, QString semester = "", int endWeek = 0);
    ~ClassTable();
    void refreshTable();

private slots:
    void on_manageButton_clicked();

    void on_prevWeekButton_clicked();

    void on_nextWeekButton_clicked();

private:
    Ui::ClassTable *ui;
    QList<ClassItem> m_classes;
    int m_currentWeek;
    QString m_semester;
    int m_endWeek;
};

#endif // CLASSTABLE_H
