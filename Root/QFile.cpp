#include <QFile.h>

namespace Qt {

	#ifdef FREERTOS
	static QMutex qfileMutex(QMutex::Recursive, true);
	#endif

	QFile::QFile(QString filePath):
		path(std::move(filePath))
	{
	#ifndef XSDK
        fillFileModeMap();
	#endif
	}

    QFile::QFile() {

    #ifndef XSDK
        fillFileModeMap();
    #endif
	}


	qfile_size_t QFile::size() {
	#ifdef XSDK
		return f_size(&file);
	#else
		if(!file.is_open())
			return -1;
		std::streampos fileSize, currentPos;
		currentPos = file.tellg();
		file.seekg(0, std::ios::end);
		fileSize = file.tellg();
		file.seekg(currentPos);
		return fileSize;
	#endif
	}

	QByteArray QFile::read(qfile_size_t count)
	{

	    QByteArray buff;
	    buff.resize(count);
	#ifdef XSDK
		UINT br;
	#ifdef FREERTOS
		QMutexLocker locker(&qfileMutex);
	#endif
		res = f_read(&file, buff.data(), count, &br);
    #else
		int br = file.read(buff.data(), count).gcount();
	#endif
        if (br != count) {
            buff.resize(br);
        }
	    return buff;
	}

	qfile_size_t QFile::read(void *data, qfile_size_t count) {
	#ifdef XSDK
		UINT br = 0; // bytes read
	#ifdef FREERTOS
	QMutexLocker locker(&qfileMutex);
	#endif
		res = f_read(&file, data, count,&br);
		return br;
	#else
		return file.read((char*)data, count).gcount();
	#endif
	}

	qfile_size_t QFile::pos() {
	#ifdef XSDK
		return f_tell(&file);
	#else
		return file.tellg();
	#endif
	}

	void QFile::seek(qfile_size_t pos) {
	#ifdef XSDK

	#ifdef FREERTOS
		QMutexLocker locker(&qfileMutex);
	#endif
		res = f_lseek(&file, pos);
	#else
		file.seekg(pos);
	#endif
	}

	bool QFile::open(QFile::QFileMode mode) {
	#ifdef XSDK
	#ifdef FREERTOS
		QMutexLocker locker(&qfileMutex);
	#endif
		res = f_open(&file, path.c_str(), mode);
		res ? isOpened = false : isOpened = true;
		if(isOpened){
			res = f_stat(path.c_str(), &info);
			if(res)
				isOpened = false;
		}
		return isOpened;
	#else
		if(!fileMode.contains(mode)) {
		    std::cout << "filemode map error\n";
            return false;
        }
		file.open(path, fileMode.value(mode));
		return file.good();
	#endif
	}



	bool QFile::isOpen() {
	#ifdef XSDK
		return isOpened;
	#else
		return file.is_open();
	#endif
	}

	bool QFile::close() {
	#ifdef XSDK
		bool out = false;
		if(isOpened) {
	#ifdef FREERTOS
			QMutexLocker locker(&qfileMutex);
	#endif
			if(f_close(&file) == FR_OK) {
				out = true;
			}
		}
		else {
			out = true;
		}
		return out;
	#else
		file.close();
		return file.is_open();
	#endif
	}

	qfile_size_t QFile::write(const void* data, qfile_size_t count) {
	#ifdef XSDK
		UINT bw = 0;// bytes written
	#ifdef FREERTOS
		QMutexLocker locker(&qfileMutex);
	#endif
		res = f_write(&file, data, count, &bw);
		if(res == FR_OK)
			return bw;
		return -1;
	#else

		return -1;
	#endif
	}

#ifndef XSDK
    void QFile::fillFileModeMap() {
        fileMode = {
                {QFileReadOnly, std::ios_base::in | std::ios_base::binary},
                {QFileWriteOnly, std::ios_base::out | std::ios_base::binary},
                {QFileRW, std::ios_base::in | std::ios_base::out | std::ios_base::binary},
        };
    }

#endif

	qfile_size_t QFile::write(const QByteArray& arr) {
	#ifdef XSDK
		return this->write(arr.data(), arr.size());
	#else
		return -1;
	#endif
	}

	bool QFile::flush() {
		bool out = false;
	#ifdef XSDK
		if(isOpened) {
	#ifdef FREERTOS
			QMutexLocker locker(&qfileMutex);
	#endif
			res = f_sync(&file);
			out = (res == FR_OK);
		}
	#else
		file.flush();
        return true;
	#endif
        return out;
	}

	qfile_size_t QFile::write(const QString& str) {
	#ifdef XSDK
		return this->write(str.data(), str.size());
	#else
        file.write(str.data(), str.size());
        return  str.size();
	#endif
	}

	QFile::~QFile(){
	#ifdef FREERTOS
		QMutexLocker locker(&qfileMutex);
	#endif
		close();
	}

	void QFile::setPath(QString filePath) {
		path = filePath;
	}
	bool QFile::isEOF() {
	#ifdef XSDK
		return f_eof(&file);
	#else
		return file.eof();
	#endif
	}
	bool QFile::remove() {
		bool out = false;
	#ifdef XSDK

	#else

	#endif
	return out;
	}

	bool QFile::exist(const QString& filePath) {
		bool out = false;
	#ifdef XSDK
		if(filePath.isEmpty()) return false;

		FRESULT _res;
		FILINFO _inf;
	#ifdef FREERTOS
		QMutexLocker locker(&qfileMutex);
	#endif
		_res = f_stat(filePath.c_str(), &_inf);
		out = (_res == FR_OK);
	#else

	#endif
	return out;
	}

	bool QFile::create(const QString& filePath) {
		bool out = false;
	#ifdef XSDK
		{
			#ifdef FREERTOS
			QMutexLocker locker(&qfileMutex);
			#endif
			if(exist(filePath)) return true;
		}
		FIL _file = {};
		FRESULT _res;
		{
			#ifdef FREERTOS
			QMutexLocker locker(&qfileMutex);
			#endif
			_res = f_open(&_file, filePath.c_str(), QFileCreateNew);
			if (_res != FR_OK) return false;
		}
		{
			#ifdef FREERTOS
			QMutexLocker locker(&qfileMutex);
			#endif
			_res = f_close(&_file);
		}
		out = (_res == FR_OK);
	#else

	#endif
	return out;
	}


	void QFile::rewind() {
	#ifdef XSDK
		#ifdef FREERTOS
		QMutexLocker locker(&qfileMutex);
		#endif
		f_rewind(&file);
	#else

	#endif
	}

	void QFile::seekToEOF()  {
	#ifdef XSDK
		#ifdef FREERTOS
		QMutexLocker locker(&qfileMutex);
		#endif
		seek(size());
	#else

	#endif
	}

}

