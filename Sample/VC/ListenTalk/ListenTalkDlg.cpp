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
// ListenTalkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListenTalk.h"
#include "ListenTalkDlg.h"


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



// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// Audio Codec PCM information
// 1. Bits per sample, sample per seconds
//    - 16, 8000
//      * IMA ADPCM (SNC-570, SND-560/460V, SNP-370/3350)
//      * G726 504X (SNC-550, SNS-100/400, SNP-1000A/3300A
//      * G726 SNR (SNR-6400/3200)
//      * G723 SVR
//      * G711 IPCAM
//      * G711U HISILICON
//    - 16, 16000
//      * G723
//      * DVI4 HISILICON (SRD-1640/840/440/442)
//    - another
//      * 8, 8000
// 2. Notify size
//    - 4096
//      * G726 504X
//      * G726 SNR
//    - 4000
//      * G711 IPCAM
//    - 6400
//      * G723
//    - 3200
//      * G711U HISILICON
//      * DVI4 HISILICON
// -----------------------------------------------------------------------
// IPCAM PCM INFO : SND-7080
// #define LOGIN_ID		"admin"
// #define PASSWORD		"4321"
// #define IP_ADDRESS		192,168,1,101
// #define PORT_NUM		4520
// #define MODEL_NAME		"SND-7080"
// #define	BIT_PER_SAMPLE	16
// #define	SAMPLE_PER_SEC	8000
// #define	CHANNEL_NUM		1
// #define BUFF_NUM		200
// #define NOTIFY_SIZE		4000
// #define TIME_OFFSET		250

// DVR PCM INFO : SRD-167X
#define LOGIN_ID		"admin"
#define PASSWORD		"5tkatjd!!"
#define IP_ADDRESS		192,168,51,114
#define PORT_NUM		4520
#define HTTP_PORT_NUM   80
#define MODEL_NAME		"Samsung Network Camera/Encoder"
#define	BIT_PER_SAMPLE	16
#define	SAMPLE_PER_SEC	8000
#define	CHANNEL_NUM		1
#define BUFF_NUM		200
#define NOTIFY_SIZE		4000
#define TIME_OFFSET		200

//SNP-1000A
// #define LOGIN_ID		"admin"
// #define PASSWORD		"4321"
// #define IP_ADDRESS		192,168,1,100
// #define PORT_NUM		4000
// #define MODEL_NAME		"SNP-1000A"
// #define	BIT_PER_SAMPLE	16
// #define	SAMPLE_PER_SEC	8000
// #define	CHANNEL_NUM		1
// #define BUFF_NUM		200
// #define NOTIFY_SIZE		8192
// #define TIME_OFFSET		400

// SNP-5200
// #define LOGIN_ID		"admin"
// #define PASSWORD		"4321"
// #define IP_ADDRESS		192,168,1,110
// #define PORT_NUM		60001
// #define MODEL_NAME		"Samsung Network Camera/Encoder"
// #define	BIT_PER_SAMPLE	16
// #define	SAMPLE_PER_SEC	8000
// #define	CHANNEL_NUM		1
// #define BUFF_NUM		200
// #define NOTIFY_SIZE		4000
// #define TIME_OFFSET		250


// SNC-C7478
// #define LOGIN_ID		"root"
// #define PASSWORD		"4321"
// #define IP_ADDRESS		192,168,1,110
// #define PORT_NUM		60001
// #define MODEL_NAME		"SNC-C7478"
// #define	BIT_PER_SAMPLE	16
// #define	SAMPLE_PER_SEC	8000
// #define	CHANNEL_NUM		1
// #define BUFF_NUM		200
// #define NOTIFY_SIZE		4000
// #define TIME_OFFSET		250




