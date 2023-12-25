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


    // 在需要的时候手动启动定时器
    void startattack() {
        schedule(CC_SCHEDULE_SELECTOR(playerScene::attack), 2.0f);
    }

    // 攻击方法
    void attack(float dt)
    {
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
            //小小英雄的攻击
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

    //通过检测fight全局变量来实现休息环节与战斗环节的交替
    void startGame(float dt) {  
        if (fight == 0) {  //退出战斗，轮到休息环节
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::startGame));  //停止外层循环回调

            //重现我方英雄
            ShowHeroes(1);

            //撤去敌方英雄
            CoverHeroes(0);

            //进度条开始
            progress0->setVisible(true);
            progress1->setVisible(true);
            // 设置定时器更新频率（这里假设以每帧更新）
            this->schedule([this](float dt) {
                currentTime += dt;
            // 计算当前进度（百分比）
            float progressPercentage = (currentTime / totalTime) * 100.0f;
            // 更新进度条
            progress1->setPercentage(progressPercentage);
            // 判断是否达到定时时间，如果达到则取消定时器或进行其他操作

            if (currentTime >= totalTime) {  //休息时间结束
                this->unschedule("progress");
                currentTime = 0.0f;   //重置
                fight = 1;
                progress0->setVisible(false);
                progress1->setVisible(false);
                schedule(CC_SCHEDULE_SELECTOR(playerScene::startGame), 1.0f);
            }
                }, "progress");
        }
        else {
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::startGame));  //停止外层回调

            //显示敌方英雄
            ShowHeroes(0);

            //开始对打
            startattack();
        }
    }
};

