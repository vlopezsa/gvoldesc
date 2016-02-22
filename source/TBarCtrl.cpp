#include "TBarCtrl.h"

CTBarCtrl::CTBarCtrl(CWinBase * wndPrnt)
	: CWinControl(wndPrnt)
{
}

CTBarCtrl::~CTBarCtrl(void)
{
}

void CTBarCtrl::CreateControl(DWORD style, int x, int y, int width, int height) {
	CWinBase * prnt = GetParent();
	HWND hWndParent = (prnt)? prnt->GetHWND(): NULL;

	hWnd = CreateWindow(TOOLBARCLASSNAME, 0, style | WS_VISIBLE | WS_CHILD, x, y, width, height, hWndParent,
						(HMENU)0x3000, (HINSTANCE)GetModuleHandle(NULL), 0);

	CWinControl::CreateControl(style, x, y, width, height);

	SendMessage(hWnd, TB_BUTTONSTRUCTSIZE, (WPARAM) sizeof(TBBUTTON), 0); 
}

LRESULT CTBarCtrl::InsertButton(int iBitmap, int idCmd, BYTE fsStyle, BYTE fsState, int iString, int dwData) {
	TBBUTTON tbb;

	tbb.iBitmap   = iBitmap; 
	tbb.idCommand = idCmd; 
	tbb.fsState   = fsState; 
	tbb.fsStyle	  = fsStyle; 
	tbb.dwData    = dwData; 
	tbb.iString   = iString; 

	return SendMessage(GetHWND(), TB_INSERTBUTTON, (WPARAM)0, (LPARAM)&tbb);
}

LRESULT CTBarCtrl::InsertSeparator() {
	return InsertButton(0, 0, BTNS_SEP);
}

LRESULT CTBarCtrl::AutoSize() {
	return SendMessage(GetHWND(), TB_AUTOSIZE, 0, 0);
}

LRESULT CTBarCtrl::SetImageList(HIMAGELIST ilist) {
	return SendMessage(GetHWND(), TB_SETIMAGELIST, 0, (LPARAM)ilist);
}
