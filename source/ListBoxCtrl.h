#pragma once
#include "wincontrol.h"

#include <string>

using namespace std;

class CListBoxCtrl :
	public CWinControl
{
public:
	CListBoxCtrl(CWinBase * wndPrnt);
	~CListBoxCtrl(void);

	void CreateControl(DWORD style, int x, int y, int width, int height);

	int AddString(const wchar_t * string);
	
	int InsertString(const wchar_t * string);

	int GetCurSel();

	int GetTextLen(int nIdx);

	void GetCurSelString(string &s);

	void Clear();
};
