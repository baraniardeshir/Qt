#pragma once
#ifdef XSDK
#ifdef FREERTOS

#include <QHostAddress.h>
#include <QByteArray.h>

class QUdpSocket {
public:

	QUdpSocket() = default;
	int64_t writeDatagram(const char *data, int64_t len, const QHostAddress &host, uint16_t port);
    inline int64_t writeDatagram(const QByteArray &datagram, const QHostAddress &host, uint16_t port)
        { return writeDatagram(datagram.constData(), datagram.size(), host, port); }


    int64_t readDatagram(char *data, int64_t maxlen, const QHostAddress &host, uint16_t port);

private:


};


#endif
#endif
