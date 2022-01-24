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
// http://www.samsungsecuritypartner.com
///////////////////////////////////////////////////////////////////////////////////
// PtzDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ptz.h"
#include "PtzDlg.h"
#include "PresetDlg.h"

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
#define MESSAGE_BOX(...) do{\
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


// CPtzDlg dialog


CPtzDlg::CPtzDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPtzDlg::IDD, pParent)
	, m_strModelName(_T("Samsung NVR"))
	, m_nPort(554)
	, m_strId(_T("admin"))
	, m_strPasswd(_T("qwe123@@"))
	, m_hDevice(0)
	, m_hMediaSource(0)
	, m_nPtzSpeed(0)
	, m_bAreaZoom(0)
	, m_nStartX(0)
	, m_nStartY(0)
	, m_nEndX(0)
	, m_nEndY(0)
	, m_nControlId(4)
	, m_nPan(0)
	, m_nTilt(0)
	, m_nZoom(0)
	, m_bMenuControl(0)
	, m_bIsMouseDown(0)
	, m_nDeviceProtocol(0)
	, m_nMediaProtocol(0)
	, m_nHttpPort(80)
	, m_fPan(0)
	, m_fTilt(0)
	, m_fZoom(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	CString strMessage = _T("");
}

void CPtzDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_EDIT_LOG_WIN, m_ctrlEditLog);
	DDX_Slider(pDX, IDC_SLIDER_PTZ_SPEED, m_nPtzSpeed);
	DDV_MinMaxInt(pDX, m_nPtzSpeed, 1, 100);
	DDX_Text(pDX, IDC_EDIT_PAN, m_nPan);
	DDX_Text(pDX, IDC_EDIT_TILT, m_nTilt);
	DDX_Text(pDX, IDC_EDIT_ZOOM, m_nZoom);
	DDX_Control(pDX, IDC_COMBO_AUTOSCAN, m_ctrlAutoScan);
	DDX_Control(pDX, IDC_COMBO_AUTOPAN, m_ctrlAutoPan);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_nHttpPort);
	DDX_Text(pDX, IDC_EDIT_PAN2, m_fPan);
	DDX_Text(pDX, IDC_EDIT_TILT2, m_fTilt);
	DDX_Text(pDX, IDC_EDIT_ZOOM2, m_fZoom);
	DDX_Control(pDX, IDC_CHECK_SUNAPI, m_ctrlSunapi);
}

BEGIN_MESSAGE_MAP(CPtzDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CPtzDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CPtzDlg::OnBnClickedButtonDisconnect)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_AREAZOOM, &CPtzDlg::OnBnClickedCheckAreazoom)
	ON_BN_CLICKED(IDC_BUTTON_ZOOM_1X, &CPtzDlg::OnBnClickedButtonZoom1x)
	ON_BN_CLICKED(IDC_BUTTON_GET_PTZ, &CPtzDlg::OnBnClickedButtonGetPtz)
	ON_BN_CLICKED(IDC_BUTTON_SET_PTZ, &CPtzDlg::OnBnClickedButtonSetPtz)
	ON_BN_CLICKED(IDC_CHECK_MENU_ON, &CPtzDlg::OnBnClickedCheckMenuOn)
	ON_BN_CLICKED(IDC_BUTTON_MENU_UP, &CPtzDlg::OnBnClickedButtonMenuUp)
	ON_BN_CLICKED(IDC_BUTTON_MENU_DOWN, &CPtzDlg::OnBnClickedButtonMenuDown)
	ON_BN_CLICKED(IDC_BUTTON_MENU_LEFT, &CPtzDlg::OnBnClickedButtonMenuLeft)
	ON_BN_CLICKED(IDC_BUTTON_MENU_RIGHT, &CPtzDlg::OnBnClickedButtonMenuRight)
	ON_BN_CLICKED(IDC_BUTTON_MENU_ENTER, &CPtzDlg::OnBnClickedButtonMenuEnter)
	ON_BN_CLICKED(IDC_BUTTON_MENU_CANCEL, &CPtzDlg::OnBnClickedButtonMenuCancel)
	ON_BN_CLICKED(IDC_BUTTON_PRESET, &CPtzDlg::OnBnClickedButtonPreset)
	ON_CBN_SELCHANGE(IDC_COMBO_AUTOPAN, &CPtzDlg::OnCbnSelchangeComboAutopan)
	ON_CBN_SELCHANGE(IDC_COMBO_AUTOSCAN, &CPtzDlg::OnCbnSelchangeComboAutoscan)
	ON_BN_CLICKED(IDC_BUTTON_GET_PTZ_NORMALIZE, &CPtzDlg::OnBnClickedButtonGetPtzNormalize)
	ON_BN_CLICKED(IDC_BUTTON_SET_PTZ_NORMALIZE, &CPtzDlg::OnBnClickedButtonSetPtzNormalize)
	ON_BN_CLICKED(IDC_CHECK_SUNAPI, &CPtzDlg::OnBnClickedCheckSunapi)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CPtzDlg::OnCbnSelchangeComboModelList)
	ON_BN_CLICKED(IDC_BUTTON_DOWNRIGHT, &CPtzDlg::OnBnClickedButtonDownright)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, &CPtzDlg::OnBnClickedButtonSnap)
END_MESSAGE_MAP()


// CPtzDlg message handlers

