#pragma once
#ifndef DRAWING_API_HPP
#define DRAWING_API_HPP

///
/// @file drawing_api.hpp
///

///
/// @defgroup internal_drawing_api_group Internal drawing API
///
/// These functions implement drawing simple primitives to an SDL_Renderer.
/// They do nothing else other than calling the according SDL_RenderDraw
/// function. They do not add any shapes to the global vector.
///

#include "SDL2/SDL.h"

#include "color.hpp"
#include "vec2.hpp"

namespace hw {
    ///
    /// @ingroup internal_drawing_api_group
    ///
    void draw_point(SDL_Renderer* t_renderer, hw::vec2 const& t_pos,
                    hw::color const& t_color);
    ///
    /// @ingroup internal_drawing_api_group
    ///
    void draw_line(SDL_Renderer* t_renderer, hw::vec2 const& t_start,
                   hw::vec2 const& t_end, hw::color const& t_color);
    ///
    /// @ingroup internal_drawing_api_group
    ///
    void draw_triangle(SDL_Renderer* t_renderer, hw::vec2 const& t_first,
                       hw::vec2 const& t_second, hw::vec2 const& t_third,
                       hw::color const& t_color);
    ///
    /// @ingroup internal_drawing_api_group
    ///
    void draw_outline_triangle(SDL_Renderer* t_renderer,
                               hw::vec2 const& t_first,
                               hw::vec2 const& t_second,
                               hw::vec2 const& t_third,
                               hw::color const& t_color);
    ///
    /// @ingroup internal_drawing_api_group
    ///
    void draw_rectangle(SDL_Renderer* t_renderer, hw::vec2 const& t_pos,
                        int const t_width, int const t_height,
                        hw::color const& t_color);
    ///
    /// @ingroup internal_drawing_api_group
    ///
    void draw_outline_rectangle(SDL_Renderer* t_renderer, hw::vec2 const& t_pos,
                                int const t_width, int const t_height,
                                hw::color const& t_color);
    ///
    /// @ingroup internal_drawing_api_group
    ///
    void draw_circle(SDL_Renderer* t_renderer, hw::vec2 const& t_pos,
                     int const t_radius, hw::color const& t_color);
    ///
    /// @ingroup internal_drawing_api_group
    ///
    void draw_outline_circle(SDL_Renderer* t_renderer, hw::vec2 const& t_pos,
                             int const t_radius, hw::color const& t_color);
} // namespace hw

#endif
