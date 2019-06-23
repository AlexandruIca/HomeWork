#include "graphics.hpp"

int main()
{
    set_background(WHITE);
    // Put WHITE instead of green not to see the rectangle
    OutlineRectangle rect{width() / 2, height() / 2, 100, 100, GREEN};
    Image img{};

    img.set_color_key(BLACK);
    img.set_path("../../media/Triangle.png");
    img.follow(rect);

    return draw(WITH {
        if(key(KEY_UP)) {
            rect.pos().y -= 10;
        }
        if(key(KEY_DOWN)) {
            rect.pos().y += 10;
        }
    });
}
