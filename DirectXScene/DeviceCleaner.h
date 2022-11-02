#pragma once

/**
* //--------------------------------------------------------------------------------------
* // Clean up the objects we've created
* //--------------------------------------------------------------------------------------  
**/

class device_cleaner
{
public:
    static void cleanup_device()
    {
        if( g_p_immediate_context ) g_p_immediate_context->ClearState();

        if( g_p_constant_buffer ) g_p_constant_buffer->Release();
        if( g_p_vertex_buffer ) g_p_vertex_buffer->Release();
        if( g_p_index_buffer ) g_p_index_buffer->Release();
        if( g_p_vertex_layout ) g_p_vertex_layout->Release();
        if( g_p_vertex_shader ) g_p_vertex_shader->Release();
        if( g_p_pixel_shader ) g_p_pixel_shader->Release();
        if( g_p_depth_stencil ) g_p_depth_stencil->Release();
        if( g_p_depth_stencil_view ) g_p_depth_stencil_view->Release();
        if( g_p_render_target_view ) g_p_render_target_view->Release();
        if( g_p_swap_chain ) g_p_swap_chain->Release();
        if( g_p_immediate_context ) g_p_immediate_context->Release();
        if( g_pd3d_device ) g_pd3d_device->Release();
    }


};
