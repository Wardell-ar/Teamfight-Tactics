#include "cocos2d.h"
#include "Online.h"
#include <iostream>
#include "cocos/network/WebSocket.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include"endScene.h"

using namespace cocos2d;
using namespace cocos2d::network;

USING_NS_CC;

cocos2d::network::WebSocket* webSocket = nullptr;
rapidjson::Document document;
rapidjson::Document documentGamein;

int BuildRoom = 0;
int JoinRoom = 0;
int GameinProgress = 0;
int Isconnected = 0;
int Gamein = 0;

// 连接到 WebSocket 服务器
void ClientSocket::connectToServer() {
	webSocket = new cocos2d::network::WebSocket();

	// 使用 init_by_url 方法初始化 WebSocket

	if (webSocket->init(*this, "ws://100.81.180.38:9002"))
	{
		Isconnected = 1;
		CCLOG("Connected to server");
		// 连接已经建立
	}

}

//传输数据
void ClientSocket::onSend(rapidjson::Document& document) {
	// 将 RapidJSON 文档转为字符串
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string message = buffer.GetString();
	webSocket->send(message);
}

void ClientSocket::onSendGamein() {
	// 将 RapidJSON 文档转为字符串
	rapidjson::StringBuffer buffer1;
	rapidjson::Writer<rapidjson::StringBuffer> writer1(buffer1);
	document.Accept(writer1);
	std::string message1 = buffer1.GetString();
	webSocket->send(message1);
}

// WebSocket 连接成功回调
void ClientSocket::onOpen(cocos2d::network::WebSocket* ws) {
	CCLOG("WebSocket 连接成功");
}

// WebSocket 收到消息回调
void ClientSocket::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {

	// 处理接收到的文本消息
	std::string message = std::string(data.bytes);
	if (message == "start") {
		GameinProgress = 2;
	}
	else if (message == "win") {
		auto endscene = endScene::createScene(1);
		Director::getInstance()->pushScene(endscene);
		AudioEngine::stopAll();
		int audioId = AudioEngine::play2d("victory.mp3");
		AudioEngine::setVolume(audioId, 1.0f);
	}
	else if (Gamein == 0) {
		ReceiveJSONstring(message);
	}
	else {
		ReceiveJSONstringGamein(message);
	}
}

// WebSocket 连接关闭回调
void ClientSocket::onClose(cocos2d::network::WebSocket* ws) {
	//CCLOG("WebSocket 连接关闭");
	closeWebSocket();
}

// WebSocket 错误回调
void ClientSocket::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
	//CCLOG("WebSocket 错误码: %d", static_cast<int>(error));
	Isconnected = 0;
	closeWebSocket();
}

void ClientSocket::closeWebSocket() {
	if (webSocket) {
		webSocket->close();
		webSocket = nullptr;
	}
}


ClientSocket::~ClientSocket() {
	if (webSocket) {
		CCLOG("Connected to server");
		webSocket->close();
		webSocket = nullptr;
	}
}