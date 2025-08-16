#include "andy/drawing/window.hpp"

#include <gtk/gtk.h>

#define m_window (GtkWindow*)m_data

namespace andy
{
    namespace drawing
    {
        window::window(std::string_view title)
        {
            // Create the window using GTK
            m_data = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            gtk_window_set_default_size(GTK_WINDOW(m_data), 800, 600);
            gtk_window_set_title(GTK_WINDOW(m_data), title.data());
        }
        void window::show(bool maximized)
        {
            // Show the window
            gtk_widget_show_all(GTK_WIDGET(m_data));
            if (maximized) {
                gtk_window_maximize(GTK_WINDOW(m_data));
            }
        }
        andy::size window::size() const
        {
            int width, height;
            gtk_window_get_size(GTK_WINDOW(m_data), &width, &height);
            return andy::size(width, height);
        }
        window::~window()
        {
            // Destroy the window
            gtk_widget_destroy(GTK_WIDGET(m_data));
            m_data = nullptr; // Avoid dangling pointer
        }
    };
};