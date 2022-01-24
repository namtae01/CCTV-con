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

#include "stdafx.h"
#include "LocalRecording.h"
#include "LocalRecordingDlg.h"

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


// CLocalRecordingDlg dialog

// Network Camera/Encoder
#define MODEL_NAME	"Samsung Network Camera/Encoder"
#define IP_ADDRESS	192,168,25,110
#define PORT_NUM	4520
#define HTTP_PORT_NUM 80
#define LOGIN_ID	"admin"
#define PASSWORD	"5tkatjd/"

#define PLAY_RECORDING "Play (REC File)"
#define STOP_RECORDING "Pause (REC File)"

CLocalRecordingDlg::CLocalRecordingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLocalRecordingDlg::IDD, pParent)
	, m_strModelName(_T(""))
	, m_strPassword(_T(PASSWORD))
	, m_strId(_T(LOGIN_ID))
	, m_lnPort(PORT_NUM)
	, m_lnHttpPort(HTTP_PORT_NUM)
	, m_hDevice(0)
	, m_nControlId(0)
	, m_hMediaSource(0)
	, m_bCheckConnect(FALSE)
	, m_bPlay(FALSE)
	, m_bDestroy(FALSE)
	, m_bRecording(FALSE)
	, m_bRecType(0)
	, m_bPlayRecord(FALSE)
	, m_bRec2Avi(FALSE)
	, m_hFileHandle(0)
	, m_nDeviceProtocol(XDEVICE_PROTOCOL_UNKNOWN)
	, m_nMediaProtocol(0)
	, m_nChannelIndex(0)
	, m_nProfileIndex()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLocalRecordingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//////////////////////////////////////////////////////////////////////////
	// Active X Control 
	DDX_Control(pDX, IDC_XNSSDKDEVICECTRL, m_ctrlXnsSdkDevice);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL, m_ctrlXnsSdkWindow);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL_RECORDING, m_ctrlXnsSdkWindow_Recording);

	//////////////////////////////////////////////////////////////////////////
	// Control Member 
	DDX_Control(pDX, IDC_COMBO_MODEL_LIST, m_ctrlModelList);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ctrlIpAddress);
	DDX_Control(pDX, IDC_EDIT_PORT, m_ctrlPort);
	DDX_Control(pDX, IDC_EDIT_PORT2, m_ctrlHttpPort);
	DDX_Control(pDX, IDC_EDIT_USER_ID, m_ctrlUserID);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ctrlPassword);
	DDX_Control(pDX, IDC_LIST_STATUS_MESSAGE, m_ctrlStatusList);


	//////////////////////////////////////////////////////////////////////////
	// Text Control
	DDX_Text(pDX, IDC_EDIT_USER_ID, m_strId);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_PORT, m_lnPort);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_lnHttpPort);
	DDX_Control(pDX, IDC_CHECK_SUNAPI, m_ctrlSunapi);
	DDX_CBString(pDX, IDC_COMBO_MODEL_LIST, m_strModelName);
}

