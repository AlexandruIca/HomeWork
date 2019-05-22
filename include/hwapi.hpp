///
/// @file hwapi.hpp
/// This file contains the api for drawing primitives. To draw a primitive
/// you have to call <primitive>(positions...) where '<primitive>' can be
/// point, line, rectangle, triangle, circle. To draw only the outline
/// of a primitive just call outline_<primitive>(positions...).
/// To draw primitives but also be able to modify them in some way
/// (eg: change their color) you should create objects of type
/// <primitive>. Only the naming convention is different. To
/// create an object of type triangle:
/// @code{.cpp}
/// Triangle shape{ x1, y1, x2, y2, x3, y3 };
/// @endcode
/// And to draw only the outline:
/// @code{.cpp}
/// OutlineTriangle shape{ x1, y1, x2, y2, x3, y3 };
/// @endcode
/// This file also provides functions to modify the size of the window
/// that will be created to draw stuff.
///
#pragma once
#ifndef HWAPI_HPP
#define HWAPI_HPP

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "color.hpp"
#include "vec2.hpp"
#include "window.hpp"

///
/// @brief Provides an easy to use api for drawing different primitives
///        like points, lines, rectangles etc.
///
namespace dummy_api {
    class Shape;

    ///
    /// @brief Accesses the vector of Shapes.
    ///
    std::vector<dummy_api::Shape*>& get_shapes();
    ///
    /// @brief Accesses the vector of anonymous Shapes.
    ///
    /// This vector holds pointers to shapes that are in the vector returned
    /// by @ref get_shapes so that when you create a shape like this:
    /// @code{.cpp}
    /// {
    ///     Rectangle r{};
    ///     // do stuff
    /// } // scope ending
    /// @endcode
    /// the destructor of the shape doesn't get called and there is no
    /// segfault. Call methods starting with lowercase to create anonymous
    /// shapes.
    /// The disadvantage of anonymous shapes is that you can't change anything
    /// about them later.
    ///
    std::vector<std::unique_ptr<dummy_api::Shape>>& get_anon_shapes();
    ///
    /// @brief Gets the global renderer(available only if
    ///        @ref NO_DEFAULT_WINDOW is not defined).
    ///
    // SDL_Renderer* get_renderer();
    ///
    /// @brief Gets the global window(available only if
    ///        @ref NO_DEFAULT_WINDOW is not defined).
    ///
    // SDL_Window* get_window();
    ///
    /// Gets the default window which is created for easy development.
    /// By default a 640x480 window is created(during the @ref draw call)
    ///
    /// @retval Returns nullptr if you call it before @ref draw. Otherwise
    ///         it returns that 640x480 window.
    ///
    hw::window* get_global_window();
    ///
    /// @retval If you don't call @ref set_global_width it returns 640
    ///         by default.
    ///
    int get_global_width();
    ///
    /// @retval If you don't call @ref set_global_height it returns 480
    ///         by default.
    ///
    int get_global_height();
    ///
    /// By default the width of the window is 640. If you want to change it
    /// call this.
    ///
    /// @param t_width New width.
    ///
    void set_global_width(const int t_width);
    ///
    /// By default the height of the window is 640. If you want to change it
    /// call this.
    ///
    /// @param t_height New height.
    ///
    void set_global_height(const int t_height);
    ///
    /// @brief Sets the background of the global color.
    ///
    void set_background_color(hw::color const& t_color) noexcept;
    ///
    /// @brief Gets the background color of the global window.
    ///
    hw::color get_background_color() noexcept;
    ///
    /// @brief Gets mouse position in window.
    ///
    hw::vec2 get_mouse_state() noexcept;
    ///
    /// @return true If the left mouse button is being clicked, false otherwise
    ///
    bool is_left_click() noexcept;
    ///
    /// @return true If the right mouse button is being clicked, false otherwise
    ///
    bool is_right_click() noexcept;

