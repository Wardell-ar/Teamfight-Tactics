#include"heroSprite.h"
#include<vector>
#include"chessboardSeat.h"
#include"preparationSeat.h"
#include "cocos/audio/include/AudioEngine.h"

extern chessboardSeat seat1;
extern preparationSeat seat2;

int fight = 0;
Vector<Hero*> allMyHeroes;//我方所有英雄
Vector<Hero*> allEnemyHeroes;//敌方所有英雄

Hero::Hero()
{
    max_blood = blood = 100;
    each_magic = 34;
    start_magic = 0;
    magic = 0;
    level = 1;
    camp = -1;
    heroType = -1;
    weapon = -1;
    power = 10;
    skill = 20;
    inBoard = 0;
    Die = 0;
    seatIndex = -1;
}

// 创建不同类型的英雄
Hero* Hero::createHero(int heroType, const Vec2& position, int camp)
{
    Hero* hero = new Hero();
    if (camp == 1) {
        allMyHeroes.pushBack(hero);
        //此处开始加入蓝条血条(！！当可以实现分辨是否在棋盘上时加入判断条件，使在备战席上不生成血条)
        auto bloodbar1 = Sprite::create("bloodbar1.png");
        auto bloodbar0 = Sprite::create("bloodbar0.png");

        hero->healthBar = ProgressTimer::create(bloodbar1);
        hero->healthBar->setType(ProgressTimer::Type::BAR);
        hero->healthBar->setMidpoint(Vec2(0, 0.5));
        hero->healthBar->setBarChangeRate(Vec2(1, 0));
        // 将 healthBar 添加到 mySprite 中
        hero->addChild(hero->healthBar, 1);
        hero->addChild(bloodbar0, 0);
        hero->healthBar->setPosition(200, 400);
        bloodbar0->setPosition(200, 400);
        // 设置血条初始进度
        hero->healthBar->setPercentage(100);  //满血
        //加蓝条
        hero->magicBar = ProgressTimer::create(Sprite::create("magicbar.png"));
        hero->magicBar->setType(ProgressTimer::Type::BAR);
        hero->magicBar->setMidpoint(Vec2(0, 0.5));
        hero->magicBar->setBarChangeRate(Vec2(1, 0));
        // 将 healthBar 添加到 mySprite 中
        hero->addChild(hero->magicBar);
        hero->magicBar->setPosition(200, 350);
        // 设置蓝条初始进度
        hero->magicBar->setPercentage(hero->magic);
    }
    else
    {
        allEnemyHeroes.pushBack(hero);
        //此处开始加入蓝条血条(！！当可以实现分辨是否在棋盘上时加入判断条件，使在备战席上不生成血条)
        auto bloodbar1 = Sprite::create("bloodbar11.png");
        auto bloodbar0 = Sprite::create("bloodbar0.png");
        bloodbar1->setColor(Color3B::RED);
        hero->healthBar = ProgressTimer::create(bloodbar1);
        hero->healthBar->setType(ProgressTimer::Type::BAR);
        hero->healthBar->setMidpoint(Vec2(0, 0.5));
        hero->healthBar->setBarChangeRate(Vec2(1, 0));
        // 将 healthBar 添加到 mySprite 中
        hero->addChild(hero->healthBar, 1);
        hero->addChild(bloodbar0, 0);
        hero->healthBar->setPosition(200, 400);
        bloodbar0->setPosition(200, 400);
        // 设置血条初始进度
        hero->healthBar->setPercentage(100);  //满血
        //加蓝条
        hero->magicBar = ProgressTimer::create(Sprite::create("magicbar.png"));
        hero->magicBar->setType(ProgressTimer::Type::BAR);
        hero->magicBar->setMidpoint(Vec2(0, 0.5));
        hero->magicBar->setBarChangeRate(Vec2(1, 0));
        // 将 healthBar 添加到 mySprite 中
        hero->addChild(hero->magicBar);
        hero->magicBar->setPosition(200, 350);
        // 设置蓝条初始进度
        hero->magicBar->setPercentage(hero->magic);
    }

    if (hero)
    {
        hero->autorelease();
        hero->camp = camp;  // 设置阵营
        // 根据不同类型初始化英雄属性
        switch (heroType)
        {
            case 1:
                // 初始化为第一种类型的英雄--小黑子（普攻小篮球，大招大篮球）(1)
                hero->initWithFile("hero1.png");
                // 可以根据实际需求再调整血量、蓝条、等级等属性
                hero->max_blood = 500;
                hero->blood = 500;
                hero->each_magic = 20;
                hero->power = 40;
                hero->skill = 80;
                hero->weapon = 1;
                hero->heroType = 1;

                break;

            case 2:
                //五条悟(普攻小能量球，大招大能量球）(5)
                hero->initWithFile("hero2.png");
                hero->max_blood = 780;
                hero->blood = 780;
                hero->each_magic = 34;
                hero->start_magic = 0;
                hero->power = 45;
                hero->skill = 123;
                hero->weapon = 1;
                hero->heroType = 2;
                break;
            case 3:
                //鸣人（普攻近距离螺旋丸，大招近距离螺旋手里剑）(3)
                hero->initWithFile("hero3.png");
                hero->max_blood = 1200;
                hero->blood = 1200;
                hero->each_magic = 20;
                hero->power = 45;
                hero->skill = 90;
                hero->weapon = 0;
                hero->heroType = 3;
                break;
            case 4:
                //贤者（普攻小冰球，大招治疗最近队友）(2)
                hero->initWithFile("hero4.png");
                hero->max_blood = 750;
                hero->blood = 750;
                hero->each_magic = 20;
                hero->power = 45;
                hero->skill = 200;
                hero->weapon = 1;
                hero->heroType = 4;
                break;
            case 5:
                //路飞（普攻转一圈，大招变大转一圈）(2)
                hero->initWithFile("hero5.png");
                hero->max_blood = 810;
                hero->blood = 810;
                hero->each_magic = 10;
                hero->start_magic = 50;
                hero->magic = 50;
                hero->power = 55;
                hero->skill = 169;
                hero->weapon = 0;
                hero->heroType = 5;
                break;
            case 6:
                //科比（普攻铁肘，大招变成直升机冲撞）(4)
                hero->initWithFile("hero6.png");
                hero->max_blood = 1200;
                hero->blood = 1200;
                hero->each_magic = 10;
                hero->start_magic = 40;
                hero->magic = 40;
                hero->power = 75;
                hero->skill = 200;
                hero->weapon = 0;
                hero->heroType = 6;
                break;
            default:
                break;
        }
        hero->setPosition(position);
        //保持输出的大小
        hero->setScale(0.15);
        return hero;
    }

    CC_SAFE_DELETE(hero);
    return nullptr;
}

