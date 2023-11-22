#pragma once

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include "public.hpp"
using namespace muduo;
using namespace muduo::net;

// 聊天的服务器的主类
class ChatServer {
  public:
    // 初始化 chatserver 对象
    ChatServer(EventLoop *loop, const InetAddress &listenAddr,
               const string &nameArg);
    ~ChatServer();

    // 启动服务
    void start();

  private:
    // 复合 muduo 库的 TcpServer
    TcpServer _server;
    // 委托 事件循环的 指针
    EventLoop *loop;

    // 上报链接的回调函数
    void onConnection(const TcpConnectionPtr &);

    // 上报读写事件的回调函数
    void onMessage(const TcpConnectionPtr &, Buffer *, Timestamp);
};