BOOL CPtzDlg::OnInitDialog()
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

	m_facilID = __targv[1];

	// TODO: Add extra initialization here
	m_ctrlIpAddress.SetAddress(192,168,85,87);

	GetDlgItem(IDC_BUTTON_UP)->SetWindowTextW(_T("↑"));
	GetDlgItem(IDC_BUTTON_UPRIGHT)->SetWindowTextW(_T("↗"));
	GetDlgItem(IDC_BUTTON_UPLEFT)->SetWindowTextW(_T("↖"));
	GetDlgItem(IDC_BUTTON_DOWN)->SetWindowTextW(_T("↓"));
	GetDlgItem(IDC_BUTTON_DOWNRIGHT)->SetWindowTextW(_T("↘"));
	GetDlgItem(IDC_BUTTON_DOWNLEFT)->SetWindowTextW(_T("↙"));
	GetDlgItem(IDC_BUTTON_LEFT)->SetWindowTextW(_T("←"));
	GetDlgItem(IDC_BUTTON_RIGHT)->SetWindowTextW(_T("→"));
	m_nPtzSpeed = 50;
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
	if (nRet != ERR_SUCCESS)
	{
		WLOGD(_T("Initialize() fail: errno=[%d]\n"), nRet);
	}
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
	m_hDevice = m_ctrlXnsDevice.CreateDevice(1);
	if (m_hDevice == 0)
	{
		WLOGD(_T("CreateDevice() fail\n"));
	}
	
#if 0
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


	int idx = m_ctrlModelList.FindStringExact(0, _T("Samsung Network Camera/Encoder"));
	if(idx != CB_ERR)
	{
		m_ctrlModelList.SetCurSel(idx);
		m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
		
		
		
		UpdateData(FALSE);
	}
	
	
// 	int idx = m_ctrlModelList.FindStringExact(0, _T("SNP-3301"));
// 	if(idx != CB_ERR) {
// 		m_ctrlModelList.SetCurSel(idx);
// 		m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
// 		UpdateData(FALSE);
// 	}

	// Scan combo list
	m_ctrlAutoScan.AddString(_T("None"));
	for(int i=0;i<6;i++)
	{
		CString strIndex;
		strIndex.Format(_T("Scan [%d]"), i+1);
		m_ctrlAutoScan.AddString(strIndex);
	}
	m_ctrlAutoScan.SetCurSel(0);

	// auto pan combo list
	m_ctrlAutoPan.AddString(_T("None"));
	for(int i=0;i<4;i++)
	{
		CString strIndex;
		strIndex.Format(_T("Auto pan[%d]"), i+1);
		m_ctrlAutoPan.AddString(strIndex);
	}
	m_ctrlAutoPan.SetCurSel(0);

	setBtnStatus(SL_STATUS_DISCONNECTED);
#endif

	OnBnClickedButtonConnect();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPtzDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPtzDlg::OnPaint()
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
HCURSOR CPtzDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPtzDlg::OnBnClickedButtonConnect()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strIpAddress;
	BYTE a1, a2, a3, a4;
#if 1
	m_saveIni = "c:\\WKIT-S\\cctv-setting.ini";

	TCHAR szRet[1024];
	char szTemp[1024];

	::GetPrivateProfileString(_T("FACILITY"), _T("facilID"), _T(""), szRet, 1024, m_saveIni);
    m_facilID = szRet;

	//AfxMessageBox((CString)m_facilID);
	::GetPrivateProfileString(_T("FACILITY"), _T("connectIp"), _T(""), szRet, 1024, m_saveIni);
	WideCharToMultiByte(CP_ACP, 0, szRet, 1024, szTemp, 1024, NULL, NULL);

	int a, b, c, d;
	char *str;
	str = strrchr(szTemp, '.');

	if(str != NULL)
	{
		*str++ = NULL;
		d = atoi(str);
	}

	str = strrchr(szTemp, '.');

	if(str != NULL)
	{
		*str++ = NULL;
		c = atoi(str);
	}

	str = strrchr(szTemp, '.');
	if(str != NULL)
	{
		*str++ = NULL;
		b = atoi(str);
	}
	a = atoi(szTemp);

	//sprintf(szTemp, "%d, %d, %d, %d", a, b, c, d);
	//AfxMessageBox((CString)szTemp);


	m_ctrlIpAddress.SetAddress((BYTE)a,(BYTE)b,(BYTE)c,(BYTE)d);
	//m_ctrlIpAddress.SetAddress(192, 168, 3, 100);

	m_nPtzSpeed = 50;

	::GetPrivateProfileString(_T("FACILITY"), _T("connectPort"), _T(""), (szRet), 1024, m_saveIni);
	WideCharToMultiByte(CP_ACP, 0, szRet, 1024, szTemp, 1024, NULL, NULL);

	m_nPort = atoi(szTemp);
	//AfxMessageBox((CString)szTemp);

	//m_ctrlIpAddress.GetAddress(a1, a2, a3, a4);
	//strIpAddress.Format(_T("%d.%d.%d.%d"), a1, a2, a3, a4);

	strIpAddress.Format(_T("%d.%d.%d.%d"), a, b, c, d);

	::GetPrivateProfileString(_T("FACILITY"), _T("userID"), _T(""), (szRet), 1024, m_saveIni);
	WideCharToMultiByte(CP_ACP, 0, szRet, 1024, szTemp, 1024, NULL, NULL);
	m_strId = szTemp;
	//strcpy(m_strId, szTemp);

	::GetPrivateProfileString(_T("FACILITY"), _T("passWD"), _T(""), (szRet), 1024, m_saveIni);
	WideCharToMultiByte(CP_ACP, 0, szRet, 1024, szTemp, 1024, NULL, NULL);
	m_strPasswd = szTemp;
	//strcpy(m_strPasswd, szTemp);

