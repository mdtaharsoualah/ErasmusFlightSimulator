#pragma once
#include <iostream>
#include <iomanip>
#include <WS2tcpip.h>
#include <qobject.h>

#define MAX_LENGTH_BUF 256

class MatlabRcv : public QObject {
	Q_OBJECT

public:
	void MatlabDisconnectRcv();
	void MatlabLisningRcv();
signals:
	void MatlabYoke(double, double);
	void MatlabThrottle(double);
	void MatlabDisconnect();

public slots:
	void MatlabRcvStart();
	void MatlabRcvFun();
private:
	int Port;
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	SOCKET listening;
	sockaddr_in hint;
	sockaddr_in client;
	int clientSize = sizeof(client);
	SOCKET clientSocket2;
	int size = sizeof(double);
	double YokeX = 0, YokeY = 0, Throttle = 0;
};