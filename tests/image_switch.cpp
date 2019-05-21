#include "graphics.hpp"

int main()
{
    OutlineRectangle rect{width() / 2 - 100, height() / 2 - 100, 200, 200,
                          CYAN};

    Image img[] = {Image{"../media/Triangle.png"}, Image{"../media/Line.png"}};

    img[0].follow(rect);
    img[1].follow(rect);

    int current_image = 0;

    return draw(WITH {
        if(key(KEY_n)) {
            img[current_image].hide();
            current_image = (current_image + 1) % 2;
            img[current_image].show();
        }
        if(key(KEY_h)) {
            if(img[current_image].hidden()) {
                img[current_image].show();
            }
            else {
                img[current_image].hide();
            }
        }
    });
}
