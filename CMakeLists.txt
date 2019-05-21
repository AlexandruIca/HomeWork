cmake_minimum_required( VERSION 3.5 ) 
project( HWAPI )

set( CMAKE_CXX_STANDARD 11 )
set( LIB_NAME HW_LIB )
set( LIB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/ )

include_directories( ${LIB_INCLUDE_DIRS} )
include_directories( ${HW_SDL2_INCLUDE_DIR} )
include_directories( ${HW_SDL2_IMAGE_INCLUDE_DIR} )
link_directories( ${HW_SDL2_LIBRARY_DIR} )

set( SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/color.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/vec2.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vec2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/hwapi.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hwapi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/drawing_api.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drawing_api.cpp
    )

add_library( ${LIB_NAME} ${SRC_FILES} )

target_link_libraries( ${LIB_NAME} SDL2main SDL2 SDL2_image )

if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    target_compile_options( ${LIB_NAME} PRIVATE -Wall -Werror -Wextra -Wpedantic )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    target_compile_options( ${LIB_NAME} PRIVATE -Wall -Werror -pedantic -pedantic-errors )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    target_compile_options( ${LIB_NAME} PRIVATE -W4 -WX )
endif()

add_subdirectory( tests )

