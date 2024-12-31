#include "win32.hpp"

#include <uva/drawing.hpp>

#define m_dc os_specific_data_as<software_renderer_data>().dc
#define m_surface os_specific_data_as<software_renderer_data>().surface

uva::drawing::software_renderer::software_renderer(surface& __surface)
    : basic_renderer(__surface)
{
    m_dc = CreateCompatibleDC(nullptr);

    if (m_dc == nullptr)
    {
        throw std::runtime_error("Failed to create compatible dc");
    }

    if(memory_surface* ms = dynamic_cast<memory_surface*>(&__surface))
    {
        SelectObject(m_dc, ms->os_specific_data_as<memory_surface_data>().bitmap);
    }
    else
    {
        throw std::runtime_error("Surface is not a memory surface");
    }

    m_surface = &__surface;
}

uva::drawing::software_renderer::~software_renderer()
{
}

void uva::drawing::software_renderer::fill_rect(const uva::rect& __rect, const uva::color& __color)
{
    RECT wrect;
    wrect.top = __rect.y;
    wrect.left = __rect.x;
    wrect.bottom = __rect.y + __rect.h;
    wrect.right = __rect.x + __rect.w;

    HBRUSH brush = CreateSolidBrush(RGB(__color.r, __color.g, __color.b));

    FillRect(m_dc, &wrect, brush);

    DeleteObject(brush);
}

void uva::drawing::software_renderer::clear(const uva::color& __color)
{
    fill_rect(uva::rect(0, 0, m_surface->width(), m_surface->height()), __color);
}