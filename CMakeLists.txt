#z最低cmake版本
cmake_minimum_required(VERSION 2.8)
#项目名称
project(HelloSLAM)

#根据当前系统配置不同的库 WIN32 代表windows系统 APPLE 代表苹果系统
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows 系统
    message("当前系统是 Windows")
    SET(SDL2_INCLUDE_DIR "D:\\env\\SDL2\\SDL2-2.26.5\\include")
    SET(SDL2_LINK_DIR "D:\\env\\SDL2\\SDL2-2.26.5\\lib\\x64")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Mac 系统
    message("当前系统是 Mac")
    SET(SDL2_INCLUDE_DIR "/opt/homebrew/Cellar/sdl2/2.28.0/include/SDL2")
    SET(SDL2_LINK_DIR "/opt/homebrew/Cellar/sdl2/2.28.0/lib")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux 系统
    message("当前系统是 Linux")
else()
    # 未知系统
    message("未知系统")
endif()


include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LINK_DIR})

#生成的可执行文件放入 bin文件中
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

target_link_libraries(helloSLAM SDL2)
#增加一个可执行的二进制
add_executable(helloSLAM main.cpp)



#移动res文件夹 到 bin/res
file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ${EXECUTABLE_OUTPUT_PATH})

