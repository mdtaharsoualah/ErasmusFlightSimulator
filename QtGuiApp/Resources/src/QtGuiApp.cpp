#include "QtGuiApp.h"

QtGuiApp::QtGuiApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	emit AddElement(DEF_THROTTLE);
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(printData()));
	timer->start(5);
}

void QtGuiApp::printData()
{

	//p3d.P3dRequestData();
	
	//p3d.P3dStart();
	
	//p3d.P3dPrintData('2');
	//ui.textEditFirst->setText(QString::fromStdString(emit PrintData(DEF_ALTITUDE)));
	//ui.textEditSecond->setText(QString::fromStdString(emit PrintData(DEF_THROTTLE)));
}

void QtGuiApp::on_CheckAltitude_stateChanged(int arg1)
{
	if (arg1) {
		emit AddElement(DEF_ALTITUDE);
		ui.LcdAltitude->setEnabled(true);
	}
	else {
		emit DelateElement(DEF_ALTITUDE);
		ui.LcdAltitude->setEnabled(false);
	}
}


void QtGuiApp::on_CheckCap_stateChanged(int arg1)
{
	if (arg1) {
		emit AddElement(DEF_CAP);
		ui.LcdCap->setEnabled(true);
	}
	else {
		emit DelateElement(DEF_CAP);
		ui.LcdCap->setEnabled(false);
	}
}

void QtGuiApp::on_CheckVSpeed_stateChanged(int arg1)
{
	if (arg1) {
		emit AddElement(DEF_VSpeed);
		ui.LcdVSpeed->setEnabled(true);
	}
	else {
		emit DelateElement(DEF_VSpeed);
		ui.LcdVSpeed->setEnabled(false);
	}
}

void QtGuiApp::on_CheckHSpeed_stateChanged(int arg1)
{
	if (arg1) {
		emit AddElement(DEF_HSpeed);
		ui.LcdHSpeed->setEnabled(true);
	}
	else {
		emit DelateElement(DEF_HSpeed);
		ui.LcdHSpeed->setEnabled(false);
	}
}



void QtGuiApp::on_CheckPitchDeg_stateChanged(int arg1) {
	if (arg1) {
		emit AddElement(DEF_PitchDeg);
		ui.LcdPitchDeg->setEnabled(true);
	}
	else {
		emit DelateElement(DEF_PitchDeg);
		ui.LcdPitchDeg->setEnabled(false);
	}
}
void QtGuiApp::on_CheckPitchRate_stateChanged(int arg1) {
	if (arg1) {
		emit AddElement(DEF_PitchRate);
		ui.LcdPitchRate->setEnabled(true);
	}
	else {
		emit DelateElement(DEF_PitchRate);
		ui.LcdPitchRate->setEnabled(false);
	}
}
void QtGuiApp::on_CheckRollDeg_stateChanged(int arg1) {
	if (arg1) {
		emit AddElement(DEF_RollDeg);
		ui.LcdRollDeg->setEnabled(true);
	}
	else {
		emit DelateElement(DEF_RollDeg);
		ui.LcdRollDeg->setEnabled(false);
	}
}
void QtGuiApp::on_CheckRollRate_stateChanged(int arg1) {
	if (arg1) {
		emit AddElement(DEF_RollRate);
		ui.LcdRollRate->setEnabled(true);
	}
	else {
		emit DelateElement(DEF_RollRate);
		ui.LcdRollRate->setEnabled(false);
	}
}


void QtGuiApp::PrintAltitude(double value) {
	emit SetAltitude(value);
	ui.LcdAltitude->display(value);
}

void QtGuiApp::PrintCap(double value) {
	ui.LcdCap->display(value);
}

void QtGuiApp::PrintHSpeed(double value) {
	ui.LcdHSpeed->display(value);
}

void QtGuiApp::PrintVSpeed(double value) {
	ui.LcdVSpeed->display(value);
}

void QtGuiApp::PrintPitchDeg(double value) {
	ui.LcdPitchDeg->display(value);
}

void QtGuiApp::PrintPitchRate(double value) {
	ui.LcdPitchRate->display(value);
}

void QtGuiApp::PrintRollDeg(double value) {
	ui.LcdRollDeg->display(value);
}

void QtGuiApp::PrintRollRate(double value) {
	ui.LcdRollRate->display(value);
}