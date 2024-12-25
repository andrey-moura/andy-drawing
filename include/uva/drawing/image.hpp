#pragma once

#include <filesystem>

#include <uva/size.hpp>
#include <uva/rect.hpp>
#include <uva/color.hpp>

namespace uva
{
    namespace drawing
    {
        class image
        {
        public:
            image(uva::size size);
            ~image();
        protected:
            uva::size m_size;
            uva::color* m_pixels;
            // Accessors
        public:
            const uva::size& size() const;
            const uva::color* pixels() const { return m_pixels; }
            uva::color* pixels() { return m_pixels; }
        public:
            void fill(const uva::color& color, const uva::rect& rect);
        public:
            bool operator==(const image& other) const;
        public:
            void save_bitmap(const std::filesystem::path& path);
        public:
            static image load_bitmap(const std::filesystem::path& path);
        };
    };
};