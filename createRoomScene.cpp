#include "createRoomScene.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <boost/thread/thread.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>



USING_NS_CC;
/*
void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get()
        << " and message: " << msg->get_payload()
        << std::endl;

    // check for a special command to instruct the server to stop listening so
    // it can be cleanly exited.
    if (msg->get_payload() == "stop-listening") {
        s->stop_listening();
        return;
    }

    try {
        s->send(hdl, msg->get_payload(), msg->get_opcode());
    }
    catch (websocketpp::exception const& e) {
        std::cout << "Echo failed because: "
            << "(" << e.what() << ")" << std::endl;
    }
}*/

/*
typedef websocketpp::client<websocketpp::config::asio_client> client;
client c;

void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg) {

    std::cout << msg->get_payload() << std::endl;

    // 解析收到的 JSON 数据
    rapidjson::Document document;
    document.Parse(msg->get_payload().c_str());

    if (!document.IsObject()) {
        log("英雄类型: a");
        std::cerr << "错误：无效的 JSON 数据格式！" << std::endl;
        return;
    }

    // 获取英雄类型
    if (document.HasMember("heroType") && document["heroType"].IsInt()) {
        int heroType = document["heroType"].GetInt();
        log("英雄类型: x");
    }
    c.close(hdl, websocketpp::close::status::normal, "Disconnecting from server");

}

void on_open(websocketpp::connection_hdl hdl) {
    std::cout << "连接已打开，可以发送消息了！" << std::endl;
    // 创建 RapidJSON 文档
    rapidjson::Document document;
    document.SetObject();

    // 添加英雄类型字段
    rapidjson::Value heroType(1);  // 1 represents the hero type, modify accordingly
    document.AddMember("heroType", heroType, document.GetAllocator());

    // 将 RapidJSON 文档转为字符串
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    std::string message = buffer.GetString();

    // 发送 JSON 数据
    c.send(hdl, message, websocketpp::frame::opcode::text);
}
void connect(const std::string& uri) {
    websocketpp::lib::error_code ec;
    client::connection_ptr con = c.get_connection(uri, ec);
    if (ec) {
        std::cout << "无法创建连接，原因是：" << ec.message() << std::endl;
        return;
    }

    // 启动 ASIO io_service 运行循环
    c.connect(con);
    c.run();
}
void reconnect(const std::string& uri) {
    c.reset(); // 重置 WebSocket 客户端对象
    Sleep(1000);
    connect(uri);
}
void on_close(websocketpp::connection_hdl hdl) {
    std::cout << "Disconnected from the server" << std::endl;

    // 在连接关闭后，可以重新连接服务器
    std::string uri = "ws://100.81.183.216:9002"; // 设置新的 URI
    reconnect(uri);
}*/


Scene* createRoomScene::createScene() {
	return createRoomScene::create();
}

bool createRoomScene::init() {
	if (!Scene::init()) {  //若父类初始化出错
		return false;
	}

    auto Background = Sprite::create("room.png");

    Background->setPosition(955, 540);
    Background->setScale(2);
    this->addChild(Background);


    auto playerLabel1 = Label::createWithTTF("player 1 ready", "fonts/arial.ttf", 48);
    playerLabel1->setPosition(955, 750);
    this->addChild(playerLabel1);


    //返回按键
    auto return1 = Sprite::create("helpLayerreturn1.png");
    auto return2 = Sprite::create("helpLayerreturn2.png");

    auto returnButton = MenuItemSprite::create(return1, return2,
        CC_CALLBACK_1(createRoomScene::callbackofreturn, this));

    returnButton->setPosition(150, 980);

    auto menu = Menu::create(returnButton, NULL);
    menu->setPosition(0, 0);
    this->addChild(menu, 1);
    
    connectToServer();

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

void createRoomScene::callbackofreturn(Ref* pSender) {
    Director::getInstance()->popScene();   
}