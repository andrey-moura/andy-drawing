#pragma once

#include <gtk/gtk.h>

namespace andy
{
    namespace drawing
    {
        namespace gtk3
        {
            struct window
            {
                GtkWindow *gtk_window = nullptr;
                GtkWidget *gtk_widget = nullptr;
                cairo_t *cairo = nullptr;
                GtkWidget* drawing_area = nullptr;
            };
        };
    };
}

#define m_window ((andy::drawing::gtk3::window*)m_data)->gtk_window
#define m_widget ((andy::drawing::gtk3::window*)m_data)->gtk_widget
#define m_cairo ((andy::drawing::gtk3::window*)m_data)->cairo
#define m_drawing_area ((andy::drawing::gtk3::window*)m_data)->drawing_area