#pragma once

#include "winbase.h"

class CFileDlg
{
	wchar_t * filename;
	OPENFILENAME of;

public:
	CFileDlg(CWinBase * wndPrnt, wchar_t *filter=L"Todos los archivos(*.*)\0*.*\0\0", wchar_t *title=NULL, wchar_t *defExt=NULL, int flags=OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_LONGNAMES, int nMaxFile=256);
	~CFileDlg(void);

	const wchar_t * GetOpenFile();
	const wchar_t * GetSaveFile();
};
