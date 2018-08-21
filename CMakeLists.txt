cmake_minimum_required( VERSION 3.5 )

project( HWAPI )

set( CMAKE_CXX_STANDARD 11 )

find_package( SDL2 REQUIRED )

if( UNIX )
	set( HW_SDL2_INCLUDE_DIR /usr/local/include )
	set( HW_SDL2_LIBRARY_DIR /usr/local/lib )
	set( HW_SDL2_LIBRARY SDL2main SDL2 )
else()
	set( HW_SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIR} )
	set( HW_SDL2_LIBRARY_DIR )
	set( HW_SDL2_LIBRARY ${SDL2_LIBRARY} )
endif()

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

add_library( HW_LIB ${SRC_FILES} )

target_link_libraries( HW_LIB ${HW_SDL2_LIBRARY} )

add_executable( basic_example ${CMAKE_CURRENT_SOURCE_DIR}/tests/basic_example.cpp )
add_executable( line_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/line.cpp )
add_executable( rect_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/rect.cpp )
add_executable( outrect_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/outrect.cpp )
add_executable( outtriangle_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/outtriangle.cpp )

target_link_libraries( basic_example HW_LIB )
target_link_libraries( line_test HW_LIB )
target_link_libraries( rect_test HW_LIB )
target_link_libraries( outrect_test HW_LIB )
target_link_libraries( outtriangle_test HW_LIB )