    ///
    /// @brief Draws all the shapes currently requested.
    ///
    /// Should be called every frame since shapes may be updated frequently
    /// (eg. changes of color).
    ///
    /// @warning Does NOTHING else, only draws the
    ///          shapes(no window event handling).
    ///
    void draw_shapes();
    ///
    /// @brief Updates the window and handles events.
    ///
    /// This is an entire "main loop" that draws everything on the screen
    /// and stops when either the window is closed by the user or the
    /// 'ESC' key is pressed.
    ///
    /// @param[in] t_call needs to be a void function that takes a float
    ///            as a parameter. The parameter of that function is
    ///            the elapsed time since the last frame.
    ///
    int draw(std::function<void(double)> t_call = [](double) -> void {});
    ///
    /// @brief Draws a point with given position and color.
    ///
    void point(const hw::vec2& t_pos, const hw::color& t_color = hw::color{});
    ///
    /// Is the same as: @code{.cpp} point(hw::vec2{ t_x, t_y }, t_color);
    ///                 @endcode
    ///
    void point(const int t_x, const int t_y,
               const hw::color& t_color = hw::color{});
    ///
    /// @brief Draws a line with given position and color.
    ///
    /// The order in which the points are given is irrelevant.
    ///
    void line(const hw::vec2& t_a, const hw::vec2& t_b,
              const hw::color& t_color = hw::color{});
    ///
    /// Same as:
    /// @code{.cpp}
    /// line(hw::vec2{ t_x1, t_y1}, hw::vec2{ t_x2, t_y2 }, t_color);
    /// @endcode
    ///
    void line(const int t_x1, const int t_y1, const int t_x2, const int t_y2,
              const hw::color& t_color = hw::color{});
    ///
    /// @brief Draws a triangle with given position and color.
    ///
    void triangle(const hw::vec2& t_pos1, const hw::vec2& t_pos2,
                  const hw::vec2& t_pos3,
                  const hw::color& t_color = hw::color{});
    ///
    /// Same as:
    /// @code{.cpp}
    /// triangle(hw::vec2{ t_x1, t_y1 },
    ///          hw::vec2{ t_x2, t_y2 },
    ///          hw::vec2{ t_x3, t_y3 },
    ///          t_color);
    /// @endcode
    ///
    void triangle(const int t_x1, const int t_y1, const int t_x2,
                  const int t_y2, const int t_x3, const int t_y3,
                  const hw::color& t_color = hw::color{});
    ///
    /// @brief Draws a triangle with given position and color but does not
    ///        fill it.
    ///
    void outline_triangle(const hw::vec2& t_pos1, const hw::vec2& t_pos2,
                          const hw::vec2& t_pos3,
                          const hw::color& t_color = hw::color{});
    ///
    /// Same as:
    /// @code
    /// outline_triangle(hw::vec2{ t_x1, t_y1 },
    ///                  hw::vec2{ t_x2, t_y2 },
    ///                  hw::vec2{ t_x3, t_y3 },
    ///                  t_color);
    /// @endcode
    ///
    void outline_triangle(const int t_x1, const int t_y1, const int t_x2,
                          const int t_y2, const int t_x3, const int t_y3,
                          const hw::color& t_color = hw::color{});
    ///
    /// @brief Draws a rectangle with given position and color
    ///
    /// @param[in] t_pos is the point where the rectangle should be drawn.
    /// @param[in] t_width is the width starting from @ref t_pos (right).
    /// @param[in] t_height is the height starting from @ref t_pos (down).
    ///
    void rectangle(const hw::vec2& t_pos, const int t_width, const int t_height,
                   const hw::color& t_color = hw::color{});
    ///
    /// Same as:
    /// @code{.cpp}
    /// rectangle(hw::vec2{ t_x, t_y },
    ///           t_width, t_height,
    ///           t_color);
    /// @endcode
    ///
    void rectangle(const int t_x, const int t_y, const int t_width,
                   const int t_height, const hw::color& t_color = hw::color{});
    ///
    /// @brief Draws a rectangle with given position and color but does
    ///        not fill it.
    ///
    /// Parameters have the same meaning as in @ref rectangle.
    ///
    void outline_rectangle(const hw::vec2& t_pos, const int t_width,
                           const int t_height,
                           const hw::color& t_color = hw::color{});
    ///
    /// Same as:
    /// @code{.cpp}
    /// outline_rectangle(hw::vec2{ t_x, t_y },
    ///                   t_width, t_height,
    ///                   t_color);
    /// @endcode
    ///
    void outline_rectangle(const int t_x, const int t_y, const int t_width,
                           const int t_height,
                           const hw::color& t_color = hw::color{});
    ///
    /// @brief Draws a circle with given center, radius and color.
    ///
    void circle(const hw::vec2& t_pos, const int t_radius,
                const hw::color& t_color = hw::color{});
    ///
    /// Same as:
    /// @code{.cpp}
    /// circle(hw::vec2{ t_x, t_y },
    ///        t_radius,
    ///        t_color);
    /// @endcode
    ///
    void circle(const int t_x, const int t_y, const int t_radius,
                const hw::color& t_color = hw::color{});
    ///
    /// @brief Draws a circle with given center, radius and color but
    ///        does not fill it.
    ///
    void outline_circle(const hw::vec2& t_pos, const int t_radius,
                        const hw::color& t_color = hw::color{});
    ///
    /// Same as:
    /// @code{.cpp}
    /// outline_circle(hw::vec2{ t_x, t_y },
    ///                t_radius,
    ///                t_color);
    /// @endcode
    ///
    void outline_circle(const int t_x, const int t_y, const int t_radius,
                        const hw::color& t_color = hw::color{});

