#ifndef QUERYDIALOG_H
#define QUERYDIALOG_H

#include <QDialog>
#include <QString>
#include <QColor>
#include "thing.h"
#include "file.h"

namespace Ui {
class QueryDialog;
}

class QueryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QueryDialog(const QDate& today, QColor *pickedColor, QList<Thing> *things, QList<File>* files, QWidget *parent = 0);
    ~QueryDialog();

private slots:
    void on_m_addButton_clicked();
    void on_m_pickColorButton_clicked();
    void on_m_deleteButton_clicked();
    void on_m_deleteAllButton_clicked();
    void on_fileDragedOut(QString fileName);
    void on_m_exceptButton_clicked();
    void on_m_editButton_clicked();

private:
    Ui::QueryDialog *ui;
    QColor *m_pickedColor;
    QList<Thing> *m_things;
    QList<File> *m_files;
    QDate m_today;
};

#endif // QUERYDIALOG_H
