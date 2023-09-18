cmake_minimum_required(VERSION 3.20)
set(BOARD esp32s3_devkitm)

find_package(Zephyr)
project(helloworld)

target_sources(app PRIVATE src/main.c)
