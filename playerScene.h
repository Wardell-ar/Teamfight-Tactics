<<<<<<< Updated upstream
=======
#pragma once
>>>>>>> Stashed changes
#include"cocos2d.h"
#include"preparationSeat.h"
#include"chessboardSeat.h"
#include"playerlistLayer.h"
#include"storeLayer.h"
#include"playerroleLayer.h"
#include"hero1.h"

USING_NS_CC;

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
/*
  put a chessboard photo(include preparation seat and chessboard)
  set a menu (option) to exit the game or stop the music

  func:
  the move of the player role
*/
class playerScene : public Scene
{
	
	

public:
<<<<<<< Updated upstream
	chessboardSeat seat1;   //棋盘位置
	preparationSeat seat2;   //备战席位置

=======

	storeLayer* store;
>>>>>>> Stashed changes

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(playerScene);
<<<<<<< Updated upstream
=======
	
>>>>>>> Stashed changes
};

