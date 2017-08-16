#ifndef CLASSMANAGER_H
#define CLASSMANAGER_H

#include <QDialog>
#include <QList>
#include "classitem.h"

namespace Ui {
class ClassManager;
}
class ClassItem;

class ClassManager : public QDialog
{
    Q_OBJECT

public:
    explicit ClassManager(QList<ClassItem> *classes, QWidget *parent = 0);
    ~ClassManager();

private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::ClassManager *ui;
    QList<ClassItem> *m_classes;
};

#endif // CLASSMANAGER_H
