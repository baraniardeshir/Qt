#pragma once
#ifdef FREERTOS
#include "QMutex.h"

class QMutexLocker {

public:
	QMutexLocker(QMutex* mutex);
	~QMutexLocker();

private:
	QMutex* _QMutex;
};

#endif
