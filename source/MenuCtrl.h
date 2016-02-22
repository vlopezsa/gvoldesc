#pragma once

#include <windows.h>

class CMenuCtrl
{
	HMENU hMenu;

public:
	CMenuCtrl(void);
	CMenuCtrl(wchar_t *id);
	~CMenuCtrl(void);

	const HMENU & GetHandle()  { return hMenu; 
	}

	void LoadFromResource(wchar_t *id);

	void AddString(int id, wchar_t *str);

	void AddSeparator();

	void AddPopup(CMenuCtrl &menu, wchar_t *str);
};
