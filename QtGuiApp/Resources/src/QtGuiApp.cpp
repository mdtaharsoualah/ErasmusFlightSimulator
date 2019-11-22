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

/*void QtGuiApp::printData()
{

	//p3d.P3dRequestData();
	
	//p3d.P3dStart();
	
	//p3d.P3dPrintData('2');
	//ui.textEditFirst->setText(QString::fromStdString(emit PrintData(DEF_ALTITUDE)));
	//ui.textEditSecond->setText(QString::fromStdString(emit PrintData(DEF_THROTTLE)));
}*/

void QtGuiApp::on_P3dConnectButton_clicked() {
	if (P3dConnectStat) {
		emit P3dDisconnect();
	}
	else {
		emit P3dConnect();
	}
}

void QtGuiApp::on_CanConnectButton_clicked() {
	if (CanConnectStat) {
		emit CanDisconnect();
	}
	else {
		emit CanConnect();
	}
}

void QtGuiApp::P3dConnected(bool arg) {
	if (arg) {
		P3dConnectStat = true;
		ui.P3dConnectButton->setText("P3d Disconnect");
	}
	else {
		ui.TextEdit->setText("Error P3d Connection!!");
	}
}
void QtGuiApp::P3dDisconnected(bool arg) {
	if (arg) {
		P3dConnectStat = false;
		ui.P3dConnectButton->setText("P3d Connect");
	}
	else {
		ui.TextEdit->setText("Error P3d Disconnection!!");
	}
}

void QtGuiApp::CanConnected(bool arg) {
	if (arg) {
		CanConnectStat = true;
		ui.CanConnectButton->setText("Usb-Can Disconnect");
	}
	else {
		ui.TextEdit->setText("Error Usb-Can Connection!!");
	}
}
void QtGuiApp::CanDisconnected(bool arg) {
	if (arg) {
		CanConnectStat = false;
		ui.CanConnectButton->setText("Usb-Can Connect");
	}
	else {
		ui.TextEdit->setText("Error Usb-Can Disconnection!!");
	}
}

void QtGuiApp::on_Tram1Check_stateChanged(int arg)
{
	if (arg) {
		emit AddElement(DEF_ALTITUDE);
		ui.LcdAltitude->setEnabled(true);
		emit AddElement(DEF_CAP);
		ui.LcdCap->setEnabled(true);
		emit AddElement(DEF_VSpeed);
		ui.LcdVSpeed->setEnabled(true);
		emit AddElement(DEF_HSpeed);
		ui.LcdHSpeed->setEnabled(true);
	}
	else {
		emit DeleteElement(DEF_ALTITUDE);
		ui.LcdAltitude->setEnabled(false);
		emit DeleteElement(DEF_CAP);
		ui.LcdCap->setEnabled(false);
		emit DeleteElement(DEF_VSpeed);
		ui.LcdVSpeed->setEnabled(false);
		emit DeleteElement(DEF_HSpeed);
		ui.LcdHSpeed->setEnabled(false);
	}
}


void QtGuiApp::on_Tram2Check_stateChanged(int arg)
{
	if (arg) {
		emit AddElement(DEF_PitchDeg);
		ui.LcdPitchDeg->setEnabled(true);
		emit AddElement(DEF_PitchRate);
		ui.LcdPitchRate->setEnabled(true);
		emit AddElement(DEF_RollDeg);
		ui.LcdRollDeg->setEnabled(true);
		emit AddElement(DEF_RollRate);
		ui.LcdRollRate->setEnabled(true);
	}
	else {
		emit DeleteElement(DEF_PitchDeg);
		ui.LcdPitchDeg->setEnabled(false);
		emit DeleteElement(DEF_PitchRate);
		ui.LcdPitchRate->setEnabled(false);
		emit DeleteElement(DEF_RollDeg);
		ui.LcdRollDeg->setEnabled(false);
		emit DeleteElement(DEF_RollRate);
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