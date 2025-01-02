#pragma once

#include <string>
#include <string_view>
#include <filesystem>

#include <uva/drawing/image.hpp>
#include <uva/drawing/gtk3+-3.0.hpp>

#include <uva/size.hpp>
#include <uva/color.hpp>
#include <uva/rect.hpp>
#include <uva/os_specific_data_member.hpp>

namespace uva
{
    //temp
    namespace drawing
    {
        class window_surface;
        class window : private os_specific_data_member<8>
        {
        public:
            /// @brief Create a new window with the specified title and the OS's default size and position.
            /// @param __title The title of the window.
            window(std::string_view __title);
        public:
            /// @brief Show the window.
            /// @param maximized Whether the window should be maximized.
            void show(bool maximized = false);
            /// @brief Hide the window.
            void hide();
        public:
            window_surface create_surface();
        };
        class surface : public os_specific_data_member<8>
        {
        public:
            surface() = default;
            surface(const uva::size& s)
                : m_size(s)
            {
            }
        // Protected members
        protected:
            uva::size m_size;
        // Acessors
        public:
            /// @brief Get the size of the surface.
            const uva::size& size() const { return m_size; }
            /// @brief Get the width of the surface.
            size_t width() const { return m_size.w; }
            /// @brief Get the height of the surface.
            size_t height() const { return m_size.h; }
        public:
            /// @brief Write the surface to a file. The format is os specific.
            /// @param path The path to write the file to. The path must be a directory. It will be updated with the file name and extension.
            /// @param stem The stem of the file.
            virtual bool write_to_file(std::filesystem::path& path, std::string_view stem) { return false; }

            /// @brief Convert the surface to an image.
            virtual uva::drawing::image to_image() { return uva::drawing::image(m_size); }
        };
        class window_surface : public surface
        {
        public:
            window_surface(size_t native_window);
        };
        class memory_surface : public surface
        {
        public:
            memory_surface(const uva::size& s);
            ~memory_surface();
        public:
            /// @brief Write the surface to a file. The format is os specific.
            /// @param path The path to write the file to. The path must be a directory. It will be updated with the file name and extension.
            /// @param stem The stem of the file.
            virtual bool write_to_file(std::filesystem::path& path, std::string_view stem) override;

            /// @brief Convert the surface to an image.
            virtual uva::drawing::image to_image() override;
        };
        class texture_surface : public surface
        {
        public:
            texture_surface(const uva::size& s);
            ~texture_surface();
        };
        class basic_renderer : public os_specific_data_member<256>
        {
        public:
            basic_renderer() = default;
            ~basic_renderer() = default;
        public:
            virtual void fill_rect(const uva::rect& __rect, const uva::color& __color) { }
            virtual void clear(const uva::color& __color) { }
            virtual uva::size text_extent(std::string_view __text, size_t font_size) const { return uva::size(0, 0); }
            virtual void draw_text(std::string_view __text, const uva::point& __rect, size_t font_size, const uva::color& __color) const { }
        };
        class software_renderer : public basic_renderer
        {
        public:
            software_renderer();
            software_renderer(surface& __surface);
            ~software_renderer();
        public:
            void fill_rect(const uva::rect& __rect, const uva::color& __color) override;
            void clear(const uva::color& __color) override;
            virtual uva::size text_extent(std::string_view __text, size_t font_size) const override;
            virtual void draw_text(std::string_view __text, const uva::point& __point, size_t font_size, const uva::color& __color) const override;
        };
        class hardware_renderer : public basic_renderer
        {
        public:
            hardware_renderer(surface& __surface);
            ~hardware_renderer();
        public:
            void fill_rect(const uva::rect& __rect, const uva::color& __color) override;
            void clear(const uva::color& __color) override;
        };
    };
};