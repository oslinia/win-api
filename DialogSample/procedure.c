#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "header.h"

TCHAR szWindowText[1024] = L"Hello world!";
int iColorText = IDC_BLACK;
HWND hWindowText = NULL;

void UpdateWindowText()
{
    if (hWindowText)
        SetDlgItemText(hWindowText, IDC_TEXT, szWindowText);
}

INT_PTR CALLBACK TextProc(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg)
    {
    case WM_INITDIALOG:
        SetDlgItemText(hDlg, IDC_TEXT, szWindowText);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_TEXT:
            if (HIWORD(wParam) == EN_CHANGE)
            {
                GetDlgItemText(hDlg, IDC_TEXT, szWindowText, 1024);
                InvalidateRect(GetParent(hDlg), 0, TRUE);
                return TRUE;
            }
            break;
        case IDCANCEL:
            DestroyWindow(hDlg);
            hWindowText = NULL;
            return TRUE;
        }
        break;
    }
    return FALSE;
}

INT_PTR CALLBACK OptionsProc(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg)
    {
    case WM_INITDIALOG:
        SetDlgItemTextW(hDlg, IDC_TEXT, szWindowText);
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            GetDlgItemText(hDlg, IDC_TEXT, szWindowText, 1024);
            if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_RED))
                iColorText = IDC_RED;
            if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_GREEN))
                iColorText = IDC_GREEN;
            if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_BLACK))
                iColorText = IDC_BLACK;
        case IDCANCEL:
            EndDialog(hDlg, 0);
            return TRUE;
        case IDC_APPLY:
            GetDlgItemText(hDlg, IDC_TEXT, szWindowText, 1024);
            if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_RED))
                iColorText = IDC_RED;
            if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_GREEN))
                iColorText = IDC_GREEN;
            if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_BLACK))
                iColorText = IDC_BLACK;
            InvalidateRect(GetParent(hDlg), 0, TRUE);
            UpdateWindowText();
            return TRUE;
        }
        break;
    }
    return FALSE;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_PAINT:
    {
        RECT rc = {0};
        GetClientRect(hWnd, &rc);

        PAINTSTRUCT ps = {0};
        HDC hdc = BeginPaint(hWnd, &ps);

        COLORREF defaultColor = GetTextColor(hdc);

        switch (iColorText)
        {
        case IDC_RED:
            SetTextColor(hdc, RGB(255, 0, 0));
            break;
        case IDC_GREEN:
            SetTextColor(hdc, RGB(0, 128, 0));
            break;
        case IDC_BLACK:
            SetTextColor(hdc, RGB(0, 0, 0));
            break;
        }

        DrawText(hdc, szWindowText, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        SetTextColor(hdc, defaultColor);

        EndPaint(hWnd, &ps);

        return 0;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDM_FILE_OPEN:
            TCHAR szFileName[_MAX_PATH] = {0};
            static OPENFILENAME ofn = {0};
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFile = szFileName;
            ofn.nMaxFile = _MAX_PATH;
            ofn.lpstrFilter = TEXT("All Files (*.*)\0*.*\0Source Files (*.cpp)\0*.cpp\0");
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
            if (GetOpenFileName(&ofn))
            {
                wcscpy_s(szWindowText, _countof(szWindowText), szFileName);
                InvalidateRect(hWnd, 0, TRUE);
                UpdateWindowText();
            }
            break;
        case IDM_FILE_TEXT:
            if (!hWindowText)
                hWindowText = CreateDialogW(hInst, MAKEINTRESOURCEW(IDD_TEXT), hWnd, TextProc);
            break;
        case IDM_FILE_OPTIONS:
            DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_OPTIONS), hWnd, OptionsProc);
            InvalidateRect(hWnd, 0, TRUE);
            UpdateWindowText();
            break;
        case IDM_FILE_EXIT:
            DestroyWindow(hWnd);
            return 0;
        }
        break;
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
        {
            DestroyWindow(hWnd);
            return 0;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}
