#include "graphics.hpp"

#include <iostream>

Rectangle r{};
Rectangle r2{30, 30, 30, 30, AMBER};

void f(double const)
{
    if(tasta(KEY_UP)) {
        r.pos().y -= 10;
    }
    if(tasta(KEY_DOWN)) {
        r.pos().y += 10;
    }
    if(tasta(KEY_LEFT)) {
        r.pos().x -= 10;
    }
    if(key(KEY_RIGHT)) {
        r.pos().x += 10;
    }
}

int main(int, char*[])
{
    set_width(700);
    set_height(700);

    r.pos() = {width() / 2, height() / 2};
    r.dim() = {200, 200};
    r.color() = GREEN;

    point({500, 500}, RED);

    return draw(f);
}
