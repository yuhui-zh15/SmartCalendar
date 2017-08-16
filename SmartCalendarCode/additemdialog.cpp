#include "additemdialog.h"
#include "ui_additemdialog.h"
#include <QInputDialog>

AddItemDialog::AddItemDialog(QWidget *parent, QString todoThing, int m_repeatMode): QDialog(parent), ui(new Ui::AddItemDialog) {
    ui->setupUi(this);
    setFixedSize(222, 310);
    m_repeatPeriod = 0;
    ui->m_textEdit->setText(todoThing);
    ui->m_repeatComboBox->setCurrentIndex(m_repeatMode - 1);
}

AddItemDialog::~AddItemDialog() {
    delete ui;
}

void AddItemDialog::on_m_isRepeatCheckBox_clicked() {
    if (ui->m_isRepeatCheckBox->isChecked()) {
        ui->m_repeatComboBox->setEnabled(true);
    }
    else {
        ui->m_repeatComboBox->setEnabled(false);
    }
}

void AddItemDialog::on_buttonBox_accepted() {
    m_todoThing = ui->m_textEdit->toPlainText();
    if (!ui->m_isRepeatCheckBox->isChecked()) m_repeatMode = 0;
    else m_repeatMode = ui->m_repeatComboBox->currentIndex() + 1;
}

void AddItemDialog::on_m_repeatComboBox_activated(int index) {
    if (index == 4) {
        m_repeatPeriod = QInputDialog::getText(this, tr("Please Set Repeat Periods"), tr("Please Set Repeat Periods")).toInt();
        if(m_repeatPeriod <= 0) m_repeatPeriod = 1;
    }
}
