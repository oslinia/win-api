#include <windows.h>
#include "header.h"

HINSTANCE hInst = NULL;

BOOL InitApplication(LPCWSTR lpClassName)
{
    WNDCLASSEXW wcx;
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = WindowProcedure;
    wcx.cbClsExtra = 0;
    wcx.cbWndExtra = 0;
    wcx.hInstance = hInst;
    wcx.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON));
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = GetStockObject(WHITE_BRUSH);
    wcx.lpszMenuName = MAKEINTRESOURCEW(IDM_MENU);
    wcx.lpszClassName = lpClassName;
    wcx.hIconSm = LoadImage(hInst,
                            MAKEINTRESOURCE(IDI_ICON),
                            IMAGE_ICON,
                            GetSystemMetrics(SM_CXSMICON),
                            GetSystemMetrics(SM_CYSMICON),
                            LR_DEFAULTCOLOR);

    return RegisterClassExW(&wcx);
}

BOOL InitInstance(LPCWSTR lpClassName, int nCmdShow)
{
    HWND hWnd = CreateWindowExW(
        0, lpClassName, L"Main Window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
        (HWND)NULL, (HMENU)NULL, (HINSTANCE)hInst, (LPVOID)NULL);

    if (!hWnd)
        return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst = hInstance;

    WCHAR lpClassName[] = L"MainWindow";

    if (!InitApplication(lpClassName))
        return FALSE;

    if (!InitInstance(lpClassName, nShowCmd))
        return FALSE;

    BOOL bRet;
    MSG msg;
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0 && bRet != -1)
    {
        if (!(IsWindow(hWindowText) && IsDialogMessage(hWindowText, &msg)))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
}
