#include "andy/drawing/basic_renderer.hpp"

namespace andy
{
    namespace drawing
    {
        basic_renderer::basic_renderer()
        {
        }

        basic_renderer::~basic_renderer()
        {
        }

        andy::size basic_renderer::client_size() const
        {
            return andy::size();            
        }
    }
};