# cmake_minimum_required(VERSION 3.0)
# project(muduo)
# 配置编译选项、
# set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 头文件搜索路径
# include_directories

# 库文件搜索路径
# link_directories

#设置需要编译的源文件列表
set(SRC_LIST muduo_test.cpp)

# 可执行文件 server 需要自己的 cpp 源文件
add_executable(muduo_test ${SRC_LIST})

# 设置可执行文件最终的存储路径 
# PROJECT_SOURCE_DIR 当前项目的根目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/Muduo)

# 表示 server 需要链接的静态库和动态库 
target_link_libraries(muduo_test muduo_net muduo_base pthread)