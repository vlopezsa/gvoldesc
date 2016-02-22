#include "ListBoxCtrl.h"

CListBoxCtrl::CListBoxCtrl(CWinBase * wndPrnt)
	: CWinControl(wndPrnt)
{
}

CListBoxCtrl::~CListBoxCtrl(void)
{
}

void CListBoxCtrl::CreateControl(DWORD style, int x, int y, int width, int height) {
	CWinBase * prnt = GetParent();
	HWND hWndParent = (prnt)? prnt->GetHWND(): NULL;

	hWnd = CreateWindow(L"LISTBOX", L"", style | WS_VISIBLE | WS_CHILD | WS_BORDER, x, y, width, height, hWndParent,
						NULL, (HINSTANCE)GetModuleHandle(NULL), 0);

	CWinControl::CreateControl(style, x, y, width, height);
}

int CListBoxCtrl::AddString(const wchar_t *string) {
	return SendMessage(GetHWND(), LB_ADDSTRING, NULL, (LPARAM)string);
}

int CListBoxCtrl::InsertString(const wchar_t *string) {
	return SendMessage(GetHWND(), LB_INSERTSTRING, NULL, (LPARAM)string);
}

void CListBoxCtrl::Clear() {
	SendMessage(GetHWND(), LB_RESETCONTENT, NULL, NULL);
}

int CListBoxCtrl::GetCurSel() {
	return SendMessage(GetHWND(), LB_GETCURSEL, 0, 0);
}

int CListBoxCtrl::GetTextLen(int nIdx) {
	if(nIdx < 0)
		return -1;

	return SendMessage(GetHWND(), LB_GETTEXTLEN, (WPARAM)nIdx, 0);
}

void CListBoxCtrl::GetCurSelString(string &s) {
	int n = GetCurSel();
	int l;
	char * sf;

	if(n < 0) {
		s.clear();
		return;
	}

	l = GetTextLen(n);

	if(l<=0) {
		s.clear();
		return;
	}

	sf = new char[l+1];

	SendMessage(GetHWND(), LB_GETTEXT, (WPARAM)n, (LPARAM)sf);

	s.clear();

	s = string(sf);

	delete sf;
}
