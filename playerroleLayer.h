<<<<<<< Updated upstream
=======
#pragma once
>>>>>>> Stashed changes
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

	static Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(playerroleLayer);
};