// 移动方法
void Hero::move(Vec2 destination)
{
    // 使用Cocos引擎提供的动作类来实现移动
    auto moveTo = MoveTo::create(1.0f, destination);
    this->runAction(moveTo);
}


// 合成方法
void Hero::mergeHeroes()
{
    //每次聚焦于同一级英雄
    for (int i = 1; i <= 3; i++) {
        //每次聚焦于一种同名英雄
        for (int j = 1; j <= ALL_TYPE; j++) {


            int myCount = 0;
            int enemyCount = 0;
            // 遍历所有非战斗的同名英雄，按等级分类
            for (Hero* hero : allMyHeroes)
            {

                if (!(hero->isInBoard() && fight == 1) && !hero->Die && hero->getType() == j && hero->getLevel() == i) {
                    myCount++;
                }
            }
            for (Hero* hero : allEnemyHeroes)
            {

                if (!(hero->isInBoard() && fight == 1) && !hero->Die && hero->getType() == j && hero->getLevel() == i) {
                    enemyCount++;
                }
            }

            for (int k = (myCount / 3); k > 0; k--) {

                int countDown = 3;
                bool heroFind = 0;
                Vector<Hero*>heroToDelete;
                Hero* temp;
                for (Hero* hero : allMyHeroes) {



                    if (!(hero->isInBoard() && fight == 1) && !hero->Die && hero->getType() == j && hero->getLevel() == i) {
                        hero->setVisible(false);
                        if (hero->inBoard) {
                            seat1.seats[hero->seatIndex].state = 0;
                        }
                        else {
                            seat2.seats[hero->seatIndex].state = 0;
                        }

                        countDown--;
                        if ((hero->inBoard || countDown == 0) && !heroFind) {
                            hero->upgrade(i + 1);
                            hero->setVisible(true);
                            temp = hero;
                            if (hero->inBoard) {
                                seat1.seats[hero->seatIndex].state = 1;
                            }
                            else {
                                seat2.seats[hero->seatIndex].state = 1;
                            }
                            heroFind = 1;
                        }
                        else {
                            heroToDelete.pushBack(hero);
                        }
                    }
                    if (countDown <= 0) {
                        break;
                    }
                }
                //删除另外两个英雄
                for (Hero* hero : heroToDelete) {
                    temp->equip_blood += hero->equip_blood;
                    temp->equip_power += hero->equip_power;
                    temp->equip_magic += hero->equip_magic;
                    allMyHeroes.eraseObject(hero);
                    hero->removeFromParent();
                }

                // 重新进行装备提升（青刀提升不用重复）
                if (temp->equip_blood) {
                    temp->setMaxBlood(temp->getMaxBlood() + 666);
                    temp->setBlood(temp->getBlood() + 666);
                }
                if (temp->equip_power) {
                    temp->setPower(temp->getPower() + 100);
                }

            }

            for (int k = (enemyCount / 3); k > 0; k--) {

                int countDown = 3;
                bool heroFind = 0;
                Vector<Hero*>heroToDelete;
                for (Hero* hero : allEnemyHeroes) {



                    if (!(hero->isInBoard() && fight == 1) && !hero->Die && hero->getType() == j && hero->getLevel() == i) {
                        hero->setVisible(false);
                        if (hero->inBoard) {
                            seat1.seats[hero->seatIndex].state = 0;
                        }
                        else {
                            seat2.seats[hero->seatIndex].state = 0;
                        }
                        countDown--;
                        if ((hero->inBoard || countDown == 0) && !heroFind) {
                            hero->upgrade(i + 1);
                            hero->setVisible(true);
                            if (hero->inBoard) {
                                seat1.seats[hero->seatIndex].state = 1;
                            }
                            else {
                                seat2.seats[hero->seatIndex].state = 1;
                            }
                            heroFind = 1;
                        }
                        else {
                            heroToDelete.pushBack(hero);
                        }

                    }
                    if (countDown <= 0) {
                        break;
                    }
                }
                //删除另外两个英雄
                for (Hero* hero : heroToDelete) {
                    allEnemyHeroes.eraseObject(hero);
                    hero->removeFromParent();
                }
            }


        }
    }
}