// CListenTalkDlg dialog
CListenTalkDlg::CListenTalkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListenTalkDlg::IDD, pParent)
	, m_strModelName(_T(""))
	, m_nPort(PORT_NUM)
	, m_nHttpPort(HTTP_PORT_NUM)
	, m_strId(_T(LOGIN_ID))
	, m_strPasswd(_T(PASSWORD))
	, m_hDevice(0)
	, m_hMediaSource(0)
	, m_bListen(0)
	, m_bTalk(0)
	, m_nSendBytes(NOTIFY_SIZE)
	, m_nBps(0)
	, m_nChannel(0)
	, m_nSps(0)
	, m_bSendAudio(0)
	, m_nDeviceProtocol(XDEVICE_PROTOCOL_UNKNOWN)
	, m_nMediaProtocol(0)
	, m_nChannelIndex(0)
	, m_nProfileIndex(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	CString strMessage = _T("");
	InitializeCriticalSection(&m_hCritSect);
}

void CListenTalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL, m_ctrlXnsWindow);
	DDX_Control(pDX, IDC_XNSSDKDEVICECTRL, m_ctrlXnsDevice);
	DDX_Control(pDX, IDC_COMBO_MODEL_LIST, m_ctrlModelList);
	DDX_Control(pDX, IDC_IPADDRESS, m_ctrlIpAddress);
	DDX_Text(pDX, IDC_COMBO_MODEL_LIST, m_strModelName);
	DDX_Text(pDX, IDC_EDIT_ID, m_strId);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPasswd);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_nHttpPort);
	DDX_Control(pDX, IDC_EDIT_LOG_WIN, m_ctrlEditLog);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ctrlChannel);
	DDX_Control(pDX, IDC_COMBO_BIT_PER_SAMPLE, m_ctrlBps);
	DDX_Control(pDX, IDC_COMBO_SAMPLE_PER_SECOND, m_ctrlSps);
	DDX_Text(pDX, IDC_EDIT_SEND_BYTES, m_nSendBytes);
	DDX_CBIndex(pDX, IDC_COMBO_BIT_PER_SAMPLE, m_nBps);
	DDX_CBIndex(pDX, IDC_COMBO_CHANNEL, m_nChannel);
	DDX_CBIndex(pDX, IDC_COMBO_SAMPLE_PER_SECOND, m_nSps);
	DDX_Control(pDX, IDC_CHECK_SUNAPI, m_ctrlSunapi);
}

BEGIN_MESSAGE_MAP(CListenTalkDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CListenTalkDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CListenTalkDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CListenTalkDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CListenTalkDlg::OnBnClickedButtonStop)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_LISTEN, &CListenTalkDlg::OnBnClickedCheckListen)
	ON_BN_CLICKED(IDC_CHECK_TALK, &CListenTalkDlg::OnBnClickedCheckTalk)
	ON_BN_CLICKED(IDC_BUTTON_SEND_AUDIO, &CListenTalkDlg::OnBnClickedButtonSendAudio)
	ON_BN_CLICKED(IDC_BUTTON_STOP_AUDIO, &CListenTalkDlg::OnBnClickedButtonStopAudio)
	ON_BN_CLICKED(IDC_BUTTON_SEND_AUDIO2, &CListenTalkDlg::OnBnClickedButtonSendAudio2)
	ON_BN_CLICKED(IDC_BUTTON_STOP_AUDIO2, &CListenTalkDlg::OnBnClickedButtonStopAudio2)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CListenTalkDlg::OnCbnSelchangeComboModelList)
	ON_BN_CLICKED(IDC_CHECK_SUNAPI, &CListenTalkDlg::OnBnClickedCheckSunapi)
END_MESSAGE_MAP()


// CListenTalkDlg message handlers

