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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow){
    int cxScreen, cyScreen;
    cxScreen = GetSystemMetrics(SM_CXSCREEN);
    cyScreen = GetSystemMetrics(SM_CYSCREEN);

    MessageBoxPrintf(TEXT("uwu screen size"), TEXT("The screen is %i pixels wide by %i pixels high."), cxScreen, cyScreen);
    
    return 0;
}
