cmake_minimum_required(VERSION 3.20)
set(BOARD esp32s3_devkitm)

find_package(Zephyr)
project(i2c)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
target_include_directories(app PRIVATE include)
