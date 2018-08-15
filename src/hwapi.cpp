#include "hwapi.hpp"
#include "window.hpp"

#include <utility>
#include <chrono>
#include <iostream>

///
/// @file
///

///
/// @def NO_DEFAULT_WINDOW
/// Define this if you want to have your custom window(s).
///

///
/// @brief
///
namespace da = dummy_api;

// no c++14
template<typename T, typename...Args>
static std::unique_ptr<T> make_unique(Args&&...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#ifndef NO_DEFAULT_WINDOW
static hw::window g_window{ 640, 480, "Hey There" };
static hw::window::event_t g_event;
#endif

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

SDL_Renderer* get_renderer()
{
#ifndef NO_DEFAULT_WINDOW
    return g_window.get_renderer();
#else
    return nullptr;
#endif
}

SDL_Window* get_window()
{
#ifndef NO_DEFAULT_WINDOW
    return g_window.get();
#else
    return nullptr;
#endif
}

namespace dummy_api {
    void draw_shapes()
    {
        for(auto& anon_shape : get_anon_shapes()) {
            anon_shape->draw();
        }
     
        for(auto& shape : get_shapes()) {
            shape->draw();
        }
    }

    int draw(std::function<void()> t_call_first, std::function<void()> t_call_last)
    {
        double avg_fps{ 0.0 };

        while(!g_window.closed(g_event) 
           && !g_window.was_key_pressed(SDL_SCANCODE_ESCAPE)) 
        {
            auto start = std::chrono::steady_clock::now();

            g_window.clear();

            t_call_first();

            draw_shapes();

            t_call_last();

            g_window.update();

            auto end = std::chrono::steady_clock::now();
            avg_fps += (std::chrono::seconds(1).count() 
                    / std::chrono::duration<double>(end - start).count());
            avg_fps /= 2;
        }

        std::cout << "FPS: " << avg_fps << '\n';
        
        return 1;
    }

    void point(const hw::vec2& t_pos, const hw::color& t_color)
    {
        get_anon_shapes().push_back(make_unique<da::Point>(t_pos, t_color));
    }
    void point(const int t_x, const int t_y, const hw::color& t_color)
    {
        point(hw::vec2{ t_x, t_y }, t_color);
    }

    Point::Point(const hw::vec2& t_pos, const hw::color& t_color)
        : m_value(t_pos)
        , m_color(t_color)
    {
        get_shapes().push_back(this);
    }

    Point::Point(const int t_x, const int t_y, const hw::color& t_color)
        : m_value(hw::vec2{ t_x, t_y })
        , m_color(t_color)
    {
        get_shapes().push_back(this);
    }

    Point::Point(hw::vec2&& t_pos, hw::color&& t_color)
        : m_value(std::move(t_pos))
        , m_color(std::move(t_color))
    {
        get_shapes().push_back(this);
    }

    void Point::draw()
    {
        SDL_SetRenderDrawColor(get_renderer(), m_color.r, m_color.g, m_color.b, m_color.a);
        SDL_RenderDrawPoint(get_renderer(), m_value.x, m_value.y);
    }

    void line(const hw::vec2& t_a, const hw::vec2& t_b, const hw::color& t_color)
    {
        get_anon_shapes().push_back(make_unique<Line>(t_a, t_b, t_color));
    }
    void line(const int t_x1, const int t_y1,
              const int t_x2, const int t_y2, 
              const hw::color& t_color)
    {
        line(hw::vec2{ t_x1, t_y1 }, hw::vec2{ t_x2, t_y2 }, t_color);
    }

    Line::Line(const int t_x1, const int t_y1, const int t_x2, const int t_y2,
            const hw::color& t_color)
        : m_start(hw::vec2{ t_x1, t_y1 })
        , m_end(hw::vec2{ t_x2, t_y2 })
        , m_color(t_color)
    {
        get_shapes().push_back(this);
    }

    Line::Line(const hw::vec2& t_a, const hw::vec2& t_b, const hw::color& t_color)
        : m_start(t_a)
        , m_end(t_b)
        , m_color(t_color)
    {
        get_shapes().push_back(this);
    }

    Line::Line(hw::vec2&& t_a, hw::vec2&& t_b, hw::color&& t_color)
        : m_start(std::move(t_a))
        , m_end(std::move(t_b))
        , m_color(std::move(t_color))
    {
        get_shapes().push_back(this);
    }

    void Line::draw()
    {
        SDL_SetRenderDrawColor(get_renderer(), m_color.r, m_color.g, m_color.b, m_color.a);
        SDL_RenderDrawLine(get_renderer(), m_start.x, m_start.y, m_end.x, m_end.y);
    }

    void outline_triangle(const hw::vec2& t_pos1, const hw::vec2& t_pos2, const hw::vec2& t_pos3,
                          const hw::color& t_color)
    {
        get_anon_shapes().push_back(make_unique<OutlineTriangle>(t_pos1, t_pos2, t_pos3, t_color));
    }
    void outline_triangle(const int t_x1, const int t_y1, 
                          const int t_x2, const int t_y2,
                          const int t_x3, const int t_y3,
                          const hw::color& t_color)
    {
        outline_triangle(hw::vec2{ t_x1, t_y1 },
                         hw::vec2{ t_x2, t_y2 },
                         hw::vec2{ t_x3, t_y3 },
                         t_color);
    }

    OutlineTriangle::OutlineTriangle(const int t_x1, const int t_y1, 
                                     const int t_x2, const int t_y2,
                                     const int t_x3, const int t_y3,
                                     const hw::color& t_color)
        : m_first(hw::vec2{ t_x1, t_y1 })
        , m_second(hw::vec2{ t_x2, t_y2 })
        , m_third(hw::vec2{ t_x3, t_y3 })
        , m_color(t_color)
    {
         get_shapes().push_back(this);
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
        get_shapes().push_back(this);
    }

    OutlineTriangle::OutlineTriangle(hw::vec2&& t_pos1, hw::vec2&& t_pos2, hw::vec2&& t_pos3,
            hw::color&& t_color)
        : m_first(std::move(t_pos1))
        , m_second(std::move(t_pos2))
        , m_third(std::move(t_pos3))
        , m_color(std::move(t_color))
    {
        get_shapes().push_back(this);
    }

    void OutlineTriangle::draw()
    {
        SDL_SetRenderDrawColor(get_renderer(), m_color.r, m_color.g, m_color.b, m_color.a);
        SDL_RenderDrawLine(get_renderer(), m_first.x, m_first.y, m_second.x, m_second.y);
        SDL_RenderDrawLine(get_renderer(), m_second.x, m_second.y, m_third.x, m_third.y);
        SDL_RenderDrawLine(get_renderer(), m_third.x, m_third.y, m_first.x, m_first.y);
    }

    void rectangle(const hw::vec2& t_pos, const int t_width, const int t_height,
              const hw::color& t_color)
    {
        get_anon_shapes().push_back(make_unique<Rectangle>(t_pos, t_width, t_height, t_color));
    }

    void rectangle(const int t_x, const int t_y, const int t_width, const int t_height,
              const hw::color& t_color)
    {
        rectangle(hw::vec2{ t_x, t_y }, t_width, t_height, t_color);
    }

    Rectangle::Rectangle(const int t_x, const int t_y,
                         const int t_width, const int t_height,
                         const hw::color& t_color)
        : m_pos(hw::vec2{ t_x, t_y })
        , m_dimensions(hw::vec2{ t_width, t_height })
        , m_color(t_color)
    {
        get_shapes().push_back(this);
    }

    Rectangle::Rectangle(const hw::vec2& t_pos, const int t_width, const int t_height,
                         const hw::color& t_color)
        : m_pos(t_pos)
        , m_dimensions(hw::vec2{ t_width, t_height })
        , m_color(t_color)
    {
        get_shapes().push_back(this);
    }

    Rectangle::Rectangle(hw::vec2&& t_pos, const int t_width, const int t_height, 
                         hw::color&& t_color)
        : m_pos(std::move(t_pos))
        , m_dimensions(hw::vec2{ t_width, t_height })
        , m_color(std::move(t_color))
    {
        get_shapes().push_back(this);
    }

    void Rectangle::draw()
    {
        SDL_SetRenderDrawColor(get_renderer(), m_color.r, m_color.g, m_color.b, m_color.a);
        
        SDL_Rect tmp_rect;

        tmp_rect.x = m_pos.x;
        tmp_rect.y = m_pos.y;
        tmp_rect.w = m_dimensions.x;
        tmp_rect.h = m_dimensions.y;

        SDL_RenderFillRect(get_renderer(), &tmp_rect);
    }

    void outline_rectangle(const hw::vec2& t_pos, const int t_width, const int t_height,
                           const hw::color& t_color)
    {
        get_anon_shapes().push_back(make_unique<OutlineRectangle>(t_pos, t_width, t_height, t_color));
    }
    void outline_rectangle(const int t_x, const int t_y, const int t_width, const int t_height,
                           const hw::color& t_color)
    {
        outline_rectangle(hw::vec2{ t_x, t_y }, t_width, t_height, t_color);
    }

    OutlineRectangle::OutlineRectangle(const int t_x, const int t_y, 
                                       const int t_width, const int t_height,
                                       const hw::color& t_color)
        : m_pos(hw::vec2{ t_x, t_y })
        , m_dimensions(hw::vec2{ t_width, t_height })
        , m_color(t_color)
    {
        get_shapes().push_back(this);
    }

    OutlineRectangle::OutlineRectangle(const hw::vec2& t_start, const int t_width, const int t_height,
                                       const hw::color& t_color)
        : m_pos(t_start)
        , m_dimensions(hw::vec2{ t_width, t_height })
        , m_color(t_color)
    {
        get_shapes().push_back(this);
    }

    OutlineRectangle::OutlineRectangle(hw::vec2&& t_start, const int t_width, const int t_height,
                                       hw::color&& t_color)
        : m_pos(std::move(t_start))
        , m_dimensions(hw::vec2{ t_width, t_height })
        , m_color(std::move(t_color))
    {
        get_shapes().push_back(this);
    }

    void OutlineRectangle::draw()
    {
        SDL_SetRenderDrawColor(get_renderer(), m_color.r, m_color.g, m_color.b, m_color.a);
        
        SDL_Rect tmp_rect;

        tmp_rect.x = m_pos.x;
        tmp_rect.y = m_pos.y;
        tmp_rect.w = m_dimensions.x;
        tmp_rect.h = m_dimensions.y;

        SDL_RenderDrawRect(get_renderer(), &tmp_rect);
    }
}

