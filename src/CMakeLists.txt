cmake_minimum_required(VERSION 3.24)
project(qword)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "D:/Programs/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/cmake")
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS AxContainer REQUIRED)

file(GLOB SRC_FILES
        ${PROJECT_SOURCE_DIR}/*.h
        ${PROJECT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::AxContainer)
target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE QWORD_LIB)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    DEBUG_POSTFIX "d"
)