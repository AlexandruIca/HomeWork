cmake_minimum_required( VERSION 3.5 ) 
project( HWAPI )

set( CMAKE_CXX_STANDARD 11 )
set( LIB_NAME HW_LIB )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include/ )
include_directories( ${HW_SDL2_INCLUDE_DIR} )
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
    )

add_library( ${LIB_NAME} ${SRC_FILES} )

target_link_libraries( ${LIB_NAME} SDL2main SDL2 )

if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    target_compile_options( ${LIB_NAME} PRIVATE -Werror -Wextra -Wpedantic )
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    target_compile_options( ${LIB_NAME} PRIVATE -Werror -pedantic -pedantic-errors )
endif()

# helper to add an example
function( add_example EXAMPLE_NAME EXAMPLE_FILE )
    add_executable( ${EXAMPLE_NAME} ${EXAMPLE_FILE} ) 
    target_link_libraries( ${EXAMPLE_NAME} HW_LIB )
endfunction()

# add all examples
add_example( basic_example ${CMAKE_CURRENT_SOURCE_DIR}/tests/basic_example.cpp )
add_example( line ${CMAKE_CURRENT_SOURCE_DIR}/tests/line.cpp )
add_example( rect ${CMAKE_CURRENT_SOURCE_DIR}/tests/rect.cpp )
add_example( rect2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/rect2.cpp )
add_example( outrect ${CMAKE_CURRENT_SOURCE_DIR}/tests/outrect.cpp )
add_example( triangle ${CMAKE_CURRENT_SOURCE_DIR}/tests/triangle.cpp )
add_example( outtriangle ${CMAKE_CURRENT_SOURCE_DIR}/tests/outtriangle.cpp )
add_example( circle ${CMAKE_CURRENT_SOURCE_DIR}/tests/circle.cpp )
add_example( circle2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/circle2.cpp )
add_example( outcircle ${CMAKE_CURRENT_SOURCE_DIR}/tests/outcircle.cpp )
add_example( outcircle2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/outcircle2.cpp )
add_example( keyboard_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/keyboard_test.cpp )
add_example( keyboard_test2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/keyboard_test2.cpp )
add_example( mixed ${CMAKE_CURRENT_SOURCE_DIR}/tests/mixed.cpp )
add_example( change_window_size ${CMAKE_CURRENT_SOURCE_DIR}/tests/change_window_size.cpp )
add_example( background ${CMAKE_CURRENT_SOURCE_DIR}/tests/background.cpp )

