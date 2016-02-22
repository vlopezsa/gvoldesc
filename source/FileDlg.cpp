#include "FileDlg.h"

CFileDlg::CFileDlg(CWinBase * wndPrnt, wchar_t *filter, wchar_t * title, wchar_t *defExt, int flags, int nMaxFile)
{
	if(nMaxFile < 0)
		nMaxFile = 0;

	filename = new wchar_t[nMaxFile + 1];

	memset(&of, 0, sizeof(of));
	memset(filename, 0, nMaxFile + 1);

	of.lStructSize = sizeof(OPENFILENAME);
	of.hwndOwner   = wndPrnt->GetHWND();
	of.hInstance   = (HINSTANCE)GetModuleHandle(NULL);
	of.lpstrTitle  = title;
	of.lpstrFilter = filter;
	of.lpstrFile   = filename;
	of.nMaxFile    = nMaxFile;
	of.Flags	   = flags;
	of.lpstrDefExt = defExt;
}

CFileDlg::~CFileDlg(void)
{
	delete [] filename;
}

const wchar_t * CFileDlg::GetOpenFile() {
	memset(filename, 0, of.nMaxFile);

	if(GetOpenFileName(&of))
		return filename;
	
	return NULL;
}

const wchar_t * CFileDlg::GetSaveFile() {
	memset(filename, 0, of.nMaxFile);

	if(GetSaveFileName(&of))
		return filename;
	
	return NULL;
}