#ifdef XSDK
#ifdef FREERTOS

#include <QUdpSocket.h>
#include <string.h>
#include "lwip/sockets.h"

int64_t QUdpSocket::writeDatagram(const char* data, int64_t len, const QHostAddress& host, uint16_t port) {


	int sock;
	int64_t out = -1;
	struct sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	err_t err;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("QUdpSocket: Error creating Socket\r\n");
		close(sock);
		return out;
	}

	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(host.Address.c_str());

	err = connect(sock, (struct sockaddr *)&addr, addrLen);
	if (err != ERR_OK) {
		close(sock);
		return out;
	}

	out = lwip_sendto(sock, data, len, 0, (struct sockaddr *)&addr, addrLen);
	close(sock);
	return out;

}

int64_t QUdpSocket::readDatagram(char* data, int64_t maxlen, const QHostAddress& host, uint16_t port) {

	int sock;
	int64_t out = -1;
	struct sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	err_t err;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("QUdpSocket: Error creating Socket\r\n");
		close(sock);
		return out;
	}

	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if(host.Address.size() > 0)
		addr.sin_addr.s_addr = inet_addr(host.Address.c_str());
	else
		addr.sin_addr.s_addr = INADDR_ANY;

	err = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	if (err != ERR_OK) {
		printf("QUdpSocket: Error on bind: %d\r\n", err);
		close(sock);
		return out;
	}

	out = lwip_recvfrom(sock, data, maxlen, 0, (struct sockaddr *)&addr, &addrLen);
	close(sock);
	return out;

}

#endif
#endif


