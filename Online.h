#pragma once
#include"cocos2d.h"
#include <iostream>
#include "cocos/network/WebSocket.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "json.h"
#include "cocos/audio/include/AudioEngine.h"

using namespace cocos2d;
using namespace cocos2d::network;

USING_NS_CC;


class ClientSocket :public cocos2d::network::WebSocket::Delegate
{
public:
	// 连接到 WebSocket 服务器
	void connectToServer();

	//发送房间信息
	static void onSend(rapidjson::Document& document);

	//发送对战信息
	static void onSendGamein();

	// WebSocket 连接成功回调
	void onOpen(cocos2d::network::WebSocket* ws);

	// WebSocket 收到消息回调
	void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);

	// WebSocket 连接关闭回调
	void onClose(cocos2d::network::WebSocket* ws);

	// WebSocket 错误回调
	void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);

	static void closeWebSocket();

	// 在适当的时候清理 WebSocket 资源
	~ClientSocket();

};
















/*
#include "cocos2d.h"
#include <string.h>
#include "network/WebSocket.h"
#include "json/document.h"

USING_NS_CC;

using namespace std;
using namespace network;

class SocketService :public network::WebSocket::Delegate
{
public:

	static SocketService* socket;

	static SocketService* getInstance();

	static void delteInstance();
public:
	~SocketService();

	void initSocket();

	void sendMessage(string str);

	string getMessage();

	void setMessage(string s);

	void setPrivatePassword(string privateStr);

	string getPrivatePassword();

	void setPlayerType(string type);

	string  getPlayerType();

	void setAccount(string name);

	string  getAccount();


	virtual void onOpen(WebSocket* ws);

	virtual void onMessage(WebSocket* ws, const WebSocket::Data& data);

	virtual void onClose(WebSocket* ws);

	virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error);
private:
	WebSocket* client;

	string receiveMessage;

	bool ifReceviceMessage;

	string privatePassword;

	string playerType;

	string account;

};
*/
