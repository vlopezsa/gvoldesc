#pragma once

#include "WinBase.h"

LRESULT CALLBACK gWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

#include "MenuCtrl.h"

class CWinParent :
	public CWinBase
{
	HACCEL hAccel;

public:
	CWinParent(CWinBase * wndParent = NULL, LPCWSTR title = NULL, 
				int w=800, int h=600, DWORD bgColor = COLOR_BACKGROUND);
	~CWinParent();

	void SetMenuEx(CMenuCtrl &menu);

	void LoadAccel(wchar_t * accel);

	int TransAccel(MSG * msg);

	virtual LRESULT WndProc(UINT Msg, WPARAM wParam, LPARAM lParam);

	virtual void OnSize(int type, int width, int height);

	virtual void OnDestroy();

	virtual void OnClose();
};
