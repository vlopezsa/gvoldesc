#pragma once
#include "editctrl.h"

class CEditUpDownCtrl :
	public CEditCtrl
{
	HWND hWndUD;

public:
	CEditUpDownCtrl(CWinBase * wndPrnt);
	~CEditUpDownCtrl(void);

	virtual void CreateControl(DWORD style, int x, int y, int width, int height);

	void SetRange(int min, int max);

	void SetPosition(int pos);
};
