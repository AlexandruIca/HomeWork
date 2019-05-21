///
/// @file drawing_api.cpp
///

#include "drawing_api.hpp"

void hw::draw_point(SDL_Renderer* t_renderer, hw::vec2 const& t_pos,
                    hw::color const& t_color)
{
    SDL_SetRenderDrawColor(t_renderer, t_color.r, t_color.g, t_color.b,
                           t_color.a);
    SDL_RenderDrawPoint(t_renderer, t_pos.x, t_pos.y);
}

void hw::draw_line(SDL_Renderer* t_renderer, hw::vec2 const& t_start,
                   hw::vec2 const& t_end, hw::color const& t_color)
{
    SDL_SetRenderDrawColor(t_renderer, t_color.r, t_color.g, t_color.b,
                           t_color.a);
    SDL_RenderDrawLine(t_renderer, t_start.x, t_start.y, t_end.x, t_end.y);
}

void hw::draw_triangle(SDL_Renderer* t_renderer, hw::vec2 const& t_first,
                       hw::vec2 const& t_second, hw::vec2 const& t_third,
                       hw::color const& t_color)
{
    SDL_SetRenderDrawColor(t_renderer, t_color.r, t_color.g, t_color.b,
                           t_color.a);
    auto SWAP = [](int& x, int& y) {
        int t = x;
        x = y;
        y = t;
    };
    auto drawline = [&](int sx, int ex, int ny) {
        // SDL_RenderDrawLine(get_global_window()->get_renderer(), sx, ny, ex,
        // ny);
        hw::draw_line(t_renderer, hw::vec2{sx, ny}, hw::vec2{ex, ny}, t_color);
    };

    auto x1 = t_first.x;
    auto y1 = t_first.y;

    auto x2 = t_second.x;
    auto y2 = t_second.y;

    auto x3 = t_third.x;
    auto y3 = t_third.y;

    int t1x, t2x, y, minx, maxx, t1xp, t2xp;
    bool changed1 = false;
    bool changed2 = false;
    int signx1, signx2, dx1, dy1, dx2, dy2;
    int e1, e2;
    // Sort vertices
    if(y1 > y2) {
        SWAP(y1, y2);
        SWAP(x1, x2);
    }
    if(y1 > y3) {
        SWAP(y1, y3);
        SWAP(x1, x3);
    }
    if(y2 > y3) {
        SWAP(y2, y3);
        SWAP(x2, x3);
    }

    t1x = t2x = x1;
    y = y1; // Starting points
    dx1 = (int)(x2 - x1);
    if(dx1 < 0) {
        dx1 = -dx1;
        signx1 = -1;
    }
    else
        signx1 = 1;
    dy1 = (int)(y2 - y1);

    dx2 = (int)(x3 - x1);
    if(dx2 < 0) {
        dx2 = -dx2;
        signx2 = -1;
    }
    else
        signx2 = 1;
    dy2 = (int)(y3 - y1);

    if(dy1 > dx1) { // swap values
        SWAP(dx1, dy1);
        changed1 = true;
    }
    if(dy2 > dx2) { // swap values
        SWAP(dy2, dx2);
        changed2 = true;
    }

    e2 = (int)(dx2 >> 1);
    // Flat top, just process the second half
    if(y1 == y2)
        goto next;
    e1 = (int)(dx1 >> 1);

    for(int i = 0; i < dx1;) {
        t1xp = 0;
        t2xp = 0;
        if(t1x < t2x) {
            minx = t1x;
            maxx = t2x;
        }
        else {
            minx = t2x;
            maxx = t1x;
        }
        // process first line until y value is about to change
        while(i < dx1) {
            i++;
            e1 += dy1;
            while(e1 >= dx1) {
                e1 -= dx1;
                if(changed1)
                    t1xp = signx1; // t1x += signx1;
                else
                    goto next1;
            }
            if(changed1)
                break;
            else
                t1x += signx1;
        }
        // Move line
    next1:
        // process second line until y value is about to change
        while(true) {
            e2 += dy2;
            while(e2 >= dx2) {
                e2 -= dx2;
                if(changed2)
                    t2xp = signx2; // t2x += signx2;
                else
                    goto next2;
            }
            if(changed2)
                break;
            else
                t2x += signx2;
        }
    next2:
        if(minx > t1x)
            minx = t1x;
        if(minx > t2x)
            minx = t2x;
        if(maxx < t1x)
            maxx = t1x;
        if(maxx < t2x)
            maxx = t2x;
        drawline(minx, maxx, y); // Draw line from min to max points found
                                 // on the y Now increase y
        if(!changed1)
            t1x += signx1;
        t1x += t1xp;
        if(!changed2)
            t2x += signx2;
        t2x += t2xp;
        y += 1;
        if(y == y2)
            break;
    }
next:
    // Second half
    dx1 = (int)(x3 - x2);
    if(dx1 < 0) {
        dx1 = -dx1;
        signx1 = -1;
    }
    else
        signx1 = 1;
    dy1 = (int)(y3 - y2);
    t1x = x2;

    if(dy1 > dx1) { // swap values
        SWAP(dy1, dx1);
        changed1 = true;
    }
    else
        changed1 = false;

    e1 = (int)(dx1 >> 1);

    for(int i = 0; i <= dx1; i++) {
        t1xp = 0;
        t2xp = 0;
        if(t1x < t2x) {
            minx = t1x;
            maxx = t2x;
        }
        else {
            minx = t2x;
            maxx = t1x;
        }
        // process first line until y value is about to change
        while(i < dx1) {
            e1 += dy1;
            while(e1 >= dx1) {
                e1 -= dx1;
                if(changed1) {
                    t1xp = signx1;
                    break;
                } // t1x += signx1;
                else
                    goto next3;
            }
            if(changed1)
                break;
            else
                t1x += signx1;
            if(i < dx1)
                i++;
        }
    next3:
        // process second line until y value is about to change
        while(t2x != x3) {
            e2 += dy2;
            while(e2 >= dx2) {
                e2 -= dx2;
                if(changed2)
                    t2xp = signx2;
                else
                    goto next4;
            }
            if(changed2)
                break;
            else
                t2x += signx2;
        }
    next4:

        if(minx > t1x) {
            minx = t1x;
        }
        if(minx > t2x) {
            minx = t2x;
        }
        if(maxx < t1x) {
            maxx = t1x;
        }
        if(maxx < t2x) {
            maxx = t2x;
        }
        drawline(minx, maxx, y);
        if(!changed1) {
            t1x += signx1;
        }
        t1x += t1xp;
        if(!changed2) {
            t2x += signx2;
        }
        t2x += t2xp;
        y += 1;
        if(y > y3) {
            return;
        }
    }
}

