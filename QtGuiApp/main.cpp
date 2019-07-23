#include "QtGuiApp.h"
#include <QtWidgets/QApplication>

#include "Convert.h"



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiApp w;
	w.show();
	return a.exec();
	

}
