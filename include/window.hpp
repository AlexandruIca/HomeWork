///
/// @file
///

#pragma once
#ifndef WINDOW_HPP 
#define WINDOW_HPP 

#include <vector>

#include "SDL2/SDL.h"
//struct SDL_Window;
//struct SDL_Renderer;
//struct SDL_Event;

#include "color.hpp" 

///
/// @brief Almost all functionality is provided in @ref hw namespace.
///
namespace hw {   
    ///
    /// @brief Window object that can (obviously) create a window, 
	///        set the clear color,
    ///        update it and get what key was pressed.
    ///
    class window
    {
    private:
        SDL_Window* m_window{ nullptr };
        SDL_Renderer* m_renderer{ nullptr };
        
        int m_width{ -1 };
        int m_height{ -1 };

        //const Uint8* m_events{ nullptr };
        std::vector<SDL_Event> m_event_queue{}; 

        hw::color m_color{ 0, 0, 0, 155 };

    public:
        window() = default;
        ///
        /// @brief Constructs the window with given dimensions and title.
        ///
        /// @param[in] t_name is the title of the window.
        ///
        window(const int t_width, const int t_height, const char* t_name);
        ~window();

        //using event_t = SDL_Event;

        inline int get_width() const
        {
            return m_width;
        }
        inline int get_height() const
        {
            return m_height;
        }
        
        ///
        /// @brief Returns the underlying renderer(used by SDL).
        ///
        inline SDL_Renderer* get_renderer()
        {
            return m_renderer;
        }
        ///
        /// @brief Returns the underlying window(used by SDL).
        ///
        inline SDL_Window* get()
        {
            return m_window;
        }

        ///
        /// @brief Renders everything on the screen.
        ///
        void update();
        void handle_events();
        void set_bgcolor(const std::uint8_t t_r, const std::uint8_t t_g,
                const std::uint8_t t_b, const std::uint8_t t_a = 255);
        void set_bgcolor(const hw::color& t_color);
        void set_bgcolor(hw::color&& t_color);
        void clear();

        bool was_key_pressed(int t_key);
        bool closed(/*event_t& t_event*/);
    };
}

#endif // !WINDOW_HPP

