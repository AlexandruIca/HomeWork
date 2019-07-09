#include <iostream>

#include "hwapi.hpp"

using namespace dummy_api;

int main(int, char*[])
{
    triangle(hw::vec2{50, 20}, hw::vec2{20, 80}, hw::vec2{70, 80});
    triangle(hw::vec2{50, 120}, hw::vec2{20, 180}, hw::vec2{70, 180},
             hw::color{234, 192, 45});
    triangle(50, 220, 20, 280, 70, 280);
    triangle(50, 320, 20, 380, 70, 380, hw::color{35, 67, 89});

    Triangle a{hw::vec2{220, 20}, hw::vec2{190, 80}, hw::vec2{230, 80}};
    Triangle b{hw::vec2{220, 120}, hw::vec2{190, 180}, hw::vec2{230, 180},
               hw::color{90, 90, 20}};
    Triangle c{220, 220, 190, 280, 230, 280};
    Triangle d{220, 320, 190, 380, 230, 380, hw::color{23, 150, 160}};

    Triangle modifiable{hw::vec2{120, 400}, hw::vec2{90, 460},
                        hw::vec2{150, 460}};

    modifiable.color() = b.color();

    int rincrement{1};
    int gincrement{-1};

    auto f = [&](double) -> void {
        if(modifiable.color().r >= 255)
            rincrement = -1;
        else if(modifiable.color().r <= 0)
            rincrement = 1;

        modifiable.color().r += rincrement;

        if(modifiable.color().g >= 255)
            gincrement = -1;
        else if(modifiable.color().g <= 0)
            gincrement = 1;

        modifiable.color().g += gincrement;
    };

    return draw(f);
}