BEGIN_MESSAGE_MAP(CLocalRecordingDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CLocalRecordingDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CLocalRecordingDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CLocalRecordingDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CLocalRecordingDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_START_RECORDING, &CLocalRecordingDlg::OnBnClickedButtonStartRecording)
	ON_BN_CLICKED(IDC_BUTTON_STOP_RECORDING, &CLocalRecordingDlg::OnBnClickedButtonStopRecording)
	ON_BN_CLICKED(IDC_RADIO_SEC, &CLocalRecordingDlg::OnBnClickedRadioSec)
	ON_BN_CLICKED(IDC_RADIO_REC, &CLocalRecordingDlg::OnBnClickedRadioRec)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_RECORDING, &CLocalRecordingDlg::OnBnClickedButtonPlayRecording)
	ON_BN_CLICKED(IDC_RADIO_AVI, &CLocalRecordingDlg::OnBnClickedRadioAvi)
	ON_BN_CLICKED(IDC_BUTTON_REC2AVI, &CLocalRecordingDlg::OnBnClickedButtonRec2avi)

	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CLocalRecordingDlg::OnCbnSelchangeComboModelList)
	ON_BN_CLICKED(IDC_CHECK_SUNAPI, &CLocalRecordingDlg::OnBnClickedCheckSunapi)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CLocalRecordingDlg, CDialog)
	ON_EVENT(CLocalRecordingDlg, IDC_XNSSDKDEVICECTRL, 10, CLocalRecordingDlg::OnDeviceStatusChangedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CLocalRecordingDlg, IDC_XNSSDKDEVICECTRL, 3, CLocalRecordingDlg::OnConnectFailedXnssdkdevicectrl, VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

// CLocalRecordingDlg message handlers

BOOL CLocalRecordingDlg::OnInitDialog()
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

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Initializes the DLL files. 
	// For this, XnsActiveX library requires config.xml, device.xml, 
	// and xns.xml files and the DLL file list should be mentioned 
	// in Xns.xml file. The path of the DLL file can not exceed 512 bytes
	// in length. The XnsActiveX library searches for xns.xml using 
	// XnsSDKDevice.ocx installed in "{$SDK path}\Config" folder.
	// -----------------------------------------------------------------------

	OnInitXnsSdk();
	OnInitModelList();
	OnSetDialog();
	setBtnStatus(STATUS_DISCONNECTED);
	
	SetLocalPlayControlStatus(FALSE);
	// ----------------------------------------------------------------------


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLocalRecordingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLocalRecordingDlg::OnPaint()
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
HCURSOR CLocalRecordingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// for ActiveX SDK Device control and Window Control initialize function.
// -----------------------------------------------------------------------
void CLocalRecordingDlg::OnInitXnsSdk(void)
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

	WLOGW(_T("Initialize() return=[%d](%s)\n"), 
		nRet, m_ctrlXnsSdkDevice.GetErrorString(nRet));

	DBG_LOG(_T("Start\n"));


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Initializes the XnsSdkWindow control. 
	// Namely, this will specify the window handle in order to display 
	// images on the screen. 
	// -----------------------------------------------------------------------
	nRet = m_ctrlXnsSdkWindow.Initialize(NULL, NULL);
	nRet = m_ctrlXnsSdkWindow_Recording.Initialize(NULL, NULL);

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
void CLocalRecordingDlg::OnInitModelList(void)
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

	m_ctrlIpAddress.SetAddress(IP_ADDRESS);

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
void CLocalRecordingDlg::OnSetDialog(void)
{
	((CButton*)GetDlgItem(IDC_RADIO_SEC))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_REC))->SetCheck(FALSE);
}

