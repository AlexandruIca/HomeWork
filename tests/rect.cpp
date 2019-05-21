#include "hwapi.hpp"

using namespace dummy_api;

int main()
{
    rectangle(hw::vec2{20, 20}, 200, 50);
    rectangle(hw::vec2{20, 100}, 200, 50, hw::color{20, 255, 30});
    rectangle(20, 180, 200, 50);
    rectangle(20, 260, 200, 50, hw::color{180, 10, 10, 34});

    Rectangle a{hw::vec2{20, 340}, 200, 50};
    Rectangle b{hw::vec2{20, 420}, 200, 50, hw::color{90, 90, 20}};
    Rectangle c{320, 20, 200, 50};
    Rectangle d{320, 100, 200, 50, hw::color{23, 150, 160}};

    Rectangle modifiable{hw::vec2{320, 180}, 200, 50};

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
