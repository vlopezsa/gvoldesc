#pragma once

#include "winbase.h"

class CFontCtrl
{
private:
	HFONT hFont;

public:
	CFontCtrl(wchar_t * family = NULL, int height=10, int width=0, int weight=FW_NORMAL, 
			  BYTE italic=FALSE, BYTE underline=FALSE, BYTE quality=ANTIALIASED_QUALITY, BYTE strikeout=FALSE,
			  int orientation=0, int escapement=0,
			  BYTE charset=DEFAULT_CHARSET, BYTE outprecision=OUT_DEFAULT_PRECIS, BYTE clipprecision=CLIP_DEFAULT_PRECIS,
			  BYTE pitchandfamily=FF_DONTCARE);
	~CFontCtrl(void);

	const HFONT & GetHandle() {return hFont; }
};
