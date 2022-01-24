// VideoRawData.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CVideoRawDataApp:
// See VideoRawData.cpp for the implementation of this class
//

class CVideoRawDataApp : public CWinApp
{
public:
	CVideoRawDataApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CVideoRawDataApp theApp;