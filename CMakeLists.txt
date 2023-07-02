#z最低cmake版本
cmake_minimum_required(VERSION 2.8)
#项目名称
project(HelloSLAM)

#增加一个可执行的二进制
add_executable(helloSLAM main.cpp)

#生成的可执行文件放入 bin文件中
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)