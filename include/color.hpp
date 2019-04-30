#pragma once
#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

///
/// @file color.hpp
/// This file contains the declaration for a color object.
///

namespace hw {
    ///
    /// @brief Describes a @ref color object.
    ///
    struct color
    {
        std::uint8_t r{255};
        std::uint8_t g{255};
        std::uint8_t b{255};
        std::uint8_t a{255};

        constexpr color() = default;
        color(const color&) = default;
        color(color&&) = default;
        color(const std::uint8_t t_r, const std::uint8_t t_g,
              const std::uint8_t t_b, const std::uint8_t t_a = 255);
        ~color() = default;

        color& operator=(const color&) = default;
        color& operator=(color&&) = default;

        inline bool operator==(const color& t_other) const
        {
            return r == t_other.r && g == t_other.g && b == t_other.b &&
                   a == t_other.a;
        }
        inline bool operator!=(const color& t_other) const
        {
            return !this->operator==(t_other);
        }
    };
} // namespace hw

#endif // !COLOR_HPP
