
//#include <websocketpp/config/asio_no_tls.hpp>
//
//#include <websocketpp/server.hpp>
//
//#include <iostream>
//
//typedef websocketpp::server<websocketpp::config::asio> server;
//
//using websocketpp::lib::placeholders::_1;
//using websocketpp::lib::placeholders::_2;
//using websocketpp::lib::bind;
//
//// pull out the type of messages sent by our config
//typedef server::message_ptr message_ptr;
//
//// Define a callback to handle incoming messages
//void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
//    std::cout << "on_message called with hdl: " << hdl.lock().get()
//              << " and message: " << msg->get_payload()
//              << std::endl;
//
//    // check for a special command to instruct the server to stop listening so
//    // it can be cleanly exited.
//    if (msg->get_payload() == "stop-listening") {
//        s->stop_listening();
//        return;
//    }
//
//    try {
//        s->send(hdl, msg->get_payload(), msg->get_opcode());
//    } catch (websocketpp::exception const & e) {
//        std::cout << "Echo failed because: "
//                  << "(" << e.what() << ")" << std::endl;
//    }
//}
//
//int main() {
//    // Create a server endpoint
//    server echo_server;
//
//    try {
//        // Set logging settings
//        echo_server.set_access_channels(websocketpp::log::alevel::all);
//        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);
//
//        // Initialize Asio
//        echo_server.init_asio();
//
//        // Register our message handler
//        echo_server.set_message_handler(bind(&on_message,&echo_server,::_1,::_2));
//
//
//     // std::string ip_address = "192.168.1.100";
//     // uint16_t port = 9002;
//        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 9002);
//
//        // Listen on port 9002
//        echo_server.listen(endpoint);
//
//        // Start the server accept loop
//        echo_server.start_accept();
//
//        // Start the ASIO io_service run loop
//        echo_server.run();
//    } catch (websocketpp::exception const & e) {
//        std::cout << e.what() << std::endl;
//    } catch (...) {
//        std::cout << "other exception" << std::endl;
//    }
//}


#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/client.hpp>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <set>
#include <vector>
using namespace std;

typedef websocketpp::server<websocketpp::config::asio> server_;

// ����һ���Զ�����Ϣ������
class MyHandler : public websocketpp::server<websocketpp::config::asio>::message_handler {
public:
    // ���յ���Ϣʱ���ô˻ص�����
    void on_message(websocketpp::connection_hdl hdl, server_::message_ptr msg) {
        // ����JSON��Ϣ
        rapidjson::Document document;
        document.Parse(msg->get_payload().c_str());
        // �������Ƿ�ɹ�
        if (!document.IsObject()) {
            std::cerr << "�޷�����JSON��Ϣ" << std::endl;
            return;
        }

        if (document.HasMember("GameinProgress") && document["GameinProgress"].IsInt()
            && document.HasMember("Gamein") && document["Gamein"].IsInt()) {
            int Type1 = document["GameinProgress"].GetInt();
            int Type2 = document["Gamein"].GetInt();
            if (Type2 == 0) {
                // ��������
                if (document.HasMember("BuildRoom") && document["BuildRoom"].IsInt()) {
                    for (auto it : connections_) {
                        try {
                            server.send(it, msg->get_payload(), websocketpp::frame::opcode::text);
                        }
                        catch (const exception& e) {
                            cout << "Error sending message: " << e.what() << endl;
                        }
                    }
                }
                // ���뷿��
                if (document.HasMember("JoinRoom") && document["JoinRoom"].IsInt()) {
                    //int Type = document["JoinRoom"].GetInt();
                    for (auto it : connections_) {
                        try {
                            server.send(it, msg->get_payload(), websocketpp::frame::opcode::text);
                        }
                        catch (const exception& e) {
                            cout << "Error sending message: " << e.what() << endl;
                        }
                    }
                }
                //��ʼ��ս
                if (document.HasMember("GameinProgress") && document["GameinProgress"].IsInt()) {
                    int Type = document["GameinProgress"].GetInt();
                    if (Type == 1) {
                        for (auto it : connections_) {
                            try {
                                server.send(it, "start", websocketpp::frame::opcode::text);
                            }
                            catch (const exception& e) {
                                cout << "Error sending message: " << e.what() << endl;
                            }
                        }
                    }
                }
            }
            else {//��ս��Ϣ
                cout << "saddddddddddddddddddddddddddddddddddddddddddddddddddddd";
                for (auto it = connections_.begin(); it != connections_.end(); ++it) {
                    try {
                        if (it->lock() != hdl.lock()) {
                           
                            server.send(it->lock(), msg->get_payload(), websocketpp::frame::opcode::text);
                        }
                    }
                    catch (const exception& e) {
                        cout << "Error sending message: " << e.what() << endl;
                    }
                }
            }
        }         
    }

