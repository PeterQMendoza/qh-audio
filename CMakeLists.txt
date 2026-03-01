cmake_minimum_required(VERSION 4.2)
project(qh_audio VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include src)

file(GLOB SOURCES "src/*.cpp")

add_executable(programa ${SOURCES})

# Dependencias segun plataforma
if(WIN32)
    target_link_libraries(programa PRIVATE user32 gdi32)
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    target_link_libraries(programa PRIVATE ${COCOA_LIBRARY})
elseif(UNIX)
    target_link_libraries(programa PRIVATE x11 m pthread)
endif()
