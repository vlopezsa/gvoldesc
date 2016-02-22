#include <windows.h>

#include "MainApp.h"

CMainApp * gMainApp;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lstr, int nShow) {
	gMainApp = new CMainApp();

	gMainApp->SetText(L"Volume Descriptor");

	return gMainApp->Run();
}
