#include "Skeleton.h"
#include "ChainTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool lessD(const FACE &f1, const FACE &f2) {
	return (f1.v[0] < f2.v[0]);
}

bool lessU(const FACE &f1, const FACE &f2) {
	return (f1.v[1] < f2.v[1]);
}

void CSkeleton::removex(int h, int n) {
	vector<int>::iterator ne;

	ne = remove(vlist[h].begin(), vlist[h].end(), n);
	vlist[h].erase(ne, vlist[h].end());

	ne = remove(vlist[n].begin(), vlist[n].end(), h);
	vlist[n].erase(ne, vlist[n].end());
}

CSkeleton::CSkeleton(void)
{
}

CSkeleton::~CSkeleton(void)
{
	CleanAll();
}

void CSkeleton::CleanAll() {
	int s, i;

	v.clear();

	vo.clear();

	lD.clear();

	s = (int)vlist.size();
	for(i=0; i<s; i++)
		vlisto[i].clear();

	vlisto.clear();

	scnt.clear();
}

__inline void CSkeleton::UpdatePreviousPoints(tPoint * np, tree * t) {
	int k, j;

	k = (int)t->point.size() - 1;
	j = (int)t->root->point.size() - 1;

	np[2] = t->point[k];

	if(k==1) {
		np[1] = t->point[k-1];
		np[0] = t->root->point[j-1];
	} else {
		np[1] = t->point[k-1];
		np[0] = t->point[k-2];
	}
}

int CSkeleton::GetSingleMov(tree *t, tPoint &pe) {
	int k;
	tPoint a1, a2, cn[5];
	float d[5], th1 = 1.002f, th2 = 2.002f;

	cn[0].color = t->color;
	cn[1].color = t->color;
	cn[2].color = t->color;
	cn[3].color = t->color;
	cn[4].color = t->color;

	a1.x = t->pp[1].x - t->pp[0].x;
	a2.x = t->pp[2].x - t->pp[1].x;
	a1.y = t->pp[1].y - t->pp[0].y;
	a2.y = t->pp[2].y - t->pp[1].y;
	a1.z = t->pp[1].z - t->pp[0].z;
	a2.z = t->pp[2].z - t->pp[1].z;

	k = (int)t->point.size() - 1;

	cn[1].x = t->point[k].x + (a1.y*a2.z - a1.z*a2.y);
	cn[1].y = t->point[k].y + (a1.z*a2.x - a1.x*a2.z);
	cn[1].z = t->point[k].z + (a1.x*a2.y - a1.y*a2.x);

	cn[2].x = t->point[k].x + a1.x;
	cn[2].y = t->point[k].y + a1.y;
	cn[2].z = t->point[k].z + a1.z;

	cn[3].x = t->point[k].x - (a1.y*a2.z - a1.z*a2.y);
	cn[3].y = t->point[k].y - (a1.z*a2.x - a1.x*a2.z);
	cn[3].z = t->point[k].z - (a1.x*a2.y - a1.y*a2.x);

	cn[4].x = t->point[k].x - a1.x;
	cn[4].y = t->point[k].y - a1.y;
	cn[4].z = t->point[k].z - a1.z;

	cn[0].x = t->point[k].x + a2.x;
	cn[0].y = t->point[k].y + a2.y;
	cn[0].z = t->point[k].z + a2.z;

	if((d[4]=(float)(cn[4]-pe)) <= th1) {
		return 4;
	} else if((d[3]=(float)(cn[3]-pe)) <= th1) {
		return 3;
	} else if((d[2]=(float)(cn[2]-pe)) <= th1) {
		return 2;
	} else if((d[1]=(float)(cn[1]-pe)) <= th1) {
		return 1;
	}  else if((d[0]=(float)(cn[0]-pe)) <= th1) {
		return 0;
	} else if(d[4] <= th2) {
		return 4;
	} else if(d[3] <= th2) {
		return 3;
	} else if(d[2] <= th2) {
		return 2;
	} else if(d[1] <= th2) {
		return 1;
	} else if(d[0] <= th2) {
		return 0;
	}

	return -1;
}

