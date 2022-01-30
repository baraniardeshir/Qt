#pragma once
#include <QString.h>
class QHostAddress {
	friend class UdpClient;
	friend class UdpServer;
	friend class QUdpSocket;
	friend class QTcpServer;
public:

    enum SpecialAddress {
        Null,
        Broadcast,
        LocalHost,
        LocalHostIPv6,
        Any,
        AnyIPv6,
        AnyIPv4
    };

    QHostAddress(SpecialAddress address);
	QHostAddress(QString address);

private:
	QString Address;
};

