#pragma once

#include "util.h"
#include "vector.h"

#define MOUSE_LEFT  0x01
#define MOUSE_RIGHT 0x02

class CCamera
{
	/*VERTEX vUp;
	VERTEX vRight;
	VERTEX vFront;
	VERTEX vView;
	VERTEX vPosition;*/

	CVector vUp;
	CVector vRight;
	CVector vFront;
	CVector vView;
	CVector vPosition;

	int mX, mY;

	bool bLeft, bRight;
private:
	void Normalize(VERTEX &v);
	void RotateEx(CVector &p, double theta, CVector r);

public:
	CCamera();
	~CCamera(void);

	void SetUpVec(float x, float y, float z);
	void SetUpVec(VERTEX v);

	void SetViewPos(float x, float y, float z);
	void SetViewPos(VERTEX v);

	void SetCameraPos(float x, float y, float z);
	void SetCameraPos(VERTEX v);

	void LookAt();

	void MousePressed(int button, int x, int y);

	void MouseReleased(int button);

	bool MouseMove(int x, int y);

	void Zoom(float amnt);
};
