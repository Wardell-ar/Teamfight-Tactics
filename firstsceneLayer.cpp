#include <random>
#include"firstsceneLayer.h"

bool firstsceneLayer::init() {
	if (!Layer::init()) {   //�������ʼ������
		return false;
	}
	auto Background = Sprite::create("map1.png");
	Background->setPosition(960, 540);
	this->addChild(Background, 0);//��ӱ���ͼ

	auto store = Sprite::create("store1.png");
	store->setPosition(960,120);
	store->setOpacity(200);
	store->setScale(0.4);
	store->setScaleY(0.3);
	this->addChild(store, 1);

	return true;
}


bool ShopLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // ��ʼ����ҡ�����ֵ���ȼ�
    gold = 100; // ��ʼ�������
    exp = 0;
    level = 1;
    herocost = 2;

    // ������ҡ��ȼ���ǩ
    goldLabel = Label::createWithTTF("Gold: " + to_string(gold), "fonts/arial.ttf", 24);
    levelLabel = Label::createWithTTF("Level: " + to_string(level), "fonts/arial.ttf", 24);
    goldLabel->setPosition(960, 180);
    levelLabel->setPosition(210, 180);
    this->addChild(goldLabel);
    this->addChild(levelLabel);

    // ����������
    expBar = ui::LoadingBar::create("LoadingBarFile.png");
    expBar->setDirection(ui::LoadingBar::Direction::LEFT);
    expBar->setPosition(Point(350, 180));
    this->addChild(expBar);

    // ����������ť
    auto upgradeButton = MenuItemImage::create("uplevel.png", "uplevel1.png",
        CC_CALLBACK_1(ShopLayer::onUpgradeButtonClicked, this));

    // ����ˢ�°�ť
    auto refreshButton = MenuItemImage::create("refresh.png", "refresh1.png",
        CC_CALLBACK_1(ShopLayer::onRefreshButtonClicked, this));
    auto storeMenu = Menu::create(upgradeButton,refreshButton, nullptr);
    storeMenu->alignItemsVerticallyWithPadding(15);  //���ô�ֱ����
    storeMenu->setPosition(-380, -280);//�ڳ����еĲ���
    storeMenu->setScale(0.3);
    this->addChild(storeMenu);

    createHeroButtons();

    updateUI(); // ��ʼ��UI��ʾ

    return true;
}

void ShopLayer::updateUI() {
    // ���½�ҡ��ȼ���ǩ�;�������ʾ
    goldLabel->setString("Gold: " + std::to_string(gold));
    levelLabel->setString("Level: " + std::to_string(level));
    expBar->setPercent(static_cast<float>(exp) / (level * 10) * 100);
}

void ShopLayer::upgrade() {
    // ��������
    if (gold >= 4) {
        gold -= 4;
        exp++;
        if (exp >= level * 10) {
            level++;
            exp = 0;
        }
        updateUI(); // ����UI��ʾ
    }
}

void ShopLayer::refresh() {
    // ˢ�²���
    if (gold >= 2) {
        gold -= 2;
        // ʵ��ˢ���߼��������Ϊ������������
        createHeroButtons();
        updateUI(); // ����UI��ʾ
    }
}

void ShopLayer::onUpgradeButtonClicked(Ref* sender) {
    // ������ť����¼�
    upgrade();
}

void ShopLayer::onRefreshButtonClicked(Ref* sender) {
    // ˢ�°�ť����¼�
    refresh();
}

void ShopLayer::createHeroButtons() {
    srand(std::time(0));


    // ����Ӣ�۰�ť1
    heroButton1 = ui::Button::create("hero1_button.png", "hero1_button_pressed.png");
    heroButton1->setPosition(Point(500, 100));
    heroButton1->setScale(0.4);
    heroButton1->addClickEventListener(CC_CALLBACK_1(ShopLayer::onHeroButtonClicked, this, 1));
    this->addChild(heroButton1);

    // ����Ӣ�۰�ť2
    heroButton2 = ui::Button::create("hero_button.png","hero_button_selected.png", "hero_button_pressed.png");
    heroButton2->setPosition(Point(500, 150));
    heroButton2->addClickEventListener(CC_CALLBACK_1(ShopLayer::onHeroButtonClicked, this, 2));
    this->addChild(heroButton2);



}


void ShopLayer::onHeroButtonClicked(Ref* sender, int heroIndex) {
    if (gold >= herocost) {
        gold -= herocost;
        updateUI();

        /*spawnHero(heroIndex);*/

        // ������ѡ���Ӣ�۰�ť
        if (heroIndex == 1) {
            heroButton1->setEnabled(false);
        }
        else if (heroIndex == 2) {
            heroButton2->setEnabled(false);
        }
    }
}