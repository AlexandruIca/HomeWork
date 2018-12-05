///
/// @file
///
#pragma once
#ifndef HWAPI_HPP
#define HWAPI_HPP

#include <functional>
#include <memory>
#include <vector>

#include "color.hpp"
#include "vec2.hpp"
#include "window.hpp"

/// 
/// @brief
///
//struct SDL_Renderer;
//struct SDL_Window;

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
	std::vector<std::unique_ptr<dummy_api::Shape>>& get_anon_shapes();
	///
	/// @brief Gets the global renderer(available only if 
	///        @ref NO_DEFAULT_WINDOW is not defined).
	///
	//SDL_Renderer* get_renderer();
	///
	/// @brief Gets the global window(available only if 
	///        @ref NO_DEFAULT_WINDOW is not defined).
	///
	//SDL_Window* get_window();
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
    void point(const hw::vec2& t_pos, 
			   const hw::color& t_color = hw::color{});
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
    void line(const int t_x1, const int t_y1, 
              const int t_x2, const int t_y2, 
              const hw::color& t_color = hw::color{});
    ///
    /// @brief Draws a triangle with given position and color.
    ///
    void triangle(const hw::vec2& t_pos1,
                  const hw::vec2& t_pos2,
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
    void triangle(const int t_x1, const int t_y1, 
                  const int t_x2, const int t_y2, 
                  const int t_x3, const int t_y3, 
                  const hw::color& t_color = hw::color{});
    ///
    /// @brief Draws a triangle with given position and color but does not
	///        fill it.
    ///
    void outline_triangle(const hw::vec2& t_pos1,
                          const hw::vec2& t_pos2,
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
    void outline_triangle(const int t_x1, const int t_y1, 
                          const int t_x2, const int t_y2, 
                          const int t_x3, const int t_y3,
                          const hw::color& t_color = hw::color{});
    ///
    /// @brief Draws a rectangle with given position and color
    ///
    /// @param[in] t_pos is the point where the rectangle should be drawn.
    /// @param[in] t_width is the width starting from @ref t_pos (right).
    /// @param[in] t_height is the height starting from @ref t_pos (down).
    ///
    void rectangle(const hw::vec2& t_pos, const int t_width, 
			const int t_height, const hw::color& t_color = hw::color{});
    ///
    /// Same as:
    /// @code{.cpp}
    /// rectangle(hw::vec2{ t_x, t_y },
    ///           t_width, t_height,
    ///           t_color);
    /// @endcode
    ///
    void rectangle(const int t_x, const int t_y, 
                   const int t_width, const int t_height, 
                   const hw::color& t_color = hw::color{});
    ///
    /// @brief Draws a rectangle with given position and color but does
	///        not fill it.
    /// 
    /// Parameters have the same meaning as in @ref rectangle.
    ///
    void outline_rectangle(const hw::vec2& t_pos, 
                           const int t_width, const int t_height, 
                           const hw::color& t_color = hw::color{});
    ///
    /// Same as:
    /// @code{.cpp}
    /// outline_rectangle(hw::vec2{ t_x, t_y },
    ///                   t_width, t_height,
    ///                   t_color);
    /// @endcode
    ///
    void outline_rectangle(const int t_x, const int t_y, 
                           const int t_width, const int t_height, 
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
    void circle(const int t_x, const int t_y, 
                const int t_radius, 
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
    /// @brief All primitives that can be drawn in @ref dummy_api.
    ///
    enum ShapeType : int 
    {
        POINT, LINE, TRIANGLE, OUTLINE_TRIANGLE, RECTANGLE, 
		OUTLINE_RECTANGLE, CIRCLE, OUTLINE_CIRCLE
    };

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
    class Shape
    {
    protected:
        Shape() = default;
    
    public:
        virtual ~Shape() = default;

        virtual void draw() = 0;
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
        Point(const hw::vec2& t_pos, 
		      const hw::color& t_color = hw::color{});
        Point(hw::vec2&& t_pos, hw::color&& t_color = hw::color{});
        virtual ~Point() = default;

        virtual void draw() final override;

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

        inline Point& operator=(const Point& t_other)
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
        Line(hw::vec2&& t_a, hw::vec2&& t_b, 
		     hw::color&& t_color = hw::color{});
        virtual ~Line() = default;

        virtual void draw() final override;
        
        inline hw::vec2& first()
        {
            return m_start;
        }
        inline hw::vec2& second()
        {
            return m_end;
        }
        inline const hw::vec2& first() const
        {
            return m_start;
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

        inline Line& operator=(const Line& t_other)
        {
            m_start = t_other.first();
            m_end = t_other.second();
            
            return *this;
        }

        inline bool operator==(const Line& t_other) const
        {
            return m_start == t_other.first()
                && m_end == t_other.second();
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
        Triangle(const int t_x1, const int t_y1, 
                 const int t_x2, const int t_y2, 
                 const int t_x3, const int t_y3,
                 const hw::color& t_color = hw::color{});
        Triangle(const hw::vec2& t_pos1,
                 const hw::vec2& t_pos2, 
                 const hw::vec2& t_pos3,
                 const hw::color& t_color = hw::color{});
        Triangle(hw::vec2&& t_pos1, hw::vec2&& t_pos2, hw::vec2&& t_pos3, 
                hw::color&& t_color = hw::color{});
        virtual ~Triangle() = default;

        virtual void draw() final override;

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

        inline Triangle& operator=(const Triangle& t_other)
        {
            m_first = t_other.first();
            m_second = t_other.second();
            m_third = t_other.third();
            
            return *this;
        }

        inline bool operator==(const Triangle& t_other) const
        { 
            return m_first == t_other.first()
                && m_second == t_other.second() 
                && m_third == t_other.third();
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
        OutlineTriangle(const int t_x1, const int t_y1,
                const int t_x2, const int t_y2,
                const int t_x3, const int t_y3,
                const hw::color& t_color = hw::color{});
        OutlineTriangle(const hw::vec2& t_pos1,
                const hw::vec2& t_pos2,
                const hw::vec2& t_pos3, 
                const hw::color& t_color = hw::color{});
        OutlineTriangle(hw::vec2&& t_pos1, hw::vec2&& t_pos2, 
		        hw::vec2&& t_pos3,
                hw::color&& t_color = hw::color{});
        virtual ~OutlineTriangle() = default;

        virtual void draw() final override;
        
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

        inline OutlineTriangle& operator=(const Triangle& t_other)
        {
            m_first = t_other.first();
            m_second = t_other.second();
            m_third = t_other.third();

            return *this;
        }

        inline bool operator==(const OutlineTriangle& t_other) const
        {
            return m_first == t_other.first()
                && m_second == t_other.second()
                && m_third == t_other.third();
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
        Rectangle(const int t_x, const int t_y,
                const int t_width, const int t_height,
                const hw::color& t_color = hw::color{});
        Rectangle(const hw::vec2& t_start, const int t_width, 
		        const int t_height, 
                const hw::color& t_color = hw::color{});
        Rectangle(hw::vec2&& t_start, 
                  const int t_width, const int t_height, 
                  hw::color&& t_color = hw::color{});
        virtual ~Rectangle() = default;

        virtual void draw() final override;
        
        inline hw::vec2& pos()
        {
            return m_pos;
        }
        inline hw::vec2& dim()
        {
            return m_dimensions;
        }
        inline const hw::vec2& pos() const
        {
            return m_pos;
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

        inline Rectangle& operator=(const Rectangle& t_other)
        {
            m_pos = t_other.pos();
            m_dimensions = t_other.dim();
            
            return *this;
        }

        inline bool operator==(const Rectangle& t_other) const
        {
            return m_pos == t_other.pos()
                && m_dimensions == t_other.dim();
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
        OutlineRectangle(const int t_x, const int t_y,
                const int t_width, const int t_height,
                const hw::color& t_color = hw::color{});
        OutlineRectangle(const hw::vec2& t_start, const int t_width, 
		        const int t_height, const hw::color& t_color = hw::color{});
        OutlineRectangle(hw::vec2&& t_start, const int t_width, 
		         const int t_height, hw::color&& t_color = hw::color{});
        virtual ~OutlineRectangle() = default;

        virtual void draw() final override;
        
        inline hw::vec2& pos()
        {
            return m_pos;
        }
        inline hw::vec2& dim()
        {
            return m_dimensions;
        }
        inline const hw::vec2& pos() const
        {
            return m_pos;
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

        inline OutlineRectangle& operator=(const OutlineRectangle& t_other)
        {
            m_pos = t_other.pos();
            m_dimensions = t_other.dim();
            
            return *this;
        }

        inline bool operator==(const OutlineRectangle& t_other) const
        {
            return m_pos == t_other.pos()
                && m_dimensions == t_other.dim();
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
        virtual ~Circle() = default;

        virtual void draw() final override;

        inline hw::vec2& pos()
        {
            return m_pos;
        }
        inline int& radius()
        {
            return m_radius;
        }
        inline const hw::vec2& pos() const
        {
            return m_pos;
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

        inline Circle& operator=(const Circle& t_other)
        {
            m_pos = t_other.pos();
            m_radius = t_other.radius();
            
            return *this;
        }

        inline bool operator==(const Circle& t_other) const
        {
            return m_pos == t_other.pos()
                && m_radius == t_other.radius();
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
        virtual ~OutlineCircle() = default;

        virtual void draw() final override;
    
        inline hw::vec2& pos()
        {
            return m_pos;
        }
        inline int& radius()
        {
            return m_radius;
        }
        inline const hw::vec2& pos() const
        {
            return m_pos;
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

        inline OutlineCircle& operator=(const OutlineCircle& t_other)
        {
            m_pos = t_other.pos();
            m_radius = t_other.radius();
            
            return *this;
        }

        inline bool operator==(const OutlineCircle& t_other) const
        {
            return m_pos == t_other.pos()
                && m_radius == t_other.radius();
        }
        inline bool operator!=(const OutlineCircle& t_other) const 
        {
            return !this->operator==(t_other);
        }
     };
}

#endif // !HWAPI_HPP

