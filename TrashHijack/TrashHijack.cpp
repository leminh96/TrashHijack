// TrashHijack.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TrashHijack.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TRASHHIJACK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TRASHHIJACK));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRASHHIJACK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TRASHHIJACK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   100, 100, 630, 500, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

HWND hWnd;
HHOOK hMyHook;
HINSTANCE hInstance;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
INT InitKeyHook(HWND hwndYourWindow)
{
	hWnd = hwndYourWindow;
	hMyHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, hInstance, 0);
	if (hMyHook != NULL)
	{
		return 1;
	}
	return 0;
}

bool flag = false;
wofstream f;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
		return CallNextHookEx(hMyHook, nCode, wParam, lParam);
	else
	{
		if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('C') & 0x8000) && (GetAsyncKeyState(VK_SHIFT) & 0x8000) && (flag == false))
		{
			flag = true;
			MessageBox(NULL, L"Activated", L"Trash Hijack", MB_OK);
		}
		else if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('C') & 0x8000) && (GetAsyncKeyState(VK_SHIFT) & 0x8000) && (flag == true))
		{
			flag = false;
			MessageBox(NULL, L"Deactivated", L"Screen Watch", NULL);
		}
	}
	return CallNextHookEx(hMyHook, nCode, wParam, lParam);
}
 
HWND clipboardviewr, smallcap;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		HFONT hFont = CreateFont(-25, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
		HFONT kFont = CreateFont(-15, 0, 0, 0, FW_LIGHT, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
		HFONT mFont = CreateFont(-13, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
		InitKeyHook(hWnd);
		const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
		f.open(L"Clipboardtext.txt", ios::out | ios::app);
		f.imbue(utf8_locale);
		OpenClipboard(hWnd);
		EmptyClipboard();
		CloseClipboard();
		clipboardviewr = SetClipboardViewer(hWnd);
		smallcap = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_BITMAP, 50, 50, 200, 200, hWnd, NULL, hInst, NULL);
		HWND hwnd = CreateWindowEx(0, L"STATIC", L"TRASH HIJACK", WS_CHILD | WS_VISIBLE | SS_LEFT , 200, 0, 300, 100, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
		hwnd = CreateWindowEx(0, L"STATIC", L"Your current screenshot", WS_CHILD | WS_VISIBLE | SS_LEFT, 220, 360, 300, 100, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(kFont), TRUE);
		hwnd = CreateWindowEx(0, L"STATIC", L"Press Ctrl + Alt + Shift + C to activate", WS_CHILD | WS_VISIBLE | SS_LEFT, 300, 50, 300, 30, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(mFont), TRUE);
	}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_DRAWCLIPBOARD:
		if (flag == true)
		{
			if (OpenClipboard(hWnd))
			{
				if (IsClipboardFormatAvailable(CF_UNICODETEXT))
				{
					HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
					LPCWSTR buffer = (LPCWSTR)GlobalLock(hClipboardData);
					f << buffer << endl;
					GlobalUnlock(hClipboardData);
				}

				else if (IsClipboardFormatAvailable(CF_BITMAP))
				{
					int left_screen = GetSystemMetrics(SM_XVIRTUALSCREEN);
					int right_screen = GetSystemMetrics(SM_CXVIRTUALSCREEN);
					int top_screen = GetSystemMetrics(SM_YVIRTUALSCREEN);
					int bottom_screen = GetSystemMetrics(SM_CYVIRTUALSCREEN);

					int width = right_screen - left_screen;
					int height = bottom_screen - top_screen;

					HDC myScreen = GetDC(NULL);
					HDC memDC = CreateCompatibleDC(myScreen);
					HBITMAP hBitmap = CreateCompatibleBitmap(myScreen, width, height);
					HGDIOBJ myobj = SelectObject(memDC, hBitmap);
					BitBlt(memDC, 0, 0, width, height, myScreen, left_screen, top_screen, SRCCOPY);
					BITMAP bitmap;
					GetObject(hBitmap, sizeof(BITMAP), &bitmap);

					OpenClipboard(NULL);
					EmptyClipboard();
					SetClipboardData(CF_BITMAP, hBitmap);

					HDC hdc = GetDC(smallcap);
					SetStretchBltMode(hdc, HALFTONE);
					StretchBlt(hdc, 0, 0, 500, 300, memDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

					TCHAR szName[MAX_PATH] = { 0 };
					SYSTEMTIME st = { 0 };
					::GetLocalTime(&st);
					wsprintf(szName, _T("Screenshot//Screen %d-%d-%d %d-%d-%d.bmp"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

					CImage image;
					image.Attach(hBitmap);
					image.Save(szName, Gdiplus::ImageFormatBMP);

					SelectObject(memDC, myobj);
					DeleteDC(memDC);
					ReleaseDC(NULL, myScreen);
					ReleaseDC(hWnd, hdc);
					DeleteObject(hBitmap);
				}
				CloseClipboard();
			}
		}
		break;
    case WM_DESTROY:
		f.close();
		ChangeClipboardChain(hWnd, clipboardviewr);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
