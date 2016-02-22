#pragma once
#include "wincontrol.h"

class CStatusCtrl :
	public CWinControl
{
public:
	CStatusCtrl(CWinBase * wndPrnt);
	~CStatusCtrl(void);

	void CreateControl(DWORD style, int x, int y, int width, int height);

	void CreateControl(DWORD style, int parts, int *widths);

	void SetParts(int parts, int *widths);

	void SetText(int part, wchar_t *text);
};
