#include "startScene.h"
#include "startLayer.h"
#include<string>
USING_NS_CC;

Scene* startScene::createScene() {
	return startScene::create();   //ֱ�ӵ���create����
}

bool startScene::init() {
	if (!Scene::init()) {  //�������ʼ������
		return false;
	}


	auto startlayer = startLayer::createLayer();  //��ȡ��ʼ���泡���ĹҼ�
	addChild(startlayer);   //��ӹҼ���Ⱦ


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

