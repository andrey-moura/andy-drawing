#include "andy/drawing/dialog.hpp"

#include <gtk/gtk.h>

#define m_dialog (GtkDialog*)m_data

namespace andy
{
    namespace drawing
    {
        dialog::dialog(std::string_view title)
        {
            // Create the dialog using GTK
            m_data = gtk_dialog_new();
            gtk_window_set_title(GTK_WINDOW(m_data), title.data());
            gtk_window_set_default_size(GTK_WINDOW(m_data), 400, 300);
        }
        void dialog::show(bool maximized)
        {
            // Show the dialog
            gtk_dialog_run(m_dialog);
            if (maximized) {
                gtk_window_maximize(GTK_WINDOW(m_data));
            }
        }
        andy::size dialog::size() const
        {
            int width, height;
            gtk_window_get_size(GTK_WINDOW(m_data), &width, &height);
            return andy::size(width, height);
        }
        dialog::~dialog()
        {
            // Destroy the dialog
            gtk_widget_destroy(GTK_WIDGET(m_data));
            m_data = nullptr; // Avoid dangling pointer
        }
    };
};