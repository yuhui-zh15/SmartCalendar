#include "classtable.h"
#include "ui_classtable.h"
#include "classmanager.h"
#include <QDebug>
#include <QVariant>
#include <QInputDialog>

ClassTable::ClassTable(QWidget *parent, QString semester, int endWeek) :
    QWidget(parent),
    ui(new Ui::ClassTable)
{
    ui->setupUi(this);
    m_currentWeek = 1;
    if (semester == "" && endWeek == 0) {
        m_semester = QInputDialog::getText(this, tr("Semester Name"), tr("Please input semester name: "), QLineEdit::Normal, "");
        m_endWeek = QInputDialog::getText(this, tr("End Week"), tr("Please input end week: "), QLineEdit::Normal, "").toInt();
    }
    for (int i = 1; i <= 49; i++) {
        QVariant label_no = i;
        QString label_str = "label_" + label_no.toString();
        QLabel* label = findChild<QLabel*>(label_str);
        label->setText("");
    }
    ui->semesterLabel->setText(m_semester);
    QVariant m_currentWeekStr = m_currentWeek;
    ui->weekShownLabel->setText(m_currentWeekStr.toString());
}

ClassTable::~ClassTable()
{
    delete ui;
}

void ClassTable::on_manageButton_clicked()
{
    ClassManager* classManager = new ClassManager(&m_classes);
    classManager->exec();
    refreshTable();
}

void ClassTable::refreshTable() {
    for (int i = 1; i <= 49; i++) {
        QVariant label_no = i;
        QString label_str = "label_" + label_no.toString();
        QLabel* label = findChild<QLabel*>(label_str);

        QString drawText = "";
        int row = (i - 1) / 7 + 1;
        int column = i - (row - 1) * 7;
        for (int i = 0; i < m_classes.count(); i++) {
            if (m_classes.at(i).isValid(m_currentWeek, row, column)) {
                drawText = drawText + m_classes.at(i).m_className + '\n' + m_classes.at(i).m_teacherName + '\n' + m_classes.at(i).m_classRoom + '\n';

            }
        }

        label->setText(drawText);
    }
    QVariant m_currentWeekStr = m_currentWeek;
    ui->weekShownLabel->setText(m_currentWeekStr.toString());
}

void ClassTable::on_prevWeekButton_clicked()
{
    m_currentWeek = (m_currentWeek == 1)? 1: m_currentWeek - 1;
    refreshTable();
}

void ClassTable::on_nextWeekButton_clicked()
{
    m_currentWeek = (m_currentWeek == m_endWeek)? m_endWeek: m_currentWeek + 1;
    refreshTable();
}
