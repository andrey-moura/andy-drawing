#include <uva/drawing/image.hpp>

#include <string.h>

#include <fstream>

namespace uva
{
    namespace drawing
    {
        image::image(uva::size __size)
            : m_size(__size), m_pixels(new uva::color[__size.w * __size.h])
        {
        }

        image::~image()
        {
            delete[] m_pixels;
        }

        const uva::size& image::size() const
        {
            return m_size;
        }

        void image::fill(const uva::color& color, const uva::rect& rect)
        {
            for(int y = rect.y; y < rect.y + rect.h; y++)
            {
                for(int x = rect.x; x < rect.x + rect.w; x++)
                {
                    m_pixels[y * m_size.w + x] = color;
                }
            }
        }

        bool image::operator==(const image& other) const
        {
            if(m_size != other.m_size)
            {
                return false;
            }

            return memcmp(m_pixels, other.m_pixels, m_size.w * m_size.h * sizeof(uva::color)) == 0;
        }

        void image::save_bitmap(const std::filesystem::path& path)
        {
            std::ofstream stream(path, std::ios::binary);

            if(!stream.is_open())
            {
                throw std::runtime_error("Failed to open file");
            }

            uint32_t file_size = 54 + m_size.w * m_size.h * 4;

            stream.write("BM", 2);
            stream.write(reinterpret_cast<char*>(&file_size), sizeof(file_size));

            uint32_t reserved = 0;

            stream.write(reinterpret_cast<char*>(&reserved), sizeof(reserved));

            uint32_t pixel_offset = 54;

            stream.write(reinterpret_cast<char*>(&pixel_offset), sizeof(pixel_offset));

            uint32_t header_size = 40;

            stream.write(reinterpret_cast<char*>(&header_size), sizeof(header_size));

            stream.write(reinterpret_cast<char*>(&m_size.w), sizeof(m_size.w));

            stream.write(reinterpret_cast<char*>(&m_size.h), sizeof(m_size.h));

            uint16_t planes = 1;

            stream.write(reinterpret_cast<char*>(&planes), sizeof(planes));

            uint16_t bpp = 32;

            stream.write(reinterpret_cast<char*>(&bpp), sizeof(bpp));

            uint32_t compression = 0;

            stream.write(reinterpret_cast<char*>(&compression), sizeof(compression));

            uint32_t image_size = m_size.w * m_size.h * 4;

            stream.write(reinterpret_cast<char*>(&image_size), sizeof(image_size));

            uint32_t x_ppm = 0;

            stream.write(reinterpret_cast<char*>(&x_ppm), sizeof(x_ppm));

            uint32_t y_ppm = 0;

            stream.write(reinterpret_cast<char*>(&y_ppm), sizeof(y_ppm));

            uint32_t colors = 0;

            stream.write(reinterpret_cast<char*>(&colors), sizeof(colors));

            uint32_t important_colors = 0;

            stream.write(reinterpret_cast<char*>(&important_colors), sizeof(important_colors));

            for(int i = 0; i < m_size.w * m_size.h; i++)
            {
                stream.write(reinterpret_cast<char*>(&m_pixels[i].b), 1);
                stream.write(reinterpret_cast<char*>(&m_pixels[i].g), 1);
                stream.write(reinterpret_cast<char*>(&m_pixels[i].r), 1);
                stream.write(reinterpret_cast<char*>(&m_pixels[i].a), 1);
            }

            stream.close();
        }

        image image::load_bitmap(const std::filesystem::path& path)
        {
            std::ifstream stream(path, std::ios::binary);

            if(!stream.is_open())
            {
                throw std::runtime_error("Failed to open file");
            }

            uint32_t pixel_offset;

            stream.seekg(10);

            stream.read(reinterpret_cast<char*>(&pixel_offset), sizeof(pixel_offset));            
            
            stream.seekg(18);

            uva::size size;

            uint32_t buffer;
            char* buffer_ptr = reinterpret_cast<char*>(&buffer);

            stream.read(buffer_ptr, sizeof(buffer));

            size.w = buffer;

            stream.read(buffer_ptr, sizeof(buffer));

            size.h = buffer;
            
            image img(size);

            stream.seekg(28);

            stream.read(buffer_ptr, 2);

            if(buffer != 32) 
            {
                throw std::runtime_error("Unsupported bpp");
            }

            stream.seekg(pixel_offset);

            int bpp = buffer / 8;

            for(int i = 0; i < size.w * size.h; i++)
            {
                stream.read(buffer_ptr, bpp);

                img.m_pixels[i] = uva::color(buffer_ptr[2], buffer_ptr[1], buffer_ptr[0], buffer_ptr[3]);
            }

            return img;
        }
    };
};