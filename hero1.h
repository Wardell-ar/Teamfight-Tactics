

#pragma once

#include"cocos2d.h"
#include"myPosition.h"
USING_NS_CC;

#define HEROTAG 222

class hero1 : public Layer
{
public:
	myPosition curp;
	myPosition enemyp;

	int HP;
	int hit;  //…À∫¶


	

	static Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(hero1);

	

};

