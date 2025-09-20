#include "andy/drawing/window.hpp"

#include <string>
#include <stdexcept>

#include <emscripten.h>

namespace andy
{
    namespace drawing
    {
        window::window(std::string_view title)
        {
            static bool has_first_window_been_created = false;
            if(has_first_window_been_created) {
                // For emscripten backend, for now, only one window can be created.
                throw std::runtime_error("only one window can be created in emscripten backend");
            } else {
                std::string script = "document.title = \"";
                script += title;
                script += "\";";
                emscripten_run_script(script.c_str());
            }
            if(!has_first_window_been_created) {
                has_first_window_been_created = true;
            }
        }

        window::~window()
        {
            // Destructor implementation
        }

        void window::show(bool maximized)
        {
            // Implementation for showing the window
        }
    }
};