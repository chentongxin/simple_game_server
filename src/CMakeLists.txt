cmake_minimum_required (VERSION 2.8.1)

PROJECT("simple_server")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

SET(CMAKE_ARCHVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../exe/bin/)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../exe/bin/)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../exe/bin/)

ADD_SUBDIRECTORY("frame")
ADD_SUBDIRECTORY("gm")
ADD_SUBDIRECTORY("share")
ADD_SUBDIRECTORY("http_proxy")