void CLocalRecordingDlg::OnDestroy()
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
				m_hDevice,			// [in] Device handle. This value is returned from CreateDevice(). 
				m_hMediaSource);	// [in] Media stream ID.		
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
// @ MFC Window Button Control Functions.
// for Device Connect Function.
// -----------------------------------------------------------------------
void CLocalRecordingDlg::OnBnClickedButtonConnect()
{
	CString strModel;									// Model Name 
	CString strIpAddress;                               // IP Address  
	BYTE address[ADDRESS_MAX];                          // Byte Value in IP Address Box 
	long nIndex = m_ctrlModelList.GetCurSel();          // ComBox Box : Device Index Value

	UpdateData(TRUE);


	m_ctrlModelList.GetLBText(nIndex, strModel);		// Get Model Name 
	m_ctrlIpAddress.GetAddress(address[0], address[1], address[2], address[3]);
	strIpAddress.Format(_T("%d.%d.%d.%d"), address[0], address[1], address[2], address[3]);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Sets the device information so that the application can connect 
	// to the device.
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.SetConnectionInfo2(
		m_hDevice,										// [in] Device handle
		_T("Samsung"),                                  // [in] Fixed as 'Samsung'
		m_strModelName,                                 // [in] Name of model to connect to.
		XADDRESS_IP,                                    // [in] Address type (Define Value : XADDRESS_IP = 1)
		strIpAddress,                                   // [in] Actual address according to nAddressType.
		m_lnPort,                                       // [in] Port Number
		m_lnHttpPort,                                              // [in] Port number for web access
		m_strId,                                        // [in] User Login ID
		m_strPassword,									// [in] User Login Password
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
void CLocalRecordingDlg::OnBnClickedButtonDisconnect()
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
		m_hDevice,			// [in] Device handle. This value is returned from CreateDevice(). 
		m_hMediaSource);	// [in] Media stream ID.

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// This event occurs if the device status has changed. 
	// It occurs if the application uses Connect() to connect or reconnect 
	// to the device after disconnected.
	// -----------------------------------------------------------------------
	m_ctrlXnsSdkDevice.Disconnect(m_hDevice);

	WLOGD(_T("Disconnect\n"));

	m_hMediaSource = 0;		// Media Source Initialize.
	m_bPlay = FALSE;
	setBtnStatus(STATUS_DISCONNECTED);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Media Play Function.
// -----------------------------------------------------------------------
void CLocalRecordingDlg::OnBnClickedButtonPlay()
{
	long nCtrlID = 1;                                                     

	if( m_bPlay )
	{
		WLOGW(_T("Media stream is already played\n"));
		return;
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
			setBtnStatus(STATUS_OPEN);
			return;
		}
	}
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Media Stop Function.
// -----------------------------------------------------------------------
void CLocalRecordingDlg::OnBnClickedButtonStop()
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
	setBtnStatus(STATUS_CLOSE);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event occurs if the device status has changed. It occurs if the 
// application uses Connect() to connect or reconnect to the device after 
// disconnected. When reconnecting, the third argument nDeviceStatus is 
// true, all media must be reopened using ReopenAllStream().
// -----------------------------------------------------------------------
void CLocalRecordingDlg::OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
	if ((nErrorCode != ERR_SUCCESS) || (nDeviceStatus != 1) || (m_bDestroy == TRUE))
	{
		setBtnStatus(STATUS_DISCONNECTED);
		return;
	}

	WLOGD(_T("Connected: deviceID=%d, errcode=%d, deviceStatus=%d\n"),
		nDeviceID, nErrorCode, nDeviceStatus);
	m_bCheckConnect = TRUE;
	setBtnStatus(STATUS_CONNECTED);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// If the application has failed in non-blocking connection using 
// ConnectNonBlock(), the OnConnectFailed event occurs. As Connect() 
// returns an immediate error message if failed, it does not trigger 
// this event. 
// -----------------------------------------------------------------------
void CLocalRecordingDlg::OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode)
{
	WLOGD(_T("Disconnected: deviceID=%d, errcode=[%d](%s)\n"),
		nDeviceID, nErrorCode, m_ctrlXnsSdkDevice.GetErrorString(nErrorCode));
	setBtnStatus(STATUS_DISCONNECTED);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Local recording start Function.
// -----------------------------------------------------------------------
void CLocalRecordingDlg::OnBnClickedButtonStartRecording()
{
	CString strFilePath;                                                 // File path for file save
	long nErrCode;                                                       // Record Function Return type

	if ((m_bCheckConnect == TRUE) && (m_bPlay == TRUE))					 // Function and Devece Status Success 
	{
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
					strFilePath.Format(_T("c:\\LiveVideo"));

					// [ XNS ACTIVEX HELP ]
					// -----------------------------------------------------------------------
					// Starts recording the stream data in the local PC.
					// -----------------------------------------------------------------------
					if (m_bRecType == 0)
						nErrCode = m_ctrlXnsSdkDevice.StartLocalRecording(m_hDevice, i+2, strFilePath, SEC_WRITER);
					else if (m_bRecType == 1)
						nErrCode = m_ctrlXnsSdkDevice.StartLocalRecording(m_hDevice, i+2, strFilePath, REC_WRITER);
					else if (m_bRecType == 2)
						nErrCode = m_ctrlXnsSdkDevice.StartAviLocalRecording(m_hDevice, i+2, strFilePath);

					WLOGD(_T("Record On !"));
					setBtnStatus(STATUS_RECORDING);
					if (m_bPlayRecord)
					{
						m_ctrlXnsSdkWindow_Recording.Stop();
						m_bPlayRecord = FALSE;
						GetDlgItem(IDC_BUTTON_PLAY_RECORDING)->SetWindowText(_T(PLAY_RECORDING));
					}
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
				if (m_ctrlXnsSdkDevice.GetControlCapability(m_hDevice, i+3, XCTL_CAP_LIVE) &&
					m_ctrlXnsSdkDevice.GetControlStatus(m_hDevice, i+3, XCAMERA_STATUS))
				{
					strFilePath.Format(_T("c:\\LiveVideo"));

					// [ XNS ACTIVEX HELP ]
					// -----------------------------------------------------------------------
					// Starts recording the stream data in the local PC.
					// -----------------------------------------------------------------------
					if (m_bRecType == 0)
						nErrCode = m_ctrlXnsSdkDevice.StartLocalRecording(m_hDevice, i+3, strFilePath, SEC_WRITER);
					else if (m_bRecType == 1)
						nErrCode = m_ctrlXnsSdkDevice.StartLocalRecording(m_hDevice, i+3, strFilePath, REC_WRITER);
					else if (m_bRecType == 2)
						nErrCode = m_ctrlXnsSdkDevice.StartAviLocalRecording(m_hDevice, i+3, strFilePath);

					WLOGD(_T("Record On !"));
					setBtnStatus(STATUS_RECORDING);
					if (m_bPlayRecord)
					{
						m_ctrlXnsSdkWindow_Recording.Stop();
						m_bPlayRecord = FALSE;
						GetDlgItem(IDC_BUTTON_PLAY_RECORDING)->SetWindowText(_T(PLAY_RECORDING));
					}
					
					return;
				}
			}
		}
	}
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Local recording stop Function.
// -----------------------------------------------------------------------
void CLocalRecordingDlg::OnBnClickedButtonStopRecording()
{
	long nErrCode;                                              // Record Function Return type

	if ((m_bCheckConnect == TRUE) && (m_bPlay == TRUE))         // Function and Devece Status Success 
	{

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
					// [ XNS ACTIVEX HELP ]
					// -----------------------------------------------------------------------
					// Stops recording in the local PC.
					// -----------------------------------------------------------------------
					if( m_bRecType == 2)
						nErrCode = m_ctrlXnsSdkDevice.StopAviLocalRecording(m_hDevice, i+2);
					else
						nErrCode = m_ctrlXnsSdkDevice.StopLocalRecording(m_hDevice, i+2);

					WLOGD(_T("Record Off !"));	
					setBtnStatus(STATUS_STOP_RECORDING);
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
				// Displays video in real time  and  Gets the status of the control module.
				if (m_ctrlXnsSdkDevice.GetControlCapability(m_hDevice, i+3, XCTL_CAP_LIVE) &&
					m_ctrlXnsSdkDevice.GetControlStatus(m_hDevice, i+3, XCAMERA_STATUS))
				{
					// [ XNS ACTIVEX HELP ]
					// -----------------------------------------------------------------------
					// Stops recording in the local PC.
					// -----------------------------------------------------------------------
					if( m_bRecType == 2)
						nErrCode = m_ctrlXnsSdkDevice.StopAviLocalRecording(m_hDevice, i+3);
					else
						nErrCode = m_ctrlXnsSdkDevice.StopLocalRecording(m_hDevice, i+3);

					WLOGD(_T("Record Off !"));
					setBtnStatus(STATUS_STOP_RECORDING);
					return;
				}
			}
		}
	}
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Radio Button Control Functions.
// -----------------------------------------------------------------------
void CLocalRecordingDlg::OnBnClickedRadioSec()
{
	m_bRecType = 0;
	WLOGD(_T("Record Type : SEC !"));
	SetLocalPlayControlStatus(FALSE);
}


