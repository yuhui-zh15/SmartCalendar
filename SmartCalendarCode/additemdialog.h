#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class AddItemDialog;
}

class AddItemDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddItemDialog(QWidget *parent = 0, QString todoThing = "", int m_repeatMode = 0);
    ~AddItemDialog();
    QString getTodoThing() { return m_todoThing; }
    int getRepeatMode() { return m_repeatMode; }
    int getRepeatPeriod() { return m_repeatPeriod; }

private slots:
    void on_m_isRepeatCheckBox_clicked();
    void on_buttonBox_accepted();
    void on_m_repeatComboBox_activated(int index);

private:
    Ui::AddItemDialog *ui;
    QString m_todoThing;
    int m_repeatMode;
    int m_repeatPeriod;
};

#endif // ADDITEMDIALOG_H
