#ifndef DRAGABLELISTWIDGET_H
#define DRAGABLELISTWIDGET_H

#include <QListWidget>
#include <QString>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPoint>

class DragableListWidget: public QListWidget
{
    Q_OBJECT
public:
    DragableListWidget(QWidget *parent = 0): QListWidget(parent) { setAcceptDrops(true); }
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dropEvent(QDropEvent *event);
signals:
    void fileDragedOut(QString);
private:
    QPoint m_dragStartPosition;
};

#endif // DRAGABLELISTWIDGET_H
