cmake_minimum_required (VERSION 2.8.1)

PROJECT("gm")

FILE(GLOB gm_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

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
			timer
			REQUIRED)

if(Boost_FOUND)
	MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
	
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
	
	# 将源代码添加到此项目的可执行文件。
	ADD_EXECUTABLE (gm ${gm_src} )
    target_link_libraries (gm 
		${Boost_LIBRARIES}
		${CMAKE_THREAD_LIBS_INIT}
		libpthread.so.0
	)
endif()
