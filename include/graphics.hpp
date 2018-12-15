#pragma once
#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

///
/// @file 
/// This file just makes it easier to interact with the library.
/// Anyone that uses this library should only need to include this
/// header.
///

///
/// @mainpage HomeWork - an API that makes it easy to draw shapes in c++
/// Please read the README.md file in the github repository for a quick
/// introduction to the library: https://github.com/AlexandruIca/HomeWork/blob/master/README.md
///

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

/// 
/// @brief Helper to change window width.
/// 
/// A wrapper for @ref dummy_api::set_global_width.
/// 
inline void set_width(const int t_width)
{ set_global_width(t_width); }

/// 
/// @brief Helper to change window height.
/// 
/// A wrapper for @ref dummy_api::set_global_height.
/// 
inline void set_height(const int t_height)
{ set_global_height(t_height); }

///
/// @brief Returns the width of the global window.
///
/// A wrapper for @ref dummy_api::get_global_width().
///
inline int width()
{ return get_global_width(); }

///
/// @brief Returns the height of the global window.
///
/// A wrapper for @ref dummy_api::get_global_height().
///
inline int height()
{ return get_global_height(); }

///
/// @brief Runs code inside main loop.
/// 
/// If you want to modify the color of an object of type triangle let's say,
/// then you can use this macro:
/// @code{.cpp}
/// #include "graphics.hpp"
///
/// int main() 
/// { 
///     Triangle t{ 20, 20, 400, 400, 150, 100, RED };
///
///     return draw(WITH{
///         ++(t.color().g);
///         t.color().g = t.color().g % 255;
///     });
/// }
/// @endcode
/// which is here only to help you. You can just pass a lambda that takes a 
/// paramater of type double which is the elapsed time since last frame.
///
#define WITH(...) [&](const double elapsed_time) 

// can't make it work on windows with mingw otherwise
#if (defined(_WIN32) || defined(__WIN32) || defined(WIN32) && !defined(__CYGWIN__)) && defined(main)
#undef main
#endif

#endif // !GRAPHICS_HPP

