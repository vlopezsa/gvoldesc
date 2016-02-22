#include "ImgList.h"

CImgList::CImgList(int cx, int cy, int nElem)
{
	himlIcons = ImageList_Create(cx, cy, ILC_MASK | ILC_COLOR24, nElem, 0); 
}

CImgList::~CImgList(void)
{
}

int CImgList::AddIcon(int id) {
	HICON hIcon;

	hIcon = LoadIcon((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(id));

	if(hIcon)
		return ImageList_AddIcon(himlIcons, hIcon);
	else
		return -1;
}

int CImgList::AddMasked(int id, COLORREF mask) {
	HBITMAP hm;

	hm = LoadBitmap((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(id));

	if(hm)
		return ImageList_AddMasked(himlIcons, hm, mask);
	else
		return -1;
}