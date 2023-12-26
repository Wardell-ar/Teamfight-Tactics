#pragma once
#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include"heroSprite.h"
#define __SHOP_LAYER_H__
USING_NS_CC;

/*
  there are totally 6 menuitem in this layer
  the first one is used to upgrade
  the second one is used to refresh the store
  the left 4 is the photo of the roles(the key items of the store)

  we use a position array to save the position of the 4 roles' position
  it will be convinent for us to refresh the store and reset the roles' photo
*/

class storeLayer : public Layer
{
public:
    int herotype[5];   //五个按键代表的英雄类型（每次都会刷新）
    int herocost[ALL_TYPE + 1] = { -1,1,5,3,2,2,4 };
    static storeLayer* createLayer();
    CREATE_FUNC(storeLayer);

    bool init() override;
    int gold;  // 金币数量
    int exp;   // 经验值
    int level;

    cocos2d::ui::LoadingBar* expBar; // 经验条
    cocos2d::Label* goldLabel;       // 显示金币数量的标签
    cocos2d::Label* levelLabel;      // 显示等级的标签

    cocos2d::ui::Button* heroButton1;
    cocos2d::ui::Button* heroButton2;
    cocos2d::ui::Button* heroButton3;
    cocos2d::ui::Button* heroButton4;
    cocos2d::ui::Button* heroButton5;

    MenuItemImage* upgradeButton;

    void updateUI(); // 更新UI显示
    void upgrade();  // 升级操作
    void refresh();  // 刷新操作

    void onUpgradeButtonClicked(cocos2d::Ref* sender);
    void onRefreshButtonClicked(cocos2d::Ref* sender);
    void createHeroButtons();  // 创建英雄按钮
    void onHeroButtonClicked(cocos2d::Ref* sender, int heroIndex);  // 英雄按钮点击事件


};

