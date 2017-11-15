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
	server
	server_main.cxx
	server.cxx
	server_connection.h
	server_connection.cxx
	connection.hpp
	sender_interface.h
	${CMAKE_HOME_DIRECTORY}/common/struct_header.h
	session.h
)