cmake_minimum_required( VERSION 3.10 )

project( HWAPI )

# Weird MacOS bug with spaces in library path
if( APPLE AND POLICY CMP0004 )
    cmake_policy( SET CMP0004 OLD )
endif()
# Maybe solves the issue with CMAKE_CXX_STANDARD in MacOS
if( APPLE AND POLICY CMP0025 )
    cmake_policy( SET CMP0025 NEW )
endif()

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/" )

find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED )

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

add_library( ${CMAKE_PROJECT_NAME} ${SRC_FILES} )
# Doesn't work for some reason with AppleClang - no c++11
#target_compile_features( ${CMAKE_PROJECT_NAME} PRIVATE cxx_std_11 )
# Maybe this one?
set_target_properties( ${CMAKE_PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    INTERFACE
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
)

if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "AppleClang" )
    target_compile_options(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        -std=c++11 -stdlib=libc++ -Wall -Werror -Wextra -Wpedantic
    )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    target_compile_options(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        -Wall -Werror -pedantic -pedantic-errors
    )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    target_compile_options(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        /W4 /WX /permissive- /analyze
    )
endif()

option( HW_BUILD_TESTS "Build the tests that come with the library" ON )

if( ${HW_BUILD_TESTS} )
    add_subdirectory( tests )
endif()