//int CSkeleton::GetSingleMov(tree *t, tPoint &pe) {
//	int k;
//	tPoint a1, a2, cn[5];
//	float d[5], th1 = 1.002f, th2 = 2.002f;
//
//	cn[0].color = VERDE;
//	cn[1].color = CIAN;
//	cn[2].color = AMARILLO;
//	cn[3].color = MAGENTA;
//	cn[4].color = ROJO;
//
//	a1.x = t->pp[1].x - t->pp[0].x;
//	a2.x = t->pp[2].x - t->pp[1].x;
//	a1.y = t->pp[1].y - t->pp[0].y;
//	a2.y = t->pp[2].y - t->pp[1].y;
//	a1.z = t->pp[1].z - t->pp[0].z;
//	a2.z = t->pp[2].z - t->pp[1].z;
//
//	k = (int)t->point.size() - 1;
//
//	cn[1].x = t->point[k].x + (a1.y*a2.z - a1.z*a2.y);
//	cn[1].y = t->point[k].y + (a1.z*a2.x - a1.x*a2.z);
//	cn[1].z = t->point[k].z + (a1.x*a2.y - a1.y*a2.x);
//
//	cn[2].x = t->point[k].x + a1.x;
//	cn[2].y = t->point[k].y + a1.y;
//	cn[2].z = t->point[k].z + a1.z;
//
//	cn[3].x = t->point[k].x - (a1.y*a2.z - a1.z*a2.y);
//	cn[3].y = t->point[k].y - (a1.z*a2.x - a1.x*a2.z);
//	cn[3].z = t->point[k].z - (a1.x*a2.y - a1.y*a2.x);
//
//	cn[4].x = t->point[k].x - a1.x;
//	cn[4].y = t->point[k].y - a1.y;
//	cn[4].z = t->point[k].z - a1.z;
//
//	cn[0].x = t->point[k].x + a2.x;
//	cn[0].y = t->point[k].y + a2.y;
//	cn[0].z = t->point[k].z + a2.z;
//
//	if((d[4]=(float)(cn[4]-pe)) <= th1) {
//		return 4;
//	} else if((d[3]=(float)(cn[3]-pe)) <= th1) {
//		return 3;
//	} else if((d[2]=(float)(cn[2]-pe)) <= th1) {
//		return 2;
//	} else if((d[1]=(float)(cn[1]-pe)) <= th1) {
//		return 1;
//	}  else if((d[0]=(float)(cn[0]-pe)) <= th1) {
//		return 0;
//	} else if(d[4] <= th2) {
//		return 4;
//	} else if(d[3] <= th2) {
//		return 3;
//	} else if(d[2] <= th2) {
//		return 2;
//	} else if(d[1] <= th2) {
//		return 1;
//	} else if(d[0] <= th2) {
//		return 0;
//	}
//
//	return -1;
//}

