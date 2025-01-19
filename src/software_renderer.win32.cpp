#include <uva/drawing/win32.hpp>
#include <uva/drawing.hpp>

#define m_dc os_specific_data_as<software_renderer_data>().dc

namespace uva
{
    namespace drawing
    {
        software_renderer::software_renderer()
        {
            
        }
        software_renderer::software_renderer(surface& __surface)
        {
            m_dc = CreateCompatibleDC(nullptr);

            if (m_dc == nullptr)
            {
                throw std::runtime_error("Failed to create compatible dc");
            }

            if(memory_surface* ms = dynamic_cast<memory_surface*>(&__surface))
            {
                SelectObject(m_dc, ms->os_specific_data_as<memory_surface_data>().bitmap);
            }
            else
            {
                throw std::runtime_error("Surface is not a memory surface");
            }
        }

        software_renderer::~software_renderer()
        {
        }

        void software_renderer::fill_rect(const uva::rect& __rect, const uva::color& __color)
        {
            RECT wrect;
            wrect.top = __rect.y;
            wrect.left = __rect.x;
            wrect.bottom = __rect.y + __rect.h;
            wrect.right = __rect.x + __rect.w;

            HBRUSH brush = CreateSolidBrush(RGB(__color.r, __color.g, __color.b));

            FillRect(m_dc, &wrect, brush);

            DeleteObject(brush);
        }

        void software_renderer::clear(const uva::color& __color)
        {
            throw std::runtime_error("The method or operation is not implemented.");
        }

        uva::size software_renderer::text_extent(std::string_view __text, size_t font_size) const
        {
            throw std::runtime_error("The method or operation is not implemented.");      
        }

        void software_renderer::draw_text(std::string_view __text, const uva::point& __point, size_t font_size, const uva::color& __color) const
        {
            throw std::runtime_error("The method or operation is not implemented.");
        }
    };
};