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
// http://security.hanwhatechwin.com//
///////////////////////////////////////////////////////////////////////////////////
// SingleLiveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SingleLive.h"
#include "SingleLiveDlg.h"

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This files are installed in {$SDK path}\sample_code\include 
// You should include this files
// -----------------------------------------------------------------------
#include "XnsCommon.h"
#include "XnsDeviceInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Macro for OutputDebugString()
#define DBG_LOG(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("(%S:%d)"), __FUNCTION__, __LINE__);	\
	strMessage.AppendFormat(__VA_ARGS__);\
	OutputDebugString(strMessage);\
}while(0);

// Macro for AfxMessageBox()
#define ERROR_BOX(...) do{\
	CString strMessage = _T("");\
	strMessage.Format(__VA_ARGS__);\
	AfxMessageBox(strMessage);\
}while(0);

// Macro for EditText control (Device control)
#define WLOGD(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("[XnsSdkDevice] "));\
	strMessage.AppendFormat(__VA_ARGS__);\
	long nLen = m_ctrlEditLog.GetWindowTextLength(); \
	m_ctrlEditLog.SetFocus(); \
	m_ctrlEditLog.SetSel(nLen, nLen); \
	m_ctrlEditLog.ReplaceSel(strMessage); \
}while(0);

// Macro for EditText control (Window control)
#define WLOGW(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("[XnsSdkWindow] "));\
	strMessage.AppendFormat(__VA_ARGS__);\
	long nLen = m_ctrlEditLog.GetWindowTextLength(); \
	m_ctrlEditLog.SetFocus(); \
	m_ctrlEditLog.SetSel(nLen, nLen); \
	m_ctrlEditLog.ReplaceSel(strMessage); \
}while(0);

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


// CSingleLiveDlg dialog
// #define LOGIN_ID	"1"
// #define PASSWORD	"1"
// #define IP_ADDRESS	192,168,217,106
// #define PORT_NUM	80
// #define MODEL_NAME	"SNP-3301"

// #define LOGIN_ID	"admin"
// #define PASSWORD	"11111111"
// #define IP_ADDRESS	195,171,3,135
// #define PORT_NUM	4000
// #define MODEL_NAME	"SNP-1000A"

// SUNAPI NVR SRN-2000
#define LOGIN_ID		"admin"
#define PASSWORD		"5gksghk!"
#define IP_ADDRESS		192,168,217,32
#define PORT_NUM		4520
#define HTTP_PORT_NUM	80
#define MODEL_NAME		"Samsung Network Camera/Encoder"

CSingleLiveDlg::CSingleLiveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSingleLiveDlg::IDD, pParent)
	, m_strModelName(_T(""))
	, m_nPort(PORT_NUM)
	, m_nHttpPort(HTTP_PORT_NUM)
	, m_strId(_T(LOGIN_ID))
	, m_strPasswd(_T(PASSWORD))
	, m_hDevice(0)
	, m_hMediaSource(0)
	, m_bIsMediaPlay(0)
	, m_nChannelIndex(0)
	, m_nProfileIndex(0)
	, m_nDeviceProtocol(0)
	, m_nMediaProtocol(0)
	, m_bSupportedSnapi(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSingleLiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL, m_ctrlXnsWindow);
	DDX_Control(pDX, IDC_XNSSDKDEVICECTRL, m_ctrlXnsDevice);
	DDX_Control(pDX, IDC_COMBO_MODEL_LIST, m_ctrlModelList);
	DDX_Control(pDX, IDC_CHECK_SUNAPI, m_ctrlSunapi);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL_LIST, m_ctrlMediaProtocol);
	DDX_Control(pDX, IDC_IPADDRESS, m_ctrlIpAddress);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ctrlChannel);
	DDX_Control(pDX, IDC_COMBO_PROFILE, m_ctrlProfile);
	DDX_Control(pDX, IDC_EDIT_LOG_WIN, m_ctrlEditLog);
	
	DDX_Text(pDX, IDC_COMBO_MODEL_LIST, m_strModelName);
	DDX_Text(pDX, IDC_EDIT_ID, m_strId);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPasswd);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_nHttpPort);
		
	DDX_CBIndex(pDX, IDC_COMBO_CHANNEL, m_nChannelIndex);
	DDX_CBIndex(pDX, IDC_COMBO_PROFILE, m_nProfileIndex);
	DDX_CBIndex(pDX, IDC_COMBO_PROTOCOL_LIST, m_nMediaProtocol);
}

