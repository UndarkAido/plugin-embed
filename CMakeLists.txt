cmake_minimum_required(VERSION 3.6)
project(discordpp-plugin-embed)

set(CMAKE_CXX_STANDARD 14)

###################

add_library(${PROJECT_NAME} INTERFACE)

INCLUDE_DIRECTORIES(${discordpp_SOURCE_DIR})
