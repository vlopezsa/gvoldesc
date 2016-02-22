#include "RebarCtrl.h"

CRebarCtrl::CRebarCtrl(CWinBase * wndParent) :
	CWinControl(wndParent)
{
}

CRebarCtrl::~CRebarCtrl(void)
{
}

void CRebarCtrl::CreateControl(DWORD style, int x, int y, int width, int height) {
	REBARINFO	  rbi;
	CWinBase * prnt = GetParent();
	HWND hWndParent = (prnt)? prnt->GetHWND(): NULL;

	hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, REBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | style,
                           0,0,0,0, hWndParent, NULL, (HINSTANCE)GetModuleHandle(NULL), NULL);

	rbi.cbSize = sizeof(REBARINFO);
	rbi.fMask  = 0;
	rbi.himl   = (HIMAGELIST)NULL;
	
	SendMessage(hWnd, RB_SETBARINFO, 0, (LPARAM)&rbi);

	CWinControl::CreateControl(style, x, y, width, height);
}

void CRebarCtrl::InsertBand(CWinBase * wnd, int cx, int style, int mask, int cxMin, int cyMin) {
	REBARBANDINFO rbBand;

	rbBand.cbSize = sizeof(REBARBANDINFO);
	rbBand.fMask  = mask;
	rbBand.fStyle = style;
	rbBand.hwndChild  = wnd->GetHWND();
	rbBand.cxMinChild = cxMin;
	rbBand.cyMinChild = cyMin;
	rbBand.cx         = cx;
	rbBand.clrBack	  = GetSysColor(COLOR_MENUBAR);
   
	SendMessage(hWnd, RB_INSERTBAND, (WPARAM)-1, (LPARAM)&rbBand);
}
