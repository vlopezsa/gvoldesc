#pragma once
#include "wincontrol.h"

class CTBarCtrl :
	public CWinControl
{
public:
	CTBarCtrl(CWinBase * wndPrnt);
	~CTBarCtrl(void);

	void CreateControl(DWORD style=0, int x=0, int y=0, int width=0, int height=0);

	LRESULT InsertButton(int iBitmap, int idCmd, BYTE fsStyle = BTNS_BUTTON, BYTE fsState = TBSTATE_ENABLED, int iString = 0, int dwData = 0);

	LRESULT InsertSeparator();

	LRESULT AutoSize();

	LRESULT SetImageList(HIMAGELIST ilist);
};
