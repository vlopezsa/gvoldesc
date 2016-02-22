#pragma once

#include "graphics.h"

#include <vector>
#include <deque>
#include <algorithm>


typedef struct {
	int head, tail;
	string s;
} tPath;

class CSkeleton
{
	vector<IVERTEX> v;
	vector<VERTEX>  vo;
	deque<int>		scnt;

	vector<FACE>	lD;

	vector<vector<int> > vlist;

	vector<vector<int> > vlisto;

private:
	void CleanAll();

	__inline void UpdatePreviousPoints(tPoint * np, tree * t);

	void AdjustCoordinates(const vector<VERTEX> &vf);

	void removex(int h, int n);

	void BuildSubChain(tree *t, tPoint &pe);

	int GetSingleMov(tree *t, tPoint &pe);

	void BuildTree(tree *t, bool preprocess);

	void GetPathArray(tree *t, vector<tPath> &pa, int pos);

public:
	CSkeleton(void);
	~CSkeleton(void);

	bool LoadFromFile(const wchar_t *file);

	int PlotAsLines();

	int PlotAsLinesOri();

	int  GetNumTree() {return (int)scnt.size(); }

	bool GetTree(tree **t, int n);

	void GetUniquePath(tree *t, unsigned __int64 &wpath);
};
