# 定义一个 SRC_LIST 变量，包含该目录下所有的源文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)


include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)
# 生成可执行文件
add_executable(ChatServer ${SRC_LIST} ${DB_LIST})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 链接的库文件
target_link_libraries(ChatServer muduo_net muduo_base pthread mysqlclient)