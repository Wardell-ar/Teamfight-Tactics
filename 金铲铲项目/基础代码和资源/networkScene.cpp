#include "networkScene.h"
#include"heroSprite.h"
#include<vector>
#include"endScene.h"

USING_NS_CC;

#define STORETAG   462

extern int Gamein;

extern std::vector<Sprite*>MySeat;  //大小为14
/*
  0——战斗席0
  1——战斗席1
  2——战斗席2
  3——战斗席3
  4——战斗席4

  5——备战席0
  6——备战席1
  7——备战席2
  8——备战席3
  9——备战席4
  10——备战席5
  11——备战席6
  12——备战席7
  13——备战席8
*/

playerroleLayer* myrole_;
playerroleLayer* enemyrole_;

extern chessboardSeat seat1;   //棋盘位置
extern preparationSeat seat2;   //备战席位置

extern chessboardSeat seat3;   //敌方棋盘位置
extern preparationSeat seat4;   //敌方备战席位置

extern Vector<Hero*> allMyHeroes;//我方所有英雄
extern Vector<Hero*> allEnemyHeroes;//敌方所有英雄

extern int fight;  //全局战况

// 英雄传输数据存储
int mydata[14][7];
int enemydata[14][7];
/*
type
level
inboard
index
bloodweap
magicweap
powerweap
*/

networkScene* networkScene::createScene() {
	return networkScene::create();
}


