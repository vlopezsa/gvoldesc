#include "WinBase.h"

CWinBase::CWinBase(CWinBase * wndPrnt) {
	wndParent = wndPrnt;

	ZeroMemory(&rSize,   sizeof(RECT));
	ZeroMemory(&rOffset, sizeof(RECT));
	
	text = NULL;

	widthRatio  = -1;
	heightRatio = -1;
	bKeepProportion = false;
	relPosition = 0;

	if(wndPrnt == NULL)
		hInst = GetModuleHandle(NULL);
	else
		hInst = wndParent->GetInstance();
}

CWinBase::~CWinBase(void)
{
	if(text) {
		delete [] text;
		text = NULL;
	}
}

void CWinBase::Enable(BOOL enable) {
	EnableWindow(hWnd, enable);
}

void CWinBase::Move(RECT r, BOOL repaint) {
	MoveWindow(hWnd, r.left, r.top, r.right, r.bottom, repaint);

	rSize = r;
}

void CWinBase::Move(int x, int y, int width, int height, BOOL repaint) {
	MoveWindow(hWnd, x, y, width, height, repaint);

	rSize.left   = x;
	rSize.right  = width;
	rSize.top    = y;
	rSize.bottom = height;
}

void CWinBase::Move(int x, int y, BOOL repaint) {
	RECT rp, rf;

	if(bKeepProportion==true && wndParent!=NULL) {
		int w=0, h=0;

		wndParent->GetCRect(&rp);

		if(widthRatio >= 0.0f && widthRatio <= 1.0f)
			w = (int)(rp.right * widthRatio);
		else
			w = rSize.right;

		if(heightRatio >= 0.0f && heightRatio <= 1.0f)
			h = (int)(rp.bottom * heightRatio);
		else
			h = rSize.bottom;

		if((relPosition & MWC_RP_TOP) == MWC_RP_TOP)
			rf.top = rOffset.top;
		else
			rf.top = -1;

		if((relPosition & MWC_RP_LEFT) == MWC_RP_LEFT)
			rf.left = rOffset.left;
		else
			rf.left = -1;

		if((relPosition & MWC_RP_BOTTOM) == MWC_RP_BOTTOM)
			rf.bottom = rp.bottom - rOffset.bottom;
		else
			rf.bottom = -1;

		if((relPosition & MWC_RP_RIGHT) == MWC_RP_RIGHT)
			rf.right = rp.right - rOffset.right;
		else
			rf.right = -1;

		x = (rf.left>=0)   ? rf.left   : (rf.right>=0) ? rf.right - w  : x;
		y = (rf.top>=0)    ? rf.top    : (rf.bottom>=0)? rf.bottom - h : y;
		w = (rf.right>=0)  ? rf.right  - x : w;
		h = (rf.bottom>=0) ? rf.bottom - y : h;

		Move(x, y, w, h, repaint);
	} else {
		Move(x, y, rSize.right, rSize.bottom, repaint);
	}
}

void CWinBase::Move(BOOL repaint) {
	Move(rSize.left, rSize.top, repaint);
}

void CWinBase::SetText(wchar_t *text) {
	if(text == NULL || !IsWindow(hWnd))
		return;

	SetWindowText(hWnd, text);
}

wchar_t * CWinBase::GetText() {
	int lenght;

	if(!IsWindow(hWnd))
		return NULL;

	lenght = GetWindowTextLength(hWnd);
	lenght ++;

	if(text) {
		delete [] text;
	}

	text = new wchar_t[lenght];
	memset(text, 0, lenght);

	GetWindowText(hWnd, text, lenght);

	return text;
}

void CWinBase::GetCRect(RECT *r) {
	GetClientRect(hWnd, r);
}

void CWinBase::GetWRect(RECT *r) {
	GetWindowRect(hWnd, r);
}

DWORD CWinBase::GetStyle() {
	return (DWORD)GetWindowLong(hWnd, GWL_STYLE);
}

void CWinBase::SetStyle(DWORD style) {
	SetWindowLong(hWnd, GWL_EXSTYLE, (LONG)style);
}

DWORD CWinBase::GetStyleEx() {
	return (DWORD)GetWindowLong(hWnd, GWL_STYLE);
}

void CWinBase::SetStyleEx(DWORD style) {
	SetWindowLong(hWnd, GWL_EXSTYLE, (LONG)style);
}

DWORD CWinBase::GetID() {
	return (DWORD)GetWindowLong(hWnd, GWL_ID);
}

void CWinBase::SetID(DWORD id) {
	SetWindowLong(hWnd, GWL_ID, id);
}

void CWinBase::Focus() {
	SetFocus(hWnd);
}

void CWinBase::SetRelativePosition(bool bKeep, DWORD relPos, float wRatio, float hRatio,
								   int oleft, int otop, int oright, int obottom) {
	bKeepProportion = bKeep;

	widthRatio  = wRatio;
	heightRatio = hRatio;

	relPosition = relPos;

	rOffset.left   = (oleft>0)  ? oleft  : 0;
	rOffset.top    = (otop>0)   ? otop   : 0;
	rOffset.right  = (oright>0) ? oright : 0;
	rOffset.bottom = (obottom>0)? obottom: 0;

	Move();
}

void CWinBase::SetFont(HFONT hFont) {
	SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, (LPARAM)0);
}
