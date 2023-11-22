cmake_minimum_required(VERSION 3.0)
project(chatServer)

# 配置编译选项、
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)

# 库文件搜索路径
# link_directories()



# 要搜索的子目录
add_subdirectory(src)

# #设置需要编译的源文件列表
# set(SRC_LIST muduo_test.cpp)

# # 如果 .cpp 文件数量过多，把指定路径下 . 中的所有 cpp 文件放入变量名 SRC_LIST 里面
# aux_source_directory(. SRC_LIST)

# # 可执行文件 server 需要自己的 cpp 源文件
# add_executable(muduo_test ${SRC_LIST})


# # 表示 server 需要链接的静态库和动态库 
# target_link_libraries(muduo_test muduo_net muduo_base pthread)