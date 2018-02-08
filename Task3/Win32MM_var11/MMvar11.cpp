#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);

#define _USE_MATH_DEFINES
#include <math.h>
LPSTR lpstr;
HINSTANCE hInst;
int stepCounter = 0;
int buff = 0;
char buffer[33];
RECT rcClient;
HDC hdc;

void OnTimer(HWND hWnd, UINT id) {

	int limit = 40;
	static int counter = limit;
	stepCounter += 5;
	InvalidateRect(hWnd, NULL, TRUE);
	buff = counter;
	counter--;

	if (!counter) {
		KillTimer(hWnd, id);
	}
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct) {

	const int period = 100; // 100 millisecond for smooth animation
	SetTimer(hWnd, 1, period, NULL);

	return TRUE;
}



void OnPaint(HWND hWnd) {
	
	RECT rect;
	GetWindowRect(hWnd, &rect);

	 int x1 = (int)((rect.right / 2)-160);
	 int y1 = (int)((rect.bottom / 2)-100);
	 int x2 = (int)(x1 + 200);
	 int y2 = (int)(y1 );

	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(hWnd, &ps);
	HPEN pen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	x2 = (int)(x1 + stepCounter);
	y2 = (int)(y1);

	pen = CreatePen(PS_SOLID, 10, RGB(0, 0, 255));
	oldPen = (HPEN)SelectObject(hdc, pen);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	SelectObject(hdc, oldPen);
	EndPaint(hWnd, &ps);
}

void cOnPaint(HWND child) {
	RECT rcClient;
	_itoa_s(buff, buffer, 10);
	LPCSTR lpstr = buffer;
	GetClientRect(child, &rcClient);
	const int cx = (int)(rcClient.left / 2);
	const int cy = (int)(rcClient.bottom / 2);
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(child, &ps);
	SelectObject(hdc, NULL);
	SetTextColor(hdc, RGB(0, 0, 150));
	TextOutA(hdc, cx, cy, lpstr, 2);
	EndPaint(child, &ps);
}

void OnDestroy(HWND hWnd) {
	PostQuitMessage(0);
}

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
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(187, 187, 187));
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
		500, 500,
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

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

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
	cwcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(187, 100, 50));
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
		WS_CHILD | WS_BORDER | WS_VISIBLE, 250, 100,
		30, 30, hWnd, NULL, hInst, NULL);
	ShowWindow(child, SW_NORMAL);
	UpdateWindow(child);

	//The parameters to ShowWindow explained:
	//hWnd: the value returned from CreateWindow
	//nCmdShow: the fourth parameter from WinMain

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
