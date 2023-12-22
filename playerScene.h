#pragma once
#include"cocos2d.h"
#include"preparationSeat.h"
#include"chessboardSeat.h"
#include"playerlistLayer.h"
#include"storeLayer.h"
#include"playerroleLayer.h"
#include"hero1.h"
extern std::vector<Hero*> allMyHeroes;//�ҷ�����Ӣ��
extern std::vector<Hero*> allEnemyHeroes;//�з�����Ӣ��
extern int fight;
USING_NS_CC;


/*
  put a chessboard photo(include preparation seat and chessboard)
  set a menu (option) to exit the game or stop the music

  func:
  the move of the player role
*/
class playerScene : public Scene
{
	
	

public:

	storeLayer* store;

	static Scene* createScene();
	virtual bool init();
    // ����Ҫ��ʱ���ֶ�������ʱ��
    void startTimer() {
        schedule(CC_SCHEDULE_SELECTOR(playerScene::attack), 2.0f);  // ÿ��1��ִ��һ��checkCondition����
    }

    // ��ʱ���ص�����������ѭ���жϲ�ִ�ж���
    void checkCondition(float dt) {
        // ���������ѭ���жϣ��������������Ƿ�ִ�ж���
        if (yourConditionIsMet()) {
            // ����һ��������������ʹ��MoveBy��Ϊʾ��
            auto moveAction = MoveBy::create(1.0f, Vec2(100, 0));

            // ִ�ж���
            runAction(moveAction);

            // ����ѡ��ֹͣ��ʱ�������������Ҫ��������Ļ�
            // unschedule(CC_SCHEDULE_SELECTOR(YourGameScene::checkCondition));
        }
    }
    // ��������
    void attack(float dt)
    {
        fight = 1;
        // ������Ӫ�����д���ս��״̬��Ӣ�۷ֱ�洢������������
        std::vector<Hero*> myHeroes;
        std::vector<Hero*> enemyHeroes;

        // ��������ս��Ӣ��

        // ����Ҫ����ʵ������޸�
        for (auto hero : allMyHeroes)
        {
            if (hero->isInBattle() && hero->isExist())
            {
                myHeroes.push_back(hero);

            }
        }
        for (auto hero : allEnemyHeroes)
        {
            if (hero->isInBattle() && hero->isExist())
            {
                enemyHeroes.push_back(hero);
            }
        }






        bool attacked = 0;
        
        //�ҷ���������
        for (auto myHero : myHeroes)
        {
            if (!myHero->isDead()) {
                Hero* target = enemyHeroes.front();
                bool targetFind = 0;
                long long nearst_distance = 99999999999;
                for (auto enemyHero : enemyHeroes) {
                    if (!enemyHero->isDead()) {
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
        for (auto enemyHero : enemyHeroes)
        {
            if (!enemyHero->isDead()) {
                Hero* target = myHeroes.front();
                bool targetFind = 0;
                long long nearst_distance = 99999999999;
                for (auto myHero : myHeroes) {
                    if (!myHero->isDead()) {
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
        if (!attacked)
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::attack));

        fight = 0;
    }
    // �滻Ϊ���Լ��������ж��߼�
    bool yourConditionIsMet() {
        // ����true��ʾ�������㣬����ִ�ж���
        // ����ֻ��һ��ʾ��������Ҫ�������ʵ��������ʵ��
        return true;
    }
	CREATE_FUNC(playerScene);
	
};

