#include "QtGuiApp.h"
#include <QtWidgets/QApplication>
#include <qthread.h>

#include "Convert.h"
#include "P3d.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiApp* w=new QtGuiApp;
	w->show();

	QThread* ThreadP3d = new QThread;
	P3d* p3d = new P3d;

	QThread* ThreadCan = new QThread;
	UsbCan* usbcan = new UsbCan;

	p3d->moveToThread(ThreadP3d);
	QObject::connect(ThreadP3d, SIGNAL(started()), p3d, SLOT(start()));
	QObject::connect(ThreadCan, SIGNAL(started()), usbcan, SLOT(start()));
	QObject::connect(p3d, SIGNAL(P3dPrintAltitude(double)), w, SLOT(PrintAltitude(double)));
	QObject::connect(p3d, SIGNAL(P3dPrintCap(double)), w, SLOT(PrintCap(double)));
	QObject::connect(p3d, SIGNAL(P3dPrintVSpeed(double)), w, SLOT(PrintVSpeed(double)));
	QObject::connect(p3d, SIGNAL(P3dPrintHSpeed(double)), w, SLOT(PrintHSpeed(double)));
	QObject::connect(w, SIGNAL(AddElement(int)), p3d, SLOT(AddElement(int)));
	QObject::connect(w, SIGNAL(DelateElement(int)), p3d, SLOT(DelateElement(int)));
	ThreadP3d->start();

	return a.exec();

}