    // �����µ����ӽ���ʱ����
    void on_open(websocketpp::connection_hdl hdl) {
        cout << "Client connected!" << endl;

        // �������Ӽ������Ӽ���
        connections_.insert(hdl);

        // ����������ﵽ��������ʼ��Ϣ����
        if (connections_.size() == 2) {
            broadcast("Two clients connected. Start exchanging messages.");
        }
    }
    // �����ӹر�ʱ����
    void on_close(websocketpp::connection_hdl hdl) {
        cout << "Client disconnected!" << endl;

        // �����Ӽ������Ƴ��رյ�����
        connections_.erase(hdl);
    }
    void broadcast(const string& message) {
        for (auto it = connections_.begin(); it != connections_.end(); ++it) {
            try {
                server.send(*it, message, websocketpp::frame::opcode::text);
            }
            catch (const exception& e) {
                cout << "Error sending message: " << e.what() << endl;
            }
        }
    }
    
    // WebSocket++������ʵ��
    websocketpp::server<websocketpp::config::asio> server;
    set<websocketpp::connection_hdl, owner_less<websocketpp::connection_hdl>> connections_;

};


int main() {
    try {
        MyHandler handler;
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");

        boost::asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);
        boost::asio::ip::tcp::resolver::iterator end;

        while (endpoints != end) {
            boost::asio::ip::tcp::endpoint endpoint = *endpoints++;
            std::cout << "IP Address: " << endpoint.address().to_string() << std::endl;
        }

        // ����WebSocket++������
        handler.server.init_asio();

        
        handler.server.set_access_channels(websocketpp::log::alevel::all);
        handler.server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        handler.server.set_message_handler(websocketpp::lib::bind(
            &MyHandler::on_message, &handler, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2
        ));
        handler.server.set_open_handler(bind(&MyHandler::on_open, &handler, std::placeholders::_1));
        handler.server.set_close_handler(bind(&MyHandler::on_close, &handler, std::placeholders::_1));
        
       
        // �����ڶ˿�9002
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v6(), 9002); 
        handler.server.listen(endpoint);

        // ��������������ѭ��
        handler.server.start_accept();

        // ����ASIO io_service����ѭ��
        handler.server.run();
    }
    catch (websocketpp::exception const& e) {
        std::cerr << "����" << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "δ֪�쳣" << std::endl;
    }

    return 0;
}

/*
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg) {
    try {
        rapidjson::Document document;
        document.Parse(msg->get_payload().c_str());

        if (!document.HasParseError()) {
            // �����ﴦ���յ���JSON����
            // ���������Լ����߼�����������
            if (document.HasMember("heroType") && document["heroType"].IsInt()) {
                int heroType = document["heroType"].GetInt();
                std::cout << "Ӣ������: " << heroType << std::endl;
            }
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);
            std::string message = buffer.GetString();
            // ����Ϣ�㲥���������ӵĿͻ���
            s->send(hdl, msg->get_payload(), msg->get_opcode());

        }
        else {
            std::cerr << "Error parsing JSON message" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error processing message: " << e.what() << std::endl;
    }
}

int main() {
    server echo_server;

    try {
        // ��ָ���˿��ϼ���
      //  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 9002);
        echo_server.listen(9002);

        // ������Ϣ������
        echo_server.set_message_handler(bind(&on_message, &echo_server, std::placeholders::_1, std::placeholders::_2));

        // ������������
        echo_server.start_accept();

        // �첽���з�����
        echo_server.run(); // ��Ӧ�������첽�������¼�ѭ��
    }
    catch (const std::exception& e) {
        std::cerr << "����: " << e.what() << std::endl;
    }

    return 0;
}
*/