BEGIN_MESSAGE_MAP(CSingleLiveDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CSingleLiveDlg::OnCbnSelchangeComboModelList)
	ON_BN_CLICKED(IDC_CHECK_SUNAPI, &CSingleLiveDlg::OnBnClickedCheckSunapi)
	ON_CBN_SELCHANGE(IDC_COMBO_PROTOCOL_LIST, &CSingleLiveDlg::OnCbnSelchangeComboProtocolList)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CSingleLiveDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CSingleLiveDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CSingleLiveDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSingleLiveDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CSingleLiveDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CSingleLiveDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT_BMP, &CSingleLiveDlg::OnBnClickedButtonSnapshotBmp)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT_JPEG, &CSingleLiveDlg::OnBnClickedButtonSnapshotJpeg)
	ON_WM_DESTROY()
	ON_WM_CLOSE()

END_MESSAGE_MAP()


// CSingleLiveDlg message handlers

BOOL CSingleLiveDlg::OnInitDialog()
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

	// TODO: Add extra initialization here
	m_ctrlIpAddress.SetAddress(IP_ADDRESS);	

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Initializes the DLL files. 
	// For this, XnsActiveX library requires config.xml, device.xml, 
	// and xns.xml files and the DLL file list should be mentioned 
	// in Xns.xml file. The path of the DLL file can not exceed 512 bytes
	// in length. The XnsActiveX library searches for xns.xml using 
	// XnsSDKDevice.ocx installed in "{$SDK path}\Config" folder.
	// -----------------------------------------------------------------------
	long nRet = m_ctrlXnsDevice.Initialize();
	WLOGD(_T("Initialize() return=[%d](%s)\n"), 
		nRet, m_ctrlXnsDevice.GetErrorString(nRet));

	DBG_LOG(_T("Start\n"));

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Initializes the XnsSdkWindow control. 
	// Namely, this will specify the window handle in order to display 
	// images on the screen. 
	// -----------------------------------------------------------------------
	nRet = m_ctrlXnsWindow.Initialize(NULL, NULL);
	WLOGW(_T("Initialize() return=[%d](%s)\n"), 
		nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	
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
	long nFind = m_ctrlXnsDevice.FindModel(_T("samsung"));

	// Returns the length of the array that is created using FindVendor(), 
	// FindModel(), and FindDevice().
	long nCount = m_ctrlXnsDevice.GetFindSize(nFind);

	CString strModel;
	for (int i = 0 ; i < nCount ; i++)
	{
		// Reurns data of nIndex from the array created using FindVendor() 
		// and FindModel(). If nIndex is larger than the actual array, 
		// "" will be returned.
		strModel = m_ctrlXnsDevice.GetFindString(nFind, i);
		m_ctrlModelList.AddString(strModel);
	}
	// Closes the Find command. Releases the memory space assinged by FindXXX().
	m_ctrlXnsDevice.CloseFind(nFind);

	m_ctrlModelList.SetCurSel(0);
	int idx = m_ctrlModelList.FindStringExact(0, _T(MODEL_NAME));
	if( idx != CB_ERR )
	{
		m_ctrlModelList.SetCurSel(idx);
		m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
		if( m_strModelName == "Samsung Network Camera/Encoder" || m_strModelName == "Samsung NVR" )
		{
			m_bSupportedSnapi = TRUE;
		}
		UpdateData(FALSE);
	}
	
	m_ctrlMediaProtocol.SetCurSel(0);
	setBtnStatus(STATUS_DISCONNECTED);
	SetDeviceProtocol();
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CSingleLiveDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSingleLiveDlg::OnPaint()
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
// the minimized window.
HCURSOR CSingleLiveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSingleLiveDlg::OnCbnSelchangeComboModelList()
{
	CString strData;
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), strData);
	if( strData == "Samsung Network Camera/Encoder" || strData == "Samsung NVR" )
	{
		m_bSupportedSnapi = TRUE;
	}
	else
	{
		m_bSupportedSnapi = FALSE;
	}

	SetDeviceProtocol();
}


void CSingleLiveDlg::OnCbnSelchangeComboProtocolList()
{
	CString strData;
	m_ctrlMediaProtocol.GetLBText(m_ctrlMediaProtocol.GetCurSel(), strData);

	if( strData == "TCP" )
	{
		m_nMediaProtocol = XMEDIA_PROTOCOL_TCP;
	}
	else if( strData == "UDP" )
	{
		m_nMediaProtocol = XMEDIA_PROTOCOL_UDP;
	}
	else if( strData == "MULTICAST" )
	{
		m_nMediaProtocol = XMEDIA_PROTOCOL_MULTICAST;
	}
	else if( strData == "HTTP" )
	{
		m_nMediaProtocol = XMEDIA_PROTOCOL_TCP_HTTP;
	}
}


