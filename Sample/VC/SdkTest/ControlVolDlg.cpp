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
// ControlVolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "ControlVolDlg.h"

#include "SdkTestDlg.h"

// CControlVolDlg dialog

IMPLEMENT_DYNAMIC(CControlVolDlg, CDialog)

CControlVolDlg::CControlVolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControlVolDlg::IDD, pParent)
	, m_pCtrlXnsDevice(0)
	, m_pCtrlXnsWindowLive(0)
	, m_pCtrlXnsWindowPlayback(0)
	, m_bSound(FALSE)
	, m_nVolume(50)
	, m_nRadioButtonBmp(0)
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

CControlVolDlg::~CControlVolDlg()
{
}

void CControlVolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SET_VOLUME, m_nVolume);
	DDX_Radio(pDX, IDC_RADIO_BUTTON_BMP_FILE, m_nRadioButtonBmp);
}

BEGIN_MESSAGE_MAP(CControlVolDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SET_SOUND, &CControlVolDlg::OnBnClickedButtonSetSound)
	ON_BN_CLICKED(IDC_BUTTON_SET_VOLUME, &CControlVolDlg::OnBnClickedButtonSetVolume)
	ON_BN_CLICKED(IDC_BUTTON_GET_VOLUME, &CControlVolDlg::OnBnClickedButtonGetVolume)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_SNAPSHOT, &CControlVolDlg::OnBnClickedButtonSaveSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_PRINT_SNAPSHOT, &CControlVolDlg::OnBnClickedButtonPrintSnapshot)
END_MESSAGE_MAP()


// CControlVolDlg message handlers

void CControlVolDlg::OnBnClickedButtonSetSound()
{
	GET_XNS_PARAM();

	switch(m_bSound)
	{
	case TRUE:
		m_bSound = FALSE;
		WLOGW(_T("Off the sound\n"));
		break;
	case FALSE:
		m_bSound = TRUE;
		WLOGW(_T("On the sound\n"));
		break;
	}	
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Turns on or off the sound. 
	// -----------------------------------------------------------------------
	m_pCtrlXnsWindowLive->SetSound(m_bSound);
}

void CControlVolDlg::OnBnClickedButtonSetVolume()
{
	GET_XNS_PARAM();
	UpdateData(TRUE);
	
	if(m_nVolume < 0)
	{
		m_nVolume = 0;
	}
	else if(m_nVolume > 100)
	{
		m_nVolume = 100;
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Specify the volume level of the sound.
	// -----------------------------------------------------------------------
	m_pCtrlXnsWindowLive->SetVolume(
		m_nVolume);		// [in] Volume level of the sound (a value between 0 and 100).
	WLOGW(_T("SetVolume():: Volume=%d \n"), m_nVolume);
}

void CControlVolDlg::OnBnClickedButtonGetVolume()
{
	GET_XNS_PARAM();

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns the sound volume that is currently specified. 
	// -----------------------------------------------------------------------
	m_nVolume = m_pCtrlXnsWindowLive->GetVolume();	
	WLOGW(_T("GetVolume():: Volume=%d \n"), m_nVolume);
}

void CControlVolDlg::OnBnClickedButtonSaveSnapshot()
{
	GET_XNS_PARAM();
	UpdateData(TRUE);

	CString strFile;
	long nFormat = m_nRadioButtonBmp;
	if(nFormat == 0)
	{
		strFile = _T("c:\\snapshot.bmp");
	}
	else if(nFormat == 1)
	{
		strFile = _T("c:\\snapshot.jpg");
	}
	
	long nRet;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Saves the snapshot of the current image. 
	// -----------------------------------------------------------------------
	nRet = m_pCtrlXnsWindowLive->SaveSnapshot(
		strFile,		// [in] File name to save.
		nFormat);		// [in] File format of image.(0:BMP, 1:JPG)

	if(nRet == 1)
	{
		WLOGW(_T("SaveSnapshot():: %s Save Successed \n"), strFile);
	}
	else if(nRet == 0)
	{
		WLOGW(_T("SaveSnapshot():: %s Save Faild \n"), strFile);
	}
}

void CControlVolDlg::OnBnClickedButtonPrintSnapshot()
{
	GET_XNS_PARAM();

	long nRet;
	nRet = m_pCtrlXnsWindowLive->PrintSnapshot();
	if(nRet == 1)
	{
		WLOGD(_T("PrintSnapshot():: Print Successed \n"));
	}
	else if(nRet == 0)
	{
		WLOGD(_T("PrintSnapshot():: Print Faild \n"));
	}
}
