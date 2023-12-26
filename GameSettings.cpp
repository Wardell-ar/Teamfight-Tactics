#include "GameSettings.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace ui;

#include "D:\jinchanchan\cocos2d\cocos\editor-support\cocostudio\SimpleAudioEngine.h"

using namespace CocosDenshion;
//CocosGUI������UIButton��UIImage��Textture

Layer* GameSettings::createLayer() {
	return GameSettings::create();   //ֱ�ӵ���create����
}

bool GameSettings::init()
{
	if (!Layer::init())
		return false;

	auto Background = Sprite::create("settingbackground.png");
	Background->setPosition(955, 540);
	this->addChild(Background, 100);  //��ӵ��Ҽ�

	//���Ű�ť
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//���ֵĻ�׼��
	Vec2 base = Vec2(visibleSize / 2);


	//����
	auto _openMusicItem = MenuItemImage::create("SoundButton11.png", "SoundButton12.png");
	auto _closeMusicItem = MenuItemImage::create("SoundButton21.png", "SoundButton22.png");
	MenuItemToggle* itembgm = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameSettings::onSoundControl, this),
		_closeMusicItem, _openMusicItem, NULL);
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		itembgm->setSelectedIndex(1);
	}
	else
	{
		itembgm->setSelectedIndex(0);
	}
	auto menu = Menu::create(itembgm, NULL);
	menu->setPosition(955, 650);
	this->addChild(menu,101);



	//Ͷ��
	auto _button = Button::create();
	_button->setTitleText("Exit");
	_button->setTitleFontSize(100);
	_button->setPositionX(base.x);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 - 150);
	_button->addClickEventListener([](Ref* sender)
		{
			//�˳���Ϸ
			Director::getInstance()->end();
		});
	this->addChild(_button, 101);

	return true;
}

void GameSettings::onSoundControl(Ref* pSender) {
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



/*
	//���Ű�ť
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//���ֵĻ�׼��
	Vec2 base = Vec2(visibleSize / 2);

	//���Ű�ť
	Button* _button = Button::create();
	_button->setTitleText("Play");
	_button->setTitleFontSize(36);
	_button->setPositionX(base.x);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 + 150);
	_button->addClickEventListener([](Ref* sender)
		{
			//�������֣�true ѭ������
			SimpleAudioEngine::getInstance()->playBackgroundMusic("Bgm1.mp3", true);
			//�������� �����Ǹ����� Ĭ�ϵ���1.f  1.2f��ʾ��ԭ�����ϷŴ�
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.2f);
		});
	this->addChild(_button);

	//��ͣ��ť
	_button = Button::create();
	_button->setTitleText("Pause");
	_button->setTitleFontSize(36);
	_button->setPositionX(base.x);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 + 50);
	_button->addClickEventListener([](Ref* sender)
		{
			//��ͣ����
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		});
	this->addChild(_button);

	//�ָ���ť
	_button = Button::create();
	_button->setTitleText("Resume");
	_button->setTitleFontSize(36);
	_button->setPositionX(base.x);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 - 50);
	_button->addClickEventListener([](Ref* sender)
		{
			//�ָ�����
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		});
	this->addChild(_button);

	//ֹͣ��ť
	_button = Button::create();
	_button->setTitleText("Stop");
	_button->setTitleFontSize(36);
	_button->setPositionX(base.x);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 - 150);
	_button->addClickEventListener([](Ref* sender)
		{
			//ֹͣ����
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		});
	this->addChild(_button);

	//����������ť
	_button = Button::create();
	_button->setTitleText("Turn Up");
	_button->setTitleFontSize(36);
	_button->setPositionX(base.x+200);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 - 250);
	_button->addClickEventListener([](Ref* sender)
		{
			//��������
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.5f);
		});
	this->addChild(_button);

	//��С������ť
	_button = Button::create();
	_button->setTitleText("Turn Down");
	_button->setTitleFontSize(36);
	_button->setPositionX(base.x - 200);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 - 250);
	_button->addClickEventListener([](Ref* sender)
		{
			//��С����
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
		});
	this->addChild(_button);
*/
