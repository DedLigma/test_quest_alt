cmake_minimum_required(VERSION 3.0)
project(alt_test)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_library(packageshandler SHARED lib_packages_handler.cpp)
target_link_libraries(packageshandler PRIVATE CURL::libcurl nlohmann_json::nlohmann_json)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json packageshandler)
