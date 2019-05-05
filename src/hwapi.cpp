#include "hwapi.hpp"
#include "window.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <utility>

#include "SDL2/SDL_image.h"

///
/// @file hwapi.cpp
///

namespace da = dummy_api;

// no c++14
template<typename T, typename... Args>
static std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

namespace {
    hw::window* g_global_window{nullptr};
    int g_global_width{640};
    int g_global_height{480};
    hw::color g_background{0, 0, 0};
} // namespace

namespace dummy_api {
    std::vector<da::Shape*>& get_shapes()
    {
        static std::vector<da::Shape*> shapes;
        return shapes;
    }

    std::vector<std::unique_ptr<da::Shape>>& get_anon_shapes()
    {
        static std::vector<std::unique_ptr<da::Shape>> shapes;
        return shapes;
    }

    hw::window* get_global_window()
    {
        return g_global_window;
    }

    int get_global_width()
    {
        return g_global_width;
    }

    int get_global_height()
    {
        return g_global_height;
    }

    void set_global_width(const int t_width)
    {
        g_global_width = t_width;
    }

    void set_global_height(const int t_height)
    {
        g_global_height = t_height;
    }

    void set_background_color(hw::color const& t_color) noexcept
    {
        g_background = t_color;
    }

    void draw_shapes()
    {
        for(auto& shape : get_shapes()) {
            shape->draw_shape();
        }
    }

    int draw(std::function<void(double)> t_call)
    {
        hw::window wnd{g_global_width, g_global_height, "HWindow"};

        g_global_window = &wnd;
        wnd.set_bgcolor(g_background);

        double avg_fps{0.0};

        auto start = std::chrono::steady_clock::now();

        while(!wnd.closed() && !wnd.was_key_pressed(SDLK_ESCAPE)) {
            auto end = std::chrono::steady_clock::now();
            double elapsed_time =
                std::chrono::duration<double>(end - start).count();
            avg_fps += (elapsed_time <= 0.0000001)
                           ? 999.0
                           : std::chrono::seconds(1).count() / elapsed_time;
            avg_fps /= 2;
            start = end;

            wnd.clear();

            t_call(elapsed_time);

            draw_shapes();

            wnd.update();
        }

        std::cout << "FPS: " << avg_fps << '\n';

        return 1;
    }

    Shape::Shape()
    {
        get_shapes().push_back(this);
    }

    void Shape::draw_shape() noexcept
    {
        if(m_hidden) {
            return;
        }

        this->draw();
    }

    void Shape::hide() noexcept
    {
        m_hidden = true;
    }

    void Shape::show() noexcept
    {
        m_hidden = false;
    }

    void point(const hw::vec2& t_pos, const hw::color& t_color)
    {
        get_anon_shapes().push_back(make_unique<da::Point>(t_pos, t_color));
    }

    void point(const int t_x, const int t_y, const hw::color& t_color)
    {
        point(hw::vec2{t_x, t_y}, t_color);
    }

    Point::Point(const hw::vec2& t_pos, const hw::color& t_color)
        : m_value(t_pos)
        , m_color(t_color)
    {
    }

    Point::Point(const int t_x, const int t_y, const hw::color& t_color)
        : m_value(hw::vec2{t_x, t_y})
        , m_color(t_color)
    {
    }

    Point::Point(hw::vec2&& t_pos, hw::color&& t_color)
        : m_value(std::move(t_pos))
        , m_color(std::move(t_color))
    {
    }

    void Point::draw()
    {
        SDL_SetRenderDrawColor(get_global_window()->get_renderer(), m_color.r,
                               m_color.g, m_color.b, m_color.a);
        SDL_RenderDrawPoint(get_global_window()->get_renderer(), m_value.x,
                            m_value.y);
    }

    void line(const hw::vec2& t_a, const hw::vec2& t_b,
              const hw::color& t_color)
    {
        get_anon_shapes().push_back(make_unique<Line>(t_a, t_b, t_color));
    }
    void line(const int t_x1, const int t_y1, const int t_x2, const int t_y2,
              const hw::color& t_color)
    {
        line(hw::vec2{t_x1, t_y1}, hw::vec2{t_x2, t_y2}, t_color);
    }