#endif
	//m_ctrlIpAddress.GetAddress(a1, a2, a3, a4);
	//strIpAddress.Format(_T("%d.%d.%d.%d"), a1, a2, a3, a4);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Sets the device informaiton so that the application can connect 
	// to the device.
	// -----------------------------------------------------------------------
// 	m_ctrlXnsDevice.SetConnectionInfo(
// 		m_hDevice,					// [in] Device handle
// 		_T("Samsung"),				// [in] Fixed as 'Samsung'
// 		m_strModelName,				// [in] Name of model to connect to. The maximum length allowed is 126-byte.
// 		XADDRESS_IP, strIpAddress,	// [in] Address type, actual address according to addresstype.
// 		m_nPort, 0,					// [in] Port number, port number for web access	
// 		m_strId, m_strPasswd		// [in] Login ID, password
// 		);

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

	WLOGD(_T("Connect. model=%s, ip=%s[type=%d], port=%d, http port=%d, id=%s, password=%s, protocol=%d\n"), 
		m_strModelName, strIpAddress, XADDRESS_IP, m_nPort, m_nHttpPort, m_strId, m_strPasswd, m_nDeviceProtocol);

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
		setBtnStatus(SL_STATUS_DISCONNECTED);
	}
}

void CPtzDlg::OnBnClickedButtonDisconnect()
{
	// TODO: Add your control notification handler code here
	if( !m_hMediaSource ) 
	{
		WLOGD(_T("May be device is not connected\n"));
		setBtnStatus(SL_STATUS_DISCONNECTED);
		return;
	}
	else
	{
		WLOGW(_T("Stop receiving media stream data\n"));
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Stops receiving the stream data from the media source handle.  
		// -----------------------------------------------------------------------
		m_ctrlXnsWindow.Stop();

		// Terminates transferring media stream data from the device. The media 
		// stream data will be separated by hMediaSource 
		// (i.e., phMediaSource of OpenMedia()).

		m_ctrlXnsDevice.CloseMedia(m_hDevice, m_hMediaSource);
	}

	// Disconnects from the device.
	m_ctrlXnsDevice.Disconnect(m_hDevice);
	WLOGD(_T("Disconnect\n"));

	m_hMediaSource = 0;
	setBtnStatus(SL_STATUS_DISCONNECTED);

}


BEGIN_EVENTSINK_MAP(CPtzDlg, CDialog)
	ON_EVENT(CPtzDlg, IDC_XNSSDKDEVICECTRL, 10, CPtzDlg::OnDeviceStatusChangedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CPtzDlg, IDC_XNSSDKDEVICECTRL, 3, CPtzDlg::OnConnectFailedXnssdkdevicectrl, VTS_I4 VTS_I4)
	ON_EVENT(CPtzDlg, IDC_XNSSDKWINDOWCTRL, 5, CPtzDlg::OnLButtonDownXnssdkwindowctrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CPtzDlg, IDC_XNSSDKWINDOWCTRL, 6, CPtzDlg::OnLButtonUpXnssdkwindowctrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CPtzDlg, IDC_XNSSDKWINDOWCTRL, 11, CPtzDlg::OnMouseMoveXnssdkwindowctrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CPtzDlg, IDC_XNSSDKDEVICECTRL, 31, CPtzDlg::OnGetPtzPosXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CPtzDlg, IDC_XNSSDKDEVICECTRL, 6, CPtzDlg::OnGetPresetListXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CPtzDlg, IDC_XNSSDKDEVICECTRL, 38, CPtzDlg::OnGetHPtzListXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CPtzDlg, IDC_XNSSDKDEVICECTRL, 67, CPtzDlg::OnGetPtzPosNormalizeXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4)
