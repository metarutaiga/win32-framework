// Win32++  Version 6.61
// Released: 30th August, 2009 by:
//
//      David Nash
//      email: dnash@bigpond.net.au
//      url: https://sourceforge.net/projects/win32-framework
//
//
// Copyright (c) 2005-2009  David Nash
//
// Permission is hereby granted, free of charge, to
// any person obtaining a copy of this software and
// associated documentation files (the "Software"),
// to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom
// the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice
// shall be included in all copies or substantial portions
// of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
// ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////


#include "propertysheet.h"

namespace Win32xx
{

	//////////////////////////////////////////
	// Definitions for the CPropertyPage class
	//
	CPropertyPage::CPropertyPage(UINT nIDTemplate, LPCTSTR szTitle /* = NULL*/)
	{
		ZeroMemory(&m_PSP, sizeof(PROPSHEETPAGE));
		SetTitle(szTitle);

		m_PSP.dwSize        = sizeof(PROPSHEETPAGE);
		m_PSP.dwFlags       |= PSP_USECALLBACK;
		m_PSP.hInstance     = GetApp()->GetResourceHandle();
		m_PSP.pszTemplate   = MAKEINTRESOURCE(nIDTemplate);
		m_PSP.pszTitle      = m_Title.c_str();
		m_PSP.pfnDlgProc    = (DLGPROC)CPropertyPage::StaticDialogProc;
		m_PSP.lParam        = (LPARAM)this;
		m_PSP.pfnCallback   = CPropertyPage::StaticPropSheetPageProc;
	}

	void CPropertyPage::CancelToClose() const
	{
		// Disables the Cancel button and changes the text of the OK button to "Close."
		if (m_hWnd)
			::SendMessage(m_hWnd, PSM_CANCELTOCLOSE, 0L, 0L);
	}


	BOOL CPropertyPage::DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		// Override this function in your class derrived from CPropertyPage if you wish to handle messages
		// A typical function might look like this:

		//	switch (uMsg)
		//	{
		//	case MESSAGE1:		// Some Win32 API message
		//		OnMessage1();	// A user defined function
		//		break;			// Also do default processing
		//	case MESSAGE2:
		//		OnMessage2();
		//		return x;		// Don't do default processing, but instead return
		//						//  a value recommended by the Win32 API documentation
		//	}

