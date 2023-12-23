#include"heroSprite.h"
#include<vector>
#include"chessboardSeat.h"
#include"preparationSeat.h"

extern chessboardSeat seat1;
extern preparationSeat seat2;

int fight = 0;
Vector<Hero*> allMyHeroes;//我方所有英雄
Vector<Hero*> allEnemyHeroes;//敌方所有英雄

Hero::Hero()
{
    blood = 100;
    magic = 50;
    level = 1;
    camp = -1;
    heroType = -1;
    weapon = -1;
    power = 10;
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
    }
    else
        allEnemyHeroes.pushBack(hero);

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
                    allMyHeroes.eraseObject(hero);
                    hero->removeFromParent();
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
    blood *= 2;
    magic *= 2;
    power *= 2;
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

    if (weapon) {



        // 在我方英雄位置生成一支飞箭的图片
        auto arrow = Sprite::create("arrow.png"); // 请替换为实际的箭头图片路径
        this->getParent()->addChild(arrow);

        arrow->setPosition(myPosition);

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

        auto moveBack = MoveTo::create(0.5f, myPosition);

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