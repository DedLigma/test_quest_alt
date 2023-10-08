cmake_minimum_required(VERSION 3.0)
project(alt_test)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
