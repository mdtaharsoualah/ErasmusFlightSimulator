




#include "QtGuiApp.h"
#include <QtWidgets/QApplication>

//#include "Convert.h"


void PUBLIC AppConnectControlCallbackEx(DWORD	dwEvent_p, DWORD dwParam_p, void * pArg_p);
void PUBLIC AppEventCallbackEx(tUcanHandle UcanHandle_p, DWORD dwEvent_p, BYTE bChannel_p, void *pArg_p);

tUcanHandle UcanHandle_g;
tCanMsgStruct aCanRxMsg_g[100];
HANDLE ahWaitHandles_g[8];
// CONNECT, RECV, STATUS
tUcanInitCanParam InitParam_g;

tCanMsgStruct CanMsg;

bool UsbCanConnect = FALSE, UsbCanReceive = FALSE;


int main(int argc, char *argv[])
{
	/*QApplication a(argc, argv);
	QtGuiApp w;
	w.show();
	return a.exec();*/

	UCANRET bRet;
	BYTE    bChannel;
	DWORD   dwRxCount;

	//bRet = UcanInitHardwareEx(&UcanHandle, USBCAN_ANY_MODULE, NULL, NULL);

	bRet = UcanInitHwConnectControlEx(AppConnectControlCallbackEx, NULL);

	memset(&InitParam_g, 0, sizeof(InitParam_g));
	InitParam_g.m_dwSize = sizeof(InitParam_g);
	InitParam_g.m_bMode = kUcanModeNormal;
	InitParam_g.m_bBTR0 = HIBYTE(USBCAN_BAUDEX_G4_250kBit);
	InitParam_g.m_bBTR1 = LOBYTE(USBCAN_BAUDEX_G4_250kBit);
	InitParam_g.m_bOCR = USBCAN_OCR_DEFAULT;
	InitParam_g.m_dwAMR = USBCAN_AMR_ALL;
	InitParam_g.m_dwACR = USBCAN_ACR_ALL;
	InitParam_g.m_dwBaudrate = USBCAN_BAUDEX_G4_250kBit;

	while (1) {
		if (UsbCanConnect) {
			bRet = UcanInitHardwareEx(&UcanHandle_g, USBCAN_ANY_MODULE, AppEventCallbackEx, NULL);
			bRet = UcanInitCanEx2(UcanHandle_g, USBCAN_CHANNEL_CH0, &InitParam_g);
		}
		if (UsbCanReceive) {
			UsbCanReceive = FALSE;
			do {
				bRet = UcanReadCanMsg(UcanHandle_g, &CanMsg);
				if (CanMsg.m_dwID == 0x55) {
					printf("%x", CanMsg.m_bData[0]);
				}
			} while (USBCAN_CHECK_VALID_RXCANMSG(bRet));
		}
	}





}

void PUBLIC AppConnectControlCallbackEx(DWORD	dwEvent_p, DWORD dwParam_p, void * pArg_p)
{
	UCANRET bRet;
	// which event did occur?
	switch (dwEvent_p)
	{
	case USBCAN_EVENT_CONNECT:
		printf("Connected");
		UsbCanConnect = TRUE;
		break;
	case USBCAN_EVENT_DISCONNECT:
		printf("Disconnected");

		break;
	}
}

void PUBLIC AppEventCallbackEx(tUcanHandle UcanHandle_p, DWORD dwEvent_p, BYTE bChannel_p, void *pArg_p) {
	switch (dwEvent_p) {
	case USBCAN_EVENT_RECEIVE:
		UsbCanReceive = TRUE;
		break;
	case USBCAN_EVENT_STATUS:
		printf("Status");
		break;
	}
}
