#include <db.h>
#include <string>
#include <muduo/base/Logging.h>

/* 数据层 对数据库的操作 */

// 数据库配置信息
static string server = "127.0.0.1";
static string user = "root";
static string password = "123456";
static string dbname = "chat";

// 初始化数据库连接
MySQL::MySQL() {
    _conn = mysql_init(nullptr);
}

// 释放数据库连接资源
MySQL::~MySQL() {
    if (_conn != nullptr)
        mysql_close(_conn);
}

// 连接数据库
bool MySQL::connect() {
    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(), password.c_str(), dbname.c_str(), 3306, nullptr,
                                  0);
    if (p != nullptr) {
        // C 和 C++ 默认的是 ASCII，不设置 gbk 会乱码
        mysql_query(_conn, "set names gbk");
        LOG_INFO << "connect mysql success!";
    } else {
        LOG_INFO << "connect mysql fail";
    };
    return p;
}

// 更新操作
bool MySQL::update(string sql) {
    if (mysql_query(_conn, sql.c_str())) { // 函数返回值为 0，表示查询成功
        LOG_INFO << "mysql 更新失败: " << mysql_error(_conn);

        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "更新失败!";
        return false;
    }
    return true;
}

// 查询操作
MYSQL_RES *MySQL::query(string sql) {
    if (mysql_query(_conn, sql.c_str())) {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}

MYSQL * MySQL::getConnection() {
    return  _conn;
}
