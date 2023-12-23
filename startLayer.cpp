#include "startLayer.h"
#include"helpScene.h"
#include "playerScene.h"
#include "ui/CocosGUI.h"
#include "GameSettings.h"

USING_NS_CC;

using namespace ui;

#include "D:\jinchanchan\cocos2d\cocos\editor-support\cocostudio\SimpleAudioEngine.h"

using namespace CocosDenshion;
//CocosGUI������UIButton��UIImage��Textture


Layer* startLayer::createLayer() {
	return startLayer::create();  //ֱ�ӵ���create����
}


bool startLayer::init() {
	if (!Layer::init()) {   //�������ʼ������
		return false;
	}

	//�������
	auto Background = Sprite::create("startSceneBackground.png");
	Background->setPosition(960, 540);
	this->addChild(Background, 0);  //��ӵ��Ҽ�

	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Bgm1.mp3", true);

	auto set1 = Sprite::create("SetButton2.png");
	auto set2 = Sprite::create("SetButton1.png");

	auto _set = MenuItemSprite::create(set1, set2,
		CC_CALLBACK_1(startLayer::callbackof_set, this));

	auto SET = Menu::create(_set, NULL);
	SET->setPosition(1795, 990);
	this->addChild(SET, 3);

	/*auto _openMusicItem = MenuItemImage::create(
		"SoundButton11.png",
		"SoundButton12.png"
	);
	auto _closeMusicItem = MenuItemImage::create(
		"SoundButton21.png",
		"SoundButton22.png");
	
	MenuItemToggle* itembgm = MenuItemToggle::createWithCallback(CC_CALLBACK_1(startLayer::onSoundControl, this),
		_closeMusicItem, _openMusicItem, NULL);
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		itembgm->setSelectedIndex(0);
	}
	else
	{
		itembgm->setSelectedIndex(1);
	}
	auto menu = Menu::create(itembgm, NULL);
	menu->setPosition(1700,900);
	this->addChild(menu);*/


	//�������ѡ���ͼƬ����
	/* ��ʼ��Ϸ */
	auto button11 = Sprite::create("startSceneButton11.png");
	auto button12 = Sprite::create("startSceneButton12.png");
	/* �������� */
	auto button21 = Sprite::create("startSceneButton21.png");
	auto button22 = Sprite::create("startSceneButton22.png");
	/* ���뷿�� */
	auto button31 = Sprite::create("startSceneButton31.png");
	auto button32 = Sprite::create("startSceneButton32.png");
	/* ���� */
	auto button41 = Sprite::create("startSceneButton41.png");
	auto button42 = Sprite::create("startSceneButton42.png");
	/* �˳� */
	auto button51 = Sprite::create("startSceneButton51.png");
	auto button52 = Sprite::create("startSceneButton52.png");

	//���ͼƬΪMenu��
	auto button1 = MenuItemSprite::create(button11, button12,
		CC_CALLBACK_1(startLayer::callbackofbutton1, this));
	auto button2 = MenuItemSprite::create(button21, button22,
		CC_CALLBACK_1(startLayer::callbackofbutton2, this));
	auto button3 = MenuItemSprite::create(button31, button32,
		CC_CALLBACK_1(startLayer::callbackofbutton3, this));
	auto button4 = MenuItemSprite::create(button41, button42,
		CC_CALLBACK_1(startLayer::callbackofbutton4, this));
	auto button5 = MenuItemSprite::create(button51, button52,
		CC_CALLBACK_1(startLayer::callbackofbutton5, this));

	auto startMenu = Menu::create(button1, button2, button3, button4, button5, NULL);  //һ�����˵�
	startMenu->alignItemsVerticallyWithPadding(15);  //���ô�ֱ����
	startMenu->setPosition(960, 400);  //�ڳ����еĲ���
	this->addChild(startMenu, 1);   //��ӵ��Ҽ�

	return true;
}


//������Ӧ

/* ��ʼ��Ϸ */
void startLayer::callbackofbutton1(Ref* pSender)   //��ʼ��Ϸ
{
	auto start = playerScene::createScene();
	Director::getInstance()->pushScene(start);   //�˳�
}

/* �������� */
void startLayer::callbackofbutton2(Ref* pSender)   //��������
{
	auto createroomscene = createRoomScene::createScene();
	Director::getInstance()->pushScene(createroomscene);
}

/* ���뷿�� */
void startLayer::callbackofbutton3(Ref* pSender)   //���뷿��
{
	Director::getInstance()->end();   //�˳�
}

/* ���� */
void startLayer::callbackofbutton4(Ref* pSender)   //����
{
	auto helpscene = helpScene::createScene();
	Director::getInstance()->pushScene(helpscene);   //ѹջ
}

/* �˳� */
void startLayer::callbackofbutton5(Ref* pSender)   //�˳�
{
	Director::getInstance()->end();   //�˳�
}

void startLayer::onSoundControl(Ref* pSender) {
	//������ʱCCMenuItemToggle
	MenuItemToggle* temp = (MenuItemToggle*)pSender;
	//����CCMenuItemToggle��ѡ�����������ֵĿ���
	if (temp->getSelectedIndex() == 0) {
		//��ͣ��������
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	if (temp->getSelectedIndex() == 1) {
		//������������
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}

void startLayer::callbackof_set(Ref* pSender)   //��������
{
	auto gamesettings = GameSettings::createLayer(); //����
	this->addChild(gamesettings, 100);

	auto closeLayerButton = Button::create("back1.png", "back2.png");
	closeLayerButton->setPosition(Vec2(1150, 750));
	this->addChild(closeLayerButton, 101);
	closeLayerButton->addClickEventListener([=](Ref* sender) {
		// �Ƴ�Layer
		gamesettings->removeFromParentAndCleanup(true);
		closeLayerButton->removeFromParentAndCleanup(true);
		});

}