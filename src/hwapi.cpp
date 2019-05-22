#include "hwapi.hpp"
#include "window.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <utility>

#include "SDL2/SDL_image.h"

#include "drawing_api.hpp"

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

///
/// @brief Globals are defined here.
///
/// Inline namespace instead of anonymous because it's clear that the namespace
/// is holding globals but also because I could not get it to show documentation
/// for
/// @ref g_inside_draw_call otherwise.
///
inline namespace globals {
    hw::window* g_global_window{nullptr};
    int g_global_width{640};
    int g_global_height{480};
    hw::color g_background{0, 0, 0};
    ///
    /// This variable is needed to see whether the user wants to draw a static
    /// primitve or not.
    /// By static primitive I mean this:
    /// @code
    /// int main()
    /// {
    ///     triangle(/*parameters...*/);
    ///     return draw();
    /// }
    /// @endcode
    /// This will draw a static triangle since it's called before the draw call.
    /// The function will add the @ref Triangle shape to the global vector of
    /// shapes.
    ///
    /// But if it's called like this:
    /// @code
    /// int main()
    /// {
    ///     return draw(WITH{
    ///         triangle(/*parameters...*/);
    ///     });
    /// }
    /// @endcode
    /// This will add nothing to the global vector of shapes. It's just calling
    /// SDL_RenderDrawTriangle. Keep in mind this is available for all
    /// primitives, not just triangles, this is just an example. This behaviour
    /// allows for games like snake where I need to draw shapes on the fly, I
    /// cannot just declare a lot of @ref Rectangle shapes because a shape's
    /// destructor is non trivial and it adds shapes to the global vector.
    ///
    bool g_inside_draw_call{false};
} // namespace globals

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

    hw::color get_background_color() noexcept
    {
        return g_background;
    }

    hw::vec2 get_mouse_state() noexcept
    {
        hw::vec2 result{0, 0};

        if(!g_inside_draw_call) {
            return result;
        }

        SDL_GetMouseState(&result.x, &result.y);

        return result;
    }

    bool is_left_click() noexcept
    {
        if(!g_inside_draw_call) {
            return false;
        }
        SDL_PumpEvents();
        return SDL_GetMouseState(nullptr, nullptr) &
               SDL_BUTTON(SDL_BUTTON_LEFT);
    }

    bool is_right_click() noexcept
    {
        if(!g_inside_draw_call) {
            return false;
        }
        SDL_PumpEvents();
        return SDL_GetMouseState(nullptr, nullptr) &
               SDL_BUTTON(SDL_BUTTON_RIGHT);
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

        g_inside_draw_call = true;

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
        if(!g_inside_draw_call) {
            get_anon_shapes().push_back(make_unique<da::Point>(t_pos, t_color));
        }
        else {
            hw::draw_point(get_global_window()->get_renderer(), t_pos, t_color);
        }
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
        hw::draw_point(get_global_window()->get_renderer(), m_value, m_color);
    }

    void line(const hw::vec2& t_a, const hw::vec2& t_b,
              const hw::color& t_color)
    {
        if(!g_inside_draw_call) {
            get_anon_shapes().push_back(make_unique<Line>(t_a, t_b, t_color));
        }
        else {
            hw::draw_line(get_global_window()->get_renderer(), t_a, t_b,
                          t_color);
        }
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
        hw::draw_line(get_global_window()->get_renderer(), m_start, m_end,
                      m_color);
    }

    void triangle(const hw::vec2& t_pos1, const hw::vec2& t_pos2,
                  const hw::vec2& t_pos3, const hw::color& t_color)
    {
        if(!g_inside_draw_call) {
            get_anon_shapes().push_back(
                make_unique<Triangle>(t_pos1, t_pos2, t_pos3, t_color));
        }
        else {
            hw::draw_triangle(get_global_window()->get_renderer(), t_pos1,
                              t_pos2, t_pos3, t_color);
        }
    }

    void triangle(const int t_x1, const int t_y1, const int t_x2,
                  const int t_y2, const int t_x3, const int t_y3,
                  const hw::color& t_color)
    {
        triangle(hw::vec2{t_x1, t_y1}, hw::vec2{t_x2, t_y2},
                 hw::vec2{t_x3, t_y3}, t_color);
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

    void Triangle::draw()
    {
        hw::draw_triangle(get_global_window()->get_renderer(), m_first,
                          m_second, m_third, m_color);
    }

    void outline_triangle(const hw::vec2& t_pos1, const hw::vec2& t_pos2,
                          const hw::vec2& t_pos3, const hw::color& t_color)
    {
        if(!g_inside_draw_call) {
            get_anon_shapes().push_back(
                make_unique<OutlineTriangle>(t_pos1, t_pos2, t_pos3, t_color));
        }
        else {
            hw::draw_outline_triangle(get_global_window()->get_renderer(),
                                      t_pos1, t_pos2, t_pos3, t_color);
        }
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
        hw::draw_outline_triangle(get_global_window()->get_renderer(), m_first,
                                  m_second, m_third, m_color);
    }

    void rectangle(const hw::vec2& t_pos, const int t_width, const int t_height,
                   const hw::color& t_color)
    {
        if(!g_inside_draw_call) {
            get_anon_shapes().push_back(
                make_unique<Rectangle>(t_pos, t_width, t_height, t_color));
        }
        else {
            hw::draw_rectangle(get_global_window()->get_renderer(), t_pos,
                               t_width, t_height, t_color);
        }
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
        hw::draw_rectangle(get_global_window()->get_renderer(), m_pos,
                           m_dimensions.x, m_dimensions.y, m_color);
    }

    void outline_rectangle(const hw::vec2& t_pos, const int t_width,
                           const int t_height, const hw::color& t_color)
    {
        if(!g_inside_draw_call) {
            get_anon_shapes().push_back(make_unique<OutlineRectangle>(
                t_pos, t_width, t_height, t_color));
        }
        else {
            hw::draw_outline_rectangle(get_global_window()->get_renderer(),
                                       t_pos, t_width, t_height, t_color);
        }
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
        hw::draw_outline_rectangle(get_global_window()->get_renderer(), m_pos,
                                   m_dimensions.x, m_dimensions.y, m_color);
    }

    void circle(const hw::vec2& t_pos, const int t_radius,
                const hw::color& t_color)
    {
        if(!g_inside_draw_call) {
            get_anon_shapes().push_back(
                make_unique<Circle>(t_pos, t_radius, t_color));
        }
        else {
            hw::draw_circle(get_global_window()->get_renderer(), t_pos,
                            t_radius, t_color);
        }
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

    void Circle::draw()
    {
        hw::draw_circle(get_global_window()->get_renderer(), m_pos, m_radius,
                        m_color);
    }

    void outline_circle(const hw::vec2& t_pos, const int t_radius,
                        const hw::color& t_color)
    {
        if(!g_inside_draw_call) {
            get_anon_shapes().push_back(
                make_unique<OutlineCircle>(t_pos, t_radius, t_color));
        }
        else {
            hw::draw_outline_circle(get_global_window()->get_renderer(), t_pos,
                                    t_radius, t_color);
        }
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

    void OutlineCircle::draw()
    {
        hw::draw_outline_circle(get_global_window()->get_renderer(), m_pos,
                                m_radius, m_color);
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

        SDL_RenderCopy(get_global_window()->get_renderer(), m_image, nullptr,
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
