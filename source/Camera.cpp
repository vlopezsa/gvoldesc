#include "Camera.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#pragma warning (disable:4244)

CCamera::CCamera(void)
{
	vUp       = CVector(0, 1, 0);
	vRight    = CVector(1, 0, 0);
	vFront    = CVector(0, 0, 1);
	vPosition = CVector(0, 0, -1);
	vView     = CVector(0, 0, 0);

	mX = 0;
	mY = 0;

	bLeft  = false;
	bRight = false;
}

CCamera::~CCamera(void)
{
}

void CCamera::Normalize(VERTEX &v) {

}

void CCamera::RotateEx(CVector &p, double theta, CVector r)
{
   CVector q;
   double costheta,sintheta;

   r.Normalize();
   costheta = cos(theta);
   sintheta = sin(theta);

   q.X += (costheta + (1 - costheta) * r.X * r.X) * p.X;
   q.X += ((1 - costheta) * r.X * r.Y - r.Z * sintheta) * p.Y;
   q.X += ((1 - costheta) * r.X * r.Z + r.Y * sintheta) * p.Z;

   q.Y += ((1 - costheta) * r.X * r.Y + r.Z * sintheta) * p.X;
   q.Y += (costheta + (1 - costheta) * r.Y * r.Y) * p.Y;
   q.Y += ((1 - costheta) * r.Y * r.Z - r.X * sintheta) * p.Z;

   q.Z += ((1 - costheta) * r.X * r.Z - r.Y * sintheta) * p.X;
   q.Z += ((1 - costheta) * r.Y * r.Z + r.X * sintheta) * p.Y;
   q.Z += (costheta + (1 - costheta) * r.Z * r.Z) * p.Z;

   p = q;
}

void CCamera::SetUpVec(float x, float y, float z) {
	vUp = CVector(x, y, z);
}

void CCamera::SetUpVec(VERTEX v) {
	SetUpVec(v.x, v.y, v.z);
}

void CCamera::SetViewPos(float x, float y, float z) {
	vView = CVector(x, y, z);
}

void CCamera::SetViewPos(VERTEX v) {
	SetViewPos(v.x, v.y, v.z);
}

void CCamera::SetCameraPos(float x, float y, float z) {
	vPosition = CVector(x, y, z);
}

void CCamera::SetCameraPos(VERTEX v) {
	SetCameraPos(v.x, v.y, v.z);
}

void CCamera::MousePressed(int button, int x, int y) {
	mX = x;
	mY = y;

	if(button == MOUSE_LEFT)
		bLeft  = true;

	if(button == MOUSE_RIGHT)
		bRight = true;
}

void CCamera::MouseReleased(int button) {
	if(button == MOUSE_LEFT)
		bLeft  = false;

	if(button == MOUSE_RIGHT)
		bRight = false;
}

bool CCamera::MouseMove(int x, int y) {
	int dx = x - mX;
	int dy = y - mY;

	if(bLeft==true) {
		/*Camara de Primera Persona*/
		/*
		RotateEx(vFront, -dx*0.001f, vUp);
		RotateEx(vRight, -dx*0.001f, vUp);

		Normalize(vRight);

		RotateEx(vFront, dy*0.001f, vRight);
		RotateEx(vUp,    dy*0.001f, vRight);

		Normalize(vFront);
		Normalize(vUp);

		vView.x = vPosition.x + vFront.x;
		vView.y = vPosition.y + vFront.y;
		vView.z = vPosition.z + vFront.z;*/

		RotateEx(vFront,	-dx*0.001f, vUp);
		RotateEx(vPosition, -dx*0.001f, vUp);
		RotateEx(vRight,    -dx*0.001f, vUp);
		vRight.Normalize();

		RotateEx(vFront,    dy*0.001f, vRight);
		RotateEx(vPosition, dy*0.001f, vRight);
		RotateEx(vUp,       dy*0.001f, vRight);

		vFront.Normalize();
		vUp.Normalize();

		mX = x;
		mY = y;

		return true;
	} else if(bRight==true) {
		float ix = (x - mX) * 0.01f;
		float iy = (y - mY) * 0.01f;
		CVector inc = (vRight * ix) + (vUp    * iy);

		vPosition = vPosition + inc;
		vView     = vView     + inc;

		mX = x;
		mY = y;

		return true;
	}

	return false;
}

void CCamera::Zoom(float amnt) {
	CVector v, t;

	t = vPosition + (vFront * amnt);
	v = t - vView;

	if(v.Magnitude() > 0.5f)
		vPosition = t;

	/*Usado para camara de primera persona*/
	/*vView = vPosition + vFront;*/
}

void CCamera::LookAt() {
	gluLookAt(vPosition.X, vPosition.Y, vPosition.Z, vView.X, vView.Y, vView.Z, vUp.X, vUp.Y, vUp.Z);
}