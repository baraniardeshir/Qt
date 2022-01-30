#include <iostream>
#include "fstream"
#include <QString.h>
#include "QStringStream.h"
#include <QStringList.h>
#include <QFile.h>
#include <QByteArray.h>
#include <QHash.h>
#include <QDate.h>
#include <QDateTime.h>
#include <QVector.h>
#include <QTimer.h>
#include <QDebug.h>
#include <QElapsedTimer.h>
#include <QTextStream.h>
#include <QDataStream.h>
#include <QSet.h>
#include <QList.h>
#include <QQueue.h>
#include <QTextFile.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <exception>




using namespace std;
using namespace Qt;

int main() {
    char* c = new char[10];
    char cStr[] = "salam";
    memcpy(c, cStr, sizeof(cStr));

    QString str(c, 5);
    cout << str << endl;
    delete c;
    cout << str;

    return 0;
}

