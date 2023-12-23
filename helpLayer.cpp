#include "helpLayer.h"
#include "network/HttpClient.h"
#include "cocos/network/WebSocket.h"

USING_NS_CC;
using namespace network;

Layer* helpLayer::createLayer() {
	return helpLayer::create();
}


bool helpLayer::init() {
	if (!Layer::init()) {  //�������ʼ������
		return false;
	}
	/*
	HttpRequest* request = new HttpRequest();
	request->setUrl("http://127.0.0.1");
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback([](HttpClient* client, HttpResponse* response) {
		if (!response || !response->isSucceed()) {
			log("HTTP request failed");
			return;
		}

		// �����������Ӧ
		std::vector<char>* buffer = response->getResponseData();
		std::string responseData(buffer->begin(), buffer->end());
		log("Response data: %s", responseData.c_str());
		});

	HttpClient::getInstance()->send(request);
	request->release();*/

	//����˵���ְ�
	auto Background = Sprite::create("helpLayerBackground.png");
	Background->setPosition(960, 540);
	this->addChild(Background, 0);

	//���ذ���
	auto return1 = Sprite::create("helpLayerreturn1.png");
	auto return2 = Sprite::create("helpLayerreturn2.png");

	auto returnButton = MenuItemSprite::create(return1, return2,
		CC_CALLBACK_1(helpLayer::callbackofreturn, this));

	returnButton->setPosition(150, 980);

	auto menu = Menu::create(returnButton, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu, 1);

	return true;
}


//���ذ�����Ӧ
void helpLayer::callbackofreturn(Ref* pSender) {
	Director::getInstance()->popScene();   //��ʼ�����ջ
}