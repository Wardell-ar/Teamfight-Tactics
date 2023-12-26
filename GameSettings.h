#pragma once
#include "cocos2d.h"
USING_NS_CC;


class GameSettings :public Layer
{
public:
	static Layer* createLayer();
	CREATE_FUNC(GameSettings);
	virtual bool init();

	

	void onSoundControl(Ref* pSender);//“Ù¿÷ø™πÿ
};
