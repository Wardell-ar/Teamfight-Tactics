#include "preparationSeat.h"
#include"myPosition.h"
preparationSeat::preparationSeat() {
	Size = 9;
	seats = new myPosition[9];

	/* the position of my preparation seat */
	seats[0] = myPosition(380, 244);
	seats[1] = myPosition(493, 249);
	seats[2] = myPosition(608, 243);
	seats[3] = myPosition(721, 244);
	seats[4] = myPosition(831, 243);
	seats[5] = myPosition(952, 240);
	seats[6] = myPosition(1069, 243);
	seats[7] = myPosition(1170, 234);
	seats[8] = myPosition(1275, 230);
}

preparationSeat::~preparationSeat() {
	delete[]seats;
}