#include "hwapi.hpp"

using namespace dummy_api;

int main()
{
    const auto width = get_global_width();
    const auto height = get_global_height();
    const auto radius = width / 10;

    outline_circle(width / 4, height / 3, radius, hw::color{120, 36, 90});
    outline_circle(2 * width / 4, height / 3, radius, hw::color{20, 136, 84});
    outline_circle(3 * width / 4, height / 3, radius, hw::color{232, 20, 60});

    OutlineCircle a{width / 4, 2 * height / 3, radius, hw::color{45, 89, 102}};
    OutlineCircle b{2 * width / 4, 2 * height / 3, radius,
                    hw::color{23, 96, 77}};
    OutlineCircle modifiable{3 * width / 4, 2 * height / 3, radius};

    modifiable.color() = a.color();

    int rincrement{1};
    int gincrement{-1};

    auto f = [&](double elapsed_time) {
        if(modifiable.color().r >= 255)
            rincrement = -1;
        else if(modifiable.color().r <= 0)
            rincrement = 1;

        modifiable.color().r += rincrement;

        if(modifiable.color().g >= 255)
            gincrement = -1;
        else if(modifiable.color().g <= 0)
            gincrement = -1;

        modifiable.color().g += gincrement;
    };

    return draw(f);
}
