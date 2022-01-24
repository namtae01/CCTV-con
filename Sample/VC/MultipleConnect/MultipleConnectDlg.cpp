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
// MultipleConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultipleConnect.h"
#include "MultipleConnectDlg.h"

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


// CMultipleConnectDlg dialog

#define MODEL_NAME	"Samsung Network Camera/Encoder"
#define IP_ADDRESS	192,168,1,101
#define PORT_NUM	4520
#define HTTP_PORT_NUM 80
#define LOGIN_ID	"admin"
#define PASSWORD	"5tkatjd!"

CMultipleConnectDlg::CMultipleConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultipleConnectDlg::IDD, pParent)
	, m_strModelName(_T(""))
	, m_nPort(PORT_NUM)
	, m_strId(_T(LOGIN_ID))
	, m_strPasswd(_T(PASSWORD))
	, m_hDevice(0)
	, m_nHttpPort(HTTP_PORT_NUM)
	, m_nDeviceProtocol(XDEVICE_PROTOCOL_UNKNOWN)
	, m_nMediaProtocol(0)
	, m_nChannelIndex(0)
	, m_nProfileIndex(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	CString strMessage = _T("");
	m_bWindowCtrl1 = FALSE;
	m_bWindowCtrl2 = FALSE;
	m_bWindowCtrl3 = FALSE;
	m_bWindowCtrl4 = FALSE;
	InitDeviceInfo(0);
	InitDeviceInfo(1);
	InitDeviceInfo(2);
	InitDeviceInfo(3);
}

void CMultipleConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_XNSSDKDEVICECTRL, m_ctrlXnsDevice);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL, m_ctrlXnsWindow);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL2, m_ctrlXnsWindow2);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL3, m_ctrlXnsWindow3);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL4, m_ctrlXnsWindow4);
	DDX_Control(pDX, IDC_COMBO_MODEL_LIST, m_ctrlModelList);
	DDX_Control(pDX, IDC_LIST_DEVICE, m_ctrlListDevice);
	DDX_Control(pDX, IDC_EDIT_LOG, m_ctrlEditLog);
	DDX_Control(pDX, IDC_IPADDRESS, m_ctrlIpAddress);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_ID, m_strId);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPasswd);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_nHttpPort);
	DDX_Control(pDX, IDC_CHECK_SUNAPI, m_ctrlSunapi);
}

BEGIN_MESSAGE_MAP(CMultipleConnectDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMultipleConnectDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMultipleConnectDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CMultipleConnectDlg::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CMultipleConnectDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CMultipleConnectDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMultipleConnectDlg::OnBnClickedButtonStop)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DEVICE, &CMultipleConnectDlg::OnNMClickListDevice)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CMultipleConnectDlg::OnCbnSelchangeComboModelList)
	ON_BN_CLICKED(IDC_CHECK_SUNAPI, &CMultipleConnectDlg::OnBnClickedCheckSunapi)
END_MESSAGE_MAP()

// CMultipleConnectDlg message handlers

