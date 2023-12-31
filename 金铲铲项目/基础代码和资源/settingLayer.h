#pragma once
#include"cocos2d.h"
USING_NS_CC;
class settingLayer : public Layer
{
public:
	static settingLayer* createLayer();
	virtual bool init();
	CREATE_FUNC(settingLayer);

	void musicControl(Ref* sender);
	void callbackofreturn(Ref* sender);
	void exitCallBack(Ref* sender);
};

