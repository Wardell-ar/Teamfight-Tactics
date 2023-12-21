#include "chessboardSeat.h"
#include"myPosition.h"
chessboardSeat::chessboardSeat() {
	Size = 13;
	seats = new myPosition[13];
	
	/* the position of my chessboard seat */
	seats[0] = myPosition(488, 555);
	seats[1] = myPosition(624, 555);
	seats[2] = myPosition(793, 555);
	seats[3] = myPosition(992, 565);
	seats[4] = myPosition(1199, 555);
	seats[5] = myPosition(506, 455);
	seats[6] = myPosition(647, 455);
	seats[7] = myPosition(837, 455);
	seats[8] = myPosition(1050, 455);
	seats[9] = myPosition(563, 355);
	seats[10] = myPosition(732, 355);
	seats[11] = myPosition(910, 355);
	seats[12] = myPosition(1100, 355);
}

chessboardSeat::~chessboardSeat() {
	delete[]seats;
}