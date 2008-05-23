//////////////////////////////////////////////////
// ThreadApp.h
//  Declaration of the CThreadApp class


#ifndef THREADAPP_H
#define THREADAPP_H


#include "MainWnd.h"
#include <string>
#include <sstream>


class CThreadApp : public CWinApp
{
public:
	CThreadApp();
	virtual ~CThreadApp();
	virtual BOOL InitInstance();
	CMainWindow& GetMainWnd() {return m_MainWnd;}

private:
	CMainWindow m_MainWnd;	
};


// returns a reference to the CThreadApp object
inline CThreadApp& GetThreadApp() { return *((CThreadApp*)GetApp()); }


#endif  //THREADAPP_H

