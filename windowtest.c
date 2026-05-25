#include <windows.h>
#include <tchar.h>
#include <stdio.h>

// display a message box with format specification syntax
// parameter: TCHAR* szCaption, TCHAR* szFormat, ...
// szCaption: the program's window's caption bar
// szFormat: the string with format specifier (e.g. "%s my beloved")
// ...: ellipsis parameter, used to indicate receiving an indefinite amount of argument
int MessageBoxPrintf(TCHAR* szCaption, TCHAR* szFormat, ...){
    TCHAR szBuffer[1024]; // the char array that will be written (by _vsntprintf)
    va_list pArgList; // the argument list

    va_start(pArgList, szFormat); // point to the first variable argument after the named argument (i.e. last named argument in this case is szFormat; it points to the first argument of ellipsis parameter)
    _vsntprintf(szBuffer, sizeof(szBuffer) / sizeof(TCHAR), szFormat, pArgList); // write the string to szBuffer, follow the format specified in szFormat with the arguments from pArgList
    va_end(pArgList); // zeroes out the argument list

    return MessageBox(NULL, szBuffer, szCaption, 0);
}

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow){
    static TCHAR szAppName[] = TEXT("Hewwo pookie");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass = {
        .style = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = WndProc,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = hInstance,
        .hIcon = LoadIcon(NULL, IDI_APPLICATION),
        .hCursor = LoadCursor(NULL, IDC_ARROW),
        .hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH),
        .lpszMenuName = NULL,
        .lpszClassName = szAppName
    };

    if (!RegisterClass(&wndclass)){
        MessageBox(NULL, TEXT("My guy it is time for you to change your computer"), szAppName, MB_ICONERROR);

        return 0;
    }

    hwnd = CreateWindow(
        szAppName,
        TEXT("window time uwu"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch (message){
        case WM_CREATE:
            PlaySound(TEXT("konpeko.wav"), NULL, SND_FILENAME | SND_ASYNC);
            return 0;
        
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);
            DrawText(hdc, TEXT("Konpeko~"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            EndPaint(hwnd, &ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
