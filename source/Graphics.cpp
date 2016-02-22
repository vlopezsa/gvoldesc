#include "Graphics.h"

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

CGraphics::CGraphics(CWinBase * wndPrnt) :
	CStaticCtrl(wndPrnt)
{
	hRC = NULL;

	cam = NULL;

	gList.empty();
}

CGraphics::~CGraphics(void)
{
	glDeleteLists(1, 64);
	EndAll();
}

void CGraphics::CreateControl(DWORD style, int x, int y, int width, int height) {
	CStaticCtrl::CreateControl(style, x, y, width, height);

	InitAll();
}

int CGraphics::InitAll() {
	GLuint PixelFormat; //Contiene el formato de pixel

	static PIXELFORMATDESCRIPTOR pfd= //Contiene la informacion del formato del pixel
	{
		sizeof(PIXELFORMATDESCRIPTOR), //Tamaño de este descriptor
			1,
			PFD_DRAW_TO_WINDOW | //Formato que soporte Windows
			PFD_SUPPORT_OPENGL | //Formato que soporte OpenGL
			PFD_DOUBLEBUFFER, //Soporta doble buffering
			PFD_TYPE_RGBA, //Peticion de un formato RGBA
			16, // Selecciona el color de la profundidad
			0, 0, 0, 0, 0, 0, //Bits de Color Ignorado
			0, // No Alpha Buffer
			0, // Shift Bit Ignorado
			0, // Buffer de no acumulacion
			0, 0, 0, 0, //Bits de acumulacion ignorados
			16, //16bit Z Buffer (Buffer de profundidad)
			0, //No Stencil Buffer
			0, //No Auxiliary Buffer
			PFD_MAIN_PLANE, //Capa principal de dibujo
			0, //Reservado
			0,0,0 //Mascaras de capa ignoradas
	};

	if (!(hDC=GetDC(GetHWND()))) { //Se obtuvo un contexto de dispositivo?
		MessageBox(NULL, L"It couldn't get window Context", L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;
	}

	if(!(PixelFormat=ChoosePixelFormat(hDC,&pfd))) {//Windows encontro un formato de pixel similar?
		MessageBox(NULL, L"Non suitable pixel format found", L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd)) {//Se pudo iniciar el formato de pixel?
		MessageBox(NULL, L"It couldn't set pixel format", L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;
	}

	if(!(hRC=wglCreateContext(hDC))) {//Conseguimos el contexto para renderear?
		MessageBox(NULL, L"It was not possible to create GL Context", L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;
	}

	if(!wglMakeCurrent(hDC,hRC)) {//Intento de activar el contexto de rendering
		MessageBox(NULL, L"It was not possible to set current GL Context", L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;
	}

	GLfloat blanco[]= {1.0f,1.0f,1.0f,1.0f};
	//GLfloat LightPosition[]={220.0f,-200.0f,220.0f,1.0f};


	glEnable(GL_LINE_SMOOTH);
	glEnable (GL_LIGHTING);
	glEnable (GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	// Buffer de profundidad 
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST); //Habilida la prueba de profundidad
	
	glDepthFunc(GL_LEQUAL); // Tipo de prueba

	glEnable(GL_NORMALIZE);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //Mejora la perspectiva

	glClearColor(1.0f, 1.0f, 1.0f, 0); //Pone el color del fondo a gris	

	glLightfv(GL_LIGHT0, GL_DIFFUSE, blanco);
	glEnable (GL_LIGHT0);

	Size();

	return 0;
}

void CGraphics::EndAll() {
	if (hRC) {
		if(!wglMakeCurrent(NULL,NULL)) // ¿Se pudo liberar los contextos DC y RC?
			MessageBox(NULL, L"Drawing context failed to freed", L"ERROR",MB_OK | MB_ICONINFORMATION);

		if(!wglDeleteContext(hRC)) // ¿Se borro RC?
			MessageBox(NULL, L"GL Context failed to freed", L"ERROR",MB_OK | MB_ICONINFORMATION);

		hRC=NULL;
	}

	glDeleteLists(1, 64);
}

void CGraphics::Size() {
	wglMakeCurrent(hDC,hRC);

	glViewport(0, 0, rSize.right, rSize.bottom);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 

	gluPerspective(30.0f,(GLfloat)rSize.right/(GLfloat)rSize.bottom, 0.5f, 1000.0f);

	//gluOrtho2D(-10, 10, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CGraphics::SetCamera(CCamera * c) {
	cam = c;
}

void CGraphics::AddRenderList(int list) {
	vector<int>::iterator it;

	wglMakeCurrent(hDC,hRC);

	it = find(gList.begin(), gList.end(), list);

	if(it!=gList.end())
		gList.erase(it);

	gList.push_back(list);
}

void CGraphics::RemoveRenderList(int list) {
	//if(glIsList(list)==GL_TRUE)
	//	glDeleteLists(list, 1);

	//gList.remove(list);
}

void CGraphics::Render() {
	wglMakeCurrent(hDC,hRC);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Se borra el buffer de pantalla y profundidad
	glLoadIdentity(); // Se resetea la matriz Current Modelview

	if(cam) {
		cam->LookAt();
	}

	if(gList.size()>0) {
		vector<int>::iterator it;

		it = gList.begin();

		for(; it!=gList.end(); it++) {
			if(glIsList(*it)==GL_TRUE)
				glCallList(*it);
			else
				it = gList.erase(it);

			if(it==gList.end())
				break;
		}
	}

	SwapBuffers(hDC);
}

void CGraphics::SetLightingMode(int mode) {
	if(mode==L_WIRED) {
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		DisableLighting();
	} else 
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void CGraphics::DisableLighting() {
	glDisable(GL_LIGHTING);
}

void CGraphics::EnableLighting() {
	glEnable(GL_LIGHTING);
}
