#pragma once

#include "andy/size.hpp"
#include "andy/point.hpp"

#include <cstddef>
#include <string_view>

namespace andy
{
    namespace drawing
    {
        class basic_renderer
        {
        public:
            basic_renderer();
            ~basic_renderer();
        public:
            virtual andy::size client_size() const;
            virtual andy::size text_extent(
                const std::string_view text,
                const std::string_view font_family,
                size_t font_size,
                bool bold = false,
                bool italic = false
            ) const { return andy::size(0, 0); };
            virtual void draw_text(
                const std::string_view text,
                andy::point position,
                const std::string_view font_family,
                size_t font_size,
                bool bold = false,
                bool italic = false
            ) const {  };
        };
    };
}