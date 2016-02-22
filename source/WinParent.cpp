#include "WinParent.h"
#include <string>
#include <sstream>

LRESULT CALLBACK gWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	CWinParent * app;

	app = (CWinParent *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if(app)
		return app->WndProc(Msg, wParam, lParam);
	else
		return DefWindowProc(hWnd, Msg, wParam, lParam);
}

CWinParent::CWinParent(CWinBase * wndPrnt, LPCWSTR title, int w, int h, DWORD bgColor) :
	CWinBase(wndPrnt)
{
	WNDCLASS wc;
	CWinBase * prnt = GetParent();
	std::wostringstream strCls;
	std::wstring str1;

	strCls << L"clsMWC" << GetTickCount();

	str1 = strCls.str();

	memset(&wc, 0, sizeof(wc));

	wc.style	     = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = gWndProc;
	wc.hInstance	 = GetInstance();
	wc.lpszClassName = str1.c_str();
	wc.hbrBackground = (HBRUSH)bgColor;
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.cbWndExtra    = 4;

	if(!RegisterClass(&wc)) {
		throw "Imposible registrar la clase";
	}

	if(!prnt)
		hWnd = CreateWindow(str1.c_str(), title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
						w, h, NULL, NULL, GetInstance(), 0);
	else
		hWnd = CreateWindow(str1.c_str(), NULL, WS_CHILD | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
						w, h, prnt->GetHWND(), NULL, GetInstance(), 0);

	if(hWnd == NULL) {
		throw "Imposiblre crear la ventana";
	}

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	GetClientRect(GetHWND(), &rSize);

	hAccel = NULL;
}

CWinParent::~CWinParent(void)
{
}

void CWinParent::LoadAccel(wchar_t * accel) {
	hAccel = LoadAccelerators(GetInstance(), accel);
}

int CWinParent::TransAccel(MSG * msg) {
	if(hAccel == NULL)
		return 0;
	else
		return TranslateAccelerator(GetHWND(), hAccel, msg);
}

void CWinParent::OnSize(int type, int width, int height) {
}

void CWinParent::SetMenuEx(CMenuCtrl &menu) {
	SetMenu(hWnd, menu.GetHandle());
}

void CWinParent::OnDestroy() {
	PostQuitMessage(0);
}

void CWinParent::OnClose() {
	DestroyWindow(hWnd);
}

LRESULT CWinParent::WndProc(UINT Msg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}
