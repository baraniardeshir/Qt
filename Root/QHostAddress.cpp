#include <QHostAddress.h>

QHostAddress::QHostAddress(SpecialAddress address) {
	switch(address) {
	case Any: {
		Address = "";
		break;
	}

	}
}

QHostAddress::QHostAddress(QString address) :
Address(address)
{}
