cmake_minimum_required(VERSION 3.7)

include_directories( 
	D:/PRogramming/boost/boost_1_64_0/boost_1_64_0
)

link_directories(
	D:/PRogramming/boost/boost_1_64_0/boost_1_64_0/stage/lib/
)

if(WIN32)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

add_executable(
	client
	client_main.cxx
)

