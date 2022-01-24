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
// EventDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Event.h"
#include "EventDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

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


// CEventDlg dialog

CEventDlg::CEventDlg(CWnd* pParent /*=NULL*/)
: CDialog(CEventDlg::IDD, pParent)
, m_strModelName(_T(""))
, m_strUrl(_T(""))
, m_strId(_T("admin"))
, m_strPassword(_T("5tkatjd!"))
, m_nDeviceProtocol(XDEVICE_PROTOCOL_UNKNOWN)
, m_lnPort(4520)
, m_lnHttpPort(80)
, m_hDevice(0)
, m_bCheckConnect(FALSE)
, m_hMediaSource(0)
, m_nControlId(0)
, m_bAlarm(FALSE)
, m_bPlay(FALSE)
, m_bDestroy(FALSE)
, m_nIndex_Sensor(0)
, m_nIndex_Motion(0)
, m_nIndex_IV(0)
, m_nIndex_VideoLoss(0)
, m_nIndex_System(0)
, m_nIndex_Device(0)
, m_nDeviceCount(0)
, m_nAlarmControlId(0)
, m_nMediaProtocol(0)
, m_nChannelIndex(0)
, m_nProfileIndex(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//////////////////////////////////////////////////////////////////////////
	// Active X Control 
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL1, m_ctrlXnsSdkWindow);
	DDX_Control(pDX, IDC_XNSSDKDEVICECTRL1, m_ctrlXnsSdkDevice);

	//////////////////////////////////////////////////////////////////////////
	// Control Member 
	DDX_Control(pDX, IDC_COMBO_MODEL_LIST, m_ctrlModelList);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ctrlIpAddress);
	DDX_Control(pDX, IDC_EDIT_PORT, m_ctrlPort);
	DDX_Control(pDX, IDC_EDIT_PORT2, m_ctrlHttpPort);
	DDX_Control(pDX, IDC_EDIT_USER_ID, m_ctrlUserID);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ctrlPassword);

	DDX_Control(pDX, IDC_TAB_ALARM_EVENT, m_ctrlTab);
	DDX_Control(pDX, IDC_LIST_STATUS_MESSAGE, m_ctrlStatusList);
	DDX_Control(pDX, IDC_LIST_SENSOR_EVENT, m_ctrlSensorLog);
	DDX_Control(pDX, IDC_LIST_MOTION_EVENT, m_ctrlMotionLog);
	DDX_Control(pDX, IDC_LIST_IV_EVENT, m_ctrlIVLog);
	DDX_Control(pDX, IDC_LIST_VIDEOLOSS_EVENT, m_ctrlVideoLossLog);
	DDX_Control(pDX, IDC_LIST_SYSTEM_EVENT, m_ctrlSystemLog);
	DDX_Control(pDX, IDC_LIST_DEVICE_EVENT, m_ctrlDeviceLog);
	DDX_Control(pDX, IDC_LIST_AMD_EVENT, m_ctrlAMDLog);

	//////////////////////////////////////////////////////////////////////////
	// Text Control
	DDX_Text(pDX, IDC_COMBO_MODEL_LIST, m_strModelName);
	DDX_Text(pDX, IDC_EDIT_USER_ID, m_strId);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_PORT, m_lnPort);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_lnHttpPort);
	DDX_Control(pDX, IDC_CHECK_SUNAPI, m_ctrlSunapi);
}


//////////////////////////////////////////////////////////////////////////////
// MFC Control Message Map
BEGIN_MESSAGE_MAP(CEventDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CEventDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CEventDlg::OnBnClickedButtonDisconnect)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_ALARM_EVENT, &CEventDlg::OnTcnSelchangeTabEvent)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CEventDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CEventDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_CHECK_SET_ALARM, &CEventDlg::OnBnClickedCheckSetAlarm)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CEventDlg::OnCbnSelchangeComboModelList)
	ON_BN_CLICKED(IDC_CHECK_SUNAPI, &CEventDlg::OnBnClickedCheckSunapi)
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////
// Active X Control Message Map
BEGIN_EVENTSINK_MAP(CEventDlg, CDialog)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 10, CEventDlg::OnDeviceStatusChangedXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 3, CEventDlg::OnConnectFailedXnssdkdevicectrl1, VTS_I4 VTS_I4)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 13, CEventDlg::OnMotionEventXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 14, CEventDlg::OnSensorEventXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 15, CEventDlg::OnVideoLossEventXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 24, CEventDlg::OnControlRemoteNameChangedXnssdkdevicectrl1, VTS_I4 VTS_I4)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 1, CEventDlg::OnControlLocalNameChangedXnssdkdevicectrl1, VTS_I4 VTS_I4)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 11, CEventDlg::OnControlStatusChangedXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 30, CEventDlg::OnIvOccurEventXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 18, CEventDlg::OnPasswordChangedXnssdkdevicectrl1, VTS_I4 VTS_BSTR)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 23, CEventDlg::OnAlarmOutControlFailedXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 59, CEventDlg::OnFaceDetectionEventChangedXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 58, CEventDlg::OnTrackingEventChangedXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 60, CEventDlg::OnAudioDetectionEventChangedXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 61, CEventDlg::OnAMDEventChangedXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 62, CEventDlg::OnSystemEventChangedXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CEventDlg, IDC_XNSSDKDEVICECTRL1, 52, CEventDlg::OnVideoLossEndXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

// CEventDlg message handlers

BOOL CEventDlg::OnInitDialog()
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

	// ----------------------------------------------------------------------
	OnInitXnsSdk();
	OnInitModelList();
	OnSetDialog();
	// ----------------------------------------------------------------------

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEventDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEventDlg::OnPaint()
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
HCURSOR CEventDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// for ActiveX SDK Device control and Window Control initialize function.
// -----------------------------------------------------------------------
void CEventDlg::OnInitXnsSdk(void)
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
void CEventDlg::OnInitModelList(void)
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
	m_ctrlModelList.SetCurSel(0);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// for Dialog Control initialize function.
