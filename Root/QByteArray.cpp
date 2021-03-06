#include <QByteArray.h>
#include <QString.h>
#include <iostream>
#include <string.h>
#include <iomanip>

constexpr char lowerCaseHexMap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
constexpr char upperCaseHexMap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
int QByteArray::indexOf(char c) const {
    auto it = std::find(this->cbegin(), this->cend(), c);
    if (it == this->cend())
        return -1;
    else
        return std::distance(this->cbegin(), it);
}

QByteArray QByteArray::mid(int pos, int n) const {
    QByteArray temp;
    for(int i = pos; i < ((n > 0) ? (pos + n) : (size())); i++){
        temp.push_back(at(i));
    }
    return temp;
}

QByteArray::QByteArray(int size) {
    this->reserve(size);
}

QByteArray QByteArray::left(int index) const {
    if(index > this->size() - 1)
        return QByteArray();
    QByteArray temp;
    for(int i = 0; i < index; i++){
        temp.push_back(this->at(i));
    }
    return temp;
}

QByteArray QByteArray::right(int index) const {
    if(index > this->size() - 1)
        return QByteArray();
    QByteArray temp;
    for(int i = index + 1; i < this->size(); i++){
        temp.push_back(this->at(i));
    }
    return temp;
}

QByteArray::QByteArray(const char *data, int size) {
    if(size > 0) {
        this->reserve(size * 2);
        this->assign(data, data + size);
    }
}

QString QByteArray::toHexString() const {

    int hexStringSize = this->size() * 2;
    QString s(hexStringSize, ' ');
    for (int i = 0; i < this->size(); i++) {
        s[2 * i]     = lowerCaseHexMap[(at(i) & 0xF0) >> 4];
        s[2 * i + 1] = lowerCaseHexMap[at(i) & 0x0F];
    }
    return s;
}

QByteArray QByteArray::toHex(char separator) const {
    int hexSize = this->size() * 2;
    QByteArray out(hexSize, ' ');
    for (int i = 0; i < this->size(); i++) {
        out[2 * i]     = lowerCaseHexMap[(at(i) & 0xF0) >> 4];
        out[2 * i + 1] = lowerCaseHexMap[at(i) & 0x0F];
    }
    return out;
}

void QByteArray::printHex() const {
	printf("%s\r\n", this->toHexString().c_str());
}

QByteArray &QByteArray::append(const char *c, int len) {
    QVector<char>::reserve(len);
    QVector<char>::insert(end(), c,c + len);
    return *this;
}

QByteArray &QByteArray::append(const char c) {
    this->push_back(c);
    return *this;
}

QByteArray& QByteArray::append(const QByteArray& arr) {
	this->insert(this->end(), arr.begin(), arr.end());
	return *this;
}

QByteArray &QByteArray::operator<<(const QString &str) {
    this->append(str);
    return *this;
}

QByteArray &QByteArray::append(const QString &str) {
    return append(str.data(), str.size());
}

QByteArray &QByteArray::append(const std::string &str) {
    return append(QString(str));
}

QByteArray::QByteArray(int size, const char value) :
QVector<char>(size, value)
{}

ostream &operator<<(ostream &os, const QByteArray &qByteArray) {
    if(qByteArray.empty()) {
        cout << "empty QByteArray\n";
        return os;
    }
    for(auto it : qByteArray) {
        cout << it;
    }
    return os;
}

QByteArray QByteArray::toLower() const {
    QByteArray out( this->data(), this->size());
    for(int i = 0; i < out.size(); i++) {
        if(out[i] >= 0x41 && out[i] <= 0x5A)
            out[i] += 0x20;
    }
    return out;
}
QByteArray QByteArray::toUpper() const {
    QByteArray out( this->data(), this->size());
    for(int i = 0; i < out.size(); i++) {
        if(out[i] >= 0x61 && out[i] <= 0x7A)
            out[i] -= 0x20;
    }
    return out;
}


QString QByteArray::toQstring() const {
    QString out( this->data(), this->size());
    return out;
}

QByteArray::QByteArray() = default;
