cmake_minimum_required(VERSION 3.10)

project(cpp-i18n-lib VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "examples/*.cpp")

add_executable(i18n_example ${SOURCES})

if(MINGW)
    target_link_libraries(i18n_example PRIVATE -static-libgcc -static-libstdc++)
endif()