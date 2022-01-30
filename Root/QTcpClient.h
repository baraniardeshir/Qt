#pragma once
#ifdef XSDK
#ifdef FREERTOS

#include <QHostAddress.h>
#include <QByteArray.h>

class QTcpClient {
	friend class QTcpServer;
public:
	QTcpClient(const QHostAddress& Addr, int sock):
	Addr(Addr),
	sock(sock)
	{}
	QTcpClient():
		Addr(QHostAddress("")),
		sock(-1)
	{}

private:
	const int sock;
	const QHostAddress Addr;
};


#endif
#endif
