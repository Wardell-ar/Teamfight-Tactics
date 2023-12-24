#include "playerScene.h"
#include"heroSprite.h"
#include<vector>
USING_NS_CC;

#define STORETAG   462

std::vector<Sprite*>MySeat;  //大小为14
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


chessboardSeat seat1(1);   //棋盘位置
preparationSeat seat2(1);   //备战席位置

chessboardSeat seat3(0);   //敌方棋盘位置
preparationSeat seat4(0);   //敌方备战席位置
extern Vector<Hero*> allMyHeroes;//我方所有英雄
extern Vector<Hero*> allEnemyHeroes;//敌方所有英雄
extern int fight;

playerScene* playerScene::createScene() {
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





	// 我方的初始英雄
	auto hero1 = Hero::createHero(1, Vec2(seat1.seats[0].x + 70, seat1.seats[0].y + 50), 1);
	seat1.seats[0].state = 1;
	this->addChild(hero1, 2);
	hero1->enterBoard();
	hero1->setIndex(0);





	/*英雄位置移动*/
	auto changePosListener = EventListenerTouchOneByOne::create();
	//事件吞没
	changePosListener->setSwallowTouches(true);   
	//英雄点击判定
	changePosListener->onTouchBegan = [this](Touch* t, Event* e)->bool {
		//获取点击的位置

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
	changePosListener->onTouchEnded = [](Touch* t, Event* e)->void {
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
							for (Hero* hero : allMyHeroes) {
								if (hero->IsClicked()) {  //找到被点击的英雄
									if (hero->isInBoard()) {  //原位置在战斗席
										seat1.seats[hero->GetIndex()].Removesprite();  //原位置设为空
									}
									else {   //原位置在备战席
										seat2.seats[hero->GetIndex()].Removesprite();  //原位置设为空
									}
									hero->setIndex(index);  //英雄存储新下标
									hero->setPosition(seat1.seats[index].x + 70, seat1.seats[index].y + 50);
									seat1.seats[index].Setsprite();
									hero->enterBoard();  //上战场
									hero->SetClicked(0);  //重置点击
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
											if(!hero1->isInBoard())
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
						if(!hero->isInBoard())
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
	}, "updateherobar");





	//每一帧更新小小英雄的血条
	this->schedule([this](float dt) {
		float mypercentage = myrole->cur_blood / myrole->max_blood * 100.0f;
	    float enemypercentage = enemyrole->cur_blood / enemyrole->max_blood * 100.0f;
		myrole->healthBar->setPercentage(mypercentage);
		enemyrole->healthBar->setPercentage(enemypercentage);
		if (mypercentage == 0) {  //我方失败
			//...切换场景
		}
		if (enemypercentage == 0) {  //敌方失败
			//...切换场景
		}
	}, "updaterolebar");






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
	this->schedule(CC_SCHEDULE_SELECTOR(playerScene::startGame), 1.0f);





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
	myrole = playerroleLayer::createLayer(1);
	this->addChild(myrole, 3, ROLETAG);
	enemyrole= playerroleLayer::createLayer(0);
	this->addChild(enemyrole, 3);




	//英雄列表
	auto playerlist = playerlistLayer::createLayer();  
	this->addChild(playerlist, 4);





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
			auto role = this->myrole->getChildByTag(ROLETAG);
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
		enemyrole->getChildByTag(ROLETAG)->stopAllActions();
	    enemyrole->getChildByTag(ROLETAG)->runAction(MoveTo::create(0.3, enemyrole->cur_position));
	}, "enemymove");
	


	
	return 1;
}

//显示所有英雄
void playerScene::ShowHeroes(int IsMine) {
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
	else {  //用于单机模式，随机生成英雄到战场（单机模式人机不放备战席、不买五费英雄）
		//删除原本的英雄
		Vector<Hero*>heroToDelete;
		for (Hero* hero : allEnemyHeroes) {
			heroToDelete.pushBack(hero);
		}
		for (Hero* hero : heroToDelete) {
			allEnemyHeroes.eraseObject(hero);
			hero->removeFromParent();
		}

		//重置seat3的state为0
		for (int i = 0; i < 5; i++) {
			seat3.seats[i].state = 0;
		}

		//遍历我方战场上的英雄，根据其位置、星级来随机生成敌方英雄放在Vector中
		//position参数随意，只要把index、inBoard值设对就好，然后设置不可见（显示板块在下面）
		//对应的位置seat3的state要设置为1
		int enemyPriority[5] = { 1,4,5,3,6 };  //随机生成英雄类型的优先级
		int i = 0;  //循环变量
		for (Hero* myhero : allMyHeroes) {
			if (myhero->isInBoard()) {
				auto enemy = Hero::createHero(enemyPriority[i], Vec2(0, 0), 0);
				enemy->setIndex(myhero->GetIndex());    //设置下标
				enemy->enterBoard();    //上战场
				this->addChild(enemy, 2);   //加入场景
				enemy->setVisible(false);   //设置不可见
				seat3.seats[myhero->GetIndex()].state = 1;   //位置设定
				enemy->update(myhero->GetIndex());  //设置为相同的星级
				i++;
			}
		}


		//通过Vector容器来显示敌方英雄
		for (Hero* hero : allEnemyHeroes) {
			if (hero->isInBoard()) {  //在战场上
				hero->setPosition(seat3.seats[hero->GetIndex()].x + 70, seat3.seats[hero->GetIndex()].y + 50);
			}
			else {  //在备战席上
				hero->setPosition(seat4.seats[hero->GetIndex()].x + 70, seat4.seats[hero->GetIndex()].y + 50);
			}
			hero->setBlood(hero->getMaxBlood());
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
void playerScene::CoverHeroes(int IsMine) {
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