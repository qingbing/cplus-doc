# 指定需要 make 的最低版本
cmake_minimum_required(VERSION 3.0.0)


# 添加头文件目录: 相当于 g++ 选项中的 -I 参数的作用，也相当于环境变量中增加路径到 CPLUS_INCLUDE_PATH 变量的作用
include_directories(libs)

# 链接的库文件目录: 相当于g++命令的-L选项的作用，也相当于环境变量中增加LD_LIBRARY_PATH的路径的作用
# target_link_directories("libs")
link_directories(libs)

# 添加需要链接的库文件路径
# link_libraries("/root/../libxxx.so")
# link_libraries("/root/../libxxx.a")

# 设置本项目信息，非必须的
project(app VERSION 0.1.0)

# 搜索编译源文件
aux_source_directory(. SRC_LISTS)
aux_source_directory("test_01" SRC_LISTS)
message("SRC_LISTS = ${SRC_LISTS}")

# 添加子目录(动态编译库)
add_subdirectory(test_02)

# 设置项目编译类型
add_executable(app ${SRC_LISTS})

# 设置要链接的库文件的名称
target_link_libraries(app test_02 stmath symath)

# 设置要链接的库文件的名称
# find_library(SYNC_LIB sum libs)
# set(SYNC_LIB sum test_02)
# message("SYNC_LIB = ${SYNC_LIB}")
# target_link_libraries(app ${SYNC_LIB})

