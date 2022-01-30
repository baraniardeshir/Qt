#pragma once
#include <QVector.h>
#include <algorithm>
#include <cstdint>
#include <string>
using namespace std;

class QString;

class QByteArray : public QVector<char> {
public:
    explicit QByteArray(int size);
    explicit QByteArray(const char* data, int size);
    QByteArray(int size, char value);
    QByteArray();
    int indexOf(char c) const;
    QByteArray mid(int pos, int n = -1) const;
    QByteArray left(int index) const;
    QByteArray right(int index) const;
    QString toHexString() const;
    QByteArray toHex(char separator = -1) const;
    void printHex() const;
    QByteArray toLower() const;
    QByteArray toUpper() const;
    QString toQstring() const;

    QByteArray& append(const char *c, int len);
    QByteArray& append(const char c);
    QByteArray& append(const QString& str);
    QByteArray& append(const std::string& str);
    QByteArray& append(const QByteArray& arr);

    inline const char* constData() const {
    	return this->data();
    }


    QByteArray& operator<<(const QString& str);

    friend ostream& operator<<(ostream& os, const QByteArray& qByteArray);

private:


};
