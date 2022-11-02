//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by DirectXScene.rc
//

#define IDS_APP_TITLE           103

#define IDR_MAINFRAME           128
#define IDD_TUTORIAL1_DIALOG    102
#define IDD_ABOUTBOX            103
#define IDM_ABOUT               104
#define IDM_EXIT                105
#define IDI_TUTORIAL1           107
#define IDI_SMALL               108
#define IDC_TUTORIAL1           109
#define IDC_MYICON              2
#define IDC_STATIC              -1
// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NO_MFC                 130
#define _APS_NEXT_RESOURCE_VALUE    129
#define _APS_NEXT_COMMAND_VALUE     32771
#define _APS_NEXT_CONTROL_VALUE     1000
#define _APS_NEXT_SYMED_VALUE       110
#endif
#endif

// Create vertex buffer
const simple_vertex vertices[] =
{
    {XMFLOAT3(-2.0f, -3.8f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.3f, 1.0f)},
    {XMFLOAT3(-2.0f, -3.8f, 0.6f), XMFLOAT4(0.5f, 0.3f, 0.3f, 1.0f)},

    {XMFLOAT3(-1.2f, -2.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.4f, 1.0f)},
    {XMFLOAT3(-1.2f, -2.0f, 0.6f), XMFLOAT4(0.3f, 0.5f, 0.3f, 1.0f)},

    {XMFLOAT3(-2.0f, -2.0f, 0.0f), XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f)},
    {XMFLOAT3(-2.0f, -2.0f, 0.6f), XMFLOAT4(0.0f, 0.0f, 0.6f, 1.0f)},

    {XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.8f, 1.0f)},
    {XMFLOAT3(-1.0f, 0.0f, 0.6f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)},

    {XMFLOAT3(-2.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
    {XMFLOAT3(-2.0f, 0.0f, 0.6f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)},

    //

    {XMFLOAT3(0.0f, 3.4f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
    {XMFLOAT3(0.0f, 3.4f, 0.6f), XMFLOAT4(0.0f, 0.3f, 1.0f, 1.0f)},

    //

    {XMFLOAT3(2.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.1f, 1.0f, 1.0f)},
    {XMFLOAT3(2.0f, 0.0f, 0.6f), XMFLOAT4(0.0f, 0.2f, 0.0f, 1.0f)},

    {XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 0.9f, 1.0f, 1.0f)},
    {XMFLOAT3(1.0f, 0.0f, 0.6f), XMFLOAT4(0.0f, 0.7f, 1.0f, 1.0f)},

    {XMFLOAT3(2.0f, -2.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.9f, 1.0f)},
    {XMFLOAT3(2.0f, -2.0f, 0.6f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},

    {XMFLOAT3(1.2f, -2.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
    {XMFLOAT3(1.2f, -2.0f, 0.6f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},

    {XMFLOAT3(2.0f, -3.8f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
    {XMFLOAT3(2.0f, -3.8f, 0.6f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
};

// Create index buffer
const WORD indices[] =
{
    // forward

    0, 2, 20,
    18, 20, 2,

    2, 14, 18,
    18, 14, 16,
    2, 6, 14,
    2, 4, 6,

    6, 8, 10,
    6, 10, 14,
    14, 10, 12,

    // backward

    1, 19, 3,
    1, 21, 19,

    3, 7, 5,
    19, 17, 15,
    19, 7, 3,
    19, 15, 7,

    7, 11, 9,
    7, 15, 11,
    15, 13, 11,

    // side left 

    1, 0, 20,
    20, 21, 1,

    0, 3, 2,
    3, 0, 1,

    3, 5, 2,
    5, 4, 2,

    5, 7, 4,
    4, 7, 6,

    9, 6, 7,
    9, 8, 6,

    9, 11, 8,
    8, 11, 10,

    // side right

    21, 20, 18,
    18, 21, 19,

    19, 16, 17,
    19, 18, 16,

    16, 14, 17,
    17, 14, 15,

    15, 12, 13,
    15, 14, 12,

    13, 12, 10,
    13, 10, 11,

};

const XMMATRIX object_position[object_count]
{
    XMMatrixTranslation( 1.0f, 1.0f, 1.0f ),
    XMMatrixTranslation( 0.1f, 0.5f, 0.04f ),
    XMMatrixTranslation( -0.5f, 0.5f, -0.4f ),
    XMMatrixTranslation( -0.6f, -0.9f, 0.3f ),
    XMMatrixTranslation( -4.0f, -2.0f, 2.0f ),
    XMMatrixTranslation( -4.0f, -2.0f, 1.0f ),
    XMMatrixTranslation( -4.0f, -2.0f, 2.0f ),
};
