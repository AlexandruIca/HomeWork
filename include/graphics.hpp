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
/// @section sec_usage Usage of this API
/// I've created this to help my teacher at school show students some
/// interesting stuff you can make with c++, not only boring console
/// programs. Untill now he had to install windows XP and get borland c++
/// compiler using "graphics.h" to be able to draw very simple stuff in the
/// console. It worked but it was not ideal at all. What if somebody wants to
/// practice at home?
/// This aims to be a replacement for that by using cross platform libraries
/// like SDL2. In theory I would setup codeblocks on the computers at my
/// school to have a user template that automatically creates a project
/// which links to this library and provide a very simple program to start
/// with so students don't have to get confused. I really hope this will
/// prove useful.
///
/// @section sec_starting Starting out
/// The best place to start out using this is to check out the git repo in
/// docs/README.md. To include it in you project it's probably easy enough
/// to just check the CMakeLists.txt and see how it's built. I didn't put too
/// much soul into making the build process easy because I am the one who should
/// build it and then it should just work with a codeblocks template, like I am
/// planning to do.
///
/// @section sec_overview Overview
/// The header that you should include every time you want to use thi is
/// graphics.hpp. It only contains a few convenient functions and a macro
/// to make the library dead easy to use. One of the main goals of this library
/// is to be incredibly accessible to anyone.
/// The header hwapi.hpp contains the actual api and you should check this out
/// whenever you want to see if a feature is available.
/// The window.hpp header is just a wrapper around SDL_Window.
/// The rest is not really that important but if you need more detail you could
/// probably just check out the sources. It's a very small library and I think
/// it's very easy to just read what happens under the hood.
///
/// @section sec_why_cpp Why C++
/// The turtle module in python is probably the easisest way to get started with
/// graphics programming but sadly python is not taught in my school. We only
/// learn c++(mostly the antique C-ish c++) and getting anything working
/// properly on our computers is an absolute pain. I've already got some demos
/// of this library working so this is the main reason why I chose c++. Luckily
/// the codeblocks version(the editor that everyone uses at my school) is 13.12
/// which includes a mingw version that supports c++11, making development
/// so much smoother.
/// I could have also just chosen plain C since we don't learn anything special
/// about c++(except IO) but it doesn't provide some neat features like
/// function overloading that make this much easier to use. As ease of use
/// is one major goal of the library the choice is c++.
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

