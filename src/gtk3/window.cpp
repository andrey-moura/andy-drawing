#include "andy/drawing/window.hpp"

#include <gtk/gtk.h>

namespace andy
{
    namespace drawing
    {
        window::window(std::string_view title)
        {
            // Create the window using GTK
            m_data = gtk_window_new(GTK_WINDOW_TOPLEVEL);

        }
        window::~window()
        {
            
        }
    };
};