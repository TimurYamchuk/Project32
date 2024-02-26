#pragma once
#include "header.h"

class CMultithreaded_ListDlg
{
public:
	CMultithreaded_ListDlg(void);
public:
	~CMultithreaded_ListDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMultithreaded_ListDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	HWND hList1, hList2, hList3, hPlay1, hPlay2, hPlay3;
	HANDLE Th1, Th2, Th3;
};