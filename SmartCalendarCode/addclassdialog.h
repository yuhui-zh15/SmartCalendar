#ifndef ADDCLASSDIALOG_H
#define ADDCLASSDIALOG_H

#include <QDialog>
#include "classmanager.h"

namespace Ui {
class AddClassDialog;
}

class AddClassDialog : public QDialog
{
    Q_OBJECT

public:
    friend class ClassManager;
    explicit AddClassDialog(QWidget *parent = 0, QString className = "", QString teacherName = "", QString classRoom = "", int startWeek = 1, int endWeek = 1, int classDay = 1, int classTime = 1);
    ~AddClassDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddClassDialog *ui;
    QString m_className;
    QString m_teacherName;
    QString m_classRoom;
    int m_startWeek;
    int m_endWeek;
    int m_classDay;
    int m_classTime;
};

#endif // ADDCLASSDIALOG_H