// -----------------------------------------------------------------------
void CEventDlg::OnSetDialog(void)
{
	// Tab control Initialize.
	static CString strEvent[EVENT_LOG] = {_T("Alarm"),_T("Motion"),_T("Inteligent Video"),_T("Video Loss"),_T("System Log"), _T("Device Log"), _T("AMD Log")};

	for(int i = 0; i < EVENT_LOG; i++)
	{	
		m_ctrlTab.InsertItem(i, strEvent[i], i);
	}

	m_ctrlSensorLog.ShowWindow(SW_SHOW);
	m_ctrlMotionLog.ShowWindow(SW_HIDE);
	m_ctrlIVLog.ShowWindow(SW_HIDE);
	m_ctrlVideoLossLog.ShowWindow(SW_HIDE);
	m_ctrlSystemLog.ShowWindow(SW_HIDE);
	m_ctrlDeviceLog.ShowWindow(SW_HIDE);
	m_ctrlAMDLog.ShowWindow(SW_HIDE);

	m_ctrlModelList.SetCurSel(0);
	int idx = m_ctrlModelList.FindStringExact(0, _T("Samsung Network Camera/Encoder"));
	if(idx != CB_ERR) 
	{
		m_ctrlModelList.SetCurSel(idx);
		m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
		UpdateData(FALSE);
	}
	else
		m_ctrlModelList.SetCurSel(62);

	m_ctrlIpAddress.SetAddress(192,168,216,48);
}


