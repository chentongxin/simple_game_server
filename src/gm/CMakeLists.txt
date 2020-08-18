cmake_minimum_required (VERSION 2.8.1)

PROJECT("gm")

FILE(GLOB gm_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 将源代码添加到此项目的可执行文件。
ADD_EXECUTABLE (gm ${gm_src} )

TARGET_LINK_LIBRARIES(${PROJECT_NAME}  "/usr/local/boost_1_74_0/lib64/")
INCLUDE_DIRECTORIES(
	"/usr/local/boost_1_74_0/include"
)