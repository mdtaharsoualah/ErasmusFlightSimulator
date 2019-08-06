#include "P3d.h"


void P3d::start() {
	P3dConnect();
	P3dConfig();
	QTimer *timer = new QTimer(this);


	usbcan = new UsbCan;

	QObject::connect(timer, SIGNAL(timeout()), usbcan, SLOT(tmout()));
	connect(this, SIGNAL(P3dSetAltitude(double)), usbcan, SLOT(SetAlt(double)));
	connect(this, SIGNAL(P3dSetCap(double)), usbcan, SLOT(SetCap(double)));
	connect(this, SIGNAL(P3dSetVSpeed(double)), usbcan, SLOT(SetVSpeed(double)));
	connect(this, SIGNAL(P3dSetHSpeed(double)), usbcan, SLOT(SetHSpeed(double)));

	connect(usbcan, SIGNAL(CanThrottle(double)), this, SLOT(P3dSetThrottle(double)));
	connect(usbcan, SIGNAL(CanYoke(double,double)), this, SLOT(P3dSetYoke(double,double)));
	usbcan->start();

	
	connect(timer, SIGNAL(timeout()), this, SLOT(P3dStart()),Qt::QueuedConnection);

	timer->start(10);
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
	//usbcan.UsbCanConnect();

}

void CALLBACK P3d::DispatchCallback(SIMCONNECT_RECV *pData, DWORD cbData, void *pContext)
{
	P3d *pThis = reinterpret_cast<P3d*>(pContext);
	pThis->Process(pData, cbData);
	//pThis->usbcan.CanSend(0x05,1);
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
			//usbcan.SetAlt(*pS);
			emit P3dSetAltitude(*pS);
			emit P3dPrintAltitude(*pS);
			break;
		}
		case DEF_CAP:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dSetCap((*pS)*((double)180 / (double)3.14));
			emit P3dPrintCap((*pS)*((double)180 / (double)3.14));
			break;
		}
		case DEF_VSpeed:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dSetVSpeed((*pS)*60.0);
			emit P3dPrintVSpeed((*pS)*60.0);
			break;
		}
		case DEF_HSpeed:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			//usbcan.SetHSpeed(*pS);
			emit P3dPrintHSpeed(*pS);
			emit P3dSetHSpeed(*pS);
			break;
		}
		case DEF_THROTTLE:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dPrintThrottle(*pS);
			emit P3dSetThrottle(*pS);
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



void P3d::SetThrottle(double value)
{
	HRESULT hr;
	throttlePercent = value;
	hr = SimConnect_SetDataOnSimObject(hSimConnect, DEF_THROTTLE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(value), &value);
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

void P3d::AddElement(int id) {
	Queue.QueueAddElement(id);
}

void P3d::DelateElement(int id) {
	Queue.QueueDelateElement(id);
}

void P3d::P3dSetThrottle(double value)
{
	HRESULT hr;
	throttlePercent = value;
	hr = SimConnect_SetDataOnSimObject(hSimConnect, DEF_THROTTLE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(value), &value);
}

void P3d::P3dSetYoke(double valueX, double valueY)
{
	HRESULT hr;
	hr = SimConnect_SetDataOnSimObject(hSimConnect, DEF_XYOKE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(valueX), &valueX);
	hr = SimConnect_SetDataOnSimObject(hSimConnect, DEF_YYOKE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(valueY), &valueY);
}
