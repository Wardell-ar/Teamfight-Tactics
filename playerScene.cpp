#include "playerScene.h"
#include"heroSprite.h"
USING_NS_CC;

#define STORETAG   462
chessboardSeat seat1;   //棋盘位置
preparationSeat seat2;   //备战席位置
extern std::vector<Hero*> allMyHeroes;//我方所有英雄
extern std::vector<Hero*> allEnemyHeroes;//敌方所有英雄
extern int fight;

Scene* playerScene::createScene() {
	return playerScene::create();
}

bool playerScene::init() {

	if (!Scene::create()) {
		return 0;
	}

	//背景设置
	auto background = Sprite::create("playerSceneBackground.png");
	this->addChild(background, 0);
	background->setPosition(955, 540);

	//英雄放置位置测试
	/*
	auto hero = hero1::createLayer();
	this->addChild(hero, 1, HEROTAG);
	hero->setPosition(Vec2(seat2.seats[8].x+70, seat2.seats[8].y+50));
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [hero, this](Touch* t, Event* e)->bool {
		Vec2 herosize = Vec2(442 * hero->getScale(), 375 * hero->getScale());
		Vec2 heroposition = hero->getPosition();
		Vec2 myclick = this->convertTouchToNodeSpace(t);
		if (myclick.x > heroposition.x - herosize.x / 9 && myclick.x<heroposition.x + herosize.x / 9 && myclick.y>heroposition.y - herosize.y / 9 && myclick.y < heroposition.y + herosize.y / 9) {
			log("yes");
		}
		else {
			log("no");
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
	*/


	
	auto hero1 = Hero::createHero(1, Vec2(700, 400), 1);
	this->addChild(hero1, 1);
	hero1->enterBattle();

	auto hero2 = Hero::createHero(1, Vec2(700, 800), 2);
	this->addChild(hero2, 1);
	hero2->enterBattle();
	Hero::attack();
	/*
	hero1->attack(hero2);
	hero2->attack(hero1);
	*/


	//英雄售卖——通过鼠标点击右键来实现
	auto sellheroListener = EventListenerMouse::create();
	sellheroListener->onMouseDown = [this](EventMouse* event)-> bool {
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			Vec2 myclick = Vec2(event->getCursorX(), event->getCursorY());
			//在战斗，则只能卖备战席上的英雄
			if (fight) {
				for (Hero* hero : allMyHeroes) {
					if (!hero->isInBoard() && hero->Getexist()) {  //不在战斗席上
						Vec2 herosize = Vec2(442 * hero->getScale(), 375 * hero->getScale());
						Vec2 heroposition = hero->getPosition();
						if (myclick.x > heroposition.x - herosize.x / 9 && myclick.x<heroposition.x + herosize.x / 9 && myclick.y>heroposition.y - herosize.y / 9 && myclick.y < heroposition.y + herosize.y / 9) {
							//商店加钱，要显示刷新
							store->gold += (store->herocost[hero->GetheroType()]) * pow(3, (hero->getLevel()) - 1);
							store->updateUI();

							//英雄消失
							hero->Setexist(0);  //使该英雄无效
							hero->setVisible(false);
							seat2.seats[hero->GetIndex()].Removesprite();
							return true;
						}
					}
				}
			}
			else {  //非战斗环节，可以点击所有英雄
				for (Hero* hero : allMyHeroes) {
					if (hero->Getexist()) {  //不在战斗席上
						Vec2 herosize = Vec2(442 * hero->getScale(), 375 * hero->getScale());
						Vec2 heroposition = hero->getPosition();
						if (myclick.x > heroposition.x - herosize.x / 9 && myclick.x<heroposition.x + herosize.x / 9 && myclick.y>heroposition.y - herosize.y / 9 && myclick.y < heroposition.y + herosize.y / 9) {
							//商店加钱，要显示刷新
							store->gold += (store->herocost[hero->GetheroType()]) * pow(3, (hero->getLevel()) - 1);
							store->updateUI();

							//英雄消失
							hero->Setexist(0);  //使该英雄无效
							hero->setVisible(false);
							if (hero->isInBoard()) {
								seat1.seats[hero->GetIndex()].Removesprite();
							}
							else {
								seat2.seats[hero->GetIndex()].Removesprite();
							}
							return true;
						}
					}
				}
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(sellheroListener, this);


	//英雄的移动换位
	// ....


	//挂件设置
	auto playerrole = playerroleLayer::createLayer();  //小小英雄
	this->addChild(playerrole, 2, ROLETAG);
	auto playerlist = playerlistLayer::createLayer();  //英雄列表
	this->addChild(playerlist, 2);
	store = storeLayer::createLayer();   //商店，是Scene中的私有成员
	this->addChild(store, 3);


	//小小英雄的移动
	auto roleMoveListener = EventListenerTouchOneByOne::create();
	roleMoveListener->setSwallowTouches(true);    //事件吞没
	roleMoveListener->onTouchBegan = [background, this](Touch* t, Event* e)-> bool {
		Vec2 pos = background->convertTouchToNodeSpace(t);
		if (pos.x > 323 && pos.x < 1247 && pos.y>327 && pos.y < 839)  //小小英雄移动范围
		{
			auto role = this->getChildByTag(ROLETAG)->getChildByTag(ROLETAG);
			role->stopAllActions();
			role->runAction(MoveTo::create(0.3, Vec2(pos.x + 55.25, pos.y + 46.875)));
			return true;   //事件不再传递给其他监听器
		}
		else {
			return false;  //事件可以继续传递
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(roleMoveListener, this);
	
	
	return 1;
}