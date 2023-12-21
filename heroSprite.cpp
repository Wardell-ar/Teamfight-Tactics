#include"heroSprite.h"
#include<vector>
#include"chessboardSeat.h"
#include"preparationSeat.h"

extern chessboardSeat seat1;
extern preparationSeat seat2;

int fight = 0;
std::vector<Hero*> allMyHeroes;//我方所有英雄
std::vector<Hero*> allEnemyHeroes;//敌方所有英雄

Hero::Hero()
{
    blood = 100;
    magic = 50;
    level = 1;
    camp = -1;
    heroType = -1;
    weapon = -1;
    power = 50;
    inBattle = 0;
    inBoard = 0;
    Die = 0;
    exist = 1;
    seatIndex = -1;
}
// 创建不同类型的英雄
Hero* Hero::createHero(int heroType, const Vec2& position, int camp)
{
    Hero* hero = new Hero();
    if (camp == 1) {
        allMyHeroes.push_back(hero);
    }
    else
        allEnemyHeroes.push_back(hero);

    if (hero)
    {
        hero->autorelease();
        hero->camp = camp;  // 设置阵营
        // 根据不同类型初始化英雄属性
        switch (heroType)
        {
            case 1:
                // 初始化为第一种类型的英雄
                hero->initWithFile("hero1.png");
                // 可以根据实际需求再调整血量、蓝条、等级等属性
                hero->blood = 100;
                hero->magic = 50;
                hero->level = 1;
                hero->weapon = 0;
                hero->heroType = 1;
                break;

            case 2:

                hero->initWithFile("hero2.png");
                hero->blood = 100;
                hero->magic = 50;
                hero->level = 1;
                hero->weapon = 1;
                hero->heroType = 2;
                break;
            case 3:

                hero->initWithFile("hero3.png");
                hero->blood = 100;
                hero->magic = 50;
                hero->level = 1;
                hero->heroType = 3;
                break;
            case 4:

                hero->initWithFile("hero4.png");
                hero->blood = 100;
                hero->magic = 50;
                hero->level = 1;
                hero->heroType = 4;
                break;
            case 5:

                hero->initWithFile("hero5.png");
                hero->blood = 100;
                hero->magic = 50;
                hero->level = 1;
                hero->heroType = 5;
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

                if (!(hero->isInBattle()) && hero->exist && !hero->Die && hero->getType() == j && hero->getLevel() == i) {
                    myCount++;
                }
            }
            for (Hero* hero : allEnemyHeroes)
            {

                if (!(hero->isInBattle()) && hero->exist && !hero->Die && hero->getType() == j && hero->getLevel() == i) {
                    enemyCount++;
                }
            }

            for (int k = (myCount / 3); k > 0; k--) {

                int countDown = 3;
                bool heroFind = 0;
                for (Hero* hero : allMyHeroes) {



                    if (!(hero->isInBattle()) && hero->exist && !hero->Die && hero->getType() == j && hero->getLevel() == i) {
                        hero->exist = 0;
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
                            hero->exist = 1;
                            hero->setVisible(true);
                            if (hero->inBoard) {
                                seat1.seats[hero->seatIndex].state = 1;
                            }
                            else {
                                seat2.seats[hero->seatIndex].state = 1;
                            }
                            heroFind = 1;
                        }

                    }
                    if (countDown <= 0) {
                        break;
                    }
                }

            }

            for (int k = (enemyCount / 3); k > 0; k--) {

                int countDown = 3;
                bool heroFind = 0;
                for (Hero* hero : allEnemyHeroes) {



                    if (!(hero->isInBattle()) && hero->exist && !hero->Die && hero->getType() == j && hero->getLevel() == i) {
                        hero->exist = 0;
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
                            hero->exist = 1;
                            hero->setVisible(true);
                            if (hero->inBoard) {
                                seat1.seats[hero->seatIndex].state = 1;
                            }
                            else {
                                seat2.seats[hero->seatIndex].state = 1;
                            }
                            heroFind = 1;
                        }

                    }
                    if (countDown <= 0) {
                        break;
                    }
                }

            }


        }
    }
}

// Getter 和 Setter 方法
int Hero::getLevel() const { return level; }
void Hero::upgrade(int newLevel) {
    level = newLevel;
    blood *= 2;
    magic *= 2;
    power *= 2;
    setScale(0.10 + level * 0.05);
    
}
int Hero::getType()const { return heroType; }

// 进入战斗状态
void Hero::enterBattle()
{
    inBattle = true;
}

// 退出战斗状态
void Hero::exitBattle()
{
    inBattle = false;
}

// 是否处于战斗状态
bool Hero::isInBattle() const
{
    return inBattle;
}

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

