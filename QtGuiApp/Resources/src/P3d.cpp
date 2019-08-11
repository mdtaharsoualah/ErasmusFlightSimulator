#include "P3d.h"


void P3d::start() {
	P3dConnect();
	P3dConfig();
	QTimer *timer = new QTimer(this);


	usbcan = new UsbCan; // ATTENTION IL FAUT LIBERER LA MÉMOIRE.
  

	QObject::connect(timer, SIGNAL(timeout()), usbcan, SLOT(tmout()));
	connect(this, SIGNAL(P3dSetAltitude(double)), usbcan, SLOT(SetAlt(double)));
	connect(this, SIGNAL(P3dSetCap(double)), usbcan, SLOT(SetCap(double)));
	connect(this, SIGNAL(P3dSetVSpeed(double)), usbcan, SLOT(SetVSpeed(double)));
	connect(this, SIGNAL(P3dSetHSpeed(double)), usbcan, SLOT(SetHSpeed(double)));

	connect(this, SIGNAL(P3dSetPitchDeg(double)), usbcan, SLOT(SetPitchDeg(double)));
	connect(this, SIGNAL(P3dSetPitchRate(double)), usbcan, SLOT(SetPitchRate(double)));
	connect(this, SIGNAL(P3dSetRollDeg(double)), usbcan, SLOT(SetRollDeg(double)));
	connect(this, SIGNAL(P3dSetRollRate(double)), usbcan, SLOT(SetRollRate(double)));

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
// Pas besoin de garder le tableau statique. 
std::array<GeneralDefine, DEFINE_ENUM_COUNT>  MyDef = 
                                 {{DEF_ALTITUDE,"Plane Altitude","feet"}, 
                                 {DEF_CAP,"PLANE HEADING DEGREES MAGNETIC","Radians"}, 
                                 {DEF_VSpeed,"VERTICAL SPEED", "Feet per second"}, 
                                 {DEF_HSpeed,"AIRSPEED TRUE","Knots"}, 
                                 {DEF_THROTTLE,"GENERAL ENG THROTTLE LEVER POSITION:1","percent"}, 
                                 {DEF_XYOKE, "YOKE X POSITION", "Position"},
                                 {DEF_YYOKE, "YOKE Y POSITION", "Position"}, 
                                 {DEF_CAP,"PLANE HEADING DEGREES MAGNETIC","Radians"}, 
                                 {DEF_VSpeed,"VERTICAL SPEED", "Feet per second"}, 
                                 {DEF_HSpeed,"AIRSPEED TRUE","Knots"}, 
                                 {DEF_THROTTLE,"GENERAL ENG THROTTLE LEVER POSITION:1","percent"}, 
                                 {DEF_XYOKE, "YOKE X POSITION", "Position"}, 
                                 {DEF_PitchDeg, "PLANE PITCH DEGREES", "Radians"}, 
                                 {DEF_PitchRate, "ROTATION VELOCITY BODY X", "Radians per second"}, 
                                 {DEF_RollDeg, "PLANE BANK DEGREES", "Radians"}, 
                                 {DEF_RollRate, "ROTATION VELOCITY BODY Z", "Radians per second"} };
   for (auto& def : MyDef)
      {
      hr = SimConnect_AddToDataDefinition(hSimConnect, def.Id, def.Name.c_str(), def.Type.c_str());
      }

	//hr = SimConnect_AddToDataDefinition(hSimConnect, 25,"GENERAL ENG THROTTLE LEVER POSITION:1", "percent");
	
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
	case SIMCONNECT_RECV_ID_EXCEPTION: 
	{
		SIMCONNECT_RECV_EXCEPTION *pObjData = (SIMCONNECT_RECV_EXCEPTION*)pData;
		qDebug("\nReceived:%d", pObjData->dwException);
		break;
	}
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
			//emit P3dPrintThrottle(*pS);
			//emit P3dSetThrottle(*pS);
			break;
		}
		case DEF_PitchDeg:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dSetPitchDeg(*pS);
			emit P3dPrintPitchDeg(*pS);
			break;
		}
		case DEF_PitchRate:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dSetPitchRate(*pS);
			emit P3dPrintPitchRate(*pS);
			break;
		}
		case DEF_RollDeg:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dSetRollDeg(*pS);
			emit P3dPrintRollDeg(*pS);
			break;
		}
		case DEF_RollRate:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dSetRollRate(*pS);
			emit P3dPrintRollRate(*pS);
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
	int throttlePercen = value;
	hr = SimConnect_SetDataOnSimObject(hSimConnect, DEF_THROTTLE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(throttlePercen), &throttlePercen);
}




void P3d::P3dRequestData() {


   m_ObjectTypeMutex.lock();
   auto ObjectTypes = m_ObjectTypesToProcess; // Copy the vector (ça reste quand mpeme performant, car ce ne sont que des ID (Int). 
                                              // ça sera plus lent si on doit à chaque fois interrompre le thread. 
   m_ObjectTypeMutex.unlock(); // NE SURTOUT PAS L'OUBLIER. SINON L'AUTRE THREAD RESTE BLOQUÉ.

   // 
   // MUTEX to request data
   // std::vector<int> ObjectTypes = m_ObjectTypesToProcess;
   // Librer le mutex
   // 
   for (auto ObjectTypeId : ObjectTypes)
      {
      SimConnect_RequestDataOnSimObjectType(hSimConnect, ObjectTypeId, ObjectTypeId, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
      }
	/*Queue.QueueReset();
	GeneralDefine* tmp = NULL;
	do {
		Queue.QueueNext(&tmp);
		if (tmp != NULL)
			SimConnect_RequestDataOnSimObjectType(hSimConnect, tmp->Id, tmp->Id, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
	} while (tmp != NULL);*/
}

void P3d::AddElement(int id) {

   // MUTEX pour blocker l'acces à m_ObjectTypesToProcess

   std::lock_guard<std::mutex> guard(m_ObjectTypeMutex);
   m_ObjectTypesToProcess.emplace_back(id);
//	Queue.QueueAddElement(id);
}

void P3d::DelateElement(int id) {
   // MUTEX pour blocker l'acces. 

      std::lock_guard<std::mutex> guard(m_ObjectTypeMutex);

      // Chercher le ID à supprimer. 

       m_ObjectTypesToProcess.erase(std::remove(m_ObjectTypesToProcess.begin(), m_ObjectTypesToProcess.end(), id),
                                    m_ObjectTypesToProcess.end());

   //	Queue.QueueDelateElement(id);
}

void P3d::P3dSetThrottle(double value)
{
	HRESULT hr;
	double throttlePercen = value;
	hr = SimConnect_SetDataOnSimObject(hSimConnect, 25, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(throttlePercen), &throttlePercen);
}

void P3d::P3dSetYoke(double valueX, double valueY)
{
	HRESULT hr;
	hr = SimConnect_SetDataOnSimObject(hSimConnect, DEF_XYOKE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(valueX), &valueX);
	hr = SimConnect_SetDataOnSimObject(hSimConnect, DEF_YYOKE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(valueY), &valueY);
}
