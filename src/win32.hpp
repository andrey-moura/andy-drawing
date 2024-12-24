#pragma once

#include <Windows.h>

#include <uva/drawing.hpp>

struct memory_surface_data
{
    HBITMAP bitmap;
};

struct software_renderer_data
{
    HDC dc;
    uva::drawing::surface* surface;
};
