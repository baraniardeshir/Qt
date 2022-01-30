#include "QMutexLocker.h"
#ifdef FREERTOS

QMutexLocker::QMutexLocker(QMutex* mutex) :
_QMutex(mutex)
{
	_QMutex->lock();
}

QMutexLocker::~QMutexLocker() {
	_QMutex->unlock();
}


#endif



