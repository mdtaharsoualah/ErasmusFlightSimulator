// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

#ifndef QueueClass_H
#define QueueClass_H

#include <string>
#include <iostream>
#include <sstream>

/*
	Structur of Data
*/
struct GeneralDefine
{
	int Id;
	std::string Name;
	std::string Type;
};

/*
	Enum Id of data
*/
enum DEFINE_ENUM
{
	DEF_ALTITUDE = 1,
	DEF_CAP = 2,
	DEF_VSpeed = 3,
	DEF_HSpeed = 4,
	DEF_THROTTLE = 50,
	DEF_XYOKE = 6,
	DEF_YYOKE = 7,
	DEF_PitchDeg = 8,
	DEF_PitchRate = 9,
	DEF_RollDeg = 10,
	DEF_RollRate = 11
};

/*
	Array Definition of all types of data
*/
static GeneralDefine MyDef[] = { {DEF_ALTITUDE,"Plane Altitude","feet"}, {DEF_CAP,"PLANE HEADING DEGREES MAGNETIC","Radians"}, {DEF_VSpeed,"VERTICAL SPEED", "Feet per second"}, {DEF_HSpeed,"AIRSPEED TRUE","Knots"}, {DEF_THROTTLE,"GENERAL ENG THROTTLE LEVER POSITION:1","percent"}, {DEF_XYOKE, "YOKE X POSITION", "Position"},{DEF_YYOKE, "YOKE Y POSITION", "Position"}, {DEF_CAP,"PLANE HEADING DEGREES MAGNETIC","Radians"}, {DEF_VSpeed,"VERTICAL SPEED", "Feet per second"}, {DEF_HSpeed,"AIRSPEED TRUE","Knots"}, {DEF_THROTTLE,"GENERAL ENG THROTTLE LEVER POSITION:1","percent"}, {DEF_XYOKE, "YOKE X POSITION", "Position"}, {DEF_PitchDeg, "PLANE PITCH DEGREES", "Radians"}, {DEF_PitchRate, "ROTATION VELOCITY BODY X", "Radians per second"}, {DEF_RollDeg, "PLANE BANK DEGREES", "Radians"}, {DEF_RollRate, "ROTATION VELOCITY BODY Z", "Radians per second"} };

/*
	Define of queue struct
*/
struct QueueDefine
{
	GeneralDefine* Var;
	QueueDefine* Next;
};

/*
	Define of class
*/
class QueueClass
{
public:
	bool QueueAddElement(int Id); //Add element in the front of the queue
	bool QueueDelateElement(int Id); //Delate element in the queue with Id
	void ElementSearch(GeneralDefine** Structure, int Id); //search in data types if the id exist and return data in structure
	void QueueSearch(GeneralDefine** Structure, int Id); //search in the queue if id exist and return data in structure
	void QueuePrintData(); //Print all the data of the queue
	bool IsQueueEmpty(); //Check if the queue is empty
	std::string QueuePrintData(int Id); //
	void QueueNext(GeneralDefine** Structure);
	bool QueueReset();
private:
	QueueDefine* Top = NULL;
	QueueDefine* Select = Top;
	int size = 0;
};


#endif //QueueClass_H
