#pragma once
#include <QDate.h>
#include <QTime.h>
#include <cstdint>

class QDateTime{
public:
    QDateTime(QDateTime &&other) noexcept ;
    QDateTime(const QDateTime &other);
    explicit QDateTime(const QDate &date);
    QDateTime() = default;

    inline QDate date(){ return bDate;}
    inline  QTime time(){return bTime;}
    void setMSecsSinceEpoch(int64_t msecs);


private:
    QTime bTime{};
    QDate bDate{};


};
