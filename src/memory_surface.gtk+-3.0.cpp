#include <uva/drawing.hpp>

#include "gtk3+-3.0.hpp"

uva::drawing::memory_surface::memory_surface(const uva::size& s)
    : surface(s)
{
    // Create the surface
    surface_data data;
    data.cairo_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, s.w, s.h);

    os_specific_data_as<surface_data>() = data;
}

uva::drawing::memory_surface::~memory_surface()
{
    const surface_data& data = os_specific_data_as<surface_data>();
    cairo_surface_destroy(data.cairo_surface);
}

bool uva::drawing::memory_surface::write_to_file(std::filesystem::path &path, std::string_view stem)
{
    cairo_surface_t* surface = os_specific_data_as<surface_data>().cairo_surface;

    std::string filename = std::string(path) + "/" + std::string(stem) + ".png";

    cairo_surface_write_to_png(surface, filename.c_str());

    return true;
}

uva::drawing::window_surface uva::drawing::window::create_surface()
{
    
}