#include <windows.h>
#include <stdio.h>
#include <ctype.h>

HHOOK hMouseHook;
int mouseButtonToMap = 0; 
char keyToMap = 'e'; 


#define PASTEL_PINK RGB(255, 182, 193)
#define PASTEL_BLUE RGB(173, 216, 230)
#define PASTEL_GREEN RGB(152, 251, 152)
#define PASTEL_YELLOW RGB(255, 255, 224)

HBRUSH SetBackgroundColor(COLORREF color) {
    return CreateSolidBrush(color);
}


LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_XBUTTONDOWN) {
            MSLLHOOKSTRUCT* mouseInfo = (MSLLHOOKSTRUCT*)lParam;
            
            if ((mouseButtonToMap == 1 && HIWORD(mouseInfo->mouseData) == XBUTTON1) ||
                (mouseButtonToMap == 2 && HIWORD(mouseInfo->mouseData) == XBUTTON2)) {
                
                
                INPUT input = {0};
                input.type = INPUT_KEYBOARD;
                input.ki.wVk = toupper(keyToMap);
                SendInput(1, &input, sizeof(INPUT));
                
                
                input.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &input, sizeof(INPUT));
                
                
                return 1;
            }
        }
    }
    return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            
            if (LOWORD(wParam) == 1) {
                mouseButtonToMap = 1;
            } else if (LOWORD(wParam) == 2) {
                mouseButtonToMap = 2;
            } else if (LOWORD(wParam) == 3) {
                char buffer[2];
                GetDlgItemText(hwnd, 1002, buffer, 2);
                if (isalpha(buffer[0])) {
                    keyToMap = toupper(buffer[0]);
                    char message[256];
                    sprintf(message, "Mouse button %d is now mapped to '%c'.", mouseButtonToMap, keyToMap);
                    MessageBox(hwnd, message, "Mapping Set", MB_OK);
                } else {
                    MessageBox(hwnd, "Invalid key. Please enter a valid alphabet key.", "Error", MB_OK | MB_ICONERROR);
                }
            }
            break;
        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;
            SetBkColor(hdcStatic, PASTEL_YELLOW);
            return (INT_PTR)SetBackgroundColor(PASTEL_YELLOW);
        }
        case WM_CTLCOLORBTN: {
            HDC hdcButton = (HDC)wParam;
            SetBkColor(hdcButton, PASTEL_GREEN);
            return (INT_PTR)SetBackgroundColor(PASTEL_GREEN);
        }
        case WM_CTLCOLOREDIT: {
            HDC hdcEdit = (HDC)wParam;
            SetBkColor(hdcEdit, PASTEL_BLUE);
            return (INT_PTR)SetBackgroundColor(PASTEL_BLUE);
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char* CLASS_NAME = "Mouse Remapper";
    
    
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = SetBackgroundColor(PASTEL_PINK); 
    
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Pranjol Das - Mouse Button Remapper",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    
    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    
    CreateWindow("STATIC", "Select Mouse Button:", WS_VISIBLE | WS_CHILD, 20, 20, 200, 20, hwnd, NULL, hInstance, NULL);
    HWND button1 = CreateWindow("BUTTON", "Side Button 1", WS_VISIBLE | WS_CHILD, 20, 50, 100, 30, hwnd, (HMENU)1, hInstance, NULL);
    HWND button2 = CreateWindow("BUTTON", "Side Button 2", WS_VISIBLE | WS_CHILD, 140, 50, 100, 30, hwnd, (HMENU)2, hInstance, NULL);
    
    CreateWindow("STATIC", "Enter Key to Map:", WS_VISIBLE | WS_CHILD, 20, 100, 200, 20, hwnd, NULL, hInstance, NULL);
    HWND editBox = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 130, 100, 20, hwnd, (HMENU)1002, hInstance, NULL);
    HWND setButton = CreateWindow("BUTTON", "Set Mapping", WS_VISIBLE | WS_CHILD, 140, 130, 100, 30, hwnd, (HMENU)3, hInstance, NULL);
    
    
    HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    SendMessage(button1, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(button2, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(editBox, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(setButton, WM_SETFONT, (WPARAM)hFont, TRUE);
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    
    hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInstance, 0);
    if (hMouseHook == NULL) {
        MessageBox(NULL, "Failed to set mouse hook. Please run as administrator.", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    
    
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    
    UnhookWindowsHookEx(hMouseHook);
    
    return 0;
}