void CLocalRecordingDlg::OnBnClickedRadioRec()
{
	m_bRecType = 1;
	WLOGD(_T("Record Type : REC !"));
	SetLocalPlayControlStatus(TRUE);
}


void CLocalRecordingDlg::OnBnClickedRadioAvi()
{
	m_bRecType = 2;
	WLOGD(_T("Record Type : AVI !"));
	SetLocalPlayControlStatus(FALSE);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Local recording stop Function.
// -----------------------------------------------------------------------
void CLocalRecordingDlg::OnBnClickedButtonPlayRecording()
{
	CString strFilePath;    // File path for file save
	strFilePath.Format(_T("c:\\LiveVideo"));

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Creates the file reader. The file reader is used to play backup or recoding data.
	// -----------------------------------------------------------------------			
	long m_hFileReader = m_ctrlXnsSdkDevice.CreateFileReader(strFilePath);
	
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Gets the handle of the media source from the file handle. 
	// This value is used to display images using XnsWindow.
	// -----------------------------------------------------------------------
	m_hMediaSource = m_ctrlXnsSdkDevice.GetMediaSource(m_hFileReader);

	if (m_bPlayRecord == FALSE)
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Plays the backup file at a specified speed.
		// -----------------------------------------------------------------------
		long nErrorCode = m_ctrlXnsSdkWindow_Recording.Start(m_hMediaSource);	
		nErrorCode = m_ctrlXnsSdkDevice.PlayReader(
			m_hFileReader,		// [in] Handle of the file to play. This value can be obtained using CreateFileReader().
			SPEED_1);			// [in] Play speed.

		m_bPlayRecord = TRUE;
		GetDlgItem(IDC_BUTTON_PLAY_RECORDING)->SetWindowText(_T(STOP_RECORDING));
	}
	else
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Stops playing the backup file temporarily. 
		// Can resume playing using PlayReader().
		// -----------------------------------------------------------------------
		long nErrCode = m_ctrlXnsSdkDevice.PauseReader(m_hFileReader);
		m_ctrlXnsSdkWindow_Recording.Stop();
		m_bPlayRecord = FALSE;
		GetDlgItem(IDC_BUTTON_PLAY_RECORDING)->SetWindowText(_T(PLAY_RECORDING));
	}
}

