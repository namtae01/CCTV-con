// SingleLive.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSingleLiveApp:
// See SingleLive.cpp for the implementation of this class
//

class CSingleLiveApp : public CWinApp
{
public:
	CSingleLiveApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSingleLiveApp theApp;