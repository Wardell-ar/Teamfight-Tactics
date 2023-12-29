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

// ���ӵ� WebSocket ������
void ClientSocket::connectToServer() {
	webSocket = new cocos2d::network::WebSocket();

	// ʹ�� init_by_url ������ʼ�� WebSocket

	if (webSocket->init(*this, "ws://192.168.43.146:9002"))
	{
		Isconnected = 1;
		CCLOG("Connected to server");
		// �����Ѿ�����
	}
	
}

//��������
void ClientSocket::onSend(rapidjson::Document& document) {
	// �� RapidJSON �ĵ�תΪ�ַ���
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string message = buffer.GetString();
	webSocket->send(message);
}

void ClientSocket::onSendGamein(rapidjson::Document& documentGamein) {
	// �� RapidJSON �ĵ�תΪ�ַ���
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string message = buffer.GetString();
	webSocket->send(message);
}

// WebSocket ���ӳɹ��ص�
void ClientSocket::onOpen(cocos2d::network::WebSocket* ws) {
	CCLOG("WebSocket ���ӳɹ�");
}

// WebSocket �յ���Ϣ�ص�
void ClientSocket::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {

	// ������յ����ı���Ϣ
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

// WebSocket ���ӹرջص�
void ClientSocket::onClose(cocos2d::network::WebSocket* ws) {
	//CCLOG("WebSocket ���ӹر�");
	closeWebSocket();
}

// WebSocket ����ص�
void ClientSocket::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
	//CCLOG("WebSocket ������: %d", static_cast<int>(error));
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