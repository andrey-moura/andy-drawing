#pragma once

#include <gtk/gtk.h>

#include <uva/drawing.hpp>

struct software_renderer_data {
    cairo_t* cairo = nullptr;
    bool should_destroy_cairo = false;
};

struct surface_data {
    cairo_surface_t* cairo_surface = nullptr;
};