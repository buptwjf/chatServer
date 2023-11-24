//
// Created by 86188 on 2023/11/20.
//
#pragma once

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "json.hpp"
#include "public.hpp"
#include "userModel.hpp"

using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

// 处理消息的事件的回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp time)>;


/*  业务层 操作的均为对象，不直接操作底层的数据库  */

// 单例模式设置聊天服务器业务类
// 将 不同的 msgId 设置不同的消息回调
class ChatService {
public:
    // 获取单例对象的接口函数
    static ChatService *instance();
    // 处理登录业务 login
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注册业务 reg
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 获取消息对应的处理器
    MsgHandler getHandler(int msgId);

private:
    ChatService();
    // 存储消息 id 和其对应的业务处理方法
    std::unordered_map<int, MsgHandler> _msgHandlerMap;

    // 存取在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnectionMap;
    // 定义互斥锁，保证 _userConnectionMap 的线程安全
    mutex _connMutex;
    // 数据操作类对象
    UserModel _userModel;
};
