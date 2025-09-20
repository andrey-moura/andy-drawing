#pragma once

#include <string_view>

#include "andy/size.hpp"

namespace andy
{
    namespace drawing
    {
        class dialog
        {
        public:
            dialog(std::string_view title);
            ~dialog();
        protected:
            void* m_data = nullptr; // Implementation-specific data
        public:
            dialog(const dialog&) = delete;
            dialog& operator=(const dialog&) = delete;
        public:
            void show(bool maximized = false);
            andy::size size() const;
        };
    };
};