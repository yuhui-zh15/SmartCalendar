#include "dragablelistwidget.h"
#include <QDrag>
#include <QMimeData>
#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QDebug>

void DragableListWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->pos();
    }
    QListWidget::mousePressEvent(event);
}

void DragableListWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton)) return;
    if ((event->pos() - m_dragStartPosition).manhattanLength() < 10) return;
    QListWidgetItem *item = currentItem();
    if (item == NULL) return;

    QDrag *drag = new QDrag(this);
    QMimeData *qm = new QMimeData;

    QString fileName = item->text();
    emit(fileDragedOut(fileName));
    QFileInfo fileInfo(fileName);

    QList<QUrl> fileNames;
    fileNames.clear();
    fileNames.append(QUrl::fromLocalFile(fileInfo.absolutePath()+ "/" +fileName));

    qm->setUrls(fileNames);
    drag->setMimeData(qm);

    Qt::DropAction dropAction = drag->exec(Qt::MoveAction);
    delete item;
}
