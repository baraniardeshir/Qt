#pragma once
#include <iostream>
#include <QSingleton.h>
#include <QString.h>
using namespace std;

class QDebug : public QSingleton<QDebug>{

    friend class QSingleton<QDebug>;
public:
    explicit QDebug(bool en = false);
    void enable() {debugEnable = true;}
    void disable() {debugEnable = false;}

    QDebug& operator<<(const QString& bString);
    QDebug& operator<<(const string& String);
    QDebug& operator<<(const char* c);
    QDebug& operator<<(int n);
    QDebug& operator<<(double n);
    QDebug& operator<<(float n);
    QDebug& operator<<(char n);
    QDebug& operator<<(short n);
    QDebug& operator<<(bool n);

private:
    bool debugEnable = {};


};

extern QDebug qDebug;