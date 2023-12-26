#include <random>
#include"cocos2d.h"
#include<string>
#include"playerScene.h"

extern chessboardSeat seat1;
extern preparationSeat seat2;
extern Vector<Hero*> allMyHeroes;//我方所有英雄
extern Vector<Hero*> allEnemyHeroes;//敌方所有英雄

storeLayer* storeLayer::createLayer() {
	return storeLayer::create();
}

bool storeLayer::init() {
	if (!Layer::init()) {
		return false;
	}

    // 初始化金币、经验值、等级
    gold = 50; // 初始金币数量
    exp = 0;
    level = 1;


    //创建商店背景 
    auto store = Sprite::create("store1.png");
    store->setPosition(960, 120);
    store->setOpacity(200);
    store->setScale(0.4);
    store->setScaleY(0.3);
    this->addChild(store);

    // 创建金币、等级标签
    goldLabel = Label::createWithTTF("Gold: " + std::to_string(gold), "fonts/arial.ttf", 24);
    levelLabel = Label::createWithTTF("Level: " + std::to_string(level), "fonts/arial.ttf", 24);
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
    upgradeButton = MenuItemImage::create("uplevel.png", "uplevel1.png",
        CC_CALLBACK_1(storeLayer::onUpgradeButtonClicked, this));

    
    //升级按钮的禁用
    this->schedule([this](float dt) {
        if (level == 5) {
            upgradeButton->setEnabled(false);  //禁用升级按键
            this->unschedule("cutupgrade");
        }
    }, "cutupgrade");

    // 创建刷新按钮
    auto refreshButton = MenuItemImage::create("refresh.png", "refresh1.png",
        CC_CALLBACK_1(storeLayer::onRefreshButtonClicked, this));
    auto storeMenu = Menu::create(upgradeButton, refreshButton, nullptr);
    storeMenu->alignItemsVerticallyWithPadding(15);  //设置垂直布局
    storeMenu->setPosition(-380, -280);//在场景中的布局
    storeMenu->setScale(0.3);
    this->addChild(storeMenu);

    createHeroButtons();

    updateUI(); // 初始化UI显示

	return true;
}

void storeLayer::updateUI() {
    // 更新金币、等级标签和经验条显示
    goldLabel->setString("Gold: " + std::to_string(gold));
    levelLabel->setString("Level: " + std::to_string(level));
    expBar->setPercent(20 * exp);
}

void storeLayer::upgrade() {
    // 升级操作
    if (gold >= 4) {
        gold -= 4;
        exp++;
        if (exp >= 5) {
            level++;
            exp = 0;
        }
        updateUI(); // 更新UI显示
    }
}

void storeLayer::refresh() {
    // 刷新操作
    if (gold >= 2) {
        gold -= 2;
        // 实现刷新逻辑，这里简化为将经验条清零
        createHeroButtons();
        updateUI(); // 更新UI显示
    }
}

void storeLayer::onUpgradeButtonClicked(Ref* sender) {
    // 升级按钮点击事件
    upgrade();
}

void storeLayer::onRefreshButtonClicked(Ref* sender) {
    // 刷新按钮点击事件
    refresh();
}


