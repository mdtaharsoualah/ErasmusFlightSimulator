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

	QThread* thread = new QThread;
	P3d* p3d = new P3d();

	p3d->moveToThread(thread);
	QObject::connect(thread, SIGNAL(started()), p3d, SLOT(start()));
	QObject::connect(p3d, SIGNAL(P3dPrintAltitude(double)), w, SLOT(PrintAltitude(double)));
	QObject::connect(p3d, SIGNAL(P3dPrintCap(double)), w, SLOT(PrintCap(double)));
	QObject::connect(p3d, SIGNAL(P3dPrintVSpeed(double)), w, SLOT(PrintVSpeed(double)));
	QObject::connect(p3d, SIGNAL(P3dPrintHSpeed(double)), w, SLOT(PrintHSpeed(double)));
	QObject::connect(w, SIGNAL(AddElement(int)), p3d, SLOT(AddElement(int)));
	QObject::connect(w, SIGNAL(DelElement(int)), p3d, SLOT(DelElement(int)));
	thread->start();

	return a.exec();

}