// Getter 和 Setter 方法
int Hero::getLevel() const { return level; }

void Hero::upgrade(int newLevel) {
    level = newLevel;
    switch (heroType) {
        case 1:
            if (newLevel == 2)
            {
                max_blood = 850;
                blood = 850;
                power = 60;
                skill = 180;
            }
            else {
                max_blood = 1500;
                blood = 1500;
                power = 90;
                skill = 405;
            }
            break;
        case 2:
            if (newLevel == 2)
            {
                max_blood = 1320;
                blood = 1320;
                power = 65;
                skill = 266;
            }
            else {
                max_blood = 2330;
                blood = 2330;
                power = 95;
                skill = 1368;
            }
            break;
        case 3:
            if (newLevel == 2)
            {
                max_blood = 2000;
                blood = 2000;
                power = 68;
                skill = 210;
            }
            else {
                max_blood = 3300;
                blood = 3300;
                power = 101;
                skill = 400;
            }
            break;
        case 4:
            if (newLevel == 2)
            {
                max_blood = 1300;
                blood = 1300;
                power = 68;
                skill = 350;
            }
            else {
                max_blood = 2300;
                blood = 2300;
                power = 101;
                skill = 1000;
            }
            break;
        case 5:
            if (newLevel == 2)
            {
                max_blood = 1410;
                blood = 1410;
                power = 83;
                skill = 273;
            }
            else {
                max_blood = 2500;
                blood = 2500;
                power = 101;
                skill = 400;
            }
            break;
        case 6:
            if (newLevel == 2)
            {
                max_blood = 2000;
                blood = 2000;
                power = 113;
                skill = 400;
            }
            else {
                max_blood = 4000;
                blood = 4000;
                power = 169;
                skill = 1000;
            }
            break;
    }

    setScale(0.10 + level * 0.05);

}

