#pragma once
#include "staticctrl.h"

#include "camera.h"
#include <vector>

#include <gl/gl.h>
#include <gl/glu.h>

#define L_WIRED	 0
#define L_NORMAL 1

#define GLIST_LINE	 1
#define GLIST_TUBE   2
#define GLIST_SPHERE 3
#define GLIST_TUBEX  4
#define GLIST_TUBEY  5
#define GLIST_TUBEZ  6
#define GLIST_SKEL   7
#define GLIST_LINED  8

#define GLIST_MAXN   8

using namespace std;
class CGraphics :
	public CStaticCtrl
{
	HDC hDC;
	HGLRC hRC;

	CCamera * cam;

	vector<int> gList;

private:
	int InitAll();

	void EndAll();

public:
	CGraphics(CWinBase * wndPrnt);
	~CGraphics(void);

	void SetCamera(CCamera * camera);
	
	void CreateControl(DWORD style, int x, int y, int width, int height);

	void Size();

	void Render();

	void AddRenderList(int list);

	void SetCurrent() const {wglMakeCurrent(hDC,hRC);};

	void RemoveRenderList(int list);

	void DisableLighting();

	void EnableLighting();

	void SetLightingMode(int mode = L_NORMAL); 
};
