#pragma once

#define _WIN32_WINDOWS 0x501
#define _WIN32_WINNT   0x501

#include <windows.h>
#include <commctrl.h>

#include "resource.h"

#define MWC_RP_TOP	   0x200001
#define MWC_RP_BOTTOM  0x200002
#define MWC_RP_LEFT    0x200004
#define MWC_RP_RIGHT   0x200008
#define MWC_RP_OTOP	   0x200010
#define MWC_RP_OBOTTOM 0x200020
#define MWC_RP_OLEFT   0x200040
#define MWC_RP_ORIGHT  0x200080

class CWinBase;

class CWinBase
{
	HINSTANCE hInst;

	CWinBase * wndParent;

protected:
	HWND hWnd;
	RECT rSize;
	RECT rOffset;

	wchar_t *text;

	bool bKeepProportion;

	float widthRatio, heightRatio;
	
	DWORD relPosition;

public:
	CWinBase(CWinBase * wndParnt=NULL);
	~CWinBase(void);

	const HWND & GetHWND()  { return hWnd; }

	const HINSTANCE & GetInstance() {return hInst; }

	CWinBase * GetParent() { return wndParent; }

	void Enable(BOOL enable);

	void Move(RECT r, BOOL repaint=TRUE);

	void Move(int x, int y, int width, int height, BOOL repaint=TRUE);

	void Move(int x, int y, BOOL repaint=TRUE);

	void Move(BOOL repaint=TRUE);

	void SetText(wchar_t *text);

	wchar_t *GetText();

	void GetCRect(RECT *r);

	void GetWRect(RECT *r);

	DWORD GetStyle();

	void SetStyle(DWORD style);

	DWORD GetStyleEx();

	void SetStyleEx(DWORD style);

	DWORD GetID();

	void SetID(DWORD id);

	void Focus();

	void SetFont(HFONT hFont);

	void SetRelativePosition(bool bKeep, DWORD relPosition = 0, float wRatio=-1.0f, float hRatio=-1.0f,
							 int oleft=0, int otop=0, int oright=0, int obottom=0);
};
