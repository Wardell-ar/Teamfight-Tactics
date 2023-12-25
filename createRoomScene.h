#pragma once
#include"cocos2d.h"
#include <iostream>
#include "cocos/network/WebSocket.h"
using namespace cocos2d;
using namespace cocos2d::network;

USING_NS_CC;

/*
typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;

*/

class ClientSocket :public cocos2d::network::WebSocket::Delegate
{
public:
    cocos2d::network::WebSocket* webSocket;
    // 连接到 WebSocket 服务器
    void connectToServer() {
        webSocket = new cocos2d::network::WebSocket();

        // 使用 init_by_url 方法初始化 WebSocket
        if (webSocket->init(*this, "ws://100.81.183.216:9002")) {

            // 发送消息示例
            std::string message = "Hello, Server!";
            webSocket->send(message);
        }
    }

    // WebSocket 连接成功回调
    void onOpen(cocos2d::network::WebSocket* ws) {
        CCLOG("WebSocket 连接成功");
    }

    // WebSocket 收到消息回调
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {
        if (data.isBinary) {
            // 处理接收到的二进制消息
            CCLOG("Received binary message");
        }
        else {
            // 处理接收到的文本消息
            std::string message = std::string(data.bytes, data.len);
            CCLOG("Received text message: %s", message.c_str());
        }
        ws->close();
        ws = nullptr;
    }

    // WebSocket 连接关闭回调
    void onClose(cocos2d::network::WebSocket* ws) {
        CCLOG("WebSocket 连接关闭");
    }

    // WebSocket 错误回调
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
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
};

class createRoomScene : public Scene, ClientSocket
{
public:
    //cocos2d::network::WebSocket* webSocket;
	//初始化操作
	static Scene* createScene();
	virtual bool init();
    /*
    // 连接到 WebSocket 服务器
    void connectToServer() {
        webSocket = new cocos2d::network::WebSocket();

        // 使用 init_by_url 方法初始化 WebSocket
        if (webSocket->init(*this, "ws://100.81.183.216:9002")) {

            // 发送消息示例
            std::string message = "Hello, Server!";
            webSocket->send(message);
        }
    }

    // WebSocket 连接成功回调
    void onOpen(cocos2d::network::WebSocket* ws) {
        CCLOG("WebSocket 连接成功");
    }

    // WebSocket 收到消息回调
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {
        if (data.isBinary) {
            // 处理接收到的二进制消息
            CCLOG("Received binary message");
        }
        else {
            // 处理接收到的文本消息
            std::string message = std::string(data.bytes, data.len);
            CCLOG("Received text message: %s", message.c_str());
        }
        ws->close();
    }

    // WebSocket 连接关闭回调
    void onClose(cocos2d::network::WebSocket* ws) {
        CCLOG("WebSocket 连接关闭");
    }

    // WebSocket 错误回调
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
        CCLOG("WebSocket 错误码: %d", static_cast<int>(error));
    }

    // 在适当的时候清理 WebSocket 资源
    virtual void onExit() override {
        if (webSocket) {
            webSocket->close();
            webSocket = nullptr;
        }

        Scene::onExit();
    }
*/
	CREATE_FUNC(createRoomScene);
	
	//返回按键的响应
	void callbackofreturn(Ref* pSender);

};

