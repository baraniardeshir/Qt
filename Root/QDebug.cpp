#include <QDebug.h>
#include <QString.h>

QDebug qDebug;


QDebug &QDebug::operator<<(const QString &bString) {
    if(debugEnable)
        cout << bString;
    return *this;
}

QDebug &QDebug::operator<<(const string &String) {
    if(debugEnable)
        cout << String;
    return *this;
}

QDebug &QDebug::operator<<(const char *c) {
    if(debugEnable)
        cout << c;
    return *this;
}



QDebug::QDebug(bool en)
:debugEnable(en)
{

}

QDebug &QDebug::operator<<(const int n) {
    if(debugEnable)
        cout << to_string(n);
    return *this;
}

QDebug &QDebug::operator<<(double n) {
    if(debugEnable)
        cout << to_string(n);
    return *this;
}

QDebug &QDebug::operator<<(float n) {
    if(debugEnable)
        cout << to_string(n);
    return *this;
}

QDebug &QDebug::operator<<(char n) {
    if(debugEnable)
        cout << to_string(n);
    return *this;
}

QDebug &QDebug::operator<<(short n) {
    if(debugEnable)
        cout << to_string(n);
    return *this;
}

QDebug &QDebug::operator<<(bool n) {
    if(debugEnable)
        cout << to_string(n);
    return *this;
}
