#include "querydialog.h"
#include "ui_querydialog.h"
#include "additemdialog.h"
#include <QColor>
#include <QColorDialog>
#include <QPalette>
#include <QDebug>

QueryDialog::QueryDialog(const QDate& today, QColor *pickedColor, QList<Thing> *things, QList<File>* files, QWidget *parent): QDialog(parent), ui(new Ui::QueryDialog)
{
    ui->setupUi(this);
    setFixedSize(400, 469);
    m_today = today;
    m_pickedColor = pickedColor;
    m_files = files;
    m_things = things;

    for (int i = 0; i < m_things->count(); i++) {
        if (m_things->at(i).isValidToday(m_today)) {
            ui->m_listWidget->addItem(m_things->at(i).getTodoThing());
        }
    }
    for (int i = 0; i < m_files->count(); i++) {
        if (m_files->at(i).getDate() == m_today) {
            ui->m_fileListWidget->addItem(m_files->at(i).getFileName());
        }
    }
    this->setWindowTitle(tr("Manage: ") + today.toString());
    connect(ui->m_fileListWidget, SIGNAL(fileDragedOut(QString)), this, SLOT(on_fileDragedOut(QString)));
}

QueryDialog::~QueryDialog() {
    delete ui;
}

void QueryDialog::on_m_addButton_clicked()
{
    AddItemDialog* additemdialog = new AddItemDialog(this);
    QString todoThing;
    int repeatMode;
    int repeatPeriod;
    if (additemdialog->exec() == QDialog::Accepted) {
        todoThing = additemdialog->getTodoThing();
        repeatMode = additemdialog->getRepeatMode();
        repeatPeriod = additemdialog->getRepeatPeriod();
    }
    if (todoThing.length() == 0) return;
    m_things->append(Thing(m_today, todoThing, repeatMode, repeatPeriod));
    ui->m_listWidget->addItem(todoThing);
}

void QueryDialog::on_m_pickColorButton_clicked()
{
    QColor pickedColor = QColorDialog::getColor(Qt::red);
    m_pickedColor->setRgb(pickedColor.red(), pickedColor.green(), pickedColor.blue());
    QString css = QString("background-color: rgb(") + QString::number(pickedColor.red()) + QString(",") + QString::number(pickedColor.green()) + QString(",") + QString::number(pickedColor.blue()) + QString(");");
    ui->m_colorLabel->setStyleSheet(css);
}

void QueryDialog::on_m_deleteButton_clicked()
{
    int index = ui->m_listWidget->currentRow();
    if(index < 0) return;
    QString todoThing = ui->m_listWidget->currentItem()->text();
    //数据结构
    for (int i = 0; i < m_things->count(); i++) {
        if (todoThing == m_things->at(i).getTodoThing()) { m_things->removeAt(i); break; }
    }
    QListWidgetItem *curItem = ui->m_listWidget->currentItem();
    ui->m_listWidget->removeItemWidget(curItem);
    delete curItem;
}

void QueryDialog::on_m_deleteAllButton_clicked()
{
    QListWidgetItem *curItem = ui->m_listWidget->currentItem();
    while(curItem != NULL) {
        QString todoThing = curItem->text();
        for (int i = 0; i < m_things->count(); i++) {
            if (todoThing == m_things->at(i).getTodoThing()) { m_things->removeAt(i); break; }
        }
        ui->m_listWidget->removeItemWidget(curItem);
        delete curItem;
        curItem = ui->m_listWidget->currentItem();
    }
}

void QueryDialog::on_fileDragedOut(QString fileName) {
    for (int i = 0; i < m_files->count(); i++) {
        if (m_files->at(i).getFileName() == fileName) {
            m_files->removeAt(i);
            i--;
        }
    }
}

void QueryDialog::on_m_exceptButton_clicked() {
    int index = ui->m_listWidget->currentRow();
    if(index < 0) return;
    QString todoThing = ui->m_listWidget->currentItem()->text();
    for (int i = 0; i < m_things->count(); i++) {
        if (todoThing == m_things->at(i).getTodoThing()) { (*m_things)[i].addException(m_today); break; }
    }
    QListWidgetItem *curItem = ui->m_listWidget->currentItem();
    ui->m_listWidget->removeItemWidget(curItem);
    delete curItem;
}

void QueryDialog::on_m_editButton_clicked()
{
    int index = ui->m_listWidget->currentRow();
    if(index < 0) return;
    QString oldTodoThing = ui->m_listWidget->currentItem()->text();
    int v_index = 0;
    for (int i = 0; i < m_things->count(); i++) {
        if (oldTodoThing == m_things->at(i).getTodoThing()) { v_index = i; break; }
    }
    AddItemDialog* additemdialog = new AddItemDialog(this, m_things->at(v_index).getTodoThing(), m_things->at(v_index).getRepeatMode());
    QString todoThing;
    int repeatMode;
    int repeatPeriod;
    if (additemdialog->exec() == QDialog::Accepted) {
        todoThing = additemdialog->getTodoThing();
        repeatMode = additemdialog->getRepeatMode();
        repeatPeriod = additemdialog->getRepeatPeriod();
    }
    if (todoThing.length() == 0) return;
    m_things->removeAt(v_index);
    m_things->append(Thing(m_today, todoThing, repeatMode, repeatPeriod));
    QListWidgetItem *curItem = ui->m_listWidget->currentItem();
    ui->m_listWidget->removeItemWidget(curItem);
    delete curItem;
    ui->m_listWidget->addItem(todoThing);
}
