#include "createRoomScene.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>



USING_NS_CC;


extern int BuildRoom;
extern int JoinRoom;
extern int GameinProgress;
extern rapidjson::Document document;

Scene* createRoomScene::createScene() {
    return createRoomScene::create();
}

bool createRoomScene::init() {
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


    schedule([this](float dt) {
        if (JoinRoom == 1) {
            auto playerLabel2 = Label::createWithTTF("player 2 ready", "fonts/arial.ttf", 48);
            playerLabel2->setPosition(955, 550);
            this->addChild(playerLabel2);
            // 满足条件时取消定时器
            if (GameinProgress == 2) {
                this->unschedule("sendPlayerPosition");
                auto scene = networkScene::createScene();
                Director::getInstance()->pushScene(scene);
            }
        }
        }, 0.05f, "sendPlayerPosition");



    /*
    //返回按键
    auto return1 = Sprite::create("helpLayerreturn1.png");
    auto return2 = Sprite::create("helpLayerreturn2.png");

    auto returnButton = MenuItemSprite::create(return1, return2,
        CC_CALLBACK_1(createRoomScene::callbackofreturn, this));

    returnButton->setPosition(150, 980);

    auto menu = Menu::create(returnButton, NULL);
    menu->setPosition(0, 0);
    this->addChild(menu, 1);
    */

    /*
    std::string uri = "ws://100.81.183.216:9002";

    c.set_access_channels(websocketpp::log::alevel::all);
    c.clear_access_channels(websocketpp::log::alevel::frame_payload);
    c.set_error_channels(websocketpp::log::elevel::all);
    // 初始化 ASIO
    c.init_asio();

    c.set_message_handler(&on_message);
    c.set_open_handler(&on_open);
    c.set_close_handler(&on_close);
    connect(uri);*/


    /*
    server echo_server;

    try {
        // Set logging settings
        echo_server.set_access_channels(websocketpp::log::alevel::all);
        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        echo_server.init_asio();

        // Register our message handler
        echo_server.set_message_handler(bind(&on_message, &echo_server, ::_1, ::_2));


        // std::string ip_address = "192.168.1.100";
        // uint16_t port = 9002;
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 9002);

        // Listen on port 9002
        echo_server.listen(endpoint);

        // Start the server accept loop
        echo_server.start_accept();

        // Start the ASIO io_service run loop
        echo_server.run();
    }
    catch (websocketpp::exception const& e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "other exception" << std::endl;
    }*/

    return true;
}

//void createRoomScene::callbackofreturn(Ref* pSender) {
//    BuildRoom = 0;
//    SendJSONstring();
//    ClientSocket::onSend(document);
//    Director::getInstance()->popScene();  
//    CCLOG("Connected to server");
//    connectToServer();
//}