void CSingleLiveDlg::OnBnClickedCheckSunapi()
{
	SetDeviceProtocol();
}


void CSingleLiveDlg::OnBnClickedButtonConnect()
{
	UpdateData(TRUE);
	CString strIpAddress;
	BYTE a1, a2, a3, a4;
	m_ctrlIpAddress.GetAddress(a1, a2, a3, a4);
	strIpAddress.Format(_T("%d.%d.%d.%d"), a1, a2, a3, a4);

	// [ XNS ACTIVEX HELP ]
	if (m_hDevice != 0)
	{
		// -----------------------------------------------------------------------
		// Cancels the memory space assigned for the device information by 
		// CreateDevice(). The device should be disconnected from the application
		// before this function is called.
		// -----------------------------------------------------------------------
		m_ctrlXnsDevice.ReleaseDevice(m_hDevice);
		m_hDevice = NULL;
	}

	// -----------------------------------------------------------------------
	// Assigns memory space for saving device information. 
	// This function will return the device handle, which the application 
	// can use to control the device.
	// [in] Device ID The value should be a greater integer than 0.
	//      Minimum value: 1 , Maximum value: 3000
	// -----------------------------------------------------------------------
	
	long device_id = m_ctrlXnsDevice.CreateDeviceEx();
	m_hDevice = m_ctrlXnsDevice.GetDeviceHandle(device_id);
	//m_hDevice = m_ctrlXnsDevice.CreateDevice(1);
	if (m_hDevice == 0)
	{
		WLOGD(_T("CreateDevice() fail\n"));
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Sets the device information so that the application can connect 
	// to the device.
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.SetConnectionInfo2(
		m_hDevice,				// [in] Device handle
		_T("Samsung"),			// [in] Fixed as 'Samsung'
		m_strModelName,			// [in] Name of model to connect to. The maximum length allowed is 126-byte.
		XADDRESS_IP,			// [in] Address type
		strIpAddress,			// [in] actual address according to address type.
		m_nPort,				// [in] Port number
		m_nHttpPort,			// [in] Port number for web access	
		m_strId,				// [in] Login ID
		m_strPasswd,			// [in] Password
		m_nDeviceProtocol,		// [in] Device protocol type
		m_nMediaProtocol		// [in] Media protocol type
		);

	WLOGD(_T("ConnectInfo. IP=%s, Device port=%d, HTTP port=%d, Id=%s, Password=%s, Device protocol=%d, Media protocol=%d\n"), 
		strIpAddress, m_nPort, m_nHttpPort, m_strId, m_strPasswd, m_nDeviceProtocol, m_nMediaProtocol);

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
	long nRet = m_ctrlXnsDevice.ConnectNonBlock(
		m_hDevice,		// [in] Device handle
		TRUE,			// [in] Flag to decide where to forcibly log in or not.
		TRUE			// [in] If this value is 1, try to connect again.
		);
	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ConnectNonBlock() fail: errno=[%d](%s)\n"), 
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
		setBtnStatus(STATUS_DISCONNECTED);
	}
}


void CSingleLiveDlg::OnBnClickedButtonDisconnect()
{
	OnBnClickedButtonClose();

	// Disconnects from the device.
	m_ctrlXnsDevice.Disconnect(m_hDevice);
	WLOGD(_T("Disconnect\n"));

	m_bIsMediaPlay = false;
	m_hMediaSource = 0;

	setBtnStatus(STATUS_DISCONNECTED);
}


void CSingleLiveDlg::OnBnClickedButtonOpen()
{
	if(m_hMediaSource) 
	{
		WLOGD(_T("Media stream was already opend.. close and reopen\n"));
		m_ctrlXnsDevice.CloseMedia(m_hDevice, m_hMediaSource);
		m_hMediaSource = 0;
	}

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
	m_nControlId = m_ctrlXnsDevice.GetVideoControlID(m_hDevice, m_nChannelIndex+1, m_nProfileIndex+1);
	if( m_ctrlXnsDevice.OpenMedia(m_hDevice, m_nControlId, MEDIA_TYPE_LIVE, 0, 0, &m_hMediaSource) == ERR_SUCCESS )
	{
		WLOGW(_T("Open media...control id=[%d]\n"), m_nControlId);
		setBtnStatus(STATUS_OPEN);
		return;
	}
	
	WLOGD(_T("Invalid device..\n"));
}


