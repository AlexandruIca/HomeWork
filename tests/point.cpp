#include "graphics.hpp"

void update(float const t_time)
{
    for(int i = 0; i < 20; ++i) {
        point(i + 200, 400, RED);
    }
}

int main(int, char*[])
{
    for(int i = 0; i < 20; ++i) {
        point(i + 200, 300, GREEN);
    }

    return draw(update);
}
