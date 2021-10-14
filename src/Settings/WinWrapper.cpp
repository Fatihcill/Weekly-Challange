#include "WinWrapper.hpp"

#ifdef __unix__
#include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

namespace raysettings
{
    void GetWindowSize(void *winHandle, int &p_out_width, int &p_out_height)
    {
    #ifdef __unix__
    #elif defined(_WIN32) || defined(WIN32)
        HWND window = (HWND)winHandle;
        RECT area;
        GetClientRect(window, &area);
        p_out_width = area.right;
        p_out_height = area.bottom;
    #endif
    }
    
}