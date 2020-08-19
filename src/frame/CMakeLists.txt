cmake_minimum_required (VERSION 2.8.1)

PROJECT("frame")

FILE(GLOB frame_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

SET(BOOST_ROOT /usr/local/boost_1_74_0/)
find_package(Boost COMPONENTS
			atomic
			chrono
			date_time
			filesystem
			log 
			regex
			system
			thread 
			REQUIRED)

if(Boost_FOUND)
	MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
	
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
	
	# 将源代码添加到此项目的可执行文件。
	ADD_EXECUTABLE (frame ${frame_src} )
    target_link_libraries (frame 
		${Boost_LIBRARIES}
		${CMAKE_THREAD_LIBS_INIT}
		libpthread.so.0
	)
endif()
