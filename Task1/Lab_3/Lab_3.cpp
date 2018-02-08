#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;
int movementIncrementor = 0;
int buff = 0;
char buffer[33];
RECT rcClient;
PAINTSTRUCT ps;

void OnTimer(HWND hWnd, UINT id) {

	GetClientRect(hWnd, &rcClient);                     //Retrieving the coordinates of a window's client area.
	movementIncrementor += 4;							// Incrementing value for moving symbol right every 4 pixels
	static int counter = rcClient.right / movementIncrementor - 2; //Setting the limit value	
	InvalidateRect(hWnd, &rcClient, TRUE);				// Setting redrawing
	buff = counter; 
	counter--;

	if (!counter) {										// Killing timer condition
		KillTimer(hWnd, id);
	}
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct) {	

	const int period = 10;                             // Frequancy  = 10 Hz , which means 100 milisecond period
	SetTimer(hWnd, 1, period, NULL);                    // Timer setting
	return TRUE;
}



void OnPaint(HWND hWnd) {
	
	LPCSTR lpstr = "F";                                 // Symbol which will be drawn
	GetClientRect(hWnd, &rcClient);						//Retrieves the coordinates of a window's client area.
	const int x1 = (int)(rcClient.left);				//X coord for start position
	const int y1 = (int)(rcClient.bottom / 2);			//Y coord
	int x2 = (int)(x1 + movementIncrementor);			// dynamic coord for moving symbol every 4 pixels

	HDC hdc = BeginPaint(hWnd, &ps);					//Preparing window to painting
	MoveToEx(hdc, x1, y1, NULL);						//start position 
	SetBkMode(hdc, TRANSPARENT);						// Setting symbol`s background color to window bckgrnd color
	SetTextColor(hdc, RGB(0, 43, 255));					// Color of the symbol will be blue
	TextOutA(hdc, x2, y1, lpstr, 1);					// Symbol outputting
	EndPaint(hWnd, &ps);
}

void cOnPaint(HWND child) {
	_itoa_s(buff, buffer, 10);							//converts an integer to a string
	LPCSTR lpstr = buffer;								//Assigning  buffer value to lpstr string
	GetClientRect(child, &rcClient);
	const int cx = (int)(rcClient.left/2);				// Coordinates of the center 
	const int cy = (int)(rcClient.bottom / 2);			// of the child window
	HDC hdc = BeginPaint(child, &ps);
	SetBkMode(hdc, TRANSPARENT);						
	SetTextColor(hdc, RGB(0, 0, 0));					
	TextOutA(hdc, cx, cy, lpstr, 3);					
	EndPaint(child, &ps);
}

void OnDestroy(HWND hWnd) {
	PostQuitMessage(0);
}
// An application - defined function that processes messages sent to a  main window.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_TIMER, OnTimer);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); // default handler
	}
	return 0;
}
// An application - defined function that processes messages sent to a  child window.
LRESULT CALLBACK ChildProc(HWND child, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message) {
		
		HANDLE_MSG(child, WM_PAINT, cOnPaint);
		HANDLE_MSG(child, WM_DESTROY, OnDestroy);
	
	default:
		return DefWindowProc(child, message, wparam, lparam); // default handler
	}
	return 0;	
}


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	static TCHAR szWindowClass[] = _T("win32app");
	static TCHAR szTitle[] = _T("Лабораторна робота #2");

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);
		return 1;
	}



	hInstance = hInstance; // Store instance handle in our global variable

						   //The parameters to CreateWindow explained:
						   //szWindowClass: the name of the application
						   //szTitle: the tex that appears in the title bar
						   //WS_OVERLAPPEDWINDOW: the type of window to create
						   //CW_USEDEFAULT,CW_USEDEFAULT: initial position(x,y)
						   //500,100: initial size(width,length)
						   //NULL:the parent of this window
						   //NULL:this application does not have a menu bar
						   //hInstance: the first parameter from WinMain
						   //NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1280, 300,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);
		return 1;
	}

	

	static TCHAR cszWindowClass[] = _T("Childwin32app");
	static TCHAR cszTitle[] = _T("Лабораторна робота #3");

	WNDCLASSEX cwcex;

	cwcex.cbSize = sizeof(WNDCLASSEX);
	cwcex.style = CS_HREDRAW | CS_VREDRAW;
	cwcex.lpfnWndProc = ChildProc;
	cwcex.cbClsExtra = 0;
	cwcex.cbWndExtra = 0;
	cwcex.hInstance = hInst;
	cwcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPLICATION));
	cwcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	cwcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(50, 200, 0));
	cwcex.lpszMenuName = NULL;
	cwcex.lpszClassName = cszWindowClass;
	cwcex.hIconSm = NULL;

	if (!RegisterClassEx(&cwcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);
		return 1;
	}

	HWND child = CreateWindowEx(0, cszWindowClass, (LPCTSTR)NULL,
		WS_CHILD | WS_BORDER | WS_VISIBLE, 50, 50,
		50, 50, hWnd, NULL, hInst, NULL);
	ShowWindow(child, SW_NORMAL);
	UpdateWindow(child);

	//The parameters to ShowWindow explained:
	//hWnd: the value returned from CreateWindow
	//nCmdShow: the fourth parameter from WinMain

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
