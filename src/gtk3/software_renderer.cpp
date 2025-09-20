#include "andy/drawing/software_renderer.hpp"
#include "andy/drawing/window.hpp"
#include "andy/drawing/gtk3/window.hpp"

namespace andy
{
    namespace drawing
    {
        software_renderer::software_renderer(window* window)
            : basic_renderer()
        {
            m_data = window->m_data;
            if(!m_cairo) {
                throw std::runtime_error("Software renderer initialized outside of draw event");
            }
        }

        software_renderer::~software_renderer()
        {
            // No resources to free
        }

        andy::size software_renderer::client_size() const
        {
            // Retrieve from drawing window
            int width = gtk_widget_get_allocated_width(m_drawing_area);
            int height = gtk_widget_get_allocated_height(m_drawing_area);

            return andy::size(width, height);
        }

        void software_renderer::draw_text(
                std::string_view text,
                andy::point position,
                std::string_view font_family,
                size_t font_size,
                bool bold,
                bool italic
        ) const
        {
            if(!m_cairo) {
                throw std::runtime_error("draw_text called outside of draw event");
            }

            cairo_select_font_face(
                m_cairo,
                font_family.data(),
                italic ? CAIRO_FONT_SLANT_NORMAL : CAIRO_FONT_SLANT_NORMAL,
                bold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL
            );

            cairo_set_font_size(m_cairo, font_size);

            cairo_move_to(m_cairo, position.x, position.y + font_size); // Adjust y for baseline
            cairo_set_source_rgba(m_cairo, 0, 0, 0, 1); // Black color
            cairo_show_text(m_cairo, text.data());
            cairo_stroke(m_cairo);
        }

        andy::size software_renderer::text_extent(
                std::string_view text,
                std::string_view font_family,
                size_t font_size,
                bool bold,
                bool italic
        ) const
        {
            if(!m_cairo) {
                throw std::runtime_error("text_extent called outside of draw event");
            }

            cairo_select_font_face(
                m_cairo,
                font_family.data(),
                italic ? CAIRO_FONT_SLANT_NORMAL : CAIRO_FONT_SLANT_NORMAL,
                bold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL
            );

            cairo_set_font_size(m_cairo, font_size);

            cairo_text_extents_t extents;
            cairo_text_extents(m_cairo, text.data(), &extents);

            return andy::size((int)extents.width, (int)extents.height);
        }
    }
};