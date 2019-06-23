#include "graphics.hpp"

int main()
{
    set_background(YELLOW);

    OutlineRectangle rect{100, 100, 200, 300, CYAN};
    Image img{"../../media/Triangle.png", rect};

    rect.hide();

    return draw(WITH {
        if(key(KEY_UP)) {
            rect.pos().y -= 10;
        }
        if(key(KEY_DOWN)) {
            rect.pos().y += 10;
        }
    });
}
