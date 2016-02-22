#pragma once
#include "wincontrol.h"

class CButtonCtrl :
	public CWinControl
{
public:
	CButtonCtrl(CWinBase * wndPrnt);
	~CButtonCtrl(void);

	void CreateControl(DWORD style, int x, int y, int width, int height);
};
