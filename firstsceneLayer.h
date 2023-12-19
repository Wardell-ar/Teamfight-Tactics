#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"hero.h"
#define __SHOP_LAYER_H__

USING_NS_CC;

class firstsceneLayer : public Layer
{
public:
	//初始化
	static Layer* createLayer() {
		return firstsceneLayer::create();  //直接调用create方法
	}
	virtual bool init();
	void callbackofbuttonuplevel(Ref* pSender);  //uplevel button
	void callbackofbuttonrefresh(Ref* pSender);  //refresh button
	CREATE_FUNC(firstsceneLayer);
};


class ShopLayer : public cocos2d::Layer {
public:
    static Layer* createShopLayer() {
        return ShopLayer::create();  //直接调用create方法
    }
    CREATE_FUNC(ShopLayer);

    bool init() override;

private:
    int gold;  // 金币数量
    int exp;   // 经验值
    int level;
    int herocost;// 等级

    cocos2d::ui::LoadingBar* expBar; // 经验条
    cocos2d::Label* goldLabel;       // 显示金币数量的标签
    cocos2d::Label* levelLabel;      // 显示等级的标签

    cocos2d::ui::Button* heroButton1;
    cocos2d::ui::Button* heroButton2;
    cocos2d::ui::Button* heroButton3;
    cocos2d::ui::Button* heroButton4;
    cocos2d::ui::Button* heroButton5;

    void updateUI(); // 更新UI显示
    void upgrade();  // 升级操作
    void refresh();  // 刷新操作

    void onUpgradeButtonClicked(cocos2d::Ref* sender);
    void onRefreshButtonClicked(cocos2d::Ref* sender);
    void createHeroButtons();  // 创建英雄按钮
    void onHeroButtonClicked(cocos2d::Ref* sender, int heroIndex);  // 英雄按钮点击事件
};

