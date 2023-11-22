# project(LearnJSON)
# cmake_minimum_required(VERSION 3.12)


# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

# 查找 JSON 库
# find_package(jsoncpp REQUIRED)
add_executable(demo1 demo1.cpp )
add_executable(demo2 demo2.cpp)
add_executable(demo3 demo3.cpp)
add_executable(test_json test_json.cpp)

# 链接 jsoncpp 库
# target_link_libraries(demo1 /usr/local/lib/libjsoncpp.so)
target_link_libraries(demo1 jsoncpp)
target_link_libraries(demo2 jsoncpp)
target_link_libraries(demo3 jsoncpp)
target_link_libraries(test_json jsoncpp)

# 设置可执行文件最终的存储路径 
# PROJECT_SOURCE_DIR 当前项目的根目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/Json)
