#pragma once
#include"cocos2d.h"
#include"preparationSeat.h"
#include"chessboardSeat.h"
#include"playerlistLayer.h"
#include"storeLayer.h"
#include"playerroleLayer.h"
#include"hero1.h"
extern std::vector<Hero*> allMyHeroes;//我方所有英雄
extern std::vector<Hero*> allEnemyHeroes;//敌方所有英雄
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
    // 在需要的时候手动启动定时器
    void startTimer() {
        schedule(CC_SCHEDULE_SELECTOR(playerScene::attack), 2.0f);  // 每隔1秒执行一次checkCondition函数
    }

    // 定时器回调函数，用于循环判断并执行动作
    void checkCondition(float dt) {
        // 在这里进行循环判断，根据条件决定是否执行动作
        if (yourConditionIsMet()) {
            // 创建一个动作对象，这里使用MoveBy作为示例
            auto moveAction = MoveBy::create(1.0f, Vec2(100, 0));

            // 执行动作
            runAction(moveAction);

            // 可以选择停止定时器，如果不再需要检查条件的话
            // unschedule(CC_SCHEDULE_SELECTOR(YourGameScene::checkCondition));
        }
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
        if (!attacked)
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::attack));

        fight = 0;
    }
    // 替换为你自己的条件判断逻辑
    bool yourConditionIsMet() {
        // 返回true表示条件满足，可以执行动作
        // 这里只是一个示例，你需要根据你的实际需求来实现
        return true;
    }
	CREATE_FUNC(playerScene);
	
};

