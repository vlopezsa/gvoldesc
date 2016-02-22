#pragma once

#include "WinParent.h"

#include "MenuCtrl.h"
#include "StatusCtrl.h"
#include "TBarCtrl.h"
#include "Graphics.h"
#include "ButtonCtrl.h"
#include "StaticCtrl.h"
#include "EditCtrl.h"
#include "FontCtrl.h"
#include "FileDlg.h"
#include "Camera.h"
#include "OffLoader.h"
#include "Skeleton.h"
#include "ChainTree.h"

#define FREEOBJECT(o) {\
	if(o) {\
		delete o;\
	}\
	o = NULL;\
}

class CMainApp : 
	public CWinParent
{
private:
	CStatusCtrl		* status;
	CTBarCtrl		* toolbar;
	CGraphics		* graphics;
	CCamera			* camera;
	CStaticCtrl		* stcodebg;
	CButtonCtrl		* stcode;
	CEditCtrl		* txtcode;
	COffLoader		* model;
	CSkeleton		  skeleton;
	CChainTree		  cTree;

public:
	CMainApp(void);
	~CMainApp(void);

	LRESULT WndProc(UINT Msg, WPARAM wParam, LPARAM lParam);

	void BuildGui();

	int Run();

	void LoadModel();

	void GetCode();

	void SaveCode();

	void OnSize(int type, int width, int height);

	void OnPaint();

};
