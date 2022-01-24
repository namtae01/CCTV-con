///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012 by Hanwha Techwin, Inc.
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

#include "stdafx.h"
#include "VideoRawData.h"
#include "VideoRawDataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

//#define USE_CALLBACK_FUNC
#define PIXEL_FORMAT 32

// Network Camera/Encoder
#define MODEL_NAME	"Samsung Network Camera/Encoder"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CVideoRawDataDlg dialog



CVideoRawDataDlg::CVideoRawDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoRawDataDlg::IDD, pParent)
	, m_strPassword(_T("4321"))
	, m_strId(_T("admin"))
	, m_lnPort(4520)
	, m_hDevice(0)
	, m_hMediaSource(0)
	, m_bCheckConnect(FALSE)
	, m_bPlay(FALSE)
	, m_bDestroy(FALSE)
	, m_nHttpPort(80)
	, m_nDeviceProtocol(XDEVICE_PROTOCOL_UNKNOWN)
	, m_nMediaProtocol(XMEDIA_PROTOCOL_TCP)
	, m_strModelName(_T(""))
{
	m_pVideoBuf = new unsigned char[MAX_WIDTH * MAX_HEIGHT * 3];
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVideoRawDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//////////////////////////////////////////////////////////////////////////
	// Active X Control 
	DDX_Control(pDX, IDC_XNSSDKDEVICECTRL, m_ctrlXnsSdkDevice);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL, m_ctrlXnsSdkWindow);

	//////////////////////////////////////////////////////////////////////////
	// Control Member 
	DDX_Control(pDX, IDC_COMBO_MODEL_LIST, m_ctrlModelList);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ctrlIpAddress);
	DDX_Control(pDX, IDC_EDIT_PORT, m_ctrlPort);
	DDX_Control(pDX, IDC_EDIT_USER_ID, m_ctrlUserID);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ctrlPassword);
	DDX_Control(pDX, IDC_LIST_STATUS_MESSAGE, m_ctrlStatusList);


	//////////////////////////////////////////////////////////////////////////
	// Text Control
	DDX_Text(pDX, IDC_EDIT_USER_ID, m_strId);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_PORT, m_lnPort);
	DDX_Control(pDX, IDC_CHECK_RAW_VIDEO, m_ViewRawVideoCheckBox);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_nHttpPort);
	DDX_CBString(pDX, IDC_COMBO_MODEL_LIST, m_strModelName);
	DDX_Control(pDX, IDC_CHECK_SUNAPI, m_ctrlSunapi);
}