int Hero::getType()const { return heroType; }


// 进入棋盘
void Hero::enterBoard()
{
    inBoard = true;
}

// 退出棋盘
void Hero::exitBoard()
{
    inBoard = false;
}

// 是否处于棋盘
bool Hero::isInBoard() const
{
    return inBoard;
}


//获取近战还是远程
int Hero::getWeapon() const
{
    return weapon;
}


// 攻击方法，攻击指定目标
void Hero::attack(Hero* target)
{
    // 获取敌我英雄位置
    Vec2 myPosition = this->getPosition();
    Vec2 enemyPosition = target->getPosition();


    //如果攻击发起方是远程
    if (weapon) {



        // 在我方英雄位置生成一支飞箭的图片
        auto arrow = Sprite::create("arrow.png"); // 请替换为实际的箭头图片路径
        arrow->setScale(0.15);
        this->getParent()->addChild(arrow, 2);


        switch (heroType) {
            case 1://小黑子
                if (magic >= 100)
                {
                    arrow->setTexture("fire_arrow.png");
                    arrow->setScale(0.3);
                    AudioEngine::play2d("big_arrow.mp3");
                }
                break;
            case 2://五条悟
                arrow->setTexture("wtw_arrow.png");

                if (magic >= 100)
                {
                    arrow->setScale(0.5);
                    AudioEngine::play2d("fire_arrow.mp3");
                }
                else {
                    arrow->setScale(0.15);
                    arrow->setColor(Color3B(0, 0, 255));
                }

                break;
            case 4://奶妈
                arrow->setTexture("sage_arrow.png");
                arrow->setScale(0.15);
                if (magic >= 100) {
                    AudioEngine::play2d("heal.mp3");
                    Hero* friendTarget;
                    Vec2 friendPosition;
                    int lowestBlood = 101;
                    if (camp) {
                        for (Hero* friendHero : allMyHeroes) {
                            if (friendHero->isInBoard() && !friendHero->isDead()) {
                                if ((friendHero->getBlood() / friendHero->getMaxBlood()) * 100 < lowestBlood) {
                                    lowestBlood = (friendHero->getBlood() / friendHero->getMaxBlood()) * 100;
                                    friendTarget = friendHero;
                                    friendPosition = friendHero->getPosition();
                                }
                            }
                        }
                    }
                    else {
                        for (Hero* friendHero : allEnemyHeroes) {
                            if (friendHero->isInBoard() && !friendHero->isDead()) {
                                if ((friendHero->getBlood() / friendHero->getMaxBlood()) * 100 < lowestBlood) {
                                    lowestBlood = (friendHero->getBlood() / friendHero->getMaxBlood()) * 100;
                                    friendTarget = friendHero;
                                    friendPosition = friendHero->getPosition();
                                }
                            }
                        }
                    }
                    arrow->setColor(Color3B(0, 255, 0));
                    arrow->setPosition(myPosition);
                    auto moveTo = MoveTo::create(0.5f, friendPosition);

                    auto heal = Sprite::create("heal.png");
                    this->getParent()->addChild(heal, 2);
                    heal->setPosition(friendPosition);
                    heal->setScale(0.50);

                    auto healCallback = CallFunc::create([this, friendTarget]() {
                        friendTarget->setBlood((friendTarget->getBlood() + skill) > friendTarget->getMaxBlood() ? friendTarget->getMaxBlood() : (friendTarget->getBlood() + skill));
                    this->magic = 0;

                        });


                    //飞箭消失
                    auto disappearCallback = CallFunc::create([arrow, heal]() {
                        // 从场景中移除
                        heal->removeFromParentAndCleanup(true);
                    arrow->removeFromParentAndCleanup(true);
                        });

                    // 创建一个序列动作，先移动并消失，然后执行回调
                    auto sequence = Sequence::create(moveTo, healCallback, disappearCallback, nullptr);
                    arrow->runAction(sequence);
                    return;
                }

                break;

        }
        arrow->setPosition(myPosition);

        // 创建移动动作，一秒后挪到敌方英雄位置
        auto moveTo = MoveTo::create(0.5f, enemyPosition);



        if (magic < 100)
            AudioEngine::setVolume(AudioEngine::play2d("arrow.mp3"), 0.05);



        // 示例：减少目标血量
        auto attackCallback = CallFunc::create([this, target]() {

            if (magic >= 100) {
                target->decreaseHealth(skill);  //技能伤害
                magic = 0;
            }

            else {
                target->decreaseHealth(power);
                magic += each_magic;
            }

            });


        //飞箭消失
        auto disappearCallback = CallFunc::create([arrow]() {
            // 从场景中移除
            arrow->removeFromParentAndCleanup(true);
            });

        // 创建一个序列动作，先移动并消失，然后执行回调
        auto sequence = Sequence::create(moveTo, attackCallback, disappearCallback, nullptr);

        // 运行飞箭动作
        arrow->runAction(sequence);

    }
    else {  //近战

        Vec2 closePosition;
        if (target->getWeapon()) {
            closePosition.x = enemyPosition.x + ((myPosition.x > enemyPosition.x) ? 10 : -10);
            closePosition.y = enemyPosition.y + ((myPosition.y > enemyPosition.y) ? 10 : -10);
        }
        else {
            closePosition.x = (myPosition.x + enemyPosition.x) / 2 + ((myPosition.x > enemyPosition.x) ? 10 : -10);
            closePosition.y = (myPosition.y + enemyPosition.y) / 2 + ((myPosition.y > enemyPosition.y) ? 10 : -10);
        }
        if (magic >= 100) {
            switch (heroType) {
                case 3:
                    this->setTexture("asg.png");
                    setScale(0.5);
                    AudioEngine::play2d("spin.mp3");
                    break;
                case 5:
                    this->setTexture("5gear.png");
                   
                    AudioEngine::setVolume(AudioEngine::play2d("laugh.mp3"), 1);
                    setScale(0.5);
                    break;
                case 6:
                    this->setTexture("helicapter.png");
                    setScale(0.25);
                    AudioEngine::play2d("bomb.mp3");
                    break;
            }
        }
        else {
            int audioId = AudioEngine::play2d("fight.mp3");
            AudioEngine::setVolume(audioId, 1);
        }
        // 创建移动动作，一秒后挪到敌方英雄位置
        auto moveTo = MoveTo::create(0.5f, closePosition);
        // 创建旋转动作，参数为旋转的角度，360度即一圈
        //auto rotateAction = RotateBy::create(0.5f, 360.0f);
        auto shakeAction = Sequence::create(
            RotateBy::create(0.05f, 20.0f),
            RotateBy::create(0.1f, -40.0f),
            RotateBy::create(0.1f, 40.0f),
            RotateBy::create(0.1f, -40.0f),
            RotateBy::create(0.05f, 20.0f),
            nullptr
        );
        // 示例：减少目标血量
        auto attackCallback = CallFunc::create([this, target]() {
            if (magic >= 100)
            {
                target->decreaseHealth(skill);
                magic = 0;
                switch (heroType) {
                    case 3:
                        this->setTexture("hero3.png");
                        setScale(0.10 + level * 0.05);
                        break;
                    case 5:
                        this->setTexture("hero5.png");
                        setScale(0.10 + level * 0.05);
                        break;
                    case 6:
                        this->setTexture("hero6.png");
                        setScale(0.10 + level * 0.05);
                        break;
                }
            }
            else
            {
                target->decreaseHealth(power);
                magic += each_magic;
            }


            });

        auto moveBack = MoveTo::create(0.5f, myPosition);
        if (heroType == 3 && magic >= 100) {
            Vec2 newPosition = Vec2(closePosition.x, closePosition.y + 50);
            auto moveTo = MoveTo::create(0.5f, newPosition);

            auto beforeRotate = CallFunc::create([this]() {
                for (auto node : this->getChildren()) {
                    node->setVisible(false);
                }
                });
            auto rotateAction = RotateBy::create(0.5f, 720.0f);
            auto afterRotate = CallFunc::create([this]() {
                for (auto node : this->getChildren()) {
                    node->setVisible(true);
                }
                });
            auto sequence = Sequence::create(beforeRotate, moveTo, rotateAction, afterRotate, attackCallback, moveBack, nullptr);
            this->runAction(sequence);
            return;
        }
        if (heroType == 5 && magic >= 100) {



            auto beforeRotate = CallFunc::create([this]() {
                for (auto node : this->getChildren()) {
                    node->setVisible(false);
                }
                });
            auto rotateAction = RotateBy::create(0.5f, 720.0f);
            auto afterRotate = CallFunc::create([this]() {
                for (auto node : this->getChildren()) {
                    node->setVisible(true);
                }
                });
            auto sequence = Sequence::create(beforeRotate, moveTo, shakeAction, afterRotate, attackCallback, moveBack, nullptr);
            this->runAction(sequence);
            return;
        }
        if (heroType == 6 && magic >= 100) {
            auto beforeRotate = CallFunc::create([this]() {
                for (auto node : this->getChildren()) {
                    node->setVisible(false);
                }
                });

            auto afterRotate = CallFunc::create([this]() {
                for (auto node : this->getChildren()) {
                    node->setVisible(true);
                }
                });
            auto scaleAction = ScaleTo::create(0.25f, 1.0f);
            auto bombCallback = CallFunc::create([this]() {
                this->setTexture("bomb.png");
            setScale(1.0);
            this->setOpacity(0);
                });
            auto appear = FadeIn::create(0.25f);

            auto sequence = Sequence::create(beforeRotate, moveTo, scaleAction, bombCallback, appear, afterRotate, attackCallback, moveBack, nullptr);
            this->runAction(sequence);
            return;
        }


        auto sequence = Sequence::create(moveTo, shakeAction, attackCallback, moveBack, nullptr);
        this->runAction(sequence);

    }
}


