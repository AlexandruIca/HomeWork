#include "hwapi.hpp"

using namespace dummy_api;

int main()
{
    outline_rectangle(hw::vec2{ 20, 20 }, 200, 50);
    outline_rectangle(hw::vec2{ 20, 100 }, 200, 50, hw::color{ 20, 255, 30 });
    outline_rectangle(20, 180, 200, 50);
    outline_rectangle(20, 260, 200, 50, hw::color{ 180, 10, 10, 34 });

    OutlineRectangle a{ hw::vec2{ 20, 340 }, 200, 50 };
    OutlineRectangle b{ hw::vec2{ 20, 420 }, 200, 50, hw::color{ 90, 90, 20 } };
    OutlineRectangle c{ 320, 20, 200, 50 };
    OutlineRectangle d{ 320, 100, 200, 50, hw::color{ 23, 150, 160 } };

    OutlineRectangle modifiable{ hw::vec2{ 320, 180 }, 200, 50 };

    modifiable.color() = b.color();

    int rincrement{ 1 };
    int gincrement{ -1 };

    auto f1 = [&]() -> void 
    { 
        if(modifiable.color().r >= 255) 
            rincrement = -1; 
        else if(modifiable.color().r <= 0)
            rincrement = 1;

        modifiable.color().r += rincrement;
    };

    auto f2 = [&]() -> void
    {
        if(modifiable.color().g >= 255)
            gincrement = -1;
        else if(modifiable.color().g <= 0)
            gincrement = 1;

        modifiable.color().g += gincrement;
    };

    return draw(f1, f2);
}