void CSkeleton::BuildSubChain(tree *t, tPoint &pe) {
	int k;
	tPoint a1, a2, cn[5];
	float d[5], th1 = 1.002f, th2 = 2.002f;

	cn[0].color = t->color;
	cn[1].color = t->color;
	cn[2].color = t->color;
	cn[3].color = t->color;
	cn[4].color = t->color;

	do {
		a1.x = t->pp[1].x - t->pp[0].x;
		a2.x = t->pp[2].x - t->pp[1].x;
		a1.y = t->pp[1].y - t->pp[0].y;
		a2.y = t->pp[2].y - t->pp[1].y;
		a1.z = t->pp[1].z - t->pp[0].z;
		a2.z = t->pp[2].z - t->pp[1].z;

		k = (int)t->point.size() - 1;

		cn[1].x = t->point[k].x + (a1.y*a2.z - a1.z*a2.y);
		cn[1].y = t->point[k].y + (a1.z*a2.x - a1.x*a2.z);
		cn[1].z = t->point[k].z + (a1.x*a2.y - a1.y*a2.x);

		cn[2].x = t->point[k].x + a1.x;
		cn[2].y = t->point[k].y + a1.y;
		cn[2].z = t->point[k].z + a1.z;

		cn[3].x = t->point[k].x - (a1.y*a2.z - a1.z*a2.y);
		cn[3].y = t->point[k].y - (a1.z*a2.x - a1.x*a2.z);
		cn[3].z = t->point[k].z - (a1.x*a2.y - a1.y*a2.x);

		cn[4].x = t->point[k].x - a1.x;
		cn[4].y = t->point[k].y - a1.y;
		cn[4].z = t->point[k].z - a1.z;
	
		cn[0].x = t->point[k].x + a2.x;
		cn[0].y = t->point[k].y + a2.y;
		cn[0].z = t->point[k].z + a2.z;

		if((d[4]=(float)(cn[4]-pe)) <= th1) {
			t->chain = t->chain + '4';
			t->point.push_back(cn[4]);
			UpdatePreviousPoints(t->pp, t);
		} else if((d[3]=(float)(cn[3]-pe)) <= th1) {
			t->chain = t->chain + '3';
			t->point.push_back(cn[3]);
			UpdatePreviousPoints(t->pp, t);
		} else if((d[2]=(float)(cn[2]-pe)) <= th1) {
			t->chain = t->chain + '2';
			t->point.push_back(cn[2]);
			UpdatePreviousPoints(t->pp, t);
		} else if((d[1]=(float)(cn[1]-pe)) <= th1) {
			t->chain = t->chain + '1';
			t->point.push_back(cn[1]);
			UpdatePreviousPoints(t->pp, t);
		}  else if((d[0]=(float)(cn[0]-pe)) <= th1) {
			t->chain = t->chain + '0';
			t->point.push_back(cn[0]);
		} else if(d[4] <= th2) {
			t->chain = t->chain + '4';
			t->point.push_back(cn[4]);
			UpdatePreviousPoints(t->pp, t);
		} else if(d[3] <= th2) {
			t->chain = t->chain + '3';
			t->point.push_back(cn[3]);
			UpdatePreviousPoints(t->pp, t);
		} else if(d[2] <= th2) {
			t->chain = t->chain + '2';
			t->point.push_back(cn[2]);
			UpdatePreviousPoints(t->pp, t);
		} else if(d[1] <= th2) {
			t->chain = t->chain + '1';
			t->point.push_back(cn[1]);
			UpdatePreviousPoints(t->pp, t);
		} else if(d[0] <= th2) {
			t->chain = t->chain + '0';
			t->point.push_back(cn[0]);
		}
	} while (t->point[k+1] != pe);
}

//void CSkeleton::BuildSubChain(tree *t, tPoint &pe) {
//	int k;
//	tPoint a1, a2, cn[5];
//	float d[5], th1 = 1.002f, th2 = 2.002f;
//
//	cn[0].color = VERDE;
//	cn[1].color = CIAN;
//	cn[2].color = AMARILLO;
//	cn[3].color = MAGENTA;
//	cn[4].color = ROJO;
//
//	do {
//		a1.x = t->pp[1].x - t->pp[0].x;
//		a2.x = t->pp[2].x - t->pp[1].x;
//		a1.y = t->pp[1].y - t->pp[0].y;
//		a2.y = t->pp[2].y - t->pp[1].y;
//		a1.z = t->pp[1].z - t->pp[0].z;
//		a2.z = t->pp[2].z - t->pp[1].z;
//
//		k = (int)t->point.size() - 1;
//
//		cn[1].x = t->point[k].x + (a1.y*a2.z - a1.z*a2.y);
//		cn[1].y = t->point[k].y + (a1.z*a2.x - a1.x*a2.z);
//		cn[1].z = t->point[k].z + (a1.x*a2.y - a1.y*a2.x);
//
//		cn[2].x = t->point[k].x + a1.x;
//		cn[2].y = t->point[k].y + a1.y;
//		cn[2].z = t->point[k].z + a1.z;
//
//		cn[3].x = t->point[k].x - (a1.y*a2.z - a1.z*a2.y);
//		cn[3].y = t->point[k].y - (a1.z*a2.x - a1.x*a2.z);
//		cn[3].z = t->point[k].z - (a1.x*a2.y - a1.y*a2.x);
//
//		cn[4].x = t->point[k].x - a1.x;
//		cn[4].y = t->point[k].y - a1.y;
//		cn[4].z = t->point[k].z - a1.z;
//	
//		cn[0].x = t->point[k].x + a2.x;
//		cn[0].y = t->point[k].y + a2.y;
//		cn[0].z = t->point[k].z + a2.z;
//
//		if((d[4]=(float)(cn[4]-pe)) <= th1) {
//			t->chain = t->chain + '4';
//			t->point.push_back(cn[4]);
//			UpdatePreviousPoints(t->pp, t);
//		} else if((d[3]=(float)(cn[3]-pe)) <= th1) {
//			t->chain = t->chain + '3';
//			t->point.push_back(cn[3]);
//			UpdatePreviousPoints(t->pp, t);
//		} else if((d[2]=(float)(cn[2]-pe)) <= th1) {
//			t->chain = t->chain + '2';
//			t->point.push_back(cn[2]);
//			UpdatePreviousPoints(t->pp, t);
//		} else if((d[1]=(float)(cn[1]-pe)) <= th1) {
//			t->chain = t->chain + '1';
//			t->point.push_back(cn[1]);
//			UpdatePreviousPoints(t->pp, t);
//		}  else if((d[0]=(float)(cn[0]-pe)) <= th1) {
//			t->chain = t->chain + '0';
//			t->point.push_back(cn[0]);
//		} else if(d[4] <= th2) {
//			t->chain = t->chain + '4';
//			t->point.push_back(cn[4]);
//			UpdatePreviousPoints(t->pp, t);
//		} else if(d[3] <= th2) {
//			t->chain = t->chain + '3';
//			t->point.push_back(cn[3]);
//			UpdatePreviousPoints(t->pp, t);
//		} else if(d[2] <= th2) {
//			t->chain = t->chain + '2';
//			t->point.push_back(cn[2]);
//			UpdatePreviousPoints(t->pp, t);
//		} else if(d[1] <= th2) {
//			t->chain = t->chain + '1';
//			t->point.push_back(cn[1]);
//			UpdatePreviousPoints(t->pp, t);
//		} else if(d[0] <= th2) {
//			t->chain = t->chain + '0';
//			t->point.push_back(cn[0]);
//		}
//	} while (t->point[k+1] != pe);
//}

