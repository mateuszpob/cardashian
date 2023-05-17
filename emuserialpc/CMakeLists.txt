cmake_minimum_required(VERSION 3.10) 
project(emuserial) 

set(CMAKE_C_STANDARD 11)

set(SRC 
    EMUSerial.c
    front.c
    serial.c
    socket_server.c
)

# set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -pthread)

add_library(${PROJECT_NAME}-lib ${SRC})
add_executable(${PROJECT_NAME} main.c)

target_compile_options(${PROJECT_NAME} PRIVATE -pthread)
target_compile_options(${PROJECT_NAME}-lib PRIVATE -pthread)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)