#include "mbed\mbed.h"
#include "mbed/Serial.h"
#include "mbed/CAN.h"

#include "function.h"

Serial matlab(p9, p10);    // 
Serial pc(USBTX, USBRX); //
CAN can(p30, p29);      // 
CANMessage RxMsg;

bool RxMatlab = false;
char var[8];
float throttle, yokeY;

void fonctionRead() {
	for (int i = 0; i < 8; i++)
	{
		var[i] = matlab.getc();
	}
	memcpy(&throttle, var, 4);
	memcpy(&yokeY, var + 4, 4);
	RxMatlab = true;
}

int main()
{
	matlab.baud(115200);
	matlab.attach(&fonctionRead);

	can.frequency(250000);     // Fréquence du CAN

	can.attach(&fonction);    // Executer la fonction chaque 1à ms

	while (1)
	{
		if (RxMatlab) {

		}
		if (RxCan) {

		}
	}
}