//
// Created by 86188 on 2023/11/20.
//
#include "chatService.hpp"
#include "public.hpp"
#include <muduo/base/Logging.h>
#include <string>

using namespace muduo;

// 线程安全的饿汉单例对象
ChatService *ChatService::instance() {
    static ChatService service;
    return &service;
}

// 注册操作以及他的回调函数
ChatService::ChatService() {
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
    _msgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});
}

// 处理登录业务 login
void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time) {
    LOG_INFO << "do login service!!!";
    int id = js["id"].get<int>();
    string pwd = js["password"];

    User user = _userModel.query(id);
    // 查询到该用户 id
    if (user.getId() != -1 && user.getPwd() == pwd) {
        // 该用户已经登陆，
        if (user.getState() == "online") {
            json response;
            response["msgId"] = LOGIN_MSG_ACK;
            response["errno"] = 2;
            response["errmsg"] = "该账号已经登陆，请重新输入新账号";
            conn->send(response.dump());
        } else {
            // 登录成功，更新用户状态信息 state offline=>online
            user.setState("online");
            _userModel.updateState(user);
            json response;
            response["msgId"] = LOGIN_MSG_ACK;
            response["errno"] = 0;
            response["id"] = user.getId();
            response["name"] = user.getName();
            conn->send(response.dump());
        }
    } else {
        // 该用户不存在 登录失败
        json response;
        response["msgId"] = LOGIN_MSG_ACK;
        response["errno"] = 1;
        response["errmsg"] = "用户名或者密码错误";
        conn->send(response.dump());
    }
}

// 处理注册业务 reg
// 注册只需要这两个字段 name password
void ChatService::reg(const TcpConnectionPtr &conn, json &js, Timestamp time) {
    LOG_INFO << "do reg service!!!";
    string name = js["name"];
    string pwd = js["password"];

    User user;
    user.setName(name);
    user.setPwd(pwd);
    bool state = _userModel.insert(user);
    if (state) {
        // 注册成功
        json response;
        response["msgId"] = REG_MSG_ACK;
        response["errno"] = 0;
        response["id"] = user.getId();
        conn->send(response.dump());
    } else {
        // 注册失败
        json response;
        response["msgId"] = REG_MSG_ACK;
        response["errno"] = 1;
        conn->send(response.dump());
    }
}

MsgHandler ChatService::getHandler(int msgId) {
    // 记录错误日志，msgId 没有对应的事件处理回调
    auto it = _msgHandlerMap.find(msgId);
    if (it == _msgHandlerMap.end()) {
        // 返回一个默认的空操作
        return [=](const TcpConnectionPtr &conn, json &js, Timestamp time) {
            LOG_ERROR << "msgId: " << msgId << "can not find handler";
        };
    } else {
        return _msgHandlerMap[msgId];
    }
}
