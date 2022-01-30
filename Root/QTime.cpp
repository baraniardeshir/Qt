#include <QTime.h>

QTime qTime;

#ifdef XSDK
// 1 tick = (1/312.5Mhz)S = 3.2ns
double QTime::getTimerTick(){
    XTime t;
    XTime_GetTime(&t);
    return t;
}
#endif

void QTime::delayMs(uint64_t ms) {
#ifdef XSDK
    uint64_t now = getNowMs();
    while((getNowMs() - now) < ms);
#else
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif
}

void QTime::delayUs(uint64_t us) {
#ifdef XSDK
    uint64_t now = getNowUs();
    while((getNowUs() - now) < us);
#else
    std::this_thread::sleep_for(std::chrono::microseconds (us));
#endif

}
void QTime::delayNs(uint64_t ns) {

#ifdef XSDK
    uint64_t now = getNowNs();
    while((getNowNs() - now) < ns);
#else
    std::this_thread::sleep_for(std::chrono::nanoseconds (ns));
#endif
}

void QTime::delayS(uint64_t s) {

#ifdef XSDK
    uint64_t now = getNowS();
    while((getNowS() - now) < s);
#else
    std::this_thread::sleep_for(std::chrono::seconds (s));
#endif

}

double QTime::getNowMs(){

#ifdef XSDK
    return (getNowUs() / 1e3);
#else
    return (std::chrono::system_clock::now().time_since_epoch().count() / 1e4);
#endif

}

double QTime::getNowUs() {

#ifdef XSDK
    return (getNowNs() / 1e3);
#else
    return (std::chrono::system_clock::now().time_since_epoch().count() / 1e1);
#endif

}

double QTime::getNowNs() {

#ifdef XSDK
    return (getTimerTick() * (((double)1e9) / COUNTS_PER_SECOND));
#else
    return (std::chrono::system_clock::now().time_since_epoch().count() * 1e2);
#endif
}

double QTime::getNowS() {

#ifdef XSDK
    return (getNowMs() / 1e3);
#else
    return (std::chrono::system_clock::now().time_since_epoch().count() / 1e7);
#endif

}