    ///
    /// @brief Every object that has information about a primitive is
    ///        derived from @ref Shape.
    ///
    /// Cannot be instantiated(only through derived ojects).
    /// Instead of calling functions like @ref point or @ref line you
    /// can create objects that
    /// store information needed to draw the primitives so you can modify
    /// it later.
    /// Objects have the UpperCamelCase naming convention(eg. @ref Line,
    /// @ref Point).
    /// Constructors of derived objects should have the same parameters
    /// as their functions relatives.
    /// Each derived class will provide equality operators and comparison
    /// operators for the same types.
    /// Each derived class will provide methods for retrieving information
    /// like color and position.
    ///
    /// @attention Constructors of types derived from @ref Shape take
    ///            the same parameters(with the same meaning) as their
    ///            function equivalents.
    ///
    class Shape
    {
      private:
        bool m_hidden{false};

      protected:
        Shape();

        ///
        /// @brief Helpful for implementing the hide function.
        ///
        void store_color(hw::vec2 const& t_color) noexcept;
        ///
        /// If the show function was called get the color of the shape.
        ///
        hw::vec2 get_previous_color() const noexcept;

      public:
        virtual ~Shape() noexcept = default;

        virtual void draw() = 0;
        void draw_shape() noexcept;
        void hide() noexcept;
        void show() noexcept;

        inline bool hidden() const noexcept
        {
            return m_hidden;
        }
    };

    ///
    /// @brief Describes a @ref Point object.
    ///
    class Point final : public Shape
    {
        hw::vec2 m_value{};
        hw::color m_color{};

      public:
        Point() = default;
        Point(const int t_x, const int t_y,
              const hw::color& t_color = hw::color{});
        Point(const hw::vec2& t_pos, const hw::color& t_color = hw::color{});
        Point(hw::vec2&& t_pos, hw::color&& t_color = hw::color{});
        ~Point() noexcept override = default;

        void draw() final;

        inline hw::vec2& data()
        {
            return m_value;
        }
        inline const hw::vec2& data() const
        {
            return m_value;
        }

        inline hw::color& color()
        {
            return m_color;
        }
        inline const hw::color& color() const
        {
            return m_color;
        }

        Point& operator=(const Point& t_other)
        {
            m_value = t_other.data();

            return *this;
        }

        inline bool operator==(const Point& t_other) const
        {
            return m_value == t_other.data();
        }
        inline bool operator!=(const Point& t_other) const
        {
            return !this->operator==(t_other);
        }
    };

    ///
    /// @brief Describes a @ref Line object.
    ///
    class Line final : public Shape
    {
        hw::vec2 m_start{};
        hw::vec2 m_end{};
        hw::color m_color;

      public:
        Line() = default;
        Line(const int t_x1, const int t_y1, const int t_x2, const int t_y2,
             const hw::color& t_color = hw::color{});
        Line(const hw::vec2& t_a, const hw::vec2& t_b,
             const hw::color& t_color = hw::color{});
        Line(hw::vec2&& t_a, hw::vec2&& t_b, hw::color&& t_color = hw::color{});
        ~Line() noexcept override = default;

        void draw() final;

        inline hw::vec2& first()
        {
            return m_start;
        }
        inline const hw::vec2& first() const
        {
            return m_start;
        }

        inline hw::vec2& second()
        {
            return m_end;
        }
        inline const hw::vec2& second() const
        {
            return m_end;
        }

