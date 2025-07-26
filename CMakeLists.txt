cmake_minimum_required(VERSION 3.31)
project(KrustyKrab)

set(CMAKE_CXX_STANDARD 17)


# Worker source code
set(WORKER_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/Employees
)
file(GLOB WORKER_SOURCE_CODE
        ${CMAKE_CURRENT_SOURCE_DIR}/Employees/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Employees/*.hpp
)

# Krusty krab source code
set(KRUSTY_KRAB_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/KrustyKrab
)
file(GLOB KRUSTY_KRAB_SOURCE_CODE
    ${CMAKE_CURRENT_SOURCE_DIR}/KrustyKrab/*.cpp
)

# Utils source code
set(UTILS_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils
)
file(GLOB UTILS_SOURCE_CODE
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils/*.cpp
)

add_executable(KrustyKrab
    main.cpp
    ${WORKER_SOURCE_CODE}
    ${KRUSTY_KRAB_SOURCE_CODE}
    ${UTILS_SOURCE_CODE}
)

target_include_directories(KrustyKrab PRIVATE
    ${WORKER_INCLUDE_DIRS}
    ${KRUSTY_KRAB_INCLUDE_DIRS}
    ${UTILS_INCLUDE_DIRS}
)

