#pragma once
#include"myPosition.h"

class chessboardSeat
{
public:
	myPosition* seats;
	int Size;
	chessboardSeat(int IsMine);
	~chessboardSeat();
};
