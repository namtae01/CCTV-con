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
// MediaStreamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "MediaStreamDlg.h"

#include "SdkTestDlg.h"


// CMediaStreamDlg dialog

IMPLEMENT_DYNAMIC(CMediaStreamDlg, CDialog)

CMediaStreamDlg::CMediaStreamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMediaStreamDlg::IDD, pParent)
	, m_hMediaSource(0)
	, m_pCtrlXnsDevice(0)
	, m_pCtrlXnsWindowLive(0)
	, m_pCtrlXnsWindowPlayback(0)
	, m_nCid(0)
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

CMediaStreamDlg::~CMediaStreamDlg()
{
}

void CMediaStreamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONTROLID, m_nCid);
}


BEGIN_MESSAGE_MAP(CMediaStreamDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ACQUIRE_MEDIA_AUTHORITY, &CMediaStreamDlg::OnBnClickedButtonAcquireMediaAuthority)
	ON_BN_CLICKED(IDC_BUTTON_RELEASE_MEDIA_AUTHORITY, &CMediaStreamDlg::OnBnClickedButtonReleaseMediaAuthority)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_MEDIA, &CMediaStreamDlg::OnBnClickedButtonOpenMedia)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_MEDIA, &CMediaStreamDlg::OnBnClickedButtonCloseMedia)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_STREAM, &CMediaStreamDlg::OnBnClickedButtonOpenStream)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_STREAM, &CMediaStreamDlg::OnBnClickedButtonCloseStream)
	ON_BN_CLICKED(IDC_BUTTON_SUSPEND_STREAM, &CMediaStreamDlg::OnBnClickedButtonSuspendStream)
	ON_BN_CLICKED(IDC_BUTTON_SUSPEND_ALL_STREAM, &CMediaStreamDlg::OnBnClickedButtonSuspendAllStream)
	ON_BN_CLICKED(IDC_BUTTON_RESUME_STREAM, &CMediaStreamDlg::OnBnClickedButtonResumeStream)
	ON_BN_CLICKED(IDC_BUTTON_RESUME_ALL_STREAM, &CMediaStreamDlg::OnBnClickedButtonResumeAllStream)
	ON_BN_CLICKED(IDC_BUTTON_REOPEN_ALL_STREAM, &CMediaStreamDlg::OnBnClickedButtonReopenAllStream)
	ON_BN_CLICKED(IDC_BUTTON_IS_PLAYING, &CMediaStreamDlg::OnBnClickedButtonIsPlaying)
	ON_BN_CLICKED(IDC_BUTTON_HAS_AUTHORITY, &CMediaStreamDlg::OnBnClickedButtonHasAuthority)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_MEDIA_EX, &CMediaStreamDlg::OnBnClickedButtonOpenMediaEx)
END_MESSAGE_MAP()


// CMediaStreamDlg message handlers