void CLocalRecordingDlg::OnBnClickedButtonRec2avi()
{
	if (m_bRec2Avi == FALSE)
	{
		m_hFileHandle = m_ctrlXnsSdkDevice.ConvertRec2Avi(_T("c:\\LiveVideo"));
		m_bRec2Avi = TRUE;
		GetDlgItem(IDC_BUTTON_REC2AVI)->SetWindowText(_T("Stop Convert"));
	}
	else
	{
		m_ctrlXnsSdkDevice.StopRec2Avi(m_hFileHandle);
		m_bRec2Avi = FALSE;
		GetDlgItem(IDC_BUTTON_REC2AVI)->SetWindowText(_T("Convert REC to AVI"));		
	}
}


void CLocalRecordingDlg::OnCbnSelchangeComboModelList()
{
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
	SetCheckSunapi();	
}


void CLocalRecordingDlg::setBtnStatus(BUTTON_STATUS nStatus)
{
	bool connection = false, disconnection = false, close = false, open = false;
	bool recording = false, stop_recording = false;
	switch(nStatus)
	{
	case STATUS_CONNECTED:
		disconnection = true;
		open = true;
		break;
	case STATUS_DISCONNECTED:
		connection = true;
		break;
	case STATUS_OPEN:
		disconnection = true;
		close = true;
		recording = true;
		break;
	case STATUS_CLOSE:
		disconnection = true;
		open = true;
		break;
	case STATUS_RECORDING:
		stop_recording = true;
		break;
	case STATUS_STOP_RECORDING:
		recording = true;
		disconnection = true;
		close = true;
	}

	// Connection Group
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(connection);
	GetDlgItem(IDC_COMBO_MODEL_LIST)->EnableWindow(connection);
	GetDlgItem(IDC_IPADDRESS1)->EnableWindow(connection);
	GetDlgItem(IDC_EDIT_USER_ID)->EnableWindow(connection);
	GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(connection);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(connection);
	GetDlgItem(IDC_EDIT_PORT2)->EnableWindow(connection);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(connection);

	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(disconnection);
	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(open);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(close);

	GetDlgItem(IDC_BUTTON_START_RECORDING)->EnableWindow(recording);
	GetDlgItem(IDC_BUTTON_STOP_RECORDING)->EnableWindow(stop_recording);
	
	SetCheckSunapi();
}

void CLocalRecordingDlg::SetLocalPlayControlStatus(bool bSelectedRec)
{
	GetDlgItem(IDC_BUTTON_PLAY_RECORDING)->EnableWindow(bSelectedRec);
	GetDlgItem(IDC_BUTTON_REC2AVI)->EnableWindow(bSelectedRec);
}

void CLocalRecordingDlg::OnOK()
{
	//CDialog::OnOK();
}


void CLocalRecordingDlg::SetCheckSunapi()
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

void CLocalRecordingDlg::OnBnClickedCheckSunapi()
{
	SetCheckSunapi();
}
