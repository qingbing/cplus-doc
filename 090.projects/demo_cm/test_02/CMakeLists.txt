# 指定需要 make 的最低版本
cmake_minimum_required(VERSION 3.0.0)

# 设置本项目信息，非必须的
project(test_02 VERSION 0.1.0)

# 搜索编译源文件
aux_source_directory(. LIB_SRC)
message("LIB_SRC = ${LIB_SRC}")

# 设置项目编译类型
add_library("test_02" ${LIB_SRC})
