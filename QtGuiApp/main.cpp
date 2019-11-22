#include "Matlab.h"
#pragma comment(lib, "Ws2_32.lib")
#include "QtGuiApp.h"
#include <QtWidgets/QApplication>
#include <qthread.h>
#include "Convert.h"
#include "P3d.h"



int main(int argc, char *argv[])
{
	qRegisterMetaType<SOCKET>("SOCKET");
	QApplication a(argc, argv);
	QtGuiApp* w = new QtGuiApp;
	w->show();

	QThread* ThreadP3d = new QThread;
	P3d* p3d = new P3d;
	p3d->moveToThread(ThreadP3d);

	QObject::connect(ThreadP3d, SIGNAL(started()), p3d, SLOT(P3dstart()));


	QObject::connect(p3d, SIGNAL(P3dAltitude(double)), w, SLOT(PrintAltitude(double)));
	QObject::connect(p3d, SIGNAL(P3dCap(double)), w, SLOT(PrintCap(double)));
	QObject::connect(p3d, SIGNAL(P3dVSpeed(double)), w, SLOT(PrintVSpeed(double)));
	QObject::connect(p3d, SIGNAL(P3dHSpeed(double)), w, SLOT(PrintHSpeed(double)));

	QObject::connect(p3d, SIGNAL(P3dPitchDeg(double)), w, SLOT(PrintPitchDeg(double)));
	QObject::connect(p3d, SIGNAL(P3dPitchRate(double)), w, SLOT(PrintPitchRate(double)));
	QObject::connect(p3d, SIGNAL(P3dRollDeg(double)), w, SLOT(PrintRollDeg(double)));
	QObject::connect(p3d, SIGNAL(P3dRollRate(double)), w, SLOT(PrintRollRate(double)));

	QObject::connect(w, SIGNAL(AddElement(int)), p3d, SLOT(AddElement(int)));
	QObject::connect(w, SIGNAL(DeleteElement(int)), p3d, SLOT(DeleteElement(int)));

	QObject::connect(w, SIGNAL(P3dConnect()), p3d, SLOT(P3dConnect()));
	QObject::connect(w, SIGNAL(P3dDisconnect()), p3d, SLOT(P3dDisconnect()));
	QObject::connect(p3d, SIGNAL(P3dConnected(bool)), w, SLOT(P3dConnected(bool)));
	QObject::connect(p3d, SIGNAL(P3dDisconnected(bool)), w, SLOT(P3dDisconnected(bool)));


	



	QThread* ThreadUsbCan = new QThread;
	UsbCan* usbcan = new UsbCan();
	usbcan->moveToThread(ThreadUsbCan);

	QObject::connect(ThreadUsbCan, SIGNAL(started()), usbcan, SLOT(usbCanStart()));

	QObject::connect(p3d, SIGNAL(P3dAltitude(double)), usbcan, SLOT(SetAlt(double)));
	QObject::connect(p3d, SIGNAL(P3dCap(double)), usbcan, SLOT(SetCap(double)));
	QObject::connect(p3d, SIGNAL(P3dVSpeed(double)), usbcan, SLOT(SetVSpeed(double)));
	QObject::connect(p3d, SIGNAL(P3dHSpeed(double)), usbcan, SLOT(SetHSpeed(double)));

	QObject::connect(p3d, SIGNAL(P3dPitchDeg(double)), usbcan, SLOT(SetPitchDeg(double)));
	QObject::connect(p3d, SIGNAL(P3dPitchRate(double)), usbcan, SLOT(SetPitchRate(double)));
	QObject::connect(p3d, SIGNAL(P3dRollDeg(double)), usbcan, SLOT(SetRollDeg(double)));
	QObject::connect(p3d, SIGNAL(P3dRollRate(double)), usbcan, SLOT(SetRollRate(double)));

	QObject::connect(usbcan, SIGNAL(CanThrottle(double)), p3d, SLOT(P3dSetThrottle(double)));
	QObject::connect(usbcan, SIGNAL(CanYoke(double, double)), p3d, SLOT(P3dSetYoke(double, double)));

	QObject::connect(w, SIGNAL(CanConnect()), usbcan, SLOT(CanConnect()));
	QObject::connect(w, SIGNAL(CanDisconnect()), usbcan, SLOT(CanDisconnect()));
	QObject::connect(usbcan, SIGNAL(CanConnected(bool)), w, SLOT(CanConnected(bool)));
	QObject::connect(usbcan, SIGNAL(CanDisconnected(bool)), w, SLOT(CanDisconnected(bool)));




	QThread* ThreadMatlab = new QThread;
	Matlab* matlab = new Matlab();
	matlab->moveToThread(ThreadMatlab);

	QObject::connect(ThreadMatlab, SIGNAL(started()), matlab, SLOT(MatlabConnect()));

	QObject::connect(p3d, SIGNAL(P3dAltitude(double)), matlab, SLOT(SetAlt(double)));
	QObject::connect(p3d, SIGNAL(P3dCap(double)), matlab, SLOT(SetCap(double)));
	QObject::connect(p3d, SIGNAL(P3dVSpeed(double)), matlab, SLOT(SetVSpeed(double)));
	QObject::connect(p3d, SIGNAL(P3dHSpeed(double)), matlab, SLOT(SetHSpeed(double)));

	/*QObject::connect(p3d, SIGNAL(P3dPitchDeg(double)), matlab, SLOT(SetPitchDeg(double)));
	QObject::connect(p3d, SIGNAL(P3dPitchRate(double)), matlab, SLOT(SetPitchRate(double)));
	QObject::connect(p3d, SIGNAL(P3dRollDeg(double)), matlab, SLOT(SetRollDeg(double)));
	QObject::connect(p3d, SIGNAL(P3dRollRate(double)), matlab, SLOT(SetRollRate(double)));*/




	QThread* ThreadMatlabRCV = new QThread;
	MatlabRcv* matlabRcv = new MatlabRcv();
	matlabRcv->moveToThread(ThreadMatlabRCV);
	QObject::connect(ThreadMatlabRCV, SIGNAL(started()), matlabRcv, SLOT(MatlabRcvStart()));
	QObject::connect(matlabRcv, SIGNAL(MatlabThrottle(double)), p3d, SLOT(P3dSetThrottle(double)));
	QObject::connect(matlabRcv, SIGNAL(MatlabYoke(double,double)), matlab, SLOT(GetYoke(double,double)));


	ThreadP3d->start();

	ThreadUsbCan->start();

	ThreadMatlab->start();

	ThreadMatlabRCV->start();

	return a.exec();

}