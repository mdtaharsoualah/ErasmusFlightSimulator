// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

#ifndef QueueClass_H
#define QueueClass_H

#include <string>
#include <iostream>
#include <sstream>
#include <array>

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
	DEF_NULL = -1,
	DEF_ALTITUDE,
	DEF_CAP,
	DEF_VSpeed,
	DEF_HSpeed,
	DEF_THROTTLE,
	DEF_XYOKE,
	DEF_YYOKE,
	DEF_PitchDeg,
	DEF_PitchRate,
	DEF_RollDeg,
	DEF_RollRate,
	MAX
};

constexpr auto DEFINE_ENUM_COUNT = static_cast<int>(DEFINE_ENUM::MAX);

/*
	Array Definition of all types of data
*/


/*
	Define of queue struct
*/
struct QueueDefine
{
	GeneralDefine* Var;
	QueueDefine* Next;
};



#endif //QueueClass_H