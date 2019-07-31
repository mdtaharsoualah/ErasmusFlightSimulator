#include "Convert.h"

void UsbCan::run() {
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeout10()), Qt::QueuedConnection);
	timer->start(5);
	exec();
}

void UsbCan::setreceiveBool(bool value) {
	receiveBool = value;
}

void UsbCan::start() {
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeout10()),Qt::QueuedConnection);
	timer->start(5);
	//UsbCanConnect();
	timeout150 = false;
	while (1) {
		if (receiveBool) {
			setreceiveBool(false);
		}
		if (timeout150) {
			timeout150 = false;
			CanSend(0x55, 1);
		}
	}
	
	
}


void UsbCan::timeout10() {
	qDebug("hello");
		timeout150 = true;
}

UsbCan::UsbCan(QObject *parent) : QThread(parent){
	qDebug("%d",QThread::currentThreadId());
	start();
}

void UsbCan::UsbCanConnect() {
	
	// initialize USB-CANmodul
	//bRet = UcanInitHardware(&UcanHandle, USBCAN_ANY_MODULE, NULL);


	setreceiveBool(false);

	memset(&InitParam, 0, sizeof(InitParam));
	InitParam.m_dwSize = sizeof(InitParam);
	InitParam.m_bMode = kUcanModeNormal;
	InitParam.m_bBTR0 = HIBYTE(USBCAN_BAUDEX_250kBit);
	InitParam.m_bBTR1 = LOBYTE(USBCAN_BAUDEX_250kBit);
	InitParam.m_bOCR = USBCAN_OCR_DEFAULT;
	InitParam.m_dwAMR = USBCAN_AMR_ALL;
	InitParam.m_dwACR = USBCAN_ACR_ALL;
	InitParam.m_dwBaudrate = USBCAN_BAUDEX_250kBit;

	ResetData();

	bRet = UcanInitHwConnectControlEx(AppConnectControlCallbackEx, NULL);

	if (bRet == USBCAN_SUCCESSFUL)
	{
		bRet = UcanInitHardwareEx(&UcanHandle, USBCAN_ANY_MODULE,
			AppEventCallbackEx, this);

		bRet = UcanInitCanEx2(UcanHandle, USBCAN_CHANNEL_CH0,
			&InitParam);
	}
}

void PUBLIC UsbCan::AppConnectControlCallbackEx(DWORD dwEvent_p, DWORD dwParam_p, void* pArg_p)
{
	switch (dwEvent_p)
	{
	case USBCAN_EVENT_CONNECT:
		qDebug("connect!!");
		break;
	case USBCAN_EVENT_DISCONNECT:
		qDebug("disconnect!!");
		break;
	}
}


void PUBLIC UsbCan::AppEventCallbackEx(tUcanHandle UcanHandle_p, DWORD dwEvent_p, BYTE bChannel_p, void* pArg_p){
	
	UsbCan *pThis = reinterpret_cast<UsbCan*>(pArg_p);

	switch (dwEvent_p)
	{

	case USBCAN_EVENT_RECEIVE: // CAN message received
		pThis->setreceiveBool(true);
		break;

	case USBCAN_EVENT_STATUS: // changes error status
	// signal that the CAN status can be read SetEvent(ahWaitHandles_g[STATUS]);
		break;

	}

}

void UsbCan::UsbCanDisconnect() {

}

void UsbCan::CanSend(BYTE Id, int type) {
	tCanMsgStruct TxCanMsg;
	TxCanMsg.m_dwID = Id;
	TxCanMsg.m_bFF = 0;
	TxCanMsg.m_bDLC = 8;
	BYTE TmpData[8] = { Tram1.altitude[0],Tram1.altitude[1], Tram1.cap[0], Tram1.cap[1], Tram1.VSpeed[0], Tram1.VSpeed[1], Tram1.HSpeed[0], Tram1.HSpeed[1] };
	memcpy(TxCanMsg.m_bData,TmpData, 8);
	UcanWriteCanMsg(UcanHandle, &TxCanMsg);
}


void UsbCan::SetAlt(double altitude) {
	unsigned int alt = (unsigned int)(altitude + ALTSHIFT);
	memcpy(Tram1.altitude, &alt, sizeof(int));
}

void UsbCan::SetCap(double cap)
{
	fixed_point_t tmp = (fixed_point_t) round(cap * (1 << FIWED_POINT_FRACTIONAL_BITS_CAP));
	memcpy(Tram1.cap, &tmp, sizeof(fixed_point_t));
}

void UsbCan::SetVSpeed(double VSpeed) {
	double tmpVal = VSpeed + VSPEEDSHIFT;
	fixed_point_t tmp = (fixed_point_t)round(tmpVal * (1 << FIWED_POINT_FRACTIONAL_BITS_SPEED));
	memcpy(Tram1.VSpeed, &tmp, sizeof(fixed_point_t));
}

void UsbCan::SetHSpeed(double HSpeed) {
	fixed_point_t tmp = (fixed_point_t)round(HSpeed * (1 << FIWED_POINT_FRACTIONAL_BITS_SPEED));
	memcpy(Tram1.HSpeed, &tmp, sizeof(fixed_point_t));
}

void UsbCan::CanSend1(BYTE Id, double altitude, double cap, double vspeed, double hspeed)
{
	SetAlt(altitude);
	SetCap(cap);
	SetVSpeed(vspeed);
	SetHSpeed(hspeed);
	CanSend(Id,1);
}

void UsbCan::ResetData()
{
	for (int i = 0; i < 2; i++)
	{
		Tram1.altitude[i] = 0x0;
		Tram1.cap[i] = 0x00;
		Tram1.VSpeed[i] = 0x0;
		Tram1.HSpeed[i] = 0x0;
	}
}

void UsbCan::receive1(int Id, DataTram1 Data)
{

}
