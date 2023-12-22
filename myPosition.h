/*
Position is used to save a coordinate of the scene and the
state(whether there is a sprite or not) of the saved coordinate
*/


#pragma once
#include"cocos2d.h"
USING_NS_CC;
class myPosition
{
public:
	int x;
	int y;
	int state;
	myPosition();
	myPosition(int xx, int yy);
	void Setsprite();
	void Removesprite();
	bool IsEmpty();
	void operator=(myPosition p);
};

