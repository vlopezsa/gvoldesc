#include "MainApp.h"

#include "ImgList.h"

#include "resource.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


CMainApp::CMainApp(void)
{
	status   = NULL;
	toolbar  = NULL;
	graphics = NULL;
	stcode   = NULL;
	stcodebg = NULL;
	txtcode  = NULL;
	camera   = NULL;
	model	 = NULL;

	SetWindowLongPtr(GetHWND(), GWLP_USERDATA, (LONG)this);

 	BuildGui();
}

CMainApp::~CMainApp(void)
{
	FREEOBJECT(status);
	FREEOBJECT(toolbar);
	FREEOBJECT(graphics);
	FREEOBJECT(stcode);
	FREEOBJECT(stcodebg);
	FREEOBJECT(txtcode);
	FREEOBJECT(camera);
	FREEOBJECT(model);
}

void CMainApp::BuildGui() {
	INITCOMMONCONTROLSEX icex;

	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);	
	icex.dwICC  = ICC_BAR_CLASSES;
	InitCommonControlsEx(&icex);


	CMenuCtrl m(L"menumain");
	SetMenuEx(m);

	LoadAccel(L"accelmain");

	int statwidths[] = {200, 500, -1};
	status = new CStatusCtrl(this);
	status->CreateControl(SBARS_SIZEGRIP, 4, statwidths);

	CFontCtrl mf(L"Arial", 14);

	toolbar = new CTBarCtrl(this);
	toolbar->CreateControl(CCS_TOP);

	CImgList imglist(24, 24, 6);
	imglist.AddMasked(IDI_OPEN, 0);
	imglist.AddMasked(IDI_SAVE, 0);
	imglist.AddMasked(IDI_DO_CODE, 0);
	imglist.AddMasked(IDI_CONFIG, 0);
	imglist.AddMasked(IDI_SETTINGS, 0);

	toolbar->SetImageList(imglist.GetListHandle());
	toolbar->InsertButton(4, IDM_CODE);
	toolbar->InsertSeparator();
	toolbar->InsertButton(3, IDM_CONF);
	toolbar->InsertSeparator();
	toolbar->InsertButton(1, IDM_SAVE);
	toolbar->InsertButton(0, IDM_OPEN);
	toolbar->AutoSize();

	graphics = new CGraphics(this);
	graphics->CreateControl(SS_BLACKFRAME, 0, 0, 800, 600);
	graphics->SetRelativePosition(true, MWC_RP_RIGHT | MWC_RP_LEFT | MWC_RP_TOP | MWC_RP_BOTTOM, 1, -1, 0, 35, 0, 80);

	camera = new CCamera();
	camera->SetCameraPos(0, 0, -10);

	graphics->SetCamera(camera);

	stcodebg = new CStaticCtrl(this);
	stcodebg->CreateControl(SS_SUNKEN, 0, 0, 800, 60);
	stcodebg->SetRelativePosition(true, MWC_RP_RIGHT | MWC_RP_LEFT | MWC_RP_BOTTOM, 1, -1, 0, 35, 0, 20);
	
	stcode = new CButtonCtrl(this);
	stcode->CreateControl(BS_GROUPBOX, 0, 0, 800, 60);
	stcode->SetRelativePosition(true, MWC_RP_RIGHT | MWC_RP_LEFT | MWC_RP_BOTTOM, -1, -1, 1, 35, 1, 20);
	stcode->SetFont(mf.GetHandle());
	stcode->SetText(L"Chain Descriptor");

	txtcode = new CEditCtrl(this);

	txtcode->CreateControl(ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY, 0, 0, 800, 40);
	txtcode->SetRelativePosition(true, MWC_RP_RIGHT | MWC_RP_LEFT | MWC_RP_BOTTOM, 1, -1, 5, 40, 5, 25);
	txtcode->SetFont(mf.GetHandle());
}

