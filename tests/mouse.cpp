#include "graphics.hpp"

#include <iostream>

void update(float const t_time)
{
    static float time = 0.f;

    time += t_time;

    if(time >= 0.5f) {
        std::cout << mouse().x << ' ' << mouse().y << '\n';
        time = 0.f;
    }

    if(left_click()) {
        std::cout << "Left click!" << std::endl;
    }
    if(right_click()) {
        std::cout << "Right click!" << std::endl;
    }
}

int main(int, char*[])
{
    std::cout << "Should not crash: " << mouse().x << ' ' << mouse().y
              << std::endl;
    std::cout << "Also should not crash: " << is_left_click() << ' '
              << is_right_click() << std::endl;
    std::cout << "PERFECT!" << std::endl;
    return draw(update);
}
