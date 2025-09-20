#pragma once

#include "basic_renderer.hpp"

#include <string_view>

#include "andy/point.hpp"

namespace andy
{
    namespace drawing
    {
        class window;
        class software_renderer : public basic_renderer
        {
        public:
            software_renderer(window* window);
            ~software_renderer();
        private:
            void* m_data = nullptr; // Implementation-specific data
        public:
            virtual andy::size client_size() const override;
            virtual andy::size text_extent(
                std::string_view text,
                std::string_view font_family,
                size_t font_size,
                bool bold = false,
                bool italic = false
            ) const override;
            virtual void draw_text(
                std::string_view text,
                andy::point position,
                std::string_view font_family,
                size_t font_size,
                bool bold = false,
                bool italic = false
            ) const override;
        };
    };
};