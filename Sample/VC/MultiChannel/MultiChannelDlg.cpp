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
// MultiChannelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultiChannel.h"
#include "MultiChannelDlg.h"
#include "afxdialogex.h"
#include <math.h>

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


// CMultiChannelDlg dialog

// Network Camera/Encoder
#define MODEL_NAME	"Samsung Network Camera/Encoder"
#define IP_ADDRESS	192,168,100,32
#define PORT_NUM	4520
#define HTTP_PORT_NUM 80
#define LOGIN_ID	"admin"
#define PASSWORD	"5gksghk!"

// DVR/NVR
// #define MODEL_NAME	"Samsung NVR"
// #define IP_ADDRESS	192,168,100,39
// #define PORT_NUM	4520
// #define LOGIN_ID	"admin"
// #define PASSWORD	"44444"


CMultiChannelDlg::CMultiChannelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMultiChannelDlg::IDD, pParent)
	, m_strModelName(_T(""))
	, m_nPort(PORT_NUM)
	, m_nHttpPort(HTTP_PORT_NUM)
	, m_strId(_T(LOGIN_ID))
	, m_strPasswd(_T(PASSWORD))
	, m_hDevice(0)
	, m_nDeviceProtocol(XDEVICE_PROTOCOL_UNKNOWN)
	, m_nMediaProtocol(0)
	, m_nChannelIndex(0)
	, m_nProfileIndex(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for(int i=0; i<16; i++)
		m_hMediaSource[i] = 0;
}

void CMultiChannelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_XNSSDKDEVICECTRL1, m_ctrlXnsDevice);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL1, m_ctrlXnsWindow1);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL2, m_ctrlXnsWindow2);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL3, m_ctrlXnsWindow3);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL4, m_ctrlXnsWindow4);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL5, m_ctrlXnsWindow5);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL6, m_ctrlXnsWindow6);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL7, m_ctrlXnsWindow7);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL8, m_ctrlXnsWindow8);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL9, m_ctrlXnsWindow9);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL10, m_ctrlXnsWindow10);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL11, m_ctrlXnsWindow11);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL12, m_ctrlXnsWindow12);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL13, m_ctrlXnsWindow13);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL14, m_ctrlXnsWindow14);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL15, m_ctrlXnsWindow15);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL16, m_ctrlXnsWindow16);
	DDX_Control(pDX, IDC_IPADDRESS, m_ctrlIpAddress);
	DDX_Text(pDX, IDC_EDIT_ID, m_strId);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPasswd);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Control(pDX, IDC_EDIT_LOG_WIN, m_ctrlEditLog);
	DDX_Control(pDX, IDC_COMBO_MODEL_LIST, m_ctrlModelList);
	DDX_CBString(pDX, IDC_COMBO_MODEL_LIST, m_strModelName);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comboChannel);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_nHttpPort);
	DDX_Control(pDX, IDC_CHECK_SUNAPI, m_ctrlSunapi);
}

BEGIN_MESSAGE_MAP(CMultiChannelDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMultiChannelDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CMultiChannelDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMultiChannelDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMultiChannelDlg::OnBnClickedButtonClose)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CMultiChannelDlg::OnCbnSelchangeComboModelList)
	ON_BN_CLICKED(IDC_CHECK_SUNAPI, &CMultiChannelDlg::OnBnClickedCheckSunapi)
END_MESSAGE_MAP()

