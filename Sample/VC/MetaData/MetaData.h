
// MetaData.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMetaDataApp:
// �� Ŭ������ ������ ���ؼ��� MetaData.cpp�� �����Ͻʽÿ�.
//

class CMetaDataApp : public CWinApp
{
public:
	CMetaDataApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMetaDataApp theApp;