# helper to add an example
function( add_example EXAMPLE_NAME EXAMPLE_FILE )
    add_executable( ${EXAMPLE_NAME} ${EXAMPLE_FILE} )
    target_link_libraries( ${EXAMPLE_NAME} ${LIB_NAME} )
endfunction()

# add all examples
add_example( basic_example ${CMAKE_CURRENT_SOURCE_DIR}/basic_example.cpp )
add_example( point ${CMAKE_CURRENT_SOURCE_DIR}/point.cpp )
add_example( line ${CMAKE_CURRENT_SOURCE_DIR}/line.cpp )
add_example( line2 ${CMAKE_CURRENT_SOURCE_DIR}/line2.cpp )
add_example( rect ${CMAKE_CURRENT_SOURCE_DIR}/rect.cpp )
add_example( rect2 ${CMAKE_CURRENT_SOURCE_DIR}/rect2.cpp )
add_example( rect_move ${CMAKE_CURRENT_SOURCE_DIR}/rect_move.cpp )
add_example( outrect ${CMAKE_CURRENT_SOURCE_DIR}/outrect.cpp )
add_example( triangle ${CMAKE_CURRENT_SOURCE_DIR}/triangle.cpp )
add_example( triangle2 ${CMAKE_CURRENT_SOURCE_DIR}/triangle2.cpp )
add_example( outtriangle ${CMAKE_CURRENT_SOURCE_DIR}/outtriangle.cpp )
add_example( circle ${CMAKE_CURRENT_SOURCE_DIR}/circle.cpp )
add_example( circle2 ${CMAKE_CURRENT_SOURCE_DIR}/circle2.cpp )
add_example( circle3 ${CMAKE_CURRENT_SOURCE_DIR}/circle3.cpp )
add_example( outcircle ${CMAKE_CURRENT_SOURCE_DIR}/outcircle.cpp )
add_example( outcircle2 ${CMAKE_CURRENT_SOURCE_DIR}/outcircle2.cpp )
add_example( keyboard_test ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_test.cpp )
add_example( keyboard_test2 ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_test2.cpp )
add_example( mixed ${CMAKE_CURRENT_SOURCE_DIR}/mixed.cpp )
add_example( change_window_size ${CMAKE_CURRENT_SOURCE_DIR}/change_window_size.cpp )
add_example( background ${CMAKE_CURRENT_SOURCE_DIR}/background.cpp )
add_example( hide ${CMAKE_CURRENT_SOURCE_DIR}/hide.cpp )
add_example( image ${CMAKE_CURRENT_SOURCE_DIR}/image.cpp )
add_example( image_norect ${CMAKE_CURRENT_SOURCE_DIR}/image_norect.cpp )
add_example( image_switch ${CMAKE_CURRENT_SOURCE_DIR}/image_switch.cpp )
add_example( image_rect_hide ${CMAKE_CURRENT_SOURCE_DIR}/image_rect_hide.cpp )

