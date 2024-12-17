#include <unistd.h>
#include <windows.h>
#include <Winuser.h>
#include <stdio.h>
#include <wingdi.h>

/*cursors: https://learn.microsoft.com/en-us/windows/win32/menurc/about-cursors */
//HCURSOR hCurs;
WNDCLASS g_wc = { };
HINSTANCE g_hInst;

/*
	https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure
	uMsg: https://learn.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues#system-defined-messages 
 */
LRESULT WindowProc(
  HWND hWindow,
  UINT uMsg,
  WPARAM wParam,
  LPARAM lParam
){

	switch(uMsg){

		case WM_CLOSE:
			DestroyWindow(hWindow);
			PostQuitMessage(0);
			return 0;
		
		/*case WM_SETCURSOR:
			g_wc.hCursor = LoadCursorA(g_hInst,IDC_ARROW);
			if (IsIconic(hWindow)) 
	    { 
	        SetCursor(LoadCursorA(g_hInst,IDC_ARROW)); 
	        break; 
	    } 
			
			return 0;

		  case WM_ENTERSIZEMOVE:
			g_wc.hCursor = LoadCursorA(g_hInst,IDC_SIZEWE);
			return DefWindowProc(hWindow, uMsg, wParam, lParam);
		  case WM_EXITSIZEMOVE:
			g_wc.hCursor = LoadCursorA(g_hInst,IDC_ARROW);
			return DefWindowProc(hWindow, uMsg, wParam, lParam);
*/


		case WM_PAINT:
		{
			/* https://learn.microsoft.com/en-us/windows/win32/learnwin32/painting-the-window */
				PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWindow, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        HBRUSH wincol = CreateSolidBrush(RGB(0xa5,0x15,0x13)); /*(HBRUSH) (COLOR_WINDOW+1) */
        FillRect(hdc, &ps.rcPaint, wincol);

        EndPaint(hWindow, &ps);

			return DefWindowProc(hWindow, uMsg, wParam, lParam);
		}
		default:
			return DefWindowProc(hWindow, uMsg, wParam, lParam);
	}
}

/*int __clrcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){*/

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	g_hInst = hInst;
	/*hCurs = LoadCursorA(hInst,IDC_ARROW);*/


	// Register the window class.
	const char CLASS_NAME[]  = "Sample Window Class";

	g_wc.lpfnWndProc   = WindowProc;
	g_wc.hInstance     = hInst;
	g_wc.lpszClassName = CLASS_NAME;
	g_wc.hCursor 			 = LoadCursorA(hInst,IDC_ARROW);
	RegisterClassA (&g_wc);



	HWND hwnd = CreateWindowEx(
	    0,                              // Optional window styles.
	    CLASS_NAME,                     // Window class
	    "First Window!",			    // Window text
	    WS_OVERLAPPEDWINDOW,            // Window style

	    // Size and position
	    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

	    NULL,       // Parent window    
	    NULL,       // Menu
	    hInst,  // Instance handle
	    NULL        // Additional application data
	    );

	if (hwnd == NULL)
	{
	    return 1;
	}


	ShowWindow(hwnd, cmdshow);


	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
	
		TranslateMessage(&msg); 
		DispatchMessage(&msg);

	}

	return 0;
}