void CSkeleton::BuildTree(tree *t, bool preprocess) {
	tPoint p;
	tree *tt;
	int k, i, j, siz, max, tmp;

	if(preprocess == true) {
		p.x = v[t->tail].x;
		p.y = v[t->tail].y;
		p.z = v[t->tail].z;

		BuildSubChain(t, p);
	}

	while(vlist[t->tail].size() == 1) {
		k = vlist[t->tail][0];

		removex(t->tail, k);
		t->tail = k;

		p.x = v[k].x;
		p.y = v[k].y;
		p.z = v[k].z;

		BuildSubChain(t, p);
	}


	if(vlist[t->tail].size() > 1) {
		if(t->chain.size() == 0) {
			t->root->leaf.pop_back();
			tt = t->root;
			delete t;
			t = tt;
		}

		while((siz = (int)vlist[t->tail].size()) > 0) {
			max = j = -1;

			for(i=0; i<siz; i++) {
				k = vlist[t->tail][i];

				p.x = v[k].x;
				p.y = v[k].y;
				p.z = v[k].z;

				tmp = GetSingleMov(t, p);
				if(tmp>max) {
					max = tmp;
					j = i;
				}
			}

			tt = new tree;

			tt->root = t;
			tt->point.push_back(t->point[t->point.size()-1]);

			tt->pp[0] = t->pp[0];
			tt->pp[1] = t->pp[1];
			tt->pp[2] = t->pp[2];

			tt->head = t->tail;
			tt->tail = vlist[t->tail][j];
			removex(tt->head, tt->tail);

			tt->chain.clear();

			tt->color = t->color;
			tt->acc = t->acc + t->chain.size();

			if(tt->acc > 50)
				tt->color++;
			//t->color++;

			if(tt->color>6)
				tt->color = 0;

			BuildTree(tt, true);

			t->leaf.push_back(tt);
		}
	}
}

