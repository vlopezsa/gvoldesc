#include <windows.h>

#include "WinControl.h"

CWinControl::CWinControl(CWinBase * wndPrnt) :
	CWinBase(wndPrnt)
{
}

CWinControl::~CWinControl(void)
{
}

void CWinControl::CreateControl(DWORD style, int x, int y, int width, int height) {
	rSize.left   = x;
	rSize.top    = y;
	rSize.right  = width;
	rSize.bottom = height;
}