    Line::Line(const int t_x1, const int t_y1, const int t_x2, const int t_y2,
               const hw::color& t_color)
        : m_start(hw::vec2{t_x1, t_y1})
        , m_end(hw::vec2{t_x2, t_y2})
        , m_color(t_color)
    {
    }

    Line::Line(const hw::vec2& t_a, const hw::vec2& t_b,
               const hw::color& t_color)
        : m_start(t_a)
        , m_end(t_b)
        , m_color(t_color)
    {
    }

    Line::Line(hw::vec2&& t_a, hw::vec2&& t_b, hw::color&& t_color)
        : m_start(std::move(t_a))
        , m_end(std::move(t_b))
        , m_color(std::move(t_color))
    {
    }

    void Line::draw()
    {
        SDL_SetRenderDrawColor(get_global_window()->get_renderer(), m_color.r,
                               m_color.g, m_color.b, m_color.a);
        SDL_RenderDrawLine(get_global_window()->get_renderer(), m_start.x,
                           m_start.y, m_end.x, m_end.y);
    }

    void triangle(const hw::vec2& t_pos1, const hw::vec2& t_pos2,
                  const hw::vec2& t_pos3, const hw::color& t_color)
    {
        get_anon_shapes().push_back(
            make_unique<Triangle>(t_pos1, t_pos2, t_pos3, t_color));
    }

    void triangle(const int t_x1, const int t_y1, const int t_x2,
                  const int t_y2, const int t_x3, const int t_y3,
                  const hw::color& t_color)
    {
        get_anon_shapes().push_back(
            make_unique<Triangle>(hw::vec2{t_x1, t_y1}, hw::vec2{t_x2, t_y2},
                                  hw::vec2{t_x3, t_y3}, t_color));
    }

    Triangle::Triangle(const int t_x1, const int t_y1, const int t_x2,
                       const int t_y2, const int t_x3, const int t_y3,
                       const hw::color& t_color)
        : m_first{t_x1, t_y1}
        , m_second{t_x2, t_y2}
        , m_third{t_x3, t_y3}
        , m_color{t_color}
    {
    }

    Triangle::Triangle(const hw::vec2& t_pos1, const hw::vec2& t_pos2,
                       const hw::vec2& t_pos3, const hw::color& t_color)
        : m_first{t_pos1}
        , m_second{t_pos2}
        , m_third{t_pos3}
        , m_color{t_color}
    {
    }

    Triangle::Triangle(hw::vec2&& t_pos1, hw::vec2&& t_pos2, hw::vec2&& t_pos3,
                       hw::color&& t_color)
        : m_first{std::move(t_pos1)}
        , m_second{std::move(t_pos2)}
        , m_third{std::move(t_pos3)}
        , m_color{std::move(t_color)}
    {
    }

