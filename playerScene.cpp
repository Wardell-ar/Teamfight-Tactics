#include "playerScene.h"
#include"heroSprite.h"
#include<vector>
USING_NS_CC;

#define STORETAG   462

std::vector<Sprite*>MySeat;  //��СΪ14
/*
  0����ս��ϯ0
  1����ս��ϯ1
  2����ս��ϯ2
  3����ս��ϯ3
  4����ս��ϯ4

  5������սϯ0
  6������սϯ1
  7������սϯ2
  8������սϯ3
  9������սϯ4
  10������սϯ5
  11������սϯ6
  12������սϯ7
  13������սϯ8
*/


chessboardSeat seat1(1);   //����λ��
preparationSeat seat2(1);   //��սϯλ��

chessboardSeat seat3(0);   //�з�����λ��
preparationSeat seat4(0);   //�з���սϯλ��
extern std::vector<Hero*> allMyHeroes;//�ҷ�����Ӣ��
extern std::vector<Hero*> allEnemyHeroes;//�з�����Ӣ��
extern int fight;

Scene* playerScene::createScene() {
	return playerScene::create();
}

bool playerScene::init() {

	if (!Scene::create()) {
		return 0;
	}

	//��������
	auto background = Sprite::create("playerSceneBackground.png");
	this->addChild(background, 0);
	background->setPosition(955, 540);

	//Ӣ�۷���λ�ò���
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


	//Ӣ�۹�������
	/*
	auto hero1 = Hero::createHero(1, Vec2(700, 400), 1);
	this->addChild(hero1, 1);
	hero1->enterBattle();

	auto hero2 = Hero::createHero(1, Vec2(700, 800), 2);
	this->addChild(hero2, 1);
	hero2->enterBattle();
	Hero::attack();
	*/
	/*
	hero1->attack(hero2);
	hero2->attack(hero1);
	*/

	//Ӣ��λ���ƶ�
	auto changePosListener = EventListenerTouchOneByOne::create();
	//�¼���û
	changePosListener->setSwallowTouches(true);   
	//Ӣ�۵���ж�
	changePosListener->onTouchBegan = [this](Touch* t, Event* e)->bool {
		//��ȡ�����λ��

		//ս������ֻ�ܶԱ�սϯ��Ӣ�۵����Ч
		if (fight) {
			for (Hero* hero : allMyHeroes) {
				if (!hero->isInBoard() && hero->Getexist()) {  //����ս��ϯ��
					Vec2 myclick = t->getLocation();
					myclick = hero->convertToNodeSpace(myclick);
					Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
					if (spriteBoundingBox.containsPoint(myclick)) {
						hero->SetClicked(1);
						return true;
					}
				}
			}
			return false;  //��û�е������սϯ���κ�Ӣ��
		}
		else {  //��ս�����ڶ����м���Ӣ�۵������Ч
			for (Hero* hero : allMyHeroes) {
				if (hero->Getexist()) {
					Vec2 myclick = t->getLocation();
					myclick = hero->convertToNodeSpace(myclick);
					Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
					if (spriteBoundingBox.containsPoint(myclick)) {
						hero->SetClicked(1);
						return true;
					}
				}
			}
			return false;  //��û�е�����κ�Ӣ��
		}

	};
	//Ӣ�۵��ƶ�
	changePosListener->onTouchMoved = [](Touch* t, Event* e)->void {
		for (Hero* hero : allMyHeroes) {
			if (hero->IsClicked()) {
				hero->setPosition(hero->getPosition() + t->getDelta());
				break;
			}
		}
	};
	//Ӣ�۷���
	changePosListener->onTouchEnded = [](Touch* t, Event* e)->void {
		if (fight) {  //������ֻ�����Ƿ����ڱ�սϯ��
			int i;
			for (i = 5; i < 14; i++) {
				Vec2 clickEnd = t->getLocation();
				clickEnd = MySeat[i]->convertToNodeSpace(clickEnd);
				Rect spriteBoundingBox = Rect(0, 0, MySeat[i]->getContentSize().width, MySeat[i]->getContentSize().height);
				if (spriteBoundingBox.containsPoint(clickEnd)) {
					int index = i - 5;  //��սϯλ���±�
					
					//�жϸ�λ���Ƿ�Ϊ��
					if (seat2.seats[index].state == 0) {  //��λ��
						for (Hero* hero : allMyHeroes) {
							if (hero->IsClicked()) {  //�ҵ��������Ӣ��
								seat2.seats[hero->GetIndex()].Removesprite();  //ԭλ����Ϊ��
								hero->setIndex(index);  //Ӣ�۴洢���±�
								hero->setPosition(seat2.seats[index].x + 70, seat2.seats[index].y + 50);
								seat2.seats[index].Setsprite();
								hero->SetClicked(0);  //���õ��
								break;
							}
						}
					}
					else {   //�ǿ�λ��
						for (Hero* hero1 : allMyHeroes) {
							if (hero1->IsClicked()) {  //�ҵ��������Ӣ��
								for (Hero* hero2 : allMyHeroes) {
									if (hero2->Getexist() && !hero2->isInBoard() && hero2->GetIndex() == index) {
										//����λ��
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

					break;  //�˳�����������սϯλ��
				}
			}
			if (i == 14) {  //�ص�ԭ��
				for (Hero* hero : allMyHeroes) {
					if (hero->IsClicked()) {
						hero->setPosition(seat2.seats[hero->GetIndex()].x + 70, seat2.seats[hero->GetIndex()].y + 50);
						hero->SetClicked(0);
						break;
					}
				}
			}
		}
		else {   //�����㿼�����е�λ
			int i;
			for (i = 0; i < 14; i++) {
				Vec2 clickEnd = t->getLocation();
				clickEnd = MySeat[i]->convertToNodeSpace(clickEnd);
				Rect spriteBoundingBox = Rect(0, 0, MySeat[i]->getContentSize().width, MySeat[i]->getContentSize().height);
				if (spriteBoundingBox.containsPoint(clickEnd)) {  //ͣ������ĳ��λ��
					if (i >= 5) {  //ͣ����λ���Ǳ�սϯ
						int index = i - 5;  //��սϯλ���±�

						//�жϸ�λ���Ƿ�Ϊ��
						if (seat2.seats[index].state == 0) {  //��λ��
							for (Hero* hero : allMyHeroes) {
								if (hero->IsClicked()) {  //�ҵ��������Ӣ��
									if (hero->isInBoard()) {  //ԭλ����ս��ϯ
										seat1.seats[hero->GetIndex()].Removesprite();  //ԭλ����Ϊ��
									}
									else {   //ԭλ���ڱ�սϯ
										seat2.seats[hero->GetIndex()].Removesprite();  //ԭλ����Ϊ��
									}
									
									hero->setIndex(index);  //Ӣ�۴洢���±�
									hero->setPosition(seat2.seats[index].x + 70, seat2.seats[index].y + 50);
									seat2.seats[index].Setsprite();
									hero->exitBoard();  //�ص���սϯ
									hero->SetClicked(0);  //���õ��
									break;
								}
							}
						}
						else {   //�ǿ�λ��
							for (Hero* hero1 : allMyHeroes) {
								if (hero1->IsClicked()) {  //�ҵ��������Ӣ��
									for (Hero* hero2 : allMyHeroes) {
										if (hero2->Getexist() && !hero2->isInBoard() && hero2->GetIndex() == index) {
											//����λ��
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
					else {   //ͣ����λ����ս��ϯ
						int index = i;
						if (seat1.seats[index].state == 0) {  //��λ��
							for (Hero* hero : allMyHeroes) {
								if (hero->IsClicked()) {  //�ҵ��������Ӣ��
									if (hero->isInBoard()) {  //ԭλ����ս��ϯ
										seat1.seats[hero->GetIndex()].Removesprite();  //ԭλ����Ϊ��
									}
									else {   //ԭλ���ڱ�սϯ
										seat2.seats[hero->GetIndex()].Removesprite();  //ԭλ����Ϊ��
									}
									hero->setIndex(index);  //Ӣ�۴洢���±�
									hero->setPosition(seat1.seats[index].x + 70, seat1.seats[index].y + 50);
									seat1.seats[index].Setsprite();
									hero->enterBoard();  //��ս��
									hero->SetClicked(0);  //���õ��
									break;
								}
							}
						}
						else {   //�ǿ�λ��
							for (Hero* hero1 : allMyHeroes) {
								if (hero1->IsClicked()) {  //�ҵ��������Ӣ��
									for (Hero* hero2 : allMyHeroes) {
										if (hero2->Getexist() && hero2->isInBoard() && hero2->GetIndex() == index) {
											//����λ��
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

					break;  //�˳�����������սϯλ��
				}
			}
			if (i == 14) {  //�ص�ԭ��
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




	/*�ҷ�λ��ͼ�����ʾ(����ʾ�ҷ�)*/
	//λ��ͼ���ʼ��
	for (int i = 0; i < 14; i++) {
		MySeat.push_back(Sprite::create("seats.png"));
	}
	//ͼ����ʾ
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


	//Ӣ����������ͨ��������Ҽ���ʵ��
	auto sellheroListener = EventListenerMouse::create();
	sellheroListener->onMouseDown = [this](EventMouse* event)->void {
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			Vec2 myclick = Vec2(event->getCursorX(), event->getCursorY());
			//��ս������ֻ������սϯ�ϵ�Ӣ��
			if (fight) {
				for (Hero* hero : allMyHeroes) {
					if (!hero->isInBoard() && hero->Getexist()) {  //����ս��ϯ��
						Vec2 herosize = Vec2(442 * hero->getScale(), 375 * hero->getScale());
						Vec2 heroposition = hero->getPosition();
						if (myclick.x > heroposition.x - herosize.x / 9 && myclick.x<heroposition.x + herosize.x / 9 && myclick.y>heroposition.y - herosize.y / 9 && myclick.y < heroposition.y + herosize.y / 9) {
							//�̵��Ǯ��Ҫ��ʾˢ��
							store->gold += (store->herocost[hero->GetheroType()]) * pow(3, (hero->getLevel()) - 1);
							store->updateUI();

							//Ӣ����ʧ
							hero->Setexist(0);  //ʹ��Ӣ����Ч
							hero->setVisible(false);
							seat2.seats[hero->GetIndex()].Removesprite();
							break;
						}
					}
				}
			}
			else {  //��ս�����ڣ����Ե������Ӣ��
				for (Hero* hero : allMyHeroes) {
					if (hero->Getexist()) {
						Vec2 herosize = Vec2(442 * hero->getScale(), 375 * hero->getScale());
						Vec2 heroposition = hero->getPosition();
						if (myclick.x > heroposition.x - herosize.x / 9 && myclick.x<heroposition.x + herosize.x / 9 && myclick.y>heroposition.y - herosize.y / 9 && myclick.y < heroposition.y + herosize.y / 9) {
							//�̵��Ǯ��Ҫ��ʾˢ��
							store->gold += (store->herocost[hero->GetheroType()]) * pow(3, (hero->getLevel()) - 1);
							store->updateUI();

							//Ӣ����ʧ
							hero->Setexist(0);  //ʹ��Ӣ����Ч
							hero->setVisible(false);
							if (hero->isInBoard()) {
								seat1.seats[hero->GetIndex()].Removesprite();
							}
							else {
								seat2.seats[hero->GetIndex()].Removesprite();
							}
							break;
						}
					}
				}
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(sellheroListener, this);

	//ССӢ��
	auto playerrole = playerroleLayer::createLayer();  
	this->addChild(playerrole, 3, ROLETAG);

	//Ӣ���б�
	auto playerlist = playerlistLayer::createLayer();  
	this->addChild(playerlist, 4);

	//�̵꣬��Scene�е�˽�г�Ա
	store = storeLayer::createLayer();   
	this->addChild(store, 4);


	//ССӢ�۵��ƶ�
	auto roleMoveListener = EventListenerTouchOneByOne::create();
	roleMoveListener->setSwallowTouches(true);    //�¼���û
	roleMoveListener->onTouchBegan = [background, this](Touch* t, Event* e)-> bool {
		Vec2 pos = background->convertTouchToNodeSpace(t);
		if (pos.x > 323 && pos.x < 1247 && pos.y>327 && pos.y < 839)  //ССӢ���ƶ���Χ
		{
			auto role = this->getChildByTag(ROLETAG)->getChildByTag(ROLETAG);
			role->stopAllActions();
			role->runAction(MoveTo::create(0.3, Vec2(pos.x + 55.25, pos.y + 46.875)));
			return true;   //�¼����ٴ��ݸ�����������
		}
		else {
			return false;  //�¼����Լ�������
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(roleMoveListener, this);
	
	
	return 1;
}