bool CSkeleton::GetTree(tree **t, int n) {
	tPoint point[3];
	bool f1[3] = {false};
	bool f2[3] = {false};
	int nc1=0, nc2=0, start, tmp;

	if(n>=(int)scnt.size() || n<0)
		return false;

	vlist = vlisto;

	(*t) = new tree;
	(*t)->root = new tree;

	(*t)->root->head = scnt[n];
	(*t)->root->tail = vlist[scnt[n]][0];

	(*t)->color = 0;
	(*t)->root->color = 0;
	(*t)->acc = 2;
	(*t)->root->acc = 0;

	removex(scnt[n], (*t)->root->tail);

	point[0].color = BLANCO;
	point[0].x     = v[scnt[n]].x;
	point[0].y     = v[scnt[n]].y;
	point[0].z     = v[scnt[n]].z;

	(*t)->root->pp[0] = point[0];

	point[1].color = BLANCO;
	point[1].x     = v[(*t)->root->tail].x;
	point[1].y     = v[(*t)->root->tail].y;
	point[1].z     = v[(*t)->root->tail].z;

	if(point[0].x != point[1].x) {
		f1[0] = true; nc1++; }
	if(point[0].y != point[1].y) {
		f1[1] = true; nc1++; }
	if(point[0].z != point[1].z) {
		f1[2] = true; nc1++; }

	if(nc1<=1 && vlist[(*t)->root->tail].size()!=1)
		return false;

	if(nc1>=2) {
		if(f1[0]==true) {
			(*t)->root->pp[1].x = point[1].x;
			(*t)->root->pp[1].y = point[0].y;
			(*t)->root->pp[1].z = point[0].z;

			if(f1[1]==true) {
				(*t)->root->pp[2].x = (*t)->root->pp[1].x;
				(*t)->root->pp[2].y = point[1].y;
				int perro  = point[1].y;
				int perroc = (*t)->root->pp[2].y;
				(*t)->root->pp[2].z = (*t)->root->pp[1].z;
			} else if(f1[2]==true) {
				(*t)->root->pp[2].x = (*t)->root->pp[1].x;
				(*t)->root->pp[2].y = (*t)->root->pp[1].y;
				(*t)->root->pp[2].z = point[1].z;
			}
		} else if(f1[1]==true) {
			(*t)->root->pp[1].x = point[0].x;
			(*t)->root->pp[1].y = point[1].y;
			(*t)->root->pp[1].z = point[0].z;

			if(f1[2]==true) {
				(*t)->root->pp[2].x = (*t)->root->pp[1].x;
				(*t)->root->pp[2].y = (*t)->root->pp[1].y;
				(*t)->root->pp[2].z = point[1].z;
			} else if(f1[0]==true) {
				(*t)->root->pp[2].x = point[1].x;
				(*t)->root->pp[2].y = (*t)->root->pp[1].y;
				(*t)->root->pp[2].z = (*t)->root->pp[1].z;
			}
		} else if(f1[2]==true) {
			(*t)->root->pp[1].x = point[0].x;
			(*t)->root->pp[1].y = point[0].y;
			(*t)->root->pp[1].z = point[1].z;

			if(f1[0]==true) {
				(*t)->root->pp[2].x = point[1].x;
				(*t)->root->pp[2].y = (*t)->root->pp[1].y;
				(*t)->root->pp[2].z = (*t)->root->pp[1].z;
			} else if(f1[2]==true) {
				(*t)->root->pp[2].x = (*t)->root->pp[1].x;
				(*t)->root->pp[2].y = point[1].y;
				(*t)->root->pp[2].z = (*t)->root->pp[1].z;
			}
		}

		if (nc1==2)
			start=2;
		else 
			start=1;
	} else {
		tmp = (*t)->root->tail;
		(*t)->root->tail = vlist[(*t)->root->tail][0];

		removex(tmp, (*t)->root->tail);

		point[2].color = BLANCO;
		point[2].x     = v[(*t)->root->tail].x;
		point[2].y     = v[(*t)->root->tail].y;
		point[2].z     = v[(*t)->root->tail].z;

		if(point[2].x != point[1].x) {
			f2[0] = true; nc2++; }
		if(point[2].y != point[1].y) {
			f2[1] = true; nc2++; }
		if(point[2].z != point[1].z) {
			f2[2] = true; nc2++; }

		if(nc1==1 && nc2==1) {
			if(f1[0]==f2[0] && f1[1]==f2[1] && f1[2]==f2[2])
				return false;
			else {
				(*t)->root->pp[0] = point[0];
				(*t)->root->pp[1] = point[1];
				(*t)->root->pp[2] = point[2];

				start=3;
			}
		} else {
			(*t)->root->pp[1] = point[1];

			if(f1[0]==true) {
				if(f2[1]==true) {
					(*t)->root->pp[2].x = (*t)->root->pp[1].x;
					(*t)->root->pp[2].y = point[2].y;
					(*t)->root->pp[2].z = (*t)->root->pp[1].z;
				} else if(f2[2]==true) {
					(*t)->root->pp[2].x = (*t)->root->pp[1].x;
					(*t)->root->pp[2].y = (*t)->root->pp[1].y;
					(*t)->root->pp[2].z = point[2].z;
				}
			} else if(f1[1]==true) {
				if(f2[2]==true) {
					(*t)->root->pp[2].x = (*t)->root->pp[1].x;
					(*t)->root->pp[2].y = (*t)->root->pp[1].y;
					(*t)->root->pp[2].z = point[2].z;
				} else if(f2[0]==true) {
					(*t)->root->pp[2].x = point[2].x;
					(*t)->root->pp[2].y = (*t)->root->pp[1].y;
					(*t)->root->pp[2].z = (*t)->root->pp[1].z;
				}
			} else if(f1[2]==true) {
				if(f2[0]==true) {
					(*t)->root->pp[2].x = point[2].x;
					(*t)->root->pp[2].y = (*t)->root->pp[1].y;
					(*t)->root->pp[2].z = (*t)->root->pp[1].z;
				} else if(f2[2]==true) {
					(*t)->root->pp[2].x = (*t)->root->pp[1].x;
					(*t)->root->pp[2].y = point[2].y;
					(*t)->root->pp[2].z = (*t)->root->pp[1].z;
				}
			}
			start = 2;
		}
	}

	(*t)->root->point.push_back((*t)->root->pp[0]);
	(*t)->root->point.push_back((*t)->root->pp[1]);
	(*t)->root->point.push_back((*t)->root->pp[2]);

	(*t)->pp[0] = (*t)->root->pp[0];
	(*t)->pp[1] = (*t)->root->pp[1];
	(*t)->pp[2] = (*t)->root->pp[2];

	(*t)->root->root = NULL;
	(*t)->root->leaf.push_back((*t));

	(*t)->point.push_back((*t)->pp[2]);

	(*t)->head = (*t)->root->head;
	(*t)->tail = (*t)->root->tail;

	point[0].x = v[(*t)->root->tail].x;
	point[0].y = v[(*t)->root->tail].y;
	point[0].z = v[(*t)->root->tail].z;

	if((*t)->point[0] == point[0]) {
		(*t)->head = (*t)->tail;
		BuildTree(*t, false);
	} else 
		BuildTree(*t, true);

	return true;
}

