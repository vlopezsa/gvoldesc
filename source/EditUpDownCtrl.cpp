#include "EditUpDownCtrl.h"

CEditUpDownCtrl::CEditUpDownCtrl(CWinBase * wndPrnt) :
	CEditCtrl(wndPrnt)
{
}

CEditUpDownCtrl::~CEditUpDownCtrl(void)
{
}

void CEditUpDownCtrl::CreateControl(DWORD style, int x, int y, int width, int height) {
	CWinBase * prnt = GetParent();
	HWND hWndParent = (prnt)? prnt->GetHWND(): NULL;

	CEditCtrl::CreateControl(style, x, y, width, height);

	hWndUD = CreateWindowEx (0L, UPDOWN_CLASS, L"",
						   WS_CHILD | WS_BORDER | WS_VISIBLE | 
						   UDS_ARROWKEYS | UDS_ALIGNRIGHT | UDS_HOTTRACK | UDS_SETBUDDYINT | UDS_NOTHOUSANDS,
						   0, 0, 8, 8, hWndParent, 0, (HINSTANCE)GetModuleHandle(NULL), NULL );

	SendMessage(hWndUD, UDM_SETBUDDY, (LONG)GetHWND(), 0L );
}

void CEditUpDownCtrl::SetRange(int min, int max) {
	SendMessage(hWndUD, UDM_SETRANGE, 0L, MAKELONG(max, min));
}

void CEditUpDownCtrl::SetPosition(int pos) {
	SendMessage(hWndUD, UDM_SETPOS, 0L, MAKELONG( pos, 0));
}