BOOL CMultiChannelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	DBG_LOG(_T("Start\n"));


	setWindowPtr();

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Initializes the XnsSdkWindow control. 
	// Namely, this will specify the window handle in order to display 
	// images on the screen. 
	// -----------------------------------------------------------------------
	for( int i=0;i<MAXCHANNEL; i++)
	{
		m_ptrXnsWindow[i]->Initialize(NULL, NULL);
		WLOGW(_T("%d. Initialize() return=[%d](%s)\n"), i+1, nRet, m_ctrlXnsDevice.GetErrorString(nRet));
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
	for(int i = 0; i < nCount; i++)
	{
		// Reurns data of nIndex from the array created using FindVendor() 
		// and FindModel(). If nIndex is larger than the actual array, 
		// "" will be returned.
		strModel = m_ctrlXnsDevice.GetFindString(nFind, i);
		m_ctrlModelList.AddString(strModel);
	}
	// Closes the Find command. Releases the memory space assinged by FindXXX().
	m_ctrlXnsDevice.CloseFind(nFind);

	int idx = m_ctrlModelList.FindStringExact(0, _T(MODEL_NAME));
	if(idx != CB_ERR)
	{
		m_ctrlModelList.SetCurSel(idx);
		m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
		UpdateData(FALSE);
	}

	setBtnStatus(STATUS_DISCONNECTED);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMultiChannelDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

HCURSOR CMultiChannelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CMultiChannelDlg, CDialogEx)
	ON_EVENT(CMultiChannelDlg, IDC_XNSSDKDEVICECTRL1, 3, CMultiChannelDlg::OnConnectFailedXnssdkdevicectrl1, VTS_I4 VTS_I4)
	ON_EVENT(CMultiChannelDlg, IDC_XNSSDKDEVICECTRL1, 10, CMultiChannelDlg::OnDeviceStatusChangedXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// If the application has failed in non-blocking connection using 
// ConnectNonBlock(), the OnConnectFailed event occurs. As Connect() 
// returns an immediate error message if failed, it does not trigger 
// this event. 
// -----------------------------------------------------------------------
void CMultiChannelDlg::OnConnectFailedXnssdkdevicectrl1(long nDeviceID, long nErrorCode)
{
	WLOGD(_T("Disconnected: deviceID=%d, errcode=[%d](%s)\n"), nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode));
	setBtnStatus(STATUS_DISCONNECTED);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the device status has changed. It occurs if the 
// application uses Connect() to connect or reconnect to the device after 
// disconnected. When reconnecting, the third argument nDeviceStatus is 
// true, all media must be reopened using ReopenAllStream().
// -----------------------------------------------------------------------
void CMultiChannelDlg::OnDeviceStatusChangedXnssdkdevicectrl1(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
	if (nErrorCode != ERR_SUCCESS || nDeviceStatus != 1)
	{
		return;
	}

	WLOGD(_T("Connected: deviceID=%d, display=%s, errcode=%d, deviceStatus=%d\n"),
		nDeviceID, m_ctrlXnsDevice.GetDisplayName(m_hDevice), nErrorCode, nDeviceStatus);
	
	setBtnStatus(STATUS_CONNECTED);
	m_comboChannel.SetCurSel(0);
}

void CMultiChannelDlg::OnBnClickedButtonConnect()
{
	UpdateData(TRUE);
	CString strIpAddress;
	BYTE a1, a2, a3, a4;
	m_ctrlIpAddress.GetAddress(a1, a2, a3, a4);
	strIpAddress.Format(_T("%d.%d.%d.%d"), a1,a2,a3,a4);

	// [ XNS ACTIVEX HELP ] 
	if(m_hDevice != 0)
	{
		// -----------------------------------------------------------------------
		// Cancels the memory space assigned for the device information by 
		// CreateDevice(). The device should be disconnected from the application
		// before this function is called.
		// -----------------------------------------------------------------------
		m_ctrlXnsDevice.ReleaseDevice(m_hDevice);
		m_hDevice = NULL;
	}

	long device_id = m_ctrlXnsDevice.CreateDeviceEx();
	m_hDevice = m_ctrlXnsDevice.GetDeviceHandle(device_id);

	if (m_hDevice == 0)
	{
		WLOGD(_T("CreateDevice() fail\n"));
		return;
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
		m_strPasswd,					// [in] Password
		m_nDeviceProtocol,
		m_nMediaProtocol
		);

	WLOGD(_T("Connect. ip=%s, port=%d, id=%s, password=%s\n"), strIpAddress, m_nPort, m_strId, m_strPasswd);

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
		WLOGD(_T("ConnectNonBlock() fail: errno=[%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
		setBtnStatus(STATUS_DISCONNECTED);
	}
}

void CMultiChannelDlg::OnBnClickedButtonDisconnect()
{
	// Disconnects from the device.
	Close();
	m_ctrlXnsDevice.Disconnect(m_hDevice);
	WLOGD(_T("Disconnect\n"));
	setBtnStatus(STATUS_DISCONNECTED);
}

void CMultiChannelDlg::OnBnClickedButtonOpen()
{
	UpdateData(TRUE);

	int index = m_comboChannel.GetCurSel();
	CString strVideo;
	m_comboChannel.GetLBText(index, strVideo);
	int nVideo = _ttoi(strVideo);

	Close();
	setWindow(nVideo);

	if( nVideo > MAXCHANNEL)
		nVideo = MAXCHANNEL;

	// DVR / NVR
	if (m_ctrlXnsDevice.GetControlType(m_hDevice, 1) & (XCTL_DVR | XCTL_NVR))
	{
		int nChannelCount = m_ctrlXnsDevice.GetControlCount(m_hDevice, XCTL_CAMERA);
		
		for(int i=0; i<nChannelCount && i<MAXCHANNEL && i<nVideo; i++)
		{
			int nControlID = m_ctrlXnsDevice.GetVideoControlID(m_hDevice, i+1, m_nProfileIndex+1);
			if (m_ctrlXnsDevice.GetControlCapability(m_hDevice, nControlID, XCTL_CAP_LIVE) &&
				m_ctrlXnsDevice.GetControlStatus(m_hDevice, nControlID, 1))
			{
				m_ctrlXnsDevice.OpenMedia(m_hDevice, nControlID, MEDIA_TYPE_LIVE, 0, 0, &m_hMediaSource[i]);
				WLOGW(_T("Open media...control id=[%d]\n"), nControlID);
				m_ptrXnsWindow[i]->Start(m_hMediaSource[i]);
			}
		}
		setBtnStatus(STATUS_OPEN);
	}
	// Network Camera / Encoder
	else if (m_ctrlXnsDevice.GetControlType(m_hDevice, 1) & (XCTL_NETCAM |XCTL_ENCODER))
	{
		int nProfileCount = m_ctrlXnsDevice.GetControlCount(m_hDevice, XCTL_VIDEO);
		
		for(int i=0; i<nProfileCount && i<nVideo; i++)
		{
			int nControlID = m_ctrlXnsDevice.GetVideoControlID(m_hDevice, m_nChannelIndex +1, i+1);
			if (m_ctrlXnsDevice.GetControlCapability(m_hDevice, nControlID, XCTL_CAP_LIVE) &&
				m_ctrlXnsDevice.GetControlStatus(m_hDevice, nControlID, 1))
			{
				m_ctrlXnsDevice.OpenMedia(m_hDevice, nControlID, MEDIA_TYPE_LIVE, 0, 0, &m_hMediaSource[i]);
				WLOGW(_T("Open media...control id=[%d]\n"), nControlID);
				m_ptrXnsWindow[i]->Start(m_hMediaSource[i]);
			}
		}
		setBtnStatus(STATUS_OPEN);
	}
}

void CMultiChannelDlg::OnBnClickedButtonClose()
{
	Close();
	WLOGW(_T("Close media...\n"));
	setBtnStatus(STATUS_CLOSE);
}

void CMultiChannelDlg::OnDestroy()
{
	Close();

	if( m_hDevice )
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Returns the connection status of the device.
		// -----------------------------------------------------------------------
		if( m_ctrlXnsDevice.GetDeviceStatus(m_hDevice) == XDEVICE_STATUS_CONNECTED )
		{
			m_ctrlXnsDevice.Disconnect(m_hDevice);
		}

		// -----------------------------------------------------------------------
		// Cancels the memory space assigned for the device information by 
		// CreateDevice(). The device should be disconnected from the application
		// before this function is called.
		// -----------------------------------------------------------------------
		m_ctrlXnsDevice.ReleaseDevice(m_hDevice);
	}

	CDialog::OnDestroy();
}

void CMultiChannelDlg::Close()
{
	for( int i=0; i<MAXCHANNEL; i++)
	{
		if(m_hMediaSource[i])
		{
			m_ptrXnsWindow[i]->Stop();
			m_ctrlXnsDevice.CloseMedia(m_hDevice, m_hMediaSource[i]);
			m_hMediaSource[i]=0;
		}
	}
}

void CMultiChannelDlg::setWindowPtr( void )
{
	m_ptrXnsWindow[0] = &m_ctrlXnsWindow1;
	m_ptrXnsWindow[1] = &m_ctrlXnsWindow2;
	m_ptrXnsWindow[2] = &m_ctrlXnsWindow3;
	m_ptrXnsWindow[3] = &m_ctrlXnsWindow4;
	m_ptrXnsWindow[4] = &m_ctrlXnsWindow5;
	m_ptrXnsWindow[5] = &m_ctrlXnsWindow6;
	m_ptrXnsWindow[6] = &m_ctrlXnsWindow7;
	m_ptrXnsWindow[7] = &m_ctrlXnsWindow8;
	m_ptrXnsWindow[8] = &m_ctrlXnsWindow9;
	m_ptrXnsWindow[9] = &m_ctrlXnsWindow10;
	m_ptrXnsWindow[10] = &m_ctrlXnsWindow11;
	m_ptrXnsWindow[11] = &m_ctrlXnsWindow12;
	m_ptrXnsWindow[12] = &m_ctrlXnsWindow13;
	m_ptrXnsWindow[13] = &m_ctrlXnsWindow14;
	m_ptrXnsWindow[14] = &m_ctrlXnsWindow15;
	m_ptrXnsWindow[15] = &m_ctrlXnsWindow16;

	m_ptrXnsWindow[0]->SetWindowPos(NULL,10,10,480,480,0);
	for( int i=1; i<16; i++)
		m_ptrXnsWindow[i]->ShowWindow(FALSE);
}

void CMultiChannelDlg::setWindow(int _nVideo)
{
	for( int i=0; i<MAXCHANNEL; i++)
		m_ptrXnsWindow[i]->ShowWindow(TRUE);

	int x = 10, y = 10;
	int ratio = sqrt((float)_nVideo);
	int nx = 480/ratio;
	int ny = 480/ratio;

	for (int i = 0 ; i<MAXCHANNEL ; i++)
	{
		if (i < _nVideo)
		{		
			m_ptrXnsWindow[i]->SetWindowPos(NULL, x, y, nx, ny, 0);	
			if ((i+1)%ratio == 0)
			{
				y += ny;
				x = 10;
			}
			else
				x += nx;
		}
		else
			m_ptrXnsWindow[i]->ShowWindow(FALSE);
	}
}

// Control button enable/disable
void CMultiChannelDlg::setBtnStatus(BUTTON_STATUS nStatus)
{
	bool conn = false, disconn = false, close = false, open = false, channel = false;
	switch(nStatus)
	{
	case STATUS_CONNECTED:
		disconn = true;
		open = true;
		channel = true;
		break;
	case STATUS_DISCONNECTED:
		conn = true;
		break;
	case STATUS_OPEN:
		disconn = true;
		close = true;
		break;
	case STATUS_CLOSE:
		disconn = true;
		open = true;
		channel = true;
		break;
	}

	// Connection Group
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(conn);
	GetDlgItem(IDC_COMBO_MODEL_LIST)->EnableWindow(conn);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PW)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PORT2)->EnableWindow(conn);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(conn);

	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(disconn);
	GetDlgItem(IDC_COMBO_CHANNEL)->EnableWindow(channel);
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(open);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(close);
	
	SetCheckSunapi();
}


void CMultiChannelDlg::OnCbnSelchangeComboModelList()
{
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
	SetCheckSunapi();
}

void CMultiChannelDlg::OnOK()
{
	//CDialogEx::OnOK();
}

void CMultiChannelDlg::SetCheckSunapi()
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


void CMultiChannelDlg::OnBnClickedCheckSunapi()
{
	SetCheckSunapi();
}
