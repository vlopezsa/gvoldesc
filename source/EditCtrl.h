#pragma once
#include "wincontrol.h"

class CEditCtrl :
	public CWinControl
{
public:
	CEditCtrl(CWinBase * wndPrnt);
	~CEditCtrl(void);

	void CreateControl(DWORD style, int x, int y, int width, int height);
};