        inline hw::color& color()
        {
            return m_color;
        }
        inline const hw::color& color() const
        {
            return m_color;
        }

        Line& operator=(const Line& t_other)
        {
            m_start = t_other.first();
            m_end = t_other.second();

            return *this;
        }

        inline bool operator==(const Line& t_other) const
        {
            return m_start == t_other.first() && m_end == t_other.second();
        }
        inline bool operator!=(const Line& t_other) const
        {
            return !this->operator==(t_other);
        }
    };

    ///
    /// @brief Describes a @ref Triangle object.
    ///
    class Triangle final : public Shape
    {
        hw::vec2 m_first{};
        hw::vec2 m_second{};
        hw::vec2 m_third{};
        hw::color m_color{};

      public:
        Triangle() = default;
        Triangle(const int t_x1, const int t_y1, const int t_x2, const int t_y2,
                 const int t_x3, const int t_y3,
                 const hw::color& t_color = hw::color{});
        Triangle(const hw::vec2& t_pos1, const hw::vec2& t_pos2,
                 const hw::vec2& t_pos3,
                 const hw::color& t_color = hw::color{});
        Triangle(hw::vec2&& t_pos1, hw::vec2&& t_pos2, hw::vec2&& t_pos3,
                 hw::color&& t_color = hw::color{});
        ~Triangle() noexcept override = default;

        void draw() final;

        inline hw::vec2& first()
        {
            return m_first;
        }
        inline const hw::vec2& first() const
        {
            return m_first;
        }

        inline hw::vec2& second()
        {
            return m_second;
        }
        inline const hw::vec2& second() const
        {
            return m_second;
        }

        inline hw::vec2& third()
        {
            return m_third;
        }
        inline const hw::vec2& third() const
        {
            return m_third;
        }

        inline hw::color& color()
        {
            return m_color;
        }
        inline const hw::color& color() const
        {
            return m_color;
        }

        Triangle& operator=(const Triangle& t_other)
        {
            m_first = t_other.first();
            m_second = t_other.second();
            m_third = t_other.third();

            return *this;
        }

        inline bool operator==(const Triangle& t_other) const
        {
            return m_first == t_other.first() && m_second == t_other.second() &&
                   m_third == t_other.third();
        }
        inline bool operator!=(const Triangle& t_other) const
        {
            return !this->operator==(t_other);
        }
    };

    ///
    /// @brief Describes an @ref OutlineTriangle object.
    ///
    class OutlineTriangle final : public Shape
    {
        hw::vec2 m_first{};
        hw::vec2 m_second{};
        hw::vec2 m_third{};
        hw::color m_color{};

      public:
        OutlineTriangle() = default;
        OutlineTriangle(const int t_x1, const int t_y1, const int t_x2,
                        const int t_y2, const int t_x3, const int t_y3,
                        const hw::color& t_color = hw::color{});
        OutlineTriangle(const hw::vec2& t_pos1, const hw::vec2& t_pos2,
                        const hw::vec2& t_pos3,
                        const hw::color& t_color = hw::color{});
        OutlineTriangle(hw::vec2&& t_pos1, hw::vec2&& t_pos2, hw::vec2&& t_pos3,
                        hw::color&& t_color = hw::color{});
        ~OutlineTriangle() noexcept override = default;

        void draw() final;

        inline hw::vec2& first()
        {
            return m_first;
        }
        inline const hw::vec2& first() const
        {
            return m_first;
        }

        inline hw::vec2& second()
        {
            return m_second;
        }
        inline const hw::vec2& second() const
        {
            return m_second;
        }

        inline hw::vec2& third()
        {
            return m_third;
        }
        inline const hw::vec2& third() const
        {
            return m_third;
        }

        inline hw::color& color()
        {
            return m_color;
        }
        inline const hw::color& color() const
        {
            return m_color;
        }

        OutlineTriangle& operator=(const Triangle& t_other)
        {
            m_first = t_other.first();
            m_second = t_other.second();
            m_third = t_other.third();

            return *this;
        }

        inline bool operator==(const OutlineTriangle& t_other) const
        {
            return m_first == t_other.first() && m_second == t_other.second() &&
                   m_third == t_other.third();
        }
        inline bool operator!=(const OutlineTriangle& t_other) const
        {
            return !this->operator==(t_other);
        }
    };

