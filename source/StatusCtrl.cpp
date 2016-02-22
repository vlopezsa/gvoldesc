#include "StatusCtrl.h"

#include <stdio.h>
#include <stdlib.h>

CStatusCtrl::CStatusCtrl(CWinBase * wndPrnt) :
	CWinControl(wndPrnt)
{
}

CStatusCtrl::~CStatusCtrl(void)
{
}

void CStatusCtrl::CreateControl(DWORD style, int x, int y, int width, int height) {
	int widths[] = {-1};
	CreateControl(style, 1, widths);
}

void CStatusCtrl::CreateControl(DWORD style, int parts, int *widths) {
	CWinBase * prnt = GetParent();
	HWND hWndParent = (prnt)? prnt->GetHWND(): NULL;

	hWnd = CreateWindow(STATUSCLASSNAME, NULL,
					    style | WS_CHILD | WS_VISIBLE,
							0, 0, 0, 0, hWndParent, NULL, (HINSTANCE)GetModuleHandle(NULL), NULL);

	SetParts(parts, widths);

	CWinControl::CreateControl(style, 0, 0, 0, 10);
}

void CStatusCtrl::SetParts(int parts, int *widths) {
	SendMessage(hWnd, SB_SETPARTS, (WPARAM)parts, (LPARAM)widths);
}

void CStatusCtrl::SetText(int part, wchar_t *str) {
	SendMessage(hWnd, SB_SETTEXT, (WPARAM)part, (LPARAM)str);
}