		// Always pass unhandled messages on to DialogProcDefault
		return DialogProcDefault(uMsg, wParam, lParam);
	}

	BOOL CPropertyPage::DialogProcDefault(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		// All unhandled property page messages end up here

		switch (uMsg)
	    {
	    case WM_INITDIALOG:
		    return OnInitDialog();

		case PSM_QUERYSIBLINGS:
			return (BOOL)OnQuerySiblings(wParam, lParam);

		case WM_COMMAND:
			{
				// Refelect this message if it's from a control
				CWnd* pWnd = FromHandle((HWND)lParam);
				if (pWnd != NULL)
					if (pWnd->OnMessageReflect(uMsg, wParam, lParam))
						return TRUE;

				// Handle user commands
				if (OnCommand(wParam, lParam))
					return TRUE;
			}
			break;

		case WM_NOTIFY:
			{
				// Do Notification reflection if it came from a CWnd object
				HWND hwndFrom = ((LPNMHDR)lParam)->hwndFrom;
				CWnd* pWndFrom = FromHandle(hwndFrom);

				if (pWndFrom != NULL)
				{	
					// Only reflect messages from the parent to avoid possible double handling
					if (::GetParent(hwndFrom) == m_hWnd)
					{
						BOOL bReturn = (BOOL)pWndFrom->OnNotifyReflect(wParam, lParam);
						if (bReturn) return TRUE;
					}
				}
			}
			return (BOOL)OnNotify(wParam, lParam);

		// A set of messages to be reflected back to the control that generated them
		case WM_CTLCOLORBTN:
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORDLG:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORSCROLLBAR:
		case WM_CTLCOLORSTATIC:
		case WM_DRAWITEM:
		case WM_MEASUREITEM:
		case WM_DELETEITEM:
		case WM_COMPAREITEM:
		case WM_CHARTOITEM:
		case WM_VKEYTOITEM:
		case WM_HSCROLL:
		case WM_VSCROLL:
		case WM_PARENTNOTIFY:
			return (BOOL) MessageReflect(m_hWnd, uMsg, wParam, lParam);

	    } // switch(uMsg)
	    return 0L;

	} // LRESULT CALLBACK CPropertyPage::DialogProc(...)

	BOOL CPropertyPage::IsButtonEnabled(int iButton) const
	{
		HWND hWnd = ::GetDlgItem(::GetParent(m_hWnd), iButton);
		return ::IsWindowEnabled(hWnd);
	}

	void CPropertyPage::OnApply()
	{
		// This function is called for each page when the Apply button is pressed
		// Override this function in your derived class if required.

		// Set the return value for this notification
		SetWindowLongPtr(DWLP_MSGRESULT, Validate());
	}

	void CPropertyPage::OnCancel()
	{
		// This function is called for each page when the Cancel button is pressed
		// Override this function in your derived class if required.
	}

	BOOL CPropertyPage::OnQueryCancel()
	{
		// Called when the cancel button is pressed, and before the cancel has taken place

		return TRUE;    // Allow cancel to proceed
	}

	BOOL CPropertyPage::OnQuerySiblings(WPARAM /*wParam*/, LPARAM /*lParam*/)
	{
		// Responds to a query request from the Property Sheet.
		// The values for wParam and lParam are the ones set by
		// the CPropertySheet::QuerySiblings call

		// return zero to allow other siblings to be queried, or
		// return nonzero to stop query at this page.
		return 0;
	}

	BOOL CPropertyPage::OnInitDialog()
	{
		// Called when the property page is created
		// Override this function in your derived class if required.

		return TRUE; // Pass Keyboard control to handle in WPARAM
	}

	void CPropertyPage::OnKillActive()
	{
		// This is called in response to a PSN_KILLACTIVE notification, which
		// is sent whenever the OK or Apply button is pressed.
		// It provides an opportunity to validate the page contents before it's closed.

		// Set the return value for this notification
		SetWindowLongPtr(DWLP_MSGRESULT, Validate());

	}

	void CPropertyPage::OnOK()
	{
		// Called for each page when the OK button is pressed
		// Override this function in your derived class if required.

		// Set the return value for this notification
		SetWindowLongPtr(DWLP_MSGRESULT, Validate());
	}

	void CPropertyPage::OnSetActive()
	{
		// Called when a page becomes active
		// Override this function in your derived class if required.
	}

	void CPropertyPage::OnWizardBack()
	{
		// This function is called when the Back button is pressed on a wizard page
		// Override this function in your derived class if required.
	}

	BOOL CPropertyPage::OnWizardFinish()
	{
		// This function is called when the Finish button is pressed on a wizard page
		// Override this function in your derived class if required.

		return TRUE; // Allow wizard to finish
	}

	void CPropertyPage::OnWizardNext()
	{
		// This function is called when the Next button is pressed on a wizard page
		// Override this function in your derived class if required.
	}

	LRESULT CPropertyPage::OnNotify(WPARAM /*wParam*/, LPARAM lParam)
	{
		LPPSHNOTIFY pNotify = (LPPSHNOTIFY)lParam;
		switch(pNotify->hdr.code)
		{
		case PSN_SETACTIVE:
			OnSetActive();
			return TRUE;
		case PSN_KILLACTIVE:
			OnKillActive();
			return TRUE;
		case PSN_APPLY:
			if (pNotify->lParam)
				OnOK();
			else
				OnApply();
			return TRUE;
		case PSN_RESET:
			OnCancel();
			return TRUE;
		case PSN_QUERYCANCEL:
			return !OnQueryCancel();
		case PSN_WIZNEXT:
			OnWizardNext();
			return TRUE;
		case PSN_WIZBACK:
			OnWizardBack();
			return TRUE;
		case PSN_WIZFINISH:
			return !OnWizardFinish();
		case PSN_HELP:
			SendMessage(m_hWnd, WM_COMMAND, ID_HELP, 0L);
			return TRUE;

		}
		return FALSE;
	}

	void CPropertyPage::SetModified(BOOL bChanged) const
	{
		if (m_hWnd != NULL)
		{
			if (bChanged)
				::SendMessage(GetParent(), PSM_CHANGED, (WPARAM)m_hWnd, 0L);
			else
				::SendMessage(GetParent(), PSM_UNCHANGED, (WPARAM)m_hWnd, 0L);
		}
	}

	void CPropertyPage::SetTitle(LPCTSTR szTitle)
	{
		if (szTitle)
		{
			m_Title = szTitle;
			m_PSP.dwFlags |= PSP_USETITLE;
		}
		else
		{
			m_Title.erase();
			m_PSP.dwFlags &= ~PSP_USETITLE;
		}

		m_PSP.pszTitle = m_Title.c_str();
	}

	UINT CALLBACK CPropertyPage::StaticPropSheetPageProc(HWND /*hwnd*/, UINT uMsg, LPPROPSHEETPAGE ppsp)
	{
		// Note: the hwnd is always NULL
		try
		{
			switch (uMsg)
			{
			case PSPCB_CREATE:
				{
					TLSData* pTLSData = (TLSData*)TlsGetValue(GetApp()->GetTlsIndex());
					if (NULL == pTLSData)
						throw CWinException(_T("CWnd::StaticCBTProc ... Unable to get TLS"));

					// Store the CPropertyPage pointer in Thread Local Storage
					pTLSData->pCWnd = (CWnd*)ppsp->lParam;
				}

				return TRUE;
			}
		}

		catch (const CWinException &e)
		{
			e.MessageBox();
		}

		catch (...)
		{
			DebugErrMsg(_T("CPropertyPage::StaticPropSheetPageProc"));
			throw;	// Rethrow unknown exception
		}

		return TRUE;
	}

	BOOL CALLBACK CPropertyPage::StaticDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		// Find matching CWnd pointer for this HWND
		CPropertyPage* pPage = (CPropertyPage*)GetApp()->GetCWndFromMap(hwndDlg);
		if (pPage != 0)
		{
			// matching CWnd pointer found for this HWND, so call DialogProc
			return pPage->DialogProc(uMsg, wParam, lParam);
		}
		else
		{
			// matching CWnd pointer not found, so add it to HWNDMap now
			TLSData* pTLSData = (TLSData*)TlsGetValue(GetApp()->GetTlsIndex());
			pPage = (CPropertyPage*)pTLSData->pCWnd;

			// Set the hWnd members and call DialogProc for this message
			pPage->m_hWnd = hwndDlg;
			pPage->AddToMap();
			return pPage->DialogProc(uMsg, wParam, lParam);
		}

	}

	int CPropertyPage::Validate()
	{
		// Override this function in your derived class if required.
		// This function is used to validate the page. Specify the appropriate return
		// value to indicate whether or not the page is valid.

		// The possible return values are:
		// PSNRET_NOERROR. The changes made to this page are valid and have been applied
		// PSNRET_INVALID. The property sheet will not be destroyed, and focus will be returned to this page.
		// PSNRET_INVALID_NOCHANGEPAGE. The property sheet will not be destroyed, and focus will be returned
		//                               to the page that had focus when the button was pressed.


		int nStatus = PSNRET_NOERROR;
	//	int nStatus = PSNRET_INVALID;
	//	int nStatus = PSNRET_INVALID_NOCHANGEPAGE;

		// Tell the user what went wrong
		if (nStatus != PSNRET_NOERROR)
			MessageBox(_T("Validation Failed"), _T("PageSheet Check"), MB_OK);

		return nStatus;
	}


	///////////////////////////////////////////
	// Definitions for the CPropertySheet class
	//
	CPropertySheet::CPropertySheet(UINT nIDCaption, HWND hwndParent /* = NULL*/)
	{
		ZeroMemory(&m_PSH, sizeof (PROPSHEETHEADER));
		m_ppsp = NULL;
		SetTitle(LoadString(nIDCaption));

#ifdef _WIN32_WCE
		m_PSH.dwSize = sizeof(PROPSHEETHEADER);
#else
		if (GetComCtlVersion() >= 471)
			m_PSH.dwSize = sizeof(PROPSHEETHEADER);
		else
			m_PSH.dwSize = PROPSHEETHEADER_V1_SIZE;
#endif

		m_PSH.dwFlags          = PSH_PROPSHEETPAGE | PSH_USECALLBACK;
		m_PSH.hwndParent       = hwndParent;
		m_PSH.hInstance        = GetApp()->GetInstanceHandle();
		m_PSH.pfnCallback      = (PFNPROPSHEETCALLBACK)CPropertySheet::Callback;
	}

	CPropertySheet::CPropertySheet(LPCTSTR pszCaption /*= NULL*/, HWND hwndParent /* = NULL*/)
	{
		ZeroMemory(&m_PSH, sizeof (PROPSHEETHEADER));
		m_ppsp = NULL;
		SetTitle(pszCaption);

#ifdef _WIN32_WCE
		m_PSH.dwSize = PROPSHEETHEADER_V1_SIZE;
#else
		if (GetComCtlVersion() >= 471)
			m_PSH.dwSize = sizeof(PROPSHEETHEADER);
		else
			m_PSH.dwSize = PROPSHEETHEADER_V1_SIZE;
#endif

		m_PSH.dwFlags          = PSH_PROPSHEETPAGE | PSH_USECALLBACK;
		m_PSH.hwndParent       = hwndParent;
		m_PSH.hInstance        = GetApp()->GetInstanceHandle();
		m_PSH.pfnCallback      = (PFNPROPSHEETCALLBACK)CPropertySheet::Callback;
	}

	CPropertySheet::~CPropertySheet()
	{
		for (int i = 0 ; i < (int)m_vPages.size(); i++)
			delete m_vPages[i];

		delete []m_ppsp;
	}

	CPropertyPage* CPropertySheet::AddPage(CPropertyPage* pPage)
	{
		if (NULL == pPage)
			throw CWinException(_T("Cannot add NULL Property Page"));

		m_vPages.push_back(pPage);

		if (m_hWnd)
		{
			// property sheet already exists, so add page to it
			PROPSHEETPAGE psp = pPage->GetPSP();
			HPROPSHEETPAGE hpsp = ::CreatePropertySheetPage(&psp);
			PropSheet_AddPage(m_hWnd, hpsp);
		}

		m_PSH.nPages = (int)m_vPages.size();

		return pPage;
	}

	void CPropertySheet::BuildPageArray()
	{
		delete []m_ppsp;
		m_ppsp = NULL;
		m_ppsp = new PROPSHEETPAGE[m_vPages.size()];

		for (int i = 0 ; i < (int)m_vPages.size(); i++)
		{
			m_ppsp[i] = m_vPages[i]->GetPSP();
		}

		m_PSH.ppsp = (LPCPROPSHEETPAGE) m_ppsp;
	}

	void CALLBACK CPropertySheet::Callback(HWND hwnd, UINT uMsg, LPARAM lParam)
	{
		switch(uMsg)
		{
		//called before the dialog is created, hwnd = NULL, lParam points to dialog resource
		case PSCB_PRECREATE:
			{
				LPDLGTEMPLATE  lpTemplate = (LPDLGTEMPLATE)lParam;

				if(!(lpTemplate->style & WS_SYSMENU))
				{
					lpTemplate->style |= WS_SYSMENU;
				}
			}
			break;

		//called after the dialog is created
		case PSCB_INITIALIZED:
			try
			{
				// Retrieve pointer to CWnd object from Thread Local Storage
				TLSData* pTLSData = (TLSData*)TlsGetValue(GetApp()->GetTlsIndex());
				if (!pTLSData)
					throw CWinException(_T("CPropertySheet::Callback ... Unable to get TLS"));

				CPropertySheet* w = (CPropertySheet*)pTLSData->pCWnd;
				if (!w)
					throw CWinException(_T("CPropertySheet::Callback ... Failed to get CWnd"));

				w->Attach(hwnd);
				w->OnCreate();
			}

			catch (const CWinException &e)
			{
				e.MessageBox();
			}

			catch (...)
			{
				DebugErrMsg(_T("Exception in CPropertySheet::Callback"));
				throw;	// Rethrow unknown exception
			}

			break;
		}
	}


	HWND CPropertySheet::Create(HWND hWndParent /*= 0*/)
	// Creates a modeless Property sheet
	{
		if (hWndParent)
		{
			m_PSH.hwndParent = hWndParent;
		}

		BuildPageArray();
		m_PSH.ppsp = m_ppsp;

		// Create a modeless Property Sheet
		m_PSH.dwFlags &= ~PSH_WIZARD;
		m_PSH.dwFlags |= PSH_MODELESS;
		HWND hWnd = (HWND)CreatePropertySheet(&m_PSH);

		return hWnd;
	}

	INT_PTR CPropertySheet::CreatePropertySheet(LPCPROPSHEETHEADER ppsph)
	{
		INT_PTR ipResult = 0;

		try
		{
			// Only one window per CWnd instance allowed
			if (::IsWindow(m_hWnd))
				throw CWinException(_T("CreatePropertySheet ... Window already exists"));

			// Ensure this thread has the TLS index set
			TLSData* pTLSData = GetApp()->SetTlsIndex();

			// Store the 'this' pointer in Thread Local Storage
			pTLSData->pCWnd = this;

			// Create the property sheet
			ipResult = PropertySheet(ppsph);

		}

		catch (const CWinException &e)
		{
			e.MessageBox();
		}

		catch (...)
		{
			DebugErrMsg(_T("Exception in CPropertySheet::CreatePropertySheet"));
			throw;	// Rethrow unknown exception
		}

		return ipResult;
	}

	void CPropertySheet::DestroyButton(int IDButton)
	{
		if (m_hWnd != NULL)
		{
			HWND hwndButton = ::GetDlgItem(m_hWnd, IDButton);
			if (hwndButton != NULL)
			{
				::ShowWindow(hwndButton, SW_HIDE);
				::EnableWindow(hwndButton, FALSE);
			}
		}
	}

	void CPropertySheet::Destroy()
	{
		CWnd::Destroy();

		for (int i = 0 ; i < (int)m_vPages.size(); i++)
			delete m_vPages[i];

		m_vPages.clear();
	}

	int CPropertySheet::DoModal()
	{
		BuildPageArray();
		m_PSH.ppsp = m_ppsp;

		// Create the Property Sheet
		int nResult = (int)CreatePropertySheet(&m_PSH);

		for (int j = 0 ; j < (int)m_vPages.size(); j++)
		{
			delete m_vPages[j];
		}
		m_vPages.clear();

		return nResult;
	}

	CPropertyPage* CPropertySheet::GetActivePage() const
	{
		CPropertyPage* pPage = NULL;
		if (m_hWnd != NULL)
		{
			HWND hPage = (HWND)::SendMessage(m_hWnd, PSM_GETCURRENTPAGEHWND, 0L, 0L);
			pPage = (CPropertyPage*)FromHandle(hPage);
		}

		return pPage;
	}

	int CPropertySheet::GetPageCount() const
	{
		return (int)m_vPages.size();
	}

	int CPropertySheet::GetPageIndex(CPropertyPage* pPage) const
	{
		for (int i = 0; i < GetPageCount(); i++)
		{
			if (m_vPages[i] == pPage)
				return i;
		}
		return -1;
	}

	HWND CPropertySheet::GetTabControl() const
	{
		return (HWND)SendMessage(m_hWnd, PSM_GETTABCONTROL, 0L, 0L);
	}

	BOOL CPropertySheet::IsModeless() const
	{
		return (m_PSH.dwFlags & PSH_MODELESS);
	}

	BOOL CPropertySheet::IsWizard() const
	{
		return (m_PSH.dwFlags & PSH_WIZARD);
	}

	void CPropertySheet::OnCreate()
	{
		// Adjust layout for modeless property sheet
		if ((IsModeless()) && !(IsWizard()))
		{
			// Reposition windows
			RECT rc;
			::GetWindowRect(m_hWnd, &rc);
			RECT rcButton;
			HWND hwndOKButton = ::GetDlgItem(m_hWnd, IDOK);
			::GetWindowRect(hwndOKButton, &rcButton);
			::SetWindowPos(m_hWnd, NULL, 0, 0, rc.right - rc.left, rcButton.top - rc.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

			// Remove buttons
			DestroyButton(IDOK);
			DestroyButton(IDCANCEL);
			DestroyButton(ID_APPLY_NOW);
			DestroyButton(IDHELP);
		}

		// Remove system menu for wizards
		if (IsWizard())
		{
			DWORD dwStyle = (DWORD)::GetWindowLongPtr(m_hWnd, GWL_STYLE);
			dwStyle &= ~WS_SYSMENU;
			::SetWindowLongPtr(m_hWnd, GWL_STYLE, dwStyle);
		}
	}

	void CPropertySheet::OnInitialUpdate()
	{
		CenterWindow();
	}

	void CPropertySheet::RemovePage(CPropertyPage* pPage)
	{
		int nPage = GetPageIndex(pPage);
		if (m_hWnd != NULL)
			SendMessage(m_hWnd, PSM_REMOVEPAGE, nPage, 0L);

		m_vPages.erase(m_vPages.begin() + nPage, m_vPages.begin() + nPage+1);
		m_PSH.nPages = (int)m_vPages.size();
	}

	BOOL CPropertySheet::PreTranslateMessage(MSG* pMsg)
	{
		// allow sheet to translate Ctrl+Tab, Shift+Ctrl+Tab, Ctrl+PageUp, and Ctrl+PageDown
		if (pMsg->message == WM_KEYDOWN && GetAsyncKeyState(VK_CONTROL) < 0 &&
			(pMsg->wParam == VK_TAB || pMsg->wParam == VK_PRIOR || pMsg->wParam == VK_NEXT))
		{
			if (SendMessage(PSM_ISDIALOGMESSAGE, 0L, (LPARAM)pMsg))
				return TRUE;
		}

		// allow the dialog to translate keyboard input
		if ((pMsg->message >= WM_KEYFIRST) && (pMsg->message <= WM_KEYLAST))
		{
			if (IsDialogMessage(m_hWnd, pMsg))
				return TRUE;
		}

		return CWnd::PreTranslateMessage(pMsg);
	}

	LRESULT CPropertySheet::QuerySiblings(WPARAM wParam, LPARAM lParam)
	{
		// Set wParam and lParam to values you want passed to the
		// property pages in CPropertyPage::OnQuerySiblings.

		return ::SendMessage(m_hWnd, PSM_QUERYSIBLINGS, wParam, lParam);
	}

	BOOL CPropertySheet::SetActivePage(int nPage)
	{
		if (m_hWnd != NULL)
			return (BOOL)SendMessage(m_hWnd, PSM_SETCURSEL, nPage, 0L);

		return FALSE;
	}

	BOOL CPropertySheet::SetActivePage(CPropertyPage* pPage)
	{
		int nPage = GetPageIndex(pPage);
		if ((m_hWnd != NULL) && (nPage >= 0))
			return SetActivePage(nPage);

		return FALSE;
	}

	void CPropertySheet::SetTitle(LPCTSTR szTitle)
	{
		if (szTitle)
			m_Title = szTitle;
		else
			m_Title.erase();

		m_PSH.pszCaption = m_Title.c_str();
	}

	void CPropertySheet::SetWizardMode(BOOL bWizard)
	{
		if (bWizard)
			m_PSH.dwFlags |= PSH_WIZARD;
		else
			m_PSH.dwFlags &= ~PSH_WIZARD;
	}

	LRESULT CPropertySheet::WndProcDefault(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		static BOOL bFirstTime = TRUE;
		switch (uMsg)
		{
		case WM_ACTIVATE:
			if (bFirstTime)
				OnInitialUpdate();
			bFirstTime = FALSE;
			break;

		case WM_DESTROY:
			bFirstTime = TRUE;
			break;

		case WM_SYSCOMMAND:
			if ((SC_CLOSE == wParam) && (m_PSH.dwFlags &  PSH_MODELESS))
			{
				Destroy();
				return 0L;
			}
			break;
		}

		// pass unhandled messages on for default processing
		return CWnd::WndProcDefault(uMsg, wParam, lParam);
	}

}
