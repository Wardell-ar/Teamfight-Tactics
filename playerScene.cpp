#include "ui/CocosGUI.h"
#include "playerScene.h"
#include"heroSprite.h"

using namespace ui;

USING_NS_CC;

#define STORETAG   462
chessboardSeat seat1;   //����λ��
preparationSeat seat2;   //��սϯλ��
extern std::vector<Hero*> allMyHeroes;//�ҷ�����Ӣ��
extern std::vector<Hero*> allEnemyHeroes;//�з�����Ӣ��
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

	
	timeLeft = 6;  // ���ó�ʼʱ�䣬��λ����
	// ����һ����ǩ������ʾ����ʱ������
	auto to1 = Sequence::createWithTwoActions(ProgressTo::create(timeLeft, 100), ProgressTo::create(0, 100));
	auto progress0 = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("progresstimer0.png"));
	auto progress1 = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("progresstimer1.png"));
	progress0->setType(cocos2d::ProgressTimer::Type::BAR);
	progress0->setMidpoint(cocos2d::Vec2(0, 0.5));// ������ʼ��Ϊ����е�
	progress0->setBarChangeRate(cocos2d::Vec2(1, 0)); // ����ֻ��ˮƽ����ı�
	progress0->setPercentage(100); // ���ó�ʼ�ٷֱ�Ϊ 0%
	progress1->setType(cocos2d::ProgressTimer::Type::BAR);
	progress1->setMidpoint(cocos2d::Vec2(0, 0.5));// ������ʼ��Ϊ����е�
	progress1->setBarChangeRate(cocos2d::Vec2(1, 0)); // ����ֻ��ˮƽ����ı�
	progress1->setPercentage(0); // ���ó�ʼ�ٷֱ�Ϊ 0%
	// ���ý�����λ��
	progress0->setPosition(955, 1000);
	progress1->setPosition(955, 1000);
	progress1->runAction(Repeat::create(to1, 1));
	// ��ӽ�����������
	this->addChild(progress0, 8);
	this->addChild(progress1, 9);
	// ������ʱ����ÿ�����һ��
	schedule(CC_CALLBACK_1(playerScene::updateTimer, this), 1.0f, "update_key");





	auto hero1 = Hero::createHero(1, Vec2(700, 400), 1);
	this->addChild(hero1, 1);
	hero1->enterBattle();

	auto hero2 = Hero::createHero(1, Vec2(700, 800), 2);
	this->addChild(hero2, 1);
	hero2->enterBattle();
	Hero::attack();

	


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
							store->gold += (store->herocost[hero->GetheroType()]) * pow(3, (hero->getLevel()) - 1);
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
							return true;
						}
					}
				}
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(sellheroListener, this);

	//�Ҽ�����
	auto playerrole = playerroleLayer::createLayer();  //ССӢ��
	this->addChild(playerrole, 2, ROLETAG);
	auto playerlist = playerlistLayer::createLayer();  //Ӣ���б�
	this->addChild(playerlist, 2);
	store = storeLayer::createLayer();   //�̵꣬��Scene�е�˽�г�Ա
	this->addChild(store, 3);


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

	






    auto listenermouse = EventListenerMouse::create();
	listenermouse->onMouseMove = [this](EventMouse* event) {
		Vec2 myMousepos = Vec2(event->getCursorX(), event->getCursorY());
		for (Hero* movehero : allMyHeroes) {
			// �������¼����������¼��ַ���
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
	



	//����
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
	auto gamesettings = GameSettings::createLayer(); //����
	this->addChild(gamesettings, 100);

	auto closeLayerButton = Button::create("back1.png", "back2.png");
	closeLayerButton->setPosition(Vec2(1150, 750));
	this->addChild(closeLayerButton, 101);
	closeLayerButton->addClickEventListener([=](Ref* sender) {
		// �Ƴ�Layer
		gamesettings->removeFromParentAndCleanup(true);
		closeLayerButton->removeFromParentAndCleanup(true);
		});
}



void playerScene::updateTimer(float dt)
{
	timeLeft--;

	if (timeLeft >= 0)
	{
		// ���±�ǩ��ʾ
	//	label->setString(StringUtils::format("Time: %d", timeLeft));
	}
	else
	{
		// ʱ�䵽��ִ�г����л�����
		unschedule("update_key");
		fight = true;


		auto playerfightscene = playerfightScene::create();
		auto fadeIn = TransitionFade::create(1.0f, playerfightscene, Color3B::BLACK);
		Director::getInstance()->pushScene(fadeIn);
	}
}