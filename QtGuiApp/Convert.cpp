#include "Convert.h"


void UsbCan::UsbCanConnect() {
	// initialize USB-CANmodul
	bRet = UcanInitHardware(&UcanHandle, USBCAN_ANY_MODULE, NULL);

	bRet = UcanInitCan(UcanHandle,
		HIBYTE(USBCAN_BAUD_250kBit), // BTR0 for 1MBit/s 
		LOBYTE(USBCAN_BAUD_250kBit), // BTR1 for 1MBit/s
		0xFFFFFFFF, // AMR for all messages received
		0x00000000); // ACR for all messages received
	ResetData();
}

void UsbCan::UsbCanDisconnect() {

}

void UsbCan::CanSend1(BYTE Id) {
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