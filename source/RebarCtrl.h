#pragma once
#include "wincontrol.h"

class CRebarCtrl :
	public CWinControl
{
public:
	CRebarCtrl(CWinBase * wndParent);
	~CRebarCtrl(void);

	void CreateControl(DWORD style, int x=0, int y=0, int width=0, int height=0);

	void InsertBand(CWinBase * wnd, int cx = 100, int style = RBBS_CHILDEDGE | RBBS_NOGRIPPER,
					int mask = RBBIM_COLORS | RBBIM_STYLE | RBBIM_CHILD  | RBBIM_CHILDSIZE | RBBIM_SIZE,
					int cxMin = 0, int cyMin = 24);
};
