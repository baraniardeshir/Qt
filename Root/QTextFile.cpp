
#include <QTextFile.h>
#include <QStringList.h>
#include <iostream>
namespace Qt {

QTextFile::QTextFile() {
}

QTextFile::~QTextFile() {
}

QStringList QTextFile::readLines() {
	return readAll().split('\n');
}

}

void Qt::QTextFile::writeNewLine(const QString& line) {
	QFile::seekToEOF();
	QFile::write(line);
	QFile::write("\n");
	QFile::flush();
}

void Qt::QTextFile::writeString(const QString& str) {
	QFile::write(str);
	QFile::flush();
}

QString Qt::QTextFile::readAll() {
	qfile_size_t availableBytes = QFile::size();
	if(availableBytes <= 0) return QString();
	QByteArray bytesRead = QFile::read(availableBytes);
	return QString(bytesRead.data(), bytesRead.size());
}