void CSkeleton::AdjustCoordinates(const vector<VERTEX> &vf) {
	int i, s;
	float step=0.0f, minx, miny, minz;

	v = vector<IVERTEX>(vf.size());

	if(fabs(vf[lD[0].v[0]].x - vf[lD[0].v[1]].x) > step)
		step = fabs(vf[lD[0].v[0]].x - vf[lD[0].v[1]].x);
	if(fabs(vf[lD[0].v[0]].y - vf[lD[0].v[1]].y) > step)
		step = fabs(vf[lD[0].v[0]].y - vf[lD[0].v[1]].y);
	if(fabs(vf[lD[0].v[0]].z - vf[lD[0].v[1]].z) > step)
		step = fabs(vf[lD[0].v[0]].z - vf[lD[0].v[1]].z);

	minx = miny = minz = 999999.0f;

	s = (int)vf.size();

	for(i=0; i<s; i++) {
		if(vf[i].x < minx)
			minx = vf[i].x;

		if(vf[i].y < miny)
			miny = vf[i].y;

		if(vf[i].z < minz)
			minz = vf[i].z;
	}

	for(i=0; i<s; i++) {
		v[i].x = round((vf[i].x - minx) / step);
		v[i].y = round((vf[i].y - miny) / step);
		v[i].z = round((vf[i].z - minz) / step);
	}
}

