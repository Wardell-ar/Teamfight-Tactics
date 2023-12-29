#include "startScene.h"
#include "startLayer.h"
#include<string>
USING_NS_CC;

Scene* startScene::createScene() {
	return startScene::create();   //直接调用create方法
}

bool startScene::init() {
	if (!Scene::init()) {  //若父类初始化有误
		return false;
	}


	auto startlayer = startLayer::createLayer();  //获取初始界面场景的挂件
	addChild(startlayer);   //添加挂件渲染


	return true;


	// set a listener

	auto lis = EventListenerMouse::create();
	lis->onMouseMove = CC_CALLBACK_1(startScene::get_position, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);


}

void startScene::get_position(Event* event) {
	EventMouse* e = (EventMouse*)event;
	std::string str = "MousePosition X:";
	str = str + std::to_string(e->getCursorX()) + " Y:" + std::to_string(e->getCursorY());

	auto myLabel = Label::createWithTTF(str, "Marker Felt.ttf", 24);
	this->addChild(myLabel, 20);
	myLabel->setPosition(960, 540);

}

void startScene::onEnter() {
	

	Scene::onEnter();
	connectToServer();
}

