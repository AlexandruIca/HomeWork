#pragma once
#ifndef VEC2_HPP
#define VEC2_HPP

///
/// @file vec2.hpp
/// This files contains the declaration for the vec2 type.
///

namespace hw {
    ///
    /// @brief Holds two ints describing position in 2D space.
    ///
    struct vec2
    {
        int x{ -1 };
        int y{ -1 };

        constexpr vec2() = default;
        vec2(int t_x, int t_y);
        ~vec2() = default;

        inline bool operator==(const vec2& t_other) const
        { return x == t_other.x && y == t_other.y; }
        inline bool operator!=(const vec2& t_other) const
        { return !this->operator==(t_other); }

        inline vec2 operator+(const vec2& t_other) const
        { return vec2{ x + t_other.x, y + t_other.y }; }
        
        vec2& operator+=(const vec2& t_other)
        {
            x += t_other.x;
            y += t_other.y;

            return *this;
        }

        inline vec2 operator-(const vec2& t_other) const
        { return vec2{ x - t_other.x, y - t_other.y }; }
        
        vec2& operator-=(const vec2& t_other) 
        {
            x -= t_other.x;
            y -= t_other.y;

            return *this;
        }
    };
}

#endif // !VEC2_HPP

