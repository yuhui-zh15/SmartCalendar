#ifndef CLASSLABEL_H
#define CLASSLABEL_H

#include <QLabel>


class ClassLabel: public QLabel
{
    Q_OBJECT
public:
    ClassLabel(QWidget* parent = 0);
private:
    int no;
};

#endif // CLASSLABEL_H
