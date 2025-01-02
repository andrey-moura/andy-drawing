#include <gtk/gtk.h>

#include <uva/drawing.hpp>

#define m_cairo os_specific_data_as<software_renderer_data>().cairo
#define m_should_destroy_cairo os_specific_data_as<software_renderer_data>().should_destroy_cairo

uva::drawing::software_renderer::software_renderer()
{
    software_renderer_data data;
    data.should_destroy_cairo = false;

    os_specific_data_as<software_renderer_data>() = data;
}

uva::drawing::software_renderer::software_renderer(surface& __surface)
{
    // Create the software_renderer
    software_renderer_data data;
    data.cairo = cairo_create(__surface.os_specific_data_as<surface_data>().cairo_surface);
    data.should_destroy_cairo = true;

    os_specific_data_as<software_renderer_data>() = data;
}

uva::drawing::software_renderer::~software_renderer()
{
    if(m_should_destroy_cairo) {
        cairo_destroy(m_cairo);
    }
}

uva::colord cairo_normalize_color(const uva::color& __color)
{
    return __color / 255.0;
}

void cairo_set_source_rgba(cairo_t* cr, const uva::color& __color)
{
    uva::colord normalized = cairo_normalize_color(__color);
    cairo_set_source_rgba(cr, normalized.r, normalized.g, normalized.b, normalized.a);
}

void cairo_rectangle(cairo_t* cr, const uva::rect& __rect)
{
    cairo_rectangle(cr, __rect.x, __rect.y, __rect.w, __rect.h);
}

void uva::drawing::software_renderer::fill_rect(const uva::rect& __rect, const uva::color& __color)
{
    cairo_set_source_rgba(m_cairo, __color);
    cairo_rectangle(m_cairo, __rect);
    cairo_fill(m_cairo);
}

void uva::drawing::software_renderer::clear(const uva::color& __color)
{
    cairo_set_source_rgba(m_cairo, __color);
    cairo_paint(m_cairo);
}

uva::size uva::drawing::software_renderer::text_extent(std::string_view __text, size_t font_size) const
{
    cairo_text_extents_t extents;
    cairo_set_font_size(m_cairo, font_size);
    cairo_text_extents(m_cairo, __text.data(), &extents);

    uva::size extents_size = { (int)extents.width, (int)extents.height };

    return extents_size;
}

void uva::drawing::software_renderer::draw_text(std::string_view __text, const uva::point& __point, size_t font_size, const uva::color& __color) const
{
    cairo_set_source_rgba(m_cairo, __color);
    cairo_set_font_size(m_cairo, font_size);

    cairo_text_extents_t extents;
    cairo_text_extents(m_cairo, __text.data(), &extents);

    cairo_move_to(m_cairo, __point.x, __point.y - extents.y_bearing);
    cairo_show_text(m_cairo, __text.data());
}