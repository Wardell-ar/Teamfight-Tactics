#pragma once
#include "cocos2d.h"
USING_NS_CC;


class GameSettings :public Scene
{
public:
	static Scene* createScene();
	CREATE_FUNC(GameSettings);
	virtual bool init();

	void onSoundControl(Ref* pSender);//“Ù¿÷ø™πÿ
};
