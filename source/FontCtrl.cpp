#include "FontCtrl.h"

CFontCtrl::CFontCtrl(wchar_t * family, int height, int width, int weight,  BYTE italic, BYTE underline, BYTE quality, BYTE strikeout,
			  int orientation, int escapement, BYTE charset, BYTE outprecision, BYTE clipprecision, BYTE pitchandfamily)
{
	LOGFONT lf = {0};

	lf.lfHeight			= height;
	lf.lfWidth			= width; 
	lf.lfEscapement		= escapement; 
	lf.lfOrientation	= orientation; 
	lf.lfWeight			= weight; 
	lf.lfItalic			= italic; 
	lf.lfUnderline		= underline; 
	lf.lfStrikeOut		= strikeout; 
	lf.lfCharSet		= charset; 
	lf.lfOutPrecision	= outprecision; 
	lf.lfClipPrecision	= clipprecision; 
	lf.lfQuality		= quality; 
	lf.lfPitchAndFamily	= pitchandfamily; 

	if(family)
		wcscpy_s(lf.lfFaceName, family);

	hFont = CreateFontIndirect(&lf);
}

CFontCtrl::~CFontCtrl(void)
{
}
