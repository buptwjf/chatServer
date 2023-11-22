//
// Created by 86188 on 2023/11/18.
//

#include "./json/json.hpp" // 直接使用 .hpp 文件
#include <iostream>
#include <string>

using namespace std;
using json = nlohmann::json;

// 反序列化  json.parse(string) -> js

string func1() {
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, how are you?";

    const std::string sendBuf = js.dump();
    std::cout << sendBuf << std::endl;
    return sendBuf;
}

string func2() {
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
    return js.dump();
}

// json 可以把容器直接序列化
string func3() {
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
    return js.dump();
}


int main() {
    string recvBuf = func1();
    json jsbuf = json::parse(recvBuf);
    cout << " ************************* " << endl;
    cout << jsbuf["msg_type"] << endl;
    cout << " ************************* " << endl;
    string recvBuf1 = func2();
    json jsbuf1 = json::parse(recvBuf1);
    cout << " ************************* " << endl;
    cout << jsbuf1["msg"] << endl;
    cout << " ************************* " << endl;
    string recvBuf2 = func3();
    json jsbuf2 = json::parse(recvBuf2);
    cout << " ************************* " << endl;
    cout << jsbuf2["path"] << endl;
    map<int, string> m = jsbuf2["path"];
//    vector<map<int, string>> vec = jsbuf2["path"] << endl;
    cout << m[1] << endl;
    cout << " ************************* " << endl;
    return 0;
}
