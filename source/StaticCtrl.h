#pragma once
#include "wincontrol.h"

class CStaticCtrl :
	public CWinControl
{
public:
	CStaticCtrl(CWinBase * hWnd);
	~CStaticCtrl(void);

	virtual void CreateControl(DWORD style, int x, int y, int width, int height);
};
