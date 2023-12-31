#pragma once
#include "cocos2d.h"
#include "Online.h"
#include "createRoomScene.h"
#include "joinRoomScene.h"
#include "networkScene.h"
USING_NS_CC;

class startLayer : public Layer
{
public:
	//初始化
	static Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(startLayer);

	//按键响应
	void callbackofbutton1(Ref* pSender);   //开始游戏
	void callbackofbutton2(Ref* pSender);   //创建房间
	void callbackofbutton3(Ref* pSender);   //加入房间
	void callbackofbutton4(Ref* pSender);   //帮助
	void callbackofbutton5(Ref* pSender);   //退出
};

