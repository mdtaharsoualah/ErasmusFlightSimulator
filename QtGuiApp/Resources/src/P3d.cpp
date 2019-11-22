#include "P3d.h"




void P3d::P3dConnect()
{
	if (SUCCEEDED(SimConnect_Open(&m_hSimConnect, "TEST", NULL, 0, 0, 0)))
	{
		emit P3dConnected(true);
		P3dConfig();
	}
	else {
		emit P3dConnected(false);
	}
}

void P3d::P3dDisconnect()
{
	timer->stop();
	disconnect(timer, SIGNAL(timeout()), this, SLOT(P3dBoucle()));
	if (SUCCEEDED(SimConnect_Close(m_hSimConnect)))
	{
		emit P3dDisconnected(true);
	}
	else {
		emit P3dDisconnected(false);
	}
}

void P3d::P3dConfig()
{
	HRESULT hr;


	std::array<GeneralDefine, DEFINE_ENUM_COUNT>  MyDef =	
											{ { {DEF_ALTITUDE,"Plane Altitude","feet"},
												{DEF_CAP,"PLANE HEADING DEGREES MAGNETIC","Radians"},
												{DEF_VSpeed,"VERTICAL SPEED", "Feet per second"},
												{DEF_HSpeed,"AIRSPEED TRUE","Knots"},
												{DEF_THROTTLE,"GENERAL ENG THROTTLE LEVER POSITION:1","percent"},
												{DEF_XYOKE, "YOKE X POSITION", "Position"},
												{DEF_YYOKE, "YOKE Y POSITION", "Position"},
												{DEF_PitchDeg, "PLANE PITCH DEGREES", "Radians"},
												{DEF_PitchRate, "ROTATION VELOCITY BODY X", "Radians per second"},
												{DEF_RollDeg, "PLANE BANK DEGREES", "Radians"},
												{DEF_RollRate, "ROTATION VELOCITY BODY Z", "Radians per second"} } };

	for (auto& def : MyDef)
	{
		hr = SimConnect_AddToDataDefinition(m_hSimConnect, def.Id, def.Name.c_str(), def.Type.c_str());
	}

	//hr = SimConnect_SubscribeToSystemEvent(m_hSimConnect, EVENT_SIM_START, "6Hz");

	



	
	connect(timer, SIGNAL(timeout()), this, SLOT(P3dBoucle()), Qt::QueuedConnection);
	timer->start(75);

}

void P3d::P3dstart() {

	

	
}


void P3d::P3dBoucle()
{
	P3dRequestData();
	SimConnect_CallDispatch(this->m_hSimConnect, &P3d::DispatchCallback, this);
}

void CALLBACK P3d::DispatchCallback(SIMCONNECT_RECV *pData, DWORD cbData, void *pContext)
{
	P3d *pThis = reinterpret_cast<P3d*>(pContext);
	pThis->Process(pData, cbData);
}


void P3d::Process(SIMCONNECT_RECV * pData, DWORD cbData)
{
	HRESULT hr;

	switch (pData->dwID)
	{
	case SIMCONNECT_RECV_ID_EXCEPTION: 
	{
		SIMCONNECT_RECV_EXCEPTION *pObjData = (SIMCONNECT_RECV_EXCEPTION*)pData;
		qDebug("\nerror:%d", pObjData->dwException);
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
			emit P3dAltitude(*pS);
			break;
		}
		case DEF_CAP:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dCap((double) ((double)(*pS) * (double)57.29577951308232087679815181));
			break;
		}
		case DEF_VSpeed:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dVSpeed((*pS)*60.0);
			break;
		}
		case DEF_HSpeed:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dHSpeed(*pS);
			break;
		}
		case DEF_THROTTLE:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			//emit P3dThrottle(*pS);
			break;
		}
		case DEF_PitchDeg:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dPitchDeg(*pS);
			break;
		}
		case DEF_PitchRate:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dPitchRate(*pS);
			break;
		}
		case DEF_RollDeg:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dRollDeg(*pS);
			break;
		}
		case DEF_RollRate:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double *pS = (double*)&pObjData->dwData;
			emit P3dRollRate(*pS);
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
			//hr = SimConnect_RequestDataOnSimObjectType(m_hSimConnect, DEF_ALTITUDE, DEF_ALTITUDE, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
			//hr = SimConnect_RequestDataOnSimObjectType(m_hSimConnect, DEF_THROTTLE, DEF_THROTTLE, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
			
			P3dRequestData();
		}

		default:
			break;
		}
		break;
	}

	case SIMCONNECT_RECV_ID_QUIT:
	{
		break;
	}

	default:
		qDebug("\nReceived:%d", pData->dwID);
		break;
	}
}


void P3d::P3dRequestData() {


	m_IdDefinitionMutex.lock();
	auto ObjectTypes = m_IdDefinition; // Copy the vector (ça reste quand mpeme performant, car ce ne sont que des ID (Int). 
											   // ça sera plus lent si on doit à chaque fois interrompre le thread. 
	m_IdDefinitionMutex.unlock(); // NE SURTOUT PAS L'OUBLIER. SINON L'AUTRE THREAD RESTE BLOQUÉ.

	// 
	// MUTEX to request data
	// std::vector<int> ObjectTypes = m_IdDefinition;
	// Librer le mutex
	// 
	for (auto ObjectTypeId : ObjectTypes)
	{
		SimConnect_RequestDataOnSimObjectType(m_hSimConnect, ObjectTypeId, ObjectTypeId, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
	}
	/*Queue.QueueReset();
	GeneralDefine* tmp = NULL;
	do {
		Queue.QueueNext(&tmp);
		if (tmp != NULL)
			SimConnect_RequestDataOnSimObjectType(m_hSimConnect, tmp->Id, tmp->Id, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
	} while (tmp != NULL);*/
}

void P3d::AddElement(int id) {

	// MUTEX pour blocker l'acces à m_IdDefinition

	std::lock_guard<std::mutex> guard(m_IdDefinitionMutex);
	m_IdDefinition.emplace_back(id);
	//	Queue.QueueAddElement(id);
}

void P3d::DeleteElement(int id) {
	// MUTEX pour blocker l'acces. 

	std::lock_guard<std::mutex> guard(m_IdDefinitionMutex);

	// Chercher le ID à supprimer. 

	m_IdDefinition.erase(std::remove(m_IdDefinition.begin(), m_IdDefinition.end(), id),
		m_IdDefinition.end());

	//	Queue.QueueDeleteElement(id);
}

void P3d::P3dSetThrottle(double value)
{
	HRESULT hr;
	m_throttle = value;
	hr = SimConnect_SetDataOnSimObject(m_hSimConnect, DEF_THROTTLE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(m_throttle), &m_throttle);
}

void P3d::P3dSetYoke(double valueX, double valueY)
{
	HRESULT hr;
	m_yokeX = valueX;
	m_yokeY = valueY;
	hr = SimConnect_SetDataOnSimObject(m_hSimConnect, DEF_XYOKE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(m_yokeX), &m_yokeX);
	hr = SimConnect_SetDataOnSimObject(m_hSimConnect, DEF_YYOKE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(m_yokeY), &m_yokeY);
}
