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
        .style = CS_HREDRAW | CS_VREDRAW, // define the window class style; in this case it defines the window should repaint itself whenever the horizontal (CS_HREDRAW) or vertical (CS_VREDRAW) window size changes
        .lpfnWndProc = WndProc, // address of window procedure; a callback function of type `LRESULT CALLBACK Wndproc(HWMD, UINT, WPARAM, LPARAM)`
        .cbClsExtra = 0, // number of extra bytes to allocate for the window class structure
        .cbWndExtra = 0, // number of extra bytes to allocate for the window instance
        .hInstance = hInstance, // the instance handle of the program; HINSTANCE: handle to an "instance" of the program itself
        .hIcon = LoadIcon(NULL, IDI_APPLICATION), // load an icon to display at the program title bar
        .hCursor = LoadCursor(NULL, IDC_HAND), // load a mouse cursor (style) for the program; the style is something like "Select", "Person", "Unavailable" (refer to your fox cursor folder); it specified how the cursor should be presented in your program
        .hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH), // obtain a graphic object; in this case a brush for painting window's background
        .lpszMenuName = NULL, // specify the window class menu; in this case, there is no application menu, thus NULL
        .lpszClassName = szAppName // text name of the window class (can be whatever you want)
    };

    // register the window class
    // idea of !RegisterClass is that the older version of Windows (Windows 98) doesn't have function for Unicode char,
    // thus the RegisterClass that is trying to call RegisterClassW will run into error,
    // and if an error occur, we notify the user by messagebox that their device does not support Unicode (doesn't have unicode related .dll)
    if (!RegisterClass(&wndclass)){
        MessageBox(NULL, TEXT("My guy it is time for you to change your computer"), szAppName, MB_ICONERROR);

        return 0;
    }

    // create a window based on a window class
    hwnd = CreateWindow(
        szAppName, // window class name
        TEXT("window time uwu"), // window caption
        WS_OVERLAPPEDWINDOW, // window style
        CW_USEDEFAULT, // initial x position
        CW_USEDEFAULT, // initial y position
        CW_USEDEFAULT, // initial x size
        CW_USEDEFAULT, // initial y size
        NULL, // parent window handle
        NULL, // window menu handle
        hInstance, // program instance handle
        NULL // creation parameters
    );

    ShowWindow(hwnd, iCmdShow); // display the window on the screen
    UpdateWindow(hwnd); // direct the window to paint itself

    // GetMessage: obtain message from message queue
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg); // translate keyboard message
        DispatchMessage(&msg); // send message to window procedure
    }
    
    return msg.wParam; // return the value passed to PostQuitMessage() (usually 0 to indicate the program has successfully terminated)
}

// CALLBACK is a special calling sequence for function calls that occur between Windows and the application (CALLBACK is defined as __stdcall)
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC hdc; // handle to a device context
    PAINTSTRUCT ps; // paint structure
    RECT rect; // rectangle structure

    // switch case to determine the message value
    // all message processed by window procedure should return 0
    switch (message){
        // initialization of window (by CreateWindow)
        case WM_CREATE:
            PlaySound(TEXT("konpeko.wav"), NULL, SND_FILENAME | SND_ASYNC); // play a sound file
            return 0;
        
        // repaint the window; called by UpdateWindow or when the window's client area is invalid (in this case, when window is being resized (due to wndclass.style))
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

    return DefWindowProc(hwnd, message, wParam, lParam); // perform default processing of messages; proess the message that is not processed by window procedure
}
