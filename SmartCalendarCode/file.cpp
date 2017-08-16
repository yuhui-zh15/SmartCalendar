#include "file.h"

File::File() { }
File::~File() { }
File::File(const QString &fileName, const QDate &date) { m_fileName = fileName; m_date = date; }
QString File::getFileName() const { return m_fileName; }
QDate File::getDate() const { return m_date; }
