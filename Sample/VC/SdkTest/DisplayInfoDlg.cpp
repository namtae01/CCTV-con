///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011 by Hanwha Techwin, Inc.
//
// This software is copyrighted by, and is the sole property of Hanwha Techwin.
// All rigths, title, ownership, or other interests in the software remain the
// property of Hanwha Techwin. This software may only be used in accordance with
// the corresponding license agreement. Any unauthorized use, duplication,
// transmission, distribution, or disclosure of this software is expressly
// forbidden.
//
// This Copyright notice may not be removed or modified without prior written
// consent of Hanwha Techwin.
//
// Hanwha Techwin reserves the right to modify this software without notice.
//
// Hanwha Techwin, Inc.
// http://security.hanwhatechwin.com/
///////////////////////////////////////////////////////////////////////////////////
// DisplayInfo.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "DisplayInfoDlg.h"

#include "SdkTestDlg.h"


// CDisplayInfo dialog

IMPLEMENT_DYNAMIC(CDisplayInfo, CDialog)

CDisplayInfo::CDisplayInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDisplayInfo::IDD, pParent)
	, m_hMediaSource(0)
	, m_pCtrlXnsDevice(0)
	, m_pCtrlXnsWindowLive(0)
	, m_pCtrlXnsWindowPlayback(0)
{
	if(pParent)
	{
		CSdkTestDlg *ptr = dynamic_cast<CSdkTestDlg *>(pParent);
		m_pCtrlXnsDevice = &(ptr->m_ctrlXnsDevice);
		m_pCtrlXnsWindowLive = &(ptr->m_ctrlXnsWindowLive);
		m_pCtrlXnsWindowPlayback = &(ptr->m_ctrlXnsWindowPlayback);
		m_pCtrlEditLog = ptr->m_pCtrlEditLog;
		m_pCtrlEditEvent = ptr->m_pCtrlEditEvent;
		m_pHDevice = &(ptr->m_hDevice);
		m_pHMediaSource = &(ptr->m_hMediaSource);
		m_pHMediaSourcePlayback = &(ptr->m_hMediaSourcePlayback);
		m_pNControlId = &(ptr->m_nControlId);
	}
}

CDisplayInfo::~CDisplayInfo()
{
}

void CDisplayInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDisplayInfo, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_GET_CURRENT_FRAMETIME, &CDisplayInfo::OnBnClickedButtonGetCurrentFrametime)
	ON_BN_CLICKED(IDC_BUTTON_FIRST_FRAMETIME, &CDisplayInfo::OnBnClickedButtonFirstFrametime)
	ON_BN_CLICKED(IDC_BUTTON_SET_BRIGHTNESS, &CDisplayInfo::OnBnClickedButtonSetBrightness)
	ON_BN_CLICKED(IDC_BUTTON_GET_BRIGHTNESS, &CDisplayInfo::OnBnClickedButtonGetBrightness)
	ON_BN_CLICKED(IDC_BUTTON_SET_CONTRAST, &CDisplayInfo::OnBnClickedButtonSetContrast)
	ON_BN_CLICKED(IDC_BUTTON_GET_CONTRAST, &CDisplayInfo::OnBnClickedButtonGetContrast)
	ON_BN_CLICKED(IDC_BUTTON_SET_DEINTERLACEMODE, &CDisplayInfo::OnBnClickedButtonSetDeinterlacemode)
	ON_BN_CLICKED(IDC_BUTTON_SET_DEFOGMODE, &CDisplayInfo::OnBnClickedButtonSetDefogmode)
END_MESSAGE_MAP()


// CDisplayInfo message handlers

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Function Name : GetCurrentFrameTime()
// Gets the frame time that is currently displayed on the screen.
// -----------------------------------------------------------------------
void CDisplayInfo::OnBnClickedButtonGetCurrentFrametime()
{
	GET_XNS_PARAM();

	long nRet = m_pCtrlXnsWindowLive->GetCurrentFrameTime();
	WLOGW(_T("GetCurrentFrameTime() :: %d\n"), nRet);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Function Name : GetFirstFrameTime()
// Gets the first frame time.
// -----------------------------------------------------------------------
void CDisplayInfo::OnBnClickedButtonFirstFrametime()
{
	GET_XNS_PARAM();

	long nRet = m_pCtrlXnsWindowLive->GetFirstFrameTime();
	WLOGW(_T("GetFirstFrameTime() :: %d\n"), nRet);
}


void CDisplayInfo::OnBnClickedButtonSetBrightness()
{
	GET_XNS_PARAM();

 	m_pCtrlXnsWindowLive->SetBrightness(DISPLAY_VAlUE);
	WLOGW(_T("SetBrightness() :: Brightness Value :%d\n"), DISPLAY_VAlUE);

}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Function Name : GetBrightness()
// Gets the specified value of brightness.
// -----------------------------------------------------------------------
void CDisplayInfo::OnBnClickedButtonGetBrightness()
{
	GET_XNS_PARAM();

	long nRet = m_pCtrlXnsWindowLive->GetBrightness();
	WLOGW(_T("GetBrightness() :: %d\n"), nRet);

}
// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Function Name : SetContrast()
// Sets the contrast.
// -----------------------------------------------------------------------
void CDisplayInfo::OnBnClickedButtonSetContrast()
{
	GET_XNS_PARAM();

	m_pCtrlXnsWindowLive->SetContrast(DISPLAY_VAlUE);
	WLOGW(_T("SetContrast() :: Contrast Value :%d\n"), DISPLAY_VAlUE);

}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Function Name : GetContrast()
// Gets the specified value of contrast.
// -----------------------------------------------------------------------
void CDisplayInfo::OnBnClickedButtonGetContrast()
{
	GET_XNS_PARAM();

	long nRet = m_pCtrlXnsWindowLive->GetContrast();
	WLOGW(_T("GetContrast() :: %d\n"), nRet);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Function Name : SetDeinterlaceMode()
// Turns on or off de-interlace mode.
// -----------------------------------------------------------------------
void CDisplayInfo::OnBnClickedButtonSetDeinterlacemode()
{
	GET_XNS_PARAM();

	m_pCtrlXnsWindowLive->SetDeinterlaceMode(ON);
	WLOGW(_T("SetDeinterlaceMode() :: De-interlace :On\n"));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Function Name : SetDefogMode()
// Enable or disable the defog mode. 
// It supports one channel only, 
// so it is blocked when another channel is using the defog mode.
// -----------------------------------------------------------------------
void CDisplayInfo::OnBnClickedButtonSetDefogmode()
{
	GET_XNS_PARAM();

	m_pCtrlXnsWindowLive->SetDefogMode(ON);
	WLOGW(_T("SetDeinterlaceMode() :: Defog Mode :On\n"));
}
