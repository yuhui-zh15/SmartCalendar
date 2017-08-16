#include "timelabel.h"
#include <QDateTime>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>

TimeLabel::TimeLabel(QWidget *parent) :
    QLabel(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    showTime();
}

void TimeLabel::showTime()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式
    setText(str);//在标签上显示时间
}
