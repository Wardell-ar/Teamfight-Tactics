#pragma once
#include"cocos2d.h"
#include"preparationSeat.h"
#include"chessboardSeat.h"
#include"playerlistLayer.h"
#include"storeLayer.h"
#include"playerroleLayer.h"
USING_NS_CC;
extern Vector<Hero*> allMyHeroes;//�ҷ�����Ӣ��
extern Vector<Hero*> allEnemyHeroes;//�з�����Ӣ��
extern int fight;


class playerScene : public Scene
{
public:
    playerroleLayer* myrole;
    playerroleLayer* enemyrole;
	storeLayer* store;
    Sprite* progress0;
    ProgressTimer* progress1;
    Sequence* to1;
    Sequence* gameprogress;
    float totalTime = 10.0f;
    float currentTime = 0.0f;
	
	static playerScene* createScene();
	virtual bool init();
	CREATE_FUNC(playerScene);
	void ShowHeroes(int IsMine);
	void CoverHeroes(int IsMine);


    // ����Ҫ��ʱ���ֶ�������ʱ��
    void startattack() {
        schedule(CC_SCHEDULE_SELECTOR(playerScene::attack), 2.0f);
    }

    // ��������
    void attack(float dt)
    {
        bool attacked = 0;

        //�ҷ���������
        for (auto myHero : allMyHeroes)
        {
            if (!myHero->isDead()&& myHero->isInBoard()) {
                Hero* target;
                bool targetFind = 0;
                long long nearst_distance = 99999999999;
                for (auto enemyHero : allEnemyHeroes) {
                    if (!enemyHero->isDead() && enemyHero->isInBoard()) {
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
                    attacked = 1;
                }
            }
        }
        //�з���������
        for (auto enemyHero : allEnemyHeroes)
        {
            if (!enemyHero->isDead()&&enemyHero->isInBoard()) {
                Hero* target;
                bool targetFind = 0;
                long long nearst_distance = 99999999999;
                for (auto myHero : allMyHeroes) {
                    if (!myHero->isDead()&&myHero->isInBoard()) {
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
                    attacked = 1;
                }

            }
        }
        if (!attacked) {
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::attack));
            fight = 0;
            //ССӢ�۵Ĺ���
            int countUnDead = 0;
            for (Hero* hero : allEnemyHeroes) {
                if (hero->isInBoard() && !hero->isDead()) {
                    countUnDead++;
                }
            }
            if (countUnDead == 0) {
                myrole->attack(enemyrole);
            }

            countUnDead = 0;
            for (Hero* hero : allMyHeroes) {
                if (hero->isInBoard() && !hero->isDead()) {
                    countUnDead++;
                }
            }
            if (countUnDead == 0) {
                enemyrole->attack(myrole);
            }
            schedule(CC_SCHEDULE_SELECTOR(playerScene::startGame), 1.0f);
        }
    }

    //ͨ�����fightȫ�ֱ�����ʵ����Ϣ������ս�����ڵĽ���
    void startGame(float dt) {  
        if (fight == 0) {  //�˳�ս�����ֵ���Ϣ����
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::startGame));  //ֹͣ���ѭ���ص�

            //�����ҷ�Ӣ��
            ShowHeroes(1);

            //��ȥ�з�Ӣ��
            CoverHeroes(0);

            //��������ʼ
            progress0->setVisible(true);
            progress1->setVisible(true);
            // ���ö�ʱ������Ƶ�ʣ����������ÿ֡���£�
            this->schedule([this](float dt) {
                currentTime += dt;
            // ���㵱ǰ���ȣ��ٷֱȣ�
            float progressPercentage = (currentTime / totalTime) * 100.0f;
            // ���½�����
            progress1->setPercentage(progressPercentage);
            // �ж��Ƿ�ﵽ��ʱʱ�䣬����ﵽ��ȡ����ʱ���������������

            if (currentTime >= totalTime) {  //��Ϣʱ�����
                this->unschedule("progress");
                currentTime = 0.0f;   //����
                fight = 1;
                progress0->setVisible(false);
                progress1->setVisible(false);
                schedule(CC_SCHEDULE_SELECTOR(playerScene::startGame), 1.0f);
            }
                }, "progress");
        }
        else {
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::startGame));  //ֹͣ���ص�

            //��ʾ�з�Ӣ��
            ShowHeroes(0);

            //��ʼ�Դ�
            startattack();
        }
    }
};

