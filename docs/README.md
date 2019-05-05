# Primitives
This library allows you to draw a few primitive shapes:
* points
* lines
* triangles
* circles
* rectangles

A very simple program which uses this library would look like this:
```c++
#include "graphics.hpp"

int main()
{
    point(50, 60);
    return draw();
}
```
which draws a point at coordinate (50, 60).

There are 2 ways to draw a primitive. The first one is by calling functions that have the same name as the primitive:
```c++
line(x0, y0, x1, y1);
```
will draw a line starting from (x0, y0) to (x1, y1). For other shapes:
```c++
point(x, y);
``` 
will draw a point at (x, y).
```c++
triangle(x0, y0, x1, y1, x2, y2);
``` 
will draw a triangle at (x0, y0), (x1, y1), (x2, y2).
```c++
rectangle(x, y, w, h);
``` 
will draw a rectangle starting at (x, y) with width = w and height = h.
```c++
circle(x, y, r);
``` 
will draw a circle starting at (x, y) with radius = r.

To draw only the outline of a primitive you can prepend 'outline\_' for every function except line and point:
```c++
outline_rectangle(...);
outline_triangle(...);
outline_circle(...);
```
They take the same arguments which have the same meaning.

# Color
Every function presented can have an optional last parameter which specifies the color of the shape. You can provide the color either by a hw::color object like so:
```c++
line(x0, y0, x1, y1, hw::color{ r, g, b };
```
where r, g and b are the red, green and blue values(between 0 and 255) for the color, or by using one of the (many) predefined colors in header graphics.hpp:
```c++
line(x0, y0, x1, y1, RED); // There is also YELLOW, AMBER, PURPLE, BLUE, GREEN, LIME etc.
                           // Refer to the full reference of the api to see all the colors predefined.
```

# Behaviour
Untill now you can only draw primitives and look at them. They are static and don't change their color or position. The second way a primitive can be drawn is by using objects which have their type named the same name as the primitive. Not to confuse the types with the functions they follow a different naming convetions.
So to draw a triangle you would use:
```c++
Triangle t{...};
``` 
And to draw an outline of a triangle:
```c++
OutlineTriangle t{...};
```
For other shapes:
```c++
Point p{...};
Line l{...};
Rectangle r{...};
OutlineRectangle or{...};
Circle c{...};
OutlineCircle oc{...};
```
The constructors for these objects take the same parameters as their function equivalents. 
Now when the draw function is called you can pass another functions which will be executed once every frame like so:
```c++
#include "graphics.hpp"

int main()
{
    Line l{ 20, 30, 60, 70, GREEN };
    return draw(WITH{
        ++(l.color().r);
        l.color().r %= 255;
        // You can use 'elapsed_time' constant here
    });
}
```
The WITH macro is nothing but a lambda that takes a constant double as a parameter which signifies the elapsed time since the last frame, named 'elapsed_time'.

# Images

Similar to other classes:
```c++
#include "graphics.hpp"

int main()
{
    Image img{ "Path/to/image" };
    return draw();
}
```

This will draw an image in the center of the screen. Of course you can specify more parameters:
```c++
OutlineRectangle rect{ 20, 20, 100, 100, BLACK };
Image img{ "Path", rect }; // The image will follow the rectangle given.
                           // That is if you modify the rectangles position/dimensions
                           // the image will be shown exactly where the rectangle is

Image img2{ "Path", 20, 20, 100, 100 }; // Draw the image at position (20, 20) with
                                       // width = 100 and height = 100
```

# Customization

To hide/show shapes:
```c++
#include "graphics.hpp"

int main()
{
    Image img{ "Path" };

    return draw(WITH {
        if(key(KEY_h)) {
            img.hide();
        }
        if(key(KEY_s)) {
            img.show();
        }
    });
}
```

```
hide
```
and
```
show
```
are available for all shapes. The shapes are:
* Point/Line
* Triangle/OutlineTriangle
* Rect/OutlineRect
* Circle/OutlineCircle
* Images

To change the size of the window that will be drawn to just call set\_width and set\_height before the draw call:
```c++
int main()
{
    // ...
    set_width(900);
    set_height(900);
    // ...

    return draw(...);
}
```
To get the size of the window that will be drawn to call width and height:
```c++
int main()
{
    // ...
    int w = width();
    int h = height();
    // ...

    return draw(...);
}
```

To check whether a key was pressed:
```c++
int main()
{
    // ...

    return draw(WITH{
        bool b = key(KEY_UP);
    });
}
```
All keys are in include/keys.hpp. They are the same as the SDL provided ones and you can use SDLK\_\* instead of KEY\_\*.

To change the background of the window:
```c++
int main()
{
    set_background(GREEN);
    return draw();
}
```

# Reference
For the full API reference please check: https://codedocs.xyz/AlexandruIca/HomeWork/ or open html/index.html with your favourite browser.

