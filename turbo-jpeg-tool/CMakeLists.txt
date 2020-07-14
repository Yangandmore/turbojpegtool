cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)
set(libs "${CMAKE_SOURCE_DIR}/libs")
set(cpps "${CMAKE_SOURCE_DIR}/src/main/cpp")
include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)

add_library( turbojpeg STATIC IMPORTED )
set_target_properties( turbojpeg PROPERTIES
        IMPORTED_LOCATION "${libs}/${ANDROID_ABI}/libturbojpeg.a" )

add_library(
        turbojpegtool
        SHARED
        ${cpps}/turbojpegtool.cpp)

find_library(
        log-lib
        log)

target_link_libraries(
        turbojpegtool
        turbojpeg
        ${log-lib})