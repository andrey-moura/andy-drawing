#pragma once

#include <filesystem>

#include <andy/size.hpp>
#include <andy/rect.hpp>
#include <andy/color.hpp>

namespace andy
{
    namespace drawing
    {
        class image
        {
        public:
            image(andy::size size);
            ~image();
        protected:
            andy::size m_size;
            andy::color* m_pixels;
            // Accessors
        public:
            const andy::size& size() const;
            const andy::color* pixels() const { return m_pixels; }
            andy::color* pixels() { return m_pixels; }
        public:
            void fill(const andy::color& color, const andy::rect& rect);
        public:
            bool operator==(const image& other) const;
        public:
            void save_bitmap(const std::filesystem::path& path);
        public:
            static image load_bitmap(const std::filesystem::path& path);
        };
    };
};