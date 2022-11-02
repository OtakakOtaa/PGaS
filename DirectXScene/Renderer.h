#pragma once
//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
class renderer
{
public:
    static  void render()
    {
        // Update our time
        static float t = 0.0f;
        if( g_driver_type == D3D_DRIVER_TYPE_REFERENCE )
        {
            t += XM_PI * 0.0125f;
        }
        else
        {
            static DWORD dw_time_start = 0;
            DWORD dw_time_cur = GetTickCount();

            if( dw_time_start == 0 )
                dw_time_start = dw_time_cur;
            
            t = ( dw_time_cur - dw_time_start ) / 1000.0f;
        }

        for (int i = 0; i < object_count / 2; i++)
        {
            XMMATRIX m_scale = XMMatrixScaling( 0.4f, 0.4f, 0.4f );
            t = (std::sin(t) + std::cos(t)) * rotation_scale;
            g_world[i] = XMMatrixRotationY(t) * object_position[i] * m_scale;
        }
        for (int i = object_count / 2; i < object_count; i++)
        {
            XMMATRIX m_spin = XMMatrixRotationZ(-t);
            XMMATRIX m_orbit = XMMatrixRotationY(-t * 2.0f);
            XMMATRIX m_scale = XMMatrixScaling( 0.1f, 0.1f, 0.1f );

            g_world[1] = m_scale * m_spin * object_position[i] * m_orbit;
        }

        

        //
        // Clear the back buffer
        //
        float clear_color[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red, green, blue, alpha
        g_p_immediate_context->ClearRenderTargetView( g_p_render_target_view, clear_color );

        //
        // Clear the depth buffer to 1.0 (max depth)
        //
        g_p_immediate_context->ClearDepthStencilView( g_p_depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0 );
    
        //
        // Update objects variables 
        //
        for (int i = 0; i < object_count; i++)
        {
            constant_buffer cb;
            cb.m_world = XMMatrixTranspose( g_world[i] );
            cb.m_view = XMMatrixTranspose( g_view );
            cb.m_projection = XMMatrixTranspose( g_projection );
            g_p_immediate_context->UpdateSubresource( g_p_constant_buffer, 0, nullptr, &cb, 0, 0 );

            // render
            g_p_immediate_context->DrawIndexed( triangle_count * 3, 0, 0 );
        }

        //
        // Set Shader
        //
        g_p_immediate_context->VSSetShader( g_p_vertex_shader, nullptr, 0 );
        g_p_immediate_context->VSSetConstantBuffers( 0, 1, &g_p_constant_buffer );
        g_p_immediate_context->PSSetShader( g_p_pixel_shader, nullptr, 0 );
    
        //
        // Present our back buffer to our front buffer
        //
        g_p_swap_chain->Present( 0, 0 );
    }

};
