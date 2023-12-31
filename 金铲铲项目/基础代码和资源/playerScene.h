#pragma once
#include"cocos2d.h"
#include"preparationSeat.h"
#include"chessboardSeat.h"
#include"storeLayer.h"
#include"playerroleLayer.h"
#include "cocos/audio/include/AudioEngine.h"
#include "settingLayer.h"
USING_NS_CC;
extern Vector<Hero*> allMyHeroes;//我方所有英雄
extern Vector<Hero*> allEnemyHeroes;//敌方所有英雄
extern int fight;
extern int enemyType;

class playerScene : public Scene
{
public:
    playerroleLayer* myrole;   //我方小小英雄
    playerroleLayer* enemyrole1;  //人机1
    playerroleLayer* enemyrole2;  //人机2

    Sprite* attacktram;  //攻击羁绊图标
    Sprite* healtram;    //治疗羁绊图标

	storeLayer* store;  //商店

    // 进度条
    Sprite* progress0;
    ProgressTimer* progress1;
    Sequence* to1;
    Sequence* gameprogress;

    // 进度时间
    float totalTime = 20.0f;
    float currentTime = 0.0f;

    // 玩家列表
    MenuItemSprite* seeEnemy1;
    MenuItemSprite* seeEnemy2;
    MenuItemSprite* goback;

    // 设置界面
    settingLayer* setting;

	static playerScene* createScene();
	virtual bool init();
	CREATE_FUNC(playerScene);
	void ShowHeroes(int IsMine);
	void CoverHeroes(int IsMine);

    Sprite* equip_for_blood;
    Sprite* equip_for_power;
    Sprite* equip_for_magic;


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

