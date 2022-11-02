#pragma once
#include <d3d10.h>

/**
* //--------------------------------------------------------------------------------------
* // Called every time the application receives a message
* //--------------------------------------------------------------------------------------
**/
class windows_proc_holder
{
public:
    static LRESULT CALLBACK wnd_proc(const HWND h_wnd, const UINT message, WPARAM w_param, const LPARAM l_param )
    {
        PAINTSTRUCT ps;
        HDC hdc;

        switch( message )
        {
        case WM_PAINT:
            hdc = BeginPaint( h_wnd, &ps );
            EndPaint( h_wnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( h_wnd, message, w_param, l_param );
        }

        return 0;
    }
    
};