BOOL CListenTalkDlg::OnInitDialog()
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

	CString strTmp = _T("");
	int index;
	m_ctrlChannel.AddString(_T("1"));
	m_ctrlChannel.AddString(_T("2"));
	m_nChannel = CHANNEL_NUM;
	index = m_ctrlChannel.FindStringExact(0, strTmp);
	if(index==CB_ERR) 
		index = 0;
	m_ctrlChannel.SetCurSel(index);
	m_nChannel = index;

	m_ctrlBps.AddString(_T("8"));
	m_ctrlBps.AddString(_T("16"));
	m_ctrlBps.AddString(_T("32"));
	strTmp.Format(_T("%d"), BIT_PER_SAMPLE);
	index = m_ctrlBps.FindStringExact(0, strTmp);
	if(index==CB_ERR) 
		index = 0;
	m_ctrlBps.SetCurSel(index);
	m_nBps = index;

	m_ctrlSps.AddString(_T("8000"));
	m_ctrlSps.AddString(_T("16000"));
	m_ctrlSps.AddString(_T("32000"));
	strTmp.Format(_T("%d"), SAMPLE_PER_SEC);
	index = m_ctrlSps.FindStringExact(0, strTmp);
	if(index==CB_ERR) 
		index = 0;
	m_ctrlSps.SetCurSel(index);
	m_nSps = index;

	UpdateData(FALSE);



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
	// Assigns memory space for saving device information. 
	// This function will return the device handle, which the application 
	// can use to control the device.
	// [in] Device ID The value should be a greater integer than 0.
	//      Minimum value: 1 , Maximum value: 3000
	// -----------------------------------------------------------------------
	long device_id = m_ctrlXnsDevice.CreateDeviceEx();
	m_hDevice = m_ctrlXnsDevice.GetDeviceHandle(device_id);

	if (m_hDevice == 0)
	{
		WLOGD(_T("CreateDevice() fail\n"));
	}
	

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
	if(idx != CB_ERR) {
		m_ctrlModelList.SetCurSel(idx);
		m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
		UpdateData(FALSE);
	}

	setBtnStatus(SL_STATUS_DISCONNECTED);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListenTalkDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListenTalkDlg::OnPaint()
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
HCURSOR CListenTalkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CListenTalkDlg::OnBnClickedButtonConnect()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strIpAddress;
	BYTE a1, a2, a3, a4;
	m_ctrlIpAddress.GetAddress(a1, a2, a3, a4);
	strIpAddress.Format(_T("%d.%d.%d.%d"), a1, a2, a3, a4);

	if(m_strModelName != "Samsung Network Camera/Encoder")
	{
		m_nDeviceProtocol = XDEVICE_PROTOCOL_UNKNOWN;
		m_nMediaProtocol = 0;
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Sets the device information so that the application can connect 
	// to the device.
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.SetConnectionInfo2(
		m_hDevice,					// [in] Device handle
		_T("Samsung"),				// [in] Fixed as 'Samsung'
		m_strModelName,				// [in] Name of model to connect to. The maximum length allowed is 126-byte.
		XADDRESS_IP,				// [in] Address type
		strIpAddress,				// [in] actual address according to address type.
		m_nPort,					// [in] Port number
		m_nHttpPort,				// [in] Port number for web access	
		m_strId,					// [in] Login ID
		m_strPasswd,				// [in] Password
		m_nDeviceProtocol,
		m_nMediaProtocol
		);

	WLOGD(_T("Connect. ip=%s, port=%d, http port=%d, id=%s, password=%s\n"), 
		strIpAddress, m_nPort, m_nHttpPort, m_strId, m_strPasswd);

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
	}
}

void CListenTalkDlg::OnBnClickedButtonDisconnect()
{
	// TODO: Add your control notification handler code here

	OnBnClickedButtonStop();

	// Disconnects from the device.
	m_ctrlXnsDevice.Disconnect(m_hDevice);
	WLOGD(_T("Disconnect\n"));

	setBtnStatus(SL_STATUS_DISCONNECTED);

}



BEGIN_EVENTSINK_MAP(CListenTalkDlg, CDialog)
	ON_EVENT(CListenTalkDlg, IDC_XNSSDKDEVICECTRL, 10, CListenTalkDlg::OnDeviceStatusChangedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CListenTalkDlg, IDC_XNSSDKDEVICECTRL, 3, CListenTalkDlg::OnConnectFailedXnssdkdevicectrl, VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the device status has changed. It occurs if the 
// application uses Connect() to connect or reconnect to the device after 
// disconnected. When reconnecting, the third argument nDeviceStatus is 
// true, all media must be reopened using ReopenAllStream().
// -----------------------------------------------------------------------
void CListenTalkDlg::OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
	// TODO: Add your message handler code here
	if (nErrorCode != ERR_SUCCESS || nDeviceStatus != 1)
	{
		return;
	}

	WLOGD(_T("Connected: deviceID=%d, errcode=%d, deviceStatus=%d\n"),
		nDeviceID, nErrorCode, nDeviceStatus);
	setBtnStatus(SL_STATUS_CONNECTED);
	
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// If the application has failed in non-blocking connection using 
// ConnectNonBlock(), the OnConnectFailed event occurs. As Connect() 
// returns an immediate error message if failed, it does not trigger 
// this event. 
// -----------------------------------------------------------------------
void CListenTalkDlg::OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode)
{
	// TODO: Add your message handler code here
	WLOGD(_T("Disconnected: deviceID=%d, errcode=[%d](%s)\n"),
			nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode));
	setBtnStatus(SL_STATUS_DISCONNECTED);
}



