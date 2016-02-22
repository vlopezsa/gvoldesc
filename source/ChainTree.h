#pragma once

#include "skeleton.h"

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <list>

class CChainTree
{
	FILE *fsal;
	deque <tFPoint> sphere;
	deque <tFPoint> circle[3];

	tree  * lTree;
	tree  * dTree;

	list<int> idx;

	string chaincode;

private:
	void FreeTree(tree ** t);
	void Initialize();

	int ParseChain(const string &chain, tree *t);
	int GraphChain(tree *t, int start);

	void GenBaseObjects();

	void GetLinePoints(const tree *t);
	void GetTubePoints(const tree *t);

	void GetColorFromIndex(VERTEX &c, int idx);

	bool WriteDummy();
	void WriteHeader();
	void WriteStartTube(int color, int nseg);
	void WriteStartSphere(int color, int nseg);
	void WriteEndSec();
	void WriteEndLine();
	void WriteVertex(float nvax, float nvay, float nvaz);
	void WriteSphere(deque <tFPoint> &s, int nseg, tPoint off, float sc);
	void WriteSphereEx(deque <tFPoint> &s, int nseg, tPoint off, float sc, float rt);
	void WriteTube(deque <tFPoint> &c, int nseg, tPoint ps, tPoint pe, float length);

	void PrintAsLines(tree *t);
	void PrintAsTubesEx(tree *t, int nseg, float rad, float length);
	void PrintAsTubes(tree *t, int nseg, float rad, float length);

	void ReverseBranch(tree *t);

	void GetBranchCode(tree *t, tree *ot, int start);

	void GetLeafCode(tree *t, tree *ot, int start);

	void BuildChain(tree *t, string &s);

	__inline void UpdatePreviousPoints(tPoint * np, tree * t);
	__inline void AddTreeLeaf(tree *t, int head, int tail);

public:
	CChainTree(void);
	~CChainTree(void);

	bool ValidateString(const string &s);

	bool CreateFromString(const string &s);

	bool CreateFromSkel(CSkeleton &s);

	int PlotAsLines();
	int PlotAsTubes();

	int PlotAsLinesDbg();
	int PlotAsTubesDbg();

	bool ExportAsLines(const char * file);

	bool ExportAsTubes(const char * file);

	const string & GetChainCode();

	static bool InvertChain(string &s);

	static unsigned __int64 Base5ToDec(const string &s);
};