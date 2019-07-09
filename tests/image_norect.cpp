#include "graphics.hpp"

int main(int, char*[])
{
    set_background(WHITE);

    Image img{"../../media/Triangle.png"};

    return draw();
}
