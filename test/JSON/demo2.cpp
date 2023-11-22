//
// Created by 86188 on 2023/11/17.
//

#include <iostream>
#include <vector>
#include <map>
#include "./json/json.hpp" // 直接使用 .hpp 文件

using namespace std;
using json = nlohmann::json;


// json 序列化示例  json.dump() -> string

void func1() {
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, how are you?";
    cout << js << endl;
    /* 内部是无序的 哈希 表
     * {
        "from" : "zhang san",
        "msg" : "hello, how are you?",
        "msg_type" : 2,
        "to" : "li si"
        }
     * */
    const std::string sendBuf = js.dump();
    std::cout << sendBuf << std::endl;
//    string sendBuf = js.dump();
}

void func2() {
    json js;
    js["id"] = {1, 2, 3, 4, 5};
// 添加key-value
    js["name"] = "zhang san";
// 添加对象
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";
// 上面等同于下面这句一次性添加数组对象
//    js["msg"] = {{"zhang san", "hello world"},
//                 {"liu shuo",  "hello china"}};
    cout << js << endl;
    const std::string sendBuf = js.dump();
    std::cout << sendBuf << std::endl;
    cout << js["msg"]["zhang san"] << endl;
    cout << js["msg"] << endl;
    /*
     *  {"id":[1,2,3,4,5],"msg":{"liu shuo":"hello china","zhang san":"hello world"},"name":"zhang san"}
        {"id":[1,2,3,4,5],"msg":{"liu shuo":"hello china","zhang san":"hello world"},"name":"zhang san"}
        "hello world"
        {"liu shuo":"hello china","zhang san":"hello world"}
     * */
}

// json 可以把容器直接序列化
void func3() {
    json js;
// 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;
// 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});
    js["path"] = m;
    cout << js << endl;
    cout << js["path"][1] << endl;
    /*
     *  {"list":[1,2,5],"path":[[1,"黄山"],[2,"华山"],[3,"泰山"]]}
        [2,"华山"]
     * */
}



int main() {
//    func1();
    func2();
    func3();
}