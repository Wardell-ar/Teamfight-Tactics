#pragma once
#include"cocos2d.h"
USING_NS_CC;
#define ALL_TYPE 5


class Hero :public Sprite {
private:
    int blood;//血量
    int magic;//蓝量
    int level;//星级(1-3)
    int camp;//1表示我方阵营，0表示敌方阵营
    int heroType;//英雄种类(1-ALL_TYPE)
    int weapon;//攻击方式(1为远程，0为近战）
    int power;//攻击力
    bool inBattle;  // 标志是否处于战斗状态(1为处于战斗状态)
    bool inBoard = 0;//标记是否位于棋盘上（1表示在棋盘上，0表示在备战席）
    int seatIndex = -1;   //seat的下标
    int Die = 0;   //1表示挂了
    int exist = 1;  //1表示还在
public:
    Hero();
    // 创建不同类型的英雄
    static Hero* createHero(int heroType, const Vec2& position, int camp);
    // 移动方法
    void move(Vec2 destination);
    // 合成方法
    static void mergeHeroes(std::vector<Hero*>& all_heroes);

    // Getter 和 Setter 方法
    int getLevel() const;
    void upgrade(int newLevel);
    int getType()const;
    void updateHeroColor();
    // 进入战斗状态
    void enterBattle();

    // 退出战斗状态
    void exitBattle();

    // 是否处于战斗状态
    bool isInBattle() const;

    // 进入棋盘
    void enterBoard();

    // 退出棋盘
    void exitBoard();

    // 是否处于棋盘
    bool isInBoard() const;

    // 创建一个包含原有动作和新动作的 Spawn
    static Spawn* addAdditionalActionToSpawn(Spawn* originalSpawn, FiniteTimeAction* additionalAction);

    // 攻击方法
    static void attack();
    //获取近战还是远程
    int getWeapon() const;


    // 攻击方法，攻击指定目标
    void attack(Hero* target);

    // 在一个新线程中模拟攻击
    void attackInThread(Hero* target);

    // 减少血量方法
    void decreaseHealth(int amount);

    // 死亡方法
    void die();

    // 获取阵营
    int getCamp() const;

    // 获取血量
    int getBlood() const;

    //设置位置下标
    void setIndex(int index);

    // 设置英雄有效性
    void Setexist(int ee) {
        exist = ee;
    }

    //获取英雄有效性
    int Getexist() {
        return exist;
    }

    // 获取英雄种类
    int GetheroType() {
        return heroType;
    }

    int getLevel() {
        return level;
    }

    //获取位置
    int GetIndex() {
        return seatIndex;
    }
};
