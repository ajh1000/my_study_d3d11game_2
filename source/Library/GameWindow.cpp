#include "pch.h"
#include "GameWindow.h"


GameWindow::GameWindow()
{
}

GameWindow::~GameWindow()
{
	//delete user vars
	m_mapBind.clear();
}


void GameWindow::init(UINT width, UINT height)
{
	m_hInst = GetModuleHandle(NULL);
	UINT windowStyle = WS_OVERLAPPEDWINDOW;

	WNDCLASS wincl = {};
	wincl.hInstance = m_hInst;
	wincl.lpszClassName = "GameAppClass";
	wincl.lpfnWndProc = WindowProc;
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	RegisterClass(&wincl);

	//setting center position and adjust window rect
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	RECT wr = { 0,0,static_cast<LONG>(width) , static_cast<LONG>(height) };
	AdjustWindowRect(&wr, windowStyle, FALSE);
	wr.right -= wr.left;
	wr.bottom -= wr.top;

	int centerX = static_cast<int>((ScreenX*0.5f) - (wr.right*0.5f));
	int centerY = static_cast<int>((ScreenY*0.5f) - (wr.bottom *0.5f));

	//init user vars before wndproc
	m_mapBind.clear();

	//create window
	m_hWnd = CreateWindow(wincl.lpszClassName, "direct11", WS_VISIBLE | windowStyle,
		centerX, centerY, wr.right, wr.bottom, 0, 0, 0, this);
}

void GameWindow::AddFuncToMsg(DWORD msg, BINDTYPE func)
{
	m_mapBind[msg].push_back(func);
}

LRESULT GameWindow::CustomMsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	

		for (auto o : m_mapBind) {
			for (auto func : o.second) {
				func(message, wParam, lParam);
			}
		}
	
	

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(S_OK);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


LRESULT GameWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	GameWindow* pThis = ((GameWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (WM_NCCREATE == uMsg)
	{
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
	}

	if (pThis == nullptr)
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return pThis->CustomMsgProc(hwnd, uMsg, wParam, lParam);
}