void hw::draw_outline_triangle(SDL_Renderer* t_renderer,
                               hw::vec2 const& t_first,
                               hw::vec2 const& t_second,
                               hw::vec2 const& t_third,
                               hw::color const& t_color)
{
    SDL_SetRenderDrawColor(t_renderer, t_color.r, t_color.g, t_color.b,
                           t_color.a);
    SDL_RenderDrawLine(t_renderer, t_first.x, t_first.y, t_second.x,
                       t_second.y);
    SDL_RenderDrawLine(t_renderer, t_second.x, t_second.y, t_third.x,
                       t_third.y);
    SDL_RenderDrawLine(t_renderer, t_third.x, t_third.y, t_first.x, t_first.y);
}

void hw::draw_rectangle(SDL_Renderer* t_renderer, hw::vec2 const& t_pos,
                        int const t_width, int const t_height,
                        hw::color const& t_color)
{
    SDL_SetRenderDrawColor(t_renderer, t_color.r, t_color.g, t_color.b,
                           t_color.a);

    SDL_Rect tmp_rect;

    tmp_rect.x = t_pos.x;
    tmp_rect.y = t_pos.y;
    tmp_rect.w = t_width;
    tmp_rect.h = t_height;

    SDL_RenderFillRect(t_renderer, &tmp_rect);
}

void hw::draw_outline_rectangle(SDL_Renderer* t_renderer, hw::vec2 const& t_pos,
                                int const t_width, int const t_height,
                                hw::color const& t_color)
{
    SDL_SetRenderDrawColor(t_renderer, t_color.r, t_color.g, t_color.b,
                           t_color.a);

    SDL_Rect tmp_rect;

    tmp_rect.x = t_pos.x;
    tmp_rect.y = t_pos.y;
    tmp_rect.w = t_width;
    tmp_rect.h = t_height;

    SDL_RenderDrawRect(t_renderer, &tmp_rect);
}

void hw::draw_circle(SDL_Renderer* t_renderer, hw::vec2 const& t_pos,
                     int const t_radius, hw::color const& t_color)
{
    auto xc = t_pos.x;
    auto yc = t_pos.y;
    auto r = t_radius;

    int x = 0;
    int y = r;
    int p = 3 - 2 * r;
    if(!r)
        return;

    SDL_SetRenderDrawColor(t_renderer, t_color.r, t_color.g, t_color.b,
                           t_color.a);
    auto drawline = [&](int sx, int ex, int ny) {
        // SDL_RenderDrawLine(get_global_window()->get_renderer(), sx, ny, ex,
        // ny);
        hw::draw_line(t_renderer, hw::vec2{sx, ny}, hw::vec2{ex, ny}, t_color);
    };

    while(y >= x) {
        // Modified to draw scan-lines instead of edges
        drawline(xc - x, xc + x, yc - y);
        drawline(xc - y, xc + y, yc - x);
        drawline(xc - x, xc + x, yc + y);
        drawline(xc - y, xc + y, yc + x);
        if(p < 0)
            p += 4 * x++ + 6;
        else
            p += 4 * (x++ - y--) + 10;
    }
}

void hw::draw_outline_circle(SDL_Renderer* t_renderer, hw::vec2 const& t_pos,
                             int const t_radius, hw::color const& t_color)
{
    SDL_SetRenderDrawColor(t_renderer, t_color.r, t_color.g, t_color.b,
                           t_color.a);

    auto Draw = [&](const int t_x, const int t_y) {
        // SDL_RenderDrawPoint(get_global_window()->get_renderer(), t_x, t_y);
        hw::draw_point(t_renderer, hw::vec2{t_x, t_y}, t_color);
    };

    auto r = t_radius;
    auto xc = t_pos.x;
    auto yc = t_pos.y;

    int x = 0;
    int y = r;
    int p = 3 - 2 * r;
    if(!r)
        return;

    while(y >= x) // only formulate 1/8 of circle
    {
        Draw(xc - x, yc - y); // upper left left
        Draw(xc - y, yc - x); // upper upper left
        Draw(xc + y, yc - x); // upper upper right
        Draw(xc + x, yc - y); // upper right right
        Draw(xc - x, yc + y); // lower left left
        Draw(xc - y, yc + x); // lower lower left
        Draw(xc + y, yc + x); // lower lower right
        Draw(xc + x, yc + y); // lower right right
        if(p < 0)
            p += 4 * x++ + 6;
        else
            p += 4 * (x++ - y--) + 10;
    }
}
