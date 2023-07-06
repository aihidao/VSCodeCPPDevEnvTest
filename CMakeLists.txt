#z最低cmake版本
cmake_minimum_required(VERSION 2.8)
#项目名称
project(HelloSLAM)

#根据当前系统配置不同的库 WIN32 代表windows系统 APPLE 代表苹果系统
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows 系统
    message("当前系统是 Windows")
    SET(SDL2_INCLUDE_DIR "D:\\env\\SDL2\\SDL2-2.26.5\\include")
    SET(SDL2_LINK_DIR "D:\\env\\SDL2\\SDL2-2.26.5\\lib\\x86")

    SET(SDL2_IMG_INCLUDE_DIR "D:/env/SDL2/SDL2_image-2.6.3/include")
    SET(SDL2_IMG_LINK_DIR "D:\\env\\SDL2\\SDL2_image-2.6.3\\lib\\x86")

    SET(SDL2_TTF_INCLUDE_DIR "D:/env/SDL2/SDL2_ttf-2.20.2/include")
    SET(SDL2_TTF_LINK_DIR "D:\\env\\SDL2\\SDL2_ttf-2.20.2\\lib\\x86")
    #拷贝 lib中的 SDL2.dll 到 bin中
    file(COPY ${SDL2_LINK_DIR}/SDL2.dll DESTINATION ${PROJECT_SOURCE_DIR}/bin)
    file(COPY ${SDL2_IMG_LINK_DIR}/SDL2_image.dll DESTINATION ${PROJECT_SOURCE_DIR}/bin)
    file(COPY ${SDL2_TTF_LINK_DIR}/SDL2_ttf.dll DESTINATION ${PROJECT_SOURCE_DIR}/bin)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Mac 系统
    message("当前系统是 Mac")
    set(CMAKE_CXX_STANDARD 11)
    
    SET(SDL2_INCLUDE_DIR "/opt/homebrew/Cellar/sdl2/2.28.0/include/SDL2")
    SET(SDL2_LINK_DIR "/opt/homebrew/Cellar/sdl2/2.28.0/lib")
    
    SET(SDL2_IMG_INCLUDE_DIR "/opt/homebrew/Cellar/sdl2_image/2.6.3_1/include/SDL2")
    SET(SDL2_IMG_LINK_DIR "/opt/homebrew/Cellar/sdl2_image/2.6.3_1/lib")

    SET(SDL2_TTF_INCLUDE_DIR "/opt/homebrew/Cellar/sdl2_ttf/2.20.2/include/SDL2")
    SET(SDL2_TTF_LINK_DIR "/opt/homebrew/Cellar/sdl2_ttf/2.20.2/lib")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux 系统
    message("当前系统是 Linux")
else()
    # 未知系统
    message("未知系统")
endif()


include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMG_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})

include_directories(include)
include_directories(include/basic)
include_directories(include/entity)
include_directories(include/ui)
include_directories(include/widget)

link_directories(${SDL2_LINK_DIR})
link_directories(${SDL2_IMG_LINK_DIR})
link_directories(${SDL2_TTF_LINK_DIR})

aux_source_directory(src SOURCE_FILES)
aux_source_directory(src/basic SOURCE_FILES)
aux_source_directory(src/entity SOURCE_FILES)
aux_source_directory(src/ui SOURCE_FILES)
aux_source_directory(src/widget SOURCE_FILES)

#生成的可执行文件放入 bin文件中
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#增加一个可执行的二进制
add_executable(helloSLAM main.cpp ${SOURCE_FILES})
target_link_libraries(helloSLAM SDL2main)
target_link_libraries(helloSLAM SDL2)
target_link_libraries(helloSLAM SDL2_image)
target_link_libraries(helloSLAM SDL2_ttf)

#移动res文件夹 到 bin/res
file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${EXECUTABLE_OUTPUT_PATH})


