#include <QElapsedTimer.h>

void QElapsedTimer::start() {
    if(!running) {
        startedEpoch = qTime.getNowNs();
        running = true;
    }
}

void QElapsedTimer::stop() {
     running = false;
}

uint64_t QElapsedTimer::nsecsElapsed() {
    if(running)
        elapsedTimeNs = qTime.getNowNs() - startedEpoch;
    return elapsedTimeNs;
}

void QElapsedTimer::restart() {

    if(running) {
        startedEpoch = qTime.getNowNs();
        elapsedTimeNs = 0;
        running = true;
    }
}

uint64_t QElapsedTimer::usecsElapsed() {
    return (nsecsElapsed() / 1e3);
}

uint64_t QElapsedTimer::msecsElapsed() {
    return (nsecsElapsed() / 1e6);
}

uint64_t QElapsedTimer::secsElapsed() {
    return (nsecsElapsed() / 1e9);
}
