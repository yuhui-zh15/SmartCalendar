#ifndef TIMELABEL_H
#define TIMELABEL_H

#include <QLabel>
#include <QPaintEvent>
#include <QTimer>
#include <QWidget>

class TimeLabel : public QLabel
{
    Q_OBJECT

public:
    TimeLabel(QWidget *parent = 0);
    QTimer *timer;

public slots:
    void showTime();
};

#endif // TIMELABEL_H
