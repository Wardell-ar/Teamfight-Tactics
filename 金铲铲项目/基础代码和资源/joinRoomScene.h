#pragma once
#include "cocos2d.h"
#include <iostream>
#include "Online.h"

using namespace cocos2d;
using namespace cocos2d::network;

USING_NS_CC;

class joinRoomScene :public Scene
{
public:
    static Scene* createScene();
    virtual bool init();

    CREATE_FUNC(joinRoomScene);

    //返回按键的响应
    void callbackofreturn(Ref* pSender);

};