    // stolen from javidx9:
    // https://github.com/OneLoneCoder/videos/blob/master/olcConsoleGameEngine.h
    void Triangle::draw()
    {
        SDL_SetRenderDrawColor(get_global_window()->get_renderer(), m_color.r,
                               m_color.g, m_color.b, m_color.a);
        auto SWAP = [](int& x, int& y) {
            int t = x;
            x = y;
            y = t;
        };
        auto drawline = [&](int sx, int ex, int ny) {
            SDL_RenderDrawLine(get_global_window()->get_renderer(), sx, ny, ex,
                               ny);
        };

        auto x1 = m_first.x;
        auto y1 = m_first.y;

        auto x2 = m_second.x;
        auto y2 = m_second.y;

        auto x3 = m_third.x;
        auto y3 = m_third.y;

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

    void outline_triangle(const hw::vec2& t_pos1, const hw::vec2& t_pos2,
                          const hw::vec2& t_pos3, const hw::color& t_color)
    {
        get_anon_shapes().push_back(
            make_unique<OutlineTriangle>(t_pos1, t_pos2, t_pos3, t_color));
    }
    void outline_triangle(const int t_x1, const int t_y1, const int t_x2,
                          const int t_y2, const int t_x3, const int t_y3,
                          const hw::color& t_color)
    {
        outline_triangle(hw::vec2{t_x1, t_y1}, hw::vec2{t_x2, t_y2},
                         hw::vec2{t_x3, t_y3}, t_color);
    }

    OutlineTriangle::OutlineTriangle(const int t_x1, const int t_y1,
                                     const int t_x2, const int t_y2,
                                     const int t_x3, const int t_y3,
                                     const hw::color& t_color)
        : m_first(hw::vec2{t_x1, t_y1})
        , m_second(hw::vec2{t_x2, t_y2})
        , m_third(hw::vec2{t_x3, t_y3})
        , m_color(t_color)
    {
    }

    OutlineTriangle::OutlineTriangle(const hw::vec2& t_pos1,
                                     const hw::vec2& t_pos2,
                                     const hw::vec2& t_pos3,
                                     const hw::color& t_color)
        : m_first(t_pos1)
        , m_second(t_pos2)
        , m_third(t_pos3)
        , m_color(t_color)
    {
    }

    OutlineTriangle::OutlineTriangle(hw::vec2&& t_pos1, hw::vec2&& t_pos2,
                                     hw::vec2&& t_pos3, hw::color&& t_color)
        : m_first(std::move(t_pos1))
        , m_second(std::move(t_pos2))
        , m_third(std::move(t_pos3))
        , m_color(std::move(t_color))
    {
    }

    void OutlineTriangle::draw()
    {
        SDL_SetRenderDrawColor(get_global_window()->get_renderer(), m_color.r,
                               m_color.g, m_color.b, m_color.a);
        SDL_RenderDrawLine(get_global_window()->get_renderer(), m_first.x,
                           m_first.y, m_second.x, m_second.y);
        SDL_RenderDrawLine(get_global_window()->get_renderer(), m_second.x,
                           m_second.y, m_third.x, m_third.y);
        SDL_RenderDrawLine(get_global_window()->get_renderer(), m_third.x,
                           m_third.y, m_first.x, m_first.y);
    }

    void rectangle(const hw::vec2& t_pos, const int t_width, const int t_height,
                   const hw::color& t_color)
    {
        get_anon_shapes().push_back(
            make_unique<Rectangle>(t_pos, t_width, t_height, t_color));
    }

    void rectangle(const int t_x, const int t_y, const int t_width,
                   const int t_height, const hw::color& t_color)
    {
        rectangle(hw::vec2{t_x, t_y}, t_width, t_height, t_color);
    }

    Rectangle::Rectangle(const int t_x, const int t_y, const int t_width,
                         const int t_height, const hw::color& t_color)
        : m_pos(hw::vec2{t_x, t_y})
        , m_dimensions(hw::vec2{t_width, t_height})
        , m_color(t_color)
    {
    }

    Rectangle::Rectangle(const hw::vec2& t_pos, const int t_width,
                         const int t_height, const hw::color& t_color)
        : m_pos(t_pos)
        , m_dimensions(hw::vec2{t_width, t_height})
        , m_color(t_color)
    {
    }

    Rectangle::Rectangle(hw::vec2&& t_pos, const int t_width,
                         const int t_height, hw::color&& t_color)
        : m_pos(std::move(t_pos))
        , m_dimensions(hw::vec2{t_width, t_height})
        , m_color(std::move(t_color))
    {
    }

    void Rectangle::draw()
    {
        SDL_SetRenderDrawColor(get_global_window()->get_renderer(), m_color.r,
                               m_color.g, m_color.b, m_color.a);

        SDL_Rect tmp_rect;

        tmp_rect.x = m_pos.x;
        tmp_rect.y = m_pos.y;
        tmp_rect.w = m_dimensions.x;
        tmp_rect.h = m_dimensions.y;

        SDL_RenderFillRect(get_global_window()->get_renderer(), &tmp_rect);
    }

    void outline_rectangle(const hw::vec2& t_pos, const int t_width,
                           const int t_height, const hw::color& t_color)
    {
        get_anon_shapes().push_back(
            make_unique<OutlineRectangle>(t_pos, t_width, t_height, t_color));
    }
    void outline_rectangle(const int t_x, const int t_y, const int t_width,
                           const int t_height, const hw::color& t_color)
    {
        outline_rectangle(hw::vec2{t_x, t_y}, t_width, t_height, t_color);
    }

    OutlineRectangle::OutlineRectangle(const int t_x, const int t_y,
                                       const int t_width, const int t_height,
                                       const hw::color& t_color)
        : m_pos(hw::vec2{t_x, t_y})
        , m_dimensions(hw::vec2{t_width, t_height})
        , m_color(t_color)
    {
    }

    OutlineRectangle::OutlineRectangle(const hw::vec2& t_start,
                                       const int t_width, const int t_height,
                                       const hw::color& t_color)
        : m_pos(t_start)
        , m_dimensions(hw::vec2{t_width, t_height})
        , m_color(t_color)
    {
    }

    OutlineRectangle::OutlineRectangle(hw::vec2&& t_start, const int t_width,
                                       const int t_height, hw::color&& t_color)
        : m_pos(std::move(t_start))
        , m_dimensions(hw::vec2{t_width, t_height})
        , m_color(std::move(t_color))
    {
    }

    void OutlineRectangle::draw()
    {
        SDL_SetRenderDrawColor(get_global_window()->get_renderer(), m_color.r,
                               m_color.g, m_color.b, m_color.a);

        SDL_Rect tmp_rect;

        tmp_rect.x = m_pos.x;
        tmp_rect.y = m_pos.y;
        tmp_rect.w = m_dimensions.x;
        tmp_rect.h = m_dimensions.y;

        SDL_RenderDrawRect(get_global_window()->get_renderer(), &tmp_rect);
    }

    void circle(const hw::vec2& t_pos, const int t_radius,
                const hw::color& t_color)
    {
        get_anon_shapes().push_back(
            make_unique<Circle>(t_pos, t_radius, t_color));
    }

    void circle(const int t_x, const int t_y, const int t_radius,
                const hw::color& t_color)
    {
        circle(hw::vec2{t_x, t_y}, t_radius, t_color);
    }

    Circle::Circle(const int t_x, const int t_y, const int t_radius,
                   const hw::color& t_color)
        : m_pos{t_x, t_y}
        , m_radius{t_radius}
        , m_color{t_color}
    {
    }

    Circle::Circle(const hw::vec2& t_pos, const int t_radius,
                   const hw::color& t_color)
        : m_pos{t_pos}
        , m_radius{t_radius}
        , m_color{t_color}
    {
    }

    Circle::Circle(hw::vec2&& t_pos, const int t_radius, hw::color&& t_color)
        : m_pos{std::move(t_pos)}
        , m_radius{t_radius}
        , m_color{std::move(t_color)}
    {
    }

    // Taken from javidx9, taken from wikipedia
    void Circle::draw()
    {
        auto xc = m_pos.x;
        auto yc = m_pos.y;
        auto r = m_radius;

        int x = 0;
        int y = r;
        int p = 3 - 2 * r;
        if(!r)
            return;

        SDL_SetRenderDrawColor(get_global_window()->get_renderer(), m_color.r,
                               m_color.g, m_color.b, m_color.a);
        auto drawline = [&](int sx, int ex, int ny) {
            SDL_RenderDrawLine(get_global_window()->get_renderer(), sx, ny, ex,
                               ny);
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

    void outline_circle(const hw::vec2& t_pos, const int t_radius,
                        const hw::color& t_color)
    {
        get_anon_shapes().push_back(
            make_unique<OutlineCircle>(t_pos, t_radius, t_color));
    }

    void outline_circle(const int t_x, const int t_y, const int t_radius,
                        const hw::color& t_color)
    {
        outline_circle(hw::vec2{t_x, t_y}, t_radius, t_color);
    }

    OutlineCircle::OutlineCircle(const int t_x, const int t_y,
                                 const int t_radius, const hw::color& t_color)
        : m_pos{t_x, t_y}
        , m_radius{t_radius}
        , m_color{t_color}
    {
    }

    OutlineCircle::OutlineCircle(const hw::vec2& t_pos, const int t_radius,
                                 const hw::color& t_color)
        : m_pos{t_pos}
        , m_radius{t_radius}
        , m_color{t_color}
    {
    }

    OutlineCircle::OutlineCircle(hw::vec2&& t_pos, const int t_radius,
                                 hw::color&& t_color)
        : m_pos{std::move(t_pos)}
        , m_radius{t_radius}
        , m_color{std::move(t_color)}
    {
    }

    // guess who wrote this?
    void OutlineCircle::draw()
    {
        SDL_SetRenderDrawColor(get_global_window()->get_renderer(), m_color.r,
                               m_color.g, m_color.b, m_color.a);

        auto Draw = [&](const int t_x, const int t_y) {
            SDL_RenderDrawPoint(get_global_window()->get_renderer(), t_x, t_y);
        };

        auto r = m_radius;
        auto xc = m_pos.x;
        auto yc = m_pos.y;

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

    void Image::delete_rect_if_created_here() noexcept
    {
        if(m_created_here) {
            delete m_rect;
        }
    }

    void Image::create_image() noexcept
    {
        if(m_created_image) {
            return;
        }
        SDL_Surface* img = IMG_Load(m_path.c_str());

        SDL_SetColorKey(img, SDL_TRUE,
                        SDL_MapRGB(img->format, m_color_key.r, m_color_key.g,
                                   m_color_key.b));

        m_image = SDL_CreateTextureFromSurface(
            get_global_window()->get_renderer(), img);

        SDL_FreeSurface(img);

        if(m_rect == nullptr) {
            m_created_here = true;
            m_rect = new OutlineRectangle{
                get_global_window()->get_width() / 2 - 50,
                get_global_window()->get_height() / 2 - 50, 100, 100,
                get_global_window()->get_bgcolor()};
        }

        m_created_image = true;
    }

    Image::Image(std::string const t_path)
        : m_rect(nullptr)
        , m_path(t_path)
        , m_created_here(true)
        , m_color_key(0, 0, 0)
        , m_created_image(false)
        , m_image(nullptr)
    {
    }

    Image::Image(std::string const t_path, int const t_x, int const t_y,
                 int const t_width, int const t_height)
        : m_rect(new OutlineRectangle{t_x, t_y, t_width, t_height})
        , m_path(t_path)
        , m_created_here(true)
        , m_color_key(0, 0, 0)
        , m_created_image(false)
        , m_image(nullptr)
    {
    }

    Image::Image(std::string const t_path, hw::vec2 const& t_pos,
                 hw::vec2 const& t_dim)
        : m_rect(new OutlineRectangle{t_pos, t_dim.x, t_dim.y})
        , m_path(t_path)
        , m_created_here(true)
        , m_color_key(0, 0, 0)
        , m_created_image(false)
        , m_image(nullptr)
    {
    }

    Image::Image(std::string const t_path, OutlineRectangle& t_rect)
        : m_rect(&t_rect)
        , m_path(t_path)
        , m_created_here(false)
        , m_color_key(0, 0, 0)
        , m_created_image(false)
        , m_image(nullptr)
    {
    }

    Image::~Image() noexcept
    {
        this->delete_rect_if_created_here();
        SDL_DestroyTexture(m_image);
    }

    void Image::draw()
    {
        this->create_image();

        SDL_Rect dest;
        dest.x = m_rect->pos().x;
        dest.y = m_rect->pos().y;
        dest.w = m_rect->dim().x;
        dest.h = m_rect->dim().y;

        SDL_RenderCopy(get_global_window()->get_renderer(), m_image, NULL,
                       &dest);
    }

    void Image::set_path(std::string const t_path)
    {
        m_path = t_path;
    }

    void Image::set_color_key(hw::color const& t_color) noexcept
    {
        m_color_key = t_color;
    }

    void Image::follow(OutlineRectangle& t_rect)
    {
        this->delete_rect_if_created_here();
        m_rect = &t_rect;
        m_created_here = false;
    }
} // namespace dummy_api
