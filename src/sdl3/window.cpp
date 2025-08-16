#include "andy/drawing/window.hpp"

#include <stdexcept>

#include <SDL3/SDL.h>

#define m_window (SDL_Window*)m_data

namespace andy
{
    namespace drawing
    {
        window::window(std::string_view title)
        {
            m_data = SDL_CreateWindow(title.data(), 600, 400, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
            if(!m_window) {
                throw std::runtime_error("Failed to create window.");
            }
        }

        void window::show(bool maximized)
        {
            if(maximized) {
                SDL_MaximizeWindow(m_window);
            }
            SDL_ShowWindow(m_window);
        }

        andy::size window::size() const
        {
            int w, h;
            SDL_GetWindowSize(m_window, &w, &h);
            return { w, h };
        }
    }
}