#include"heroSprite.h"
#include<vector>
#include"chessboardSeat.h"
#include"preparationSeat.h"

extern chessboardSeat seat1;
extern preparationSeat seat2;

int fight = 0;
std::vector<Hero*> allMyHeroes;//�ҷ�����Ӣ��
std::vector<Hero*> allEnemyHeroes;//�з�����Ӣ��

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
// ������ͬ���͵�Ӣ��
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
        hero->camp = camp;  // ������Ӫ
        // ���ݲ�ͬ���ͳ�ʼ��Ӣ������
        switch (heroType)
        {
            case 1:
                // ��ʼ��Ϊ��һ�����͵�Ӣ��
                hero->initWithFile("hero1.png");
                // ���Ը���ʵ�������ٵ���Ѫ�����������ȼ�������
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
        //��������Ĵ�С
        hero->setScale(0.15);
        return hero;
    }

    CC_SAFE_DELETE(hero);
    return nullptr;
}
// �ƶ�����
void Hero::move(Vec2 destination)
{
    // ʹ��Cocos�����ṩ�Ķ�������ʵ���ƶ�
    auto moveTo = MoveTo::create(1.0f, destination);
    this->runAction(moveTo);
}
// �ϳɷ���
void Hero::mergeHeroes()
{
    //ÿ�ξ۽���ͬһ��Ӣ��
    for (int i = 1; i <= 3; i++) {
        //ÿ�ξ۽���һ��ͬ��Ӣ��
        for (int j = 1; j <= ALL_TYPE; j++) {


            int myCount = 0;
            int enemyCount = 0;
            // �������з�ս����ͬ��Ӣ�ۣ����ȼ�����
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

// Getter �� Setter ����
int Hero::getLevel() const { return level; }
void Hero::upgrade(int newLevel) {
    level = newLevel;
    blood *= 2;
    magic *= 2;
    power *= 2;
    setScale(0.10 + level * 0.05);
    
}
int Hero::getType()const { return heroType; }

// ����ս��״̬
void Hero::enterBattle()
{
    inBattle = true;
}

// �˳�ս��״̬
void Hero::exitBattle()
{
    inBattle = false;
}

// �Ƿ���ս��״̬
bool Hero::isInBattle() const
{
    return inBattle;
}

// ��������
void Hero::enterBoard()
{
    inBoard = true;
}

// �˳�����
void Hero::exitBoard()
{
    inBoard = false;
}

// �Ƿ�������
bool Hero::isInBoard() const
{
    return inBoard;
}

// ����һ������ԭ�ж������¶����� Spawn
Spawn* Hero::addAdditionalActionToSpawn(Spawn* originalSpawn, FiniteTimeAction* additionalAction) {
    // ����һ���µ� Spawn������ԭ�ж������¶���
    auto combinedSpawn = Spawn::create(additionalAction, originalSpawn, nullptr);

    return combinedSpawn;
}

// ��������
void Hero::attack()
{
    fight = 1;
    // ������Ӫ�����д���ս��״̬��Ӣ�۷ֱ�洢������������
    std::vector<Hero*> myHeroes;
    std::vector<Hero*> enemyHeroes;

    // ��������ս��Ӣ��

    // ����Ҫ����ʵ������޸�
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
        //�ҷ���������
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
        //�з���������
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
//��ȡ��ս����Զ��
int Hero::getWeapon() const
{
    return weapon;
}


// ��������������ָ��Ŀ��
void Hero::attack(Hero* target)
{
    // ��ȡ����Ӣ��λ��
    Vec2 myPosition = this->getPosition();
    Vec2 enemyPosition = target->getPosition();

    if (weapon) {



        // ���ҷ�Ӣ��λ������һ֧�ɼ���ͼƬ
        auto arrow = Sprite::create("arrow.png"); // ���滻Ϊʵ�ʵļ�ͷͼƬ·��
        arrow->setPosition(myPosition);
        this->getParent()->addChild(arrow);


        // �����ƶ�������һ���Ų���з�Ӣ��λ��
        auto moveTo = MoveTo::create(0.5f, enemyPosition);

        // ʾ��������Ŀ��Ѫ��
        auto attackCallback = CallFunc::create([this, target]() {
            target->decreaseHealth(power);
            });


        //�ɼ���ʧ
        auto disappearCallback = CallFunc::create([arrow]() {
            // �ӳ������Ƴ�
            arrow->removeFromParentAndCleanup(true);
            });

        // ����һ�����ж��������ƶ�����ʧ��Ȼ��ִ�лص�
        auto sequence = Sequence::create(moveTo, attackCallback, disappearCallback, nullptr);


        // ���зɼ�����
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
        // �����ƶ�������һ���Ų���з�Ӣ��λ��
        auto moveTo = MoveTo::create(0.5f, closePosition);
        // ������ת����������Ϊ��ת�ĽǶȣ�360�ȼ�һȦ
        auto rotateAction = RotateBy::create(0.5f, 360.0f);
        // ʾ��������Ŀ��Ѫ��
        auto attackCallback = CallFunc::create([this, target]() {
            target->decreaseHealth(power);
        });

        auto moveBack=MoveTo::create(0.5f, myPosition);

        auto sequence = Sequence::create(moveTo, rotateAction, attackCallback, moveBack, nullptr);
        this->runAction(sequence);

    }
}


// ����Ѫ������
void Hero::decreaseHealth(int amount)
{
    blood -= amount;

    // ���Ѫ�����͵�0���£�������
    if (blood <= 0)
    {
        this->die();
    }
}

// ��������
void Hero::die()
{
    // �����������������������߼�
    // ...

    Die = 1;
    // �������ɫ����
    auto grayAction = TintTo::create(0.5f, 0, 0, 0); // ��ͼƬ��ɫ����Ϊ��ɫ�����Ը�����Ҫ����ʱ�����ɫ

    // ����һ���ص��������ڱ��ɫ������ɺ�ִ����ʧ�߼�
    auto disappearCallback = CallFunc::create([this]() {
        // ʾ�����ӳ������Ƴ�

        this->setVisible(false);

    });

    // ����һ�����ж������ȱ��ɫ��Ȼ��ִ�лص�
    auto sequence = Sequence::create(grayAction, disappearCallback, nullptr);

    // �������ж���
    this->runAction(sequence);

}

// ��ȡ��Ӫ
int Hero::getCamp() const
{
    return camp;
}

// ��ȡѪ��
int Hero::getBlood() const
{
    return blood;
}

void Hero::setIndex(int index) {
    seatIndex = index;
}