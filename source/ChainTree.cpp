#include "Graphics.h"
#include "ChainTree.h"

CChainTree::CChainTree(void)
{
	lTree = NULL;
	dTree = NULL;
}

CChainTree::~CChainTree(void)
{
	glDeleteLists(1, GLIST_MAXN);

	//flags.clear();

	FreeTree(&lTree);

	FreeTree(&dTree);
}

#define BLANCO		0
#define ROJO		1
#define AMARILLO	2
#define	VERDE		3
#define CIAN		4
#define AZUL		5
#define MAGENTA		6

void GetStringColorFromIndex(string &s, int idx) {
	switch(idx) {
		case 0: s = "#DD0000"; break;
		case 1: s = "#DDDD00"; break;
		case 2: s = "#00DD00"; break;
		case 3: s = "#00DDDD"; break;
		case 4: s = "#0000DD"; break;
		case 5: s = "#DD00DD"; break;
		default: s = "#000000"; break;
	}
}

void CChainTree::GetColorFromIndex(VERTEX &c, int idx) {
	//VERTEX colors[7] = {
	//	{0.0f, 0.0f, 0.0f},
	//	{0.0f, 0.0f, 0.0f},
	//	{0.0f, 0.0f, 0.0f},
	//	{0.0f, 0.0f, 0.0f},
	//	{0.0f, 0.0f, 0.0f},
	//	{0.0f, 0.0f, 0.0f},
	//	{0.0f, 0.0f, 0.0f},
	//};

	//VERTEX colors[7] = {
	//	{1.0f, 1.0f, 1.0f},
	//	{1.0f, 0.0f, 0.0f},
	//	{1.0f, 1.0f, 0.0f},
	//	{0.0f, 1.0f, 0.0f},
	//	{0.0f, 1.0f, 1.0f},
	//	{0.0f, 0.0f, 1.0f},
	//	{1.0f, 0.0f, 1.0f},
	//};

		VERTEX colors[7] = {
		{1.0f, 0.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 1.0f},
		{1.0f, 0.0f, 1.0f},
		{0.3f, 0.3f, 0.3f},
	};

	if(idx<0 || idx>6)
		c = colors[0];
	else
		c = colors[idx];
}

void CChainTree::FreeTree(tree ** t) {
	tree *tt;
	if(*t==NULL)
		return;

	for(int i=0; i<(int)(*t)->leaf.size(); i++) {
		tt = (*t)->leaf[i];
		FreeTree(&tt);
	}

	(*t)->leaf.clear();

	delete *t;

	*t = NULL;
}

void CChainTree::GenBaseObjects() {
	GLUquadricObj* pQuadric;

	if(glIsList(GLIST_SPHERE) != GL_TRUE) {
		pQuadric = gluNewQuadric();

		glPushMatrix();
		glLoadIdentity();

		glNewList(GLIST_SPHERE, GL_COMPILE);
		gluSphere(pQuadric, 0.2f, 8, 8);
		glEndList();

		glPopMatrix();

		gluDeleteQuadric(pQuadric);
	}

	if(glIsList(GLIST_TUBEX) != GL_TRUE) {
		pQuadric = gluNewQuadric();

		glPushMatrix();
		glLoadIdentity();

		glNewList(GLIST_TUBEX, GL_COMPILE);
		gluCylinder(pQuadric, 0.2f, 0.2f, 1.0f, 8, 8);
		glEndList();

		glPopMatrix();

		gluDeleteQuadric(pQuadric);
	}
}

void CChainTree::Initialize() {
	tPoint p;

	//flags.empty();

	FreeTree(&lTree);

	lTree = new tree;

	lTree->root = new tree;
	lTree->root->root = NULL;

	p.color = BLANCO;

	p.x = 0; p.y = 0; p.z = 0;
	lTree->root->point.push_back(p);

	lTree->root->pp[0] = p;

	p.x =-1; p.y = 0; p.z = 0;
	lTree->root->point.push_back(p);

	lTree->root->pp[1] = p;

	p.x =-1; p.y = 0; p.z = 1;
	lTree->root->point.push_back(p);

	lTree->root->pp[2] = p;

	lTree->root->leaf.push_back(lTree);
}

