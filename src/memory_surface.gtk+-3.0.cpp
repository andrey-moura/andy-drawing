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

uva::drawing::image uva::drawing::memory_surface::to_image()
{
    const surface_data& data = os_specific_data_as<surface_data>();

    cairo_surface_t* surface = data.cairo_surface;

    cairo_surface_flush(surface);

    cairo_format_t format = cairo_image_surface_get_format(surface);

    if(format != CAIRO_FORMAT_ARGB32)
    {
        throw std::runtime_error("Unsupported format");
    }

    int stride = cairo_image_surface_get_stride(surface);

    uva::size size(cairo_image_surface_get_width(surface), cairo_image_surface_get_height(surface));

    if (stride != size.w * 4) {
        throw std::runtime_error("Unsupported stride");
    }

    uva::drawing::image img(size);

    uva::color* pixels = img.pixels();

    unsigned char* surface_data = cairo_image_surface_get_data(surface);

    for (int y = 0; y < size.h; ++y) {
        for (int x = 0; x < size.w; ++x) {
            int i = y * stride + x * 4;
            pixels[y * size.w + x] = uva::color(
                surface_data[i + 2], // Red
                surface_data[i + 1], // Green
                surface_data[i + 0], // Blue
                surface_data[i + 3]  // Alpha
            );
        }
    }

    return img;
}

uva::drawing::window_surface uva::drawing::window::create_surface()
{
    
}