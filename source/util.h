#ifndef UTILH
#define UTILH

#include <deque>
#include <vector>
#include <string>
#include <algorithm>

#include <math.h>

#define BLANCO		0
#define ROJO		1
#define AMARILLO	2
#define	VERDE		3
#define CIAN		4
#define AZUL		5
#define MAGENTA		6

using namespace std;

#define round(x) ((int)((x)+0.5f))

typedef struct {
	int x, y, z;
}IVERTEX;

typedef struct {
	float x, y, z;
}VERTEX;

typedef struct {
	VERTEX v;
	VERTEX n;
}VERTEXN;

typedef struct {
	VERTEX v;
	VERTEX c;
}VERTEXC;

typedef struct {
	VERTEX v;
	VERTEX n;
	VERTEX c;
}VERTEXNC;

typedef struct {
	int v[2];
}FACE;

typedef struct {
	int nFaces;
	int nVerts;
	VERTEX * v;
	FACE   * f;
}OBJECT;

typedef struct {
	float x, y, z;
	int  color;
} tFPoint;

typedef struct {
	int  x, y, z;
	int  color;
} tPoint;

struct ttree {
	string chain;
	struct ttree * root;

	int head, tail;

	int color;

	int acc;

	tPoint	pp[3];

	deque <struct ttree *> leaf;

	deque <tPoint> point;
};

typedef struct ttree tree;

bool operator== (const FACE &f1, const FACE &f2);

bool  operator== (const tPoint &p1, const tPoint &p2);
bool  operator!= (const tPoint &p1, const tPoint &p2);

int operator-  (const tPoint &p1, const tPoint &p2);

#endif
