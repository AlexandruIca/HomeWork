#include "color.hpp"

///
/// @file color.cpp
///

hw::color::color(const std::uint8_t t_r, const std::uint8_t t_g,
                 const std::uint8_t t_b, const std::uint8_t t_a)
    : r(t_r)
    , g(t_g)
    , b(t_b)
    , a(t_a)
{
}
