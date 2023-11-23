//
// Created by 86188 on 2023/11/21.
//
#pragma once

#include <muduo/base/Logging.h>
#include <string>

using namespace std;

// User 表的 ORM 类
// 用来映射字段
class User {
public:
    explicit User(int id = -1, string name = "", string pwd = "", string state = "offline") : id(id), name(name), password(pwd),
                                                                                     state(state) {
    }

    void setId(int id) { this->id = id; }

    void setName(string name) { this->name = name; }

    void setPwd(string pwd) { this->password = pwd; }

    void setState(string state) { this->state = state; }

    int getId() { return id; }

    string getName() { return name; }

    string getPwd() { return password; }

    string getState() { return state; }

private:
    int id;
    string name;
    string password;
    string state;

};