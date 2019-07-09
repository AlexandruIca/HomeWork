cmake_minimum_required( VERSION 3.10 )

project( HWAPI )

# Weird MacOS bug with spaces in library path
if( APPLE AND POLICY CMP0004 )
    cmake_policy( SET CMP0004 OLD )
endif()

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/" )

include( SetCXXStandard )

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
set_cxx_standard( ${CMAKE_PROJECT_NAME} 11 )
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
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)

set( LIBRARY_COMPILE_OPTIONS )

if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "AppleClang" )
    set( LIBRARY_COMPILE_OPTIONS ${LIBRARY_COMPILE_OPTIONS} -Wall -Werror -Wextra -Wpedantic )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    set( LIBRARY_COMPILE_OPTIONS ${LIBRARY_COMPILE_OPTIONS} -Wall -Werror -pedantic -pedantic-errors )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    set( LIBRARY_COMPILE_OPTIONS ${LIBRARY_COMPILE_OPTIONS} /W4 /WX /permissive- /analyze )
endif()

target_compile_options( ${CMAKE_PROJECT_NAME} PRIVATE ${LIBRARY_COMPILE_OPTIONS} )

option( HW_BUILD_TESTS "Build the tests that come with the library" ON )

if( ${HW_BUILD_TESTS} )
    add_subdirectory( tests )
endif()

option( HW_BUILD_DOCS "Build the documentation that comes with the library" ON )

if( ${HW_BUILD_DOCS} )
    find_package( Doxygen )

    if( DOXYGEN_FOUND )
        add_custom_target( documentation ALL
            COMMAND ${CMAKE_COMMAND} -E echo "Building documentation..."
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM
        )
    else()
        message( "You need doxygen to build the documentation." )
    endif()
endif()

