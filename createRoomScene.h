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
    // ���ӵ� WebSocket ������
    void connectToServer() {
        webSocket = new cocos2d::network::WebSocket();

        // ʹ�� init_by_url ������ʼ�� WebSocket
        if (webSocket->init(*this, "ws://100.81.183.216:9002")) {

            // ������Ϣʾ��
            std::string message = "Hello, Server!";
            webSocket->send(message);
        }
    }

    // WebSocket ���ӳɹ��ص�
    void onOpen(cocos2d::network::WebSocket* ws) {
        CCLOG("WebSocket ���ӳɹ�");
    }

    // WebSocket �յ���Ϣ�ص�
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {
        if (data.isBinary) {
            // ������յ��Ķ�������Ϣ
            CCLOG("Received binary message");
        }
        else {
            // ������յ����ı���Ϣ
            std::string message = std::string(data.bytes, data.len);
            CCLOG("Received text message: %s", message.c_str());
        }
        ws->close();
        ws = nullptr;
    }

    // WebSocket ���ӹرջص�
    void onClose(cocos2d::network::WebSocket* ws) {
        CCLOG("WebSocket ���ӹر�");
    }

    // WebSocket ����ص�
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
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
};

class createRoomScene : public Scene, ClientSocket
{
public:
    //cocos2d::network::WebSocket* webSocket;
	//��ʼ������
	static Scene* createScene();
	virtual bool init();
    /*
    // ���ӵ� WebSocket ������
    void connectToServer() {
        webSocket = new cocos2d::network::WebSocket();

        // ʹ�� init_by_url ������ʼ�� WebSocket
        if (webSocket->init(*this, "ws://100.81.183.216:9002")) {

            // ������Ϣʾ��
            std::string message = "Hello, Server!";
            webSocket->send(message);
        }
    }

    // WebSocket ���ӳɹ��ص�
    void onOpen(cocos2d::network::WebSocket* ws) {
        CCLOG("WebSocket ���ӳɹ�");
    }

    // WebSocket �յ���Ϣ�ص�
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {
        if (data.isBinary) {
            // ������յ��Ķ�������Ϣ
            CCLOG("Received binary message");
        }
        else {
            // ������յ����ı���Ϣ
            std::string message = std::string(data.bytes, data.len);
            CCLOG("Received text message: %s", message.c_str());
        }
        ws->close();
    }

    // WebSocket ���ӹرջص�
    void onClose(cocos2d::network::WebSocket* ws) {
        CCLOG("WebSocket ���ӹر�");
    }

    // WebSocket ����ص�
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
        CCLOG("WebSocket ������: %d", static_cast<int>(error));
    }

    // ���ʵ���ʱ������ WebSocket ��Դ
    virtual void onExit() override {
        if (webSocket) {
            webSocket->close();
            webSocket = nullptr;
        }

        Scene::onExit();
    }
*/
	CREATE_FUNC(createRoomScene);
	
	//���ذ�������Ӧ
	void callbackofreturn(Ref* pSender);

};

