#pragma once
#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "hwapi.hpp"
#include "keys.hpp"

using namespace dummy_api;

const hw::color RED    = hw::color{ 255, 0, 0 };
const hw::color GREEN  = hw::color{ 0, 255, 0 };
const hw::color BLUE   = hw::color{ 0, 0, 255 };
const hw::color WHITE  = hw::color{ 255, 255, 255 };
const hw::color BLACK  = hw::color{ 0, 0, 0 };
const hw::color CYAN   = hw::color{ 0, 188, 212 };
const hw::color YELLOW = hw::color{ 255, 235, 59 };
const hw::color LIME   = hw::color{ 205, 220, 57 };
const hw::color TEAL   = hw::color{ 0, 150, 136 };
const hw::color PURPLE = hw::color{ 156, 39, 176 };
const hw::color PINK   = hw::color{ 236, 64, 122 };
const hw::color INDIGO = hw::color{ 63, 81, 181 };
const hw::color AMBER  = hw::color{ 255, 193, 7 };
const hw::color ORANGE = hw::color{ 255, 152, 0 };
const hw::color BROWN  = hw::color{ 121, 85, 72 };
const hw::color GREY   = hw::color{ 158, 158, 158 };

inline void set_width(const int t_width)
{ set_global_width(t_width); }

inline void set_height(const int t_height)
{ set_global_width(t_height); }

#endif // !GRAPHICS_HPP

