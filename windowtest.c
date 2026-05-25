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

// WINAPI is a special calling sequence for function calls that occur between Windows and the application (WINAPI is defined as __stdcall)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow){
    static TCHAR szAppName[] = TEXT("Hewwo pookie");
    HWND hwnd; // handle to a window
    MSG msg; // message structure
    WNDCLASS wndclass = { // window class structure
        .style = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = WndProc,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = hInstance, // HINSTANCE: handle to an "instance" of the program itself
        .hIcon = LoadIcon(NULL, IDI_APPLICATION), // load an icon to display at the program title bar
        .hCursor = LoadCursor(NULL, IDC_HAND), // load a mouse cursor (style) for the program; the style is something like "Select", "Person", "Unavailable" (refer to your fox cursor folder); it specified how the cursor should be presented in your program
        .hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH), // obtain a graphic object; in this case a brush for painting window's background
        .lpszMenuName = NULL,
        .lpszClassName = szAppName
    };

    if (!RegisterClass(&wndclass)){
        MessageBox(NULL, TEXT("My guy it is time for you to change your computer"), szAppName, MB_ICONERROR);

        return 0;
    }

    // create a window based on a window class
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

    ShowWindow(hwnd, iCmdShow); // display the window on the screen
    UpdateWindow(hwnd); // direct the window to paint itself

    // GetMessage: obtain message from message queue
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg); // translate keyboard message
        DispatchMessage(&msg); // send message to window procedure
    }
    
    return msg.wParam;
}

// CALLBACK is a special calling sequence for function calls that occur between Windows and the application (CALLBACK is defined as __stdcall)
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC hdc; // handle to a device context
    PAINTSTRUCT ps; // paint structure
    RECT rect; // rectangle structure

    switch (message){
        case WM_CREATE:
            PlaySound(TEXT("konpeko.wav"), NULL, SND_FILENAME | SND_ASYNC); // play a sound file
            return 0;
        
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps); // initialize the beginning of window painting
            GetClientRect(hwnd, &rect); // obtain the dimension of the window's client area
            DrawText(hdc, TEXT("Konpeko~"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); // display a text string
            EndPaint(hwnd, &ps); // end window painting
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0); // insert a "quit" message into the message queue
            return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam); // perform default processing of messages
}
