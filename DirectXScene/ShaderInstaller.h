#pragma once

/**
* //--------------------------------------------------------------------------------------
* // Helper for compiling shaders with D3DX11
* //--------------------------------------------------------------------------------------
**/
class shader_installer
{
public:
    static HRESULT compile_shader_from_file(const WCHAR* sz_file_name,
        const LPCSTR sz_entry_point, const LPCSTR sz_shader_model,
        ID3DBlob** pp_blob_out)
    {
        HRESULT hr = S_OK;

        DWORD dw_shader_flags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )

        // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
        // Setting this flag improves the shader debugging experience, but still allows 
        // the shaders to be optimized and to run exactly the way they will run in 
        // the release configuration of this program.

        dw_shader_flags |= D3DCOMPILE_DEBUG;

#endif
        
        ID3DBlob* p_error_blob;
        hr = D3DX11CompileFromFile(sz_file_name, NULL, NULL, sz_entry_point, sz_shader_model,
                                   dw_shader_flags, 0, NULL, pp_blob_out, &p_error_blob, NULL);
        if (FAILED(hr))
        {
            if (p_error_blob != nullptr)
                OutputDebugStringA(static_cast<char*>(p_error_blob->GetBufferPointer()));
            if (p_error_blob) p_error_blob->Release();
            return hr;
        }
        if (p_error_blob) p_error_blob->Release();
        return S_OK;
    }
};
