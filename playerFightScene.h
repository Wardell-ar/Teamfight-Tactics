#pragma once
#include"cocos2d.h"
#include"preparationSeat.h"
#include"chessboardSeat.h"
#include"playerlistLayer.h"
#include"storeLayer.h"
#include"playerroleLayer.h"
#include"hero1.h"
#include"GameSettings.h"

USING_NS_CC;

class playerfightScene :public Scene {

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(playerfightScene);

	void callbackof_set(Ref* pSender);  //…Ë÷√
	void fightEnd();//’Ω∂∑Ω· ¯

};



