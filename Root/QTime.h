#pragma once
#ifdef XSDK
    #include <xtime_l.h>
#else
    #include <chrono>
    #include <thread>
#endif
#include <cstdint>
#include <QSingleton.h>

class QTime : public QSingleton<QTime> {

    friend class QSingleton<QTime>;
public:
    void delayMs(uint64_t ms);
    void delayUs(uint64_t us);
    void delayNs(uint64_t ns);
    void delayS(uint64_t s);

#ifdef XSDK
    double getTimerTick();
#endif
    double getNowMs();
    double getNowUs();
    double getNowNs();
    double getNowS();

private:

};

extern QTime qTime;