BOOL CMultipleConnectDlg::OnInitDialog()
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
	if (nRet != ERR_SUCCESS)
	{
		WLOGD(_T("Initialize() fail: errno=[%d]\n"), nRet);
	}
	
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Initializes the XnsSdkWindow control. 
	// Namely, this will specify the window handle in order to display 
	// images on the screen. 
	// -----------------------------------------------------------------------
	nRet = m_ctrlXnsWindow.Initialize(NULL, NULL);
	WLOGW(_T("Initialize() return=[%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	nRet = m_ctrlXnsWindow2.Initialize(NULL, NULL);
	WLOGW(_T("Initialize() return=[%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	nRet = m_ctrlXnsWindow3.Initialize(NULL, NULL);
	WLOGW(_T("Initialize() return=[%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	nRet = m_ctrlXnsWindow4.Initialize(NULL, NULL);
	WLOGW(_T("Initialize() return=[%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	m_ctrlXnsWindow.SetOSDOnOff(0xFFFF, 0);
	m_ctrlXnsWindow2.SetOSDOnOff(0xFFFF, 0);
	m_ctrlXnsWindow3.SetOSDOnOff(0xFFFF, 0);
	m_ctrlXnsWindow4.SetOSDOnOff(0xFFFF, 0);

	m_ctrlXnsWindow.SetOSDOnOff(0x0004, 1);
	m_ctrlXnsWindow2.SetOSDOnOff(0x0004, 1);
	m_ctrlXnsWindow3.SetOSDOnOff(0x0004, 1);
	m_ctrlXnsWindow4.SetOSDOnOff(0x0004, 1);


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
		if(m_strModelName == "Samsung Network Camera/Encoder")
		{
			
		}
		UpdateData(FALSE);
	}
	
	CreateDeviceList();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMultipleConnectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMultipleConnectDlg::OnPaint()
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
HCURSOR CMultipleConnectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMultipleConnectDlg::OnBnClickedButtonAdd()
{
	UpdateData(TRUE);

	int nDeviceIndex;
	nDeviceIndex = getWindowCtrl();
	if(!nDeviceIndex)
	{
		WLOGD(_T("Not enought xnsSdkWindow\n"));
		return;
	}
	if(!m_hDevice)
	{
		m_hDevice = m_ctrlXnsDevice.CreateDevice(nDeviceIndex);
	}
	CString strModel;
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), strModel);
	CString strIpAddress;
	BYTE a1, a2, a3, a4;
	m_ctrlIpAddress.GetAddress(a1, a2, a3, a4);
	strIpAddress.Format(_T("%d.%d.%d.%d"), a1, a2, a3, a4);

	DevInfo[nDeviceIndex-1].hDevice			= m_hDevice;
	DevInfo[nDeviceIndex-1].nDevice			= nDeviceIndex;
	DevInfo[nDeviceIndex-1].strModel		= strModel;
	DevInfo[nDeviceIndex-1].nDeviceProtocol	= m_nDeviceProtocol;
	DevInfo[nDeviceIndex-1].nMediaProtocol	= m_nMediaProtocol;
	DevInfo[nDeviceIndex-1].strIpAddress	= strIpAddress;
	DevInfo[nDeviceIndex-1].nPort			= m_nPort;
	DevInfo[nDeviceIndex-1].nHttpPort		= m_nHttpPort;
	DevInfo[nDeviceIndex-1].strId			= m_strId;
	DevInfo[nDeviceIndex-1].strPasswd		= m_strPasswd;
	DevInfo[nDeviceIndex-1].bIsDevice		= TRUE;
	
	setTrueWindowCtrl(nDeviceIndex);
	m_hDevice = 0;
	RefreshDeviceList();
}

void CMultipleConnectDlg::OnBnClickedButtonRemove()
{
	if(!ExceptionHandling())
	{
		return;
	}
	if(DevInfo[m_nSelItem].bIsMediaPlay)
	{
		setCtrlXnsWindow(m_nSelItem+1);
		m_ptrXnsWindow->Stop();
	}
	if(DevInfo[m_nSelItem].hMediaSource) 
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Terminates transferring media stream data from the device. The media 
		// stream data will be separated by hMediaSource 
		// (i.e., phMediaSource of OpenMedia()).
		// -----------------------------------------------------------------------
		m_ctrlXnsDevice.CloseMedia(DevInfo[m_nSelItem].hDevice, DevInfo[m_nSelItem].hMediaSource);
	}
	if(m_ctrlXnsDevice.GetDeviceStatus(DevInfo[m_nSelItem].hDevice))
	{
		// Disconnects from the device.
		m_ctrlXnsDevice.Disconnect(DevInfo[m_nSelItem].hDevice);
		WLOGD(_T("Disconnect\n"));
	}
	m_ctrlXnsDevice.ReleaseDevice(DevInfo[m_nSelItem].hDevice);
	setFalseWindowCtrl(m_nSelItem+1);
	InitDeviceInfo(m_nSelItem);
	WLOGD(_T("DeleteItem\n"));
	RefreshDeviceList();
}

void CMultipleConnectDlg::OnBnClickedButtonConnect()
{
	if(!ExceptionHandling())
	{
		return;
	}
	SetCheckSunapi();
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Sets the device information so that the application can connect 
	// to the device.
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.SetConnectionInfo2(
		DevInfo[m_nSelItem].hDevice,				// [in] Device handle
		_T("Samsung"),								// [in] Fixed as 'Samsung'
		DevInfo[m_nSelItem].strModel,				// [in] Name of model to connect to. The maximum length allowed is 126-byte.
		XADDRESS_IP,								// [in] Address type
		DevInfo[m_nSelItem].strIpAddress,			// [in] actual address according to address type.
		DevInfo[m_nSelItem].nPort,					// [in] Port number
		DevInfo[m_nSelItem].nHttpPort,				// [in] port number for web access	
		DevInfo[m_nSelItem].strId,					// [in] Login ID
		DevInfo[m_nSelItem].strPasswd,				// [in] password
		DevInfo[m_nSelItem].nDeviceProtocol,
		DevInfo[m_nSelItem].nMediaProtocol
		);

	WLOGD(_T("Connect. ip=%s, deviceProtocol=%d, mediaProtocol=%d, port=%d, httpport=%d,  id=%s, password=%s\n"), 
		DevInfo[m_nSelItem].strIpAddress, DevInfo[m_nSelItem].nDeviceProtocol, DevInfo[m_nSelItem].nMediaProtocol, DevInfo[m_nSelItem].nPort, DevInfo[m_nSelItem].nHttpPort,
		DevInfo[m_nSelItem].strId, DevInfo[m_nSelItem].strPasswd);

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
		DevInfo[m_nSelItem].hDevice,		// [in] Device handle
		TRUE,			// [in] Flag to decide where to forcibly log in or not.
		FALSE			// [in] If this value is 1, try to connect again.
		);
	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ConnectNonBlock() fail: errno=[%d](%s)\n"), 
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
}

void CMultipleConnectDlg::OnBnClickedButtonDisconnect()
{
	if(!ExceptionHandling())
	{
		return;
	}
	if(!DevInfo[m_nSelItem].bIsMediaPlay)
	{
		setCtrlXnsWindow(m_nSelItem+1);
		m_ptrXnsWindow->Stop();
	}
	if(!DevInfo[m_nSelItem].hMediaSource) 
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Terminates transferring media stream data from the device. The media 
		// stream data will be separated by hMediaSource 
		// (i.e., phMediaSource of OpenMedia()).
		// -----------------------------------------------------------------------
		m_ctrlXnsDevice.CloseMedia(DevInfo[m_nSelItem].hDevice, DevInfo[m_nSelItem].hMediaSource);
	}
	if(m_ctrlXnsDevice.GetDeviceStatus(DevInfo[m_nSelItem].hDevice))
	{
		// Disconnects from the device.
		m_ctrlXnsDevice.Disconnect(DevInfo[m_nSelItem].hDevice);
		WLOGD(_T("Disconnect\n"));
	}
	DevInfo[m_nSelItem].bIsMediaPlay = FALSE;
	DevInfo[m_nSelItem].hMediaSource = 0;
}

void CMultipleConnectDlg::OnBnClickedButtonPlay()
{
	if(!ExceptionHandling())
	{
		return;
	}
	if(!DevInfo[m_nSelItem].hMediaSource) 
	{
		WLOGD(_T("Media stream was not opened\n"));
		return;
	}
	if(DevInfo[m_nSelItem].bIsMediaPlay)
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
	setCtrlXnsWindow(m_nSelItem+1);
	m_ptrXnsWindow->Start(DevInfo[m_nSelItem].hMediaSource);

	WLOGW(_T("Start receiving media stream data...\n"));
	DevInfo[m_nSelItem].bIsMediaPlay = TRUE;
}

void CMultipleConnectDlg::OnBnClickedButtonStop()
{
	if(!ExceptionHandling())
	{
		return;
	}
	if(!DevInfo[m_nSelItem].hMediaSource) 
	{
		WLOGD(_T("Media stream was not opened\n"));
		return;
	}
	if(!DevInfo[m_nSelItem].bIsMediaPlay)
	{
		WLOGW(_T("Media stream is not played\n"));
		return;
	}

	setCtrlXnsWindow(m_nSelItem+1);
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Stops receiving the stream data from the media source handle.  
	// -----------------------------------------------------------------------
	m_ptrXnsWindow->Stop();

	WLOGW(_T("Stop receiving stream data...\n"));

	DevInfo[m_nSelItem].bIsMediaPlay = FALSE;
}

void CMultipleConnectDlg::OnDestroy()
{
	for(int i = 0; i < 4; i++)
	{
		if(DevInfo[i].hDevice)
		{
			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Returns the connection status of the device.
			// -----------------------------------------------------------------------
			if(m_ctrlXnsDevice.GetDeviceStatus(DevInfo[i].hDevice) == XDEVICE_STATUS_CONNECTED)
			{
				OnBnClickedButtonDisconnect();
			}
			// Cancels the memory space assigned for the device information by 
			// CreateDevice(). The device should be disconnected from the application
			// before this function is called.
			m_ctrlXnsDevice.ReleaseDevice(DevInfo[i].hDevice);
		}
	}
	CDialog::OnDestroy();
}

BEGIN_EVENTSINK_MAP(CMultipleConnectDlg, CDialog)
	ON_EVENT(CMultipleConnectDlg, IDC_XNSSDKDEVICECTRL, 10, CMultipleConnectDlg::OnDeviceStatusChangedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CMultipleConnectDlg, IDC_XNSSDKDEVICECTRL, 3, CMultipleConnectDlg::OnConnectFailedXnssdkdevicectrl, VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the device status has changed. It occurs if the 
// application uses Connect() to connect or reconnect to the device after 
// disconnected. When reconnecting, the third argument nDeviceStatus is 
// true, all media must be reopened using ReopenAllStream().
// -----------------------------------------------------------------------
void CMultipleConnectDlg::OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
	// TODO: Add your message handler code here
	if(nErrorCode != ERR_SUCCESS || nDeviceStatus != 1)
	{
		return;
	}

	WLOGD(_T("Connected: deviceID=%d, errcode=%d, deviceStatus=%d\n"),
		nDeviceID, nErrorCode, nDeviceStatus);

	if(DevInfo[m_nSelItem].hMediaSource) 
	{
		WLOGD(_T("Media stream was already opend\n"));
		return;
	}

	WLOGD(_T("Open media stream\n"));
	
	UpdateData(TRUE);

	WLOGD(_T("Open media stream::channel(%d), profile(%d)\n"), m_nChannelIndex+1, m_nProfileIndex+1);
	
	m_nControlId = m_ctrlXnsDevice.GetVideoControlID(DevInfo[m_nSelItem].hDevice, m_nChannelIndex+1, m_nProfileIndex+1);
	if( m_ctrlXnsDevice.OpenMedia(DevInfo[m_nSelItem].hDevice, m_nControlId, MEDIA_TYPE_LIVE, 0, 0, &DevInfo[m_nSelItem].hMediaSource) == ERR_SUCCESS )
	{
		WLOGW(_T("Open media...control id=[%d]\n"), m_nControlId);
		return;
	}
	
	WLOGD(_T("Invalid device..\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// If the application has failed in non-blocking connection using 
// ConnectNonBlock(), the OnConnectFailed event occurs. As Connect() 
// returns an immediate error message if failed, it does not trigger 
// this event. 
// -----------------------------------------------------------------------
void CMultipleConnectDlg::OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode)
{
	WLOGD(_T("Disconnected: deviceID=%d, errcode=%d:%s\n"),
		nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode));
}

void CMultipleConnectDlg::CreateDeviceList(void)
{
	m_ctrlListDevice.SetExtendedStyle(LVS_EX_FULLROWSELECT  | LVS_EX_GRIDLINES );
	m_ctrlListDevice.InsertColumn(0, _T("No"), LVCFMT_LEFT, 25);
	m_ctrlListDevice.InsertColumn(1, _T("Model"), LVCFMT_LEFT, 60);
	m_ctrlListDevice.InsertColumn(2, _T("IP"), LVCFMT_LEFT, 90);
	m_ctrlListDevice.InsertColumn(3, _T("Port"), LVCFMT_LEFT, 40);
	m_ctrlListDevice.InsertColumn(4, _T("ID"), LVCFMT_LEFT, 40);
	m_ctrlListDevice.InsertColumn(5, _T("PW"), LVCFMT_LEFT, 40);
	m_ctrlListDevice.InsertColumn(6, _T("Dev"), LVCFMT_LEFT, 30);
}

void CMultipleConnectDlg::RefreshDeviceList(void)
{
	m_ctrlListDevice.DeleteAllItems();

	int j = 0;
	for(int i = 0 ; i < 4 ; i++)
	{
		if(DevInfo[i].bIsDevice == TRUE)
		{
			CString strDeviceIndex;
			strDeviceIndex.Format(_T("%d"), j+1);
			m_ctrlListDevice.InsertItem(j, strDeviceIndex, 0);
			m_ctrlListDevice.SetItemText(j, 1, DevInfo[i].strModel);
			m_ctrlListDevice.SetItemText(j, 2, DevInfo[i].strIpAddress);
			CString strPort;
			strPort.Format(_T("%d"), DevInfo[i].nPort);
			m_ctrlListDevice.SetItemText(j, 3, strPort);
			m_ctrlListDevice.SetItemText(j, 4, DevInfo[i].strId);
			m_ctrlListDevice.SetItemText(j, 5, DevInfo[i].strPasswd);
			CString strDev;
			strDev.Format(_T("%d"), DevInfo[i].nDevice);
			m_ctrlListDevice.SetItemText(j, 6, strDev);
			j++;
		}
	}
}

void CMultipleConnectDlg::setCtrlXnsWindow(int m_nSelItem)
{
	switch(m_nSelItem)
	{
	case 1:
		m_ptrXnsWindow = &m_ctrlXnsWindow;
		break;
	case 2:
		m_ptrXnsWindow = &m_ctrlXnsWindow2;
		break;
	case 3:
		m_ptrXnsWindow = &m_ctrlXnsWindow3;
		break;
	case 4:
		m_ptrXnsWindow = &m_ctrlXnsWindow4;
		break;
	}
}

int CMultipleConnectDlg::getWindowCtrl(void)
{
	if(!m_bWindowCtrl1)
	{
		return 1;
	}
	else if(!m_bWindowCtrl2)
	{
		return 2;
	}
	else if(!m_bWindowCtrl3)
	{
		return 3;
	}
	else if(!m_bWindowCtrl4)
	{
		return 4;
	}
	return 0;
}

void CMultipleConnectDlg::setFalseWindowCtrl(int WindowCtrl)
{
	switch(WindowCtrl)
	{
	case 1:
		m_bWindowCtrl1 = FALSE;
		break;
	case 2:
		m_bWindowCtrl2 = FALSE;
		break;
	case 3:
		m_bWindowCtrl3 = FALSE;
		break;
	case 4:
		m_bWindowCtrl4 = FALSE;
		break;
	}
}

void CMultipleConnectDlg::setTrueWindowCtrl(int WindowCtrl)
{
	switch(WindowCtrl)
	{
	case 1:
		m_bWindowCtrl1 = TRUE;
		break;
	case 2:
		m_bWindowCtrl2 = TRUE;
		break;
	case 3:
		m_bWindowCtrl3 = TRUE;
		break;
	case 4:
		m_bWindowCtrl4 = TRUE;
		break;
	}
}

bool CMultipleConnectDlg::IsEmptyWindowCtrl()
{
	if(m_bWindowCtrl1 || m_bWindowCtrl2 || m_bWindowCtrl3 || m_bWindowCtrl4)
	{
		return TRUE;
	}
	return FALSE;
}

// Device Information Initialize
void CMultipleConnectDlg::InitDeviceInfo(int m_nSelItem)
{
	DevInfo[m_nSelItem].bIsDevice = FALSE;
	DevInfo[m_nSelItem].nDevice = 0;
	DevInfo[m_nSelItem].strModel = _T("");
	DevInfo[m_nSelItem].strIpAddress = _T("");
	DevInfo[m_nSelItem].nPort = 0;
	DevInfo[m_nSelItem].nHttpPort = 0;
	DevInfo[m_nSelItem].strId = _T("");
	DevInfo[m_nSelItem].strPasswd = _T("");
	DevInfo[m_nSelItem].hDevice = 0;
	DevInfo[m_nSelItem].hMediaSource = 0;
	DevInfo[m_nSelItem].bIsMediaPlay = FALSE;
}

bool CMultipleConnectDlg::ExceptionHandling()
{
	POSITION pos = m_ctrlListDevice.GetFirstSelectedItemPosition();
	if(!pos)
	{
		WLOGD(_T("May be device is not seleted\n"));
		return FALSE;
	}
	int nSelItem = m_ctrlListDevice.GetNextSelectedItem(pos);
	if(!IsEmptyWindowCtrl())
	{
		WLOGD(_T("May be device is not connected\n"));
		return FALSE;
	}
	return TRUE;
}

void CMultipleConnectDlg::OnNMClickListDevice(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;
	int idx = pNMListView->iItem;
	m_nSelItem = _ttoi(m_ctrlListDevice.GetItemText(idx, 6))-1;
}

void CMultipleConnectDlg::OnCbnSelchangeComboModelList()
{
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
	SetCheckSunapi();
}


void CMultipleConnectDlg::OnOK()
{
	/*CDialog::OnOK();*/
}


void CMultipleConnectDlg::OnBnClickedCheckSunapi()
{
	SetCheckSunapi();
}

void CMultipleConnectDlg::SetCheckSunapi()
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