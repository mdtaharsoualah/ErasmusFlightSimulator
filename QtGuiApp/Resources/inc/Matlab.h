#pragma once
#include <iostream>
#include <iomanip>
#include <WS2tcpip.h>
#include <qobject.h>
#include <qtimer.h>
#include <qdebug.h>

#include "MatlabRcv.h"
#include <qthread.h>

struct Tram1
{
	double Altitude;
	double Cap;
	double VSpeed;
	double HSpeed;
};

struct Tram2
{
	double Altitude;
	double Cap;
	double VSpeed;
	double HSpeed;
};

class Matlab : public QObject {
	Q_OBJECT
public:
	void MatlabDisconnect();
	void MatlabLisning();

signals:
	void MatlabThrottle(double);
	void MatlabYoke(double, double);
	void matlabRcvStart(SOCKET);

public slots:
	void GetYoke(double, double);
	void GetThrottle(double);

	void MatlabConnect();

	void MatlabSend();
	
	void SetAlt(double altitude);

	void SetCap(double cap);

	void SetVSpeed(double VSpeed);

	void SetHSpeed(double HSpeed);

	/*void SetPitchDeg(double value);
	void SetPitchRate(double value);
	void SetRollDeg(double value);
	void SetRollRate(double value);*/
	
private:
	int Port;
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	SOCKET listening;
	sockaddr_in hint;
	sockaddr_in client;
	int clientSize = sizeof(client);
	SOCKET clientSocket;
	Tram1 tram1;
	QTimer *timer = new QTimer(this);

	

};