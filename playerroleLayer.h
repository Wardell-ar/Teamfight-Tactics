#pragma once
#include"cocos2d.h"
USING_NS_CC;

/*
  we need to save the palyer role's current position
  set a simple photo to represent the player role

  func: 
  attack display
*/

#define ROLETAG 111

class playerroleLayer : public Layer
{
public:
	int camp = 1;  // 1代表我方  0代表敌方
	float max_blood = 10;
	float cur_blood = 10;
	ProgressTimer* healthBar;//血条类
	Vec2 cur_position;

	static playerroleLayer* createLayer(int c);
};