            //小小英雄的攻击、会自动扣血
            int countUnDead = 0;
            for (Hero* hero : allEnemyHeroes) {
                if (hero->isInBoard() && !hero->isDead()) {
                    countUnDead++;
                }
            }
            if (countUnDead == 0) {
                if (enemyType == 1)
                {
                    myrole->attack(enemyrole1);
                }
                else {
                    myrole->attack(enemyrole2);
                }
            }
            countUnDead = 0;
            for (Hero* hero : allMyHeroes) {
                if (hero->isInBoard() && !hero->isDead()) {
                    countUnDead++;
                }
            }
            if (countUnDead == 0) {
                if (enemyType == 1)
                {
                    enemyrole1->attack(myrole);
                }
                else {
                    enemyrole2->attack(myrole);
                }
            }
            schedule(CC_SCHEDULE_SELECTOR(playerScene::startGame), 1.0f);
        }
    }

    //通过检测fight全局变量来实现休息环节与战斗环节的交替
    void startGame(float dt) {  
        if (fight == 0) {  //退出战斗，轮到休息环节
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::startGame));  //停止外层循环回调
            static int count = 0;  //用于跳过初始界面商店的重复刷新
            if (count)
            {
                store->gold += 2;  //本次刷新是免费的
                store->refresh();   //新的环节会刷新商店

                if (store->level < 5)
                {
                    store->gold += 4;  //免费升级
                    store->upgrade();
                }

                //每一轮的额外奖励
                store->gold += 2;

                /*获取商店返还的利息*/
                // 每满10个金币可以返回一个金币的利息
                store->gold += store->gold / 10;
                store->updateUI();
            }
            count++;

            seeEnemy1->setEnabled(true);
            seeEnemy2->setEnabled(true);

            //重现我方英雄
            ShowHeroes(0);

            //撤去敌方英雄
            CoverHeroes(enemyType);


            // 改变下一次需要对战的人机
            if (enemyType == 1) {
                enemyType = 2;
            }
            else {
                enemyType = 1;
            }


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
            ShowHeroes(enemyType);
            ShowHeroes(0);
            store->setVisible(true);

            // 设置观察按键的禁用
            goback->setVisible(false);
            seeEnemy1->setEnabled(false);
            seeEnemy2->setEnabled(false);

            //开始对打
            startattack();
        }
    }

    void seeEnemy1_callback(Ref* pSender);  //观察人机1的棋盘
    void seeEnemy2_callback(Ref* pSender);  //观察人机2的棋盘
    void goback_callback(Ref* pSender);     //返回
    void enemyMove(float dt);    //人机的移动

    //检测攻击羁绊
    void detect_attack_in(float dt) {
        int tag1 = 0;
        int tag2 = 0;
        int tag4 = 0;
        for (Hero* hero : allMyHeroes) {
            if (hero->isInBoard() && hero->getType() == 1) {
                tag1 = 1;
            }
            else if (hero->isInBoard() && hero->getType() == 2) {
                tag2 = 1;
            }
            else if (hero->isInBoard() && hero->getType() == 4) {
                tag4 = 1;
            }
        }
        if (tag1 && tag2 && tag4) {  //成功构成攻击羁绊
            this->unschedule(CC_SCHEDULE_SELECTOR(playerScene::detect_attack_in));
            //显示图标、响起音效
            attacktram->setVisible(true);
            int audioId = AudioEngine::play2d("trammel.mp3");
            AudioEngine::setVolume(audioId, 1.0f);
            this->schedule(CC_SCHEDULE_SELECTOR(playerScene::detect_attack_out), 0.01f);
        }
    }
    void detect_attack_out(float dt) {
        int tag1 = 0;
        int tag2 = 0;
        int tag4 = 0;
        for (Hero* hero : allMyHeroes) {
            if (hero->isInBoard() && hero->getType() == 1) {
                tag1 = 1;
            }
            else if (hero->isInBoard() && hero->getType() == 2) {
                tag2 = 1;
            }
            else if (hero->isInBoard() && hero->getType() == 4) {
                tag4 = 1;
            }
        }
        if ((!tag1) || (!tag2) || (!tag4)) {  //成功退出攻击羁绊
            this->unschedule(CC_SCHEDULE_SELECTOR(playerScene::detect_attack_out));
            //撤去图标
            attacktram->setVisible(false);
            this->schedule(CC_SCHEDULE_SELECTOR(playerScene::detect_attack_in), 0.01f);
        }
    }

    //检测恢复羁绊
    void detect_heal_in(float dt) {
        int tag3 = 0;
        int tag5 = 0;
        int tag6 = 0;
        for (Hero* hero : allMyHeroes) {
            if (hero->isInBoard() && hero->getType() == 3) {
                tag3 = 1;
            }
            else if (hero->isInBoard() && hero->getType() == 5) {
                tag5 = 1;
            }
            else if (hero->isInBoard() && hero->getType() == 6) {
                tag6 = 1;
            }
        }
        if (tag3 && tag5 && tag6) {  //成功构成恢复羁绊
            this->unschedule(CC_SCHEDULE_SELECTOR(playerScene::detect_heal_in));
            //显示图标、响起音效
            healtram->setVisible(true);
            int audioId = AudioEngine::play2d("trammel.mp3");
            AudioEngine::setVolume(audioId, 1.0f);
            this->schedule(CC_SCHEDULE_SELECTOR(playerScene::detect_heal_out), 0.01f);
        }
    }
    void detect_heal_out(float dt) {
        int tag3 = 0;
        int tag5 = 0;
        int tag6 = 0;
        for (Hero* hero : allMyHeroes) {
            if (hero->isInBoard() && hero->getType() == 3) {
                tag3 = 1;
            }
            else if (hero->isInBoard() && hero->getType() == 5) {
                tag5 = 1;
            }
            else if (hero->isInBoard() && hero->getType() == 6) {
                tag6 = 1;
            }
        }
        if ((!tag3) || (!tag5) || (!tag6)) {  //成功退出恢复羁绊
            this->unschedule(CC_SCHEDULE_SELECTOR(playerScene::detect_heal_out));
            //撤去图标
            healtram->setVisible(false);
            this->schedule(CC_SCHEDULE_SELECTOR(playerScene::detect_heal_in), 0.01f);
        }
    }

    // 设置按键响应
    void settingCallBack(Ref* sender);

    // 将武器放置在原位置上
    void putback_equip_for_blood() {
        equip_for_blood->setScale(0.2);
        equip_for_blood->setPosition(200, 750);
        equip_for_blood->setVisible(true);
    }
    void putback_equip_for_power(){
        equip_for_power->setScale(0.2);
        equip_for_power->setPosition(200, 650);
        equip_for_power->setVisible(true);
    }
    void putback_equip_for_magic() {  
        equip_for_magic->setScale(0.2);
        equip_for_magic->setPosition(200, 550);
        equip_for_magic->setVisible(true);
    }
};