void CListenTalkDlg::OnDestroy()
{
	if( m_hDevice )
	{
		OnBnClickedButtonStop();
		

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


void CListenTalkDlg::OnBnClickedButtonPlay()
{
	// TODO: Add your control notification handler code here
	if(m_hMediaSource) 
	{
		WLOGD(_T("Media stream was already opend\n"));
		return;
	}

	UpdateData(TRUE);
	WLOGD(_T("Open media stream::channel(%d), profile(%d)\n"), m_nChannelIndex+1, m_nProfileIndex+1);
	
	m_nControlId = m_ctrlXnsDevice.GetVideoControlID(m_hDevice, m_nChannelIndex+1, m_nProfileIndex+1);
	if( m_ctrlXnsDevice.OpenMedia(m_hDevice, m_nControlId, MEDIA_TYPE_LIVE, 0, 0, &m_hMediaSource) == ERR_SUCCESS )
	{
		WLOGW(_T("Open media...control id=[%d]\n"), m_nControlId);
		m_ctrlXnsWindow.Start(m_hMediaSource);
		WLOGW(_T("Start receiving media stream data...\n"));
		setBtnStatus(SL_STATUS_PLAY);
	}
}

void CListenTalkDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	if( !m_hMediaSource ) 
	{
		WLOGD(_T("Media stream was not opened\n"));
		return;
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Stops receiving the stream data from the media source handle.  
	// -----------------------------------------------------------------------
	m_ctrlXnsWindow.Stop();
	WLOGW(_T("Stop receiving stream data...\n"));
	

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Terminates transferring media stream data from the device. The media 
	// stream data will be separated by hMediaSource 
	// (i.e., phMediaSource of OpenMedia()).
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.CloseMedia(m_hDevice, m_hMediaSource);
	WLOGD(_T("Close media...\n"));
	m_hMediaSource = 0;
	m_nControlId = 0;

	setBtnStatus(SL_STATUS_STOP);
}



// Control button enable/disable
void CListenTalkDlg::setBtnStatus(SLIVE_BUTTON_STATUS nStatus)
{
	bool conn = false, disconn = false, play = false, stop = false;
	switch(nStatus)
	{
	case SL_STATUS_CONNECTED:
		conn = false;
		disconn = true;
		play = true;
		stop = false;
		break;
	case SL_STATUS_DISCONNECTED:
		conn = true;
		disconn = false;
		play = false;
		stop = false;
		break;
	case SL_STATUS_PLAY:
		conn = false;
		disconn = true;
		play = false;
		stop = true;
		break;
	case SL_STATUS_STOP:
		conn = false;
		disconn = true;
		play = true;
		stop = false;
		break;
	}

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(conn);
	GetDlgItem(IDC_COMBO_MODEL_LIST)->EnableWindow(conn);
	GetDlgItem(IDC_CHECK_SUNAPI)->EnableWindow(conn);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PW)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PORT2)->EnableWindow(conn);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(disconn);
	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(play);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(stop);

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(conn);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(disconn);
	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(play);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(stop);

	SetCheckSunapi();
}

