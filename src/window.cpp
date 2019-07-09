#include "window.hpp"

///
/// @file window.cpp
///

#include <utility>

hw::window::window(const int t_width, const int t_height, const char* t_name)
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_width(t_width)
    , m_height(t_height)
    , m_event_queue(std::vector<SDL_Event>{})
    , m_color{0, 0, 0, 255}
{
    SDL_Init(SDL_INIT_VIDEO);

    m_window = SDL_CreateWindow(t_name, SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, m_width, m_height,
                                SDL_WINDOW_SHOWN);

    // keep SDL_RENDERER_PRESENTVSYNC so that when somebody decides to
    // change something about a primitive and their computer is
    // beefy it won't seem like nothing is happening(and hopefully less
    // glitches will appear)
    m_renderer = SDL_CreateRenderer(
        m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    m_event_queue.reserve(10);

    if(!m_window) {
        SDL_Log("Could not initialize window %s \n", SDL_GetError());
    }
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
    handle_events();
}

void hw::window::handle_events()
{
    m_event_queue.clear();

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        m_event_queue.push_back(event);
    }
}

void hw::window::set_bgcolor(const std::uint8_t t_r, const std::uint8_t t_g,
                             const std::uint8_t t_b, const std::uint8_t t_a)
{
    m_color = hw::color{t_r, t_g, t_b, t_a};
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
    SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b,
                           m_color.a);
    SDL_RenderClear(m_renderer);
}

bool hw::window::was_key_pressed(int t_key)
{
    for(const auto& event : m_event_queue) {
        switch(event.type) {
        case SDL_KEYDOWN:
            return t_key == event.key.keysym.sym;
        default:
            break;
        }
    }

    return false;
}

bool hw::window::closed()
{
    for(const auto& event : m_event_queue) {
        switch(event.type) {
        case SDL_QUIT:
            return true;
        default:
            break;
        }
    }

    return false;
}
