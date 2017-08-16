#include "addclassdialog.h"
#include "ui_addclassdialog.h"

AddClassDialog::AddClassDialog(QWidget *parent, QString className, QString teacherName, QString classRoom, int startWeek, int endWeek, int classDay, int classTime) :
    QDialog(parent),
    ui(new Ui::AddClassDialog)
{
    ui->setupUi(this);
    m_className = className;
    m_teacherName = teacherName;
    m_classRoom = classRoom;
    m_startWeek = startWeek;
    m_endWeek = endWeek;
    m_classDay = classDay;
    m_classTime = classTime;
    ui->nameLineEdit->setText(m_className);
    ui->teacherLineEdit->setText(m_teacherName);
    ui->roomLineEdit->setText(m_classRoom);
    ui->startSpinBox->setValue(m_startWeek);
    ui->endSpinBox->setValue(m_endWeek);
    ui->dayComboBox->setCurrentIndex(m_classDay - 1);
    ui->timeComboBox->setCurrentIndex(m_classTime - 1);
}

AddClassDialog::~AddClassDialog()
{
    delete ui;
}

void AddClassDialog::on_buttonBox_accepted()
{
    m_className = ui->nameLineEdit->text();
    m_classRoom = ui->roomLineEdit->text();
    m_teacherName = ui->teacherLineEdit->text();
    m_startWeek = ui->startSpinBox->value();
    m_endWeek = ui->endSpinBox->value();
    m_classDay = ui->dayComboBox->currentIndex() + 1;
    m_classTime = ui->timeComboBox->currentIndex() + 1;
}
