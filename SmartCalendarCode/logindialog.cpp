#include "logindialog.h"
#include "ui_logindialog.h"
#include "Calendar.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <string>

LoginDialog::LoginDialog(QWidget *parent): QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this); 
}

LoginDialog::~LoginDialog() {
    delete ui;
}

void LoginDialog::on_loginButton_clicked() {
    QString username = ui->username->text();
    if(username == "") {
        QMessageBox::information(NULL, tr("Error"), tr("Please input user name!"));
    }
    else {
        MainWindow *w = new MainWindow(username);
        w->show();
        this->close();
    }
}
