#pragma once
#include"cocos2d.h"
USING_NS_CC;

class helpLayer : public Layer
{
public:
	//初始化
	static Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(helpLayer);

	//返回按键的响应
	void callbackofreturn(Ref* pSender);
};

