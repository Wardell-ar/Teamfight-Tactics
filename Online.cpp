#include "cocos2d.h"
#include "Online.h"
#include <iostream>
#include "cocos/network/WebSocket.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

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
int Gamein;

// 连接到 WebSocket 服务器
void ClientSocket::connectToServer() {
	webSocket = new cocos2d::network::WebSocket();

	// 使用 init_by_url 方法初始化 WebSocket

	if (webSocket->init(*this, "ws://192.168.43.146:9002"))
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

void ClientSocket::onSendGamein(rapidjson::Document& documentGamein) {
	// 将 RapidJSON 文档转为字符串
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string message = buffer.GetString();
	webSocket->send(message);
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
	else if(Gamein == 0){
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