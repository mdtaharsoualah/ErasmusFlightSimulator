#include "P3d.h"

bool P3d::MbedReadConnect(int COM, int BAUD)
{
	if (mbedRead.Open(COM, BAUD))
		return true;
	return false;
}

std::string P3d::MbedRead()
{
	if (!mbedRead.IsOpened())
		return false;
	std::stringstream ss;
	char buffer;
	while (mbedRead.ReadDataWaiting()) {
		mbedRead.ReadData(&buffer, 1);
		if (buffer == '|')
			break;
		ss << buffer;
	}
	return ss.str();
}

bool P3d::MbedWrite(int Id)
{
	if (!mbedRead.IsOpened())
		return false;
	std::stringstream ss;
	if (Queue.QueuePrintData(Id) != "Nothing") {

	}
	
}

bool P3d::MbedWriteConnect(int COM, int BAUD)
{
	if (mbedWrite.Open(COM, BAUD))
		return true;
	return false;
}

bool P3d::MbedReadAvailable()
{
	if (!mbedRead.IsOpened())
		return false;
	if (mbedRead.ReadDataWaiting())
			return true;
	return false;
}

bool P3d::P3dConnect()
{
	if (SUCCEEDED(SimConnect_Open(&hSimConnect, "TEST", NULL, 0, 0, 0)))
	{
		qDebug("\nConnected to Prepar3D!");
		return true;
	}
	else {
		qDebug("\nError Connection");
		return false;
	}
}

void P3d::P3dDisconnect()
{
	if (SUCCEEDED(SimConnect_Close(hSimConnect)))
	{
		qDebug("\nDisconnected from Prepar3D!");
	}
	else {
		qDebug("\nError Disconnection");
	}
}

void P3d::P3dStart()
{
		SimConnect_CallDispatch(this->hSimConnect, &P3d::DispatchCallback, this);
}

void P3d::P3dConfig()
{
	HRESULT hr;
	for (int i = 0; i < (sizeof(MyDef) / sizeof(GeneralDefine)); i++) {
		hr = SimConnect_AddToDataDefinition(hSimConnect, MyDef[i].Id, MyDef[i].Name.c_str(), MyDef[i].Type.c_str());
	}
	//hr = SimConnect_AddToDataDefinition(hSimConnect, DEF_THROTTLE, "GENERAL ENG THROTTLE LEVER POSITION:1", "percent");
	
	hr = SimConnect_SubscribeToSystemEvent(hSimConnect, EVENT_SIM_START, "6Hz");

}

void CALLBACK P3d::DispatchCallback(SIMCONNECT_RECV *pData, DWORD cbData, void *pContext)
{
	P3d *pThis = reinterpret_cast<P3d*>(pContext);
	pThis->Process(pData, cbData);
}

void P3d::P3dPrintData()
{

}


void P3d::Process(SIMCONNECT_RECV * pData, DWORD cbData)
{
	HRESULT hr;

	switch (pData->dwID)
	{
	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA_BYTYPE:
	{
		SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE *pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE*)pData;

		switch (pObjData->dwRequestID)
		{
		case DEF_ALTITUDE:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			P3dPrintAltitude(*pS);
			break;
		}
		case DEF_THROTTLE:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			P3dPrintThrottle(*pS);
			break;
		}

		default:
			break;
		}
		break;
	}

	case SIMCONNECT_RECV_ID_EVENT:
	{
		SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;

		switch (evt->uEventID)
		{

		case EVENT_SIM_START:
		{
			//hr = SimConnect_RequestDataOnSimObjectType(hSimConnect, DEF_ALTITUDE, DEF_ALTITUDE, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
			//hr = SimConnect_RequestDataOnSimObjectType(hSimConnect, DEF_THROTTLE, DEF_THROTTLE, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
			
			P3dRequestData();
		}

		default:
			break;
		}
		break;
	}

	case SIMCONNECT_RECV_ID_QUIT:
	{
		quit = 1;
		break;
	}

	default:
		qDebug("\nReceived:%d", pData->dwID);
		break;
	}
}


void P3d::P3dPrintAltitude(double value) {
	QtParametre.LcdAltitude->display(value);
}

void P3d::P3dPrintThrottle(double value) {
	if (throttlePercent != value)
		SetThrottle(throttlePercent);
	QtParametre.LcdThrottle->display(throttlePercent);
}




void P3d::SetThrottle(double value)
{
	HRESULT hr;
	throttlePercent = value;
	hr = SimConnect_SetDataOnSimObject(hSimConnect, DEF_THROTTLE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(throttlePercent), &throttlePercent);
}


void P3d::P3dConfig(QtParameter* qt) {
	QtParametre = *qt;
}


void P3d::P3dRequestData() {
	Queue.QueueReset();
	GeneralDefine* tmp = NULL;
	do {
		Queue.QueueNext(&tmp);
		if (tmp != NULL)
			SimConnect_RequestDataOnSimObjectType(hSimConnect, tmp->Id, tmp->Id, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
	} while (tmp != NULL);
}