#include "GameSettings.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace ui;

#include "D:\jinchanchan\cocos2d\cocos\editor-support\cocostudio\SimpleAudioEngine.h"

using namespace CocosDenshion;
//CocosGUI包含了UIButton、UIImage、Textture

Layer* GameSettings::createLayer() {
	return GameSettings::create();   //直接调用create方法
}

bool GameSettings::init()
{
	if (!Layer::init())
		return false;

	auto Background = Sprite::create("settingbackground.png");
	Background->setPosition(955, 540);
	this->addChild(Background, 100);  //添加到挂件

	//播放按钮
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//布局的基准点
	Vec2 base = Vec2(visibleSize / 2);


	//音乐
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



	//投降
	auto _button = Button::create();
	_button->setTitleText("Exit");
	_button->setTitleFontSize(100);
	_button->setPositionX(base.x);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 - 150);
	_button->addClickEventListener([](Ref* sender)
		{
			//退出游戏
			Director::getInstance()->end();
		});
	this->addChild(_button, 101);

	return true;
}

void GameSettings::onSoundControl(Ref* pSender) {
	//创建临时CCMenuItemToggle
	MenuItemToggle* temp = (MenuItemToggle*)pSender;
	//根据CCMenuItemToggle的选项来决定音乐的开关
	if (temp->getSelectedIndex() == 0) {
		//暂停播放音乐
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	if (temp->getSelectedIndex() == 1) {
		//继续播放音乐
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}



/*
	//播放按钮
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//布局的基准点
	Vec2 base = Vec2(visibleSize / 2);

	//播放按钮
	Button* _button = Button::create();
	_button->setTitleText("Play");
	_button->setTitleFontSize(36);
	_button->setPositionX(base.x);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 + 150);
	_button->addClickEventListener([](Ref* sender)
		{
			//播放音乐，true 循环播放
			SimpleAudioEngine::getInstance()->playBackgroundMusic("Bgm1.mp3", true);
			//控制音量 参数是浮点数 默认的是1.f  1.2f表示在原声音上放大
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.2f);
		});
	this->addChild(_button);

	//暂停按钮
	_button = Button::create();
	_button->setTitleText("Pause");
	_button->setTitleFontSize(36);
	_button->setPositionX(base.x);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 + 50);
	_button->addClickEventListener([](Ref* sender)
		{
			//暂停播放
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		});
	this->addChild(_button);

	//恢复按钮
	_button = Button::create();
	_button->setTitleText("Resume");
	_button->setTitleFontSize(36);
	_button->setPositionX(base.x);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 - 50);
	_button->addClickEventListener([](Ref* sender)
		{
			//恢复播放
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		});
	this->addChild(_button);

	//停止按钮
	_button = Button::create();
	_button->setTitleText("Stop");
	_button->setTitleFontSize(36);
	_button->setPositionX(base.x);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 - 150);
	_button->addClickEventListener([](Ref* sender)
		{
			//停止播放
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		});
	this->addChild(_button);

	//调大音量按钮
	_button = Button::create();
	_button->setTitleText("Turn Up");
	_button->setTitleFontSize(36);
	_button->setPositionX(base.x+200);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 - 250);
	_button->addClickEventListener([](Ref* sender)
		{
			//调大音量
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.5f);
		});
	this->addChild(_button);

	//调小音量按钮
	_button = Button::create();
	_button->setTitleText("Turn Down");
	_button->setTitleFontSize(36);
	_button->setPositionX(base.x - 200);
	_button->setPositionY(base.y + _button->getContentSize().height * 0.5 - 250);
	_button->addClickEventListener([](Ref* sender)
		{
			//调小音量
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
		});
	this->addChild(_button);
*/
