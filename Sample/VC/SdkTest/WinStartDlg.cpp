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
// WinStartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "WinStartDlg.h"

#include "SdkTestDlg.h"


// CWinStartDlg dialog

IMPLEMENT_DYNAMIC(CWinStartDlg, CDialog)

CWinStartDlg::CWinStartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinStartDlg::IDD, pParent)
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

CWinStartDlg::~CWinStartDlg()
{
}

void CWinStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWinStartDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_WIN_INIT, &CWinStartDlg::OnBnClickedButtonWinInit)
	ON_BN_CLICKED(IDC_BUTTON_WIN_START, &CWinStartDlg::OnBnClickedButtonWinStart)
	ON_BN_CLICKED(IDC_BUTTON_WIN_STOP, &CWinStartDlg::OnBnClickedButtonWinStop)
	ON_BN_CLICKED(IDC_BUTTON_WIN_DEVICE_STATUS, &CWinStartDlg::OnBnClickedButtonWinDeviceStatus)
END_MESSAGE_MAP()


// CWinStartDlg message handlers

void CWinStartDlg::OnBnClickedButtonWinInit()
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Initializes the XnsSdkWindow control. Namely, this will specify the 
	// window handle in order to display images on the screen.
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsWindowLive->Initialize(NULL, NULL);
	WLOGW(_T("Initialize()::Live Window: ret=%d(%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));

	nRet = m_pCtrlXnsWindowPlayback->Initialize(NULL, NULL);
	WLOGW(_T("Initialize()::Playback Window: ret=%d(%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CWinStartDlg::OnBnClickedButtonWinStart()
{
	GET_XNS_PARAM()

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Adds the media source handle to XnsSdkWindow. 
	// The media source handle is created by XnsSdkDevice. 
	// If the application calls XnsSdkDevice::OpenMedia(), 
	// it will receive media stream from the device and return the MediaSource 
	// handle. The application uses uses Start() to forward the mediasource 
	// handle to XnsSdkWindow so that XnsSdkWindow can obtain stream data. 
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsWindowLive->Start(m_hMediaSource);
	WLOGW(_T("Start():: ret=%d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CWinStartDlg::OnBnClickedButtonWinStop()
{
	GET_XNS_PARAM()

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Stops receiving the stream data from the media source handle.  
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsWindowLive->Stop();
	WLOGW(_T("Stop():: media source=%d\n"), nRet);
}

void CWinStartDlg::OnBnClickedButtonWinDeviceStatus()
{
	GET_XNS_PARAM();

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns the ID of the device that is connected to media source. 
	// The device ID is defined by the application using XnsSdkDevice::CreateDevice(). 
	// -----------------------------------------------------------------------
	long nDeviceID = m_pCtrlXnsWindowLive->GetDeviceID();
	if(nDeviceID == 0)
	{
		WLOGW(_T("GetDeviceID():: Indicates no device ID exists.\n"));
		return;
	}
	WLOGW(_T("GetDeviceID():: Connected Device ID = %d \n"), nDeviceID);

	// Returns the control ID from media source. 
	long nControlID = m_pCtrlXnsWindowLive->GetControlID();
	if(nControlID == 0)
	{
		WLOGW(_T("GetControlID():: Indicates no Control ID exists.\n"));
		return;
	}
	WLOGW(_T("GetControlID():: Control ID = %d \n"), nControlID);


	// Returns the width of the source image. 
	long nWidth = m_pCtrlXnsWindowLive->GetImageWidth();
	WLOGW(_T("GetImageWidth():: Image Width = %d \n"), nWidth);


	// Returns the height of the source image.
	long nHeight = m_pCtrlXnsWindowLive->GetImageHeight();
	WLOGW(_T("GetImageHeight():: Image Width = %d \n"), nHeight);

	// Check if there exists stream source. 
	long nRet = m_pCtrlXnsWindowLive->IsMedia();
	if(nRet == 1)
	{
		WLOGW(_T("IsMedia():: There exists stream source.\n"));		
	}
	else if(nRet == 0)
	{
		WLOGW(_T("IsMedia():: There exists not stream source.\n"));
	}

	// Returns the type of media currently playing. 
	CString strMediaType;
	long nMediaType = m_pCtrlXnsWindowLive->GetMediaType();
	switch(nMediaType)
	{
	case 0:
		strMediaType = _T("There is no media currently playing");
		break;
	case 1:
		strMediaType = _T("MEDIA_TYPE_LIVE");
		break;
	case 2:
		strMediaType = _T("MEDIA_TYPE_PLAYBACK");
		break;
	case 3:
		strMediaType = _T("MEDIA_TYPE_BACKUP");
		break;
	}
	WLOGW(_T("GetMediaType():: MediaType=%d(%s)\n"), nMediaType, strMediaType);
}
