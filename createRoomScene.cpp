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

    // �����յ��� JSON ����
    rapidjson::Document document;
    document.Parse(msg->get_payload().c_str());

    if (!document.IsObject()) {
        log("Ӣ������: a");
        std::cerr << "������Ч�� JSON ���ݸ�ʽ��" << std::endl;
        return;
    }

    // ��ȡӢ������
    if (document.HasMember("heroType") && document["heroType"].IsInt()) {
        int heroType = document["heroType"].GetInt();
        log("Ӣ������: x");
    }
    c.close(hdl, websocketpp::close::status::normal, "Disconnecting from server");

}

void on_open(websocketpp::connection_hdl hdl) {
    std::cout << "�����Ѵ򿪣����Է�����Ϣ�ˣ�" << std::endl;
    // ���� RapidJSON �ĵ�
    rapidjson::Document document;
    document.SetObject();

    // ���Ӣ�������ֶ�
    rapidjson::Value heroType(1);  // 1 represents the hero type, modify accordingly
    document.AddMember("heroType", heroType, document.GetAllocator());

    // �� RapidJSON �ĵ�תΪ�ַ���
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    std::string message = buffer.GetString();

    // ���� JSON ����
    c.send(hdl, message, websocketpp::frame::opcode::text);
}
void connect(const std::string& uri) {
    websocketpp::lib::error_code ec;
    client::connection_ptr con = c.get_connection(uri, ec);
    if (ec) {
        std::cout << "�޷��������ӣ�ԭ���ǣ�" << ec.message() << std::endl;
        return;
    }

    // ���� ASIO io_service ����ѭ��
    c.connect(con);
    c.run();
}
void reconnect(const std::string& uri) {
    c.reset(); // ���� WebSocket �ͻ��˶���
    Sleep(1000);
    connect(uri);
}
void on_close(websocketpp::connection_hdl hdl) {
    std::cout << "Disconnected from the server" << std::endl;

    // �����ӹرպ󣬿����������ӷ�����
    std::string uri = "ws://100.81.183.216:9002"; // �����µ� URI
    reconnect(uri);
}*/


Scene* createRoomScene::createScene() {
	return createRoomScene::create();
}

bool createRoomScene::init() {
	if (!Scene::init()) {  //�������ʼ������
		return false;
	}

    auto Background = Sprite::create("room.png");

    Background->setPosition(955, 540);
    Background->setScale(2);
    this->addChild(Background);


    auto playerLabel1 = Label::createWithTTF("player 1 ready", "fonts/arial.ttf", 48);
    playerLabel1->setPosition(955, 750);
    this->addChild(playerLabel1);


    //���ذ���
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
    // ��ʼ�� ASIO
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