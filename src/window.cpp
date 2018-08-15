#include "window.hpp"

#include <utility>

hw::window::window(const int t_width, const int t_height, const char* t_name)
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_width(t_width)
    , m_height(t_height)
    , m_events(nullptr)
    , m_color{ 0, 0, 0, 255 }
{
    m_window = SDL_CreateWindow(t_name, 
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            m_width, m_height,
            SDL_WINDOW_RESIZABLE);

    m_renderer = SDL_CreateRenderer(m_window, -1, 
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!m_window) {
        SDL_Log("Could not initialize window %s \n", SDL_GetError());
    }

    SDL_PumpEvents();
    m_events = SDL_GetKeyboardState(nullptr);
}

hw::window::~window()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    SDL_Quit();
}

void hw::window::update()
{
    SDL_RenderPresent(m_renderer);

    m_events = SDL_GetKeyboardState(nullptr);
}

void hw::window::set_bgcolor(const std::uint8_t t_r, const std::uint8_t t_g,
        const std::uint8_t t_b, const std::uint8_t t_a)
{
    m_color = hw::color{ t_r, t_g, t_b, t_a };
}

void hw::window::set_bgcolor(const hw::color& t_color)
{
    m_color = t_color;
}

void hw::window::set_bgcolor(hw::color&& t_color)
{
    m_color = std::move(t_color);
}

void hw::window::clear()
{
    SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderClear(m_renderer);

    SDL_PumpEvents();
}

bool hw::window::was_key_pressed(int t_key)
{
    return m_events[t_key];
}

bool hw::window::closed(hw::window::event_t& t_event)
{
    while(SDL_PollEvent(&t_event)) {
        if(t_event.type == SDL_QUIT) {
            return true;
        }
    }

    return false;
}

