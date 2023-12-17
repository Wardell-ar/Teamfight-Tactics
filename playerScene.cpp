#include "playerScene.h"
USING_NS_CC;

Scene* playerScene::createScene() {
	return playerScene::create();
}

bool playerScene::init() {

	if (!Scene::create()) {
		return 0;
	}

	//background setting
	auto background = Sprite::create("playerSceneBackground.png");
	this->addChild(background, 0);
	background->setPosition(955, 540);

	

	

	



	//英雄放置位置测试
	auto hero = hero1::createLayer();
	this->addChild(hero, 1, HEROTAG);
	hero->setPosition(Vec2(seat2.seats[8].x+70, seat2.seats[8].y+50));

	/*
	Vec2 herosize = Vec2(442 * hero->getScale(), 375 * hero->getScale());
	Vec2 heroposition = hero->getPosition();
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [hero, this](Touch* t, Event* e)->bool {
		Vec2 myclick = this->convertTouchToNodeSpace(t);
		if(myclick.x>)
	};
	*/






	auto playerrole = playerroleLayer::createLayer();
	this->addChild(playerrole, 2, ROLETAG);

	auto playerlist = playerlistLayer::createLayer();
	this->addChild(playerlist, 2);

	auto store = storeLayer::createLayer();
	this->addChild(store, 3);


	//小小英雄的移动
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [background, this](Touch* t, Event* e)-> bool {
		Vec2 pos = background->convertTouchToNodeSpace(t);
		if (pos.x > 323 && pos.x < 1247 && pos.y>327 && pos.y < 839)
		{
			auto role = this->getChildByTag(ROLETAG)->getChildByTag(ROLETAG);
			role->stopAllActions();
			role->runAction(MoveTo::create(0.3, Vec2(pos.x + 55.25, pos.y + 46.875)));
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);









	return 1;
}
