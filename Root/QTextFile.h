#include <QFile.h>

namespace Qt {

class QTextFile : private QFile {

private:







public:

	using QFile::create;
	using QFile::open;
	using QFile::size;
	using QFile::isOpen;
	using QFile::close;
	using QFile::isEOF;
	using QFile::remove;
	using QFile::exist;
	using QFile::getPath;
	using QFile::write;
	#ifdef XSDK
	using QFile::getLastError;
	#endif

	QTextFile(QString filePath) : QFile(filePath) {};
	QTextFile();
	~QTextFile();

	QStringList readLines();
	QString readAll();
	QString readLine(int lineNumber);


	void writeString(const QString& str);
	void writeNewLine(const QString& line);
	void appendNewLine(int lineNumber, const QString& line);

};

}
