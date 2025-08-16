#include <andy/drawing/app.hpp>

#include <gtk/gtk.h>

namespace andy
{
    namespace drawing
    {
        app::app()
        {
            gtk_init(nullptr, nullptr);
        }

        void app::run()
        {
            on_init();
            gtk_main();
        }

        app::~app()
        {
            gtk_main_quit();
        }
    }
};