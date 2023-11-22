#include "chatServer.hpp"
#include "chatService.hpp"
#include "../../thirdparty/json.hpp"
#include <muduo/base/Logging.h>
#include <functional>

using namespace std::placeholders;
using namespace muduo;
using namespace muduo::net;
using namespace nlohmann;

ChatServer::ChatServer(EventLoop *loop, const InetAddress &listenAddr, const string &nameArg) : _server(loop,
                                                                                                        listenAddr,
                                                                                                        nameArg) {
    // 注册连接的回调函数
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    // 注册读写时间的的回调函数
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    // 设置线程数量
    _server.setThreadNum(4);
}

// 启动服务
void ChatServer::start() { _server.start(); }

ChatServer::~ChatServer() {}

// 上报连接事件的回调函数
void ChatServer::onConnection(const TcpConnectionPtr &conn) {
    // 客户端断开连接
    if (!conn->connected()) {
        conn->shutdown();
    }
}

// 上报读写事件的回调函数
void ChatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time) {
    string buf = buffer->retrieveAllAsString();
    // 数据的反序列化
    json js = json::parse(buf);
    if (js.contains("msgId") && js["msgId"].is_number()) {
        // 达到的目的：完全耦合网络模块的代码和业务模块的代码
        // 通过 js["msgId"] 获取 => 业务 handler => conn js time
        int msgId = js["msgId"].get<int>();
        LOG_INFO << "get msgId: " << msgId;
        // 执行回调消息绑定好的事件处理函数，来执行相应的业务处理
        MsgHandler msgHandler = ChatService::instance()->getHandler(msgId);
        LOG_INFO << "get msgHandler";
        msgHandler(conn, js, time);
    }
}