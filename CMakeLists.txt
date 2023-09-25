cmake_minimum_required(VERSION 3.26)
project(SortTZ)

set(CMAKE_CXX_STANDARD 23)
set(INCLUDE_DIR include)
set(SRC_DIR src)

set(SOURCE_FILES
        main.cpp
        ${SRC_DIR}/Employee.cpp
)

include_directories(${INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

#target_link_libraries(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})