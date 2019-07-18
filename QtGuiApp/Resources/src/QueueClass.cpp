// pch.cpp : fichier source correspondant à l'en-tête précompilé ; nécessaire au bon déroulement de la compilation

#include "QueueClass.h"

// Vous pouvez en général ignorer ce fichier, mais gardez-le si vous utilisez des en-têtes précompilés.

bool QueueClass::QueueAddElement(int Id)
{
	GeneralDefine* tmpData = NULL;
	QueueSearch(&tmpData, Id);
	if (tmpData == NULL)
		return false;
	QueueDefine* tmpQueue = new QueueDefine;
	tmpQueue->Var = tmpData;
	tmpQueue->Next = Top;
	Top = tmpQueue;
	size++;
	return true;
}

bool QueueClass::QueueDelateElement(int Id)
{
	QueueReset();
	if (Top->Var->Id == Id) {
		Select = Top;
		Top = Top->Next;
		delete Select;
		size--;
		return true;
	}
	QueueDefine* tmp = Top->Next;
	while (tmp != NULL) {
		if (tmp->Var->Id == Id) {
			Select->Next = tmp->Next;
			delete tmp;
			size--;
			break;
		}
		Select = Select->Next;
		tmp = tmp->Next;
	}
	return true;
}

void QueueClass::QueuePrintData()
{
	QueueReset();
	std::cout << "\nPrint Data :";
	while (Select!=NULL) {
		GeneralDefine* Data = NULL;
		QueueNext(&Data);
		std::cout << "\nId " << Data->Id << "; Name " << Data->Name << "; Type " << Data->Type << ";";
	}
}
bool QueueClass::IsQueueEmpty()
{
	if (size == 0)
		return true;
	return false;
}
std::string QueueClass::QueuePrintData(int Id)
{
	QueueReset();
	while (Select != NULL) {
		GeneralDefine* Data = NULL;
		QueueNext(&Data);
		if (Data->Id == Id) {
			std::stringstream sstm;
			sstm << "Id" << Data->Id << "; Name " << Data->Name << "; Type " << Data->Type << ";";
			return sstm.str();
		}	
	}
	if (Select == NULL)
		return "Nothing";

}

void QueueClass::QueueNext(GeneralDefine** Structure)
{
	if (Select == NULL) {
		*Structure = NULL;
		return;
	}
	*Structure = Select->Var;
	Select = Select->Next;
}

bool QueueClass::QueueReset()
{
	Select = Top;
	return true;
}


/*
	Search in 
*/
void QueueClass::QueueSearch(GeneralDefine ** Structure, int Id)
{
	*Structure = NULL;
	QueueDefine * tmp = Top;
	for (int i = 0; i < (sizeof(MyDef)/sizeof(GeneralDefine)); i++) {
		if (Id==MyDef[i].Id) {
			*Structure = MyDef+i;
		}
	}
}