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
