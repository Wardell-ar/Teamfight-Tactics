
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

// 定义一个自定义消息处理器
class MyHandler : public websocketpp::server<websocketpp::config::asio>::message_handler {
public:
    // 当收到消息时调用此回调函数
    void on_message(websocketpp::connection_hdl hdl, server_::message_ptr msg) {
        // 解析JSON消息
        rapidjson::Document document;
        document.Parse(msg->get_payload().c_str());
        // 检查解析是否成功
        if (!document.IsObject()) {
            std::cerr << "无法解析JSON消息" << std::endl;
            return;
        }

        if (document.HasMember("GameinProgress") && document["GameinProgress"].IsInt()
            && document.HasMember("Gamein") && document["Gamein"].IsInt()) {
            int Type1 = document["GameinProgress"].GetInt();
            int Type2 = document["Gamein"].GetInt();
            if (Type2 == 0) {
                // 创建房间
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
                // 加入房间
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
                //开始对战
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
            else {//对战信息
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

    // 当有新的连接建立时调用
    void on_open(websocketpp::connection_hdl hdl) {
        cout << "Client connected!" << endl;

        // 将新连接加入连接集合
        connections_.insert(hdl);

        // 如果连接数达到两个，则开始消息交换
        if (connections_.size() == 2) {
            broadcast("Two clients connected. Start exchanging messages.");
        }
    }
    // 当连接关闭时调用
    void on_close(websocketpp::connection_hdl hdl) {
        cout << "Client disconnected!" << endl;

        // 从连接集合中移除关闭的连接
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
    
    // WebSocket++服务器实例
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

        // 设置WebSocket++服务器
        handler.server.init_asio();

        
        handler.server.set_access_channels(websocketpp::log::alevel::all);
        handler.server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        handler.server.set_message_handler(websocketpp::lib::bind(
            &MyHandler::on_message, &handler, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2
        ));
        handler.server.set_open_handler(bind(&MyHandler::on_open, &handler, std::placeholders::_1));
        handler.server.set_close_handler(bind(&MyHandler::on_close, &handler, std::placeholders::_1));
        
       
        // 监听在端口9002
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v6(), 9002); 
        handler.server.listen(endpoint);

        // 启动服务器接受循环
        handler.server.start_accept();

        // 启动ASIO io_service运行循环
        handler.server.run();
    }
    catch (websocketpp::exception const& e) {
        std::cerr << "错误：" << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "未知异常" << std::endl;
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
            // 在这里处理收到的JSON数据
            // 你可以添加自己的逻辑来处理数据
            if (document.HasMember("heroType") && document["heroType"].IsInt()) {
                int heroType = document["heroType"].GetInt();
                std::cout << "英雄类型: " << heroType << std::endl;
            }
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);
            std::string message = buffer.GetString();
            // 将消息广播给所有连接的客户端
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
        // 在指定端口上监听
      //  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 9002);
        echo_server.listen(9002);

        // 设置消息处理函数
        echo_server.set_message_handler(bind(&on_message, &echo_server, std::placeholders::_1, std::placeholders::_2));

        // 启动接受连接
        echo_server.start_accept();

        // 异步运行服务器
        echo_server.run(); // 这应该启动异步操作的事件循环
    }
    catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
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

// WebSocket++配置
typedef websocketpp::server<websocketpp::config::asio> server;

std::unordered_set<websocketpp::connection_hdl> connections;

class WebSocketServer {
public:
    WebSocketServer() {
        // 设置WebSocket服务器的回调函数
        server_.set_open_handler(bind(&WebSocketServer::on_open, this, std::placeholders::_1));
        server_.set_close_handler(bind(&WebSocketServer::on_close, this, std::placeholders::_1));
        server_.set_message_handler(bind(&WebSocketServer::on_message, this, std::placeholders::_1, std::placeholders::_2));
    }

    // 启动WebSocket服务器
    void run(uint16_t port) {
        try {
            // 启动服务器
            server_.listen(port);
            server_.start_accept();
            server_.run();
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

private:
    // 当有新的连接建立时调用
    void on_open(websocketpp::connection_hdl hdl) {
        cout << "Client connected!" << endl;

        // 将新连接加入连接集合
        connections_.insert(hdl);

        // 如果连接数达到两个，则开始消息交换
        if (connections_.size() == 2) {
            broadcast("Two clients connected. Start exchanging messages.");
        }
    }

    // 当连接关闭时调用
    void on_close(websocketpp::connection_hdl hdl) {
        cout << "Client disconnected!" << endl;

        // 从连接集合中移除关闭的连接
        connections_.erase(hdl);
    }

    // 当接收到消息时调用
    void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {
        // 将接收到的消息广播给另一个连接
        for (auto it = connections_.begin(); it != connections_.end(); ++it) {
            if (it->lock() != hdl.lock()) {
                try {
                    server_.send(it->lock(), msg->get_payload(), websocketpp::frame::opcode::text);
                }
                catch (const exception& e) {
                    cout << "Error sending message: " << e.what() << endl;
                }
                break;  // 只广播给一个连接
            }
        }
    }

    // 广播消息给所有连接
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
    ws_server.run(9002); // 选择一个合适的端口

    return 0;
}
*/




// const rapidjson::Value& name = document["heroType"];
       // std::cout << "收到消息：" << std::endl;
       // std::cout << "姓名：" << name.GetString() << std::endl;

       // 
       // // 访问JSON值
       // const rapidjson::Value& name = document["name"];
       // const rapidjson::Value& age = document["age"];
       //// const rapidjson::Value& city = document["city"];

       // // 处理值（在此示例中，只是打印它们）
       // std::cout << "收到消息：" << std::endl;
       // std::cout << "姓名：" << name.GetString() << std::endl;
       // std::cout << "年龄：" << age.GetInt() << std::endl;
       // //std::cout << "城市：" << city.GetString() << std::endl;