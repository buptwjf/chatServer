cmake_minimum_required(VERSION 3.0)
project(demo1)

# 用于指定构建类型，例如 "Debug" 或 "Release"。
# 如果设置为 "Debug"，则开启调试模式，通常包含调试信息，并且编译器会优化速度而不是代码大小。
# 如果设置为 "Release"，则关闭调试模式，编译器可能会启用更多的优化
# 如果你只关心调试信息，你可以只设置 CMAKE_BUILD_TYPE 为 "Debug"，而不设置 CMAKE_CXX_FLAGS
# CMake 会在 Debug 模式下自动添加 -g 选项。
set(CMAKE_BUILD_TYPE "Debug")

# 控制 C++ 编译器的标志。
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g) 

add_executable(main main.cpp)

# add_subdirectory(lib)
# add_subdirectory(tests)