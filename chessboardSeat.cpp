#include "chessboardSeat.h"
#include"myPosition.h"
chessboardSeat::chessboardSeat(int IsMine) {
	Size = 5;
	seats = new myPosition[5];
	
	/* the position of my chessboard seat */
	if(IsMine)
	{
		seats[0] = myPosition(709, 540);
		seats[1] = myPosition(954, 540);
		seats[2] = myPosition(609, 372);
		seats[3] = myPosition(874, 372);
		seats[4] = myPosition(1199, 372);
	}
	else {
		seats[0] = myPosition(726, 693);
		seats[1] = myPosition(995, 693);
		seats[2] = myPosition(539, 805);
		seats[3] = myPosition(826, 805);
		seats[4] = myPosition(1093, 805);
	}
}

chessboardSeat::~chessboardSeat() {
	delete[]seats;
}