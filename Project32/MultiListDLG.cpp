#include "Multithreaded_ListDlg.h"

CMultithreaded_ListDlg* CMultithreaded_ListDlg::ptr = NULL;

CMultithreaded_ListDlg::CMultithreaded_ListDlg(void)
{
	ptr = this;
}

CMultithreaded_ListDlg::~CMultithreaded_ListDlg(void)
{

}

void CMultithreaded_ListDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}


///////////////////äîï ôóíêöèè////////////////

BOOL isPrime(int num)
{
	if (num <= 1)
	{
		return FALSE;
	}

	// Ïðîâåðÿåì ÷èñëà îò 2 äî êîðíÿ èç num
	for (int i = 2; i <= sqrt(num); ++i) {
		if (num % i == 0)
			return FALSE;
	}
	return TRUE;
}


//////////////////////////////////////////////

DWORD WINAPI Thread_PrimeNumbersInRange(LPVOID lp)//ïðîñòûå ÷èñëà
{
	HWND hList1 = (HWND)lp;

	SendMessage(hList1, LB_RESETCONTENT, 0, 0); // Î÷èñòèì ñïèñîê ïåðåä äîáàâëåíèåì ÷èñåë

	for (int i = 1; i <= 50000; ++i)
	{

		if (isPrime(i)) {

			wchar_t buffer[50]; // Áóôåð äëÿ ïðåîáðàçîâàíèÿ ÷èñëà â ñòðîêó

			wsprintf(buffer, TEXT("%d"), i); // Ïðåîáðàçîâàíèå ÷èñëà â ñòðîêó

			SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)buffer); // Äîáàâëåíèå ÷èñëà â ñïèñîê

			// Ïðîêðóòêà ñïèñêà âíèç
			int count = SendMessage(hList1, LB_GETCOUNT, 0, 0);
			SendMessage(hList1, LB_SETCURSEL, count - 1, 0);
			SendMessage(hList1, LB_SETCARETINDEX, count - 1, TRUE);

			Sleep(100); // Ïàóçà â 100 ìèëëèñåêóíä
		}
	}

	return FALSE;
}

DWORD WINAPI Thread_EvenNumbersInRange(LPVOID lp)//÷¸òíûå ÷èñëà
{
	HWND hList2 = (HWND)lp;

	SendMessage(hList2, LB_RESETCONTENT, 0, 0); // Î÷èñòèì ñïèñîê ïåðåä äîáàâëåíèåì ÷èñåë

	for (int i = 2; i <= 50000; i += 2)
	{
		wchar_t buffer[50]; // Áóôåð äëÿ ïðåîáðàçîâàíèÿ ÷èñëà â ñòðîêó

		wsprintf(buffer, TEXT("%d"), i); // Ïðåîáðàçîâàíèå ÷èñëà â ñòðîêó

		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)buffer); // Äîáàâëåíèå ÷èñëà â ñïèñîê

		// Ïðîêðóòêà ñïèñêà âíèç
		int count = SendMessage(hList2, LB_GETCOUNT, 0, 0);
		SendMessage(hList2, LB_SETCURSEL, count - 1, 0);
		SendMessage(hList2, LB_SETCARETINDEX, count - 1, TRUE);

		Sleep(100); // Ïàóçà â 100 ìèëëèñåêóíä
	}

	return FALSE;
}

DWORD WINAPI Thread_AllNumbersInRange(LPVOID lp)//÷èñëà îò 0 äî 20,000
{
	HWND hList3 = (HWND)lp;

	SendMessage(hList3, LB_RESETCONTENT, 0, 0); // Î÷èñòèì ñïèñîê ïåðåä äîáàâëåíèåì ÷èñåë

	for (int i = 2; i <= 20000; ++i)
	{

		wchar_t buffer[50]; // Áóôåð äëÿ ïðåîáðàçîâàíèÿ ÷èñëà â ñòðîêó

		wsprintf(buffer, TEXT("%d"), i); // Ïðåîáðàçîâàíèå ÷èñëà â ñòðîêó

		SendMessage(hList3, LB_ADDSTRING, 0, (LPARAM)buffer); // Äîáàâëåíèå ÷èñëà â ñïèñîê

		// Ïðîêðóòêà ñïèñêà âíèç
		int count = SendMessage(hList3, LB_GETCOUNT, 0, 0);
		SendMessage(hList3, LB_SETCURSEL, count - 1, 0);
		SendMessage(hList3, LB_SETCARETINDEX, count - 1, TRUE);

		Sleep(100); // Ïàóçà â 100 ìèëëèñåêóíä
	}

	return FALSE;
}


BOOL  CMultithreaded_ListDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	// Óñòàíîâêà çàãîëîâêà îêíà
	SetWindowText(hwnd, TEXT("Multithreaded_List"));


	hList1 = GetDlgItem(hwnd, IDC_LIST1);
	hList2 = GetDlgItem(hwnd, IDC_LIST2);
	hList3 = GetDlgItem(hwnd, IDC_LIST3);

	hPlay1 = GetDlgItem(hwnd, IDC_PLAY1);
	hPlay2 = GetDlgItem(hwnd, IDC_PLAY2);
	hPlay3 = GetDlgItem(hwnd, IDC_PLAY3);

	Th1 = CreateThread(NULL, 0, Thread_PrimeNumbersInRange, hList1, CREATE_SUSPENDED, NULL);
	Th2 = CreateThread(NULL, 0, Thread_EvenNumbersInRange, hList2, CREATE_SUSPENDED, NULL);
	Th3 = CreateThread(NULL, 0, Thread_AllNumbersInRange, hList3, CREATE_SUSPENDED, NULL);

	return TRUE;
}

void CMultithreaded_ListDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_PLAY1)
	{
		static BOOL flag = FALSE;

		if (flag)
		{
			SuspendThread(Th1);
			SetWindowText(hPlay1, TEXT("Ïóñê"));
		}
		else
		{
			ResumeThread(Th1);
			SetWindowText(hPlay1, TEXT("Ïàóçà"));
		}

		flag = !flag;
	}

	if (id == IDC_PLAY2)
	{
		static BOOL flag = FALSE;

		if (flag)
		{
			SuspendThread(Th2);
			SetWindowText(hPlay2, TEXT("Ïóñê"));
		}
		else
		{
			ResumeThread(Th2);
			SetWindowText(hPlay2, TEXT("Ïàóçà"));
		}

		flag = !flag;
	}

	if (id == IDC_PLAY3)
	{
		static BOOL flag = FALSE;

		if (flag)
		{
			SuspendThread(Th3);
			SetWindowText(hPlay3, TEXT("Ïóñê"));
		}
		else
		{
			ResumeThread(Th3);
			SetWindowText(hPlay3, TEXT("Ïàóçà"));
		}

		flag = !flag;
	}

	else if (id == IDC_STOP1)
	{
		TerminateThread(Th1, 0);
		CloseHandle(Th1);
		EnableWindow(hPlay1, FALSE);
	}

	else if (id == IDC_STOP2)
	{
		TerminateThread(Th2, 0);
		CloseHandle(Th2);
		EnableWindow(hPlay2, FALSE);
	}

	else if (id == IDC_STOP3)
	{
		TerminateThread(Th3, 0);
		CloseHandle(Th3);
		EnableWindow(hPlay3, FALSE);
	}


}


BOOL CALLBACK CMultithreaded_ListDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}