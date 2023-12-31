#include "startScene.h"
#include "startLayer.h"
#include "cocos/audio/include/AudioEngine.h"

USING_NS_CC;


Scene* startScene::createScene() {
	return startScene::create();   //直接调用create方法
}

bool startScene::init() {
	if (!Scene::init()) {  //若父类初始化有误
		return false;
	}


	//connectToServer();



	// 背景音乐
	int audioId = AudioEngine::play2d("welcome.mp3", -1);
	AudioEngine::setVolume(audioId, 0.05);

	
	auto item1 = cocos2d::MenuItemImage::create(
		"musicControl11.png", "musicControl12.png", CC_CALLBACK_1(startScene::musicControl, this));
	auto item2 = cocos2d::MenuItemImage::create(
		"musicControl21.png", "musicControl22.png", CC_CALLBACK_1(startScene::musicControl, this));
	auto toggleItem = cocos2d::MenuItemToggle::createWithCallback(CC_CALLBACK_1(startScene::musicControl, this), item1, item2, nullptr);
	toggleItem->setSelectedIndex(0);   // 设置初始按钮项
	auto menu = cocos2d::Menu::create(toggleItem, nullptr);
	menu->setPosition(1260, 700);
	menu->setScale(0.5);
	addChild(menu, 2);
	




	auto startlayer = startLayer::createLayer();  //获取初始界面场景的挂件
	addChild(startlayer, 1);   //添加挂件渲染
	return true;
}

void startScene::musicControl(Ref* sender) {
	// 处理菜单项切换事件
	auto toggleItem = dynamic_cast<cocos2d::MenuItemToggle*>(sender);
	if (toggleItem) {
		int selectedIndex = toggleItem->getSelectedIndex();
		if (selectedIndex == 0) {
			int audioId = AudioEngine::play2d("welcome.mp3", -1);
			AudioEngine::setVolume(audioId, 0.05);
		}
		else {
			AudioEngine::stopAll();
		}
	}
}

void startScene::onEnter() {
	Scene::onEnter();
	connectToServer();
}

