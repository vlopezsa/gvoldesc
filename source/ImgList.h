#pragma once

#include "WinBase.h"

class CImgList
{
private:
	HIMAGELIST himlIcons;

public:
	CImgList(int cx=24, int cy=24, int nElem = 1);
	~CImgList(void);

	int AddIcon(int id);

	int AddMasked(int id, COLORREF mask);

	const HIMAGELIST & GetListHandle() {return himlIcons;}
};
