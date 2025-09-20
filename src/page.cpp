#include "andy/drawing/page.hpp"

#include "andy/xml.hpp"

#include <iostream>

namespace andy
{
    namespace drawing
    {
        page::page(andy::xml::schema __schema, andy::xml __xml)
            : schema(std::move(__schema)), xml(std::move(__xml))
        {
            
        }

        page::~page()
        {
            // Destructor implementation
        }

        void page::draw(andy::drawing::basic_renderer& renderer)
        {
            andy::size size = renderer.client_size();

            if(!root_layout) {
                root_layout = std::make_unique<andy::widgets::layout>();
                root_layout->parse(schema, xml);
            }

            root_layout->calculate_layout(renderer, { 0, 0 }, size);

            root_layout->render(renderer);
        }
    }
};