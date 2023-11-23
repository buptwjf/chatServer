//
// Created by 86188 on 2023/11/20.
//

#pragma once

/*
 *  server 和 client 的公共函数
 * */

enum EnMsgType {
    LOGIN_MSG = 1,  // 登录消息
    LOGIN_MSG_ACK,
    REG_MSG, // 注册消息
    REG_MSG_ACK // 注册响应消息
};