void CListenTalkDlg::OnBnClickedCheckListen()
{
	// TODO: Add your control notification handler code here

	m_bListen = !m_bListen;


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Enable or disable the Listen icon from XnsSDKWindow control, 
	// when the Listen function is set to ON or OFF. Turns on or off the 
	// Listen function. Listen enables the application to play the audio 
	// source. To enable this function, the control module should support 
	// XCTL_CAP_LISTEN capability. 
	// -----------------------------------------------------------------------
	long nRet = m_ctrlXnsDevice.SetListen(
		m_hDevice,			// [in] Device handle. 
		m_nControlId,		// [in] Control ID,
		XMEDIA_LIVE,		// [in] Media type.
							//      * XMEDIA_LIVE(=1):Live, 
							//      * XMEDIA_PLAYBACK(=2):Playback
		m_bListen			// [in] Listen is activated.
		);
	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("SetListen() fail: ret=[%d](%s)\n"),
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
		return;
	}
	WLOGD(_T("SetListen() flag=%d\n"), m_bListen);


	// Turns on or off the sound. 
	m_ctrlXnsWindow.SetSound(m_bListen);

	// Specify the volume level of the sound.
	if(m_bListen)
	{
		m_ctrlXnsWindow.SetVolume(100);
	}
}


void CListenTalkDlg::OnBnClickedCheckTalk()
{
	// TODO: Add your control notification handler code here

	m_bTalk = !m_bTalk;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Turns on or off the Talk function. 
	// Talk can enable the device to play the audio source. 
	// The application should use SendAudioData() to transfer the audio 
	// source that it wants to play. Talk is available only in live streaming 
	// mode and only if the control module supports XCTL_CAP_TALK capability. 
	// -----------------------------------------------------------------------
	long nRet = m_ctrlXnsDevice.SetTalk(
		m_hDevice,			// [in] Device handle.
		m_nControlId,		// [in] Control ID
		m_bTalk				// [in] Talk is activated.
		);

	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("SetTalk() fail: ret=[%d](%s)\n"),
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
		return;
	}
	WLOGD(_T("SetTalk() flag=%d\n"), m_bTalk);

}


// WAVE TALK
WAVEFORMATEX wave_format_in;
struct HWAVEIN__ *  wavein_handle;

char *abuffer[BUFF_NUM];
WAVEHDR WaveHeaderIn[BUFF_NUM];

int		curr_in = 0;
bool	terminate_thread_in = false;
HANDLE  WaveInEvent; 
long	tick_count = 0;
long	notify_size=0;

UINT WaveInThreadProc(void *param)
{
	CListenTalkDlg *parent = (CListenTalkDlg *)param;
	WaitForSingleObject(WaveInEvent, INFINITE); 
	tick_count = 0;
	unsigned long last_tick=0;
	while(1)
	{
		if((WaitForSingleObject(WaveInEvent, INFINITE) == WAIT_OBJECT_0) && (!terminate_thread_in) ) 
		{
			EnterCriticalSection(&parent->m_hCritSect);
			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Transfers the audio data to the device. This function is used when 
			// the application transfers the audio data to the device using Talk. 
			// Then, the audio data should be encoded to be suitable for the device. 
			// This function is valid only in live mode. 
			// -----------------------------------------------------------------------
			if (tick_count != 0)
			{
				tick_count = ::GetTickCount()-last_tick;
			}
			
			int nRet = parent->m_ctrlXnsDevice.SendAudioData(
				parent->m_hDevice,					// [in] Device handle. This value is returned from CreateDevice()
				(long)((char *)(abuffer[curr_in])), // [in] Pointer to indicate the memory where the audio data is stored.
				notify_size,						// [in] Length of the audio data to transfer.
				tick_count							// [in] TimeStamp (msec)
				);
			
			last_tick = ::GetTickCount();

			SYSTEMTIME cur_time; 
			GetLocalTime(&cur_time); 
			CString timeStr;
			timeStr.Format(_T("%02d-%02d-%02d:%03ld"),cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds);

			DBG_LOG(_T("(%s)SendAudioData:: idx=%d, SEND=(%d::%d)bytes, ret=[%d](%s)\n"), 
				timeStr, curr_in, notify_size, tick_count, nRet, parent->m_ctrlXnsDevice.GetErrorString(nRet));
			tick_count += TIME_OFFSET;

			
			curr_in++;
			if(curr_in >= BUFF_NUM)
			{
				curr_in = 0;
			}
			
			waveInUnprepareHeader (wavein_handle, &WaveHeaderIn[curr_in], sizeof(WAVEHDR));
			waveInPrepareHeader( wavein_handle, &WaveHeaderIn[curr_in], sizeof(WAVEHDR) );
			waveInAddBuffer( wavein_handle, &WaveHeaderIn[curr_in], sizeof(WAVEHDR) );
			LeaveCriticalSection(&parent->m_hCritSect);
			continue;
		}
		break;
	}

	return 0;
}


