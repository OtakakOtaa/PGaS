#pragma once
/**
* //--------------------------------------------------------------------------------------
* // Register class and create window
* //--------------------------------------------------------------------------------------
**/
class window_factory
{
public:
    static HRESULT create( HINSTANCE h_instance, const int nCmdShow )
    {
        // Register class
        WNDCLASSEX wcex;
        wcex.cbSize = sizeof( WNDCLASSEX );
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = windows_proc_holder::wnd_proc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = h_instance;
        wcex.hIcon = LoadIcon( h_instance, reinterpret_cast<LPCTSTR>(IDI_TUTORIAL1) );
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW );
        wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = L"TutorialWindowClass";
        wcex.hIconSm = LoadIcon( wcex.hInstance, reinterpret_cast<LPCTSTR>(IDI_TUTORIAL1) );
        if( !RegisterClassEx( &wcex ) )
            return E_FAIL;

        // Create window
        g_h_inst = h_instance;
        RECT rc = { 0, 0, 400, 480 };
        AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
        g_h_wnd = CreateWindow(L"TutorialWindowClass",
                              L"Direct3D 11 Tutorial 5",
                              WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT,
                              CW_USEDEFAULT,
                              rc.right - rc.left,
                              rc.bottom - rc.top,
                              NULL,
                              NULL,
                              h_instance,
                              NULL);
        if( !g_h_wnd )
            return E_FAIL;

        ShowWindow( g_h_wnd, nCmdShow );

        return S_OK;
    }
};