void CMediaStreamDlg::OnBnClickedButtonAcquireMediaAuthority(void)
{
	GET_XNS_PARAM();

	long nRet;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Acquires the permission to play the recorded multimedia. 
	// The application should acquire the permission using this function 
	// before it can play video.
	// -----------------------------------------------------------------------
	nRet = m_pCtrlXnsDevice->AcquireMediaAuthority(m_hDevice);
	WLOGD(_T("AcquireMediaAuthority():: ret=%d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CMediaStreamDlg::OnBnClickedButtonReleaseMediaAuthority()
{
	GET_XNS_PARAM();

	long nRet;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Releases the permission to play the multimedia contents. 
	// The application should release the play permission using this function
	// after playing the multimedia contents.
	// -----------------------------------------------------------------------
	nRet = m_pCtrlXnsDevice->ReleaseMediaAuthority(m_hDevice);
	WLOGD(_T("ReleaseMediaAuthority():: ret=%d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CMediaStreamDlg::OnBnClickedButtonOpenMedia()
{
	GET_XNS_PARAM();

	UpdateData(TRUE);
	if (m_nCid != m_nControlId)
	{
		WLOGD(_T("OpenMedia():: control id changed=%d to %d\n"), m_nControlId, m_nCid) 
		m_nControlId = m_nCid;
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// When called, it will start getting media streams from the device. 
	// The receiving media streams will, then, be forwarded to the 
	// XnsSdkWindow component that will play the streams after decoding. 
	// phMediaSource is needed to link the stream data with XnsSdkWindow. 
	// The value can be obtained from a parameter (out-parameter) of 
	// OpenMedia(). When XnsSdkWindow receives this value, it can get stream 
	// data from the device. phMediaSource is also used for controlling 
	// playback of multimedia files. As a result, the application should keep 
	// this value at all times.
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->OpenMedia(
		m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
		m_nControlId,		// [in] Control ID of video control module. 
		MEDIA_TYPE_LIVE,	// [in] Media type.
		0,					// [in] Play start time. Format: 4-byte time_t.
		0,					// [in] Play end time. Format: 4-byte time_t.
		&m_hMediaSource		// [out] Media stream ID. This is needed for controlling 
							//       the media stream and also used as a parameter 
							//       of XnsSdkWindow::Start().
		);

	WLOGD(_T("OpenMedia():: mediaSource=%d, ret=%d(%s)\n"), 
		m_hMediaSource, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
	if(nRet == ERR_SUCCESS)
	{
		*m_pHMediaSource = m_hMediaSource;
	}
}

void CMediaStreamDlg::OnBnClickedButtonOpenMediaEx()
{
	GET_XNS_PARAM();

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// It will start getting media streams from the device, used by Javascript. 
	// -----------------------------------------------------------------------
	m_hMediaSource = m_pCtrlXnsDevice->OpenMediaEx(
		m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
		m_nControlId,		// [in] Control ID of video control module.
		XMEDIA_LIVE,		// [in] Media type
		0,					// [in] Play start time. Format: 4-byte time_t.
		0);					// [in] Play end time. Format: 4-byte time_t.
	if(m_hMediaSource == 0)
	{
		WLOGD(_T("OpenMediaEx():: Faild Open MediaEx!\n"));
		return;
	}
	WLOGD(_T("OpenMediaEx():: mediaSource=%d\n"), m_hMediaSource);
	*m_pHMediaSource = m_hMediaSource;
}	

void CMediaStreamDlg::OnBnClickedButtonCloseMedia()
{
	GET_XNS_PARAM();

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Terminates transferring media stream data from the device. The media 
	// stream data will be separated by hMediaSource 
	// (i.e., phMediaSource of OpenMedia()).
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->CloseMedia(m_hDevice, m_hMediaSource);
	WLOGD(_T("CloseMedia():: ret=%d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
	m_hMediaSource = 0;
	*m_pHMediaSource = m_hMediaSource;
}

void CMediaStreamDlg::OnBnClickedButtonOpenStream()
{
	GET_XNS_PARAM();

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Starts receiving the media stream data from the device. 
	// The incoming media stream will then forwarded to the OnNewMedia event. 
	// The application can decode or forward this data to XnsSdkWindow before 
	// playing.
	// [Return Value]
	// Media stream ID. This is needed for controlling the media stream and 
	// also used as a parameter of XnsSdkWindow::Start().
	// -----------------------------------------------------------------------
	m_hMediaSource = m_pCtrlXnsDevice->OpenStream(
		m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
		m_nControlId,		// [in] Control ID of video control module.
		XMEDIA_LIVE,		// [in] Media type
		0,					// [in] Play start time. Format: 4-byte time_t.
		0);					// [in] Play end time. Format: 4-byte time_t.
	if(m_hMediaSource == 0)
	{
		WLOGD(_T("OpenStream():: Faild Open Stream!\n"));
		return;
	}
	WLOGD(_T("OpenStream():: mediaSource=%d\n"), m_hMediaSource);
	*m_pHMediaSource = m_hMediaSource;
}


void CMediaStreamDlg::OnBnClickedButtonCloseStream()
{
	GET_XNS_PARAM();
	
	long nRet;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Terminates transferring the media stream. The media stream data will be 
	// identified by the control ID.
	// -----------------------------------------------------------------------
	nRet = m_pCtrlXnsDevice->CloseStream(
		m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
		m_nControlId,		// [in] Control ID of video control module.
		XMEDIA_LIVE);		// [in] Media type.

	WLOGD(_T("CloseStream():: ret=%d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
	m_hMediaSource = 0;
	*m_pHMediaSource = m_hMediaSource;
}

void CMediaStreamDlg::OnBnClickedButtonSuspendStream()
{
	GET_XNS_PARAM();

	long nRet;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Suspends transferring the media stream data. 
	// The media stream data will be identified by the control ID.
	// -----------------------------------------------------------------------
	nRet = m_pCtrlXnsDevice->SuspendStream(
		m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
		m_nControlId,		// [in] Control ID of video control module.
		XMEDIA_LIVE);		// [in] Media type.

	WLOGD(_T("SuspendStream():: ret=%d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CMediaStreamDlg::OnBnClickedButtonSuspendAllStream()
{
	GET_XNS_PARAM();

	long nRet;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Suspends transferring all media stream data.
	// -----------------------------------------------------------------------
	nRet = m_pCtrlXnsDevice->SuspendAllStream(
		m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
		XMEDIA_LIVE);		// [in] Media type.

	WLOGD(_T("SuspendAllStream():: ret=%d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}


void CMediaStreamDlg::OnBnClickedButtonResumeStream()
{
	GET_XNS_PARAM();

	long nRet;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Resumes transferring the media stream. 
	// The media stream data will be identified by the control ID.
	// -----------------------------------------------------------------------
	nRet = m_pCtrlXnsDevice->ResumeStream(
		m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
		m_nControlId,		// [in] Control ID of video control module.
		XMEDIA_LIVE);		// [in] Media type.

	WLOGD(_T("ResumeStream():: ret=%d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CMediaStreamDlg::OnBnClickedButtonResumeAllStream()
{
	GET_XNS_PARAM();

	long nRet;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Resumes transferring all media stream.
	// -----------------------------------------------------------------------
	nRet = m_pCtrlXnsDevice->ResumeAllStream(
		m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
		XMEDIA_LIVE);		// [in] Media type.

	WLOGD(_T("ResumeAllStream():: ret=%d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CMediaStreamDlg::OnBnClickedButtonReopenAllStream()
{
	GET_XNS_PARAM();

	long nRet;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Reopens transferring all media stream. 
	// This function is used to refresh the video stream if the camera fails 
	// to display video properly on the screen for any reason. 
	// This function can be replaced by OpenMedia() or OpenMedia().
	// -----------------------------------------------------------------------
	nRet = m_pCtrlXnsDevice->ReopenAllStream(
		m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
		XMEDIA_LIVE);		// [in] Media type.

	WLOGD(_T("ReopenAllStream()::ret=%d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CMediaStreamDlg::OnBnClickedButtonIsPlaying()
{
	GET_XNS_PARAM();

	long nRet;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Informs if the media stream is currently playing.
	// -----------------------------------------------------------------------
	nRet = m_pCtrlXnsDevice->IsPlaying(m_hDevice);
	if(nRet == 1)
	{
		WLOGD(_T("IsPlaying():: The multimedia file is playing now.\n"));
		return;
	}
	else if(nRet == 0)
	{
		WLOGD(_T("IsPlaying():: The multimedia file is not playing now.\n"));
	}
}

void CMediaStreamDlg::OnBnClickedButtonHasAuthority()
{
	GET_XNS_PARAM();

	long nRet;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Confirms if the application has the permission to play the multimedia file.
	// -----------------------------------------------------------------------
	nRet = m_pCtrlXnsDevice->HasAuthority(m_hDevice);
	if(nRet == 1)
	{
		WLOGD(_T("HasAuthority():: Play permission obtained.\n"));
	}
	else if(nRet == 0)
	{
		WLOGD(_T("HasAuthority():: Play permission not obtained.\n"));
	}
}