LRESULT CMainApp::WndProc(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(Msg) {
		case WM_CTLCOLORSTATIC:
			OnPaint();
			return FALSE;

		case WM_SIZE:
			OnSize((int)wParam, LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_LBUTTONDOWN:
			camera->MousePressed(MOUSE_LEFT, (int)LOWORD(lParam), (int)HIWORD(lParam));
			break;

		case WM_RBUTTONDOWN:
			camera->MousePressed(MOUSE_RIGHT, (int)LOWORD(lParam), (int)HIWORD(lParam));
			break;

		case WM_LBUTTONUP:
			camera->MouseReleased(MOUSE_LEFT);
			break;

		case WM_RBUTTONUP:
			camera->MouseReleased(MOUSE_RIGHT);
			break;

		case WM_MOUSEMOVE:
			if(camera->MouseMove((int)LOWORD(lParam), (int)HIWORD(lParam)))
				InvalidateRect(GetHWND(), NULL, FALSE);
			break;

		case WM_MOUSEWHEEL:
			if((short)HIWORD(wParam) > 0)
				camera->Zoom(0.3f);
			else
				camera->Zoom(-0.3f);
			InvalidateRect(GetHWND(),  NULL, FALSE);
			break;

		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case IDM_OPEN:
					LoadModel();
					break;
				case IDM_SAVE:
					SaveCode();
					break;
				case IDM_CODE:
					GetCode();
					break;
				case IDM_EXIT:
					PostQuitMessage(0);
					return 0;
			} break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_CLOSE:
			DestroyWindow(GetHWND());
			return 0;

		default:
			return DefWindowProc(GetHWND(), Msg, wParam, lParam);
	}

	return FALSE;
}

int CMainApp::Run() {
	MSG messages;

	while (GetMessage (&messages, NULL, 0, 0))
    {
        if(!TransAccel(&messages))
			TranslateMessage(&messages);
		DispatchMessage(&messages);
    }

	return 0;
}

void CMainApp::OnPaint() {
	graphics->Render();
}

void CMainApp::OnSize(int type, int x, int y) {
	if(toolbar) toolbar->Move();
	if(status) status->Move();
	if(graphics) {graphics->Move(); graphics->Size(); }
	if(stcode) stcode->Move();
	if(stcodebg) stcodebg->Move();
	if(txtcode) txtcode->Move();
}

void CMainApp::SaveCode() {
	const wchar_t * file;
	CFileDlg dlg(this, L"Text files (*.txt)\0*.txt\0\0", NULL, L"txt");

	file = dlg.GetSaveFile();

	if(file!=NULL) {
		wofstream of;

		of.open(file);
		of << txtcode->GetText();
		of.close();
	}
}

void CMainApp::LoadModel() {
	wchar_t skfil[256]={0}, skfilb[64]={0};
	const wchar_t *file;
	int len, i;

	CFileDlg dlg(this, L"OFF Files (*.off)\0*.off\0\0");

	FREEOBJECT(model);

	model = new COffLoader();

	file = dlg.GetOpenFile();

	if(model->FromFile(file) == true) {
		len = wcslen(file);

		for(i=len-1; i>=0; i--) {
			if(file[i]=='\\') break;
		}

		if(i<len) {
			wcsncpy(skfil, file, i);
			wcscat(skfil, L"\\skeleton\\");
			wcscpy(skfilb, file+i+1);
			skfilb[wcslen(skfilb)-4] = 0;
			wcscat(skfil, skfilb);
			wcscat(skfil, L"_unit_skeleton3_clean.off");
		}

		skeleton.LoadFromFile(skfil);
		graphics->DisableLighting();
		graphics->AddRenderList(skeleton.PlotAsLinesOri());

		graphics->SetLightingMode(L_NORMAL);
		//graphics->EnableLighting();
		glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		graphics->AddRenderList(model->DrawModel());

		InvalidateRect(GetHWND(), NULL, FALSE);

		status->SetText(0, skfilb);

		txtcode->SetText(L"");
	}
}

void CMainApp::GetCode() {
	string s;
	wchar_t *ts;
	int i, l;

	if(cTree.CreateFromSkel(skeleton) == true) {
		s = cTree.GetChainCode();
		l = strlen(s.c_str());


		ts = new wchar_t[l+1];
		memset(ts, 0, (l+1)*sizeof(wchar_t));

		for(i=0; i<l; i++) {
			ts[i] = s[i];
		}

		txtcode->SetText(ts);
	}
}