    ///
    /// @brief Describes a @ref Rectangle object.
    ///
    class Rectangle final : public Shape
    {
        hw::vec2 m_pos{};
        hw::vec2 m_dimensions{};
        hw::color m_color{};

      public:
        Rectangle() = default;
        Rectangle(const int t_x, const int t_y, const int t_width,
                  const int t_height, const hw::color& t_color = hw::color{});
        Rectangle(const hw::vec2& t_start, const int t_width,
                  const int t_height, const hw::color& t_color = hw::color{});
        Rectangle(hw::vec2&& t_start, const int t_width, const int t_height,
                  hw::color&& t_color = hw::color{});
        ~Rectangle() noexcept override = default;

        void draw() final;

        inline hw::vec2& pos()
        {
            return m_pos;
        }
        inline const hw::vec2& pos() const
        {
            return m_pos;
        }

        inline hw::vec2& dim()
        {
            return m_dimensions;
        }
        inline const hw::vec2& dim() const
        {
            return m_dimensions;
        }

        inline hw::color& color()
        {
            return m_color;
        }
        inline const hw::color& color() const
        {
            return m_color;
        }

        Rectangle& operator=(const Rectangle& t_other)
        {
            m_pos = t_other.pos();
            m_dimensions = t_other.dim();

            return *this;
        }

        inline bool operator==(const Rectangle& t_other) const
        {
            return m_pos == t_other.pos() && m_dimensions == t_other.dim();
        }
        inline bool operator!=(const Rectangle& t_other) const
        {
            return !this->operator==(t_other);
        }
    };

    ///
    /// @brief Describes an @ref OutlineRectangle object.
    ///
    class OutlineRectangle final : public Shape
    {
        hw::vec2 m_pos{};
        hw::vec2 m_dimensions{};
        hw::color m_color{};

      public:
        OutlineRectangle() = default;
        OutlineRectangle(const int t_x, const int t_y, const int t_width,
                         const int t_height,
                         const hw::color& t_color = hw::color{});
        OutlineRectangle(const hw::vec2& t_start, const int t_width,
                         const int t_height,
                         const hw::color& t_color = hw::color{});
        OutlineRectangle(hw::vec2&& t_start, const int t_width,
                         const int t_height, hw::color&& t_color = hw::color{});
        ~OutlineRectangle() noexcept override = default;

        void draw() final;

        inline hw::vec2& pos()
        {
            return m_pos;
        }
        inline const hw::vec2& pos() const
        {
            return m_pos;
        }

        inline hw::vec2& dim()
        {
            return m_dimensions;
        }
        inline const hw::vec2& dim() const
        {
            return m_dimensions;
        }

        inline hw::color& color()
        {
            return m_color;
        }
        inline const hw::color& color() const
        {
            return m_color;
        }

        OutlineRectangle& operator=(const OutlineRectangle& t_other)
        {
            m_pos = t_other.pos();
            m_dimensions = t_other.dim();

            return *this;
        }

        inline bool operator==(const OutlineRectangle& t_other) const
        {
            return m_pos == t_other.pos() && m_dimensions == t_other.dim();
        }
        inline bool operator!=(const OutlineRectangle& t_other) const
        {
            return !this->operator==(t_other);
        }
    };

    ///
    /// @brief Describes a @ref Circle object.
    ///
    class Circle final : public Shape
    {
        hw::vec2 m_pos{};
        int m_radius;
        hw::color m_color{};

      public:
        Circle() = default;
        Circle(const int t_x, const int t_y, const int t_radius,
               const hw::color& t_color = hw::color{});
        Circle(const hw::vec2& t_pos, const int t_radius,
               const hw::color& t_color = hw::color{});
        Circle(hw::vec2&& t_pos, const int t_radius,
               hw::color&& t_color = hw::color{});
        ~Circle() noexcept override = default;

        void draw() final;

        inline hw::vec2& pos()
        {
            return m_pos;
        }
        inline const hw::vec2& pos() const
        {
            return m_pos;
        }

        inline int& radius()
        {
            return m_radius;
        }
        inline const int& radius() const
        {
            return m_radius;
        }

        inline hw::color& color()
        {
            return m_color;
        }
        inline const hw::color& color() const
        {
            return m_color;
        }

        Circle& operator=(const Circle& t_other)
        {
            m_pos = t_other.pos();
            m_radius = t_other.radius();

            return *this;
        }