bool networkScene::init() {

	if (!Scene::create()) {
		return 0;
	}



	//背景设置
	auto background = Sprite::create("playerSceneBackground.png");
	this->addChild(background, 0);
	background->setPosition(955, 540);





	// 每一帧更新传输数组的值，并发送消息
	this->schedule([](float dt) {
		int i = 0;
		for (Hero* hero : allMyHeroes) {
			mydata[i][0] = hero->getType();
			mydata[i][1] = hero->getLevel();
			mydata[i][2] = hero->isInBoard();
			mydata[i][3] = hero->GetIndex();
			mydata[i][4] = hero->equip_blood;
			mydata[i][5] = hero->equip_magic;
			mydata[i][6] = hero->equip_power;
			i++;
		}
		while (i < 14) {
			mydata[i][0] = -1;
			i++;
		}

		// 进行传输
		Gamein = 1;
		SendJSONstringGamein();
		ClientSocket::onSendGamein();
	}, "passdata");






	//武器图片初始化
	equip_for_blood = Sprite::create("equip_for_blood.png");    // 增加最大血量666
	equip_for_power = Sprite::create("equip_for_power.png");    // 增加攻击力100
	equip_for_magic = Sprite::create("equip_for_magic.png");    // 增加每次普攻回蓝10

	equip_for_blood->setScale(0.2);
	equip_for_power->setScale(0.2);
	equip_for_magic->setScale(0.2);

	equip_for_blood->setPosition(200, 750);
	equip_for_power->setPosition(200, 650);
	equip_for_magic->setPosition(200, 550);

	this->addChild(equip_for_blood, 4);
	this->addChild(equip_for_power, 4);
	this->addChild(equip_for_magic, 4);







	//羁绊图标初始化
	attacktram = Sprite::create("attacktrammel.png");
	healtram = Sprite::create("healtrammel.png");
	attacktram->setPosition(172 + 70, 900 + 50);
	attacktram->setScale(0.5);
	healtram->setPosition(172 + 70, 900 + 50);
	healtram->setScale(0.6);
	this->addChild(attacktram, 4);
	this->addChild(healtram, 4);
	attacktram->setVisible(false);
	healtram->setVisible(false);





	//设置按键的布置
	setting = settingLayer::createLayer();  // 设置界面初始化
	setting->setPosition(0, 0);
	this->addChild(setting, 10);
	setting->setVisible(false);

	auto settingbutton1 = Sprite::create("setting1.png");
	auto settingbutton2 = Sprite::create("setting2.png");
	auto settingbutton = MenuItemSprite::create(settingbutton1, settingbutton2,
		CC_CALLBACK_1(networkScene::settingCallBack, this));
	auto menu = Menu::create(settingbutton, NULL);
	menu->setPosition(940, 520);
	this->addChild(menu, 4);
	menu->setScale(0.1);



	// 背景音乐
	AudioEngine::stopAll();
	int audioId = AudioEngine::play2d("background_music.mp3", -1);
	AudioEngine::setVolume(audioId, 0.05);




	// 我方的初始英雄
	auto hero1 = Hero::createHero(1, Vec2(seat1.seats[0].x + 70, seat1.seats[0].y + 50), 1);
	seat1.seats[0].state = 1;
	this->addChild(hero1, 2);
	hero1->enterBoard();
	hero1->setIndex(0);





	/* 装备的移动——狂徒 */
	auto equipmentListener1 = EventListenerTouchOneByOne::create();
	equipmentListener1->setSwallowTouches(true);
	//装备点击判定
	equipmentListener1->onTouchBegan = [this](Touch* t, Event* e)->bool {
		Vec2 myclick = t->getLocation();
		myclick = equip_for_blood->convertToNodeSpace(myclick);
		Rect spriteBoundingBox = Rect(0, 0, equip_for_blood->getContentSize().width, equip_for_blood->getContentSize().height);
		if (spriteBoundingBox.containsPoint(myclick)) {
			return true;
		}
		return false;
	};
	//装备的移动
	equipmentListener1->onTouchMoved = [this](Touch* t, Event* e)->void {
		equip_for_blood->setPosition(equip_for_blood->getPosition() + t->getDelta());
	};
	//英雄放置
	equipmentListener1->onTouchEnded = [this](Touch* t, Event* e)->void {
		int find = 0;
		for (Hero* hero : allMyHeroes) {
			Vec2 clickEnd = t->getLocation();
			clickEnd = hero->convertToNodeSpace(clickEnd);
			Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
			if (spriteBoundingBox.containsPoint(clickEnd)) {  // 装备成功
				// 效果
				hero->setMaxBlood(hero->getMaxBlood() + 666);
				hero->setBlood(hero->getBlood() + 666);
				hero->equip_blood = 1;
				find = 1;

				// 装备的消失效果（缩小、消失、音效）
				auto scale = ScaleTo::create(0.2f, 0.01f);
				auto disappear = CallFunc::create([this]() {
					equip_for_blood->setVisible(false);
					});
				auto music = CallFunc::create([]() {
					int audioId = AudioEngine::play2d("equip.mp3");
				AudioEngine::setVolume(audioId, 1.0f);
					});
				auto sequence = Sequence::create(scale, disappear, music, nullptr);
				equip_for_blood->runAction(sequence);

				break;
			}
		}
		if (find == 0) {  // 没有装备成功，返回原位
			putback_equip_for_blood();
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(equipmentListener1, this);






	/* 装备的移动——大刀 */
	auto equipmentListener2 = EventListenerTouchOneByOne::create();
	equipmentListener2->setSwallowTouches(true);
	//装备点击判定
	equipmentListener2->onTouchBegan = [this](Touch* t, Event* e)->bool {
		Vec2 myclick = t->getLocation();
		myclick = equip_for_power->convertToNodeSpace(myclick);
		Rect spriteBoundingBox = Rect(0, 0, equip_for_power->getContentSize().width, equip_for_power->getContentSize().height);
		if (spriteBoundingBox.containsPoint(myclick)) {
			return true;
		}
		return false;
	};
	//装备的移动
	equipmentListener2->onTouchMoved = [this](Touch* t, Event* e)->void {
		equip_for_power->setPosition(equip_for_power->getPosition() + t->getDelta());
	};
	//英雄放置
	equipmentListener2->onTouchEnded = [this](Touch* t, Event* e)->void {
		int find = 0;
		for (Hero* hero : allMyHeroes) {
			Vec2 clickEnd = t->getLocation();
			clickEnd = hero->convertToNodeSpace(clickEnd);
			Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
			if (spriteBoundingBox.containsPoint(clickEnd)) {  // 装备成功
				// 效果
				hero->setPower(hero->getPower() + 100);
				hero->equip_power = 1;
				find = 1;

				// 装备的消失效果（缩小、消失、音效）
				auto scale = ScaleTo::create(0.2f, 0.01f);
				auto disappear = CallFunc::create([this]() {
					equip_for_power->setVisible(false);
					});
				auto music = CallFunc::create([]() {
					int audioId = AudioEngine::play2d("equip.mp3");
				AudioEngine::setVolume(audioId, 1.0f);
					});
				auto sequence = Sequence::create(scale, disappear, music, nullptr);
				equip_for_power->runAction(sequence);

				break;
			}
		}
		if (find == 0) {  // 没有装备成功，返回原位
			putback_equip_for_power();
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(equipmentListener2, this);






	/* 装备的移动——青刀 */
	auto equipmentListener3 = EventListenerTouchOneByOne::create();
	equipmentListener3->setSwallowTouches(true);
	//装备点击判定
	equipmentListener3->onTouchBegan = [this](Touch* t, Event* e)->bool {
		Vec2 myclick = t->getLocation();
		myclick = equip_for_magic->convertToNodeSpace(myclick);
		Rect spriteBoundingBox = Rect(0, 0, equip_for_magic->getContentSize().width, equip_for_magic->getContentSize().height);
		if (spriteBoundingBox.containsPoint(myclick)) {
			return true;
		}
		return false;
	};
	//装备的移动
	equipmentListener3->onTouchMoved = [this](Touch* t, Event* e)->void {
		equip_for_magic->setPosition(equip_for_magic->getPosition() + t->getDelta());
	};
	//英雄放置
	equipmentListener3->onTouchEnded = [this](Touch* t, Event* e)->void {
		int find = 0;
		for (Hero* hero : allMyHeroes) {
			Vec2 clickEnd = t->getLocation();
			clickEnd = hero->convertToNodeSpace(clickEnd);
			Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
			if (spriteBoundingBox.containsPoint(clickEnd)) {  // 装备成功
				// 效果
				hero->setEachMagic(hero->getEachMagic() + 10);
				hero->equip_magic = 1;
				find = 1;

				// 装备的消失效果（缩小、消失、音效）
				auto scale = ScaleTo::create(0.2f, 0.01f);
				auto disappear = CallFunc::create([this]() {
					equip_for_magic->setVisible(false);
					});
				auto music = CallFunc::create([]() {
					int audioId = AudioEngine::play2d("equip.mp3");
				AudioEngine::setVolume(audioId, 1.0f);
					});
				auto sequence = Sequence::create(scale, disappear, music, nullptr);
				equip_for_magic->runAction(sequence);

				break;
			}
		}
		if (find == 0) {  // 没有装备成功，返回原位
			putback_equip_for_magic();
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(equipmentListener3, this);





	/*英雄位置移动*/
	auto changePosListener = EventListenerTouchOneByOne::create();
	//事件吞没
	changePosListener->setSwallowTouches(true);
	//英雄点击判定
	changePosListener->onTouchBegan = [this](Touch* t, Event* e)->bool {

		//战斗环节只能对备战席上英雄点击有效
		if (fight) {
			for (Hero* hero : allMyHeroes) {
				if (!hero->isInBoard()) {  //不在战斗席上
					Vec2 myclick = t->getLocation();
					myclick = hero->convertToNodeSpace(myclick);
					Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
					if (spriteBoundingBox.containsPoint(myclick)) {
						hero->SetClicked(1);
						return true;
					}
				}
			}
			return false;  //即没有点击到备战席上任何英雄
		}
		else {  //非战斗环节对所有己方英雄点击均有效
			for (Hero* hero : allMyHeroes) {
				Vec2 myclick = t->getLocation();
				myclick = hero->convertToNodeSpace(myclick);
				Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
				if (spriteBoundingBox.containsPoint(myclick)) {
					hero->SetClicked(1);
					return true;
				}
			}
			return false;  //即没有点击到任何英雄
		}

	};
	//英雄的移动
	changePosListener->onTouchMoved = [](Touch* t, Event* e)->void {
		for (Hero* hero : allMyHeroes) {
			if (hero->IsClicked()) {
				hero->setPosition(hero->getPosition() + t->getDelta());
				break;
			}
		}
	};
	//英雄放置
	changePosListener->onTouchEnded = [this](Touch* t, Event* e)->void {
		if (fight) {  //结束点只考虑是否落在备战席上
			int i;
			for (i = 5; i < 14; i++) {
				Vec2 clickEnd = t->getLocation();
				clickEnd = MySeat[i]->convertToNodeSpace(clickEnd);
				Rect spriteBoundingBox = Rect(0, 0, MySeat[i]->getContentSize().width, MySeat[i]->getContentSize().height);
				if (spriteBoundingBox.containsPoint(clickEnd)) {
					int index = i - 5;  //备战席位置下标

					//判断该位置是否为空
					if (seat2.seats[index].state == 0) {  //空位置
						for (Hero* hero : allMyHeroes) {
							if (hero->IsClicked()) {  //找到被点击的英雄
								seat2.seats[hero->GetIndex()].Removesprite();  //原位置设为空
								hero->setIndex(index);  //英雄存储新下标
								hero->setPosition(seat2.seats[index].x + 70, seat2.seats[index].y + 50);
								seat2.seats[index].Setsprite();
								hero->SetClicked(0);  //重置点击
								break;
							}
						}
					}
					else {   //非空位置
						for (Hero* hero1 : allMyHeroes) {
							if (hero1->IsClicked()) {  //找到被点击的英雄
								for (Hero* hero2 : allMyHeroes) {
									if (!hero2->isInBoard() && hero2->GetIndex() == index) {
										//交换位置
										hero2->setIndex(hero1->GetIndex());
										hero1->setIndex(index);
										hero1->setPosition(seat2.seats[hero1->GetIndex()].x + 70, seat2.seats[hero1->GetIndex()].y + 50);
										hero2->setPosition(seat2.seats[hero2->GetIndex()].x + 70, seat2.seats[hero2->GetIndex()].y + 50);
										hero1->SetClicked(0);
										break;
									}
								}

								break;
							}
						}
					}

					break;  //退出查找其他备战席位置
				}
			}
			if (i == 14) {  //回到原点
				for (Hero* hero : allMyHeroes) {
					if (hero->IsClicked()) {
						hero->setPosition(seat2.seats[hero->GetIndex()].x + 70, seat2.seats[hero->GetIndex()].y + 50);
						hero->SetClicked(0);
						break;
					}
				}
			}
		}
		else {   //结束点考虑所有点位
			int i;
			for (i = 0; i < 14; i++) {
				Vec2 clickEnd = t->getLocation();
				clickEnd = MySeat[i]->convertToNodeSpace(clickEnd);
				Rect spriteBoundingBox = Rect(0, 0, MySeat[i]->getContentSize().width, MySeat[i]->getContentSize().height);
				if (spriteBoundingBox.containsPoint(clickEnd)) {  //停留在了某个位置
					if (i >= 5) {  //停留的位置是备战席
						int index = i - 5;  //备战席位置下标

						//判断该位置是否为空
						if (seat2.seats[index].state == 0) {  //空位置
							for (Hero* hero : allMyHeroes) {
								if (hero->IsClicked()) {  //找到被点击的英雄
									if (hero->isInBoard()) {  //原位置在战斗席
										seat1.seats[hero->GetIndex()].Removesprite();  //原位置设为空
									}
									else {   //原位置在备战席
										seat2.seats[hero->GetIndex()].Removesprite();  //原位置设为空
									}

									hero->setIndex(index);  //英雄存储新下标
									hero->setPosition(seat2.seats[index].x + 70, seat2.seats[index].y + 50);
									seat2.seats[index].Setsprite();
									hero->exitBoard();  //回到备战席
									hero->SetClicked(0);  //重置点击
									break;
								}
							}
						}
						else {   //非空位置
							for (Hero* hero1 : allMyHeroes) {
								if (hero1->IsClicked()) {  //找到被点击的英雄
									for (Hero* hero2 : allMyHeroes) {
										if (!hero2->isInBoard() && hero2->GetIndex() == index) {
											//交换位置
											hero2->setIndex(hero1->GetIndex());
											hero1->setIndex(index);
											hero1->setPosition(seat2.seats[hero1->GetIndex()].x + 70, seat2.seats[hero1->GetIndex()].y + 50);
											if (!hero1->isInBoard())
											{
												hero2->setPosition(seat2.seats[hero2->GetIndex()].x + 70, seat2.seats[hero2->GetIndex()].y + 50);
											}
											else {
												hero2->setPosition(seat1.seats[hero2->GetIndex()].x + 70, seat1.seats[hero2->GetIndex()].y + 50);
											}
											hero1->SetClicked(0);
											hero2->SetBoard(hero1->isInBoard());
											hero1->exitBoard();
											break;
										}
									}

									break;
								}
							}
						}
					}
					else {   //停留的位置是战斗席
						int index = i;
						if (seat1.seats[index].state == 0) {  //空位置
							int hero_in_board = 0;
							for (Hero* hero : allMyHeroes) {
								if (hero->isInBoard()) {
									hero_in_board++;
								}
							}
							for (Hero* hero : allMyHeroes) {
								if (hero->IsClicked()) {  //找到被点击的英雄
									if (hero->isInBoard()) {  //原位置在战斗席
										seat1.seats[hero->GetIndex()].Removesprite();  //原位置设为空
										hero->setIndex(index);  //英雄存储新下标
										hero->setPosition(seat1.seats[index].x + 70, seat1.seats[index].y + 50);
										seat1.seats[index].Setsprite();
										hero->enterBoard();  //上战场
										hero->SetClicked(0);  //重置点击
									}
									else {   //原位置在备战席
										if (hero_in_board >= store->level)  //超出人数
										{
											hero->setPosition(seat2.seats[hero->GetIndex()].x + 70, seat2.seats[hero->GetIndex()].y + 50);
										}
										else {
											seat2.seats[hero->GetIndex()].Removesprite();  //原位置设为空
											hero->setIndex(index);  //英雄存储新下标
											hero->setPosition(seat1.seats[index].x + 70, seat1.seats[index].y + 50);
											seat1.seats[index].Setsprite();
											hero->enterBoard();  //上战场
											hero->SetClicked(0);  //重置点击
										}
									}
									break;
								}
							}
						}
						else {   //非空位置
							for (Hero* hero1 : allMyHeroes) {
								if (hero1->IsClicked()) {  //找到被点击的英雄
									for (Hero* hero2 : allMyHeroes) {
										if (hero2->isInBoard() && hero2->GetIndex() == index) {
											//交换位置
											hero2->setIndex(hero1->GetIndex());
											hero1->setIndex(index);
											hero1->setPosition(seat1.seats[hero1->GetIndex()].x + 70, seat1.seats[hero1->GetIndex()].y + 50);
											if (!hero1->isInBoard())
											{
												hero2->setPosition(seat2.seats[hero2->GetIndex()].x + 70, seat2.seats[hero2->GetIndex()].y + 50);
											}
											else {
												hero2->setPosition(seat1.seats[hero2->GetIndex()].x + 70, seat1.seats[hero2->GetIndex()].y + 50);
											}
											hero1->SetClicked(0);
											hero2->SetBoard(hero1->isInBoard());
											hero1->enterBoard();
											break;
										}
									}

									break;
								}
							}
						}
					}

					break;  //退出查找其他备战席位置
				}
			}
			if (i == 14) {  //回到原点
				for (Hero* hero : allMyHeroes) {
					if (hero->IsClicked()) {
						if (!hero->isInBoard())
						{
							hero->setPosition(seat2.seats[hero->GetIndex()].x + 70, seat2.seats[hero->GetIndex()].y + 50);
						}
						else {
							hero->setPosition(seat1.seats[hero->GetIndex()].x + 70, seat1.seats[hero->GetIndex()].y + 50);
						}
						hero->SetClicked(0);
						break;
					}
				}
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(changePosListener, this);





	//每一帧更新英雄的血条和蓝条
	this->schedule([this](float dt) {
		//更新我方英雄血量和蓝量
		for (Hero* hero : allMyHeroes) {
			hero->updatebloodandmagic();
		}
	//更新敌方英雄的血量和蓝量
	for (Hero* hero : allEnemyHeroes) {
		hero->updatebloodandmagic();
	}
		}, "updateherobar_");





	//每一帧更新小小英雄的血条
	this->schedule([this](float dt) {
		float mypercentage = myrole_->cur_blood / myrole_->max_blood * 100.0f;
	float enemypercentage = enemyrole_->cur_blood / enemyrole_->max_blood * 100.0f;
	myrole_->healthBar->setPercentage(mypercentage);
	enemyrole_->healthBar->setPercentage(enemypercentage);
	if (mypercentage == 0 && enemypercentage != 0) {  //我方失败
		auto delayAction = DelayTime::create(1.0f); // 1秒钟的延迟时间
		auto callback = CallFunc::create([]() {
			auto endscene = endScene::createScene(0);
		Director::getInstance()->replaceScene(endscene);
		AudioEngine::stopAll();
		int audioId = AudioEngine::play2d("failure.mp3");
		AudioEngine::setVolume(audioId, 1.0f);
			});
		auto sequence = Sequence::create(delayAction, callback, nullptr);
		this->runAction(sequence);
	}
	if (enemypercentage == 0 && mypercentage != 0) {  //敌方失败
		auto delayAction = DelayTime::create(1.0f); // 1秒钟的延迟时间
		auto callback = CallFunc::create([]() {
			auto endscene = endScene::createScene(1);
		Director::getInstance()->replaceScene(endscene);
		AudioEngine::stopAll();
		int audioId = AudioEngine::play2d("victory.mp3");
		AudioEngine::setVolume(audioId, 1.0f);
			});
		auto sequence = Sequence::create(delayAction, callback, nullptr);
		this->runAction(sequence);
	}
	if (mypercentage == 0 && enemypercentage == 0) {  //平局
		auto delayAction = DelayTime::create(1.0f); // 1秒钟的延迟时间
		auto callback = CallFunc::create([]() {
			auto endscene = endScene::createScene(2);
		Director::getInstance()->replaceScene(endscene);
			});
		auto sequence = Sequence::create(delayAction, callback, nullptr);
		this->runAction(sequence);
	}
		}, "updaterolebar_");






	//进度条设置
	progress0 = Sprite::create("progress0.png");
	progress1 = ProgressTimer::create(Sprite::create("progress1.png"));
	progress0->setPosition(955, 1000);
	progress1->setPosition(955, 1000);
	this->addChild(progress0, 5);
	this->addChild(progress1, 6);
	progress1->setType(ProgressTimer::Type::BAR);
	progress1->setMidpoint(Vec2(0, 0.5)); // 从左到右
	progress1->setBarChangeRate(Vec2(1, 0)); // 沿水平方向改变





	//游戏主循环的回调函数
	this->schedule(CC_SCHEDULE_SELECTOR(networkScene::startGame), 1.0f);





	/*我方位置图标的显示(仅显示我方)*/
	//位置图标初始化
	for (int i = 0; i < 14; i++) {
		MySeat.push_back(Sprite::create("seats.png"));
	}
	//图标显示
	for (int i = 0; i < 5; i++) {
		MySeat[i]->setScale(0.25);
		MySeat[i]->setPosition(seat1.seats[i].x + 70, seat1.seats[i].y + 50);
		this->addChild(MySeat[i], 1);
	}
	for (int i = 0; i < 9; i++) {
		MySeat[i + 5]->setScale(0.25);
		MySeat[i + 5]->setPosition(seat2.seats[i].x + 70, seat2.seats[i].y + 50);
		this->addChild(MySeat[i + 5], 1);
	}





	/* 羁绊设置 */
	/*

	  攻击型羁绊：type 1、2、4   //每5秒给敌方减血100
	  回复性羁绊：type 3、5、6   //每5秒给我方加血100

	*/
	/* 攻击羁绊 */
	this->schedule(CC_SCHEDULE_SELECTOR(networkScene::detect_attack_in), 0.01f);
	this->schedule([this](float dt) {
		//我方攻击羁绊效果
		int tag1 = 0;
	int tag2 = 0;
	int tag4 = 0;
	for (Hero* hero : allMyHeroes) {
		if (hero->isInBoard() && hero->getType() == 1) {
			tag1 = 1;
		}
		else if (hero->isInBoard() && hero->getType() == 2) {
			tag2 = 1;
		}
		else if (hero->isInBoard() && hero->getType() == 4) {
			tag4 = 1;
		}
	}
	if (tag1 && tag2 && tag4)
	{
		if (fight) {  // 战斗环节
			for (Hero* hero : allEnemyHeroes) {
				if (hero->isInBoard() && !hero->isDead()) {
					//攻击羁绊图标缩放、羁绊音效
					auto scale1 = ScaleTo::create(0.5f, 0.8f);
					auto scale2 = ScaleTo::create(0.5f, 0.5f);
					auto sequence = Sequence::create(scale1, scale2, nullptr);
					attacktram->runAction(sequence);
					int audioId = AudioEngine::play2d("trammel.mp3");
					AudioEngine::setVolume(audioId, 1.0f);

					// 扣血
					hero->decreaseHealth(200);
				}
			}
		}
	}

	//敌方攻击羁绊效果
	tag1 = 0;
	tag2 = 0;
	tag4 = 0;
	for (Hero* hero : allEnemyHeroes) {
		if (hero->isInBoard() && hero->getType() == 1) {
			tag1 = 1;
		}
		else if (hero->isInBoard() && hero->getType() == 2) {
			tag2 = 1;
		}
		else if (hero->isInBoard() && hero->getType() == 4) {
			tag4 = 1;
		}
	}
	if (tag1 && tag2 && tag4)
	{
		if (fight) {  // 战斗环节
			for (Hero* hero : allMyHeroes) {
				if (hero->isInBoard() && !hero->isDead()) {
					hero->decreaseHealth(200);
				}
			}
		}
	}

		}, 5.0f, "attacktrammel_");

	/* 恢复羁绊 */
	this->schedule(CC_SCHEDULE_SELECTOR(networkScene::detect_heal_in), 0.01f);
	this->schedule([this](float dt) {
		//我方恢复羁绊效果
		int tag3 = 0;
	int tag5 = 0;
	int tag6 = 0;
	for (Hero* hero : allMyHeroes) {
		if (hero->isInBoard() && hero->getType() == 3) {
			tag3 = 1;
		}
		else if (hero->isInBoard() && hero->getType() == 5) {
			tag5 = 1;
		}
		else if (hero->isInBoard() && hero->getType() == 6) {
			tag6 = 1;
		}
	}
	if (tag3 && tag5 && tag6)
	{
		if (fight) {  // 战斗环节
			for (Hero* hero : allMyHeroes) {
				if (hero->isInBoard() && !hero->isDead()) {
					//治疗羁绊图标缩放、羁绊音效
					auto scale1 = ScaleTo::create(0.5f, 0.9f);
					auto scale2 = ScaleTo::create(0.5f, 0.6f);
					auto sequence = Sequence::create(scale1, scale2, nullptr);
					healtram->runAction(sequence);
					int audioId = AudioEngine::play2d("trammel.mp3");
					AudioEngine::setVolume(audioId, 1.0f);

					//回血
					hero->setBlood((hero->getBlood() + 200) > hero->getMaxBlood() ? hero->getMaxBlood() : (hero->getBlood() + 200));
				}
			}
		}
	}

	//敌方恢复羁绊效果
	tag3 = 0;
	tag5 = 0;
	tag6 = 0;
	for (Hero* hero : allEnemyHeroes) {
		if (hero->isInBoard() && hero->getType() == 3) {
			tag3 = 1;
		}
		else if (hero->isInBoard() && hero->getType() == 5) {
			tag5 = 1;
		}
		else if (hero->isInBoard() && hero->getType() == 6) {
			tag6 = 1;
		}
	}
	if (tag3 && tag5 && tag6)
	{
		if (fight) {  // 战斗环节
			for (Hero* hero : allEnemyHeroes) {
				if (hero->isInBoard() && !hero->isDead()) {
					hero->setBlood((hero->getBlood() + 200) > hero->getMaxBlood() ? hero->getMaxBlood() : (hero->getBlood() + 200));
				}
			}
		}
	}

		}, 5.0f, "healtrammel_");






	//英雄售卖——通过鼠标点击右键来实现
	auto sellheroListener = EventListenerMouse::create();
	sellheroListener->onMouseDown = [this](EventMouse* event)->void {
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			//在战斗，则只能卖备战席上的英雄
			if (fight) {
				for (Hero* hero : allMyHeroes) {
					if (!hero->isInBoard()) {  //不在战斗席上
						Vec2 touchLocation = Vec2(event->getCursorX(), event->getCursorY());
						touchLocation = hero->convertToNodeSpace(touchLocation);
						Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
						if (spriteBoundingBox.containsPoint(touchLocation)) {
							//商店加钱，要显示刷新
							store->gold += (store->herocost[hero->GetheroType()]) * pow(3, (hero->getLevel()) - 1);
							store->updateUI();

							// 装备返还
							if (hero->equip_blood) {
								putback_equip_for_blood();
							}
							if (hero->equip_power) {
								putback_equip_for_power();
							}
							if (hero->equip_magic) {
								putback_equip_for_magic();
							}

							//英雄消失
							seat2.seats[hero->GetIndex()].Removesprite();
							allMyHeroes.eraseObject(hero);
							hero->removeFromParent();
							break;
						}
					}
				}
			}
			else {  //非战斗环节，可以点击所有英雄
				for (Hero* hero : allMyHeroes) {
					Vec2 touchLocation = Vec2(event->getCursorX(), event->getCursorY());
					touchLocation = hero->convertToNodeSpace(touchLocation);
					Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);

					if (spriteBoundingBox.containsPoint(touchLocation)) {
						//商店加钱，要显示刷新
						store->gold += (store->herocost[hero->GetheroType()]) * pow(3, (hero->getLevel()) - 1);
						store->updateUI();

						// 装备返还
						if (hero->equip_blood) {
							putback_equip_for_blood();
						}
						if (hero->equip_power) {
							putback_equip_for_power();
						}
						if (hero->equip_magic) {
							putback_equip_for_magic();
						}

						//英雄消失
						if (hero->isInBoard()) {
							seat1.seats[hero->GetIndex()].Removesprite();
						}
						else {
							seat2.seats[hero->GetIndex()].Removesprite();
						}
						allMyHeroes.eraseObject(hero);
						hero->removeFromParent();
						break;
					}
				}
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(sellheroListener, this);





	//小小英雄
	myrole_ = playerroleLayer::createLayer(0);
	this->addChild(myrole_, 3, ROLETAG);
	enemyrole_ = playerroleLayer::createLayer(1);
	this->addChild(enemyrole_, 3);





	//英雄列表
	/* 敌方 */
	auto enemy1 = Sprite::create("enemyplayer1.png");
	auto enemy2 = Sprite::create("enemyplayer2.png");
	auto enemy3 = Sprite::create("enemyplayer3.png");
	seeEnemy = MenuItemSprite::create(enemy1, enemy2, enemy3,
		CC_CALLBACK_1(networkScene::seeEnemy_callback, this));
	auto see_enemy = Menu::create(seeEnemy, NULL);
	this->addChild(see_enemy, 4);
	see_enemy->setScale(0.7);
	see_enemy->setPosition(1400, 600);

	/* 返回按键 */
	auto goback1 = Sprite::create("goback1.png");
	auto goback2 = Sprite::create("goback2.png");
	goback = MenuItemSprite::create(goback1, goback2,
		CC_CALLBACK_1(networkScene::goback_callback, this));
	auto go_back = Menu::create(goback, NULL);
	this->addChild(go_back, 4);
	go_back->setScale(0.7);
	go_back->setPosition(1400, 500);
	goback->setVisible(false);





	//商店，是Scene中的私有成员
	store = storeLayer::createLayer();
	this->addChild(store, 4);





	//小小英雄的移动
	auto roleMoveListener = EventListenerTouchOneByOne::create();
	roleMoveListener->setSwallowTouches(true);    //事件吞没
	roleMoveListener->onTouchBegan = [background, this](Touch* t, Event* e)-> bool {
		Vec2 pos = background->convertTouchToNodeSpace(t);
		if (pos.x > 323 && pos.x < 1247 && pos.y>327 && pos.y < 839)  //小小英雄移动范围
		{
			myrole_->cur_position = Vec2(pos.x + 70, pos.y + 50);
			auto role = myrole_->getChildByTag(ROLETAG);
			role->stopAllActions();
			role->runAction(MoveTo::create(0.3, Vec2(pos.x + 55.25, pos.y + 46.875)));
			return true;   //事件不再传递给其他监听器
		}
		else {
			return false;  //事件可以继续传递
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(roleMoveListener, this);




	//检测敌方英雄的移动
	this->schedule([this](float dt) {
		enemyrole_->getChildByTag(ROLETAG)->stopAllActions();
	enemyrole_->getChildByTag(ROLETAG)->runAction(MoveTo::create(0.3f, Vec2(enemyrole_->cur_position.x - 14.75, enemyrole_->cur_position.y - 3.125)));
		}, 0.05, "enemymove_");




	return 1;
}


//显示所有英雄
void networkScene::ShowHeroes(int IsMine) {
	if (IsMine) {
		for (Hero* hero : allMyHeroes) {
			if (hero->isInBoard()) {  //在战场上
				hero->setPosition(seat1.seats[hero->GetIndex()].x + 70, seat1.seats[hero->GetIndex()].y + 50);
			}
			else {  //在备战席上
				hero->setPosition(seat2.seats[hero->GetIndex()].x + 70, seat2.seats[hero->GetIndex()].y + 50);
			}
			hero->setBlood(hero->getMaxBlood());   //设置初始血量、满血
			hero->setMagic(hero->getStartMagic());  //设置初始蓝量
			hero->setColor(Color3B::WHITE);  //恢复颜色（死亡后会改变颜色）
			hero->setVisible(true);   //重新显示
			if (hero->isDead()) {   //重置Die标志
				hero->setDie(0);
			}
		}
	}
	else {
		// 首先清空原本的容器
		Vector<Hero*>heroToDelete;
		for (Hero* hero : allEnemyHeroes) {
			heroToDelete.pushBack(hero);
		}
		for (Hero* hero : heroToDelete) {
			allEnemyHeroes.eraseObject(hero);
		}

		// 根据enemydata数组来重新生成敌方英雄放入数组中
		Hero* temp;
		for (int i = 0; i < 14; i++) {
			if (enemydata[i][0] == -1) {  // 已全部生成完毕
				break;
			}
			else {
				temp = Hero::createHero(enemydata[i][0], Vec2(0, 0), 0);
				if (enemydata[i][1] != 1) {
					temp->upgrade(enemydata[i][1]);
				}
				temp->SetBoard(enemydata[i][2]);
				temp->setIndex(enemydata[i][3]);
				temp->equip_blood = enemydata[i][4];
				temp->equip_magic = enemydata[i][5];
				temp->equip_power = enemydata[i][6];
				this->addChild(temp, 2);
				temp->setVisible(false);
			}
		}

		// 检测英雄是否有携带装备
		for (Hero* hero : allEnemyHeroes) {
			if (hero->equip_blood) {
				hero->setMaxBlood(hero->getMaxBlood() + 666);
				hero->setBlood(hero->getBlood() + 666);
			}
			if (hero->equip_magic) {
				hero->setEachMagic(hero->getEachMagic() + 10);
			}
			if (hero->equip_power) {
				hero->setPower(hero->getPower() + 100);
			}
		}

		for (Hero* hero : allEnemyHeroes) {
			if (hero->isInBoard()) {  //在战场上
				hero->setPosition(seat3.seats[hero->GetIndex()].x + 70, seat3.seats[hero->GetIndex()].y + 50);
			}
			else {  //在备战席上
				hero->setPosition(seat4.seats[hero->GetIndex()].x + 70, seat4.seats[hero->GetIndex()].y + 50);
			}
			hero->setMagic(hero->getStartMagic());
			hero->setColor(Color3B::WHITE);
			hero->setVisible(true);
			if (hero->isDead()) {
				hero->setDie(0);
			}
		}
	}
}



//覆盖所有英雄
void networkScene::CoverHeroes(int IsMine) {
	if (IsMine) {
		for (Hero* hero : allMyHeroes) {
			hero->setVisible(false);
		}
	}
	else {
		for (Hero* hero : allEnemyHeroes) {
			hero->setVisible(false);
		}
	}
}



//观察敌方棋盘
void networkScene::seeEnemy_callback(Ref* pSender) {
	seeEnemy->setEnabled(false);  //禁用
	goback->setVisible(true);  //返回按键

	// 显示我方英雄撤去，我方商店撤去，显示敌方1
	CoverHeroes(1);
	store->setVisible(false);
	ShowHeroes(0);
}



//返回
void networkScene::goback_callback(Ref* pSender) {
	goback->setVisible(false);
	seeEnemy->setEnabled(true);

	//撤去敌方英雄，显示我方英雄和商店
	CoverHeroes(0);
	ShowHeroes(1);
	store->setVisible(true);
}



// 设置按键响应
void networkScene::settingCallBack(Ref* sender) {
	setting->setVisible(true);
}