void CListenTalkDlg::OnBnClickedButtonSendAudio()
{
	if(m_bSendAudio)
	{
		WLOGD(_T("Already Sending audio...\n"));
		return;
	}

	EnterCriticalSection(&m_hCritSect);
	m_bSendAudio = true;
	UpdateData(TRUE);
	int channel, bps, sps;
	CString strTmp;

	m_ctrlChannel.GetLBText(m_nChannel, strTmp);
	channel = _ttoi(strTmp);
	m_ctrlBps.GetLBText(m_nBps, strTmp);
	bps = _ttoi(strTmp);
	m_ctrlSps.GetLBText(m_nSps, strTmp);
	sps = _ttoi(strTmp);
	WLOGD(_T("SendAudio:: channel=%d, bps=%d, sps=%d, packet=%d\n"), 
		channel, bps, sps, m_nSendBytes);
	notify_size = m_nSendBytes;

	for(int i=0; i<BUFF_NUM;i++)
	{
		if(abuffer[i]!=NULL)
		{
			delete[] abuffer[i];
			abuffer[i]=NULL;
		}
		abuffer[i] = new char[m_nSendBytes];
	}

	memset((char*)&wave_format_in,0, sizeof(wave_format_in));
	wave_format_in.wFormatTag		= WAVE_FORMAT_PCM;
	wave_format_in.nChannels		= channel;
	wave_format_in.nSamplesPerSec	= sps; 
	wave_format_in.wBitsPerSample	= bps;
	wave_format_in.nBlockAlign		= (channel*bps/8);
	wave_format_in.nAvgBytesPerSec	= (sps*wave_format_in.nBlockAlign);
	wave_format_in.cbSize			= 0;

	terminate_thread_in=false;
	curr_in = 0;
	WaveInEvent = CreateEvent(NULL, FALSE, FALSE, NULL);  
	AfxBeginThread(WaveInThreadProc, this, THREAD_PRIORITY_NORMAL , 0, 0, NULL);  

	int result = waveInOpen( &wavein_handle, WAVE_MAPPER, 
		(WAVEFORMATEX *) &wave_format_in,
		(DWORD) WaveInEvent,
		0, CALLBACK_EVENT);

	for(int i=0; i<BUFF_NUM; i++) 
	{
		WaveHeaderIn[i].lpData = abuffer[i];
		WaveHeaderIn[i].dwBufferLength = m_nSendBytes; 
		waveInPrepareHeader( wavein_handle, &WaveHeaderIn[i], sizeof(WAVEHDR) );
		waveInAddBuffer( wavein_handle, &WaveHeaderIn[i], sizeof(WAVEHDR) );
	}
	waveInStart(wavein_handle);
	LeaveCriticalSection(&m_hCritSect);
}

void CListenTalkDlg::OnBnClickedButtonStopAudio()
{
	EnterCriticalSection(&m_hCritSect);
	waveInStop(wavein_handle);
	waveInReset(wavein_handle);
	waveInClose(wavein_handle);
	m_bSendAudio = false;
	LeaveCriticalSection(&m_hCritSect);
}



#if 0 // for record test
WAVEFORMATEX wave_format_out;
struct HWAVEOUT__ *  waveout_handle;
WAVEHDR WaveHeaderOut[BUFF_NUM];
int		curr_out = 0;
bool	terminate_thread_out = false;
HANDLE  WaveOutEvent; 

