#include "andy/drawing/window.hpp"

#include <iostream>

#include "andy/drawing/gtk3/window.hpp"

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    andy::drawing::window* window = (andy::drawing::window*)user_data;
    andy::drawing::gtk3::window* priv = (andy::drawing::gtk3::window*)window->m_data;
    priv->cairo = cr;
    window->draw();
    priv->cairo = nullptr;
    return TRUE;
}

namespace andy
{
    namespace drawing
    {
        window::window(std::string_view title)
        {
            // Create the window using GTK
            m_data = new andy::drawing::gtk3::window();
            m_widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            m_window = (GtkWindow*)m_widget;

            m_drawing_area = gtk_drawing_area_new();
            gtk_container_add(GTK_CONTAINER(m_window), m_drawing_area);

            gtk_window_set_default_size(m_window, 800, 600);
            gtk_window_set_title(m_window, title.data());

            g_signal_connect(
                G_OBJECT(m_drawing_area),
                "draw",
                G_CALLBACK(on_draw_event),
                this
            );
        }
        void window::show(bool maximized)
        {
            // Show the window
            gtk_widget_show_all(GTK_WIDGET(m_window));
            if (maximized) {
                gtk_window_maximize(m_window);
            }
        }
        andy::size window::size() const
        {
            int width, height;
            gtk_window_get_size(m_window, &width, &height);
            return andy::size(width, height);
        }
        window::~window()
        {
            // Destroy the window
            gtk_widget_destroy(m_widget);
            m_window = nullptr; // Avoid dangling pointer
            m_widget = nullptr;
            m_cairo = nullptr;
            delete (andy::drawing::gtk3::window*)m_data;
            m_data = nullptr;
        }
    };
};