END_EVENTSINK_MAP()


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the device status has changed. It occurs if the 
// application uses Connect() to connect or reconnect to the device after 
// disconnected. When reconnecting, the third argument nDeviceStatus is 
// true, all media must be reopened using ReopenAllStream().
// -----------------------------------------------------------------------
void CPtzDlg::OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
	// TODO: Add your message handler code here
	if (nErrorCode != ERR_SUCCESS || nDeviceStatus != 1)
	{
		return;
	}

	WLOGD(_T("Connected: deviceID=%d, errcode=%d, deviceStatus=%d\n"),
		nDeviceID, nErrorCode, nDeviceStatus);
	setBtnStatus(SL_STATUS_CONNECTED);
	
		// CCTV error report .....
	WritePrivateProfileString(_T("FACILITY"), _T("result"), _T("NO-ERR"), m_saveIni);

	if(m_hMediaSource) 
	{
		WLOGD(_T("Media stream was already opend\n"));
		return;
	}
	
	int xret = m_ctrlXnsDevice.GetControlType(m_hDevice, 1);

	WLOGD(_T("Open media stream:%d\n"), xret);

 	int controlID = m_ctrlXnsDevice.GetVideoControlID(m_hDevice, 1, 1);
  	m_ctrlXnsDevice.OpenMedia(
  		m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
  		controlID,					// [in] Control ID of video control module. 
  		MEDIA_TYPE_LIVE,	// [in] Media type.
  		0,					// [in] Play start time. Format: 4-byte time_t.
  		0,					// [in] Play end time. Format: 4-byte time_t.
  		&m_hMediaSource		// [out] Media stream ID. This is needed for controlling 
  							//       the media stream and also used as a parameter 
  							//       of XnsSdkWindow::Start().
  		);
 
 	
 	m_ctrlXnsWindow.Start(m_hMediaSource);

	m_nControlId = controlID;
	WLOGD(_T("Dcontrol id = %d\n"), m_nControlId);

}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// If the application has failed in non-blocking connection using 
// ConnectNonBlock(), the OnConnectFailed event occurs. As Connect() 
// returns an immediate error message if failed, it does not trigger 
// this event. 
// -----------------------------------------------------------------------
void CPtzDlg::OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode)
{
	// TODO: Add your message handler code here
	WLOGD(_T("Disconnected: deviceID=%d, errcode=[%d](%s)\n"),
			nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode));

	MESSAGE_BOX(_T("Connection fail.."));

	// CCTV error report .....
	WritePrivateProfileString(_T("FACILITY"), _T("result"), _T("ERR"), m_saveIni);

	setBtnStatus(SL_STATUS_DISCONNECTED);
}



void CPtzDlg::setBtnStatus(SLIVE_BUTTON_STATUS nStatus)
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
	}

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(conn);
	GetDlgItem(IDC_COMBO_MODEL_LIST)->EnableWindow(conn);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PW)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PORT2)->EnableWindow(conn);

	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(disconn);

	SetCheckSunapi();
}


void CPtzDlg::OnDestroy()
{
	if( m_hDevice )
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Stops receiving the stream data from the media source handle.  
		// -----------------------------------------------------------------------
		if( m_hMediaSource )
		{
			m_ctrlXnsWindow.Stop();

			// Terminates transferring media stream data from the device. 
			// The media stream data will be separated by hMediaSource 
			// (i.e., phMediaSource of OpenMedia()).
			m_ctrlXnsDevice.CloseMedia( m_hDevice, m_hMediaSource );
		}

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

void CPtzDlg::moveCamera(const int nCommand)
{
	long ret;
	UpdateData(TRUE);
	WLOGD(_T("MoveCamera, command=[%d], speed=%d\n"), nCommand, m_nPtzSpeed);

	// Returns the capabilities of the control module.
	BOOL bIsCap = m_ctrlXnsDevice.GetControlCapability(m_hDevice, m_nControlId, XCTL_CAP_PTZ_PAN);
	WLOGD(_T("is_ptz_support=%d\n"), bIsCap);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Moves the camera to the predefined PTZ position. This function is 
	// valid as long as the application is receiving media stream from the 
	// camera. 
	// -----------------------------------------------------------------------
	//	Command			Value	Description
	// -----------------------------------------------------------------------
	//	XPTZ_UP			1		Tilt up
	//	XPTZ_DOWN		2		Tilt down
	//	XPTZ_LEFT		3		Pan left
	//	XPTZ_RIGHT		4		Pan right
	//	XPTZ_UPLEFT		5		Tilt up and pan left
	//	XPTZ_UPRIGHT	6		Tilt up and pan right
	//	XPTZ_DOWNLEFT	7		Tilt down and pan left
	//	XPTZ_DOWNRIGHT	8		Tilt down and pan right
	//	XPTZ_ZOOMIN		9		Zoom in
	//	XPTZ_ZOOMOUT	10		Zoom out
	//	XPTZ_STOP		11		Stop the PTZ moving
	//	XPTZ_FOCUS_NEAR	12		Focus near
	//	XPTZ_FOCUS_FAR	13		Focus far
	//	XPTZ_FOCUS_STOP	14		Stop focus moving
	//	XPTZ_IRIS_OPEN	15		Open iris
	//	XPTZ_IRIS_CLOSE	16		Close iris
	// -----------------------------------------------------------------------
	if (bIsCap)
	{
		ret = m_ctrlXnsDevice.ControlPtz(
			m_hDevice,		// [in] Device handle. This value is returned from CreateDevice().
			m_nControlId,	// [in] Control ID.
			nCommand,		// [in] PTZ command 
			m_nPtzSpeed		// [in] If nPtzCommand is a speed-related command, 
							// this value indicates the PTZ operation speed. 
							// (1~100) This value is valid only if the camera 
							// supports the XCTL_CAP_PTZ_SPEED capability.
			);
		WLOGD(_T("ControlPtz():: controlID=%d, command=%d, speed=%d, ret=%d(%s)\n"), 
			m_nControlId, nCommand, m_nPtzSpeed, ret, m_ctrlXnsDevice.GetErrorString(ret));
	}
	else
	{
		ret = m_ctrlXnsDevice.ControlPtz(m_hDevice, m_nControlId, nCommand, 30);
		WLOGD(_T("ControlPtz():: controlID=%d, command=%d, speed=%d, ret=%d(%s)\n"), 
			m_nControlId, nCommand, 30, ret, m_ctrlXnsDevice.GetErrorString(ret));
	}
}


// Read mouse event for PTZ functions
BOOL CPtzDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rect;
	if(pMsg->message == WM_LBUTTONDOWN) 
	{
		CButton *pButton = (CButton *)GetDlgItem(IDC_BUTTON_ZOOM_IN);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
		{
			moveCamera(XPTZ_ZOOMIN);
		}

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_ZOOM_OUT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
		{
			moveCamera(XPTZ_ZOOMOUT);
		}

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_UP);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
		{
			moveCamera(XPTZ_UP);
		}

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_UPLEFT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
		{
			moveCamera(XPTZ_UPLEFT);
		}

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_UPRIGHT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
		{
			moveCamera(XPTZ_UPRIGHT);
		}

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_DOWN);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
		{
			moveCamera(XPTZ_DOWN);
		}

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_DOWNLEFT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
		{
			moveCamera(XPTZ_DOWNLEFT);
		}

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_DOWNRIGHT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
		{
			moveCamera(XPTZ_DOWNRIGHT);
		}

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_LEFT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
		{
			moveCamera(XPTZ_LEFT);
		}

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_RIGHT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
		{
			moveCamera(XPTZ_RIGHT);
		}
	}
	else if(pMsg->message == WM_LBUTTONUP) 
	{
		bool is_stop = false;

		CButton *pButton = (CButton *)GetDlgItem(IDC_BUTTON_ZOOM_IN);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
			is_stop = true;

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_ZOOM_OUT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
			is_stop = true;

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_UP);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
			is_stop = true;

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_UPLEFT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
			is_stop = true;

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_UPRIGHT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
			is_stop = true;

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_DOWN);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
			is_stop = true;

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_DOWNLEFT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
			is_stop = true;

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_DOWNRIGHT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
			is_stop = true;

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_LEFT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
			is_stop = true;

		pButton = (CButton *)GetDlgItem(IDC_BUTTON_RIGHT);
		pButton->GetWindowRect(rect); 
		if(rect.PtInRect(pMsg->pt))
			is_stop = true;

		if(is_stop)
		{
			moveCamera(XPTZ_STOP);
		}
	}


	return CDialog::PreTranslateMessage(pMsg);
}

