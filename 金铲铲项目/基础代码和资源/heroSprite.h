#pragma once
#include"cocos2d.h"
USING_NS_CC;
#define ALL_TYPE 6


class Hero :public Sprite {
private:
    float blood;//血量
    float max_blood;
    int each_magic;//每次增加蓝量
    int start_magic;//初始magic
    int magic;//蓝量
    int level;//星级(1-3)
    int camp;//1表示我方阵营，0表示敌方阵营
    int heroType;//英雄种类(1-ALL_TYPE)
    int weapon;//攻击方式(1为远程，0为近战）
    int power;//普攻伤害
    int skill;//技能伤害

    

    bool inBoard = 0;//标记是否位于棋盘上（1表示在棋盘上，0表示在备战席）
    int seatIndex = -1;   //seat的下标
    int Die = 0;   //1表示挂了
    int click = 0;   //用于点击判定
    ProgressTimer* healthBar;//血条类
    ProgressTimer* magicBar;//蓝条类
public:

    // 看是否有装备
    int equip_blood = 0;
    int equip_magic = 0;
    int equip_power = 0;

    Hero();
    // 创建不同类型的英雄
    static Hero* createHero(int heroType, const Vec2& position, int camp);
    // 移动方法
    void move(Vec2 destination);
    // 合成方法
    static void mergeHeroes();

    // Getter 和 Setter 方法
    int getLevel() const;
    void upgrade(int newLevel);
    int getType()const;


    // 进入棋盘
    void enterBoard();

    // 退出棋盘
    void exitBoard();

    // 是否处于棋盘
    bool isInBoard() const;

    //获取近战还是远程
    int getWeapon() const;


    // 攻击方法，攻击指定目标
    void attack(Hero* target);

    // 减少血量方法
    void decreaseHealth(int amount);

    // 死亡方法
    void die();

    // 获取阵营
    int getCamp() const;

    // 获取血量
    float getBlood();

    //设置位置下标
    void setIndex(int index);


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

    //判断是否被点击
    int IsClicked() {
        return click;
    }

    //设置点击
    void SetClicked(int c) {
        click = c;
    }

    //设置Borad变量值
    void SetBoard(int b) {
        inBoard = b;
    }

    int isDead() {
        return Die;
    }

    void setDie(int d) {
        Die = d;
    }

    float getMaxBlood() {
        return max_blood;
    }

    void setBlood(float b) {
        blood = b;
    }

    void setMagic(int m) {
        magic = m;
    }

    void updatebloodandmagic();

    int getStartMagic() {
        return start_magic;
    }

    int getMagic() {
        return magic;
    }

    int getEachMagic() {
        return each_magic;
    }

    int getPower() {
        return power;
    }

    int getSkill() {
        return skill;
    }

    void setMaxBlood(int m) {
        max_blood = m;
    }

    void setPower(int m) {
        power = m;
    }

    void setEachMagic(int m) {
        each_magic = m;
    }
};