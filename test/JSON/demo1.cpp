#include <iostream>
#include <json/json.h>

int main() {
    // 输出 jsoncpp 的版本信息
    std::cout << "jsoncpp version: " << JSONCPP_VERSION_STRING << std::endl;
    Json::Value root;

    // 创建一个用于写入 JSON 的 StreamWriterBuilder
    Json::StreamWriterBuilder builder;

    // 使用 builder 创建一个 StreamWriter
    Json::StreamWriter *writer(builder.newStreamWriter());

    // 向 JSON 对象 'root' 中添加键值对
    root["Name"] = "robin";
    root["Age"] = 20;

    // 使用 StreamWriter 将 JSON 对象写入标准输出
    writer->write(root, &std::cout);
    delete writer;
    return EXIT_SUCCESS; // 0
}