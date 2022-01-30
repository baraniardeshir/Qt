#pragma once
#ifdef FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

class QMutex {
	friend class QMutexLocker;
public:
	enum RecursionMode{
		Recursive,
		NonRecursive
	} ;
	QMutex(RecursionMode mode = NonRecursive, bool areSamePriorityTask = false);
	~QMutex();
	void lock();
	void unlock();
	bool isLocked() { return locked; }

private:
	SemaphoreHandle_t mutex = NULL;
	bool locked = false;
	RecursionMode mode;
	int lockCount = 0;
	bool samePriority = false;
};

#endif
