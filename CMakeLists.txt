cmake_minimum_required(VERSION 3.2.2)

project(explorer)

set(EXPLORER_VERSION_MAJOR 0)
set(EXPLORER_VERSION_MINOR 1)
set(EXPLORER_VERSION_PATCH 1)
set(EXPLORER_VERSION_TWEAK 0)
set(EXPLORER_VERSION ${EXPLORER_VERSION_MAJOR}.${EXPLORER_VERSION_MINOR}.${EXPLORER_VERSION_PATCH}.${EXPLORER_VERSION_TWEAK})
set(EXPLORER_VERSION_STRING "v${EXPLORER_VERSION}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(explorer STATIC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)


install(TARGETS explorer
    EXPORT explorer-config
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

target_link_libraries(${PROJECT_NAME} -pthread -std=c++14 -lboost_system -lboost_filesystem)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES main.cpp DESTINATION bin)

include(CPackConfig.cmake)
