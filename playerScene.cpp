#include "ui/CocosGUI.h"
#include "playerScene.h"
#include"heroSprite.h"

using namespace ui;

USING_NS_CC;

#define STORETAG   462
chessboardSeat seat1;   //棋盘位置
preparationSeat seat2;   //备战席位置
extern std::vector<Hero*> allMyHeroes;//我方所有英雄
extern std::vector<Hero*> allEnemyHeroes;//敌方所有英雄
extern int fight;
extern playerroleLayer* smallhero;

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

	
	timeLeft = 6;  // 设置初始时间，单位是秒
	// 创建一个标签用于显示倒计时进度条
	auto to1 = Sequence::createWithTwoActions(ProgressTo::create(timeLeft, 100), ProgressTo::create(0, 100));
	auto progress0 = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("progresstimer0.png"));
	auto progress1 = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("progresstimer1.png"));
	progress0->setType(cocos2d::ProgressTimer::Type::BAR);
	progress0->setMidpoint(cocos2d::Vec2(0, 0.5));// 设置起始点为左边中点
	progress0->setBarChangeRate(cocos2d::Vec2(1, 0)); // 设置只在水平方向改变
	progress0->setPercentage(100); // 设置初始百分比为 0%
	progress1->setType(cocos2d::ProgressTimer::Type::BAR);
	progress1->setMidpoint(cocos2d::Vec2(0, 0.5));// 设置起始点为左边中点
	progress1->setBarChangeRate(cocos2d::Vec2(1, 0)); // 设置只在水平方向改变
	progress1->setPercentage(0); // 设置初始百分比为 0%
	// 设置进度条位置
	progress0->setPosition(955, 1000);
	progress1->setPosition(955, 1000);
	progress1->runAction(Repeat::create(to1, 1));
	// 添加进度条到场景
	this->addChild(progress0, 8);
	this->addChild(progress1, 9);
	// 启动定时器，每秒更新一次
	schedule(CC_CALLBACK_1(playerScene::updateTimer, this), 1.0f, "update_key");





	auto hero1 = Hero::createHero(1, Vec2(700, 400), 1);
	this->addChild(hero1, 1);
	hero1->enterBattle();

	auto hero2 = Hero::createHero(1, Vec2(700, 800), 2);
	this->addChild(hero2, 1);
	hero2->enterBattle();
	Hero::attack();

	


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

	






    auto listenermouse = EventListenerMouse::create();
	listenermouse->onMouseMove = [this](EventMouse* event) {
		Vec2 myMousepos = Vec2(event->getCursorX(), event->getCursorY());
		for (Hero* movehero : allMyHeroes) {
			// 添加鼠标事件监听器到事件分发器
			auto listener = EventListenerTouchOneByOne::create();
			Vec2 herosize = Vec2(442 * movehero->getScale(), 375 * movehero->getScale());
			Vec2 heroposition = movehero->getPosition();
			if (myMousepos.x > heroposition.x - herosize.x / 9 && myMousepos.x<heroposition.x + herosize.x / 9 && myMousepos.y>heroposition.y - herosize.y / 9 && myMousepos.y < heroposition.y + herosize.y / 9) {
				listener->onTouchBegan = CC_CALLBACK_2(Hero::onTouchBegan, movehero);
				listener->onTouchMoved = CC_CALLBACK_2(Hero::onTouchMoved, movehero);
				listener->onTouchEnded = CC_CALLBACK_2(Hero::onTouchEnded, movehero);
				_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, movehero);
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenermouse, this);
	



	//设置
	auto set1 = Sprite::create("SetButton2.png");
	auto set2 = Sprite::create("SetButton1.png");
	auto _set = MenuItemSprite::create(set1, set2,
		CC_CALLBACK_1(playerScene::callbackof_set, this));
	auto SET = Menu::create(_set, NULL);
	SET->setPosition(1795, 990);
	this->addChild(SET, 40);



	return 1;
}


void playerScene::callbackof_set(Ref* pSender)   
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



void playerScene::updateTimer(float dt)
{
	timeLeft--;

	if (timeLeft >= 0)
	{
		// 更新标签显示
	//	label->setString(StringUtils::format("Time: %d", timeLeft));
	}
	else
	{
		// 时间到，执行场景切换操作
		unschedule("update_key");
		fight = true;


		auto playerfightscene = playerfightScene::create();
		auto fadeIn = TransitionFade::create(1.0f, playerfightscene, Color3B::BLACK);
		Director::getInstance()->pushScene(fadeIn);
	}
}