void CEventDlg::OnDestroy()
{

	// for Control Member Value Release
	m_bDestroy = TRUE;

	if( m_hDevice )
	{
		if(m_hMediaSource != NULL)
		{
			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Stops receiving the stream sata from the mediasource handle (pMediaSource).
			// -----------------------------------------------------------------------
			m_ctrlXnsSdkWindow.Stop();
			m_bPlay = FALSE;

			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Terminates transferring media stream data from the device. 
			// The media stream data will be separated by hMediaSource 
			// (i.e., phMediaSource of OpenMedia()).
			// -----------------------------------------------------------------------
			m_ctrlXnsSdkDevice.CloseMedia(
				m_hDevice,														// [in] Device handle. This value is returned from CreateDevice(). 
				m_hMediaSource);												// [in] Media stream ID.		
		}

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Cancels the memory space assigned for the device information by 
		// CreateDevice(). The device should be disconnected from the application
		// before this function is called.
		// -----------------------------------------------------------------------
		if(m_bCheckConnect == TRUE)
		{
			m_ctrlXnsSdkDevice.Disconnect(m_hDevice);
		}

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Cancels the memory space assigned for the device information by 
		// CreateDevice(). The device should be disconnected from the application
		// before this function is called.
		// -----------------------------------------------------------------------
		m_ctrlXnsSdkDevice.ReleaseDevice(m_hDevice);
	}

	CDialog::OnDestroy();
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// for Window Control Enable and Disable.
// -----------------------------------------------------------------------
void CEventDlg::OnEnableControlWindow(BOOL bCheck)
{
	// Control Enable
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(!bCheck);
	m_ctrlIpAddress.EnableWindow(!bCheck);
	m_ctrlModelList.EnableWindow(!bCheck);
	m_ctrlPort.EnableWindow(!bCheck);
	m_ctrlHttpPort.EnableWindow(!bCheck);
	m_ctrlUserID.EnableWindow(!bCheck);
	m_ctrlPassword.EnableWindow(!bCheck);
	m_ctrlSunapi.EnableWindow(!bCheck);

	// Control Disable
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(bCheck);
	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(bCheck);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(bCheck);
	GetDlgItem(IDC_CHECK_SET_ALARM)->EnableWindow(bCheck);

	SetCheckSunapi();
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// for Window Control(in Tab control) Enable and Disable.
// -----------------------------------------------------------------------
void CEventDlg::OnSetEventlogList(int nStatus)
{
	switch(nStatus)
	{
	case INDEX_ALARM:
		m_ctrlSensorLog.ShowWindow(SW_SHOW);
		m_ctrlMotionLog.ShowWindow(SW_HIDE);
		m_ctrlIVLog.ShowWindow(SW_HIDE);
		m_ctrlVideoLossLog.ShowWindow(SW_HIDE);
		m_ctrlSystemLog.ShowWindow(SW_HIDE);
		m_ctrlDeviceLog.ShowWindow(SW_HIDE);
		m_ctrlAMDLog.ShowWindow(SW_HIDE);
		break;

	case INDEX_MOTION:
		m_ctrlSensorLog.ShowWindow(SW_HIDE);
		m_ctrlMotionLog.ShowWindow(SW_SHOW);
		m_ctrlIVLog.ShowWindow(SW_HIDE);
		m_ctrlVideoLossLog.ShowWindow(SW_HIDE);
		m_ctrlSystemLog.ShowWindow(SW_HIDE);
		m_ctrlDeviceLog.ShowWindow(SW_HIDE);
		m_ctrlAMDLog.ShowWindow(SW_HIDE);
		break;

	case INDEX_IV:
		m_ctrlSensorLog.ShowWindow(SW_HIDE);
		m_ctrlMotionLog.ShowWindow(SW_HIDE);
		m_ctrlIVLog.ShowWindow(SW_SHOW);
		m_ctrlVideoLossLog.ShowWindow(SW_HIDE);
		m_ctrlSystemLog.ShowWindow(SW_HIDE);
		m_ctrlDeviceLog.ShowWindow(SW_HIDE);
		m_ctrlAMDLog.ShowWindow(SW_HIDE);
		break;

	case INDEX_VIDEOLOSS:
		m_ctrlSensorLog.ShowWindow(SW_HIDE);
		m_ctrlMotionLog.ShowWindow(SW_HIDE);
		m_ctrlIVLog.ShowWindow(SW_HIDE);
		m_ctrlVideoLossLog.ShowWindow(SW_SHOW);
		m_ctrlSystemLog.ShowWindow(SW_HIDE);
		m_ctrlDeviceLog.ShowWindow(SW_HIDE);
		m_ctrlAMDLog.ShowWindow(SW_HIDE);
		break;

	case INDEX_SYSTEM:
		m_ctrlSensorLog.ShowWindow(SW_HIDE);
		m_ctrlMotionLog.ShowWindow(SW_HIDE);
		m_ctrlIVLog.ShowWindow(SW_HIDE);
		m_ctrlVideoLossLog.ShowWindow(SW_HIDE);
		m_ctrlSystemLog.ShowWindow(SW_SHOW);
		m_ctrlDeviceLog.ShowWindow(SW_HIDE);
		m_ctrlAMDLog.ShowWindow(SW_HIDE);
		break;

	case INDEX_DEVICE:
		m_ctrlSensorLog.ShowWindow(SW_HIDE);
		m_ctrlMotionLog.ShowWindow(SW_HIDE);
		m_ctrlIVLog.ShowWindow(SW_HIDE);
		m_ctrlVideoLossLog.ShowWindow(SW_HIDE);
		m_ctrlSystemLog.ShowWindow(SW_HIDE);
		m_ctrlDeviceLog.ShowWindow(SW_SHOW);
		m_ctrlAMDLog.ShowWindow(SW_HIDE);
		break;

	case INDEX_AMD:
		m_ctrlSensorLog.ShowWindow(SW_HIDE);
		m_ctrlMotionLog.ShowWindow(SW_HIDE);
		m_ctrlIVLog.ShowWindow(SW_HIDE);
		m_ctrlVideoLossLog.ShowWindow(SW_HIDE);
		m_ctrlSystemLog.ShowWindow(SW_HIDE);
		m_ctrlDeviceLog.ShowWindow(SW_HIDE);
		m_ctrlAMDLog.ShowWindow(SW_SHOW);
		break;

	default:
		break;
	}
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Device Connect Function.
// -----------------------------------------------------------------------
void CEventDlg::OnBnClickedButtonConnect()
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
	// Sets the device informaiton so that the application can connect 
	// to the device.
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.SetConnectionInfo2(
		m_hDevice,				// [in] Device handle
		_T("Samsung"),			// [in] Fixed as 'Samsung'
		m_strModelName,			// [in] Name of model to connect to. The maximum length allowed is 126-byte.
		XADDRESS_IP,			// [in] Address type
		strIpAddress,			// [in] actual address according to address type.
		m_lnPort,				// [in] Port number
		m_lnHttpPort,			// [in] Port number for web access	
		m_strId,				// [in] Login ID
		m_strPassword,			// [in] Password
		m_nDeviceProtocol,		// [in] Protocol
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
	}


}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Device DisConnect Function.
// -----------------------------------------------------------------------
void CEventDlg::OnBnClickedButtonDisconnect()
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Stops receiving the stream sata from 
	// the mediasource handle (pMediaSource).
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkWindow.Stop();

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
	// This event occurs if the device status has changed. 
	// It occurs if the application uses Connect() to connect or reconnect 
	// to the device after disconnected.
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.Disconnect(m_hDevice);

	WLOGD(_T("Disconnect\n"));

	m_hMediaSource = 0;													// Media Source Initialize.
	m_bPlay = FALSE;
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event occurs if the device status has changed. It occurs if the 
// application uses Connect() to connect or reconnect to the device after 
// disconnected. When reconnecting, the third argument nDeviceStatus is 
// true, all media must be reopened using ReopenAllStream().
// -----------------------------------------------------------------------
void CEventDlg::OnDeviceStatusChangedXnssdkdevicectrl1(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
	if((nErrorCode != ERR_SUCCESS) || (m_bDestroy == TRUE))
		return;

	WLOGD(_T("Device Status : deviceID=%d, errcode=%d, deviceStatus=%d\n"),
		nDeviceID, nErrorCode, nDeviceStatus);

	CString str;
	m_nAlarmControlId = 0;

	// Connect Success.
	if ((nErrorCode == ERR_SUCCESS) && (nDeviceStatus == TRUE))
	{
		m_bCheckConnect = TRUE;
		if ((m_bCheckConnect == TRUE) && (m_bDestroy == FALSE))
		{
			OnEnableControlWindow(m_bCheckConnect);
			WLOGD(_T("Connection Success !"));
			
			// System Log
			str.Format(_T("[system Log][%d] / [Device Connection Success.]"), ++m_nIndex_System);
			m_ctrlSystemLog.AddString(str);
			m_ctrlDeviceLog.SetCurSel(m_ctrlDeviceLog.GetCount()-1);
		}
	}
	// DisConnect Success.
	else if ((nErrorCode == ERR_SUCCESS) && (nDeviceStatus == FALSE))
	{
		m_bCheckConnect = FALSE;
		OnEnableControlWindow(m_bCheckConnect);
		WLOGD(_T("DisConnection Success !"));

		// System Log
		str.Format(_T("[system Log][%d] / [Device Disconnection Success.]"), ++m_nIndex_System);
		m_ctrlSystemLog.AddString(str);
		m_ctrlDeviceLog.SetCurSel(m_ctrlDeviceLog.GetCount()-1);
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
void CEventDlg::OnConnectFailedXnssdkdevicectrl1(long nDeviceID, long nErrorCode)
{
	WLOGD(_T("Disconnected: deviceID=%d, errcode=[%d](%s)\n"),
		nDeviceID, nErrorCode, m_ctrlXnsSdkDevice.GetErrorString(nErrorCode));

	// System Log
	CString str;
	str.Format(_T("[system Log][%d] / [%s]"), ++m_nIndex_System, m_ctrlXnsSdkDevice.GetErrorString(nErrorCode));
	m_ctrlSystemLog.AddString(str);
	m_ctrlDeviceLog.SetCurSel(m_ctrlDeviceLog.GetCount()-1);

}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Media Play Function.
// -----------------------------------------------------------------------
void CEventDlg::OnBnClickedButtonPlay()
{
	if( m_bPlay )
	{
		WLOGW(_T("Media stream is already played\n"));
		return;
	}

	if ((m_bCheckConnect == TRUE) && (m_bPlay == TRUE))
	{
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(FALSE);
	}

	if (m_bCheckConnect == TRUE)         // Function and Devece Status Success 
	{
		UpdateData(TRUE);
		WLOGD(_T("Open media stream::channel(%d), profile(%d)\n"), m_nChannelIndex+1, m_nProfileIndex+1);

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Returns the type of control module corresponding to the control ID.
		//
		// < DVR/NVR control module structure >
		// +------------------------------------------------------------
		// Control Module(Device, 1) ----------------- Control ID : 1
		// |---- Control Module(Camera, 1) ----------- Control ID : 2
		// |---- Control Module(Camera, 2) ----------- Control ID : 3
		// |---- Control Module(Camera, 3) ----------- Control ID : 4
		// |---- ....
		// |---- Control Module(Camera,16) ----------- Control ID : 17
		// |---- Control Module(Sensor-in, 1) -------- Control ID : 18
		// |---- ...
		// |---- Control Module(Sensor-in, 16) ------- Control ID : 34
		// |---- Control Module(Digital-out, 1) ------ Control ID : 35
		// |---- ...
		// |---- Control Module(Digital-out, 4) ------ Control ID : 38
		// +------------------------------------------------------------
		//
		// < Network Camera control module structure >
		// +------------------------------------------------------------
		// Control Module(Device, 1) ----------------- Control ID : 1
		// |---- Control Module(Camera, 1) ----------- Control ID : 2
		//       |--- Control Module(Video, 1) ------- Control ID : 3
		//       |--- Control Module(Video, 2) ------- Control ID : 4
		//       |--- ...
		//       |--- Control Module(Video, 10) ------ Control ID : 12
		//       |--- Control Module(Sensor-in, 1) --- Control ID : 13
		//       |--- Control Module(Digital-out, 1) - Control ID : 14
		// +------------------------------------------------------------
		//
		//< MultiProfile DVR/NVR control module structure >
		// +------------------------------------------------------------
		// Control Module(Device, 1) ----------------- Control ID : 1
		// |---- Control Module(Camera, 1) ----------- Control ID : 2
		//       |--- Control Module(Video, 1) ------- Control ID : 3
		//       |--- ...
		// |---- Control Module(Camera, 2) ----------- Control ID : 
		//       |--- Control Module(Video, 1) ------- Control ID : 
		//       |--- ...
		// |---- ...
		// |---- Control Module(Sensor-in, 16) ------- Control ID : 
		// |---- Control Module(Digital-out, 1) ------ Control ID : 
		// |---- ...
		// |---- Control Module(Digital-out, 4) ------ Control ID : 	
		// +------------------------------------------------------------ 
		//
		// -----------------------------------------------------------------------
		m_nControlId = m_ctrlXnsSdkDevice.GetVideoControlID(m_hDevice, m_nChannelIndex+1, m_nProfileIndex+1);
		if( m_ctrlXnsSdkDevice.OpenMedia(m_hDevice, m_nControlId, MEDIA_TYPE_LIVE, 0, 0, &m_hMediaSource) == ERR_SUCCESS )
		{
			WLOGW(_T("Open media...control id=[%d]\n"), m_nControlId);
			m_ctrlXnsSdkWindow.Start(m_hMediaSource);
			WLOGW(_T("Start receiving media stream data...\n"));
			m_bPlay = TRUE;
			
			return;
		}
	
		WLOGD(_T("Invalid device..\n"));
		
	}
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Media Stop Function.
// -----------------------------------------------------------------------
void CEventDlg::OnBnClickedButtonStop()
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
	// Stops receiving the stream data from the media source handle.  
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkWindow.Stop();

	WLOGW(_T("Stop receiving stream data...\n"));

	m_bPlay = FALSE;
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Media Stop Function.
// -----------------------------------------------------------------------
void CEventDlg::OnTcnSelchangeTabEvent(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nIndex = m_ctrlTab.GetCurSel();

	OnSetEventlogList(nIndex);

	UpdateData();
	*pResult = 0;
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// For an alarm occurs.
// -----------------------------------------------------------------------
void CEventDlg::OnBnClickedCheckSetAlarm()
{
	m_bAlarm = !m_bAlarm;

	if(m_nAlarmControlId==0)
	{
		long nCount = m_ctrlXnsSdkDevice.GetControlCount(m_hDevice, XCTL_ALL);
		int i = 0;
		for (i=1; i<= nCount ; i++)
		{
			// Returns the type of control module corresponding to the control ID.
			long nType = m_ctrlXnsSdkDevice.GetControlType(m_hDevice, i);
			WLOGD(_T("GetControlType():: controlType=(%d)[%#02x]\n"), 
				i, nType);
			if(nType == XCTL_ALARM)
			{
				WLOGD(_T("GetControlType():: Alarm control id=%d\n"), i);
				m_nAlarmControlId = i;
				break;
			}
		}
		if(m_nAlarmControlId==0)
		{
			WLOGD(_T("GetControlType():: Not found Alarm control id\n"));
			return;
		}
	}
	
	if(m_ctrlXnsSdkDevice.GetControlCapability(m_hDevice, m_nAlarmControlId, XCTL_CAP_ALARM_ONOFF))
	{
		// Search all device.
		if (m_bAlarm == TRUE)
		{
			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Turns on or off the alarm-out device (also called digital-out device). 
			// To enable this function, 
			// the control module should support the XCTL_CAP_ALARM_ONOFF capability.
			// -----------------------------------------------------------------------
			m_ctrlXnsSdkDevice.SetAlarm(
				m_hDevice,												// [in] Device handle. This value is returned from CreateDevice().
				m_nAlarmControlId,											// [in] Control ID.
				ALARM_ON);												// [in] Status of the alarm device.
		}
		else
		{
			m_ctrlXnsSdkDevice.SetAlarm(
				m_hDevice,													// [in] Device handle. This value is returned from CreateDevice().
				m_nAlarmControlId,												// [in] Control ID.
				ALARM_OFF);													// [in] Status of the alarm device.
		}
	}
	
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event occurs if the application has failed to control the alarm-out.
// -----------------------------------------------------------------------
void CEventDlg::OnAlarmOutControlFailedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nErrorCode)
{
	CString str;
	str.Format(_T("[Alarm][%d] / [%s]"), ++m_nIndex_Sensor, m_ctrlXnsSdkDevice.GetErrorString(nErrorCode));

	m_ctrlSensorLog.AddString(str);
	m_ctrlSensorLog.SetCurSel(m_ctrlSensorLog.GetCount()-1);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This events informs that a sensor-in (i.e., alarm-in) 
// event occurs from the device.
// -----------------------------------------------------------------------
void CEventDlg::OnSensorEventXnssdkdevicectrl1(long nDeviceID, long nControlID, long nSensorNumber, long tEventUTC)
{
	CString str;
	long Year, Mon, Day;
	long Hour, Min, Sec;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local UTC t_time to t_time. 
	// Return Value : Number of blocks of the recording data in the timeline. 
	// -----------------------------------------------------------------------
	long tLocal = 0;
	tLocal = m_ctrlXnsSdkDevice.UTCToDeviceLocalTime(
		m_hDevice,												// [in] Device handle. This value is returned from CreateDevice(). 
		tEventUTC);												// [in] local time_t value


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.TimetToDate(
		tLocal,													// [in] Data in time_t format to convert.
		&Year,													// [out] Year
		&Mon,													// [out] Month
		&Day,													// [out] Day
		&Hour,													// [out] Hour
		&Min,													// [out] Minute
		&Sec);													// [out] Second

	str.Format(_T("[Alarm][%d] / [Time(Remote) : %d-%02d-%02d  %02d:%02d:%02d]"), 
		++m_nIndex_Sensor, Year, Mon, Day, Hour, Min, Sec);

	m_ctrlSensorLog.AddString(str);
	m_ctrlSensorLog.SetCurSel(m_ctrlSensorLog.GetCount()-1);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event informs that a motion event occurs from the device.
// -----------------------------------------------------------------------
void CEventDlg::OnMotionEventXnssdkdevicectrl1(long nDeviceID, long nControlID, long tEventUTC)
{
	CString str;
	long Year, Mon, Day;
	long Hour, Min, Sec;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local UTC t_time to t_time. 
	// Return Value : Number of blocks of the recording data in the timeline. 
	// -----------------------------------------------------------------------
	long tLocal = 0;
	tLocal = m_ctrlXnsSdkDevice.UTCToDeviceLocalTime(
		m_hDevice,												// [in] Device handle. This value is returned from CreateDevice(). 
		tEventUTC);												// [in] local time_t value


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.TimetToDate(
		tLocal,													// [in] Data in time_t format to convert.
		&Year,													// [out] Year
		&Mon,													// [out] Month
		&Day,													// [out] Day
		&Hour,													// [out] Hour
		&Min,													// [out] Minute
		&Sec);													// [out] Second

	str.Format(_T("[Motion][%d] / [Time(Remote) : %d-%02d-%02d  %02d:%02d:%02d]"), 
		++m_nIndex_Motion, Year, Mon, Day, Hour, Min, Sec);

	m_ctrlMotionLog.AddString(str);
	m_ctrlMotionLog.SetCurSel(m_ctrlMotionLog.GetCount()-1);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This events informs that IV event occurs at device.
// -----------------------------------------------------------------------
void CEventDlg::OnIvOccurEventXnssdkdevicectrl1(long nDeviceID, long nControlID, long tEventUTC, long nIvType)
{
	CString str;
	long Year, Mon, Day;
	long Hour, Min, Sec;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local UTC t_time to t_time. 
	// Return Value : Number of blocks of the recording data in the timeline. 
	// -----------------------------------------------------------------------
	long tLocal = 0;
	tLocal = m_ctrlXnsSdkDevice.UTCToDeviceLocalTime(
		m_hDevice,												// [in] Device handle. This value is returned from CreateDevice(). 
		tEventUTC);												// [in] local time_t value


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.TimetToDate(
		tLocal,													// [in] Data in time_t format to convert.
		&Year,													// [out] Year
		&Mon,													// [out] Month
		&Day,													// [out] Day
		&Hour,													// [out] Hour
		&Min,													// [out] Minute
		&Sec);													// [out] Second

	str.Format(_T("[Inteligent Video][%d] / [Time(Remote) : %d-%02d-%02d  %02d:%02d:%02d]"), 
		++m_nIndex_IV, Year, Mon, Day, Hour, Min, Sec);

	m_ctrlIVLog.AddString(str);
	m_ctrlIVLog.SetCurSel(m_ctrlIVLog.GetCount()-1);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event informs that a video loss event occurs from the device.
// -----------------------------------------------------------------------
void CEventDlg::OnVideoLossEventXnssdkdevicectrl1(long nDeviceID, long nControlID, long tEventUTC)
{
	CString str;
	long Year, Mon, Day;
	long Hour, Min, Sec;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local UTC t_time to t_time. 
	// Return Value : Number of blocks of the recording data in the timeline. 
	// -----------------------------------------------------------------------
	long tLocal = 0;
	tLocal = m_ctrlXnsSdkDevice.UTCToDeviceLocalTime(
		m_hDevice,												// [in] Device handle. This value is returned from CreateDevice(). 
		tEventUTC);												// [in] local time_t value


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.TimetToDate(
		tLocal,													// [in] Data in time_t format to convert.
		&Year,													// [out] Year
		&Mon,													// [out] Month
		&Day,													// [out] Day
		&Hour,													// [out] Hour
		&Min,													// [out] Minute
		&Sec);													// [out] Second

	str.Format(_T("[Video Loss][%d] DeviceID[%d] ControlID[%d] / [Time(Remote) : %d-%02d-%02d  %02d:%02d:%02d]"), 
		++m_nIndex_VideoLoss, nDeviceID, nControlID, Year, Mon, Day, Hour, Min, Sec);

	m_ctrlVideoLossLog.AddString(str);
	m_ctrlVideoLossLog.SetCurSel(m_ctrlVideoLossLog.GetCount()-1);
}

//////////////////////////////////////////////////////////////////////////
// Device Log

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event occurs if a control module of DVR has been renamed.
// -----------------------------------------------------------------------
void CEventDlg::OnControlRemoteNameChangedXnssdkdevicectrl1(long nDeviceID, long nControlID)
{
	CString str;
	str.Format(_T("[Device Log][%d] / [Control module of DVR has been renamed.]"), ++m_nIndex_Device);

	m_ctrlDeviceLog.AddString(str);
	m_ctrlDeviceLog.SetCurSel(m_ctrlDeviceLog.GetCount()-1);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// If the control module is renamed in the local PC, 
// the ActiveX object will trigger the OnControlLocalNameChanged event.
// The event will also occur if the application tries to rename 
// the control module using ChangeControlLocalName().
// -----------------------------------------------------------------------
void CEventDlg::OnControlLocalNameChangedXnssdkdevicectrl1(long nDeviceID, long nControlID)
{
	CString str;
	str.Format(_T("[Device Log][%d] / [The control module is renamed in the local PC.]"), ++m_nIndex_Device);

	m_ctrlDeviceLog.AddString(str);
	m_ctrlDeviceLog.SetCurSel(m_ctrlDeviceLog.GetCount()-1);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event occurs if a control module of DVR has been renamed.
// -----------------------------------------------------------------------
void CEventDlg::OnControlStatusChangedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nErrorCode, long nStatusMask)
{
	CString str;
	str.Format(_T("Control Status Changed DeviceID[%d] ControlID[%d], Status[%d], ErrCode[%s]\n", nDeviceID, nControlID, nStatusMask, m_ctlXnsDevice.GetErrorString(nErrorCode)));
	
	m_ctrlDeviceLog.AddString(str);
	m_ctrlDeviceLog.SetCurSel(m_ctrlDeviceLog.GetCount()-1);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event occurs if a control module of DVR has been renamed.
// -----------------------------------------------------------------------
void CEventDlg::OnPasswordChangedXnssdkdevicectrl1(long nDeviceID, LPCTSTR szID)
{
	CString str;
	str.Format(_T("[Device Log][%d] / [the password for DVR has changed.]"), ++m_nIndex_Device);

	m_ctrlDeviceLog.AddString(str);
	m_ctrlDeviceLog.SetCurSel(m_ctrlDeviceLog.GetCount()-1);
}
//////////////////////////////////////////////////////////////////////////


void CEventDlg::OnFaceDetectionEventChangedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nSubEvent, long tEventUTC, long nParam1, long nParam2, long nParam3, long nParam4, LPCTSTR description, LPCTSTR strParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CString str;
	CString subEvent;

	long Year, Mon, Day;
	long Hour, Min, Sec;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local UTC t_time to t_time. 
	// Return Value : Number of blocks of the recording data in the timeline. 
	// -----------------------------------------------------------------------
	long tLocal = 0;
	tLocal = m_ctrlXnsSdkDevice.UTCToDeviceLocalTime(
		m_hDevice,												// [in] Device handle. This value is returned from CreateDevice(). 
		tEventUTC);												// [in] local time_t value


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.TimetToDate(
		tLocal,													// [in] Data in time_t format to convert.
		&Year,													// [out] Year
		&Mon,													// [out] Month
		&Day,													// [out] Day
		&Hour,													// [out] Hour
		&Min,													// [out] Minute
		&Sec);													// [out] Second

	if(nSubEvent == XEVT_FACE_DETECTION_OCCUR)
		subEvent.Format(_T("OCCUR"));

	str.Format(_T("[Face Detection Event Detected] [SubEvent Type : %s] [Time(Remote) : %d-%02d-%02d  %02d:%02d:%02d] "), 
		subEvent, Year, Mon, Day, Hour, Min, Sec);

	m_ctrlIVLog.InsertString(-1,str);
	m_ctrlIVLog.SetCurSel(m_ctrlIVLog.GetCount()-1);
}


void CEventDlg::OnTrackingEventChangedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nSubEvent, long tEventUTC, long nParam1, long nParam2, long nParam3, long nParam4, LPCTSTR description, LPCTSTR strParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString str;
	CString subEvent;
	long Year, Mon, Day;
	long Hour, Min, Sec;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local UTC t_time to t_time. 
	// Return Value : Number of blocks of the recording data in the timeline. 
	// -----------------------------------------------------------------------
	long tLocal = 0;
	tLocal = m_ctrlXnsSdkDevice.UTCToDeviceLocalTime(
		m_hDevice,												// [in] Device handle. This value is returned from CreateDevice(). 
		tEventUTC);												// [in] local time_t value


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.TimetToDate(
		tLocal,													// [in] Data in time_t format to convert.
		&Year,													// [out] Year
		&Mon,													// [out] Month
		&Day,													// [out] Day
		&Hour,													// [out] Hour
		&Min,													// [out] Minute
		&Sec);													// [out] Second


	if(nSubEvent == XEVT_TRACKING_OCCUR)
		subEvent.Format(_T("OCCUR"));

	str.Format(_T("[Tracking Event Detected] [SubEvent Type : %s] [Time(Remote) : %d-%02d-%02d  %02d:%02d:%02d] "), 
		subEvent, Year, Mon, Day, Hour, Min, Sec);

	m_ctrlSensorLog.InsertString(-1,str);
	m_ctrlSensorLog.SetCurSel(m_ctrlSensorLog.GetCount()-1);
}


void CEventDlg::OnAudioDetectionEventChangedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nSubEvent, long tEventUTC, long nParam1, long nParam2, long nParam3, long nParam4, LPCTSTR description, LPCTSTR strParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString str;
	CString subEvent;
	long Year, Mon, Day;
	long Hour, Min, Sec;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local UTC t_time to t_time. 
	// Return Value : Number of blocks of the recording data in the timeline. 
	// -----------------------------------------------------------------------
	long tLocal = 0;
	tLocal = m_ctrlXnsSdkDevice.UTCToDeviceLocalTime(
		m_hDevice,												// [in] Device handle. This value is returned from CreateDevice(). 
		tEventUTC);												// [in] local time_t value


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.TimetToDate(
		tLocal,													// [in] Data in time_t format to convert.
		&Year,													// [out] Year
		&Mon,													// [out] Month
		&Day,													// [out] Day
		&Hour,													// [out] Hour
		&Min,													// [out] Minute
		&Sec);													// [out] Second


	if(nSubEvent == XEVT_AUDIO_DETECTION_OCCUR)
		subEvent.Format(_T("OCCUR"));

	str.Format(_T("[Audio Detection Event Detected] [SubEvent Type : %s] [Time(Remote) : %d-%02d-%02d  %02d:%02d:%02d] "), 
		subEvent, Year, Mon, Day, Hour, Min, Sec);

	m_ctrlSensorLog.InsertString(-1,str);
	m_ctrlSensorLog.SetCurSel(m_ctrlSensorLog.GetCount()-1);
}


void CEventDlg::OnAMDEventChangedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nSubEvent, long tEventUTC, long nParam1, long nParam2, long nParam3, long nParam4, LPCTSTR description, LPCTSTR strParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString str;
	CString subEvent;
	long Year, Mon, Day;
	long Hour, Min, Sec;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local UTC t_time to t_time. 
	// Return Value : Number of blocks of the recording data in the timeline. 
	// -----------------------------------------------------------------------
	long tLocal = 0;
	tLocal = m_ctrlXnsSdkDevice.UTCToDeviceLocalTime(
		m_hDevice,												// [in] Device handle. This value is returned from CreateDevice(). 
		tEventUTC);												// [in] local time_t value


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.TimetToDate(
		tLocal,													// [in] Data in time_t format to convert.
		&Year,													// [out] Year
		&Mon,													// [out] Month
		&Day,													// [out] Day
		&Hour,													// [out] Hour
		&Min,													// [out] Minute
		&Sec);													// [out] Second

	if(nSubEvent == XEVT_AMD_ROI_MOTION_DETECTION_START)
		subEvent.Format(_T("ROI_MOTION_DETECTION_START"));
	
	else if(nSubEvent == XEVT_AMD_ROI_MOTION_DETECTION_STOP)
		subEvent.Format(_T("ROI_MOTION_DETECTION_STOP"));

	else if(nSubEvent == XEVT_AMD_LIB_LOAD_FAILED)
		subEvent.Format(_T("LIB_LOAD_FAILED"));

	else if(nSubEvent == XEVT_AMD_LOW_FPS_START)
		subEvent.Format(_T("LOW_FPS_START"));

	else if(nSubEvent == XEVT_AMD_LOW_FPS_END)
		subEvent.Format(_T("LOW_FPS_END"));

	else if(nSubEvent == XEVT_AMD_DSP_DISPLAY_START)
		subEvent.Format(_T("DSP_DISPLAY_START"));

	else if(nSubEvent == XEVT_AMD_DSP_DISPLAY_FAIL)
		subEvent.Format(_T("DSP_DISPLAY_FAIL"));

	else if(nSubEvent == XEVT_AMD_DSP_VA_START)
		subEvent.Format(_T("DSP_VA_START"));

	else if(nSubEvent == XEVT_AMD_DSP_VA_FAIL)
		subEvent.Format(_T("DSP_VA_FAIL"));


	str.Format(_T("[AMD Event Detected] [SubEvent Type : %s] [Time(Remote) : %d-%02d-%02d  %02d:%02d:%02d] "), 
		subEvent, Year, Mon, Day, Hour, Min, Sec);

	m_ctrlAMDLog.InsertString(-1,str);
	m_ctrlAMDLog.SetCurSel(m_ctrlAMDLog.GetCount()-1);
}


void CEventDlg::OnSystemEventChangedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nSubEvent, long tEventUTC, long nParam1, long nParam2, long nParam3, long nParam4, LPCTSTR description, LPCTSTR strParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString str;
	CString subEvent;
	long Year, Mon, Day;
	long Hour, Min, Sec;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local UTC t_time to t_time. 
	// Return Value : Number of blocks of the recording data in the timeline. 
	// -----------------------------------------------------------------------
	long tLocal = 0;
	tLocal = m_ctrlXnsSdkDevice.UTCToDeviceLocalTime(
		m_hDevice,												// [in] Device handle. This value is returned from CreateDevice(). 
		tEventUTC);												// [in] local time_t value


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.TimetToDate(
		tLocal,													// [in] Data in time_t format to convert.
		&Year,													// [out] Year
		&Mon,													// [out] Month
		&Day,													// [out] Day
		&Hour,													// [out] Hour
		&Min,													// [out] Minute
		&Sec);													// [out] Second


	if(nSubEvent == XEVT_PROFILE_ADD) 
		subEvent.Format(_T("PROFILE_ADD"));

	else if(nSubEvent == XEVT_PROFILE_CHANGED)
		subEvent.Format(_T("PROFILE_CHANGED"));

	else if(nSubEvent == XEVT_PROFILE_REMOVED)
		subEvent.Format(_T("PROFILE_REMOVED"));

	else if(nSubEvent == XEVT_BEING_UPDATED)
		subEvent.Format(_T("BEING_UPDATED"));

	else if(nSubEvent == XEVT_RECORD_FILTERING_START)
		subEvent.Format(_T("RECORD_FILTERING_START"));

	else if(nSubEvent == XEVT_RECORD_FILTERING_STOP)
		subEvent.Format(_T("RECORD_FILTERING_STOP"));

	else if(nSubEvent == XEVT_BATTERY_FAIL)
		subEvent.Format(_T("BATTERY_FAIL"));

	else if(nSubEvent == XEVT_NETWORK_TRAFFIC_STATUS_OVERFLOW)
		subEvent.Format(_T("NETWORK_TRAFFIC_STATUS_OVERFLOW"));

	else if(nSubEvent == XEVT_NETWORK_TRAFFIC_STATUS_RELEASE)
		subEvent.Format(_T("NETWORK_TRAFFIC_STATUS_RELEASE"));

	else if(nSubEvent == XEVT_UPGRADE_LOG)
		subEvent.Format(_T("UPGRADE_LOG"));

	else if(nSubEvent == XEVT_OVERWRITE_DECODING)
		subEvent.Format(_T("OVERWRITE_DECODING"));

	else if(nSubEvent == XEVT_RAID_MODE_ENABLE)
	{
		subEvent.Format(_T("RAID_MODE_ENABLE, RAID Array NO. : %d"), nParam1);
	}

	else if(nSubEvent == XEVT_RAID_MODE_DISABLE)
		subEvent.Format(_T("RAID_MODE_DISENABLE"));

	else if(nSubEvent == XEVT_RAID_SETUP_CHANGE)
		subEvent.Format(_T("RAID_SETUP_CHANGE"));

	else if(nSubEvent == XEVT_RAID_BUILD_CANCEL)
		subEvent.Format(_T("RAID_BUILD_CANCEL"));

	else if(nSubEvent == XEVT_RAID_BUILD_FAIL)
		subEvent.Format(_T("RAID_BUILD_FAIL"));

	else if(nSubEvent == XEVT_RAID_REBUILDING_START)
		subEvent.Format(_T("RAID_REBUILDING_START"));

	else if(nSubEvent == XEVT_RAID_REBUILDING_END)
		subEvent.Format(_T("RAID_REBUILDING_END"));

	else if(nSubEvent == XEVT_RAID_REBUILDING_FAIL)
		subEvent.Format(_T("RAID_REBUILDING_FAIL"));

	else if(nSubEvent == XEVT_RAID_DEGRADED)
		subEvent.Format(_T("RAID_DEGRADED"));

	else if(nSubEvent == XEVT_RAID_FAIL)
		subEvent.Format(_T("RAID_FAIL"));

	else if(nSubEvent == XEVT_ISCSI_CONNECTED)
		subEvent.Format(_T("ISCSI_CONNECTED"));

	else if(nSubEvent == XEVT_ISCSI_DISCONNECTED)
		subEvent.Format(_T("ISCSI_DISCONNECTED"));

	else if(nSubEvent == XEVT_RECORDING_FRAME_DROP)
		subEvent.Format(_T("RECORDING_FRAME_DROP"));

	else if(nSubEvent == XEVT_DUAL_SMPS_FAILURE)
		subEvent.Format(_T("DUAL_SMPS_FAILURE"));

	else if(nSubEvent == XEVT_DUAL_SMPS_RECOVERED)
		subEvent.Format(_T("DUAL_SMPS_RECOVERED"));

	else if(nSubEvent == XEVT_INTERNAL_HDD_CONNECTED)
	{
		subEvent.Format(_T("INTERNAL_HDD_CONNECTED, HDD NO. : %d"), nParam1);
	}

	else if(nSubEvent == XEVT_INTERNAL_HDD_DISCONNECTED)
	{
		subEvent.Format(_T("INTERNAL_HDD_DISCONNECTED, HDD NO. : %d"), nParam1);
	}

	else if(nSubEvent == XEVT_USB_HDD_CONNECTED)
		subEvent.Format(_T("USB_HDD_CONNECTED"));

	else if(nSubEvent == XEVT_USB_HDD_DISCONNECTED)
		subEvent.Format(_T("USB_HDD_DISCONNECTED"));

	else if(nSubEvent == XEVT_BACKUP_START)
		subEvent.Format(_T("BACKUP_START"));

	else if(nSubEvent == XEVT_BACKUP_END)
		subEvent.Format(_T("BACKUP_END"));

	else if(nSubEvent == XEVT_ALARM_RESET)
		subEvent.Format(_T("ALARM_RESET"));

	else if(nSubEvent == XEVT_RAID_DEVICE_ADD)
		subEvent.Format(_T("RAID_DEVICE_ADD"));

	else if(nSubEvent == XEVT_RAID_DEVICE_ADD_FAIL)
		subEvent.Format(_T("RAID_DEVICE_ADD_FAIL"));

	else if(nSubEvent == XEVT_RAID_REC_RESTRICTION)
		subEvent.Format(_T("RAID_REC_RESTRICTION"));

	str.Format(_T("[SYSTEM Event Detected] [SubEvent Type : %s] [Time(Remote) : %d-%02d-%02d  %02d:%02d:%02d] "), 
		subEvent, Year, Mon, Day, Hour, Min, Sec);

	m_ctrlSystemLog.InsertString(-1,str);
	m_ctrlSystemLog.SetCurSel(m_ctrlSystemLog.GetCount()-1);
}


void CEventDlg::OnCbnSelchangeComboModelList()
{
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
	SetCheckSunapi();
}

void CEventDlg::OnOK()
{
	/*CDialog::OnOK();*/
}

void CEventDlg::SetCheckSunapi()
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

void CEventDlg::OnBnClickedCheckSunapi()
{
	SetCheckSunapi();
}


void CEventDlg::OnVideoLossEndXnssdkdevicectrl1(long nDeviceID, long nControlID, long tEventUTC)
{
	// TODO: Add your message handler code here
		CString str;
	long Year, Mon, Day;
	long Hour, Min, Sec;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local UTC t_time to t_time. 
	// Return Value : Number of blocks of the recording data in the timeline. 
	// -----------------------------------------------------------------------
	long tLocal = 0;
	tLocal = m_ctrlXnsSdkDevice.UTCToDeviceLocalTime(
		m_hDevice,												// [in] Device handle. This value is returned from CreateDevice(). 
		tEventUTC);												// [in] local time_t value


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.TimetToDate(
		tLocal,													// [in] Data in time_t format to convert.
		&Year,													// [out] Year
		&Mon,													// [out] Month
		&Day,													// [out] Day
		&Hour,													// [out] Hour
		&Min,													// [out] Minute
		&Sec);													// [out] Second

	str.Format(_T("[Video Loss End][%d] DeviceID[%d] ControlID[%d] / [Time(Remote) : %d-%02d-%02d  %02d:%02d:%02d]"), 
		 ++m_nIndex_VideoLoss, nDeviceID, nControlID, Year, Mon, Day, Hour, Min, Sec);

	m_ctrlVideoLossLog.AddString(str);
	m_ctrlVideoLossLog.SetCurSel(m_ctrlVideoLossLog.GetCount()-1);
}
