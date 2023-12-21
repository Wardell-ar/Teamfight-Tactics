#include"heroSprite.h"
#include<vector>
int fight = 1;
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
    power = 20;
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
        hero->setScale(0.25);
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
void Hero::mergeHeroes(std::vector<Hero*>& all_heroes)
{
    //ÿ�ξ۽���һ��ͬ��Ӣ��
    for (int i = 1; i <= ALL_TYPE; i++) {

        std::map<int, std::vector<Hero*>> levelMap; // ���ȼ������ͬ��Ӣ�ۼ���

        // �������з�ս����ͬ��Ӣ�ۣ����ȼ�����
        for (Hero* hero : all_heroes)
        {
            if (!(hero->isInBattle()) && hero->getType() == i) {
                int heroLevel = hero->getLevel();
                if (heroLevel < 3)
                    levelMap[heroLevel].push_back(hero);
            }
        }

        // ����������ͬ��Ӣ�ۼ��ϣ����кϳ�
        for (auto& pair : levelMap)
        {
            int heroLevel = pair.first;
            std::vector<Hero*>& heroesOfSameLevel = pair.second;

            // ������㹻��Ӣ�ۣ�ÿ�����ϳ�һ�����ߵȼ���Ӣ��
            while (heroesOfSameLevel.size() >= 3)
            {

                bool herofind = 0;//�����ж��Ƿ��ҵ����ںϺ��λ��

                // ɾ�����ϳɵ�����Ӣ��
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

// Getter �� Setter ����
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
    // ��ȡԭʼ��ɫ
    Color3B originalColor = getColor();

    // ��������ɫ������ level ���ʱ��ɫ����
    float darkeningFactor = 0.8f; // ������ֵ�Կ��Ʊ䰵�ĳ̶�
    int newRed = originalColor.r * darkeningFactor;
    int newGreen = originalColor.g * darkeningFactor;
    int newBlue = originalColor.b * darkeningFactor;

    // ��������ɫ
    setColor(Color3B(newRed, newGreen, newBlue));
}
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
    // ������Ӫ�����д���ս��״̬��Ӣ�۷ֱ�洢������������
    std::vector<Hero*> myHeroes;
    std::vector<Hero*> enemyHeroes;

    // ��������ս��Ӣ��

    // ����Ҫ����ʵ������޸�
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

        //�ҷ���������
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
        //�з���������
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
//��ȡ��ս����Զ��
int Hero::getWeapon() const
{
    return weapon;
}

// ��һ�����߳���ģ�⹥��
void Hero::attackInThread(Hero* target)
{
    // �����߳��н��й�������
    std::thread([this, target]() {
        // ģ�⹥����һЩ��������߼�
        // �������ʹ��std::this_thread::sleep_forģ��һЩ�����ʱ�Ĳ���
        std::this_thread::sleep_for(std::chrono::seconds(1));

    // �ص����߳�ִ�й����߼�
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([this, target]() {
        // �����߳���ִ�й����߼�
        this->attack(target);
        });
        }).detach();  // ʹ��detachʹ���̶߳�������
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
            closePosition.x = enemyPosition.x + (myPosition.x > enemyPosition.x) ? 100 : -100;
            closePosition.y = enemyPosition.y + (myPosition.y > enemyPosition.y) ? 100 : -100;
        }
        else {
            closePosition.x = (myPosition.x + enemyPosition.x) / 2 + (myPosition.x > enemyPosition.x) ? 50 : -50;
            closePosition.y = (myPosition.y + enemyPosition.y) / 2 + (myPosition.y > enemyPosition.y) ? 50 : -50;
        }
        // �����ƶ�������һ���Ų���з�Ӣ��λ��
        auto moveTo = MoveTo::create(0.5f, closePosition);
        // ������ת����������Ϊ��ת�ĽǶȣ�360�ȼ�һȦ
        auto rotateAction = RotateBy::create(0.5f, 360.0f);
        // ʾ��������Ŀ��Ѫ��
        auto attackCallback = CallFunc::create([this, target]() {
            target->decreaseHealth(power);
            });
        auto sequence = Sequence::create(moveTo, rotateAction, attackCallback, nullptr);
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
        die();
    }
}

// ��������
void Hero::die()
{
    // �����������������������߼�
    // ...
   

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
    if (getCamp()) {
        allMyHeroes.erase(std::remove(allMyHeroes.begin(), allMyHeroes.end(), this), allMyHeroes.end());
    }
    else {
        allEnemyHeroes.erase(std::remove(allEnemyHeroes.begin(), allEnemyHeroes.end(), this), allEnemyHeroes.end());
    }

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