void CSingleLiveDlg::OnBnClickedButtonClose()
{
	if( !m_hMediaSource ) 
	{
		WLOGD(_T("May be device is not openned\n"));
		return;
	}

	if( m_bIsMediaPlay)
	{
		// stop
		OnBnClickedButtonStop();
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Terminates transferring media stream data from the device. The media 
	// stream data will be separated by hMediaSource 
	// (i.e., phMediaSource of OpenMedia()).
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.CloseMedia(m_hDevice, m_hMediaSource);
	WLOGW(_T("Close media...\n"));
	m_hMediaSource = 0;
	m_nControlId = 0;
	setBtnStatus(STATUS_CLOSE);
}


void CSingleLiveDlg::OnBnClickedButtonPlay()
{
	if( !m_hMediaSource ) 
	{
		WLOGD(_T("Media stream was not opened\n"));
		setBtnStatus(STATUS_CLOSE);
		return;
	}

	if( m_ctrlXnsWindow.IsMedia() == FALSE )
	{
		m_bIsMediaPlay = false;
	}

	if( m_bIsMediaPlay )
	{
		WLOGW(_T("Media stream is already played\n"));
		return;
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Adds the media source handle to XnsSdkWindow. 
	// The media source handle is created by XnsSdkDevice. 
	// If the application calls XnsSdkDevice::OpenMedia(), 
	// it will receive media stream from the device and return the MediaSource 
	// handle. The application uses uses Start() to forward the mediasource 
	// handle to XnsSdkWindow so that XnsSdkWindow can obtain stream data. 
	// -----------------------------------------------------------------------
	m_ctrlXnsWindow.Start(m_hMediaSource);
	setBtnStatus(STATUS_PLAY);
	WLOGW(_T("Start receiving media stream data...\n"));
	m_bIsMediaPlay = true;
}


void CSingleLiveDlg::OnBnClickedButtonStop()
{
	if( !m_hMediaSource ) 
	{
		WLOGD(_T("Media stream was not opened\n"));
		return;
	}

	if( !m_bIsMediaPlay )
	{
		WLOGW(_T("Media stream is not played\n"));
		return;
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Stops receiving the stream data from the media source handle.  
	// -----------------------------------------------------------------------
	m_ctrlXnsWindow.Stop();
	WLOGW(_T("Stop receiving stream data...\n"));
	m_bIsMediaPlay = false;
	setBtnStatus(STATUS_STOP);
}


void CSingleLiveDlg::OnBnClickedButtonSnapshotBmp()
{
	BOOL ret =  m_ctrlXnsWindow.SaveSnapshot(_T("c:\\test.bmp"), 0);
	WLOGW(_T("Save snapshot \"c:\\test.bmp\".. res=%d\n"), ret);
}


void CSingleLiveDlg::OnBnClickedButtonSnapshotJpeg()
{
	static int a=1;
	CString filename;

	filename.Format(_T("c:\\test%d.jpg"), a);	
	BOOL ret =  m_ctrlXnsWindow.SaveSnapshot(filename, 1);

	if(ret==1)
	{
		WLOGW(_T("Save snapshot \"c:\\%s\".. res=%d\n"), filename, ret);
		a++;
	}
	else
	{
		WLOGW(_T("Save snapshot fail \"c:\\%s\".. res=%d\n"), filename, ret);
	}
}


BEGIN_EVENTSINK_MAP(CSingleLiveDlg, CDialog)
	ON_EVENT(CSingleLiveDlg, IDC_XNSSDKDEVICECTRL, 10, CSingleLiveDlg::OnDeviceStatusChangedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSingleLiveDlg, IDC_XNSSDKDEVICECTRL, 3, CSingleLiveDlg::OnConnectFailedXnssdkdevicectrl, VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the device status has changed. It occurs if the 
// application uses Connect() to connect or reconnect to the device after 
// disconnected. When reconnecting, the third argument nDeviceStatus is 
// true, all media must be reopened using ReopenAllStream().
// -----------------------------------------------------------------------
void CSingleLiveDlg::OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
	if ( nErrorCode != ERR_SUCCESS || nDeviceStatus != 1 )
	{
		setBtnStatus(STATUS_DISCONNECTED);
		return;
	}

	BOOL bIsPtzSupport = m_ctrlXnsDevice.GetControlCapability(m_hDevice, 2, XCTL_CAP_PTZ_PAN);

	WLOGD(_T("Connected: deviceID=%d, display=%s, errcode=%d, deviceStatus=%d, is_ptz_support=%d\n"),
		nDeviceID, m_ctrlXnsDevice.GetDisplayName(m_hDevice), nErrorCode, nDeviceStatus, bIsPtzSupport);

	m_ctrlChannel.ResetContent();
	int nChannelCount = m_ctrlXnsDevice.GetControlCount(m_hDevice, XCTL_CAMERA);
	CString ChannelIndex;
	for( int i = 1; i <= nChannelCount; ++i )
	{
		ChannelIndex.Format(_T("%d"), i);
		m_ctrlChannel.AddString(ChannelIndex);
	}
	m_ctrlChannel.SetCurSel(0);

	m_ctrlProfile.ResetContent();
	int nProfileCount = m_ctrlXnsDevice.GetControlCount(m_hDevice, XCTL_VIDEO) / nChannelCount;
	CString ProfileIndex;
	for( int i = 1; i <= nProfileCount; ++i )
	{
		ProfileIndex.Format(_T("%d"), i);
		m_ctrlProfile.AddString(ProfileIndex);
	}
	m_ctrlProfile.SetCurSel(0);

	setBtnStatus(STATUS_CONNECTED);
	if( nProfileCount == 0 )
		m_ctrlProfile.EnableWindow(false);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// If the application has failed in non-blocking connection using 
// ConnectNonBlock(), the OnConnectFailed event occurs. As Connect() 
// returns an immediate error message if failed, it does not trigger 
// this event. 
// -----------------------------------------------------------------------
void CSingleLiveDlg::OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode)
{
	WLOGD(_T("Disconnected: deviceID=%d, errcode=[%d](%s)\n"),
			nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode));
	setBtnStatus(STATUS_DISCONNECTED);
}

void CSingleLiveDlg::OnDestroy()
{
	if( m_hDevice )
	{
		OnBnClickedButtonStop();
		OnBnClickedButtonClose();
	
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
	}

	CDialog::OnDestroy();
}


void CSingleLiveDlg::SetDeviceProtocol()
{ 
	m_ctrlSunapi.EnableWindow(FALSE);
	m_ctrlMediaProtocol.EnableWindow(FALSE);
	m_nDeviceProtocol = 0;
	m_nMediaProtocol = 0;

	if (m_bSupportedSnapi == true) 
	{  
		m_ctrlSunapi.EnableWindow(TRUE);
		if( m_ctrlSunapi.GetCheck() )
		{
			m_nDeviceProtocol = XDEVICE_PROTOCOL_SUNAPI;
			m_ctrlMediaProtocol.EnableWindow(TRUE);
			CString strData;
			m_ctrlMediaProtocol.GetLBText(m_ctrlMediaProtocol.GetCurSel(), strData);

			if( strData == "TCP" )
			{
				m_nMediaProtocol = XMEDIA_PROTOCOL_TCP;
			}
			else if( strData == "UDP" )
			{
				m_nMediaProtocol = XMEDIA_PROTOCOL_UDP;
			}
			else if( strData == "MULTICAST" )
			{
				m_nMediaProtocol = XMEDIA_PROTOCOL_MULTICAST;
			}
			else if( strData == "HTTP" )
			{
				m_nMediaProtocol = XMEDIA_PROTOCOL_TCP_HTTP;
			}
		}
	}
}


// Control button enable/disable
void CSingleLiveDlg::setBtnStatus(BUTTON_STATUS nStatus)
{
	bool connect = false, disconnect = false, close = false, open = false, play = false, stop = false;
	switch(nStatus)
	{
	case STATUS_CONNECTED:
		disconnect = true;
		open = true;
		break;
	case STATUS_DISCONNECTED:
		connect = true;
		break;
	case STATUS_OPEN:
		disconnect = true;
		close = true;
		play = true;
		break;
	case STATUS_CLOSE:
		disconnect = true;
		open = true;
		break;
	case STATUS_PLAY:
		disconnect = true;
		close = true;
		stop = true;
		break;
	case STATUS_STOP:
		disconnect = true;
		close = true;
		play = true;
		break;
	}

	// Connection Group
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(connect);
	GetDlgItem(IDC_COMBO_MODEL_LIST)->EnableWindow(connect);
	GetDlgItem(IDC_CHECK_SUNAPI)->EnableWindow(connect);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_PW)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_PORT2)->EnableWindow(connect);
	GetDlgItem(IDC_COMBO_PROTOCOL_LIST)->EnableWindow(connect);
	GetDlgItem(IDC_COMBO_CHANNEL)->EnableWindow(disconnect);
	GetDlgItem(IDC_COMBO_PROFILE)->EnableWindow(disconnect);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(disconnect);
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(open);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(close);
	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(play);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(stop);
}

void CSingleLiveDlg::OnOK()
{
	//CDialog::OnOK();
}