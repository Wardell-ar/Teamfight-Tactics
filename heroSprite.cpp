#include"heroSprite.h"
#include<vector>
#include"chessboardSeat.h"
#include"preparationSeat.h"

extern chessboardSeat seat1;
extern preparationSeat seat2;

int fight = 0;
Vector<Hero*> allMyHeroes;//�ҷ�����Ӣ��
Vector<Hero*> allEnemyHeroes;//�з�����Ӣ��

Hero::Hero()
{
    max_blood = blood = 100;
    each_magic = 34;
    magic = 0;
    level = 1;
    camp = -1;
    heroType = -1;
    weapon = -1;
    power = 10;
    inBoard = 0;
    Die = 0;
    seatIndex = -1;
}

// ������ͬ���͵�Ӣ��
Hero* Hero::createHero(int heroType, const Vec2& position, int camp)
{
    Hero* hero = new Hero();
    if (camp == 1) {
        allMyHeroes.pushBack(hero);
        //�˴���ʼ��������Ѫ��(����������ʵ�ֱַ��Ƿ���������ʱ�����ж�������ʹ�ڱ�սϯ�ϲ�����Ѫ��)
        auto bloodbar1 = Sprite::create("bloodbar1.png");
        auto bloodbar0 = Sprite::create("bloodbar0.png");
        
        hero->healthBar = ProgressTimer::create(bloodbar1);
        hero->healthBar->setType(ProgressTimer::Type::BAR);
        hero->healthBar->setMidpoint(Vec2(0, 0.5));
        hero->healthBar->setBarChangeRate(Vec2(1, 0));
        // �� healthBar ��ӵ� mySprite ��
        hero->addChild(hero->healthBar, 1);
        hero->addChild(bloodbar0, 0);
        hero->healthBar->setPosition(200,400);
        bloodbar0->setPosition(200,400);
        // ����Ѫ����ʼ����
        hero->healthBar->setPercentage(100);  //��Ѫ
        //������
        hero->magicBar = ProgressTimer::create(Sprite::create("magicbar.png"));
        hero->magicBar->setType(ProgressTimer::Type::BAR);
        hero->magicBar->setMidpoint(Vec2(0, 0.5));
        hero->magicBar->setBarChangeRate(Vec2(1, 0));
        // �� healthBar ��ӵ� mySprite ��
        hero->addChild(hero->magicBar);
        hero->magicBar->setPosition(200, 350);
        // ����������ʼ����
        hero->magicBar->setPercentage(hero->magic);
    }
    else
    {
        allEnemyHeroes.pushBack(hero);
        //�˴���ʼ��������Ѫ��(����������ʵ�ֱַ��Ƿ���������ʱ�����ж�������ʹ�ڱ�սϯ�ϲ�����Ѫ��)
        auto bloodbar1 = Sprite::create("bloodbar1.png");
        auto bloodbar0 = Sprite::create("bloodbar0.png");
        bloodbar1->setColor(Color3B::RED);
        hero->healthBar = ProgressTimer::create(bloodbar1);
        hero->healthBar->setType(ProgressTimer::Type::BAR);
        hero->healthBar->setMidpoint(Vec2(0, 0.5));
        hero->healthBar->setBarChangeRate(Vec2(1, 0));
        // �� healthBar ��ӵ� mySprite ��
        hero->addChild(hero->healthBar,1);
        hero->addChild(bloodbar0,0);
        hero->healthBar->setPosition(200,400);
        bloodbar0->setPosition(200,400);
        // ����Ѫ����ʼ����
        hero->healthBar->setPercentage(100);  //��Ѫ
        //������
        hero->magicBar = ProgressTimer::create(Sprite::create("magicbar.png"));
        hero->magicBar->setType(ProgressTimer::Type::BAR);
        hero->magicBar->setMidpoint(Vec2(0, 0.5));
        hero->magicBar->setBarChangeRate(Vec2(1, 0));
        // �� healthBar ��ӵ� mySprite ��
        hero->addChild(hero->magicBar);
        hero->magicBar->setPosition(200, 350);
        // ����������ʼ����
        hero->magicBar->setPercentage(hero->magic);
    }

    if (hero)
    {
        hero->autorelease();
        hero->camp = camp;  // ������Ӫ
        // ���ݲ�ͬ���ͳ�ʼ��Ӣ������
        switch (heroType)
        {
            case 1:
                // ��ʼ��Ϊ��һ�����͵�Ӣ��--С���ӣ��չ�С���򣬴��д�����(1)
                hero->initWithFile("hero1.png");
                // ���Ը���ʵ�������ٵ���Ѫ�����������ȼ�������
                hero->max_blood = 100;
                hero->blood = 100;
                hero->each_magic = 50;
                hero->power = 34;
                hero->weapon = 1;
                hero->heroType = 1;
                break;

            case 2:
                //������(�չ�С�����򣬴��д�������(5)
                hero->initWithFile("hero2.png");
                hero->max_blood = 200;
                hero->blood = 200;
                hero->each_magic = 50;
                hero->power = 100;
                hero->weapon = 1;
                hero->heroType = 2;
                break;
            case 3:
                //���ˣ��չ������������裬���н������������｣��(3)
                hero->initWithFile("hero3.png");
                hero->max_blood = 200;
                hero->blood = 200;
                hero->each_magic = 34;
                hero->power = 50;
                hero->weapon = 0;
                hero->heroType = 3;
                break;
            case 4:
                //���ߣ��չ�С���򣬴�������������ѣ�(2)
                hero->initWithFile("hero4.png");
                hero->max_blood = 100;
                hero->blood = 100;
                hero->each_magic = 50;
                hero->power = 25;
                hero->weapon = 1;
                hero->heroType = 4;
                break;
            case 5:
                //·�ɣ��չ�תһȦ�����б��תһȦ��(2)
                hero->initWithFile("hero5.png");
                hero->max_blood = 200;
                hero->blood = 200;
                hero->magic = 50;
                hero->power = 25;
                hero->weapon = 0;
                hero->heroType = 5;
                break;
            case 6:
                //�Ʊȣ��չ����⣬���б��ֱ������ײ��(4)
                hero->initWithFile("hero6.png");
                hero->max_blood = 200;
                hero->blood = 200;
                hero->magic = 100;
                hero->power = 50;
                hero->weapon = 0;
                hero->heroType = 6;
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
                //ɾ����������Ӣ��
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
                //ɾ����������Ӣ��
                for (Hero* hero : heroToDelete) {
                    allEnemyHeroes.eraseObject(hero);
                    hero->removeFromParent();
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


    //�������������Զ��
    if (weapon) {



        // ���ҷ�Ӣ��λ������һ֧�ɼ���ͼƬ
        auto arrow = Sprite::create("arrow.png"); // ���滻Ϊʵ�ʵļ�ͷͼƬ·��
        this->getParent()->addChild(arrow);


        switch (heroType) {
            case 1://С����
                if (magic >= 100)
                    arrow->setScale(2);
                break;
            case 2://������
                arrow->setTexture("wtw_arrow.png");
                if (magic >= 100)
                    arrow->setScale(2);
                break;
            case 4://����
                arrow->setTexture("sage_arrow.png");
                if (magic >= 100) {
                    Hero* friendTarget;
                    Vec2 friendPosition;
                    int lowestBlood = 999;
                    for (Hero* friendHero : allMyHeroes) {
                        if (friendHero->isInBoard() && !friendHero->isDead()) {
                            if (friendHero->getBlood() < lowestBlood) {
                                lowestBlood = friendHero->getBlood();
                                friendTarget = friendHero;
                                friendPosition = friendHero->getPosition();
                            }
                        }
                    }
                    if (lowestBlood < 999) {
                        arrow->setPosition(myPosition);
                        auto moveTo = MoveTo::create(0.5f, friendPosition);

                        auto heal = Sprite::create("heal.png");
                        this->getParent()->addChild(heal);
                        heal->setPosition(friendPosition);

                        auto healCallback = CallFunc::create([this, friendTarget]() {
                            friendTarget->setBlood(friendTarget->getMaxBlood());
                        this->magic = 0;
                            });


                        //�ɼ���ʧ
                        auto disappearCallback = CallFunc::create([arrow, heal]() {
                            // �ӳ������Ƴ�
                            heal->removeFromParentAndCleanup(true);
                        arrow->removeFromParentAndCleanup(true);
                            });

                        // ����һ�����ж��������ƶ�����ʧ��Ȼ��ִ�лص�
                        auto sequence = Sequence::create(moveTo, healCallback, disappearCallback, nullptr);
                    }
                    return;
                }

                break;

        }
        arrow->setPosition(myPosition);

        // �����ƶ�������һ���Ų���з�Ӣ��λ��
        auto moveTo = MoveTo::create(0.5f, enemyPosition);

        // ʾ��������Ŀ��Ѫ��
        auto attackCallback = CallFunc::create([this, target]() {
            target->decreaseHealth(power);
        if (magic >= 100){
            target->decreaseHealth(power * 2);  //�����˺�
            magic = 0;
        }
           
        else{
            target->decreaseHealth(power); 
            magic += each_magic;
        }
           
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
    else {  //��ս

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
                    break;
                case 5:
                    this->setTexture("5gear.png");
                    break;
                case 6:
                    this->setTexture("helicapter.png");
                    break;
            }
        }
        // �����ƶ�������һ���Ų���з�Ӣ��λ��
        auto moveTo = MoveTo::create(0.5f, closePosition);
        // ������ת����������Ϊ��ת�ĽǶȣ�360�ȼ�һȦ
        auto rotateAction = RotateBy::create(0.5f, 360.0f);
        // ʾ��������Ŀ��Ѫ��
        auto attackCallback = CallFunc::create([this, target]() {
        if (magic >= 100)
        {
            target->decreaseHealth(power * 2);
            magic = 0;
        }
        else
        {
            target->decreaseHealth(power);
            magic += each_magic;
        }
            });

        auto moveBack = MoveTo::create(0.5f, myPosition);

        auto sequence = Sequence::create(moveTo, rotateAction, attackCallback, moveBack, nullptr);
        this->runAction(sequence);
        switch (heroType) {
            case 3:
                this->setTexture("hero3.png");
                break;
            case 5:
                this->setTexture("hero5.png");
                break;
            case 6:
                this->setTexture("hero6.png");
                break;
        }
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

void Hero::updatebloodandmagic() {
    healthBar->setPercentage(blood / max_blood * 100.0f);
    magicBar->setPercentage(magic);
}