UINT WaveOutThreadProc(void *param)
{
	CListenTalkDlg *parent = (CListenTalkDlg *)param;
	WaitForSingleObject(WaveOutEvent, INFINITE);  
	while(1)
	{
		curr_out++;
		if(curr_out == BUFF_NUM)
		{
			AfxMessageBox(_T("BUFFER END"));
			curr_out = 0;
			waveOutClose(waveout_handle);
			break;
		}

		WaveHeaderOut[curr_out].lpData = abuffer[curr_out];
		WaveHeaderOut[curr_out].dwBufferLength = NOTIFY_SIZE; 
		WaveHeaderOut[curr_out].dwFlags = 0L;
		WaveHeaderOut[curr_out].dwLoops = 0L;
		WaveHeaderOut[curr_out].dwBytesRecorded = WaveHeaderIn[curr_out].dwBytesRecorded;

		waveOutPrepareHeader(waveout_handle, &WaveHeaderOut[curr_out], sizeof(WAVEHDR) );
		waveOutWrite( (HWAVEOUT)waveout_handle, &WaveHeaderOut[curr_out], sizeof(WAVEHDR));
	}

	return 0;
}


void CListenTalkDlg::OnBnClickedButtonGo()
{
	// TODO: Add your control notification handler code here

	WaveOutEvent = CreateEvent(NULL, FALSE, FALSE, NULL);  
	AfxBeginThread(WaveOutThreadProc, this, THREAD_PRIORITY_NORMAL , 0, 0, NULL); 
	wave_format_out = wave_format_in;
	int result = waveOutOpen( &waveout_handle, WAVE_MAPPER, 
		(WAVEFORMATEX *) &wave_format_out,
		(DWORD) WaveOutEvent, 
		0, CALLBACK_EVENT );


	curr_out = 0;
	memset( &WaveHeaderOut[curr_out], 0x00, sizeof(WAVEHDR)); 

	WaveHeaderOut[curr_out].lpData = abuffer[curr_out];
	WaveHeaderOut[curr_out].dwBufferLength = NOTIFY_SIZE; 
	WaveHeaderOut[curr_out].dwFlags = 0L;
	WaveHeaderOut[curr_out].dwLoops = 0L;
	WaveHeaderOut[curr_out].dwBytesRecorded = WaveHeaderIn[curr_out].dwBytesRecorded;
	DBG_LOG(_T("record out size[%d]::%d\n"), 
		WaveHeaderOut[curr_out].dwBytesRecorded , curr_out);

	waveOutPrepareHeader(waveout_handle, &WaveHeaderOut[curr_out], sizeof(WAVEHDR) );
	waveOutWrite( (HWAVEOUT)waveout_handle, 
		&WaveHeaderOut[curr_out], sizeof(WAVEHDR));
}

#endif

void CListenTalkDlg::OnBnClickedButtonSendAudio2()
{
	long ret = m_ctrlXnsDevice.SendAudioData2(m_hDevice, m_nControlId);
}


void CListenTalkDlg::OnBnClickedButtonStopAudio2()
{
	long ret = m_ctrlXnsDevice.StopAudioData2(m_hDevice);
}


void CListenTalkDlg::OnCbnSelchangeComboModelList()
{
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
	SetCheckSunapi();
}

void CListenTalkDlg::SetCheckSunapi()
{
	GetDlgItem(IDC_CHECK_SUNAPI)->EnableWindow(FALSE);
	m_nDeviceProtocol = XDEVICE_PROTOCOL_UNKNOWN;

	if(m_strModelName == "Samsung Network Camera/Encoder" || m_strModelName == "Samsung NVR")
	{
		if(m_ctrlSunapi.GetCheck())
			m_nDeviceProtocol = XDEVICE_PROTOCOL_SUNAPI;
		if(m_ctrlXnsDevice.GetDeviceStatus(m_hDevice) != XDEVICE_STATUS_CONNECTED)
			GetDlgItem(IDC_CHECK_SUNAPI)->EnableWindow(TRUE);
	}
}

void CListenTalkDlg::OnOK()
{
	//CDialog::OnOK();
}


void CListenTalkDlg::OnBnClickedCheckSunapi()
{
	SetCheckSunapi();
}
