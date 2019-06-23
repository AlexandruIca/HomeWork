cmake_minimum_required( VERSION 3.5 )
project( HWAPI )

option( HW_BUILD_TESTS "Build the tests that come with the library" ON )

set( LIB_NAME HW_LIB )

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

target_compile_features( ${LIB_NAME} PRIVATE cxx_std_11 )
target_include_directories( ${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/ )
target_link_libraries( ${LIB_NAME} INTERFACE SDL2main SDL2 SDL2_image )

if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "AppleClang" )
    target_compile_options( ${LIB_NAME} PRIVATE -Wall -Werror -Wextra -Wpedantic )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    target_compile_options( ${LIB_NAME} PRIVATE -Wall -Werror -pedantic -pedantic-errors )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    target_compile_options( ${LIB_NAME} PRIVATE -W4 -WX )
endif()

if( ${HW_BUILD_TESTS} )
    add_subdirectory( tests )
endif()