/*
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include <unordered_set>
#include <set>

using namespace std;

// WebSocket++����
typedef websocketpp::server<websocketpp::config::asio> server;

std::unordered_set<websocketpp::connection_hdl> connections;

class WebSocketServer {
public:
    WebSocketServer() {
        // ����WebSocket�������Ļص�����
        server_.set_open_handler(bind(&WebSocketServer::on_open, this, std::placeholders::_1));
        server_.set_close_handler(bind(&WebSocketServer::on_close, this, std::placeholders::_1));
        server_.set_message_handler(bind(&WebSocketServer::on_message, this, std::placeholders::_1, std::placeholders::_2));
    }

    // ����WebSocket������
    void run(uint16_t port) {
        try {
            // ����������
            server_.listen(port);
            server_.start_accept();
            server_.run();
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

private:
    // �����µ����ӽ���ʱ����
    void on_open(websocketpp::connection_hdl hdl) {
        cout << "Client connected!" << endl;

        // �������Ӽ������Ӽ���
        connections_.insert(hdl);

        // ����������ﵽ��������ʼ��Ϣ����
        if (connections_.size() == 2) {
            broadcast("Two clients connected. Start exchanging messages.");
        }
    }

    // �����ӹر�ʱ����
    void on_close(websocketpp::connection_hdl hdl) {
        cout << "Client disconnected!" << endl;

        // �����Ӽ������Ƴ��رյ�����
        connections_.erase(hdl);
    }

    // �����յ���Ϣʱ����
    void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {
        // �����յ�����Ϣ�㲥����һ������
        for (auto it = connections_.begin(); it != connections_.end(); ++it) {
            if (it->lock() != hdl.lock()) {
                try {
                    server_.send(it->lock(), msg->get_payload(), websocketpp::frame::opcode::text);
                }
                catch (const exception& e) {
                    cout << "Error sending message: " << e.what() << endl;
                }
                break;  // ֻ�㲥��һ������
            }
        }
    }

    // �㲥��Ϣ����������
    void broadcast(const string& message) {
        for (auto it = connections_.begin(); it != connections_.end(); ++it) {
            try {
                server_.send(*it, message, websocketpp::frame::opcode::text);
            }
            catch (const exception& e) {
                cout << "Error sending message: " << e.what() << endl;
            }
        }
    }

    server server_;
    set<websocketpp::connection_hdl, owner_less<websocketpp::connection_hdl>> connections_;
};

int main() {
    WebSocketServer ws_server;
    ws_server.run(9002); // ѡ��һ�����ʵĶ˿�

    return 0;
}
*/




// const rapidjson::Value& name = document["heroType"];
       // std::cout << "�յ���Ϣ��" << std::endl;
       // std::cout << "������" << name.GetString() << std::endl;

       // 
       // // ����JSONֵ
       // const rapidjson::Value& name = document["name"];
       // const rapidjson::Value& age = document["age"];
       //// const rapidjson::Value& city = document["city"];

       // // ����ֵ���ڴ�ʾ���У�ֻ�Ǵ�ӡ���ǣ�
       // std::cout << "�յ���Ϣ��" << std::endl;
       // std::cout << "������" << name.GetString() << std::endl;
       // std::cout << "���䣺" << age.GetInt() << std::endl;
       // //std::cout << "���У�" << city.GetString() << std::endl;