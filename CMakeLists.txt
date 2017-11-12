cmake_minimum_required(VERSION 3.7)

project(boost_client_server_exmple)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/)

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(client_interface)

