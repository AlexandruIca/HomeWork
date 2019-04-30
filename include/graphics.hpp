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
/// introduction to the library, this is the API reference:
/// https://github.com/AlexandruIca/HomeWork/blob/master/README.md
///

#include "hwapi.hpp"
#include "keys.hpp"

// evil but necessary(easy to use)
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
/// @brief Checks if @ref t_key was pressed.
///
bool key(int const t_key)
{ return get_global_window()->was_key_pressed(t_key); }

///
/// @brief Verifica data @ref t_tasta a fost apasata.
///
inline bool tasta(int const t_tasta)
{ return key(t_tasta); }

///
/// @brief Changes the background color of global window.
///
void set_background(hw::color const& t_color)
{ get_global_window()->set_bgcolor(t_color); }

///
/// @brief Changes the background color of global window.
///
/// @attention NEVER use this before the @ref hw::draw call.
///
void set_background(
        unsigned char const t_r,
        unsigned char const t_g,
        unsigned char const t_b,
        unsigned char const t_a
    )
{ get_global_window()->set_bgcolor(hw::color{ t_r, t_g, t_b, t_a }); }

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
#define WITH [&](const double elapsed_time)

// can't make it work on windows with mingw otherwise
#if (defined(_WIN32) || defined(__WIN32) || defined(WIN32) && !defined(__CYGWIN__)) && defined(main)
#undef main
#endif

#endif // !GRAPHICS_HPP

