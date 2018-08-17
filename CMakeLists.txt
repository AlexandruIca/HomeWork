cmake_minimum_required( VERSION 2.8 )

project( HWAPI )

set( CMAKE_CXX_STANDARD 11 )

find_package( SDL2 REQUIRED )

include_directories( ${PROJECT_SOURCE_DIR}/include/ )
include_directories( ${SDL2_INCLUDE_DIR} )

set( SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/color.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/vec2.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vec2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/hwapi.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hwapi.cpp
    )

add_library( HW_LIB ${SRC_FILES} )

target_link_libraries( HW_LIB ${SDL2_LIBRARIES} )

add_executable( basic_example ${CMAKE_CURRENT_SOURCE_DIR}/tests/basic_example.cpp )

target_link_libraries( basic_example HW_LIB )

