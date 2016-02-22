#include "util.h"

bool operator== (const FACE &f1, const FACE &f2) {
	return (f1.v[0]==f2.v[0] && f1.v[1]==f2.v[1]);
}

bool operator== (const tPoint &p1, const tPoint &p2) {
	return (p1.x==p2.x && p1.y==p2.y && p1.z==p2.z);
}

bool operator != (const tPoint &p1, const tPoint &p2) {
	return (p1.x!=p2.x || p1.y!=p2.y || p1.z!=p2.z);
}

int operator- (const tPoint &p1, const tPoint &p2) {
	tPoint p;

	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	p.z = p1.z - p2.z;

	return (p.x*p.x + p.y*p.y + p.z*p.z);
}