// 减少血量方法
void Hero::decreaseHealth(int amount)
{
    blood -= amount;
    // 如果血量降低到0以下，则死亡
    if (blood <= 0)
    {
        this->die();
    }
}

// 死亡方法
void Hero::die()
{
    // 在这里可以添加死亡动画等逻辑
    // ...

    Die = 1;
    // 创建变灰色动作
    auto grayAction = TintTo::create(0.5f, 0, 0, 0); // 将图片颜色渐变为黑色，可以根据需要调整时间和颜色

    // 创建一个回调动作，在变灰色动作完成后执行消失逻辑
    auto disappearCallback = CallFunc::create([this]() {
        // 示例：从场景中移除

        this->setVisible(false);

        });

    // 创建一个序列动作，先变灰色，然后执行回调
    auto sequence = Sequence::create(grayAction, disappearCallback, nullptr);

    // 运行序列动作
    this->runAction(sequence);

}

// 获取阵营
int Hero::getCamp() const
{
    return camp;
}

// 获取血量
float Hero::getBlood()
{
    return blood;
}

void Hero::setIndex(int index) {
    seatIndex = index;
}

void Hero::updatebloodandmagic() {
    healthBar->setPercentage(blood / max_blood * 100.0f);
    magicBar->setPercentage(magic);
}