#include "QtGuiApp.h"

QtGuiApp::QtGuiApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(printData()));
	timer->start(5);
}

void QtGuiApp::printData()
{

	//p3d.P3dRequestData();
	
	//p3d.P3dStart();
	
	//p3d.P3dPrintData('2');
	//ui.textEditFirst->setText(QString::fromStdString(p3d.Queue.QueuePrintData(DEF_ALTITUDE)));
	//ui.textEditSecond->setText(QString::fromStdString(p3d.Queue.QueuePrintData(DEF_THROTTLE)));
}

void QtGuiApp::on_CheckAltitude_stateChanged(int arg1)
{
	if (arg1) {
		//p3d.Queue.QueueAddElement(DEF_ALTITUDE);
		ui.LcdAltitude->setEnabled(true);
	}
	else {
		//p3d.Queue.QueueDelateElement(DEF_ALTITUDE);
		ui.LcdAltitude->setEnabled(false);
	}
}


void QtGuiApp::on_CheckCap_stateChanged(int arg1)
{
	if (arg1) {
		p3d.Queue.QueueAddElement(DEF_CAP);
		ui.LcdCap->setEnabled(true);
	}
	else {
		p3d.Queue.QueueDelateElement(DEF_CAP);
		ui.LcdCap->setEnabled(false);
	}
}

void QtGuiApp::on_CheckVSpeed_stateChanged(int arg1)
{
	if (arg1) {
		p3d.Queue.QueueAddElement(DEF_VSpeed);
		ui.LcdVSpeed->setEnabled(true);
	}
	else {
		p3d.Queue.QueueDelateElement(DEF_VSpeed);
		ui.LcdVSpeed->setEnabled(false);
	}
}

void QtGuiApp::on_CheckHSpeed_stateChanged(int arg1)
{
	if (arg1) {
		p3d.Queue.QueueAddElement(DEF_HSpeed);
		ui.LcdHSpeed->setEnabled(true);
	}
	else {
		p3d.Queue.QueueDelateElement(DEF_HSpeed);
		ui.LcdHSpeed->setEnabled(false);
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

void QtGuiApp::on_MbedReadButton_clicked() {
}


void QtGuiApp::PrintAltitude(double value) {
	ui.LcdAltitude->display(value);
}

void QtGuiApp::PrintCap(double value) {
	ui.LcdCap->display(value);
}

void QtGuiApp::PrintVSpeed(double value) {
	ui.LcdVSpeed->display(value);
}

void QtGuiApp::PrintHSpeed(double value) {
	ui.LcdHSpeed->display(value);
}

void QtGuiApp::PrintThrottle(double value) {
	ui.LcdThrottle->display(value);
}