BEGIN_MESSAGE_MAP(CVideoRawDataDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CVideoRawDataDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CVideoRawDataDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CVideoRawDataDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CVideoRawDataDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_CHECK_RAW_VIDEO, &CVideoRawDataDlg::OnBnClickedCheckRawVideo)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CVideoRawDataDlg::OnCbnSelchangeComboModelList)
	ON_BN_CLICKED(IDC_CHECK_SUNAPI, &CVideoRawDataDlg::OnBnClickedCheckSunapi)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CVideoRawDataDlg, CDialog)
	ON_EVENT(CVideoRawDataDlg, IDC_XNSSDKDEVICECTRL, 10, CVideoRawDataDlg::OnDeviceStatusChangedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CVideoRawDataDlg, IDC_XNSSDKDEVICECTRL, 3, CVideoRawDataDlg::OnConnectFailedXnssdkdevicectrl, VTS_I4 VTS_I4)
	ON_EVENT(CVideoRawDataDlg, IDC_XNSSDKWINDOWCTRL, 22, CVideoRawDataDlg::OnVideoRawDataReceivedXnssdkwindowctrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CVideoRawDataDlg, IDC_XNSSDKWINDOWCTRL, 18, CVideoRawDataDlg::OnEventStatusChangedXnssdkwindowctrl, VTS_I4 VTS_I4)
	ON_EVENT(CVideoRawDataDlg, IDC_XNSSDKDEVICECTRL, 15, CVideoRawDataDlg::OnVideoLossEventXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CVideoRawDataDlg, IDC_XNSSDKDEVICECTRL, 20, CVideoRawDataDlg::OnNewMediaXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

// CVideoRawDataDlg message handlers

BOOL CVideoRawDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_ViewRawVideoCheckBox.SetCheck(TRUE);

#ifdef USE_CALLBACK_FUNC
	GetDlgItem(IDC_CHECK_RAW_VIDEO)->EnableWindow(FALSE);
#endif

	// ----------------------------------------------------------------------
	OnInitXnsSdk();
	OnInitModelList();
	OnSetDialog();
	// ----------------------------------------------------------------------



	setBtnStatus(STATUS_DISCONNECTED);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVideoRawDataDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVideoRawDataDlg::OnPaint()
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
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// @ User-Defined Block.
		// for Video screen Drawing. 
		// -----------------------------------------------------------------------
		{
			CPaintDC dc(this); // device context for painting

			HBITMAP hBmpOld = NULL;
			CRect rc;
			HDC hDC = dc.GetSafeHdc();
			GetDlgItem(IDC_BITMAP)->GetClientRect(&rc);

			SetStretchBltMode(hDC, COLORONCOLOR);
			StretchDIBits( hDC, 
				10, 10, rc.Width(), rc.Height()-rc.top,
				0, 0, m_nWidth, m_nHeight,
				m_pVideoBuf, (LPBITMAPINFO)&m_bmiHeader, DIB_RGB_COLORS, SRCCOPY);
		}

		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVideoRawDataDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// for ActiveX SDK Device control and Window Control initialize function.
// -----------------------------------------------------------------------
void CVideoRawDataDlg::OnInitXnsSdk(void)
{
	int nDeviceID = 1;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Initializes the DLL files. 
	// For this, XnsActiveX library requires config.xml, device.xml, 
	// and xns.xml files and the DLL file list should be mentioned 
	// in Xns.xml file. The path of the DLL file can not exceed 512 bytes
	// in length. The XnsActiveX library searches for xns.xml using 
	// XnsSDKDevice.ocx installed in "{$SDK path}\Config" folder.
	// -----------------------------------------------------------------------
	long nRet = m_ctrlXnsSdkDevice.Initialize();

	WLOGD(_T("Initialize() return=[%d](%s)\n"), 
		nRet, m_ctrlXnsSdkDevice.GetErrorString(nRet));
	DBG_LOG(_T("Start\n"));


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Initializes the XnsSdkWindow control. 
	// Namely, this will specify the window handle in order to display 
	// images on the screen. 
	// -----------------------------------------------------------------------
	nRet = m_ctrlXnsSdkWindow.Initialize(NULL, NULL);

	WLOGW(_T("Initialize() return=[%d](%s)\n"), 
		nRet, m_ctrlXnsSdkDevice.GetErrorString(nRet));

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Assigns memory space for saving device information. 
	// This function will return the device handle, which the application 
	// can use to control the device.
	// [in] Device ID The value should be a greater integer than 0.
	//      Minimum value: 1 , Maximum value: 3000
	// -----------------------------------------------------------------------
	if (!m_hDevice)
	{
		m_hDevice = m_ctrlXnsSdkDevice.CreateDevice(nDeviceID);                 // Create Device ID
	}

	if (m_hDevice == HANDLE_FAIL)
	{
		WLOGD(_T("CreateDevice() fail\n"));
	}
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// for Device Model List ComboBox initialize function.
// -----------------------------------------------------------------------
void CVideoRawDataDlg::OnInitModelList()
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Reads device list from {$SDK path}\Bin\Config\xns.xml. 
	// Finds information mentioned in the configuration file before returning. 
	// To enable this function, follow the steps below:
	// < Procedure >
	// Step 1. 	Use FindVendor(), FindModel(), FindDevice() to start searching.
	// Step 2. 	Use GetFindSize to get the array size.
	// Step 3. 	Use GetFindString() to obtain the vendor name and model name.
	// Step 4. 	Use GetFindLong() and GetFindDouble0 to obtain the device ID. 
	//			(Repeat this process if necessary)
	// Step 5. 	Call CloseFind0 to end the search.
	// -----------------------------------------------------------------------
	// Returns the handle of the Find array. 
	// Returns NULL(0) if no model list is found.
	long hFind = m_ctrlXnsSdkDevice.FindModel(_T("samsung"));			// Search Model 

	// Returns the length of the array that is created using FindVendor(), 
	// FindModel(), and FindDevice().
	long nFindSize = m_ctrlXnsSdkDevice.GetFindSize(hFind);				// Get Array Size
	CString strModel;

	for (int i = 0; i < nFindSize; i++)
	{
		// Reurns data of nIndex from the array created using FindVendor() 
		// and FindModel(). If nIndex is larger than the actual array, 
		// "" will be returned.
		strModel = m_ctrlXnsSdkDevice.GetFindString(hFind, i);			// Get Model Name 
		m_ctrlModelList.AddString(strModel);                            // Add Combo Box - Model Name
	}

	// Closes the Find command. Releases the memory space assinged by FindXXX().
	m_ctrlXnsSdkDevice.CloseFind(hFind);                                // End Search 
	int idx = m_ctrlModelList.FindStringExact(0, _T(MODEL_NAME));
	if(idx != CB_ERR)
	{
		m_ctrlModelList.SetCurSel(idx);
		m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
		UpdateData(FALSE);
	}

}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// for Dialog Control initialize function.
// -----------------------------------------------------------------------
void CVideoRawDataDlg::OnSetDialog(void)
{

	m_ctrlIpAddress.SetAddress(192,168,217,59);

	m_pCallbackFunc = ReceiveDecodingVideoFrame;
//	GetDlgItem(IDC_XNSSDKWINDOWCTRL)->ShowWindow(SW_HIDE);


}


void CVideoRawDataDlg::OnDestroy()
{
	// for Control Member Value Release
	m_bDestroy = TRUE;

	if( m_hDevice )
	{
		OnBnClickedButtonDisconnect();

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Cancels the memory space assigned for the device information by 
		// CreateDevice(). The device should be disconnected from the application
		// before this function is called.
		// -----------------------------------------------------------------------
		m_ctrlXnsSdkDevice.ReleaseDevice(m_hDevice);
	}
	delete [] m_pVideoBuf;
	CDialog::OnDestroy();
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Device Connect Function.
// -----------------------------------------------------------------------
void CVideoRawDataDlg::OnBnClickedButtonConnect()
{
	CString strModel;													// Model Name 
	CString strIpAddress;                                               // IP Address  
	BYTE address[ADDRESS_MAX];                                          // Byte Value in IP Address Box 
	long nIndex = m_ctrlModelList.GetCurSel();                          // ComBox Box : Device Index Value

	UpdateData(TRUE);


	m_ctrlModelList.GetLBText(nIndex, strModel);						// Get Model Name 
	m_ctrlIpAddress.GetAddress(address[0], address[1], address[2], address[3]);
	strIpAddress.Format(_T("%d.%d.%d.%d"), address[0], address[1], address[2], address[3]);


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Sets the device information so that the application can connect 
	// to the device.
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.SetConnectionInfo2(
		m_hDevice,					// [in] Device handle
		_T("Samsung"),				// [in] Fixed as 'Samsung'
		m_strModelName,				// [in] Name of model to connect to. The maximum length allowed is 126-byte.
		XADDRESS_IP,				// [in] Address type
		strIpAddress,				// [in] actual address according to address type.
		m_lnPort,					// [in] Port number
		m_nHttpPort,				// [in] Port number for web access	
		m_strId,					// [in] Login ID
		m_strPassword,					// [in] Password
		m_nDeviceProtocol,
		m_nMediaProtocol
		);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Enables the application to connect to the device using the connection 
	// information. You can use SetConnectionInfo() to configure the 
	// connection settings. This function performs as non-blocking function, 
	// and will be returned immediately even if the connection is not 
	// completed. The connection result will be transferred through the event. 
	// When connection is made successfully, the OnDeviceStatusChanged() event
	// will occur. When failed, the OnConnectFailed event occurs.
	// -----------------------------------------------------------------------
	long nRet = m_ctrlXnsSdkDevice.ConnectNonBlock(
		m_hDevice,														// [in] Device handle
		true,															// [in] Flag to decide where to forcibly log in or not.
		true);															// [in] If this value is 1, try to connect again.

	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ConnectNonBlock() fail: errno=[%d](%s)\n"), 
			nRet, m_ctrlXnsSdkDevice.GetErrorString(nRet));
		setBtnStatus(STATUS_DISCONNECTED);
	}

}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Device DisConnect Function.
// -----------------------------------------------------------------------
void CVideoRawDataDlg::OnBnClickedButtonDisconnect()
{
	OnBnClickedButtonStop();

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// This event occurs if the device status has changed. 
	// It occurs if the application uses Connect() to connect or reconnect 
	// to the device after disconnected.
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.Disconnect(m_hDevice);
	setBtnStatus(STATUS_DISCONNECTED);
	WLOGD(_T("Disconnect\n"));

}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Media Play Function.
// -----------------------------------------------------------------------
void CVideoRawDataDlg::OnBnClickedButtonPlay()
{
	long nCtrlID = 1;                                                     

	if( m_bPlay )
	{
		WLOGW(_T("Media stream is already played\n"));
		return;
	}

	if ( !m_bCheckConnect )
	{
		WLOGW(_T("Device is not connected...\n"));
		return;
	}


	//////////////////////////////////////////////////////////////////////////
	// Control mudule : DVR
	// Returns the type of control module
	if (m_ctrlXnsSdkDevice.GetControlType(m_hDevice, 1) & XCTL_DVR)   // Device Type : DVR
	{
		// XCTL_CAMERA : Camera channel of DVR. 
		for(int i=0; i<m_ctrlXnsSdkDevice.GetControlCount(m_hDevice, XCTL_CAMERA); i++)
		{
			// Displays video in real time.
			if (m_ctrlXnsSdkDevice.GetControlCapability(m_hDevice, i+2, XCTL_CAP_LIVE) )          
			{
				// Start getting media streams from the device.
				m_ctrlXnsSdkDevice.OpenMedia(m_hDevice,                // [in] Device Handle.
					i+2,                                               // [in] Control ID of Video control module 
					MEDIA_TYPE_LIVE,                                   // [in] Media type : MEDIA_TYPE_LIVE(=1) = Live
					0,                                                 // [in] Play start time
					0,                                                 // [in] Play end time
					&m_hMediaSource);                                  // [in] Media stream ID.
				// [ XNS ACTIVEX HELP ]
				// -----------------------------------------------------------------------
				// Adds the media source handle to XnsSdkWindow. 
				// The media source handle is created by XnsSdkDevice. 
				// If the application calls XnsSdkDevice::OpenMedia(), 
				// it will receive media stream from the device and return the MediaSource 
				// handle. The application uses uses Start() to forward the mediasource 
				// handle to XnsSdkWindow so that XnsSdkWindow can obtain stream data. 
				// -----------------------------------------------------------------------
				m_ctrlXnsSdkWindow.Start(m_hMediaSource);
					
				OnBnClickedCheckRawVideo();
				WLOGW(_T("Start receiving stream data...\n"));
				m_bPlay = TRUE;
				return;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Control mudule : Network Camera or Encoder Box(Video server)
	else if (m_ctrlXnsSdkDevice.GetControlType(m_hDevice, 1) & (XCTL_NETCAM | XCTL_ENCODER))
	{
		// Possible video stream of network camera
		for(int i=0; i<m_ctrlXnsSdkDevice.GetControlCount(m_hDevice, XCTL_VIDEO); i++)
		{
			//// Displays video in real time  and  Gets the status of the control module.
			//// OpenMedia profile 2
			if (m_ctrlXnsSdkDevice.GetControlCapability(m_hDevice, i+4, XCTL_CAP_LIVE) &&
				m_ctrlXnsSdkDevice.GetControlStatus(m_hDevice, i+4, XCAMERA_STATUS))
			{
				m_ctrlXnsSdkDevice.OpenMedia(m_hDevice,                // [in] Device Handle.
					i+4,                                               // [in] Control ID of Video control module 
					MEDIA_TYPE_LIVE,                                   // [in] Media type : MEDIA_TYPE_LIVE(=1) = Live
					0,                                                 // [in] Play start time
					0,                                                 // [in] Play end time
					&m_hMediaSource);                                  // [in] Media stream ID.

				// [ XNS ACTIVEX HELP ]
				// -----------------------------------------------------------------------
				// Adds the media source handle to XnsSdkWindow.
				// The media source handle is created by XnsSdkDevice. 
				// If the application calls XnsSdkDevice::OpenMedia(), 
				// it will receive media stream from the device and return the MediaSource handle. 
				// The application uses uses Start() to forward the mediasource handle 
				// to XnsSdkWindow so that XnsSdkWindow can obtain stream data.
				// -----------------------------------------------------------------------
				m_ctrlXnsSdkWindow.Start(m_hMediaSource);
				OnBnClickedCheckRawVideo();
				WLOGW(_T("Start receiving stream data...\n"));
				m_bPlay = TRUE;
				return;
			}
		}
	}
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Media Stop Function.
// -----------------------------------------------------------------------
void CVideoRawDataDlg::OnBnClickedButtonStop()
{
	if( !m_hMediaSource ) 
	{
		WLOGD(_T("Media stream was not opened\n"));
		return;
	}

	if( !m_bPlay )
	{
		WLOGW(_T("Media stream is not played\n"));
		return;
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Terminates transferring media stream data from the device. The media 
	// stream data will be separated by hMediaSource 
	// (i.e., phMediaSource of OpenMedia()).
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.CloseMedia(
		m_hDevice,														// [in] Device handle. This value is returned from CreateDevice(). 
		m_hMediaSource);												// [in] Media stream ID.

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Stops receiving the stream data from the media source handle.  
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkWindow.Stop();

	m_hMediaSource = 0;													// Media Source Initialize.
	m_bPlay = FALSE;
	WLOGW(_T("Stop receiving stream data...\n"));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event occurs if the device status has changed. It occurs if the 
// application uses Connect() to connect or reconnect to the device after 
// disconnected. When reconnecting, the third argument nDeviceStatus is 
// true, all media must be reopened using ReopenAllStream().
// -----------------------------------------------------------------------
void CVideoRawDataDlg::OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
	if((nErrorCode != ERR_SUCCESS) || (m_bDestroy == TRUE))
		return;

	if (nDeviceStatus == TRUE)
	{
		WLOGD(_T("Connected: deviceID=%d, errcode=%d, deviceStatus=%d\n"),
			nDeviceID, nErrorCode, nDeviceStatus);

		m_bCheckConnect = TRUE;
		setBtnStatus(STATUS_CONNECTED);
		OnBnClickedButtonPlay();
	}
	else
	{
		WLOGD(_T("Disconnected: deviceID=%d, errcode=%d, deviceStatus=%d\n"),
			nDeviceID, nErrorCode, nDeviceStatus);

		if (m_bCheckConnect == TRUE && m_hMediaSource)
		{
			OnBnClickedButtonStop();
		}

		m_bCheckConnect = FALSE;
		setBtnStatus(STATUS_DISCONNECTED);
	}
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// If the application has failed in non-blocking connection using 
// ConnectNonBlock(), the OnConnectFailed event occurs. As Connect() 
// returns an immediate error message if failed, it does not trigger 
// this event. 
// -----------------------------------------------------------------------
void CVideoRawDataDlg::OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode)
{
	WLOGD(_T("Disconnected: deviceID=%d, errcode=[%d](%s)\n"),
		nDeviceID, nErrorCode, m_ctrlXnsSdkDevice.GetErrorString(nErrorCode));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// for SetVideoCallbackFunc() Callback function. 
// -----------------------------------------------------------------------
void ReceiveDecodingVideoFrame(long hMediaSource, long nWidth, long nHeight, long nFrameSize, unsigned char* pVideo)
{
// 	CString str;
// 	str.Format(_T("hMediaSource[%d], nWidth[%d], nHeight[%d], nFrameSize[%d], pVideo[0x%x]\n"),
// 		hMediaSource, nWidth, nHeight, nFrameSize, pVideo);
// 	OutputDebugString(str);

	// for Video Frame Copy Function
	((CVideoRawDataDlg*)AfxGetApp()->m_pMainWnd)->OnVideoFrame(hMediaSource, nWidth, nHeight, nFrameSize, pVideo);	
	
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// for Video Frame Copy Function
// -----------------------------------------------------------------------
void CVideoRawDataDlg::OnVideoFrame(long hMediaSource, long nWidth, long nHeight, long nFrameSize, unsigned char* pVideo)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	ZeroMemory( &m_bmiHeader, sizeof(BITMAPINFOHEADER) );
 	m_bmiHeader.biWidth			= m_nWidth;
 	m_bmiHeader.biHeight		= m_nHeight*(-1);
 	m_bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
 	m_bmiHeader.biPlanes		= 1;
 	m_bmiHeader.biBitCount		= 24;
  	m_bmiHeader.biCompression	= BI_RGB;	
 	m_bmiHeader.biClrImportant	= 0;
 	m_bmiHeader.biSizeImage		= m_nWidth * m_nHeight * (m_bmiHeader.biBitCount / 8);

	// 32bit RGB -> 24bit RGB
	for(int i = 0 ; i < nHeight*nWidth; i++)
	{
		memcpy(&m_pVideoBuf[i*3],&pVideo[i*4],3);
	}
 
	// Call OnPaint 
	Invalidate(FALSE);
}


void CVideoRawDataDlg::OnVideoRawDataReceivedXnssdkwindowctrl(long nDeviceID, long nControlID, long nWidth, long nHeight, long nVideoSize, long pVideoData)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	unsigned char *pVideo = (unsigned char*)pVideoData;

//	m_ctrlXnsSdkWindow.SaveSnapshotWithData(pVideoData, nVideoSize, nWidth, nHeight, _T("C:\\Temp\\snapshot2.jpg"), 1);
	
	ZeroMemory( &m_bmiHeader, sizeof(BITMAPINFOHEADER) );
	m_bmiHeader.biWidth			= m_nWidth;
	m_bmiHeader.biHeight		= m_nHeight*-1;
	m_bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	m_bmiHeader.biPlanes		= 1;
	m_bmiHeader.biBitCount		= 24;
	m_bmiHeader.biCompression	= BI_RGB;	
	m_bmiHeader.biClrImportant	= 0;
	m_bmiHeader.biSizeImage		= m_nWidth * m_nHeight * (m_bmiHeader.biBitCount / 8);

	long pixel_format = m_ctrlXnsSdkWindow.GetVideoPixelFormat();
	if (pixel_format == XVIDEO_PIXEL_BGRA)
	{
		// 32bit RGB -> 24bit RGB
		for(int i = 0 ; i < nHeight*nWidth; i++)
		{
			memcpy(&m_pVideoBuf[i*3],&pVideo[i*4],3);
		}
	}
	else if (pixel_format == XVIDEO_PIXEL_R565)
	{// 16bit RGB -> 24bit RGB
		unsigned short *pVideo16 = (unsigned short *)pVideo;
		int index = 0;
		for(int i = 0 ; i < nHeight*nWidth; i++)
		{
			unsigned short rgb16 = pVideo16[i];
			m_pVideoBuf[index++] = (rgb16 & 0x001f) << 3;
			m_pVideoBuf[index++] = (rgb16 & 0x07e0) >> 3;
			m_pVideoBuf[index++] = (rgb16 & 0xf800) >> 8;
		}
	}

	// Call OnPaint 
	Invalidate(FALSE);
}


void CVideoRawDataDlg::OnBnClickedCheckRawVideo()
{
	if (m_hMediaSource == 0)
		return;

#ifdef USE_CALLBACK_FUNC
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Video Frame Callback Function. 
	// -----------------------------------------------------------------------
	if (m_ViewRawVideoCheckBox.GetCheck()==TRUE)
	{
		m_ctrlXnsSdkWindow.SetVideoCallbackFunc(
			m_hMediaSource, 
			(long)m_pCallbackFunc);
	}
#else
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Video Frame Callback Function. 
	// -----------------------------------------------------------------------
	if (m_ViewRawVideoCheckBox.GetCheck()==TRUE)
	{
		m_ctrlXnsSdkWindow.SetVideoRawDataReceived(m_hMediaSource);
	}
	else
	{
		m_ctrlXnsSdkWindow.UnSetVideoRawDataReceived(m_hMediaSource);
	}
#endif
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event informs that a video loss event occurs from the device.
// -----------------------------------------------------------------------
void CVideoRawDataDlg::OnEventStatusChangedXnssdkwindowctrl(long nOldEventStatus, long nNewEventStatus)
{
	// TODO: Add your message handler code here
	WLOGW(_T("OnEventStatusChangedXnssdkwindowctrl:: old_event_status=%d, new_event_status=%d\n"),
		nOldEventStatus, nNewEventStatus);

	//Event				Value
	//XEVENT_ALL		0x000000ff
	//XEVENT_SENSOR		0x00000001
	//XEVENT_MOTION		0x00000002
	//XEVENT_VIDEOLOSS	0x00000004

	if ( (nNewEventStatus != nOldEventStatus) &&
		nNewEventStatus == 0x04)
	{
		// 비디오 로스 이벤트는 10초간 카메라로부터 영상을 수신받지 못하였을 때 발생합니다.
		// 비디오 로스가 발생한 경우, 재접속하도록 수정합니다.)
		OnBnClickedButtonDisconnect();
		OnBnClickedButtonConnect();
	}
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the event status has changed. Event types include: 
// video loss, alarm, and motion detection.
// -----------------------------------------------------------------------
void CVideoRawDataDlg::OnVideoLossEventXnssdkdevicectrl(long nDeviceID, long nControlID, long tEventUTC)
{
	// TODO: Add your message handler code here
	WLOGD(_T("OnVideoLossEventXnssdkdevicectrl:: device_id=%d, control_id=%d, event_utc=%d\n"),
		nDeviceID, nControlID, tEventUTC);
}


void CVideoRawDataDlg::OnNewMediaXnssdkdevicectrl(long nDeviceID, long nControlID, long nMediaType, long hMediaData, long nInputType, long nFrameType, long nFrameTime, long nFrameSize, long nTimestamp)
{

	m_ctrlXnsSdkWindow.PushMedia(hMediaData);
	// TODO: Add your message handler code here
}


void CVideoRawDataDlg::OnOK()
{
	//CDialog::OnOK();
}


void CVideoRawDataDlg::OnCbnSelchangeComboModelList()
{
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
	SetCheckSunapi();
}


// Control button enable/disable
void CVideoRawDataDlg::setBtnStatus(BUTTON_STATUS nStatus)
{
	bool connect = false, disconnect = false,play = false, stop = false;
	switch(nStatus)
	{
	case STATUS_CONNECTED:
		disconnect = true;
		break;
	case STATUS_DISCONNECTED:
		connect = true;
		break;
	case STATUS_PLAY:
		disconnect = true;
		stop = true;
		break;
	case STATUS_STOP:
		disconnect = true;
		play = true;
		break;
	}

	// Connection Group
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(connect);
	GetDlgItem(IDC_COMBO_MODEL_LIST)->EnableWindow(connect);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_PW)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_PORT2)->EnableWindow(connect);
	
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(disconnect);
	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(play);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(stop);

	SetCheckSunapi();
}


void CVideoRawDataDlg::OnBnClickedCheckSunapi()
{
	SetCheckSunapi();
}


void CVideoRawDataDlg::SetCheckSunapi()
{
	GetDlgItem(IDC_CHECK_SUNAPI)->EnableWindow(FALSE);
	m_nDeviceProtocol = XDEVICE_PROTOCOL_UNKNOWN;

	if(m_strModelName == "Samsung Network Camera/Encoder" || m_strModelName == "Samsung NVR")
	{
		if(m_ctrlSunapi.GetCheck())
			m_nDeviceProtocol = XDEVICE_PROTOCOL_SUNAPI;
		if(m_ctrlXnsSdkDevice.GetDeviceStatus(m_hDevice) != XDEVICE_STATUS_CONNECTED)
			GetDlgItem(IDC_CHECK_SUNAPI)->EnableWindow(TRUE);
	}
}