#include "classmanager.h"
#include "ui_classmanager.h"
#include "addclassdialog.h"
#include <QLabel>
#include <QDebug>

ClassManager::ClassManager(QList<ClassItem> *classes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClassManager)
{
    ui->setupUi(this);
    m_classes = classes;
    for (int i = 0; i < m_classes->count(); i++) {
        ui->listWidget->addItem(m_classes->at(i).m_className);
    }

}

ClassManager::~ClassManager()
{
    delete ui;
}

void ClassManager::on_addButton_clicked()
{
    AddClassDialog *addClassDialog = new AddClassDialog(this);
    if (addClassDialog->exec() == QDialog::Accepted) {
        QString className = addClassDialog->m_className;
        QString teacherName = addClassDialog->m_teacherName;
        QString classRoom = addClassDialog->m_classRoom;
        int classDay = addClassDialog->m_classDay;
        int classTime = addClassDialog->m_classTime;
        int startWeek = addClassDialog->m_startWeek;
        int endWeek = addClassDialog->m_endWeek;
        //qDebug() << classDay << ' ' << classTime << ' ' << startWeek << ' ' << endWeek << endl;
        ClassItem classItem(className, teacherName, classRoom, classDay, classTime, startWeek, endWeek);
        m_classes->append(classItem);
        ui->listWidget->addItem(className);
    }
}

void ClassManager::on_editButton_clicked()
{
    int index = ui->listWidget->currentRow();
    if(index < 0) return;
    QString oldClassName = ui->listWidget->currentItem()->text();
    int v_index = 0;
    for (int i = 0; i < m_classes->count(); i++) {
        if (oldClassName == m_classes->at(i).m_className) { v_index = i; break; }
    }
    AddClassDialog* addClassDialog = new AddClassDialog(this, m_classes->at(v_index).m_className, m_classes->at(v_index).m_teacherName, m_classes->at(v_index).m_classRoom, m_classes->at(v_index).m_startWeek, m_classes->at(v_index).m_endWeek, m_classes->at(v_index).m_classDay, m_classes->at(v_index).m_classTime);
    if (addClassDialog->exec() == QDialog::Accepted) {
        QString className = addClassDialog->m_className;
        QString teacherName = addClassDialog->m_teacherName;
        QString classRoom = addClassDialog->m_classRoom;
        int classDay = addClassDialog->m_classDay;
        int classTime = addClassDialog->m_classTime;
        int startWeek = addClassDialog->m_startWeek;
        int endWeek = addClassDialog->m_endWeek;
        ClassItem classItem(className, teacherName, classRoom, classDay, classTime, startWeek, endWeek);
        m_classes->append(classItem);
        m_classes->removeAt(v_index);
        QListWidgetItem *curItem = ui->listWidget->currentItem();
        ui->listWidget->removeItemWidget(curItem);
        ui->listWidget->addItem(className);
        delete curItem;
    }
}

void ClassManager::on_deleteButton_clicked()
{
    int index = ui->listWidget->currentRow();
    if(index < 0) return;
    QString className = ui->listWidget->currentItem()->text();
    for (int i = 0; i < m_classes->count(); i++) {
        if (className == m_classes->at(i).m_className) { m_classes->removeAt(i); break; }
    }
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    ui->listWidget->removeItemWidget(curItem);
    delete curItem;
}
