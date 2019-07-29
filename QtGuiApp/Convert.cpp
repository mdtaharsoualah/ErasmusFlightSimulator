#include "Convert.h"

void UsbCan::setreceiveBool1(bool value) {
	receiveBool1 = value;
}

void UsbCan::start() {
	setreceiveBool1(false);
	UsbCanConnect();
	while (1) {
		if (receiveBool1) {
			setreceiveBool1(false);
		}
	}
}

void UsbCan::UsbCanConnect() {
	// initialize USB-CANmodul
	//bRet = UcanInitHardware(&UcanHandle, USBCAN_ANY_MODULE, NULL);


	memset(&InitParam, 0, sizeof(InitParam));
	InitParam.m_dwSize = sizeof(InitParam);
	InitParam.m_bMode = kUcanModeNormal;
	InitParam.m_bBTR0 = HIBYTE(USBCAN_BAUDEX_G4_125kBit);
	InitParam.m_bBTR1 = LOBYTE(USBCAN_BAUDEX_G4_125kBit);
	InitParam.m_bOCR = USBCAN_OCR_DEFAULT;
	InitParam.m_dwAMR = USBCAN_AMR_ALL;
	InitParam.m_dwACR = USBCAN_ACR_ALL;
	InitParam.m_dwBaudrate = USBCAN_BAUDEX_G4_125kBit;


	bRet = UcanInitHardwareEx(&UcanHandle, USBCAN_ANY_MODULE, AppEventCallbackEx, this);

	bRet = UcanInitCanEx2(UcanHandle, USBCAN_CHANNEL_CH0, &InitParam);


	ResetData();
}

void PUBLIC UsbCan::AppEventCallbackEx(tUcanHandle UcanHandle_p, DWORD dwEvent_p, BYTE bChannel_p, void* pArg_p){
	
	UsbCan *pThis = reinterpret_cast<UsbCan*>(pArg_p);

	switch (dwEvent_p)
	{

	case USBCAN_EVENT_RECEIVE: // CAN message received
		pThis->setreceiveBool1(TRUE);
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
