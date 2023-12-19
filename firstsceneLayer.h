#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"hero.h"
#define __SHOP_LAYER_H__

USING_NS_CC;

class firstsceneLayer : public Layer
{
public:
	//��ʼ��
	static Layer* createLayer() {
		return firstsceneLayer::create();  //ֱ�ӵ���create����
	}
	virtual bool init();
	void callbackofbuttonuplevel(Ref* pSender);  //uplevel button
	void callbackofbuttonrefresh(Ref* pSender);  //refresh button
	CREATE_FUNC(firstsceneLayer);
};


class ShopLayer : public cocos2d::Layer {
public:
    static Layer* createShopLayer() {
        return ShopLayer::create();  //ֱ�ӵ���create����
    }
    CREATE_FUNC(ShopLayer);

    bool init() override;

private:
    int gold;  // �������
    int exp;   // ����ֵ
    int level;
    int herocost;// �ȼ�

    cocos2d::ui::LoadingBar* expBar; // ������
    cocos2d::Label* goldLabel;       // ��ʾ��������ı�ǩ
    cocos2d::Label* levelLabel;      // ��ʾ�ȼ��ı�ǩ

    cocos2d::ui::Button* heroButton1;
    cocos2d::ui::Button* heroButton2;
    cocos2d::ui::Button* heroButton3;
    cocos2d::ui::Button* heroButton4;
    cocos2d::ui::Button* heroButton5;

    void updateUI(); // ����UI��ʾ
    void upgrade();  // ��������
    void refresh();  // ˢ�²���

    void onUpgradeButtonClicked(cocos2d::Ref* sender);
    void onRefreshButtonClicked(cocos2d::Ref* sender);
    void createHeroButtons();  // ����Ӣ�۰�ť
    void onHeroButtonClicked(cocos2d::Ref* sender, int heroIndex);  // Ӣ�۰�ť����¼�
};