__inline void CChainTree::UpdatePreviousPoints(tPoint * np, tree * t) {
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

int CChainTree::GraphChain(tree *t, int start) {
	tPoint a1, a2, p;
	int incx, incy, incz;
	int i, l, k;

	l = (int)t->chain.size();

	if(start >= l && l>0)
		return -1;

	if(start==0) {
		t->pp[0] = t->root->pp[0];
		t->pp[1] = t->root->pp[1];
		t->pp[2] = t->root->pp[2];
	}

	for(i=start; i<l; i++) {
		a1.x = t->pp[1].x - t->pp[0].x;
		a2.x = t->pp[2].x - t->pp[1].x;
		a1.y = t->pp[1].y - t->pp[0].y;
		a2.y = t->pp[2].y - t->pp[1].y;
		a1.z = t->pp[1].z - t->pp[0].z;
		a2.z = t->pp[2].z - t->pp[1].z;

		k = (int)t->point.size() - 1;

		switch(t->chain[i]) {
			case '0':
				p.x = t->point[k].x + a2.x;
				p.y = t->point[k].y + a2.y;
				p.z = t->point[k].z + a2.z;

				p.color = VERDE;

				t->point.push_back(p);

				break;
			case '1':
				incx = (a1.y*a2.z - a1.z*a2.y);
				incy = (a1.z*a2.x - a1.x*a2.z);
				incz = (a1.x*a2.y - a1.y*a2.x);

				p.x = t->point[k].x + incx;
				p.y = t->point[k].y + incy;
				p.z = t->point[k].z + incz;

				p.color = CIAN;

				t->point.push_back(p);

				UpdatePreviousPoints(t->pp, t);

				break;

			case '2':
				p.x = t->point[k].x + a1.x;
				p.y = t->point[k].y + a1.y;
				p.z = t->point[k].z + a1.z;

				p.color = AMARILLO;

				t->point.push_back(p);

				UpdatePreviousPoints(t->pp, t);

				break;

			case '3':
				incx = (a1.y*a2.z - a1.z*a2.y);
				incy = (a1.z*a2.x - a1.x*a2.z);
				incz = (a1.x*a2.y - a1.y*a2.x);

				p.x = t->point[k].x - incx;
				p.y = t->point[k].y - incy;
				p.z = t->point[k].z - incz;

				p.color = MAGENTA;

				t->point.push_back(p);

				UpdatePreviousPoints(t->pp, t);

				break;

			case '4':
				p.x = t->point[k].x - a1.x;
				p.y = t->point[k].y - a1.y;
				p.z = t->point[k].z - a1.z;

				p.color = ROJO;

				t->point.push_back(p);

				UpdatePreviousPoints(t->pp, t);

				break;
		}		
	}

	return 0;
}

int CChainTree::ParseChain(const string &chain, tree *t) {
	int p=0, i, pc=0;
	int l = (int)chain.length();
	string st;
	tree * tt;

	if(l <= 0)
		return -1;

	for(i=0; i<l; i++) {
		if(chain[i]=='(') 
		{
			st = chain.substr(p, i-p);
			t->chain += st;

			if(pc==0) {
				t->point.push_back(t->root->point[t->root->point.size()-1]);
			}

			GraphChain(t, pc);

			pc = (int)t->chain.size();

			st = chain.substr(i+1, l-i+1);

			tt = new tree;

			if(t->chain.size()>0)
				tt->root = t;
			else
				tt->root = t->root;

			i += ParseChain(st, tt);

			t->leaf.push_back(tt);

			p = i+1;
		} else if(chain[i]==')') {
			t->chain += chain.substr(p, i-p);

			if(pc==0) {
				t->point.push_back(t->root->point[t->root->point.size()-1]);
			}

			GraphChain(t, pc);

			break;
		} else if(i == l-1) {
			t->chain += chain.substr(p, l-p);

			if(pc==0) {
				t->point.push_back(t->root->point[t->root->point.size()-1]);
			}

			GraphChain(t, pc);
		}
	}

	return i+1;
}

bool CChainTree::ValidateString(const string &s) {
	size_t tpos = s.find_first_not_of("01234()\n\r");

	if(tpos != s.npos)
		return false;

	return true;
}

bool CChainTree::CreateFromString(const string &s) {
	if(s.size() == 0)
		return false;

	Initialize();

	if(!ValidateString(s)) {
		MessageBox(NULL, L"Chain with no valida characters", L"Error", MB_ICONERROR);
		return false;
	}

	ParseChain(s, lTree);

	return true;
}

void CChainTree::GetBranchCode(tree *t, tree *ot, int start) {	
	int i, k, siz;
	tPoint a1, a2, cn[5];
	int d[5];
	float th1 = 1.002f, th2 = 2.002f;

	siz = (int)ot->point.size();

	/*if(start==0) {
		t->pp[0] = t->root->pp[0];
		t->pp[1] = t->root->pp[1];
		t->pp[2] = t->root->pp[2];
	}*/

	cn[0].color = VERDE;
	cn[1].color = CIAN;
	cn[2].color = AMARILLO;
	cn[3].color = MAGENTA;
	cn[4].color = ROJO;

	for(i=start; i<siz; i++) {
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

			if((d[4]=cn[4]-ot->point[i]) <= th1) {
				t->chain = t->chain + '4';
				t->point.push_back(cn[4]);
				UpdatePreviousPoints(t->pp, t);
			} else if((d[3]=cn[3]-ot->point[i]) <= th1) {
				t->chain = t->chain + '3';
				t->point.push_back(cn[3]);
				UpdatePreviousPoints(t->pp, t);
			} else if((d[2]=cn[2]-ot->point[i]) <= th1) {
				t->chain = t->chain + '2';
				t->point.push_back(cn[2]);
				UpdatePreviousPoints(t->pp, t);
			} else if((d[1]=cn[1]-ot->point[i]) <= th1) {
				t->chain = t->chain + '1';
				t->point.push_back(cn[1]);
				UpdatePreviousPoints(t->pp, t);
			}  else if((d[0]=cn[0]-ot->point[i]) <= th1) {
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

			/*if((d[0]=cn[0]-ot->point[i]) <= th1) {
				t->chain = t->chain + '0';
				t->point.push_back(cn[0]);
			} else if((d[1]=cn[1]-ot->point[i]) <= th1) {
				t->chain = t->chain + '1';
				t->point.push_back(cn[1]);
				UpdatePreviousPoints(t->pp, t);
			} else if((d[2]=cn[2]-ot->point[i]) <= th1) {
				t->chain = t->chain + '2';
				t->point.push_back(cn[2]);
				UpdatePreviousPoints(t->pp, t);
			} else if((d[3]=cn[3]-ot->point[i]) <= th1) {
				t->chain = t->chain + '3';
				t->point.push_back(cn[3]);
				UpdatePreviousPoints(t->pp, t);
			} else if((d[4]=cn[4]-ot->point[i]) <= th1) {
				t->chain = t->chain + '4';
				t->point.push_back(cn[4]);
				UpdatePreviousPoints(t->pp, t);
			} else if(d[0] <= th2) {
				t->chain = t->chain + '0';
				t->point.push_back(cn[0]);
			} else if(d[1] <= th2) {
				t->chain = t->chain + '1';
				t->point.push_back(cn[1]);
				UpdatePreviousPoints(t->pp, t);
			} else if(d[2] <= th2) {
				t->chain = t->chain + '2';
				t->point.push_back(cn[2]);
				UpdatePreviousPoints(t->pp, t);
			} else if(d[3] <= th2) {
				t->chain = t->chain + '3';
				t->point.push_back(cn[3]);
				UpdatePreviousPoints(t->pp, t);
			} else if(d[4] <= th2) {
				t->chain = t->chain + '4';
				t->point.push_back(cn[4]);
				UpdatePreviousPoints(t->pp, t);
			}*/
		} while (t->point[k+1] != ot->point[i]);
	}
}

void CChainTree::GetLeafCode(tree *t, tree *ot, int start) {
	int i, siz;
	tree *tt;

	t->chain.clear();
	GetBranchCode(t, ot, start);

	if(t->chain.size() == 0) {
		t->root->leaf.pop_back();
		tt = t->root;
		FreeTree(&t);
		t = tt;
	}

	siz = (int)ot->leaf.size();

	for(i=0; i<siz; i++) {
		tt = new tree;

		tt->root = t;
		tt->point.push_back(t->point[t->point.size()-1]);

		tt->pp[0] = t->pp[0];
		tt->pp[1] = t->pp[1];
		tt->pp[2] = t->pp[2];

		tt->chain.clear();
		GetLeafCode(tt, ot->leaf[i], 1);

		t->leaf.push_back(tt);
	}
}

bool CChainTree::CreateFromSkel(CSkeleton & s) {
	unsigned __int64 wp, wpmax=0;
	tree *t = NULL;
	int i, siz;

	if(lTree) {
		lTree->root->point.clear();
		delete lTree->root;
	}

	FreeTree(&lTree);

	siz = s.GetNumTree();

	if(siz <= 0) {
		MessageBox(NULL, L"No suitable starting vertex were found in the skeleton", L"Error", MB_ICONERROR);
		return false;
	}

	if(siz == 1) {
		s.GetTree(&lTree, 0);

		if(lTree->chain.size() == 0) {
			MessageBox(NULL, L"No suitable starting vertex were found in the skeleton", L"Error", MB_ICONERROR);
			return false;
		}

		return true;
	}

	for(i=0; i<siz; i++) {
		s.GetTree(&t, i);
		s.GetUniquePath(t, wp);

		if(wp>wpmax)
			lTree = t;
		else if(t) {
			t->root->point.clear();
			delete t->root;

			FreeTree(&t);
		}
	}

	if(lTree == NULL) {
		MessageBox(NULL, L"Non suitable starting vertex was found in the skeleton", L"Error", MB_ICONERROR);
		return false;
	}

	return true;
}

void CChainTree::BuildChain(tree *t, string &s) {
	int i, siz;
	string st, sc;

	if(t==NULL)
		return;

	GetStringColorFromIndex(sc, t->color);

	//s = s + "<font color=" + sc + ">" + t->chain + "</font>";
	s = s + t->chain;

	siz = (int)t->leaf.size();

	for(i=0; i<siz; i++) {
		st.clear();

		BuildChain(t->leaf[i], st);

		sc.clear();

		GetStringColorFromIndex(sc, t->leaf[i]->color);
	
		//s = s + "<font color=" + sc + ">" + '(' + st + ')' + "</font>";
		s = s + '(' + st + ')';
	}
}

const string & CChainTree::GetChainCode() {
	chaincode.clear();
	BuildChain(lTree, chaincode);

	return chaincode;
}

unsigned __int64 CChainTree::Base5ToDec(const string &s) {
	unsigned __int64 n=0, bas5=1;
	int i, siz;

	siz = (int)s.size();

	for(i=siz-1; i>=0; i--) {
		n += (s[i]-0x30)*bas5;
		bas5 *= 5;
	}

	return n;
}

bool CChainTree::InvertChain(string &s) {
	int i, a, b, j, siz;
	string sl;
	char tmp;

	siz = (int)s.size();

	if(siz==0)
		return false;

	if(s[siz-1] == '0')
		return false;

	for(i=0; i<siz; ) {
		if(s[i]=='0') {
			for(a=i; s[i]=='0' && i<siz; i++);
			i++;

			sl = s.substr(a, i-a) + sl;
		} else {
			for(a=i; s[i]!='0' && i<siz; i++);

			for(b=a, j=i-1; b<((i-a)/2); b++, j--) {
				tmp  = s[b];
				s[b] = s[j];
				s[j] = tmp;
			}

			sl = s.substr(a, i-a) + sl;
		}
	}

	s = sl;

	return true;
}

void CChainTree::GetLinePoints(const tree *t) {
	int i, np, l;
	VERTEX c;

	if(t==NULL)
		return;

	l  = (int)t->leaf.size();
	np = (int)t->point.size();

	glBegin(GL_LINES);
	for(i=1; i<np; i++) {
		GetColorFromIndex(c, t->point[i].color);
		glColor3f(c.x, c.y, c.z);
		glVertex3i(t->point[i-1].x, t->point[i-1].y, t->point[i-1].z);
		glVertex3i(t->point[i].x, t->point[i].y, t->point[i].z);
	}
	glEnd();

	for(i=0; i<l; i++) {
		GetLinePoints(t->leaf[i]);
	}
}

void CChainTree::GetTubePoints(const tree *t) {
	int i, np, l, lc=0, c=0, tmp;
	VERTEX cl;

	if(t==NULL)
		return;

	l  = (int)t->leaf.size();
	np = (int)t->point.size();

	for(i=1; i<np; i++) {
		if(t->point[i-1].x != t->point[i].x) {
			c = 0;
			tmp = (t->point[i-1].x - t->point[i].x);
		} else if(t->point[i-1].y != t->point[i].y) {
			c = 1;
			tmp = (t->point[i-1].y - t->point[i].y);
		} else if(t->point[i-1].z != t->point[i].z) {
			c = 2;
			tmp = (t->point[i-1].z - t->point[i].z);
		}

		glPushMatrix();
		if(tmp>0)
			glTranslatef((float)t->point[i].x, (float)t->point[i].y, (float)t->point[i].z);
		else
			glTranslatef((float)t->point[i-1].x, (float)t->point[i-1].y, (float)t->point[i-1].z);

		if(c==0)
			glRotatef(90.0f, 0, 1, 0);
		else if(c==1)
			glRotatef(90.0f,-1, 0, 0);

		GetColorFromIndex(cl, t->point[i].color);
		glColor3f(cl.x, cl.y, cl.z);
		glCallList(GLIST_TUBEX);
		glPopMatrix();

		if(lc!=c) {
			glPushMatrix();
			glTranslatef((float)t->point[i-1].x, (float)t->point[i-1].y, (float)t->point[i-1].z);
			GetColorFromIndex(cl, t->point[i-1].color);
			glColor3f(cl.x, cl.y, cl.z);
			glCallList(GLIST_SPHERE);
			glPopMatrix();
		}

		lc = c;
	}

	glPushMatrix();
	glTranslatef((float)t->point[np-1].x, (float)t->point[np-1].y, (float)t->point[np-1].z);
	GetColorFromIndex(cl, t->point[np-1].color);
	glColor3f(cl.x, cl.y, cl.z);
	glCallList(GLIST_SPHERE);
	glPopMatrix();

	for(i=0; i<l; i++) {
		GetTubePoints(t->leaf[i]);
	}
}

int CChainTree::PlotAsTubes() {
	VERTEX cl;
	if(glIsList(GLIST_TUBE))
		glDeleteLists(GLIST_TUBE, 1);

	GenBaseObjects();

	glNewList(GLIST_TUBE, GL_COMPILE);

	glPushMatrix();
	glTranslatef((float)lTree->root->point[0].x, (float)lTree->root->point[0].y, (float)lTree->root->point[0].z);
	glScalef(1.5f, 1.5f, 1.5f);
	GetColorFromIndex(cl, lTree->root->point[0].color);
	glColor3f(cl.x, cl.y, cl.z);
	glCallList(GLIST_SPHERE);
	glPopMatrix();

	GetTubePoints(lTree->root);

	glEndList();

	return GLIST_TUBE;
}

int CChainTree::PlotAsTubesDbg() {
	VERTEX cl;

	if(glIsList(GLIST_TUBE))
		glDeleteLists(GLIST_TUBE, 1);

	if(lTree == NULL)
		return GLIST_TUBE;

	GenBaseObjects();

	glNewList(GLIST_TUBE, GL_COMPILE);

	glPushMatrix();
	glTranslatef((float)lTree->root->point[0].x, (float)lTree->root->point[0].y, (float)lTree->root->point[0].z);
	glScalef(1.5f, 1.5f, 1.5f);
	GetColorFromIndex(cl, lTree->root->point[0].color);
	glColor3f(cl.x, cl.y, cl.z);
	glCallList(GLIST_SPHERE);
	glPopMatrix();

	GetTubePoints(dTree->root);
	
	glEndList();

	return GLIST_TUBE;
}

int CChainTree::PlotAsLines() {
	if(glIsList(GLIST_LINED))
		glDeleteLists(GLIST_LINED, 1);

	glNewList(GLIST_LINED, GL_COMPILE);

	if(lTree) {
		GetLinePoints(lTree->root);
	}
	
	glEndList();

	return GLIST_LINED;
}

int CChainTree::PlotAsLinesDbg() {
	if(glIsList(GLIST_LINE))
		glDeleteLists(GLIST_LINE, 1);

	glNewList(GLIST_LINE, GL_COMPILE);

	GetLinePoints(dTree->root);
	
	glEndList();

	return GLIST_LINE;
}

bool CChainTree::WriteDummy() {
	char linea[80],*resultado;  
	int sale,num;
	FILE *f;

	f = fopen("prueba.dxf", "r");
	if(!f)
		return false;

    while((resultado=fgets(linea,80,f))!=NULL) {
		sale=fputs(linea, fsal);
		
		if (sale!=0)
			printf("\n Fall¢ escritura ");
  
		if ((num=strcmp(linea,"ENTITIES\n"))==0)
			{break;}	   
	}

	fclose(f);

	return true;
}

void CChainTree::WriteHeader() {
	 int sale;
    sale=fputs("  0\n",fsal);
    sale=fputs("POLYLINE\n",fsal);
    sale=fputs("  8\n",fsal);
    sale=fputs("0\n",fsal);
    sale=fputs(" 66\n",fsal);
    sale=fputs("     1\n",fsal);
    sale=fputs(" 10\n",fsal);
    sale=fputs("0.0\n",fsal);
    sale=fputs(" 20\n",fsal);
    sale=fputs("0.0\n",fsal);
    sale=fputs(" 30\n",fsal);
    sale=fputs("0.0\n",fsal);
    sale=fputs(" 70\n",fsal);
    sale=fputs("     8\n",fsal);
}

void CChainTree::WriteStartTube(int color, int nseg)  {
	int sale;

	if(color<0)
		color=0;

    sale=fputs("  0\n",fsal);
    sale=fputs("POLYLINE\n",fsal);
    sale=fputs("  8\n",fsal);
    sale=fputs("0\n",fsal);
	sale=fputs(" 62\n",fsal);
	sale=fprintf(fsal,"     %d\n", color);
    sale=fputs(" 66\n",fsal);
    sale=fputs("     1\n",fsal);
    sale=fputs(" 10\n",fsal);
    sale=fputs("0.0\n",fsal);
    sale=fputs(" 20\n",fsal);
    sale=fputs("0.0\n",fsal);
    sale=fputs(" 30\n",fsal);
    sale=fputs("0.0\n",fsal);
    sale=fputs(" 70\n",fsal);
    sale=fputs("     48\n",fsal);
	sale=fputs(" 71\n",fsal);
    sale=fputs("     2\n",fsal);
	sale=fputs(" 72\n",fsal);
    sale=fprintf(fsal,"     %d\n",nseg);
}

void CChainTree::WriteStartSphere(int color, int nseg) {
    int sale;

	if(color<0)
		color=0;

    sale=fputs("  0\n",fsal);
    sale=fputs("POLYLINE\n",fsal);
    sale=fputs("  8\n",fsal);
    sale=fputs("0\n",fsal);
	sale=fputs(" 62\n",fsal);
	sale=fprintf(fsal,"     %d\n", color);
    sale=fputs(" 66\n",fsal);
    sale=fputs("     1\n",fsal);
    sale=fputs(" 10\n",fsal);
    sale=fputs("0.0\n",fsal);
    sale=fputs(" 20\n",fsal);
    sale=fputs("0.0\n",fsal);
    sale=fputs(" 30\n",fsal);
    sale=fputs("0.0\n",fsal);
    sale=fputs(" 70\n",fsal);
    sale=fputs("     17\n",fsal);
	sale=fputs(" 71\n",fsal);
    sale=fprintf(fsal,"     %d\n",nseg);
	sale=fputs(" 72\n",fsal);
    sale=fprintf(fsal,"     %d\n",nseg);

}

void CChainTree::WriteEndSec() {
	int sale;
	
	sale=fputs("  0\n",fsal);
	sale=fputs("ENDSEC\n",fsal);
	sale=fputs("  0\n",fsal);
	sale=fputs("EOF\n",fsal);
}

void CChainTree::WriteEndLine() {
    int sale;

	sale=fputs("  0\n",fsal);
	sale=fputs("SEQEND\n",fsal);
    sale=fputs("  8\n",fsal);
    sale=fputs("0\n",fsal);
}

void CChainTree::WriteVertex(float nvax, float nvay, float nvaz) {
	int sale;
	
	sale=fputs("  0\n",fsal);
	sale=fputs("VERTEX\n",fsal);
	sale=fputs("  8\n",fsal);
	sale=fputs("0\n",fsal);
	sale=fputs(" 10\n",fsal);
	fprintf(fsal,"%f\n",nvax);
	sale=fputs(" 20\n",fsal);
	fprintf(fsal,"%f\n",nvay);
	sale=fputs(" 30\n",fsal);
	fprintf(fsal,"%f\n",nvaz);
	sale=fputs(" 70\n",fsal);
	sale=fputs("    64\n",fsal);
}

void CChainTree::WriteSphere(deque <tFPoint> &s, int nseg, tPoint off, float sc) {
	int i, l;
	
	l = (int)s.size();

	WriteStartSphere(off.color, nseg);

	for(i=0; i<l; i++) {
		WriteVertex(s[i].x + (off.x * sc), s[i].y + (off.y * sc), s[i].z + (off.z * sc));
	}

	WriteEndLine();
}

void CChainTree::WriteSphereEx(deque <tFPoint> &s, int nseg, tPoint off, float sc, float rt) {
	int i, l;
	
	l = (int)s.size();

	WriteStartSphere(off.color, nseg);

	for(i=0; i<l; i++) {
		WriteVertex((s[i].x * rt) + (off.x * sc), (s[i].y * rt) + (off.y * sc), (s[i].z * rt) + (off.z * sc));
	}

	WriteEndLine();
}

void CChainTree::WriteTube(deque <tFPoint> &c, int nseg, tPoint ps, tPoint pe, float length) {
	int i, l;

	l = (int)c.size();

	WriteStartTube(pe.color, nseg);

	for(i=0; i<l; i++) {
		WriteVertex(c[i].x + (ps.x * length), c[i].y + (ps.y * length), c[i].z + (ps.z * length));
	}

	for(i=0; i<l; i++) {
		WriteVertex(c[i].x + (pe.x * length), c[i].y + (pe.y * length), c[i].z + (pe.z * length));
	}

	WriteEndLine();
}

void CChainTree::PrintAsLines(tree *t) {
	int i, np, l;

	if(t==NULL)
		return;

	l  = (int)t->leaf.size();
	np = (int)t->point.size();

	WriteHeader();
	for(i=0; i<np; i++) {
		WriteVertex((float)t->point[i].x, (float)t->point[i].y, (float)t->point[i].z);
	}
	WriteEndLine();

	for(i=0; i<l; i++) {
		PrintAsLines(t->leaf[i]);
	}
}

void CChainTree::PrintAsTubesEx(tree *t, int nseg, float rad, float length) {
	int i, np, l, lc=0, c=0;
	const float eps=0.01f;

	if(t==NULL)
		return;

	l  = (int)t->leaf.size();
	np = (int)t->point.size();

	for(i=1; i<np; i++) {
		if(t->point[i-1].x != t->point[i].x) {
			c = 0;
		} else if(t->point[i-1].y != t->point[i].y) {
			c = 1;
		} else if(t->point[i-1].z != t->point[i].z) {
			c = 2;
		}

		WriteTube(circle[c], nseg, t->point[i-1], t->point[i], length);

		if(lc!=c)
			WriteSphere(sphere, nseg, t->point[i-1], length);

		lc = c;
	}

	WriteSphere(sphere, nseg, t->point[np-1], length);

	for(i=0; i<l; i++) {
		PrintAsTubesEx(t->leaf[i], nseg, rad, length);
	}
}

void CChainTree::PrintAsTubes(tree *t, int nseg, float rad, float length) {
	int i=0, j=0, k=0;
	float rdst = 6.28318f / nseg;
	float ang = 0.0f, ang1=0.0;
	tFPoint p;

	if(t==NULL)
		return;

	for(i=0; i<nseg; i++) {
		ang=0.0f;
		for(j=0; j<nseg; j++) {
			p.x = cos(ang) * cos(ang1) * rad;
			p.y = cos(ang) * sin(ang1) * rad;
			p.z = sin(ang) * rad;

			sphere.push_back(p);

			ang += rdst;
		}
		ang1+=rdst;
	}

	WriteSphereEx(sphere, nseg, t->point[0], length, 1.5f);

	ang = 0.0f;
	for(i=0; i<nseg; i++) {
		p.x = 0.0f;
		p.y = cos(ang) * rad;
		p.z = sin(ang) * rad;

		circle[0].push_back(p);

		p.x = cos(ang) * rad;
		p.y = 0.0f;
		p.z = sin(ang) * rad;

		circle[1].push_back(p);

		p.x = sin(ang) * rad;
		p.y = cos(ang) * rad;
		p.z = 0.0f;

		circle[2].push_back(p);

		ang+=rdst;
	}

	PrintAsTubesEx(t, nseg, rad, length);
}

bool CChainTree::ExportAsLines(const char * file) {
	fsal = fopen(file, "w");
	if(!fsal)
		return false;

	if(WriteDummy()==false) {
		fclose(fsal);
		return false;
	}

	PrintAsLines(lTree->root);

	WriteEndSec();

	fclose(fsal);

	return true;
}

bool CChainTree::ExportAsTubes(const char * file) {
	fsal = fopen(file, "w");
	if(!fsal)
		return false;

	if(WriteDummy()==false) {
		fclose(fsal);
		return false;
	}

	PrintAsTubes(lTree, 8, 0.2f, 1.0f);

	WriteEndSec();

	fclose(fsal);

	return true;
}

