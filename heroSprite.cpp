#include"heroSprite.h"
#include<vector>
int fight = 1;
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
    power = 20;
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
        hero->setScale(0.25);
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
void Hero::mergeHeroes(std::vector<Hero*>& all_heroes)
{
    //每次聚焦于一种同名英雄
    for (int i = 1; i <= ALL_TYPE; i++) {

        std::map<int, std::vector<Hero*>> levelMap; // 按等级分类的同名英雄集合

        // 遍历所有非战斗的同名英雄，按等级分类
        for (Hero* hero : all_heroes)
        {
            if (!(hero->isInBattle()) && hero->getType() == i) {
                int heroLevel = hero->getLevel();
                if (heroLevel < 3)
                    levelMap[heroLevel].push_back(hero);
            }
        }

        // 遍历分类后的同名英雄集合，进行合成
        for (auto& pair : levelMap)
        {
            int heroLevel = pair.first;
            std::vector<Hero*>& heroesOfSameLevel = pair.second;

            // 如果有足够的英雄，每三个合成一个更高等级的英雄
            while (heroesOfSameLevel.size() >= 3)
            {

                bool herofind = 0;//用于判断是否找到了融合后的位置

                // 删除被合成的三个英雄
                for (int i = 0; i < 3; ++i)
                {
                    Hero* heroToMerge = heroesOfSameLevel[i];

                    if ((heroToMerge->isInBoard() || i == 2) && !herofind) {
                        heroToMerge->upgrade(heroLevel + 1);
                    }

                    else {
                        heroToMerge->setVisible(false);
                        all_heroes.erase(std::remove(all_heroes.begin(), all_heroes.end(), heroToMerge), all_heroes.end());
                        
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
    updateHeroColor();
}
int Hero::getType()const { return heroType; }
void Hero::updateHeroColor()
{
    // 获取原始颜色
    Color3B originalColor = getColor();

    // 计算新颜色，假设 level 变大时颜色变深
    float darkeningFactor = 0.8f; // 调整此值以控制变暗的程度
    int newRed = originalColor.r * darkeningFactor;
    int newGreen = originalColor.g * darkeningFactor;
    int newBlue = originalColor.b * darkeningFactor;

    // 设置新颜色
    setColor(Color3B(newRed, newGreen, newBlue));
}
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
    // 根据阵营将所有处于战斗状态的英雄分别存储到两个堆里面
    std::vector<Hero*> myHeroes;
    std::vector<Hero*> enemyHeroes;

    // 遍历所有战斗英雄

    // 你需要根据实际情况修改
    for (auto hero : allMyHeroes)
    {
        if (hero->isInBattle())
        {
            myHeroes.push_back(hero);

        }
    }
    for (auto hero : allEnemyHeroes)
    {
        if (hero->isInBattle())
        {
            enemyHeroes.push_back(hero);
        }
    }



    while (!myHeroes.empty() && !enemyHeroes.empty())
    {

        //我方攻击动作
        for (auto myHero : myHeroes)
        {
            Hero* target = enemyHeroes.front();
            long long nearst_distance = 99999999999;
            for (auto enemyHero : enemyHeroes) {
                long long x_distance = myHero->getPosition().x - enemyHero->getPosition().x;
                long long y_distance = myHero->getPosition().y - enemyHero->getPosition().y;
                long long distance = pow(x_distance, 2) + pow(y_distance, 2);
                if (distance < nearst_distance) {
                    target = enemyHero;
                    nearst_distance = distance;
                }
            }

            myHero->attackInThread(target);

        }
        //敌方攻击动作
        for (auto enemyHero : enemyHeroes)
        {
            Hero* target = myHeroes.front();
            long long nearst_distance = 99999999999;
            for (auto myHero : myHeroes) {
                long long x_distance = myHero->getPosition().x - enemyHero->getPosition().x;
                long long y_distance = myHero->getPosition().y - enemyHero->getPosition().y;
                long long distance = pow(x_distance, 2) + pow(y_distance, 2);
                if (distance < nearst_distance) {
                    target = myHero;
                    nearst_distance = distance;
                }
            }

            enemyHero->attackInThread(target);


        }

    }

}
//获取近战还是远程
int Hero::getWeapon() const
{
    return weapon;
}

// 在一个新线程中模拟攻击
void Hero::attackInThread(Hero* target)
{
    // 在新线程中进行攻击操作
    std::thread([this, target]() {
        // 模拟攻击的一些计算或者逻辑
        // 这里可以使用std::this_thread::sleep_for模拟一些计算耗时的操作
        std::this_thread::sleep_for(std::chrono::seconds(1));

    // 回到主线程执行攻击逻辑
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([this, target]() {
        // 在主线程中执行攻击逻辑
        this->attack(target);
        });
        }).detach();  // 使用detach使新线程独立运行
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
            closePosition.x = enemyPosition.x + (myPosition.x > enemyPosition.x) ? 100 : -100;
            closePosition.y = enemyPosition.y + (myPosition.y > enemyPosition.y) ? 100 : -100;
        }
        else {
            closePosition.x = (myPosition.x + enemyPosition.x) / 2 + (myPosition.x > enemyPosition.x) ? 50 : -50;
            closePosition.y = (myPosition.y + enemyPosition.y) / 2 + (myPosition.y > enemyPosition.y) ? 50 : -50;
        }
        // 创建移动动作，一秒后挪到敌方英雄位置
        auto moveTo = MoveTo::create(0.5f, closePosition);
        // 创建旋转动作，参数为旋转的角度，360度即一圈
        auto rotateAction = RotateBy::create(0.5f, 360.0f);
        // 示例：减少目标血量
        auto attackCallback = CallFunc::create([this, target]() {
            target->decreaseHealth(power);
            });
        auto sequence = Sequence::create(moveTo, rotateAction, attackCallback, nullptr);
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
        die();
    }
}

// 死亡方法
void Hero::die()
{
    // 在这里可以添加死亡动画等逻辑
    // ...
   

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
    if (getCamp()) {
        allMyHeroes.erase(std::remove(allMyHeroes.begin(), allMyHeroes.end(), this), allMyHeroes.end());
    }
    else {
        allEnemyHeroes.erase(std::remove(allEnemyHeroes.begin(), allEnemyHeroes.end(), this), allEnemyHeroes.end());
    }

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