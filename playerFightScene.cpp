#include "ui/CocosGUI.h"
#include "playerScene.h"
#include"heroSprite.h"
#include"playerFightScene.h"

using namespace ui;

USING_NS_CC;
/*
#define STORETAG   462
chessboardSeat seat1;   //棋盘位置
preparationSeat seat2;   //备战席位置
extern std::vector<Hero*> allMyHeroes;//我方所有英雄
extern std::vector<Hero*> allEnemyHeroes;//敌方所有英雄
extern int fight;
*/
Scene* playerfightScene::createScene() {
	return playerfightScene::create();
}

bool playerfightScene::init() {

	if (!Scene::create()) {
		return 0;
	}

	//background setting
	auto background = Sprite::create("playerSceneBackground.png");
	this->addChild(background, 0);
	background->setPosition(955, 540);

	auto playerrole = playerroleLayer::createLayer();  //小小英雄
	this->addChild(playerrole, 2, ROLETAG);


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


	//设置
	auto set1 = Sprite::create("SetButton2.png");
	auto set2 = Sprite::create("SetButton1.png");
	auto _set = MenuItemSprite::create(set1, set2,
		CC_CALLBACK_1(playerfightScene::callbackof_set, this));
	auto SET = Menu::create(_set, NULL);
	SET->setPosition(1795, 990);
	this->addChild(SET, 40);

}

void playerfightScene::callbackof_set(Ref* pSender)
{
	auto gamesettings = GameSettings::createLayer(); //设置
	this->addChild(gamesettings, 100);

	auto closeLayerButton = Button::create("back1.png", "back2.png");
	closeLayerButton->setPosition(Vec2(1150, 750));
	this->addChild(closeLayerButton, 101);
	closeLayerButton->addClickEventListener([=](Ref* sender) {
		// 移除Layer
		gamesettings->removeFromParentAndCleanup(true);
		closeLayerButton->removeFromParentAndCleanup(true);
		});
}


void playerfightScene::fightEnd() {
	//for (Hero* heroesend : allMyHeroes) {

	//}

}


