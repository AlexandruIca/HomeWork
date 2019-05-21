#include "graphics.hpp"

int main()
{
    Rectangle r{300, 300, 100, 100, PURPLE};

    return draw(WITH {
        if(key(KEY_h)) {
            r.hide();
        }
        else if(key(KEY_s)) {
            r.show();
        }
    });
}
