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
        // 根据阵营将所有处于战斗状态的英雄分别存储到两个堆里面
        std::vector<Hero*> myHeroes;
        std::vector<Hero*> enemyHeroes;

        // 遍历所有战斗英雄

        // 你需要根据实际情况修改
        for (auto hero : allMyHeroes)
        {
            if (hero->isInBoard() && fight == 1)
            {
                myHeroes.push_back(hero);

            }
        }
        for (auto hero : allEnemyHeroes)
        {
            if (hero->isInBoard() && fight == 1)
            {
                enemyHeroes.push_back(hero);
            }
        }




        bool attacked = 0;

        //我方攻击动作
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
        //敌方攻击动作
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
        if (!attacked) {
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::attack));

            fight = 0;
        }
    }
};

