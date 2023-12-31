#include "joinRoomScene.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>

USING_NS_CC;

extern int BuildRoom;
extern int JoinRoom;
extern int GameinProgress;
extern rapidjson::Document document;


Scene* joinRoomScene::createScene() {
	return joinRoomScene::create();
}

bool joinRoomScene::init() {
	if (!Scene::init()) {  //若父类初始化出错
		return false;
	}

	auto roomBackground = Sprite::create("room.png");
	roomBackground->setPosition(955, 540);
	roomBackground->setScale(2);
	this->addChild(roomBackground);

	auto playerLabel1 = Label::createWithTTF("player 1 ready", "fonts/arial.ttf", 48);
	playerLabel1->setPosition(955, 750);
	this->addChild(playerLabel1);

	auto playerLabel2 = Label::createWithTTF("player 2 ready", "fonts/arial.ttf", 48);
	playerLabel2->setPosition(955, 550);
	this->addChild(playerLabel2);

	GameinProgress = 1;
	SendJSONstring(document);
	schedule([this](float dt) {
		ClientSocket::onSend(document);
	if (GameinProgress == 2) {
		this->unschedule("sendPlayerPosition");
		auto scene = networkScene::createScene();
		Director::getInstance()->pushScene(scene);
	}
		}, 0.05f, "sendPlayerPosition");



	/*
	//返回按键
	auto return1 = Sprite::create("helpLayerreturn1.png");
	auto return2 = Sprite::create("helpLayerreturn2.png");

	auto returnButton = MenuItemSprite::create(return1, return2,
		CC_CALLBACK_1(joinRoomScene::callbackofreturn, this));

	returnButton->setPosition(150, 980);

	auto menu = Menu::create(returnButton, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu, 1);
*/



	return true;
}

void joinRoomScene::callbackofreturn(Ref* pSender) {
	JoinRoom = 0;
	GameinProgress = 0;
	SendJSONstring(document);
	ClientSocket::onSend(document);
	Director::getInstance()->popScene();
}