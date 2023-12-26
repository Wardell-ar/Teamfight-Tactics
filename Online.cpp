#include"cocos2d.h"
#include"Online.h"
#include <iostream>
#include "cocos/network/WebSocket.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace cocos2d;
using namespace cocos2d::network;

USING_NS_CC;

cocos2d::network::WebSocket* webSocket;
rapidjson::Document document;


// ���ӵ� WebSocket ������
void ClientSocket::connectToServer() {
    webSocket = new cocos2d::network::WebSocket();

    // ʹ�� init_by_url ������ʼ�� WebSocket
    if (webSocket->init(*this, "ws://100.78.214.7:9002")) {

        // ������Ϣʾ��
        std::string message = "Hello, Server!";
        webSocket->send(message);
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

// WebSocket ���ӳɹ��ص�
void ClientSocket::onOpen(cocos2d::network::WebSocket* ws) {
    CCLOG("WebSocket ���ӳɹ�");
}

// WebSocket �յ���Ϣ�ص�
void ClientSocket::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {
    if (data.isBinary) {
        // ������յ��Ķ�������Ϣ
        CCLOG("Received binary message");
    }
    else {
        // ������յ����ı���Ϣ
        std::string message = std::string(data.bytes, data.len);
        CCLOG("Received text message: %s", message.c_str());
    }
    //  ws->close();
    //  ws = nullptr;
}

// WebSocket ���ӹرջص�
void ClientSocket::onClose(cocos2d::network::WebSocket* ws) {
    CCLOG("WebSocket ���ӹر�");
}

    // WebSocket ����ص�
void ClientSocket::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
    CCLOG("WebSocket ������: %d", static_cast<int>(error));
}
    /*
    // ���ʵ���ʱ������ WebSocket ��Դ
    virtual void onExit() override {
        if (webSocket) {
            webSocket->close();
            webSocket = nullptr;
        }

        Scene::onExit();
    }*/













/*
SocketService* SocketService::socket = NULL;

SocketService::~SocketService()
{
	client->close();
}

SocketService* SocketService::getInstance()
{
	if (socket == NULL)
	{
		socket = new SocketService();
	}
	return socket;
}
void SocketService::initSocket()
{
	auto s = FileUtils::getInstance()->getStringFromFile("Data.json");
	rapidjson::Document doc;
	doc.Parse<0>(s.c_str());
	auto ip = doc["ip"].GetString();
	auto port = doc["port"].GetInt();
	//string str = String::createWithFormat("ws://%s:%d", ip, port)->getCString();
	client = new WebSocket();
	//client->init(*this, str);

	receiveMessage = "";
	ifReceviceMessage = false;
	privatePassword = "";
}



void SocketService::onOpen(WebSocket* ws)
{
	log("connect successful");
}
void SocketService::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
	//���յ���������������Ϣ
	log("%s", data.bytes);

	receiveMessage = data.bytes;

	ifReceviceMessage = true;
}

void SocketService::onClose(WebSocket* ws)
{
	log("connect stop");
}

void SocketService::onError(WebSocket* ws, const WebSocket::ErrorCode& error)
{

}

void SocketService::delteInstance()
{
	if (socket)
	{
		delete socket;
		socket = NULL;
	}
}

void SocketService::sendMessage(string str)
{
	log("%s", str.c_str());
	client->send(str);
}

std::string SocketService::getMessage()
{
	return receiveMessage;
}

void SocketService::setPrivatePassword(string privateStr)
{
	privatePassword = privateStr;
}

std::string SocketService::getPrivatePassword()
{
	return privatePassword;
}

void SocketService::setMessage(string s)
{
	receiveMessage = s;
}

void SocketService::setPlayerType(string type)
{
	this->playerType = type;
}

string SocketService::getPlayerType()
{
	return playerType;
}

void SocketService::setAccount(string name)
{
	this->account = name;
}

std::string SocketService::getAccount()
{
	return this->account;
}*/