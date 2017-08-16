#include "Calendar.h"
#include <QtWidgets>
#include <QInputDialog>
#include <QTextCharFormat>
#include <QDebug>
#include <QtGlobal>
#include <QVariant>
#include "querydialog.h"

Calendar::Calendar(const QString &username): m_userName(username)
{
    m_currentDate = QDate::currentDate();
    m_outlinePen.setColor(Qt::red);
    m_transparentBrush.setColor(Qt::transparent);
    c_tableView = findChild<QTableView*>("qt_calendar_calendarview");
    this->setHorizontalHeaderFormat(LongDayNames);
    this->setVerticalHeaderFormat(NoVerticalHeader);
    this->setFirstDayOfWeek(Qt::Monday);
//    this->connect(this, SIGNAL(backgroundColorChanged(QDate, QColor)), this, SLOT(setBackgroundColor(QDate, QColor)));
}

Calendar::~Calendar() { }

void Calendar::addNote( const QDate &date )
{
    QColor *paraColor = NULL;
    for (int i = 0; i < m_dates.count(); ++i) {
        if (date == m_dates.at(i)) {
            paraColor = &m_colors[i];
            break;
        }
    }
    if (paraColor == NULL) {
        paraColor = new QColor(Qt::transparent);
    }

    QueryDialog *querydialog = new QueryDialog(date, paraColor, &m_things, &m_files, this);

    if(querydialog->exec() == QDialog::Accepted) {
        if(!m_dates.contains(date) && *paraColor != Qt::transparent)
        {
            m_dates.append(date);
            m_colors.append(*paraColor);
        }
        QTextCharFormat cf = this->dateTextFormat(date);
        cf.setBackground(*paraColor);
        setDateTextFormat(date, cf);
    }
}

void Calendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
//    QCalendarWidget::paintCell(painter, rect, date);
    //画背景色
    painter->setBrush(Qt::transparent);
    painter->setPen(Qt::transparent);
    for (int i = 0; i < m_dates.count(); i++) {
        if (date == m_dates.at(i)) {
            QColor settingColor = m_colors.at(i);
            painter->setBrush(settingColor);
            break;
        }
    }
    painter->drawRect(rect);
    //画日期
    if(date.month() != this->monthShown()) painter->setPen(Qt::gray);
    else if(date.dayOfWeek() == 6 || date.dayOfWeek() == 7) painter->setPen(Qt::red);
    else painter->setPen(Qt::black);
    QFont dateFont("Helvetica", 16);
    dateFont.setItalic(true);
    painter->setFont(dateFont);
    QVariant day = date.day();
    painter->drawText(rect.adjusted(5,5,0,0), day.toString());
    //如果是今天，画红色边框
    painter->setPen(m_outlinePen);
    painter->setBrush(m_transparentBrush);
    if (date == QDate::currentDate()) {
        painter->drawRect(rect.adjusted(0,0,-1,-1));
    }
    //写事项和文字
    QString drawtext;
    painter->setPen(Qt::blue);
    painter->setFont(QFont("Helvetica", 13));
    painter->setBrush(m_transparentBrush);
    for (int i = 0; i < m_things.count(); i++) {
       if (m_things.at(i).isValidToday(date)) {
            drawtext = drawtext + tr("<Todo>") + m_things.at(i).getTodoThing() + QString("\n");
        }
    }
    for (int i = 0; i < m_files.count(); i++) {
        if (m_files.at(i).getDate() == date) {
            drawtext = drawtext + tr("<File>") + m_files.at(i).getFileName() + QString("\n");
        }
    }
    painter->drawText(rect.adjusted(10,20,0,0), drawtext);
}

//void Calendar::setBackgroundColor(const QDate &date, const QColor &color) {
//    QTextCharFormat cf = this->dateTextFormat(date);
//    if(cf.background().color() == color) return;
//    cf.setBackground(color);
//    setDateTextFormat(date, cf);
//}

void Calendar::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list")) {
        if (event->mimeData()->urls().count() > 1) {
            QMessageBox::warning(this,tr("Warning"),tr("Too many files selected!"));
            event->ignore();
            return;
        }
        event->acceptProposedAction();
    }
    QCalendarWidget::dragEnterEvent(event);
}

void Calendar::dropEvent(QDropEvent *event)
{
    QPoint dropPos = event->pos();
    QModelIndex index = c_tableView->indexAt(dropPos);
    int dayShown = index.data().toInt();
    QDate dropDate(yearShown(), monthShown(), dayShown);

    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) return;

    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) return;
    QString oldFileName = fileName;
    fileName = fileName.section("/",-1,-1);
    QFile::copy(oldFileName, "./"+fileName);

    m_files.append(File(fileName, dropDate));
}
