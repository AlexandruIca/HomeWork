#include <iostream>

#include "hwapi.hpp"

using namespace dummy_api;
using hw::vec2;
using hw::color;

int main(const int, const char*[])
{
    point(20, 30, color{23, 147, 60});

    line(50, 60, 300, 400, color{50, 60, 230});

    outline_triangle(360, 20, 360, 220, 520, 20, color{245, 45, 30});

    rectangle(140, 300, 200, 100);

    outline_rectangle(380, 100, 200, 100);

    return draw();
}
