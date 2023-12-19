#include <random>
#include"firstsceneLayer.h"

bool firstsceneLayer::init() {
	if (!Layer::init()) {   //若父类初始化出错
		return false;
	}
	auto Background = Sprite::create("map1.png");
	Background->setPosition(960, 540);
	this->addChild(Background, 0);//添加背景图

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

    // 初始化金币、经验值、等级
    gold = 100; // 初始金币数量
    exp = 0;
    level = 1;
    herocost = 2;

    // 创建金币、等级标签
    goldLabel = Label::createWithTTF("Gold: " + to_string(gold), "fonts/arial.ttf", 24);
    levelLabel = Label::createWithTTF("Level: " + to_string(level), "fonts/arial.ttf", 24);
    goldLabel->setPosition(960, 180);
    levelLabel->setPosition(210, 180);
    this->addChild(goldLabel);
    this->addChild(levelLabel);

    // 创建经验条
    expBar = ui::LoadingBar::create("LoadingBarFile.png");
    expBar->setDirection(ui::LoadingBar::Direction::LEFT);
    expBar->setPosition(Point(350, 180));
    this->addChild(expBar);

    // 创建升级按钮
    auto upgradeButton = MenuItemImage::create("uplevel.png", "uplevel1.png",
        CC_CALLBACK_1(ShopLayer::onUpgradeButtonClicked, this));

    // 创建刷新按钮
    auto refreshButton = MenuItemImage::create("refresh.png", "refresh1.png",
        CC_CALLBACK_1(ShopLayer::onRefreshButtonClicked, this));
    auto storeMenu = Menu::create(upgradeButton,refreshButton, nullptr);
    storeMenu->alignItemsVerticallyWithPadding(15);  //设置垂直布局
    storeMenu->setPosition(-380, -280);//在场景中的布局
    storeMenu->setScale(0.3);
    this->addChild(storeMenu);

    createHeroButtons();

    updateUI(); // 初始化UI显示

    return true;
}

void ShopLayer::updateUI() {
    // 更新金币、等级标签和经验条显示
    goldLabel->setString("Gold: " + std::to_string(gold));
    levelLabel->setString("Level: " + std::to_string(level));
    expBar->setPercent(static_cast<float>(exp) / (level * 10) * 100);
}

void ShopLayer::upgrade() {
    // 升级操作
    if (gold >= 4) {
        gold -= 4;
        exp++;
        if (exp >= level * 10) {
            level++;
            exp = 0;
        }
        updateUI(); // 更新UI显示
    }
}

void ShopLayer::refresh() {
    // 刷新操作
    if (gold >= 2) {
        gold -= 2;
        // 实现刷新逻辑，这里简化为将经验条清零
        createHeroButtons();
        updateUI(); // 更新UI显示
    }
}

void ShopLayer::onUpgradeButtonClicked(Ref* sender) {
    // 升级按钮点击事件
    upgrade();
}

void ShopLayer::onRefreshButtonClicked(Ref* sender) {
    // 刷新按钮点击事件
    refresh();
}

void ShopLayer::createHeroButtons() {
    srand(std::time(0));


    // 创建英雄按钮1
    heroButton1 = ui::Button::create("hero1_button.png", "hero1_button_pressed.png");
    heroButton1->setPosition(Point(500, 100));
    heroButton1->setScale(0.4);
    heroButton1->addClickEventListener(CC_CALLBACK_1(ShopLayer::onHeroButtonClicked, this, 1));
    this->addChild(heroButton1);

    // 创建英雄按钮2
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

        // 禁用已选择的英雄按钮
        if (heroIndex == 1) {
            heroButton1->setEnabled(false);
        }
        else if (heroIndex == 2) {
            heroButton2->setEnabled(false);
        }
    }
}