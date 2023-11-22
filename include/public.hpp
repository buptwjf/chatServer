//
// Created by 86188 on 2023/11/20.
//

#pragma once

/*
 *  server 和 client 的公共函数
 * */

enum EnMsgType {
    LOGIN_MSG = 1,  // 登录消息
    REG_MSG = 2, // 注册消息
    REG_MSG_ACK = 3 // 注册响应消息
};