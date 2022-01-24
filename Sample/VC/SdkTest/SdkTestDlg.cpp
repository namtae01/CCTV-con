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
// SdkTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "SdkTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSdkTestDlg dialog




CSdkTestDlg::CSdkTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSdkTestDlg::IDD, pParent)
	, m_hDevice(0)
	, m_nControlId(0)
	, m_hMediaSource(0)
	, m_hMediaSourcePlayback(0)
	, m_bAreaZoom(0)
	, m_bLmouseDown(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pCtrlEditLog = &m_ctrlEditLog;
	m_pCtrlEditEvent = &m_ctrlEditEvent;
}

void CSdkTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL_LIVE, m_ctrlXnsWindowLive);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL_PLAYBACK, m_ctrlXnsWindowPlayback);
	DDX_Control(pDX, IDC_XNSSDKDEVICECTRL, m_ctrlXnsDevice);
	DDX_Control(pDX, IDC_EDIT_LOG_WIN, m_ctrlEditLog);
	DDX_Control(pDX, IDC_EDIT_LOG_EVENT, m_ctrlEditEvent);
}

BEGIN_MESSAGE_MAP(CSdkTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CSdkTestDlg message handlers

BOOL CSdkTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	OpenChildDialog();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSdkTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSdkTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSdkTestDlg::OnDestroy()
{
	if( m_hDevice )
	{
// 		if(m_hMediaSource)
// 		{
// 			m_ctrlXnsWindowLive.Stop();
// 		}

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Returns the connection status of the device.
		// -----------------------------------------------------------------------
		if( m_ctrlXnsDevice.GetDeviceStatus(m_hDevice) == XDEVICE_STATUS_CONNECTED )
		{
			m_ctrlXnsDevice.Disconnect(m_hDevice);
		}

		// Cancels the memory space assigned for the device information by 
		// CreateDevice(). The device should be disconnected from the application
		// before this function is called.
		m_ctrlXnsDevice.ReleaseDevice(m_hDevice);
		m_hDevice = 0;
	}

	CloseChildDialog();
	CDialog::OnDestroy();
}

void CSdkTestDlg::OpenChildDialog()
{
	m_pDlgDeviceInfo = new CDeviceInfoDlg(this);
	m_pDlgDeviceInfo->Create(IDD_DIALOG_CONFIG, this);
	m_pDlgDeviceInfo->ShowWindow(SW_SHOWNORMAL);

	m_pDlgMediaStream = new CMediaStreamDlg(this);
	m_pDlgMediaStream->Create(IDD_DIALOG_MEDIA_STREAM, this);
	m_pDlgMediaStream->ShowWindow(SW_SHOWNORMAL);

	m_pDlgPlayBack = new CPlayBackDlg(this);
	m_pDlgPlayBack->Create(IDD_DIALOG_PLAYBACK, this);
	m_pDlgPlayBack->ShowWindow(SW_SHOWNORMAL);

	m_pAudioDlg = new CAudioDlg(this);
	m_pAudioDlg->Create(IDD_DIALOG_AUDIO_ALARM, this);
	m_pAudioDlg->ShowWindow(SW_SHOWNORMAL);

	m_pPtz = new CPtzDlg(this);
	m_pPtz->Create(IDD_DIALOG_PTZ, this);
	m_pPtz->ShowWindow(SW_SHOWNORMAL);

	m_pBackup = new CBackupDlg(this);
	m_pBackup->Create(IDD_DIALOG_BACKUP, this);
	m_pBackup->ShowWindow(SW_SHOWNORMAL);

	m_pDeviceMisc = new CDeviceMiscDlg(this);
	m_pDeviceMisc->Create(IDD_DIALOG_DEVICE_MISC, this);
	m_pDeviceMisc->ShowWindow(SW_SHOWNORMAL);

	m_pWindowInit = new CWinStartDlg(this);
	m_pWindowInit->Create(IDD_DIALOG_WIN_START, this);
	m_pWindowInit->ShowWindow(SW_SHOWNORMAL);

	m_pControlZoom = new CControlZoomDlg(this);
	m_pControlZoom->Create(IDD_DIALOG_CONTROL_ZOOM, this);
	m_pControlZoom->ShowWindow(SW_SHOWNORMAL);

	m_pControlVol = new CControlVolDlg(this);
	m_pControlVol->Create(IDD_DIALOG_CONTROL_VOL, this);
	m_pControlVol->ShowWindow(SW_SHOWNORMAL);

	m_pDisplayInfo = new CDisplayInfo(this);
	m_pDisplayInfo->Create(IDD_DIALOG_WINDOW_DISPLAYINFO, this);
	m_pDisplayInfo->ShowWindow(SW_SHOWNORMAL);

	m_pWinMisc = new CWinMiscDlg(this);
	m_pWinMisc->Create(IDD_DIALOG_WIN_MISC, this);
	m_pWinMisc->ShowWindow(SW_SHOWNORMAL);

	m_pChangePw = new CChangePwDlg(this);
	m_pChangePw->Create(IDD_DIALOG_CHANGE_PW, this);
	m_pChangePw->ShowWindow(SW_SHOWNORMAL);
}

void CSdkTestDlg::CloseChildDialog()
{
	if(m_pDlgDeviceInfo)
	{
		m_pDlgDeviceInfo->DestroyWindow();
		delete m_pDlgDeviceInfo;
		m_pDlgDeviceInfo = NULL;
	}
	if(m_pDlgMediaStream)
	{
		m_pDlgMediaStream->DestroyWindow();
		delete m_pDlgMediaStream;
		m_pDlgMediaStream = NULL;
	}
	if(m_pDlgPlayBack)
	{
		m_pDlgPlayBack->DestroyWindow();
		delete m_pDlgPlayBack;
		m_pDlgPlayBack = NULL;
	}
	if(m_pAudioDlg)
	{
		m_pAudioDlg->DestroyWindow();
		delete m_pAudioDlg;
		m_pAudioDlg = NULL;
	}
	if(m_pPtz)
	{
		m_pPtz->DestroyWindow();
		delete m_pPtz;
		m_pPtz = NULL;
	}
	if(m_pBackup)
	{
		m_pBackup->DestroyWindow();
		delete m_pBackup;
		m_pBackup = NULL;
	}
	if(m_pDeviceMisc)
	{
		m_pDeviceMisc->DestroyWindow();
		delete m_pDeviceMisc;
		m_pDeviceMisc = NULL;
	}
	if(m_pWindowInit)
	{
		m_pWindowInit->DestroyWindow();
		delete m_pWindowInit;
		m_pWindowInit = NULL;
	}

	if(m_pControlZoom)
	{
		m_pControlZoom->DestroyWindow();
		delete m_pControlZoom;
		m_pControlZoom = NULL;
	}
	if(m_pControlVol)
	{
		m_pControlVol->DestroyWindow();
		delete m_pControlVol;
		m_pControlVol = NULL;
	}
	if(m_pDisplayInfo)
	{
		m_pDisplayInfo->DestroyWindow();
		delete m_pDisplayInfo;
		m_pDisplayInfo = NULL;
	}
	if(m_pWinMisc)
	{
		m_pWinMisc->DestroyWindow();
		delete m_pWinMisc;
		m_pWinMisc = NULL;
	}
}
BEGIN_EVENTSINK_MAP(CSdkTestDlg, CDialog)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 23, CSdkTestDlg::OnAlarmOutControlFailedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 19, CSdkTestDlg::OnBackupProgressXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 27, CSdkTestDlg::OnCallbackEventXnssdkdevicectrl, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 3, CSdkTestDlg::OnConnectFailedXnssdkdevicectrl, VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 12, CSdkTestDlg::OnControlCapabilityChangedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 1, CSdkTestDlg::OnControlLocalNameChangedXnssdkdevicectrl, VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 24, CSdkTestDlg::OnControlRemoteNameChangedXnssdkdevicectrl, VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 11, CSdkTestDlg::OnControlStatusChangedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 10, CSdkTestDlg::OnDeviceStatusChangedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 9, CSdkTestDlg::OnExportConfigProgressXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 21, CSdkTestDlg::OnFanBrokenXnssdkdevicectrl, VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 25, CSdkTestDlg::OnGetMotionGridXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 6, CSdkTestDlg::OnGetPresetListXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 31, CSdkTestDlg::OnGetPtzPosXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 16, CSdkTestDlg::OnHDDFailedXnssdkdevicectrl, VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 17, CSdkTestDlg::OnHDDFulledXnssdkdevicectrl, VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 8, CSdkTestDlg::OnImportConfigProgressXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 30, CSdkTestDlg::OnIvOccurEventXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 13, CSdkTestDlg::OnMotionEventXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 26, CSdkTestDlg::OnMotionSearchXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 20, CSdkTestDlg::OnNewMediaXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 18, CSdkTestDlg::OnPasswordChangedXnssdkdevicectrl, VTS_I4 VTS_BSTR)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 22, CSdkTestDlg::OnPtzControlFailedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 28, CSdkTestDlg::OnRecvSerialDataXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 4, CSdkTestDlg::OnSearchCalendarXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 5, CSdkTestDlg::OnSearchDayXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 14, CSdkTestDlg::OnSensorEventXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 29, CSdkTestDlg::OnTalkFailedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 7, CSdkTestDlg::OnUploadSoftwareProgressXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 15, CSdkTestDlg::OnVideoLossEventXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 11, CSdkTestDlg::OnMouseMoveXnssdkwindowctrlLive, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 15, CSdkTestDlg::OnBufferEmptyXnssdkwindowctrlLive, VTS_NONE)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 14, CSdkTestDlg::OnBufferFullXnssdkwindowctrlLive, VTS_NONE)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 18, CSdkTestDlg::OnEventStatusChangedXnssdkwindowctrlLive, VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 1, CSdkTestDlg::OnFrameTimeChangedXnssdkwindowctrlLive, VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 2, CSdkTestDlg::OnImageResolutionChangedXnssdkwindowctrlLive, VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 19, CSdkTestDlg::OnKeyDownXnssdkwindowctrlLive, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 20, CSdkTestDlg::OnKeyUpXnssdkwindowctrlLive, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 9, CSdkTestDlg::OnLButtonDblClkXnssdkwindowctrlLive, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 5, CSdkTestDlg::OnLButtonDownXnssdkwindowctrlLive, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 6, CSdkTestDlg::OnLButtonUpXnssdkwindowctrlLive, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 4, CSdkTestDlg::OnMediaOffXnssdkwindowctrlLive, VTS_NONE)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 3, CSdkTestDlg::OnMediaOnXnssdkwindowctrlLive, VTS_NONE)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 12, CSdkTestDlg::OnMouseHoverXnssdkwindowctrlLive, VTS_NONE)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 13, CSdkTestDlg::OnMouseLeaveXnssdkwindowctrlLive, VTS_NONE)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 17, CSdkTestDlg::OnPreBufferEmptyXnssdkwindowctrlLive, VTS_NONE)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 16, CSdkTestDlg::OnPreBufferFullXnssdkwindowctrlLive, VTS_NONE)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 10, CSdkTestDlg::OnRButtonDblClkXnssdkwindowctrlLive, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 7, CSdkTestDlg::OnRButtonDownXnssdkwindowctrlLive, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 8, CSdkTestDlg::OnRButtonUpXnssdkwindowctrlLive, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKWINDOWCTRL_LIVE, 21, CSdkTestDlg::OnWindowSizeChangedXnssdkwindowctrlLive, VTS_I4 VTS_I4)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 57, CSdkTestDlg::OnDeviceDetected3Xnssdkdevicectrl, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 VTS_BSTR)
	ON_EVENT(CSdkTestDlg, IDC_XNSSDKDEVICECTRL, 64, CSdkTestDlg::OnChangeDeviceAdminPasswordXnssdkdevicectrl, VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


// DEVICE EVENT ///////////////////////////////////////////////////////////

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the application has failed to control the alarm-out. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnAlarmOutControlFailedXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode)
{
	ELOGD(_T("OnAlarmOutControlFailed():: deviceID=%d, controlID=%d, errorCode=%d\n"),
		nDeviceID, nControlID, nErrorCode);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs at a regular interval each time the progress of 
// multimedia data backup increases by 5%. It contains the progress (%) 
// and error code.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnBackupProgressXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode, long nProgress, long tStart, long tEnd)
{
	ELOGD(_T("OnBackupProgress():: deivcdID=%d, conrolID=%d, errorCode=%d, progress=%d, start=%d, end=%d\n"),
		nDeviceID, nControlID, nErrorCode, nProgress, tStart, tEnd);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void CSdkTestDlg::OnCallbackEventXnssdkdevicectrl(
	LPCTSTR szVendorName, 
	LPCTSTR szModelName, 
	LPCTSTR szAddress, 
	long nPort, 
	LPCTSTR szUserID, 
	LPCTSTR szPassword, 
	long nEventType, 
	long nEventIndex, 
	long tEventTime
	)
{
	ELOGD(_T("OnCallbackEvent():: vendor=%s, model=%s, address=%s, port=%d, userid=%s, password=%s\n"),
		szVendorName, szModelName, szAddress, nPort, szUserID, szPassword);
	ELOGD(_T("OnCallbackEvent():: eventType=%d, eventIndex=%d, eventTime=%d\n"),
		nEventType, nEventIndex, tEventTime);
		
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// If the application has failed in non-blocking connection using 
// ConnectNonBlock(), the OnConnectFailed event occurs. As Connect() 
// returns an immediate error message if failed, it does not trigger 
// this event. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode)
{
	ELOGD(_T("OnConnectFailed():: deviceID=%d, errcode=%d(%s)\n"),
		nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the device status has changed. It occurs if the 
// application uses Connect() to connect or reconnect to the device after 
// disconnected. When reconnecting, the third argument nDeviceStatus is 
// true, all media must be reopened using ReopenAllStream().
// -----------------------------------------------------------------------
void CSdkTestDlg::OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
	ELOGD(_T("OnDeviceStatusChanged():: deviceID=%d, errcode=%d, deviceStatus=%d, hddCondition=%d\n"),
		nDeviceID, nErrorCode, nDeviceStatus, nHddCondition);

	if (nErrorCode == ERR_SUCCESS && nDeviceStatus == 1)
	{
		ELOGD(_T("OnDeviceStatusChanged():: Connected: deviceID=%d, errcode=%d, deviceStatus=%d\n"),
			nDeviceID, nErrorCode, nDeviceStatus);
		if(m_hMediaSource)
		{
			ELOGD(_T("OnDeviceStatusChanged():: media source reopen...\n"));
			m_ctrlXnsDevice.CloseMedia(m_hDevice, m_hMediaSource);
			m_hMediaSource = 0;
			long nRet = m_ctrlXnsDevice.OpenMedia(
				m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
				m_nControlId,		// [in] Control ID of video control module. 
				MEDIA_TYPE_LIVE,	// [in] Media type.
				0,					// [in] Play start time. Format: 4-byte time_t.
				0,					// [in] Play end time. Format: 4-byte time_t.
				&m_hMediaSource		// [out] Media stream ID. This is needed for controlling 
									//       the media stream and also used as a parameter 
									//       of XnsSdkWindow::Start().
				);
			WLOGD(_T("OpenMedia():: mediaSource=%d, control id=%d, ret=%d(%s)\n"), 
				m_hMediaSource, m_nControlId, nRet, m_ctrlXnsDevice.GetErrorString(nRet));
			//m_ctrlXnsWindowLive.Start(m_hMediaSource);

		}
	}

	
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the control module has changed its capability. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnControlCapabilityChangedXnssdkdevicectrl(long nDeviceID, long nControlID, long nCapabilityMask)
{
	ELOGD(_T("OnControlCapabilityChanged():: deviceID=%d, controlID=%d, cmask=%d\n"),
		nDeviceID, nControlID, nCapabilityMask);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// If the control module is renamed in the local PC, the ActiveX object 
// will trigger the OnControlLocalNameChanged event. The event will also 
// occur if the application tries to rename the control module using 
// ChangeControlLocalName(). 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnControlLocalNameChangedXnssdkdevicectrl(long nDeviceID, long nControlID)
{
	ELOGD(_T("OnControlLocalNameChanged():: deviceID=%d, conrolID=%d\n"), nDeviceID, nControlID);
}
// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void CSdkTestDlg::OnControlRemoteNameChangedXnssdkdevicectrl(long nDeviceID, long nControlID)
{
	ELOGD(_T("OnControlRemoteNameChanged():: deviceID=%d, conrolID=%d\n"), nDeviceID, nControlID);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the device status or the capability of the 
// control module has changed. When receiving this event, the application
// can use GetControlStatus() to check the changes.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnControlStatusChangedXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode, long nStatusMask)
{
	ELOGD(_T("OnControlStatusChanged():: deviceID=%d, conrolID=%d, errorCode=%d, statusMask=%d\n"),  
		nDeviceID, nControlID, nErrorCode, nStatusMask);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This events informs that IV event occurs at device.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnIvOccurEventXnssdkdevicectrl(long nDeviceID, long nControlID, long tEventUTC, long nIvType)
{
	CString strIvType;
	if(nIvType & XIV_TYPE_PASSING)
		strIvType = _T("PASSING");
	else if(nIvType & XIV_TYPE_ENTERING)
		strIvType = _T("ENTERING");
	else if(nIvType & XIV_TYPE_EXITING)
		strIvType = _T("EXITIN");
	else if(nIvType & XIV_TYPE_APPEARING)
		strIvType = _T("APPEARING");
	else
		strIvType = _T("UNKNOWN");

	ELOGD(_T("OnIvOccurEvent():: deviceID=%d, controlID=%d, eventUTC=%d, nIvType=%d(%s)\n"), 
		nDeviceID, nControlID, tEventUTC, nIvType, strIvType);
}

void CSdkTestDlg::OnMotionEventXnssdkdevicectrl(long nDeviceID, long nControlID, long tEventUTC)
{
	ELOGD(_T("OnMotionEvent():: deviceID=%d, controlID=%d, eventUTC=%d\n"), 
		nDeviceID, nControlID, tEventUTC);
}
// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void CSdkTestDlg::OnMotionSearchXnssdkdevicectrl(long nDeviceID, long nControlID, long hTimeline)
{
	// TODO: Add your message handler code here
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs when the application receives the frame data. 
// If the application uses OpenStream() to request for stream data, 
// the frame data will be transferred through this event. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnNewMediaXnssdkdevicectrl(
	long nDeviceID,
	long nControlID, 
	long nMediaType, 
	long hMediaData, 
	long nInputType, 
	long nFrameType, 
	long nFrameTime, 
	long nFrameSize, 
	long nTimestamp
	)
{
	ELOGD(_T("OnNewMedia():: deviceID=%d, controlID=%d, mediaType=%d, inputType=%d\n"),
			nDeviceID, nControlID, nMediaType, nInputType);
	ELOGD(_T("OnNewMedia():: frameType=%d, frameTime=%d, frameSize=%d, timeStatmp=%d\n"),
		nFrameType, nFrameTime, nFrameSize, nTimestamp);

	long frame_time = m_ctrlXnsWindowLive.GetFrameTime(hMediaData);
	long frame_size = m_ctrlXnsWindowLive.GetFrameSize(hMediaData);
	long frame_type = m_ctrlXnsWindowLive.GetFrameType(hMediaData);
	long time_stamp = m_ctrlXnsWindowLive.GetTimeStamp(hMediaData);
	long input_type = m_ctrlXnsWindowLive.GetInputType(hMediaData);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// @ ActiveX SDK Window Control Member Function.
	// Transfers stream data to XnsSdkWindow so that the media stream 
	// will be displayed on the window after decoded.
	// If XnsSdkDevice::OpenStream is called, the stream data will be transferred 
	// to the application from the OnNewMedia event.
	// Then, the application should use PushMedia to forward the stream data to XnsSdkWindow 
	// for decoding so that the video is properly displayed on the screen. 
	// This function is valid only within the event handler of the OnNewMedia event.
	// -----------------------------------------------------------------------
	long nRet = m_ctrlXnsWindowLive.PushMedia(hMediaData);

	m_cCS2.Lock(); 
	WLOGW(_T("GetFrameTime() :: %d\n"), frame_time);
	WLOGW(_T("GetFrameSize() :: %d\n"), frame_size);
	WLOGW(_T("GetFrameType() :: %d\n"), frame_type);
	WLOGW(_T("GetTimeStamp() :: %d\n"), time_stamp);
	WLOGW(_T("GetInputType() :: %d\n"), input_type);
	WLOGW(_T("PushMedia() :: [%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	m_cCS2.Unlock();
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the password for DVR has changed.  
// -----------------------------------------------------------------------
void CSdkTestDlg::OnPasswordChangedXnssdkdevicectrl(long nDeviceID, LPCTSTR szID)
{
	ELOGD(_T("OnPasswordChanged():: deviceID=%d, ID=%s\n"), 
		nDeviceID, szID);
}
// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the PTZ control has failed. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnPtzControlFailedXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode)
{
	ELOGD(_T("OnPtzControlFailed():: deviceID=%d, controlID=%d, errorCode=%d\n"),
		nDeviceID, nControlID, nErrorCode);
}
// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void CSdkTestDlg::OnRecvSerialDataXnssdkdevicectrl(long nDeviceID, long nCmdID, long nRecvDataLength, long pRecvData)
{
	// TODO: Add your message handler code here
}
// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the application calls SearchCalendar(), 
// which contains the search result. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnSearchCalendarXnssdkdevicectrl(long nDeviceID, long nControlID, long nRecDay)
{
	ELOGD(_T("OnSearchCalendar():: deviceID=%d, controlID=%d, recDay=%d\n"), 
		nDeviceID, nControlID, nRecDay);

	ELOGD(_T("01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31\n"));
	long nBitFlag = 0x01;
	CString strRec = _T("");

	for (int i=0; i<31; i++)
	{
		if (nRecDay & nBitFlag)
		{
			strRec.Append(_T("  1 "));
		}
		else
		{
			strRec.Append(_T("  0 "));
		}
		nBitFlag <<=1;
	}

	ELOGD(_T("%s\n"), strRec);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the application calls SearchDay(). 
// The timeline handle will be forwarded to a parameter of the event 
// handler. Some functions such as GetTimeline() use this handle as a 
// parameter. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnSearchDayXnssdkdevicectrl(long nDeviceID, long nControlID, long hTimeline)
{
	ELOGD(_T("OnSearchDay():: deviceID=%d, controlID=%d, timeLine=%d\n"), 
		nDeviceID, nControlID, hTimeline);
	

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// GetTimeline()      : Returns information on the recording data block.
	// GetTimelineCount() : Number of blocks of the recording data in the timeline. 
	//                      This value is used as a parameter of functions: 
	//                      GetStartTime(), GetEndTime(), GetRecordingType().
	// GetCameraCount()   : Returns the number of cameras existing in the timeline.
	// -----------------------------------------------------------------------
	long nCamCount = m_ctrlXnsDevice.GetCameraCount(hTimeline);
	m_cCS2.Lock(); 
	WLOGD(_T("GetCameraCount() :: [%d]\n"), nCamCount);
	m_cCS2.Unlock(); 

	long tStart, tEnd;
	long nRecType;
	long nRecId;
	long Year, Month, Day, StartHour, StartMin, StartSec, EndHour, EndMin, EndSec;
	long nTimelineCount;
	CString strBuffer=_T("");

	int i, j;
	long nTotalCount = 0;
	for (i=0; i<nCamCount; i++)
	{
		nTimelineCount = m_ctrlXnsDevice.GetTimelineCount(hTimeline, i);
		m_cCS2.Lock(); 
		WLOGD(_T("GetTimelineCount() :: idx=%d, [%d]\n"), i, nTimelineCount);
		m_cCS2.Unlock(); 
		nTotalCount += nTimelineCount;
	}

	nTotalCount = 0;
	for (i=0; i<nCamCount; i++)
	{
		nTimelineCount = m_ctrlXnsDevice.GetTimelineCount(hTimeline, i);
		for(j=0; j<nTimelineCount; j++)
		{
			m_ctrlXnsDevice.GetTimeline(hTimeline, i, j, XTIME_LOCAL, &tStart, &tEnd, &nRecType, &nRecId);

			DBG_LOG(_T("[%d][%d] Timeline[%d], tStart[%d], tEnd[%d]\n"), i, j, nTotalCount, tStart, tEnd);
			m_ctrlXnsDevice.TimetToDate(tStart, &Year, &Month, &Day, &StartHour, &StartMin, &StartSec);
			m_ctrlXnsDevice.TimetToDate(tEnd, &Year, &Month, &Day, &EndHour, &EndMin, &EndSec);
			CString strType;
			switch(nRecType)
			{
			case REC_TYPE_MOTION:
				strType = _T("MOT");
				break;
			case REC_TYPE_ALARM:
				strType = _T("ALM");
				break;
			case REC_TYPE_VLOSS:
				strType = _T("VLS");
				break;
			case REC_TYPE_MANUAL:
				strType = _T("MAN");
				break;
			case REC_TYPE_CONTINUOS:
				strType = _T("CON");
				break;
			default:
				strType = _T("OTH");
				break;
			}

			strBuffer.Format(_T("%02d|%s|%02d:%02d:%02d~%02d:%02d:%02d"),
				nTotalCount, strType, StartHour, StartMin, StartSec, EndHour, EndMin, EndSec);

			m_cCS2.Lock(); 
			WLOGD(_T("GetTimeline() :: %s\n"), strBuffer);
			m_cCS2.Unlock(); 
			nTotalCount++;
		}
	}
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This events informs that a sensor-in (i.e., alarm-in) event occurs 
// from the device.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnSensorEventXnssdkdevicectrl(long nDeviceID, long nControlID, long nSensorNumber, long tEventUTC)
{
	ELOGD(_T("OnSensorEvent():: deviceID=%d, controlID=%d, sensorName=%d, eventUTC=%d\n"),
		nDeviceID, nControlID, nSensorNumber, tEventUTC);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void CSdkTestDlg::OnTalkFailedXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode)
{
	ELOGD(_T("OnTalkFailed():: deviceID=%d, controlID=%d, errorCode=%d\n"),
		nDeviceID, nControlID, nErrorCode);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs at a regular interval each time the progress of
// uploading software to the device using UploadSoftware() increases 
// by 5%. It contains the progress (%) and error code. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnUploadSoftwareProgressXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nProgress)
{
	ELOGD(_T("OnUploadSoftwareProgress():: deviceID=%d, errorCode=%d(%s), progress=%d\n"),
		nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode), nProgress);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event informs that a video loss event occurs from the device.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnVideoLossEventXnssdkdevicectrl(long nDeviceID, long nControlID, long tEventUTC)
{
	ELOGD(_T("OnVideoLossEvent():: deviceID=%d, controlID=%d, eventUTC=%d\n"),
		nDeviceID, nControlID, tEventUTC);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs at a regular interval each time the progress of 
// exporting configuration file to the device using ExportConfig() 
// increases by 5%. It contains the progress (%) and error code.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnExportConfigProgressXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nProgress)
{
	ELOGD(_T("OnExportConfigProgress():: deviceID=%d, errorCode=%d(%s), progress=%d\n"),
		nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode), nProgress);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the fan of DVR malfunctions. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnFanBrokenXnssdkdevicectrl(long nDeviceID)
{
	ELOGD(_T("OnFanBroken():: deviceID=%d\n"), nDeviceID);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void CSdkTestDlg::OnGetMotionGridXnssdkdevicectrl(long nDeviceID, long nControlID, long nGridWidth, long nGridHeight, long pGridArray)
{
	ELOGD(_T("OnGetMotionGrid():: deviceID=%d, controlID=%d, gridWidth=%d, gridHeight=%d\n"),
		nDeviceID, nControlID, nGridHeight, nGridHeight);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if GetPresetList() is called, the handle of the 
// preset list will be forwarded to the parameter of event handler. 
// This handle is input as a parameter of GetPresetCount(), and is used
// to get information about the preset.
// 
// Parameters
// - nDeviceID
//   [in] Device ID.
// - nControlID
//   [in] Control ID.
// - hPresetListList
//   [in] Handle to indicate the preset list.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnGetPresetListXnssdkdevicectrl(long nDeviceID, long nControlID, long hPresetListList)
{
	long nNumber;
	long nPresetCount;
	CString strPresetName;
	CMap< int, int, CString, CString > cmPresetList;

	ELOGD(_T("OnGetPresetList():: nDevice[%d], nControlId[%d], hPresetList[%d]\n"),
		nDeviceID, nControlID, hPresetListList);

	// Gets the number of presets defined. 
	// This value is used to get the preset name and information. 
	// This function is valid as long as the application is receiving 
	// media stream from the camera.
	nPresetCount = m_ctrlXnsDevice.GetPresetCount(hPresetListList);
	WLOGD(_T("GetPresetCount():: PresetCount=%d\n"), nPresetCount);

	for( int i=0 ; i<nPresetCount ; i++ )
	{
		// Returns the preset number and name corresponding to the 
		// given index in the preset list of XnsSdkDevice. 
		strPresetName = m_ctrlXnsDevice.GetPreset(
			hPresetListList,	// [in] Handle of the preset list. 
			i,					// [in] Preset index to get the preset information (start with 1).
			&nNumber			// [out] Preset index specified in XnsSdkDevice.
			);
		WLOGD(_T("GetPreset():: PresetList[%02d] name=[%s]\n"), nNumber, strPresetName);
		cmPresetList.SetAt(nNumber, strPresetName);
	}

	PresetDlg dlg(this);
	INT_PTR nResult = dlg.DoModal();
	
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs when GetPtzPos() is called. One of the parameter 
// of event handler is the handle of preset list, which used to get the 
// absolute coordinate of camera.
//
// Parameters
// - nDeviceID
//   [in] Device ID.
// - nControlID
//   [in] Control ID.
// - nErrorCode
//   [in] return value. 
// - nPan
//   [in] Absolute value of Pan. 
// - nTilt
//   [in] Absolute value of Tilt. 
// - nZoom
//   [in] Absolute value of Zoom. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnGetPtzPosXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode, long nPan, long nTilt, long nZoom)
{
	ELOGD(_T("OnGetPtzPos():: device_id=%d, control_id=%d, pan=%d, tilt=%d, zoom=%d, ret=%d\n"),
		nDeviceID, nControlID, nPan, nTilt, nZoom, nErrorCode);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void CSdkTestDlg::OnHDDFailedXnssdkdevicectrl(long nDeviceID, long nHDDNumber)
{
	ELOGD(_T("OnHDDFailed():: device_id=%d, hddNumber=%d\n"), nDeviceID, nHDDNumber);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void CSdkTestDlg::OnHDDFulledXnssdkdevicectrl(long nDeviceID, long nHDDNumber)
{
	ELOGD(_T("OnHDDFulled()::\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the application uses ImportConfig() to get the 
// configuration file from the device. It occurs at a regular interval 
// each time the progress increases by 5%, and it contains the error code. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnImportConfigProgressXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nProgress)
{
	ELOGD(_T("OnImportConfigProgress():: deviceID=%d, errorCode=%d(%s), progress=%d\n"),
		nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode), nProgress);
}

// WINDOW EVENT ////////////////////////////////////////////////////

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the mouse pointer is moving. This event is valid 
// only if both XnsSdkWindow handle and parent window handle are reset 
// to Null.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnMouseMoveXnssdkwindowctrlLive(long nFlags, long nX, long nY)
{
	//ELOGW(_T("OnMouseMove():: flag=%d, x=%d, y=%d\n"), nFlags, nX, nY);
	if (!m_bAreaZoom) 
		return;

	if (!m_bLmouseDown)
		return;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Uses the blue brush to draw a rectangle on XnsSdkWindow. 
	// If this function is called more than twice, the existing rectangle 
	// will be replaced with a new one.
	// -----------------------------------------------------------------------
	m_ctrlXnsWindowLive.DrawRect(
		m_nStartX,			// [in] X-axis coordinate of top left.
		m_nStartY,			// [in] Y-axis coordinate of top left.
		nX-m_nStartX,		// [in] Width of the rectangle.
		nY-m_nStartY		// [in] Height of the rectangle.
		);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the buffer of XnsSdkWindow component is empty. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnBufferEmptyXnssdkwindowctrlLive()
{
	ELOGW(_T("OnBufferEmpty():: event occured..\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the buffer of XnsSdkWindow component is full. 
// The application can use ClearMediaBuffer() o empty the buffer or 
// use SetBufferSize() to resize it. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnBufferFullXnssdkwindowctrlLive()
{
	ELOGW(_T("OnBufferFull():: event occured..\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the event status has changed. 
// Event types include: video loss, alarm, motion detection.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnEventStatusChangedXnssdkwindowctrlLive(long nOldEventStatus, long nNewEventStatus)
{
	ELOGW(_T("OnEventStatusChanged():: old=%d, new=%d\n"), nOldEventStatus, nNewEventStatus);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the frame time displayed on the screen is changed. 
// This happens every second video is played. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnFrameTimeChangedXnssdkwindowctrlLive(long tFrameTime)
{
	//ELOGW(_T("OnFrameTimeChanged():: time=%d\n"), tFrameTime);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the resolution of the original image is changed. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnImageResolutionChangedXnssdkwindowctrlLive(long nWidth, long nHeight)
{
	ELOGW(_T("OnImageResolutionChanged():: width=%d, height=%d\n"), nWidth, nHeight);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the non-system key is pressed.  
// -----------------------------------------------------------------------
void CSdkTestDlg::OnKeyDownXnssdkwindowctrlLive(long nChar, long nRepCnt, long nFlags)
{
	ELOGW(_T("OnKeyDown():: char=%d, repCnt=%d, flags=%d\n"), nChar, nRepCnt, nFlags);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the non-system key is pressed and released. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnKeyUpXnssdkwindowctrlLive(long nChar, long nRepCnt, long nFlags)
{
	ELOGW(_T("OnKeyUp():: char=%d, repCnt=%d, flags=%d\n"), nChar, nRepCnt, nFlags);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the left mouse button is pressed and released 
// twice in XnSdkWindow. This event is valid only if both XnsSdkWindow 
// handle and parent window handle are reset to Null.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnLButtonDblClkXnssdkwindowctrlLive(long nFlags, long nX, long nY)
{
	ELOGW(_T("OnLButtonDblClk():: flags=%d, x=%d, y=%d\n"), nFlags, nX, nY);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if a left button on the mouse is pressed in 
// XnSdkWindow. This event is valid only if both XnsSdkWindow handle and 
// parent window handle are reset to Null.  
// -----------------------------------------------------------------------
void CSdkTestDlg::OnLButtonDownXnssdkwindowctrlLive(long nFlags, long nX, long nY)
{
	ELOGW(_T("OnLButtonDown():: flags=%d, x=%d, y=%d\n"), nFlags, nX, nY);
	m_bLmouseDown = true;
	// TODO: Add your message handler code here
	if (!m_bAreaZoom) 
		return;

	m_nStartX = nX;
	m_nStartY = nY;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Uses the blue brush to draw a rectangle on XnsSdkWindow. 
	// If this function is called more than twice, the existing rectangle 
	// will be replaced with a new one.
	// -----------------------------------------------------------------------
	m_ctrlXnsWindowLive.DrawRect(
		m_nStartX,			// [in] X-axis coordinate of top left.
		m_nStartY,			// [in] Y-axis coordinate of top left.
		0,					// [in] Width of the rectangle.
		0					// [in] Height of the rectangle.
		);
	WLOGW(_T("DrawRect():: start..\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the left mouse button is pressed and released in 
// XnSdkWindow. This event is valid only if both XnsSdkWindow handle and 
// parent window handle are reset to Null.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnLButtonUpXnssdkwindowctrlLive(long nFlags, long nX, long nY)
{
	ELOGW(_T("OnLButtonUp():: flags=%d, x=%d, y=%d\n"), nFlags, nX, nY);

	m_bLmouseDown = false;
	if (!m_bAreaZoom) 
		return;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns the width of the source image. 
	// Returns the height of the source image.
	// -----------------------------------------------------------------------
	long nImageWidth = m_ctrlXnsWindowLive.GetImageWidth();
	long nImageHeight = m_ctrlXnsWindowLive.GetImageHeight();
	WLOGW(_T("GetImageWidth():: imageWidth=%d, imageHeight=%d\n"), 
		nImageWidth, nImageHeight);

	CRect rt; 
	m_ctrlXnsWindowLive.GetClientRect(rt);
	long nWindowWidth = rt.Width();
	long nWindowHeight = rt.Height();
	WLOGW(_T("GetClientRect():: windowWidth=%d, windowHeight=%d\n"), 
		nWindowWidth, nWindowHeight);

	m_nEndX = nX;
	m_nEndY = nY;


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Deletes the existing rectangle on the screen.
	// -----------------------------------------------------------------------
	m_ctrlXnsWindowLive.ClearDraw();
	WLOGW(_T("ClearDraw()::\n"));

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Set up AreaZoom feature, which is available when application 
	// receives media stream from the camera. 
	// Moves the camera to the Area zoom position. 
	// This function is valid as long as the application is receiving 
	// media stream from the camera. 
	// -----------------------------------------------------------------------
	long nRet = m_ctrlXnsDevice.AreaZoom(
		m_hDevice,			// Device handle. This value is returned from CreateDevice().
		m_nControlId,		// Control ID.
		m_nStartX,			// X-axis start position
		m_nStartY,			// Y-axis start position
		m_nEndX,			// X-axis end position
		m_nEndY,			// Y-axis end position
		nWindowWidth,		// Window width
		nWindowHeight,		// Window height
		nImageWidth,		// Image width
		nImageHeight		// Image height
		);

	WLOGD(_T("AreaZoom():: ret = %d(%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This occurs if receiving media stream is stopped or completed.  
// -----------------------------------------------------------------------
void CSdkTestDlg::OnMediaOffXnssdkwindowctrlLive()
{
	ELOGW(_T("OnMediaOff()::\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This occurs if the XnsSdkWindow component receives media stream. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnMediaOnXnssdkwindowctrlLive()
{
	ELOGW(_T("OnMediaOn()::\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the mouse pointer enters XnsSdkWindow. 
// This event is valid only if both XnsSdkWindow handle and parent 
// window handle are reset to Null.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnMouseHoverXnssdkwindowctrlLive()
{
	//ELOGW(_T("OnMouseHover()::\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the mouse pointer moves out of XnsSdkWindow. 
// This event is valid only if both XnsSdkWindow handle and parent 
// window handle are reset to Null.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnMouseLeaveXnssdkwindowctrlLive()
{
	//ELOGW(_T("OnMouseLeave()::\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the remaining data size in the XnsSdkWindow buffer 
// is less than specified. Namely, this occurs if the remaining data size 
// is less than required by the nMinRemainingSize parameter of 
// SetBufferSize().The minimum space defaulted by nMinRemainingSize is 0.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnPreBufferEmptyXnssdkwindowctrlLive()
{
	ELOGW(_T("OnPreBufferEmpty()::\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs at the point when the remaining space of XnsSdkWindow 
// buffer gets less than the minimum required space. The application can 
// uses SetBufferSize() to adjust the minimum required space for the 
// buffer. (adjust the nMinRemainingSize parameter of SetBufferSize()) 
// The minimum space defaulted by nMinRemainingSize is 0. 
// -----------------------------------------------------------------------
void CSdkTestDlg::OnPreBufferFullXnssdkwindowctrlLive()
{
	ELOGW(_T("OnPreBufferFull()::\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the right mouse button is pressed and released
// twice in XnSdkWindow. This event is valid only if both XnsSdkWindow
// handle and parent window handle are reset to Null.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnRButtonDblClkXnssdkwindowctrlLive(long nFlags, long nX, long nY)
{
	ELOGW(_T("OnRButtonDblClk():: flags=%d, x=%d, y=%d\n"), nFlags, nX, nY);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if a right button on the mouse is pressed in 
// XnSdkWindow. This event is valid only if both XnsSdkWindow handle and 
// parent window handle are reset to Null.
// -----------------------------------------------------------------------
void CSdkTestDlg::OnRButtonDownXnssdkwindowctrlLive(long nFlags, long nX, long nY)
{
	ELOGW(_T("OnRButtonDown():: flags=%d, x=%d, y=%d\n"), nFlags, nX, nY);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the right mouse button is pressed and released in 
// XnSdkWindow. This event is valid only if both XnsSdkWindow handle and 
// parent window handle are reset to Null.  
// -----------------------------------------------------------------------
void CSdkTestDlg::OnRButtonUpXnssdkwindowctrlLive(long nFlags, long nX, long nY)
{
	ELOGW(_T("OnRButtonUp():: flags=%d, x=%d, y=%d\n"), nFlags, nX, nY);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void CSdkTestDlg::OnWindowSizeChangedXnssdkwindowctrlLive(long lWidth, long lHeight)
{
//	ELOGW(_T("OnWindowSizeChanged():: width=%d, height=%d\n"), lWidth, lHeight);
}


void CSdkTestDlg::OnDeviceDetected3Xnssdkdevicectrl(LPCTSTR szVendorName, LPCTSTR szModelName, LPCTSTR szDeviceName, LPCTSTR szIP, LPCTSTR szSubnetMask, LPCTSTR szGateway, LPCTSTR szMac, long nPort, long nHttpPort, LPCTSTR szModelType, 
	BOOL bSupportIpInstall, long nNetworkMode, BOOL bDHCPIPInstall, long nDeviceProtocolType, LPCTSTR szUUID)
{
	DBG_LOG(_T("OnDeviceDetected3():: vendor=%s, model=%s, device=%s, ip=%s, mac=%s, port=%d, httpPort=%d, protocolType=%d\n"),
		szVendorName, szModelName, szDeviceName, szIP, szMac, nPort, nHttpPort, nDeviceProtocolType);

	CString strKey;
	CString strValue;

	strKey.Format(_T("%s:%d"), szIP, nPort);
	strValue.Format(_T("%s:%s:%s:%d:%d:%d"), szModelName, szDeviceName, szMac, nHttpPort, bSupportIpInstall,nDeviceProtocolType);

	if(!m_AutoSearchMap.Lookup(strKey, strValue))
	{
		m_AutoSearchMap[strKey] = strValue;
		ELOGDNOLOCK(_T("OnDeviceDetected3():: %s -- %s\n"), strKey, strValue);
	}
}


void CSdkTestDlg::OnChangeDeviceAdminPasswordXnssdkdevicectrl(long nDeviceID, long nErrorCode)
{
	WLOGD(_T("Change Password, errcode=[%d](%s)\n"), nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode));

	if(nErrorCode == ERR_SUCCESS)
	{
		m_pDlgDeviceInfo->ReconnectNewPw(m_pChangePw->m_strNewPw);
	}

}


void CSdkTestDlg::OnOK()
{
	//CDialog::OnOK();
}