        inline bool operator==(const Circle& t_other) const
        {
            return m_pos == t_other.pos() && m_radius == t_other.radius();
        }
        inline bool operator!=(const Circle& t_other) const
        {
            return !this->operator==(t_other);
        }
    };

    ///
    /// @brief Describes an @ref OutlineCircle object.
    ///
    class OutlineCircle final : public Shape
    {
        hw::vec2 m_pos{};
        int m_radius;
        hw::color m_color{};

      public:
        OutlineCircle() = default;
        OutlineCircle(const int t_x, const int t_y, const int t_radius,
                      const hw::color& t_color = hw::color{});
        OutlineCircle(const hw::vec2& t_pos, const int t_radius,
                      const hw::color& t_color = hw::color{});
        OutlineCircle(hw::vec2&& t_pos, const int t_radius,
                      hw::color&& t_color = hw::color{});
        ~OutlineCircle() noexcept override = default;

        void draw() final;

        inline hw::vec2& pos()
        {
            return m_pos;
        }
        inline const hw::vec2& pos() const
        {
            return m_pos;
        }

        inline int& radius()
        {
            return m_radius;
        }
        inline const int& radius() const
        {
            return m_radius;
        }

        inline hw::color& color()
        {
            return m_color;
        }
        inline const hw::color& color() const
        {
            return m_color;
        }

        OutlineCircle& operator=(const OutlineCircle& t_other)
        {
            m_pos = t_other.pos();
            m_radius = t_other.radius();

            return *this;
        }

        inline bool operator==(const OutlineCircle& t_other) const
        {
            return m_pos == t_other.pos() && m_radius == t_other.radius();
        }
        inline bool operator!=(const OutlineCircle& t_other) const
        {
            return !this->operator==(t_other);
        }
    };

    ///
    /// @brief Describes an @ref Image object.
    ///
    class Image : public Shape
    {
      private:
        ///
        /// If the user specifies a rectangle or calls @ref follow this will
        /// just point to the specified rectangle. Otherwise it will create
        /// a rect on the heap with specified dimensions.
        ///
        OutlineRectangle* m_rect{nullptr};
        std::string m_path{};
        bool m_created_here{false};
        hw::color m_color_key{};
        bool m_created_image{false};

        SDL_Texture* m_image{nullptr};

        ///
        /// @attention MUST NOT be called before @ref draw_shapes.
        ///
        void create_image() noexcept;
        void delete_rect_if_created_here() noexcept;

      public:
        Image() = default;
        ///
        /// @param[in] t_path Where the image is located.
        ///
        /// When no rect is specified there will be one created in the center
        /// of the screen with coordinates 100, 100.
        ///
        Image(std::string const t_path);
        ///
        /// @param[in] t_path Where the image is located.
        /// @param[in] t_x X coordonate of the rect representing the image.
        /// @param[in] t_y Y coordonate of the rect representing the image.
        /// @param[in] t_width Width of the rect representing the image.
        /// @param[in] t_height Height of the rect representing the image.
        ///
        Image(std::string const t_path, int const t_x, int const t_y,
              int const t_width, int const t_height);
        ///
        /// @brief Same as @ref Rectangle parameters except t_path.
        ///
        Image(std::string const t_path, hw::vec2 const& t_pos,
              hw::vec2 const& t_dim);
        ///
        /// @param[in] t_rect With this specified the image structure will
        ///                   keep a pointer to the rect so whenever the rect
        ///                   updates the image will also follow the rectangle.
        ///
        Image(std::string const t_path, OutlineRectangle& t_rect);
        ~Image() noexcept override;

        ///
        /// @brief Specify where the image is located.
        ///
        /// @attention Calling inside drawing loop has no effect.
        ///
        void set_path(std::string const t_path);
        ///
        /// @brief Ignore specified color
        ///
        /// If you want to load a sprite and it's background color should not
        /// be rendered specify it with this function.
        ///
        /// @attention Can NOT be changed dynamically, meaning if you call this
        ///            inside the drawing loop it will have no effect.
        ///
        void set_color_key(hw::color const& t_color) noexcept;
        ///
        /// Whenever the rectangle changes position/dimensions, the image will
        /// also change accordingly.
        ///
        void follow(OutlineRectangle& t_rect);

        void draw() final;
    };
} // namespace dummy_api

#endif // !HWAPI_HPP
