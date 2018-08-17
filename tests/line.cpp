#include "hwapi.hpp"

using namespace dummy_api;

int main()
{
    line(hw::vec2{ 20, 20 }, hw::vec2{ 300, 20 });
    line(hw::vec2{ 20, 21 }, hw::vec2{ 300, 21 }, hw::color{ 20, 255, 30 });
    line(20, 22, 300, 22);
    line(20, 23, 300, 23, hw::color{ 180, 10, 10, 34 });

    Line a{ hw::vec2{ 20, 34 }, hw::vec2{ 300, 34 } };
    Line b{ hw::vec2{ 20, 35 }, hw::vec2{ 300, 35 }, hw::color{ 90, 90, 20 } };
    Line c{ 20, 36, 300, 36 };
    Line d{ 20, 36, 300, 37, hw::color{ 23, 150, 160 } };

    Line modifiable{ hw::vec2{ 20, 80 }, hw::vec2{ 300, 80 } };

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

