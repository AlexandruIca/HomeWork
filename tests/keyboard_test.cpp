#include <iostream>

#include "graphics.hpp"

void update(float const)
{
    if(key(KEY_a)) {
        std::cout << "key 'a' pressed" << std::endl;
    }
}

int main(int, char*[])
{
    set_width(1280);
    set_height(720);

    return draw(update);
}