//五个英雄按键
void storeLayer::createHeroButtons() {
    srand(std::time(0));

    //第一个按钮
    if (heroButton1 != nullptr) {
        heroButton1->removeFromParent();
    }
    int randnum = rand() % 6 + 1;
    switch (randnum) {
        case 1:
            heroButton1 = ui::Button::create("storehero1.png");
            break;
        case 2:
            heroButton1 = ui::Button::create("storehero2.png");
            break;
        case 3:
            heroButton1 = ui::Button::create("storehero3.png");
            break;
        case 4:
            heroButton1 = ui::Button::create("storehero4.png");
            break;
        case 5:
            heroButton1 = ui::Button::create("storehero5.png");
            break;
        case 6:
            heroButton1 = ui::Button::create("storehero6.png");
            break;
    }
    heroButton1->setPosition(Point(500, 100));
    heroButton1->setScale(0.4);
    heroButton1->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 0));
    this->addChild(heroButton1);
    herotype[0] = randnum;

    //第二个按钮
    if (heroButton2 != nullptr) {
        heroButton2->removeFromParent();
    }
    randnum = rand() % 6 + 1;
    switch (randnum) {
        case 1:
            heroButton2 = ui::Button::create("storehero1.png");
            break;
        case 2:
            heroButton2 = ui::Button::create("storehero2.png");
            break;
        case 3:
            heroButton2 = ui::Button::create("storehero3.png");
            break;
        case 4:
            heroButton2 = ui::Button::create("storehero4.png");
            break;
        case 5:
            heroButton2 = ui::Button::create("storehero5.png");
            break;
        case 6:
            heroButton2 = ui::Button::create("storehero6.png");
            break;
    }
    heroButton2->setPosition(Point(500 + 128, 100));
    heroButton2->setScale(0.4);
    heroButton2->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 1));
    this->addChild(heroButton2);
    herotype[1] = randnum;

    //第三个按钮
    if (heroButton3 != nullptr) {
        heroButton3->removeFromParent();
    }
    randnum = rand() % 6 + 1;
    switch (randnum) {
        case 1:
            heroButton3 = ui::Button::create("storehero1.png");
            break;
        case 2:
            heroButton3 = ui::Button::create("storehero2.png");
            break;
        case 3:
            heroButton3 = ui::Button::create("storehero3.png");
            break;
        case 4:
            heroButton3 = ui::Button::create("storehero4.png");
            break;
        case 5:
            heroButton3 = ui::Button::create("storehero5.png");
            break;
        case 6:
            heroButton3 = ui::Button::create("storehero6.png");
            break;
    }
    heroButton3->setPosition(Point(500 + 128 * 2, 100));
    heroButton3->setScale(0.4);
    heroButton3->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 2));
    this->addChild(heroButton3);
    herotype[2] = randnum;

    //第四个按钮
    if (heroButton4 != nullptr) {
        heroButton4->removeFromParent();
    }
    randnum = rand() % 6 + 1;
    switch (randnum) {
        case 1:
            heroButton4 = ui::Button::create("storehero1.png");
            break;
        case 2:
            heroButton4 = ui::Button::create("storehero2.png");
            break;
        case 3:
            heroButton4 = ui::Button::create("storehero3.png");
            break;
        case 4:
            heroButton4 = ui::Button::create("storehero4.png");
            break;
        case 5:
            heroButton4 = ui::Button::create("storehero5.png");
            break;
        case 6:
            heroButton4 = ui::Button::create("storehero6.png");
            break;
    }
    heroButton4->setPosition(Point(500 + 128 * 3, 100));
    heroButton4->setScale(0.4);
    heroButton4->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 3));
    this->addChild(heroButton4);
    herotype[3] = randnum;

    //第五个按钮
    if (heroButton5 != nullptr) {
        heroButton5->removeFromParent();
    }
    randnum = rand() % 6 + 1;
    switch (randnum) {
        case 1:
            heroButton5 = ui::Button::create("storehero1.png");
            break;
        case 2:
            heroButton5 = ui::Button::create("storehero2.png");
            break;
        case 3:
            heroButton5 = ui::Button::create("storehero3.png");
            break;
        case 4:
            heroButton5 = ui::Button::create("storehero4.png");
            break;
        case 5:
            heroButton5 = ui::Button::create("storehero5.png");
            break;
        case 6:
            heroButton5 = ui::Button::create("storehero6.png");
            break;
    }
    heroButton5->setPosition(Point(500 + 128 * 4, 100));
    heroButton5->setScale(0.4);
    heroButton5->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 4));
    this->addChild(heroButton5);
    herotype[4] = randnum;
}


void storeLayer::onHeroButtonClicked(Ref* sender, int buttonIndex) {
    for (int i = 0; i < 9; i++) {
        if (seat2.seats[i].IsEmpty()) {
            if (gold >= herocost[herotype[buttonIndex]]) {

                //金币减少
                gold -= herocost[herotype[buttonIndex]];
                updateUI();  //刷新

                //英雄显示在备战席
                auto hero = Hero::createHero(herotype[buttonIndex], Vec2(seat2.seats[i].x + 70, seat2.seats[i].y + 50), 1);
                this->getParent()->addChild(hero, 2);
                seat2.seats[i].Setsprite();
                hero->setIndex(i);

                //按键消失
                switch (buttonIndex) {
                    case 0:
                        heroButton1->removeFromParent();
                        delete heroButton1;
                        heroButton1 = nullptr;
                        break;
                    case 1:
                        heroButton2->removeFromParent();
                        delete heroButton2;
                        heroButton2 = nullptr;
                        break;
                    case 2:
                        heroButton3->removeFromParent();
                        delete heroButton3;
                        heroButton3 = nullptr;
                        break;
                    case 3:
                        heroButton4->removeFromParent();
                        delete heroButton4;
                        heroButton4 = nullptr;
                        break;
                    case 4:
                        heroButton5->removeFromParent();
                        delete heroButton5;
                        heroButton5 = nullptr;
                        break;
                }

                Hero::mergeHeroes();

                break;

            }
        }
    }
}

