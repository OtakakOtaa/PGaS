#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>

#include <cmath>

//--------------------------------------------------------------------------------------
// struct DTO
//--------------------------------------------------------------------------------------
struct simple_vertex
{
    XMFLOAT3 pos;
    XMFLOAT4 color;
};

struct constant_buffer
{
	XMMATRIX m_world;
	XMMATRIX m_view;
	XMMATRIX m_projection;
};

//--------------------------------------------------------------------------------------
// cashed scene values
//--------------------------------------------------------------------------------------
constexpr int           vertex_count = 22;
constexpr int           triangle_count = 40;
constexpr FLOAT         rotation_scale = 1.4f;
constexpr int           object_count = 7;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HINSTANCE               g_h_inst = nullptr;
HWND                    g_h_wnd = nullptr;
D3D_DRIVER_TYPE         g_driver_type = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL       g_feature_level = D3D_FEATURE_LEVEL_11_0;
ID3D11Device*           g_pd3d_device = nullptr;
ID3D11DeviceContext*    g_p_immediate_context = nullptr;
IDXGISwapChain*         g_p_swap_chain = nullptr;
ID3D11RenderTargetView* g_p_render_target_view = nullptr;
ID3D11Texture2D*        g_p_depth_stencil = nullptr;
ID3D11DepthStencilView* g_p_depth_stencil_view = nullptr;
ID3D11VertexShader*     g_p_vertex_shader = nullptr;
ID3D11PixelShader*      g_p_pixel_shader = nullptr;
ID3D11InputLayout*      g_p_vertex_layout = nullptr;
ID3D11Buffer*           g_p_vertex_buffer = nullptr;
ID3D11Buffer*           g_p_index_buffer = nullptr;
ID3D11Buffer*           g_p_constant_buffer = nullptr;

XMMATRIX*               g_world = new XMMATRIX[object_count]; 

XMMATRIX                g_view;
XMMATRIX                g_projection;


//--------------------------------------------------------------------------------------
// include dependencies function class
//--------------------------------------------------------------------------------------

#include "resource.h"

#include "WindowsProcHolder.h"
#include "WindowFactory.h"
#include "ShaderInstaller.h"
#include "DeviceFactory.h"
#include "DeviceCleaner.h"
#include "Renderer.h"

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    if( FAILED( window_factory::create(hInstance, nCmdShow)))
        return 0;

    if( FAILED( device_factory::init_device()))
    {
        device_cleaner::cleanup_device();
        return 0;
    }

    // Main message loop
    MSG msg = {nullptr};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
            continue;
        }
        renderer::render();
    }
    
    device_cleaner::cleanup_device();
    return static_cast<int>(msg.wParam);
}

