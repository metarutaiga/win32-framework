//////////////////////////////////////////////
// TestWnd.cpp
//  Definitions for the CTestWindow class

#include "ThreadApp.h"
#include "TestWnd.h"


CTestWindow::CTestWindow()
{
}

void CTestWindow::CreateWin(int i)
{
	TCHAR str[80];

	m_nThread = i + 1;
	::wsprintf(str, TEXT("Thread #%d"), m_nThread);
	CreateEx(0L, NULL, str, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		70 + 20*i, 120 + 20*i, 300, 200, NULL, NULL);
}

void CTestWindow::OnInitialUpdate()
{
	// Get a reference to the CMainWnd object
	CMainWindow& MainWnd = ((CThreadApp*)GetApp())->GetMainWnd();

	// Post a message to MainWnd when the window is created. The MainWnd window
	//  is in a different thread, so PostMessage is preferred over SendMessage.
	//  SendMessage would wait for the MainWnd thread to respond.
	::PostMessage(MainWnd.GetHwnd(), WM_WINDOWCREATED, 0, 0);
}

LRESULT CTestWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LRESULT nMessages = 0;
	switch (uMsg)
	{
	case WM_CLOSE:
		{
			TCHAR str[80];
			::wsprintf(str, TEXT("Closing test Window #%d"), m_nThread);
			TRACE(str);
		}
		break;

	case WM_DESTROY:
		// Post the WM_QUIT message to terminate the thread.
		::PostQuitMessage(0);
		return 0L;

	case WM_TESTMESSAGE:
		// return the number of WM_TESTMESSAGE messages processsed by this thread so far
		return ++nMessages;
	}

	//Use the CWnd default message handling for remaining messages
	return CWnd::WndProc(hwnd, uMsg, wParam, lParam);
}

