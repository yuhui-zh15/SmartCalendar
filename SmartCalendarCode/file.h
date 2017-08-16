#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QDate>

class File
{
public:
    File();
    ~File();
    File(const QString &fileName, const QDate &date);
    QString getFileName() const;
    QDate getDate() const;
private:
    QDate m_date;
    QString m_fileName;
};

#endif // FILE_H
