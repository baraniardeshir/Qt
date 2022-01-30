#pragma  once

#ifdef XSDK
#include "ff.h"
typedef int64_t qfile_size_t;
#ifdef FREERTOS
#include <QMutex.h>
#include <QMutexLocker.h>
#endif
#else
#include <fstream>
#include <QHash.h>
typedef std::streamsize qfile_size_t;
#endif
#include <utility>
#include <QString.h>
#include <QByteArray.h>
#include <Qint.h>

namespace Qt {
	class QFile {
	public:

		enum QFileMode {
	#ifdef XSDK
			QFileReadOnly		= 0x01,
			QFileWriteOnly		= 0x02,
			QFileOpenExisting	= 0x00,
			QFileCreateNew		= 0x04,
			QFileCreateAlways	= 0x08,
			QFileOpenAlways	    = 0x10,
			QFileOpenAppend	    = 0x30,
			QFileAppend	    	= (0x10 | 0x02),
			QFileReadWrite		= (0x01 | 0x02),
			QFileTemp			= (0x01 | 0x02 | 0x00 | 0x04 | 0x30 | 0x04)
	#else
			QFileReadOnly,
			QFileWriteOnly,
			QFileRW,
	#endif
		};
		explicit QFile(QString filePath);
		QFile();
		~QFile();
		void setPath(QString filePath);
		qfile_size_t findPos(const quint8& c);
		qfile_size_t findPos(const QString& str);
		qfile_size_t findPos(const QByteArray& arr);

		QByteArray read(qfile_size_t count);
		qfile_size_t read(void* data, qfile_size_t count);

		qfile_size_t write(const void* data, qfile_size_t count);
		qfile_size_t write(const QByteArray& arr);
		qfile_size_t write(const QString& str);
		bool flush();

		qfile_size_t pos();
		void seek(qfile_size_t pos);
		void rewind();
		void seekToEOF();

	#ifdef XSDK
		inline FRESULT getLastError() {
			return res;
		}
	#endif

		static bool create(const QString& filePath);
		bool open(QFileMode mode = QFileReadOnly);
		qfile_size_t size();
		bool isOpen();
		bool close();
		bool isEOF();
		bool remove();
		static bool exist(const QString& filePath);
		QString getPath() { return path;}




	private:

	#ifdef XSDK
		bool isOpened;
		FIL file = {};
		FILINFO info = {};
		FRESULT res;
    #else
		void fillFileModeMap();
		QHash<QFileMode, std::ios_base::openmode> fileMode ;
		std::fstream file;
	#endif
		 QString path;

	};
}
