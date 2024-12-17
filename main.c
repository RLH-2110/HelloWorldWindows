#include <unistd.h>
#include <windows.h>
#include <Winuser.h>
#include <stdio.h>
/*#include <winutil.h>*/

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
			PostQuitMessage(0);
			return DefWindowProc(hWindow, uMsg, wParam, lParam);
		default:
			return DefWindowProc(hWindow, uMsg, wParam, lParam);
	}
}

/*int __clrcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){*/

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{

	#ifdef CBaseWindow
		puts("CBaseWindow is defined");
	#else
			puts("Not Defined CBaseWindow!");	
	#endif


	puts("winmain");

	// Register the window class.
	const char CLASS_NAME[]  = "Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInst;
	wc.lpszClassName = CLASS_NAME;

	RegisterClassA (&wc);



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

	puts("winmain end");

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
	
		TranslateMessage(&msg); 
		DispatchMessage(&msg);

	}

	MessageBox(NULL, "progamm wird beented", "ende", 0);

	return 0;

}
