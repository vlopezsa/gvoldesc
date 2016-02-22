#include "StaticCtrl.h"

CStaticCtrl::CStaticCtrl(CWinBase * hWndP):
	CWinControl(hWndP)
{
}

CStaticCtrl::~CStaticCtrl(void)
{
}

void CStaticCtrl::CreateControl(DWORD style, int x, int y, int width, int height) {
	CWinBase * prnt = GetParent();
	HWND hWndParent = (prnt)? prnt->GetHWND(): NULL;

	hWnd = CreateWindow(L"STATIC", L"", style | WS_VISIBLE | WS_CHILD | WS_BORDER, x, y, width, height, hWndParent,
						NULL, (HINSTANCE)GetModuleHandle(NULL), 0);

	CWinControl::CreateControl(style, x, y, width, height);
}
