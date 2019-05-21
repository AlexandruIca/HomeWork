#include "graphics.hpp"

struct rect
{
    int x, y, w, h;
} g_rect = {0, 0, 300, 300};

void update(float const)
{
    if(key(KEY_UP)) {
        g_rect.y -= 10;
    }
    if(key(KEY_DOWN)) {
        g_rect.y += 10;
    }
    if(key(KEY_LEFT)) {
        g_rect.x -= 10;
    }
    if(key(KEY_RIGHT)) {
        g_rect.x += 10;
    }

    rectangle(g_rect.x, g_rect.y, g_rect.w, g_rect.h, CYAN);
}

int main()
{
    g_rect.x = width() / 2 - g_rect.w / 2;
    g_rect.y = height() / 2 - g_rect.h / 2;
    return draw(update);
}
