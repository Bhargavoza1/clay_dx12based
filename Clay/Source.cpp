#include <windows.h>
#include <wrl.h>
#include "resource.h"

#include<WinUser.h>

LRESULT CALLBACK MainWndProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{

    switch (uMsg)
    {
    case WM_CREATE:

        return 0;

    case WM_PAINT:

        return 0;

    case WM_SIZE:

        return 0;

    case WM_DESTROY:

        PostQuitMessage(200);
        return 0;



    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
    PSTR cmdLine, int showCmd)
{
    int mClientWidth = 800;
    int mClientHeight = 600;
    HWND      mhMainWnd = nullptr;
    const auto mMainWndCaption = L"mara gharni app";
    HINSTANCE mhAppInst = nullptr;

    WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = L"MainWnd";

    if (!::RegisterClassW(&wc))
    {
        MessageBox(0, L"RegisterClass Failed.", 0, 0);
        return false;
    }

    RECT R = { 0, 0, mClientWidth, mClientHeight };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
    int width = R.right - R.left;
    int height = R.bottom - R.top;

    mhMainWnd = CreateWindowW(L"MainWnd", mMainWndCaption,
        WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_MAXIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hInstance, 0);

    if (!mhMainWnd)
    {
        MessageBox(0, L"CreateWindow Failed.", 0, 0);
        return false;
    }


    ShowWindow(mhMainWnd, SW_SHOW);
    UpdateWindow(mhMainWnd);

    MSG msg = { 0 };


    try
    {
        while (msg.message != WM_QUIT)
        {
            if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        return (int)msg.wParam;
    }
    catch (...)
    {
        MessageBox(nullptr, L"error", L"HR Failed", MB_OK);
        return 0;
    }


}

