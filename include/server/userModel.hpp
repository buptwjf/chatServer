//
// Created by 86188 on 2023/11/22.
//
#include "user.hpp"

#pragma once

// User 表的数据操作类
class UserModel {
public:
    // User 表的增加方法
    bool insert(User &user);

    // 根据用户号码查询用户信息
    User query(int id);

    // 更新用户表的状态信息
    bool updateState(User user);

};