bool CSkeleton::LoadFromFile(const wchar_t *files) {
	FILE *fmt;
	char buf[256] = {0};
	char file[256]= {0};
	int  i, nv, nf, ne, f1, f2;
	vector<VERTEX> vf;

	if(files == NULL)
		return false;
	
	for(i=0; i<wcslen(files); i++)
		file[i] = (char)(files[i]&0xFF);

	CleanAll();

	fmt = fopen(file, "r");
	if(!fmt)
		return false;

	fgets(buf, 256, fmt);

	if(strncmp(buf, "OFF", 3)) {
		fclose(fmt);
		return false;
	}

	fgets(buf, 256, fmt);
	sscanf_s(buf, "%d %d %d", &nv, &nf, &ne);

	if(nv <= 0 || nf <= 0)  {
		fclose(fmt);
		return false;
	}


	vf = vector<VERTEX>(nv);

	vlist = vector<vector<int> >(nv);

	for(i=0; i<nv; i++) {
		fgets(buf, 256, fmt);
		sscanf_s(buf, "%f %f %f", &vf[i].x, &vf[i].y, &vf[i].z);
	}

	lD = vector<FACE>(nf);

	for(i=0; i<nf; i++) {
		fgets(buf, 256, fmt);
		sscanf_s(buf, "%d %d %d", &ne, &f1, &f2);

		vlist[f1].push_back(f2);
		vlist[f2].push_back(f1);

		lD[i].v[0] = f1;
		lD[i].v[1] = f2;
	}

	fclose(fmt);

	AdjustCoordinates(vf);

	for(i=0; i<nv; i++) {
		if(vlist[i].size()==1)
			scnt.push_back(i);
	}

	vlisto = vlist;

	vo = vf;

	return true;
}

void CSkeleton::GetPathArray(tree *t, vector<tPath> &pa, int pos) {
	int i, siz;

	pa[pos].s    = pa[pos].s + t->chain;
	pa[pos].tail = t->tail;

	siz = (int)t->leaf.size();

	if(siz>0) {
		for(i=1; i<siz; i++) {
			pa.push_back(pa[pos]);
			GetPathArray(t->leaf[i], pa, (int)pa.size()-1);
		}

		GetPathArray(t->leaf[0], pa, pos);
	}
}

void CSkeleton::GetUniquePath(tree *t, unsigned __int64 &wpath) {
	int i, siz;
	unsigned __int64 n, n1, nmax=0;
	tPath p;
	vector<tPath> pa;
	string sinv;

	p.head = t->head;
	p.tail = t->tail;

	pa.push_back(p);

	GetPathArray(t->root, pa, 0);

	siz = (int)pa.size();

	for(i=0; i<siz; i++) {
		if(find(scnt.begin(), scnt.end(), pa[i].tail) != scnt.end()) {
			sinv = pa[i].s;

			if(CChainTree::InvertChain(sinv) == true) {
				n  = CChainTree::Base5ToDec(pa[i].s);
				n1 = CChainTree::Base5ToDec(sinv);

				if(n1>n)
					n = n1;

				if(n>nmax) {
					nmax = n;
				}
			}
		}
	}

	wpath = nmax;
}

int CSkeleton::PlotAsLines() {
	int i, s;
	if(glIsList(GLIST_SKEL))
		glDeleteLists(GLIST_SKEL, 1);

	glNewList(GLIST_SKEL, GL_COMPILE);

	glColor3f(0.0f, 0.0f, 0.0f);

	s = (int)lD.size();

	for(i=0; i<s; i++) {
		glBegin(GL_LINES);

		glVertex3i(v[lD[i].v[0]].x, v[lD[i].v[0]].y, v[lD[i].v[0]].z);
		glVertex3i(v[lD[i].v[1]].x, v[lD[i].v[1]].y, v[lD[i].v[1]].z);

		glEnd();
	}

	glEndList();

	return GLIST_SKEL;
}

int CSkeleton::PlotAsLinesOri() {
	int i, s;
	if(glIsList(GLIST_SKEL))
		glDeleteLists(GLIST_SKEL, 1);

	glNewList(GLIST_SKEL, GL_COMPILE);

	glColor3f(1.0f, 0.0f, 0.0f);

	s = (int)lD.size();

	for(i=0; i<s; i++) {
		glBegin(GL_LINES);

		glVertex3f(vo[lD[i].v[0]].x, vo[lD[i].v[0]].y, vo[lD[i].v[0]].z);
		glVertex3f(vo[lD[i].v[1]].x, vo[lD[i].v[1]].y, vo[lD[i].v[1]].z);

		glEnd();
	}

	glEndList();

	return GLIST_SKEL;
}