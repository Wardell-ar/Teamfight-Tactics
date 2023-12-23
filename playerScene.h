#pragma once
#include"cocos2d.h"
#include"preparationSeat.h"
#include"chessboardSeat.h"
#include"playerlistLayer.h"
#include"storeLayer.h"
#include"playerroleLayer.h"
USING_NS_CC;
extern Vector<Hero*> allMyHeroes;//我方所有英雄
extern Vector<Hero*> allEnemyHeroes;//敌方所有英雄
extern int fight;


class playerScene : public Scene
{
public:

	storeLayer* store;
	
	static playerScene* createScene();
	virtual bool init();
	CREATE_FUNC(playerScene);
	void ShowHeroes(int IsMine);
	void CoverHeroes(int IsMine);

    // 在需要的时候手动启动定时器
    void startTimer() {
        schedule(CC_SCHEDULE_SELECTOR(playerScene::attack), 2.0f);  // 每隔1秒执行一次checkCondition函数
    }
    // 攻击方法
    void attack(float dt)
    {
        fight = 1;

        bool attacked = 0;

        //我方攻击动作
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
        //敌方攻击动作
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
        }
    }
};

