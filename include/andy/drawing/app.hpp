#pragma once

namespace andy
{
    namespace drawing
    {
        class app
        {
        public:
            app();
            ~app();
        protected:
            void run();
            virtual void on_init();
        };
    }
};