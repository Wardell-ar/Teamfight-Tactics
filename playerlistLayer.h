

#pragma once

#include"cocos2d.h"
USING_NS_CC;

/*
  show all of the players (3)
  we need to save 3 position
  for each position,we put a photo(the player's head sculptrue)
  the one who stay higher has more blood volume left
  the head sculpture is a menuitem for looking others' chessboard

  func:
  change the position of the 3 head sculpture by the blood volume of the 3 player

*/

class playerlistLayer : public Layer
{


public:
	static Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(playerlistLayer);
};

