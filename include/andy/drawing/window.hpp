#pragma once

#include <string_view>

#include "andy/size.hpp"

namespace andy
{
    namespace drawing
    {
        class window
        {
        public:
            window(std::string_view title);
            ~window();
        public:
            void show(bool maximized = false);
            andy::size size() const;
        protected:
            void* m_data = nullptr; // Implementation-specific data
        };
    };
};