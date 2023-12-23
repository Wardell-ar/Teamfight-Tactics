#pragma once
#include"cocos2d.h"
#include"preparationSeat.h"
#include"chessboardSeat.h"
#include"playerlistLayer.h"
#include"storeLayer.h"
#include"playerroleLayer.h"
#include"hero1.h"
#include"GameSettings.h"
#include"playerFightScene.h"


USING_NS_CC;

/*
  put a chessboard photo(include preparation seat and chessboard)
  set a menu (option) to exit the game or stop the music

  func:
  the move of the player role
*/
class playerScene : public Scene
{



public:
	chessboardSeat seat1;   //棋盘位置
	preparationSeat seat2;   //备战席位置

	storeLayer* store;


	int timeLeft;

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(playerScene);

	void callbackof_set(Ref* pSender);  //设置
	void updateTimer(float dt);

};