void CPtzDlg::OnBnClickedCheckAreazoom()
{
	// TODO: Add your control notification handler code here
	m_bAreaZoom = !m_bAreaZoom;
	WLOGD(_T("Area Zoom setting=%d\n"), m_bAreaZoom);
}




// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if a left button on the mouse is pressed in 
// XnSdkWindow. This event is valid only if both XnsSdkWindow 
// handle and parent window handle are reset to Null.  
//
// Parameters
// - nFlags
// [in] Same as the flag used in window message by WM_MOUSEMOVE
// * MK_CONTROL: [Ctrl] key is pressed.
// * MK_MBUTTON: Middle button on the mouse is pressed.
// * MK_RBUTTON: Right button on the mouse is pressed.
// - nX
// [in] X coordinate of the mouse pointer.
// - nY
// [in] Y coordinate of the mouse pointer.
// -----------------------------------------------------------------------
void CPtzDlg::OnLButtonDownXnssdkwindowctrl(long nFlags, long nX, long nY)
{
	m_bIsMouseDown = true;
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
	m_ctrlXnsWindow.DrawRect(
		m_nStartX,			// [in] X-axis coordinate of top left.
		m_nStartY,			// [in] Y-axis coordinate of top left.
		0,					// [in] Width of the rectangle.
		0					// [in] Height of the rectangle.
		);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the left mouse button is pressed and released 
// in XnSdkWindow. This event is valid only if both XnsSdkWindow 
// handle and parent window handle are reset to Null.
// -----------------------------------------------------------------------
void CPtzDlg::OnLButtonUpXnssdkwindowctrl(long nFlags, long nX, long nY)
{
	m_bIsMouseDown = false;
	// TODO: Add your message handler code here
	if (!m_bAreaZoom) 
		return;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns the width of the source image. 
	// Returns the height of the source image.
	// -----------------------------------------------------------------------
	long nImageWidth = m_ctrlXnsWindow.GetImageWidth();
	long nImageHeight = m_ctrlXnsWindow.GetImageHeight();

	CRect rt; 
	m_ctrlXnsWindow.GetClientRect(rt);
	long nWindowWidth = rt.Width();
	long nWindowHeight = rt.Height();

	m_nEndX = nX;
	m_nEndY = nY;

	WLOGW(_T("On LButtonUp XNSWindow flag=%d, x=%d, y=%d, imagew=%d, imgaeh=%d, windoww=%d, windowh=%d\n"), 
		nFlags, nX, nY, nImageWidth, nImageHeight, nWindowWidth, nWindowHeight);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Deletes the existing rectangle on the screen.
	// -----------------------------------------------------------------------
	m_ctrlXnsWindow.ClearDraw();

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

	if(nRet != ERR_SUCCESS) 
	{
		WLOGD(_T("AreaZoom() fail:: nRet = [%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}

}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the mouse pointer is moving. This event is valid 
// only if both XnsSdkWindow handle and parent window handle are 
// reset to Null.
// -----------------------------------------------------------------------
void CPtzDlg::OnMouseMoveXnssdkwindowctrl(long nFlags, long nX, long nY)
{
	// TODO: Add your message handler code here
	if (!m_bAreaZoom) 
		return;

	if (!m_bIsMouseDown)
		return;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Uses the blue brush to draw a rectangle on XnsSdkWindow. 
	// If this function is called more than twice, the existing rectangle 
	// will be replaced with a new one.
	// -----------------------------------------------------------------------
	m_ctrlXnsWindow.DrawRect(
		m_nStartX,			// [in] X-axis coordinate of top left.
		m_nStartY,			// [in] Y-axis coordinate of top left.
		nX-m_nStartX,		// [in] Width of the rectangle.
		nY-m_nStartY		// [in] Height of the rectangle.
		);
}

void CPtzDlg::OnBnClickedButtonZoom1x()
{
	// TODO: Add your control notification handler code here

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Performs the zoom-1x. This function is valid as long as the application 
	// is receiving media stream from the camera.
	// Parameters
	// - hDevice
	//   [in] Device handle. This value is returned from CreateDevice().
	// - nControlID
	//	 [in] Control ID.
	// -----------------------------------------------------------------------
	long nRet = m_ctrlXnsDevice.Zoom1X(m_hDevice, m_nControlId);
	if(nRet != ERR_SUCCESS) 
	{
		WLOGD(_T("AreaZoom() fail:: nRet = [%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
}

void CPtzDlg::OnBnClickedButtonGetPtz()
{
	// TODO: Add your control notification handler code here

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns an absolute coordinate of the camera, is available when 
	// application receives media stream from the camera. 
	// The value themselves could be read by using OnGetPtzPos event handler. 
	// -----------------------------------------------------------------------
	long nRet = m_ctrlXnsDevice.GetPtzPos(m_hDevice, m_nControlId);
	if(nRet != ERR_SUCCESS) 
	{
		WLOGD(_T("GetPtzPos() fail:: nRet = [%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
}

void CPtzDlg::OnBnClickedButtonSetPtz()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Change the absolute coordinate of the camera, 
	// is available when application receives media stream from the camera.
	// -----------------------------------------------------------------------
	long nRet = m_ctrlXnsDevice.SetPtzPos(
		m_hDevice, 
		m_nControlId, 
		m_nPan, 
		m_nTilt, 
		m_nZoom
		);
	if(nRet != ERR_SUCCESS) 
	{
		WLOGD(_T("SetPtzPos() fail:: nRet = [%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
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
void CPtzDlg::OnGetPtzPosXnssdkdevicectrl(
	long nDeviceID, 
	long nControlID, 
	long nErrorCode, 
	long nPan, 
	long nTilt, 
	long nZoom
	)
{
	// TODO: Add your message handler code here
	WLOGD(_T("Get Ptz Position device_id=%d, pan=%d, tilt=%d, zoom=%d, ret=%d\n"),
		nDeviceID, nPan, nTilt, nZoom, nErrorCode);

	m_nPan = nPan;
	m_nTilt = nTilt; 
	m_nZoom = nZoom;
	CString strTmp;
	strTmp.Format(_T("%d"), nPan);
	GetDlgItem(IDC_EDIT_PAN)->SetWindowText(strTmp);
	strTmp.Format(_T("%d"), nTilt);
	GetDlgItem(IDC_EDIT_TILT)->SetWindowText(strTmp);
	strTmp.Format(_T("%d"), nZoom);
	GetDlgItem(IDC_EDIT_ZOOM)->SetWindowText(strTmp);
}



void CPtzDlg::OnBnClickedCheckMenuOn()
{
	// TODO: Add your control notification handler code here
	m_bMenuControl = !m_bMenuControl;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns the capabilities of the control module.
	// -----------------------------------------------------------------------
	long bCap = m_ctrlXnsDevice.GetControlCapability(
		m_hDevice,				// Device handle
		m_nControlId,			// Control ID
		XCTL_CAP_CAM_MENU		// Capability ID
		);
	if (!bCap)
	{
		WLOGD(_T("No capability for the menu control\n"));
		return;
	}


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Controls the OSD menus of the camera. This function is valid as long 
	// as the application is receiving media stream from the camera.(ex.SND-5080)
	// -----------------------------------------------------------------------
	//  Command			Value	Description
	// -----------------------------------------------------------------------
	//	XMENU_UP		1		Menu up.
	//	XMENU_DOWN		2		Menu down.
	//	XMENU_LEFT		3		Menu left or prev menu.
	//	XMENU_RIGHT		4		Menu right or next menu.
	//	XMENU_ENTER		5		Menu enter, select.
	//	XMENU_ON		6		Menu on.
	//	XMENU_OFF		7		Menu off.
	//	XMENU_CANCEL	8		Cancel (Changes are not saved).
	// -----------------------------------------------------------------------
	int nRet = m_ctrlXnsDevice.ControlMenu(
		m_hDevice,
		m_nControlId,
		(m_bMenuControl?XMENU_ON:XMENU_OFF)
		);
	if (nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ControlMenu() fail: ret=[%d](%s)\n"), 
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
}

void CPtzDlg::OnBnClickedButtonMenuUp()
{
	// TODO: Add your control notification handler code here
	int nRet = m_ctrlXnsDevice.ControlMenu(
		m_hDevice,
		m_nControlId,
		XMENU_UP
		);
	if (nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ControlMenu() fail: ret=[%d](%s)\n"), 
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
}

void CPtzDlg::OnBnClickedButtonMenuDown()
{
	// TODO: Add your control notification handler code here
	int nRet = m_ctrlXnsDevice.ControlMenu(
		m_hDevice,
		m_nControlId,
		XMENU_DOWN
		);
	if (nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ControlMenu() fail: ret=[%d](%s)\n"), 
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
}

void CPtzDlg::OnBnClickedButtonMenuLeft()
{
	// TODO: Add your control notification handler code here
	int nRet = m_ctrlXnsDevice.ControlMenu(
		m_hDevice,
		m_nControlId,
		XMENU_LEFT
		);
	if (nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ControlMenu() fail: ret=[%d](%s)\n"), 
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
}

void CPtzDlg::OnBnClickedButtonMenuRight()
{
	// TODO: Add your control notification handler code here
	int nRet = m_ctrlXnsDevice.ControlMenu(
		m_hDevice,
		m_nControlId,
		XMENU_RIGHT
		);
	if (nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ControlMenu() fail: ret=[%d](%s)\n"), 
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
}

void CPtzDlg::OnBnClickedButtonMenuEnter()
{
	// TODO: Add your control notification handler code here
	int nRet = m_ctrlXnsDevice.ControlMenu(
		m_hDevice,
		m_nControlId,
		XMENU_ENTER
		);
	if (nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ControlMenu() fail: ret=[%d](%s)\n"), 
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
}

void CPtzDlg::OnBnClickedButtonMenuCancel()
{
	// TODO: Add your control notification handler code here
	int nRet = m_ctrlXnsDevice.ControlMenu(
		m_hDevice,
		m_nControlId,
		XMENU_CANCEL
		);
	if (nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ControlMenu() fail: ret=[%d](%s)\n"), 
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// Open a dialog for preset functions
// -----------------------------------------------------------------------
void CPtzDlg::OnBnClickedButtonPreset()
{
	
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Gets the preset list. A preset is a user-defined position of the camera. 
	// The number of presets available varies depending on the model. 
	// However, the XNS ActiveX library can support up to 20 presets. 
	// The result of this function will be forwarded by the OnGetPresetList 
	// event. This function is valid as long as the application is receiving 
	// media stream from the camera.
	// -----------------------------------------------------------------------
	int nRet = m_ctrlXnsDevice.GetPresetList(m_hDevice, m_nControlId);
	//int nRet = m_ctrlXnsDevice.GetHPtzList(m_hDevice, m_nControlId, XHPTZ_SCAN);
	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("GetPresetList() fail. ret=[%d](%s)\n"), 
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
		return;
	}

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
void CPtzDlg::OnGetPresetListXnssdkdevicectrl(long nDeviceID, long nControlID, long hPresetListList)
{
	// TODO: Add your message handler code here
	long nNumber;
	long nPresetCount;
	CString strPresetName;
	CMap< int, int, CString, CString > cmPresetList;

	// Gets the number of presets defined. 
	// This value is used to get the preset name and information. 
	// This function is valid as long as the application is receiving 
	// media stream from the camera.
	nPresetCount = m_ctrlXnsDevice.GetPresetCount(hPresetListList);
	WLOGD(_T("Event OnGetPresetList.. nDevice[%d], nControlId[%d], PresetCount[%d]\n"),
		nDeviceID, nControlID, nPresetCount);

	for( int i=0 ; i<nPresetCount ; i++ )
	{
		// Returns the preset number and name corresponding to the 
		// given index in the preset list of XnsSdkDevice. 
		strPresetName = m_ctrlXnsDevice.GetPreset(
			hPresetListList,	// [in] Handle of the preset list. 
			i,					// [in] Preset index to get the preset information (start with 1).
			&nNumber			// [out] Preset index specified in XnsSdkDevice.
			);
		WLOGD(_T("PresetList[%02d] name=[%s]\n"), nNumber, strPresetName);
		cmPresetList.SetAt(nNumber, strPresetName);
	}

	PresetDlg dlg(&m_ctrlXnsDevice, m_hDevice, m_nControlId, &cmPresetList);
	INT_PTR nResult = dlg.DoModal();
}

void CPtzDlg::OnCbnSelchangeComboAutoscan()
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctrlAutoScan.GetCurSel();
	if (nIndex == 0)
	{
		// stop action
		moveCamera(XPTZ_UP);
		return;
	}


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Performs operations of Preset, Autopan, Scan and Pattern. 
	// This function is valid as long as the application is receiving 
	// media stream from the camera.
	// 
	// Parameters
	// - hDevice
	//	 [in] Device handle. This value is returned from CreateDevice().
	//	nControlID
	//	 [in] Control ID.
	// - nType
	//	 [in] Camera operations.
	//	 * XHPTZ_PRESET(1): Preset
	//	 * XHPTZ_AUTOPAN(2): Autopan(Swing)
	//	 * XHPTZ_SCAN(3): Scan
	//	 * XHPTZ_PATTERN(4): Pattern
	// - nNumber
	//	 [in] Index of camera's list of features (Preset, AutoPan, Scan, Pattern). 
	//        (start with 1) For instance, if multiple presets are defined, 
	//        a list of presets will be created and the user should specify 
	//        the index of the list.
	// -----------------------------------------------------------------------
	long nRet = m_ctrlXnsDevice.ExecuteHPtz(
		m_hDevice,
		m_nControlId,
		XHPTZ_TOUR,
		nIndex
		);
	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ExecuteHPtz() failed: ret=[%d](%s)\n"),
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
		return;
	}
	WLOGD(_T("Scanning index=[%d]\n"), nIndex);
}


void CPtzDlg::OnCbnSelchangeComboAutopan()
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctrlAutoPan.GetCurSel();
	if (nIndex == 0)
	{
		// stop action
		moveCamera(XPTZ_UP);
		return;
	}

	long nRet = m_ctrlXnsDevice.ExecuteHPtz(
		m_hDevice,
		m_nControlId,
		XHPTZ_AUTOPAN,
		nIndex
		);
	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ExecuteHPtz() failed: ret=[%d](%s)\n"),
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
		return;
	}
	WLOGD(_T("Auto panning index=[%d]\n"), nIndex);
}


void CPtzDlg::OnGetHPtzListXnssdkdevicectrl(long nDeviceID, long nControlID, long nType, long hHptzList)
{
	// TODO: Add your message handler code here
	long nNumber;
	long nPresetCount;
	CString strHptzName;
	CMap< int, int, CString, CString > cmPresetList;

	// Gets the number of presets defined. 
	// This value is used to get the preset name and information. 
	// This function is valid as long as the application is receiving 
	// media stream from the camera.
	nPresetCount = m_ctrlXnsDevice.GetPresetCount(hHptzList);
	WLOGD(_T("Event OnGetHPtzList.. nDevice[%d], nControlId[%d], nType[%d], PresetCount[%d]\n"),
		nDeviceID, nControlID, nType, nPresetCount);

	for( int i=0 ; i<nPresetCount ; i++ )
	{
		// Returns the preset number and name corresponding to the 
		// given index in the preset list of XnsSdkDevice. 
		strHptzName = m_ctrlXnsDevice.GetPreset(
			hHptzList,	// [in] Handle of the preset list. 
			i,					// [in] Preset index to get the preset information (start with 1).
			&nNumber			// [out] Preset index specified in XnsSdkDevice.
			);
		WLOGD(_T("HPtzList[%02d] name=[%s]\n"), nNumber, strHptzName);
	}
}


void CPtzDlg::OnBnClickedButtonGetPtzNormalize()
{
	long nRet = m_ctrlXnsDevice.GetPtzPosNormalize(m_hDevice, m_nControlId);
	if(nRet != ERR_SUCCESS) 
	{
		WLOGD(_T("GetPtzPos() fail:: nRet = [%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
}


void CPtzDlg::OnBnClickedButtonSetPtzNormalize()
{
	UpdateData(true);

	long nRet = m_ctrlXnsDevice.SetPtzPosNormalize(
		m_hDevice, 
		m_nControlId, 
		m_fPan, 
		m_fTilt, 
		m_fZoom
		);
	if(nRet != ERR_SUCCESS) 
	{
		WLOGD(_T("SetPtzPos() fail:: nRet = [%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}
}


void CPtzDlg::OnGetPtzPosNormalizeXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode, float fPan, float fTilt, float fZoom)
{
	WLOGD(_T("Get Ptz Position device_id=%d, pan=%f, tilt=%f, zoom=%f, ret=%d\n"),
		nDeviceID, fPan, fTilt, fZoom, nErrorCode);

	m_fPan = fPan;
	m_fTilt = fTilt; 
	m_fZoom = fZoom;
	CString strTmp;
	strTmp.Format(_T("%f"), fPan);
	GetDlgItem(IDC_EDIT_PAN2)->SetWindowText(strTmp);
	strTmp.Format(_T("%f"), fTilt);
	GetDlgItem(IDC_EDIT_TILT2)->SetWindowText(strTmp);
	strTmp.Format(_T("%f"), fZoom);
	GetDlgItem(IDC_EDIT_ZOOM2)->SetWindowText(strTmp);
}


void CPtzDlg::OnOK()
{
	//CDialog::OnOK();
}


void CPtzDlg::OnBnClickedCheckSunapi()
{
	SetCheckSunapi();
}


void CPtzDlg::SetCheckSunapi()
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

void CPtzDlg::OnCbnSelchangeComboModelList()
{
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
	SetCheckSunapi();
}

void CPtzDlg::OnBnClickedButtonDownright()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	WLOGD(_T("OnBnClickedButtonDownright \n"));

}

void CPtzDlg::OnBnClickedButtonSnap()
{
	WLOGD(_T("OnBnClickedButtonSnap \n"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static int a=1;
	CString filename;

	BROWSEINFO BrInfo;
	TCHAR szBuffer[512];                                      // 경로저장 버퍼 

	::ZeroMemory(&BrInfo, sizeof(BROWSEINFO));
	::ZeroMemory(szBuffer, 512);

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.lpszTitle = _T("파일이 저장될 폴더를 선택하세요");
	BrInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder(&BrInfo);
	::SHGetPathFromIDList(pItemIdList, szBuffer);               // 파일경로 읽어오기

	CTime t1 = CTime::GetCurrentTime();
	CString strTimeData = t1.Format("%Y%m%d-%H%M%S");

	filename.Format(_T("%s\\%s-%s.jpg"), szBuffer, m_facilID, strTimeData);	
	BOOL ret =  m_ctrlXnsWindow.SaveSnapshot(filename, 1);

	if(ret==1)
	{
		WLOGW(_T("Save snapshot %s.. res=%d\n"), filename, ret);
		a++;
	}
	else
	{
		WLOGW(_T("Save snapshot fail %s.. res=%d\n"), filename, ret);
	}

}
