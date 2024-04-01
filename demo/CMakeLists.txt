cmake_minimum_required(VERSION 3.24)
project(demo)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "D:/Programs/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/cmake")
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS AxContainer REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::AxContainer qword)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    DEBUG_POSTFIX "d"
)