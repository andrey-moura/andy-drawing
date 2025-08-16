#include "andy/drawing/window.hpp"

#include <Windows.h>

auto to_tstring(std::string_view str)
{
#ifdef UNICODE
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), &wstr[0], size_needed);
    return wstr;
#else
    return str;
#endif
}

static HWND create_window(std::string_view title)
{
    // Register the window class
    const TCHAR CLASS_NAME[] = TEXT("Window Class");

    WNDCLASS wc = { };

    wc.lpfnWndProc   = DefWindowProc;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                                // Optional window styles.
        CLASS_NAME,                       // Window class
        to_tstring(title).data(),         // Window text
        WS_OVERLAPPEDWINDOW,              // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        GetModuleHandle(NULL),  // Instance handle
        NULL        // Additional application data
    );

    return hwnd;
}

#define m_hwnd (HWND)m_data

namespace andy
{
    namespace drawing
    {
        window::window(std::string_view title)
        {
            // Create the window using GTK
            m_data = create_window(title);
        }

        void window::show(bool maxmized)
        {
            ShowWindow(m_hwnd, maxmized ? SW_MAXIMIZE : SW_SHOW);
            UpdateWindow(m_hwnd);
        }

        andy::size window::size() const
        {
            RECT rect;
            GetClientRect(m_hwnd, &rect);
            return andy::size{ rect.right - rect.left, rect.bottom - rect.top };
        }

        window::~window()
        {
            DestroyWindow(m_hwnd);
            m_data = nullptr;
        }
    };
};