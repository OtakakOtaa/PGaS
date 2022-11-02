#pragma once
/**
* //--------------------------------------------------------------------------------------
* // Create Direct3D device and swap chain
* //--------------------------------------------------------------------------------------
**/
class device_factory
{
public:
    static HRESULT init_device()
    {
        HRESULT hr = S_OK;

        RECT rc;
        GetClientRect(g_h_wnd, &rc);
        UINT width = rc.right - rc.left;
        UINT height = rc.bottom - rc.top;

        UINT create_device_flags = 0;

#ifdef _DEBUG
        create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        D3D_DRIVER_TYPE driver_types[] =
        {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE,
        };
        UINT numDriverTypes = ARRAYSIZE(driver_types);

        D3D_FEATURE_LEVEL feature_levels[] =
        {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
        };
        UINT num_feature_levels = ARRAYSIZE(feature_levels);

        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = g_h_wnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        for (UINT driver_type_index = 0; driver_type_index < numDriverTypes; driver_type_index++)
        {
            g_driver_type = driver_types[driver_type_index];
            hr = D3D11CreateDeviceAndSwapChain(nullptr, g_driver_type, nullptr, create_device_flags, feature_levels,
                                               num_feature_levels,
                                               D3D11_SDK_VERSION, &sd, &g_p_swap_chain, &g_pd3d_device,
                                               &g_feature_level, &g_p_immediate_context);
            if (SUCCEEDED(hr))
                break;
        }
        if (FAILED(hr))
            return hr;

        // Create a render target view
        ID3D11Texture2D* p_back_buffer = nullptr;
        hr = g_p_swap_chain->GetBuffer(0, __uuidof( ID3D11Texture2D), reinterpret_cast<LPVOID*>(&p_back_buffer));
        if (FAILED(hr))
            return hr;

        hr = g_pd3d_device->CreateRenderTargetView(p_back_buffer, nullptr, &g_p_render_target_view);
        p_back_buffer->Release();
        if (FAILED(hr))
            return hr;

        // Create depth stencil texture
        D3D11_TEXTURE2D_DESC descDepth;
        ZeroMemory(&descDepth, sizeof(descDepth));
        descDepth.Width = width;
        descDepth.Height = height;
        descDepth.MipLevels = 1;
        descDepth.ArraySize = 1;
        descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        descDepth.SampleDesc.Count = 1;
        descDepth.SampleDesc.Quality = 0;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        descDepth.CPUAccessFlags = 0;
        descDepth.MiscFlags = 0;
        hr = g_pd3d_device->CreateTexture2D(&descDepth, nullptr, &g_p_depth_stencil);
        if (FAILED(hr))
            return hr;

        // Create the depth stencil view
        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
        ZeroMemory(&descDSV, sizeof(descDSV));
        descDSV.Format = descDepth.Format;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;
        hr = g_pd3d_device->CreateDepthStencilView(g_p_depth_stencil, &descDSV, &g_p_depth_stencil_view);
        if (FAILED(hr))
            return hr;

        g_p_immediate_context->OMSetRenderTargets(1, &g_p_render_target_view, g_p_depth_stencil_view);

        // Setup the viewport
        D3D11_VIEWPORT vp;
        vp.Width = static_cast<FLOAT>(width);
        vp.Height = static_cast<FLOAT>(height);
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        g_p_immediate_context->RSSetViewports(1, &vp);

        // Compile the vertex shader
        ID3DBlob* p_vs_blob = nullptr;
        hr = shader_installer::compile_shader_from_file(L"DirectXScene.fx", "VS", "vs_4_0", &p_vs_blob);
        if (FAILED(hr))
        {
            MessageBox(nullptr,
                       L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.",
                       L"Error", MB_OK);
            return hr;
        }

        // Create the vertex shader
        hr = g_pd3d_device->CreateVertexShader(p_vs_blob->GetBufferPointer(), p_vs_blob->GetBufferSize(), NULL,
                                               &g_p_vertex_shader);
        if (FAILED(hr))
        {
            p_vs_blob->Release();
            return hr;
        }

        // Define the input layout
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
        UINT num_elements = ARRAYSIZE(layout);

        // Create the input layout
        hr = g_pd3d_device->CreateInputLayout(layout, num_elements, p_vs_blob->GetBufferPointer(),
                                              p_vs_blob->GetBufferSize(), &g_p_vertex_layout);
        p_vs_blob->Release();
        if (FAILED(hr))
            return hr;

        // Set the input layout
        g_p_immediate_context->IASetInputLayout(g_p_vertex_layout);

        // Compile the pixel shader
        ID3DBlob* pPSBlob = nullptr;
        hr = shader_installer::compile_shader_from_file(L"DirectXScene.fx", "PS", "ps_4_0", &pPSBlob);
        if (FAILED(hr))
        {
            MessageBox(nullptr,
                       L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.",
                       L"Error", MB_OK);
            return hr;
        }

        // Create the pixel shader
        hr = g_pd3d_device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr,
                                              &g_p_pixel_shader);
        pPSBlob->Release();
        if (FAILED(hr))
            return hr;
        
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(simple_vertex) * vertex_count;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        D3D11_SUBRESOURCE_DATA init_data;
        ZeroMemory(&init_data, sizeof(init_data));
        init_data.pSysMem = vertices;
        hr = g_pd3d_device->CreateBuffer(&bd, &init_data, &g_p_vertex_buffer);
        if (FAILED(hr))
            return hr;

        // Set vertex buffer
        UINT stride = sizeof(simple_vertex);
        UINT offset = 0;
        g_p_immediate_context->IASetVertexBuffers(0, 1, &g_p_vertex_buffer, &stride, &offset);
        
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(WORD) * triangle_count * 3; // 
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.CPUAccessFlags = 0;
        init_data.pSysMem = indices;
        hr = g_pd3d_device->CreateBuffer(&bd, &init_data, &g_p_index_buffer);
        if (FAILED(hr))
            return hr;

        // Set index buffer
        g_p_immediate_context->IASetIndexBuffer(g_p_index_buffer, DXGI_FORMAT_R16_UINT, 0);

        // Set primitive topology
        g_p_immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // Create the constant buffer
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(constant_buffer);
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.CPUAccessFlags = 0;
        hr = g_pd3d_device->CreateBuffer(&bd, nullptr, &g_p_constant_buffer);
        if (FAILED(hr))
            return hr;

        // Initialize the world matrix
        for (int i = 0; i < object_count; i++)
            g_world[i] = XMMatrixIdentity();

        // Initialize the view matrix
        auto eye = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
        auto at = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        auto up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        g_view = XMMatrixLookAtLH(eye, at, up);

        // Initialize the projection matrix
        g_projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, width / static_cast<FLOAT>(height), 0.01f, 100.0f);

        return S_OK;
    }
};
