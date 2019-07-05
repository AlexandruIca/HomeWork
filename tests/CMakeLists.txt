enable_testing()

# helper to add a test
function( build_test TEST_NAME TEST_FILE )
    add_executable( ${TEST_NAME} ${TEST_FILE} )
    target_compile_features( ${TEST_NAME} PRIVATE cxx_std_11 )

    if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang" OR "Clang" )
        target_compile_options( ${TEST_NAME} PRIVATE -stdlib=libc++ )
    endif()

    target_link_libraries( ${TEST_NAME} ${CMAKE_PROJECT_NAME} )
    add_test( ${TEST_NAME} ${TEST_NAME} )
    #add_custom_command(
    #    TARGET ${TEST_NAME}
    #    POST_BUILD
    #    COMMAND ${CMAKE_COMMAND} -E echo "Running ${TEST_NAME}..."
    #    COMMAND ${TEST_NAME}
    #    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    #    VERBATIM
    #)
    set_tests_properties( ${TEST_NAME} PROPERTIES TIMEOUT 2 )
endfunction()

build_test( basic_example ${CMAKE_CURRENT_SOURCE_DIR}/basic_example.cpp )
build_test( point ${CMAKE_CURRENT_SOURCE_DIR}/point.cpp )
build_test( line ${CMAKE_CURRENT_SOURCE_DIR}/line.cpp )
build_test( line2 ${CMAKE_CURRENT_SOURCE_DIR}/line2.cpp )
build_test( rect ${CMAKE_CURRENT_SOURCE_DIR}/rect.cpp )
build_test( rect2 ${CMAKE_CURRENT_SOURCE_DIR}/rect2.cpp )
build_test( rect_move ${CMAKE_CURRENT_SOURCE_DIR}/rect_move.cpp )
build_test( outrect ${CMAKE_CURRENT_SOURCE_DIR}/outrect.cpp )
build_test( triangle ${CMAKE_CURRENT_SOURCE_DIR}/triangle.cpp )
build_test( triangle2 ${CMAKE_CURRENT_SOURCE_DIR}/triangle2.cpp )
build_test( outtriangle ${CMAKE_CURRENT_SOURCE_DIR}/outtriangle.cpp )
build_test( circle ${CMAKE_CURRENT_SOURCE_DIR}/circle.cpp )
build_test( circle2 ${CMAKE_CURRENT_SOURCE_DIR}/circle2.cpp )
build_test( circle3 ${CMAKE_CURRENT_SOURCE_DIR}/circle3.cpp )
build_test( outcircle ${CMAKE_CURRENT_SOURCE_DIR}/outcircle.cpp )
build_test( outcircle2 ${CMAKE_CURRENT_SOURCE_DIR}/outcircle2.cpp )
build_test( keyboard_test ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_test.cpp )
build_test( keyboard_test2 ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_test2.cpp )
build_test( mixed ${CMAKE_CURRENT_SOURCE_DIR}/mixed.cpp )
build_test( change_window_size ${CMAKE_CURRENT_SOURCE_DIR}/change_window_size.cpp )
build_test( background ${CMAKE_CURRENT_SOURCE_DIR}/background.cpp )
build_test( hide ${CMAKE_CURRENT_SOURCE_DIR}/hide.cpp )
build_test( image ${CMAKE_CURRENT_SOURCE_DIR}/image.cpp )
build_test( image_norect ${CMAKE_CURRENT_SOURCE_DIR}/image_norect.cpp )
build_test( image_switch ${CMAKE_CURRENT_SOURCE_DIR}/image_switch.cpp )
build_test( image_rect_hide ${CMAKE_CURRENT_SOURCE_DIR}/image_rect_hide.cpp )
build_test( mouse ${CMAKE_CURRENT_SOURCE_DIR}/mouse.cpp )

