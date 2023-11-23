//
// Created by 86188 on 2023/11/22.
//
#include "userModel.hpp"
#include "db.h"
#include <muduo/base/Logging.h>

bool UserModel::insert(User &user) {
    // 1 组装 sql 语句
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name, password, state) values('%s', '%s', '%s')", user.getName().c_str(),
            user.getPwd().c_str(), user.getState().c_str());

    // 2 初始化 mysql 对象
    MySQL mysql;
    if (mysql.connect()) {
        LOG_INFO << "mysql connect!!";
        if (mysql.update(sql)) {
            LOG_INFO << "mysql update!!";
            // 获取插入成功的用户数据生成的主键 id
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}

User UserModel::query(int id) {
    // 1 组装 sql 语句
    char sql[1024] = {0};
    sprintf(sql, "select * from user where id = %d", id);
    // 2 初始化 mysql 对象
    MySQL mysql;
    if (mysql.connect()) {
        LOG_INFO << "mysql connect!!";
        MYSQL_RES *res = mysql.query(sql); // 动态分配内存
        if (res != nullptr) {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr) {
                User user;
                user.setId(stoi(row[0]));
                user.setName(row[1]);
                user.setPwd(row[2]);
                user.setState(row[3]);
                mysql_free_result(res); // 释放资源
                return user;
            }
        } else {
            LOG_INFO << "mysql query err!!";
        };
    }
    return User();
}

bool UserModel::updateState(User user) {
    // 1 组装 sql 语句
    char sql[1024] = {0};
    sprintf(sql, "update user set state = '%s' where id = '%d'", user.getState().c_str(), user.getId());
    // 2 初始化 mysql 对象
    MySQL mysql;
    if (mysql.connect()) {
        LOG_INFO << "mysql connect!!";
        if (mysql.update(sql)) {
            LOG_INFO << "mysql update!!";
            return true;
        } else {
            LOG_INFO << "mysql update err!!";
            return false;
        }
    } else {
        LOG_INFO << "mysql not connect!!";
        return false;
    }
}