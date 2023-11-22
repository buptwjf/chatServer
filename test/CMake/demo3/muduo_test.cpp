#include <functional> // 绑定器
#include <iostream>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

/*
 * 基于 muduo 网络库开发服务程序
 * 1. 组合 TcpServer 对象
 * 2. 创建 EventLoop 事件循环对象的指针
 * 3. 明确 TcpServer 的构造函数需要什么参数，输出 ChatServer 的构造函数
 * 4. 在当前服务器类的构造函数中，注册处理连接的回调函数和处理读写事件的回调函数
 * 5. 设置合适的服务端线程数量，muduo库会自己划分 I/O 线程和 worker 线程
 * */
class ChatServer {

  public:
    // 事件循环，IP地址，服务器的名称
    ChatServer(EventLoop *loop, const InetAddress &listenAddr,
               const string &nameArg)
        : _server(loop, listenAddr, nameArg), _loop(loop) {

        // 给服务器创建注册用户连接的创建和断开的回调
        _server.setConnectionCallback(
            std::bind(&ChatServer::onConnection, this, _1));
        // 给_server 注册 onConnection 方法

        // 给服务器注册用户读写事件回调
        _server.setMessageCallback(
            std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        // 设置服务器的线程数量 1个I/O 线程，三个 worker 线程
        _server.setThreadNum(4);
    }
    // 开启事件循环
    void start() { _server.start(); }

  private:
    // 专门处理用户的连接创建和断开  epoll listenfd accept
    void onConnection(const TcpConnectionPtr &conn) {
        if (conn->connected()) {
            cout << conn->peerAddress().toIpPort() << "->"
                 << conn->localAddress().toIpPort() << " state:online" << endl;

        } else {
            cout << conn->peerAddress().toIpPort() << "->"
                 << conn->localAddress().toIpPort() << " state:offline" << endl;
            conn->shutdown();  // close(fd)
            // _loop->quit();
        }
    }

    // 处理读写事件的回调函数
    void onMessage(const TcpConnectionPtr &conn, Buffer *buffer,
                   Timestamp time) {
        string buf = buffer->retrieveAllAsString();
        cout << "recv data:" << buf << "time:" << time.toString() << endl; // 接收数据
        conn->send(buf); // 将接收到的数据返回

    }


    TcpServer _server; // # 1 
    EventLoop *_loop;  // # 2 epoll
};

int main() {
    EventLoop loop; // epoll
    InetAddress addr("127.0.0.1", 6000); // 给定 ip 地址和端口号
    ChatServer server(&loop, addr, "ChatServer"); // 创建用户服务器
    server.start();  // listenfd 通过 epoll_ctl 挂到 epoll 上 
    loop.loop(); // 最后 epoll_wait,以阻塞的方式等待新用户连接，已连接用户的读写事件等
    return 0;
}
