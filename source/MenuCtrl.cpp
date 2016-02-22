#include "MenuCtrl.h"

CMenuCtrl::CMenuCtrl(void)
{
	hMenu = CreateMenu();
}

CMenuCtrl::CMenuCtrl(wchar_t *id)
{
	hMenu = LoadMenu((HINSTANCE)GetModuleHandle(NULL), id);
}

CMenuCtrl::~CMenuCtrl(void)
{
}

void CMenuCtrl::AddString(int id, wchar_t *str) {
	AppendMenu(hMenu, MF_STRING, id, str);
}

void CMenuCtrl::AddSeparator() {
	AppendMenu(hMenu, MF_SEPARATOR, NULL, NULL);
}

void CMenuCtrl::AddPopup(CMenuCtrl &menu, wchar_t *str) {
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)menu.GetHandle(), str);
}

void CMenuCtrl::LoadFromResource(wchar_t * id) {
	if(hMenu)
		DestroyMenu(hMenu);

	hMenu = LoadMenu((HINSTANCE)GetModuleHandle(NULL), id);
}
