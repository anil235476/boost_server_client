cmake_minimum_required(VERSION 3.7)

include_directories( 
	../../../boost/
)

link_directories(
	../../../boost/stage/lib/
)

if(WIN32)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

add_executable(
	client
	client_main.cxx
)

