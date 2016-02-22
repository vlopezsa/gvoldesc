#include <windows.h>
#include "EditCtrl.h"

CEditCtrl::CEditCtrl(CWinBase * wndPrnt) :
	CWinControl(wndPrnt)
{
}

CEditCtrl::~CEditCtrl(void)
{
}

void CEditCtrl::CreateControl(DWORD style, int x, int y, int width, int height) {
	CWinBase * prnt = GetParent();
	HWND hWndParent = (prnt)? prnt->GetHWND(): NULL;

	hWnd = CreateWindow(L"EDIT", L"", style | WS_VISIBLE | WS_CHILD | WS_BORDER, x, y, width, height, hWndParent,
						NULL, (HINSTANCE)GetModuleHandle(NULL), 0);

	CWinControl::CreateControl(style, x, y, width, height);
}
