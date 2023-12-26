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


// 连接到 WebSocket 服务器
void ClientSocket::connectToServer() {
    webSocket = new cocos2d::network::WebSocket();

    // 使用 init_by_url 方法初始化 WebSocket
    if (webSocket->init(*this, "ws://100.78.214.7:9002")) {

        // 发送消息示例
        std::string message = "Hello, Server!";
        webSocket->send(message);
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

// WebSocket 连接成功回调
void ClientSocket::onOpen(cocos2d::network::WebSocket* ws) {
    CCLOG("WebSocket 连接成功");
}

// WebSocket 收到消息回调
void ClientSocket::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {
    if (data.isBinary) {
        // 处理接收到的二进制消息
        CCLOG("Received binary message");
    }
    else {
        // 处理接收到的文本消息
        std::string message = std::string(data.bytes, data.len);
        CCLOG("Received text message: %s", message.c_str());
    }
    //  ws->close();
    //  ws = nullptr;
}

// WebSocket 连接关闭回调
void ClientSocket::onClose(cocos2d::network::WebSocket* ws) {
    CCLOG("WebSocket 连接关闭");
}

    // WebSocket 错误回调
void ClientSocket::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
    CCLOG("WebSocket 错误码: %d", static_cast<int>(error));
}
    /*
    // 在适当的时候清理 WebSocket 资源
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
	//接收到服务器发来的消息
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