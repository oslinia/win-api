#include <windows.h>

#define IDI_ICON    100
#define IDM_MENU    101
#define IDD_TEXT    103
#define IDD_OPTIONS 104

#define IDC_TEXT   1000
#define IDC_STATIC 1001
#define IDC_RED    1002
#define IDC_GREEN  1003
#define IDC_BLACK  1004
#define IDC_APPLY  1005

#define IDM_FILE_OPEN    4000
#define IDM_FILE_TEXT    4001
#define IDM_FILE_OPTIONS 4002
#define IDM_FILE_EXIT    4003

extern HINSTANCE hInst;
extern HWND hWindowText;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
