#pragma once

#include "WinBase.h"

class CWinControl : 
	public CWinBase
{
public:
	CWinControl(CWinBase * wndPrnt);
	~CWinControl(void);

	virtual void CreateControl(DWORD style, int x, int y, int width, int height);
};