// 创建一个包含原有动作和新动作的 Spawn
Spawn* Hero::addAdditionalActionToSpawn(Spawn* originalSpawn, FiniteTimeAction* additionalAction) {
    // 创建一个新的 Spawn，包括原有动作和新动作
    auto combinedSpawn = Spawn::create(additionalAction, originalSpawn, nullptr);

    return combinedSpawn;
}

// 攻击方法
void Hero::attack()
{
    fight = 1;
    // 根据阵营将所有处于战斗状态的英雄分别存储到两个堆里面
    std::vector<Hero*> myHeroes;
    std::vector<Hero*> enemyHeroes;

    // 遍历所有战斗英雄

    // 你需要根据实际情况修改
    for (auto hero : allMyHeroes)
    {
        if (hero->isInBattle() && hero->exist)
        {
            myHeroes.push_back(hero);

        }
    }
    for (auto hero : allEnemyHeroes)
    {
        if (hero->isInBattle() && hero->exist)
        {
            enemyHeroes.push_back(hero);
        }
    }




    
        bool attacked_1 = 0;
        bool attacked_2 = 0;
        //我方攻击动作
        for (auto myHero : myHeroes)
        {
            if (!myHero->Die) {
                Hero* target = enemyHeroes.front();
                bool targetFind = 0;
                long long nearst_distance = 99999999999;
                for (auto enemyHero : enemyHeroes) {
                    if (!enemyHero->Die) {
                        targetFind = 1;
                        long long x_distance = myHero->getPosition().x - enemyHero->getPosition().x;
                        long long y_distance = myHero->getPosition().y - enemyHero->getPosition().y;
                        long long distance = pow(x_distance, 2) + pow(y_distance, 2);
                        if (distance < nearst_distance) {
                            target = enemyHero;
                            nearst_distance = distance;
                        }
                    }
                }
                if (targetFind) {
                    myHero->attack(target);
                    attacked_1 = 1;
                }

            }
        }
        //敌方攻击动作
        for (auto enemyHero : enemyHeroes)
        {
            if (!enemyHero->Die) {
                Hero* target = myHeroes.front();
                bool targetFind = 0;
                long long nearst_distance = 99999999999;
                for (auto myHero : myHeroes) {
                    if (!myHero->Die) {
                        targetFind = 1;
                        long long x_distance = myHero->getPosition().x - enemyHero->getPosition().x;
                        long long y_distance = myHero->getPosition().y - enemyHero->getPosition().y;
                        long long distance = pow(x_distance, 2) + pow(y_distance, 2);
                        if (distance < nearst_distance) {
                            target = myHero;
                            nearst_distance = distance;
                        }
                    }
                }

                if (targetFind) {
                    enemyHero->attack(target);
                    attacked_2 = 1;
                }

            }
        }
        
    

    fight = 0;
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

    if (weapon) {



        // 在我方英雄位置生成一支飞箭的图片
        auto arrow = Sprite::create("arrow.png"); // 请替换为实际的箭头图片路径
        arrow->setPosition(myPosition);
        this->getParent()->addChild(arrow);


        // 创建移动动作，一秒后挪到敌方英雄位置
        auto moveTo = MoveTo::create(0.5f, enemyPosition);

        // 示例：减少目标血量
        auto attackCallback = CallFunc::create([this, target]() {
            target->decreaseHealth(power);
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
    else {


        Vec2 closePosition;
        if (target->getWeapon()) {
            closePosition.x = enemyPosition.x + ((myPosition.x > enemyPosition.x) ? 10 : -10);
            closePosition.y = enemyPosition.y + ((myPosition.y > enemyPosition.y) ? 10 : -10);
        }
        else {
            closePosition.x = (myPosition.x + enemyPosition.x) / 2 + ((myPosition.x > enemyPosition.x) ? 10 : -10);
            closePosition.y = (myPosition.y + enemyPosition.y) / 2 + ((myPosition.y > enemyPosition.y) ? 10 : -10);
        }
        // 创建移动动作，一秒后挪到敌方英雄位置
        auto moveTo = MoveTo::create(0.5f, closePosition);
        // 创建旋转动作，参数为旋转的角度，360度即一圈
        auto rotateAction = RotateBy::create(0.5f, 360.0f);
        // 示例：减少目标血量
        auto attackCallback = CallFunc::create([this, target]() {
            target->decreaseHealth(power);
        });

        auto moveBack=MoveTo::create(0.5f, myPosition);

        auto sequence = Sequence::create(moveTo, rotateAction, attackCallback, moveBack, nullptr);
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
int Hero::getBlood() const
{
    return blood;
}

void Hero::setIndex(int index) {
    seatIndex = index;
}