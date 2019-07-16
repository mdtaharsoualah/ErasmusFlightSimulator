#include "QtGuiApp.h"

QtGuiApp::QtGuiApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QtParameter qt;

	qt.TextEdit = ui.TextEdit;

	qt.CheckAltitude = ui.CheckAltitude;
	qt.LcdAltitude = ui.LcdAltitude;

	qt.CheckThrottle = ui.CheckThrottle;
	qt.LcdThrottle = ui.LcdThrottle;
	qt.ControlThrottle = ui.ControlThrottle;

	p3d.P3dConfig(&qt);
	p3d.P3dConnect();
	p3d.P3dConfig();
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(printData()));
	timer->start(150);
}

void QtGuiApp::printData()
{
	p3d.P3dStart();
	//p3d.P3dPrintData('2');
	//ui.textEditFirst->setText(QString::fromStdString(p3d.Queue.QueuePrintData(DEF_ALTITUDE)));
	//ui.textEditSecond->setText(QString::fromStdString(p3d.Queue.QueuePrintData(DEF_THROTTLE)));
}

void QtGuiApp::on_CheckAltitude_stateChanged(int arg1)
{
	if (arg1) {
		p3d.Queue.QueueAddElement(DEF_ALTITUDE);
		ui.LcdAltitude->setEnabled(true);
	}
	else {
		p3d.Queue.QueueDelateElement(DEF_ALTITUDE);
		ui.LcdAltitude->setEnabled(false);
	}
}

void QtGuiApp::on_CheckThrottle_stateChanged(int arg1)
{
	if (arg1) {
		p3d.Queue.QueueAddElement(DEF_THROTTLE);
		ui.LcdThrottle->setEnabled(true);
	}
	else {
		p3d.Queue.QueueDelateElement(DEF_THROTTLE);
		ui.LcdThrottle->setEnabled(false);
	}
}


void QtGuiApp::on_ControlThrottle_valueChanged(int value)
{
	p3d.SetThrottle((double)value);
}

