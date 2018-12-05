#include <iostream>

#include "graphics.hpp"

int main()
{
    hw::window test_window{ 1280, 720, "Test Window" };

    while(!test_window.closed() && !test_window.was_key_pressed(KEY_ESCAPE)) {
        if(test_window.was_key_pressed(KEY_a)) {
            std::cout << "key 'a' pressed" << std::endl;
        }
        test_window.update();
    } 
}

