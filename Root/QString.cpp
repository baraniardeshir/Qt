#include <QString.h>

#include <utility>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <QStringList.h>
#include <cstdlib>
#include <QByteArray.h>

QString operator+(const char* c, const QString& str) {
    QString out(c);
    return (out + str);
}

QStringList QString::split(const QString& sep, bool SkipEmptyParts) const{
    if(this->empty())
        return QStringList();
    QStringList strList;
    QString str = *this;
    size_t pos = 0;
    QString token;
    while ((pos = str.find(sep)) != QString::npos) {
        token.assign(str.substr(0, pos));
        if(SkipEmptyParts){
            if(!token.empty())
                strList.push_back(token);
        }
        else{
            strList.push_back(token);
        }
        token.clear();
        str.erase(0, pos + sep.length());
    }
    return strList;
}

QByteArray QString::toUtf8() const {
    if(this->size() > 0) 
        return QByteArray(this->data(), this->size());
    return QByteArray();
}


bool QString::contains(const QString &str, bool caseSensitivity) const {
    return (std::string::find(str) != std::string::npos );
}

QStringList QString::split(char sep, bool SkipEmptyParts) const{
    if(this->empty())
        return QStringList();
    QStringList strList;
    QString str = *this;
    size_t pos = 0;
    QString token;
    bool flag = false;
    while ((pos = str.find(sep)) != QString::npos) {
        flag = true;
        token.assign(str.substr(0, pos));
        if(SkipEmptyParts){
            if(!token.empty())
                strList.push_back(token);
        }
        else{
            strList.push_back(token);
        }
        token.clear();
        str.erase(0, pos + 1);
    }
    if(flag)
        strList.push_back(str);
    return strList;
}

int QString::indexOf(char c) const{
    auto it = std::find(cbegin(), cend(), c);
    if (it == cend())
        return -1;
    else
        return std::distance(cbegin(), it);
}
QVector<int> QString::indexesOf(char c) const{
	QVector<int> out;
	auto startOfFind = cbegin();
	auto foundIt = cend();
	while (1) {
		foundIt = std::find(startOfFind, cend(), c);
		if (foundIt == cend())
			return out;
		else {
			out.push_back(std::distance(cbegin(), foundIt));
			startOfFind = foundIt + 1;
		}
	}
}

QString QString::chop(int n) const{
    QString str = *this;
    str.erase(str.size() - n, n);
    return str;
}

QString QString::mid(int pos, int n) const{
    QString temp;
    for(size_t i = pos; i < ((n > 0) ? (pos + n) : (size())); i++){
        temp.push_back(at(i));
    }
    return temp;
}

bool QString::startsWith(const QString &startWith)const {
    if (rfind(startWith, 0) == 0)
        return true;
    return false;
}

QString QString::left(int index) const{
    if(index > this->size() - 1)
        return {};
    QString temp;
    for(int i = 0; i < index; i++){
        temp.push_back(this->at(i));
    }
    return temp;
}

QString QString::right(int index)const {
    if(index > this->size() - 1)
        return {};
    QString temp;
    for(int i = index + 1; i < this->size(); i++){
        temp.push_back(at(i));
    }
    return temp;
}

int QString::toInt(bool *stat) const{
    int out = 0;
    try {
        out = std::stoi(*this);
        *stat = true;
    }
    catch (...) {
        *stat = false;
    }
    return out;
}

QString::QString(std::string s)
:std::string(std::move(s))
{
}

QString::QString(const QByteArray& BA) {
    std::string::append(BA.data(), BA.size());
}

void QString::remove(const QString &str) {
    for(auto i = this->begin(); i != this->end(); i++){
        size_t pos = find(str);
        if (pos != std::string::npos) {
            // If found then erase it from string
            this->erase(pos, str.length());
        }
    }
}

uint64_t QString::toULongLong(bool *stat) const{
    uint64_t out = 0;
    try {
        out = std::stoull(*this);
        *stat = true;
    }
    catch (...) {
        *stat = false;
    }
    return out;
}

double QString::toDouble(bool *stat) const{
	double out;
    try {
    	out = std::stod(*this);
        *stat = true;
    }
    catch (...) {
        *stat = false;
    }
    return out;
}

QString& QString::operator=(std::string& str) {
    std::string::append(str);
    return *this;
}


QString &QString::operator<<(const QString& str) {
    std::string::append(str);
    return *this;
}

QString &QString::operator+(const QString &str) {
    std::string::append(str);
    return *this;
}



bool QString::isEmpty() const{
    return this->empty();
}

QString &QString::operator<<(const size_t &i) {
    std::string::append(std::to_string(i));
    return *this;
}

QString::QString(const char* c) {
    std::string::append(c);
}



QString QString::number(double n, char format, int precision) {

	std::stringstream ss;
	ss << std::fixed << std::setprecision(precision) << n;
	std::string out = ss.str();
	return QString(out);
}

QString &QString::operator+(const char * c) {
    std::string::append(c);
    return *this;
}

QString QString::leftJustified(int width, char fill, bool trunc) const{

    if(this->size() >= width) {
        if(trunc)
            return this->left(width);
        else
            return *this;
    }
    else if (this->size() < width) {
        QString out = *this;
        out += QString(width - this->size(), fill);
        return  out;
    }

    return QString();
}

QString QString::number(long n, int base){
    return anyDigitToString(n, base);
}

QString QString::number(int n, int base) {
    return anyDigitToString(n, base);
}

QString QString::number(unsigned int n, int base) {
    return anyDigitToString(n, base);
}

QString QString::number(unsigned long n, int base) {
    return anyDigitToString(n, base);
}

QString QString::number(long long int n, int base) {
    return anyDigitToString(n, base);
}

QString QString::number(unsigned long long int n, int base) {
    return anyDigitToString(n, base);
}

void QString::remove(char c) {
    this->remove(QString(&c));
}

QString QString::rightJustified(int width, char fill, bool trunc)const {

    if(this->size() >= width) {
        if(trunc)
            return this->left(width);
        else
            return *this;
    }
    else if (this->size() < width) {
        QString out = QString(width - this->size(), fill) + *this;
        return  out;
    }

    return QString();
}

QString QString::toLower()const {
    QString out( this->data(), this->size());
    for(int i = 0; i < out.size(); i++) {
        if(out[i] >= 0x41 && out[i] <= 0x5A)
            out[i] += 0x20;
    }
    return out;
}
QString QString::toUpper() const{
    QString out( this->data(), this->size());
    for(int i = 0; i < out.size(); i++) {
        if(out[i] >= 0x61 && out[i] <= 0x7A)
            out[i] -= 0x20;
    }
    return out;
}

QString& QString::append(const QByteArray& arr) {
    std::string::append(arr.data(), arr.size());
    return *this;
}

QString QString::reverse() const {
    QString out;
    for (int i = size() - 1 ; i >= 0 ; i--) {
        out.push_back(this->at(i));
    }
    return out;
}

QString& QString::operator <<(const QByteArray& arr) {
	for(auto it : arr){
		this->push_back(it);
	}

	return *this;
}

uint64_t QString::checksum() const {
	uint64_t out = 0;
	for(auto i = 0; i < this->size(); i++) {
		out += *(data() + i);
	}
	return out;
}
