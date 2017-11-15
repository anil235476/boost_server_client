cmake_minimum_required(VERSION 3.7)

include_directories( 
	../../../boost
	${CMAKE_HOME_DIRECTORY}
)

link_directories(
	../../../boost/stage/lib/
)


if(WIN32)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

add_executable(
	client_interface
	client_interface_main.cxx
	${CMAKE_HOME_DIRECTORY}/common/struct_header.h
	tcp_client.cpp
	tcp_client.h
)

