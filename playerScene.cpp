#include "playerScene.h"
<<<<<<< Updated upstream
USING_NS_CC;

=======
#include"heroSprite.h"
USING_NS_CC;

#define STORETAG   462
chessboardSeat seat1;   //����λ��
preparationSeat seat2;   //��սϯλ��
extern std::vector<Hero*> allMyHeroes;//�ҷ�����Ӣ��
extern std::vector<Hero*> allEnemyHeroes;//�з�����Ӣ��
extern int fight;

>>>>>>> Stashed changes
Scene* playerScene::createScene() {
	return playerScene::create();
}

bool playerScene::init() {

	if (!Scene::create()) {
		return 0;
	}

<<<<<<< Updated upstream
	//background setting
=======
	//��������
>>>>>>> Stashed changes
	auto background = Sprite::create("playerSceneBackground.png");
	this->addChild(background, 0);
	background->setPosition(955, 540);

<<<<<<< Updated upstream
	

	

	



	//Ӣ�۷���λ�ò���
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
=======
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


	//Ӣ����������ͨ��������Ҽ���ʵ��
	auto sellheroListener = EventListenerMouse::create();
	sellheroListener->onMouseDown = [this](EventMouse* event)-> bool {
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
							store->gold += (store->herocost[hero->GetheroType()]) * (hero->getLevel());
							store->updateUI();

							//Ӣ����ʧ
							hero->Setexist(0);  //ʹ��Ӣ����Ч
							hero->setVisible(false);
							seat2.seats[hero->GetIndex()].Removesprite();
							return true;
						}
					}
				}
			}
			else {  //��ս�����ڣ����Ե������Ӣ��
				for (Hero* hero : allMyHeroes) {
					if (hero->Getexist()) {  //����ս��ϯ��
						Vec2 herosize = Vec2(442 * hero->getScale(), 375 * hero->getScale());
						Vec2 heroposition = hero->getPosition();
						if (myclick.x > heroposition.x - herosize.x / 9 && myclick.x<heroposition.x + herosize.x / 9 && myclick.y>heroposition.y - herosize.y / 9 && myclick.y < heroposition.y + herosize.y / 9) {
							//�̵��Ǯ��Ҫ��ʾˢ��
							store->gold += (store->herocost[hero->GetheroType()]) * (hero->getLevel());
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
							return true;
						}
					}
				}
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(sellheroListener, this);


	//Ӣ�۵��ƶ���λ
	// ....


	//�Ҽ�����
	auto playerrole = playerroleLayer::createLayer();  //ССӢ��
	this->addChild(playerrole, 2, ROLETAG);
	auto playerlist = playerlistLayer::createLayer();  //Ӣ���б�
	this->addChild(playerlist, 2);
	store = storeLayer::createLayer();   //�̵꣬��Scene�е�˽�г�Ա
>>>>>>> Stashed changes
	this->addChild(store, 3);


	//ССӢ�۵��ƶ�
<<<<<<< Updated upstream
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [background, this](Touch* t, Event* e)-> bool {
		Vec2 pos = background->convertTouchToNodeSpace(t);
		if (pos.x > 323 && pos.x < 1247 && pos.y>327 && pos.y < 839)
=======
	auto roleMoveListener = EventListenerTouchOneByOne::create();
	roleMoveListener->setSwallowTouches(true);    //�¼���û
	roleMoveListener->onTouchBegan = [background, this](Touch* t, Event* e)-> bool {
		Vec2 pos = background->convertTouchToNodeSpace(t);
		if (pos.x > 323 && pos.x < 1247 && pos.y>327 && pos.y < 839)  //ССӢ���ƶ���Χ
>>>>>>> Stashed changes
		{
			auto role = this->getChildByTag(ROLETAG)->getChildByTag(ROLETAG);
			role->stopAllActions();
			role->runAction(MoveTo::create(0.3, Vec2(pos.x + 55.25, pos.y + 46.875)));
<<<<<<< Updated upstream
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);









	return 1;
}
=======
			return true;   //�¼����ٴ��ݸ�����������
		}
		else {
			return false;  //�¼����Լ�������
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(roleMoveListener, this);
	
	
	return 1;
}
>>>>>>> Stashed changes
