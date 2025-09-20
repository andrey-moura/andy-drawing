#include "andy/xml.hpp"
#include "andy/widgets.hpp"
#include "andy/drawing/basic_renderer.hpp"

namespace andy
{
    namespace drawing
    {
        class page
        {
        public:
            page(andy::xml::schema schema, andy::xml xml);
            ~page();
        public:
            andy::xml::schema schema;
            andy::xml xml;
        public:
            void draw(andy::drawing::basic_renderer& renderer);
        protected:
            std::unique_ptr<andy::widgets::layout> root_layout;
        };
    };
};