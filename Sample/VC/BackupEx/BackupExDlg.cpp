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
// BackupExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BackupEx.h"
#include "BackupExDlg.h"
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


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

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

#define LOGIN_ID	"admin"
#define PASSWORD	"5gksghk!"
#define IP_ADDRESS	192,168,217,20
#define PORT_NUM	554
#define HTTP_PORT_NUM 80
#define MODEL_NAME	"Samsung NVR"

// CBackupExDlg dialog

CBackupExDlg::CBackupExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBackupExDlg::IDD, pParent)
	, m_strModelName(_T(""))
	, m_nPort(PORT_NUM)
	, m_nHttpPort(HTTP_PORT_NUM)
	, m_strId(_T(LOGIN_ID))
	, m_strPasswd(_T(PASSWORD))
	, m_hDevice(0)
	, m_hMediaSource(0)
	, m_nControlId(0)
	, m_nProgress(-1)
	, m_hFileReader(0)
	, m_strFile(_T("c:\\BackupVideo"))
	, m_nDeviceProtocol(XDEVICE_PROTOCOL_UNKNOWN)
	, m_nMediaProtocol(0)
	, m_nChannelIndex(0)
	, m_nProfileIndex(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBackupExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL, m_ctrlXnsWindow);
	DDX_Control(pDX, IDC_XNSSDKDEVICECTRL, m_ctrlXnsDevice);
	DDX_Control(pDX, IDC_COMBO_MODEL_LIST, m_ctrlModelList);
	DDX_Control(pDX, IDC_IPADDRESS, m_ctrlIpAddress);
	DDX_Text(pDX, IDC_COMBO_MODEL_LIST, m_strModelName);
	DDX_Text(pDX, IDC_EDIT_USER_ID, m_strId);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPasswd);
	DDX_Text(pDX, IDC_EDIT_VNP_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_HTTP_PORT, m_nHttpPort);
	DDX_Control(pDX, IDC_EDIT_STATUS_LOG, m_ctrlEditLog);
	DDX_Control(pDX, IDC_CHECK_SUNAPI, m_ctrlSunapi);
}

BEGIN_MESSAGE_MAP(CBackupExDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CBackupExDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CBackupExDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_BACKUP, &CBackupExDlg::OnBnClickedButtonBackup)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CBackupExDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CBackupExDlg::OnBnClickedButtonStop)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CBackupExDlg::OnCbnSelchangeComboModelList)
	ON_BN_CLICKED(IDC_CHECK_SUNAPI, &CBackupExDlg::OnBnClickedCheckSunapi)
END_MESSAGE_MAP()


// CBackupExDlg message handlers

BOOL CBackupExDlg::OnInitDialog()
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
	if(idx != CB_ERR)
	{
		m_ctrlModelList.SetCurSel(idx);
		m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
		UpdateData(FALSE);
	}
	setBtnStatus(SL_STATUS_DISCONNECTED);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(false);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBackupExDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBackupExDlg::OnPaint()
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
HCURSOR CBackupExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Device Connect Function.
// -----------------------------------------------------------------------
void CBackupExDlg::OnBnClickedButtonConnect()
{
	UpdateData(TRUE);
	CString strIpAddress;
	BYTE a1, a2, a3, a4;
	m_ctrlIpAddress.GetAddress(a1, a2, a3, a4);
	strIpAddress.Format(_T("%d.%d.%d.%d"), a1, a2, a3, a4);

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
		m_nDeviceProtocol,				// [in] Protocol
		m_nMediaProtocol
		);

	WLOGD(_T("Connect. ip=%s, port=%d, id=%s, password=%s\n"), 
		strIpAddress, m_nPort, m_strId, m_strPasswd);

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

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Device DisConnect Function.
// -----------------------------------------------------------------------
void CBackupExDlg::OnBnClickedButtonDisconnect()
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// This event occurs if the device status has changed. 
	// It occurs if the application uses Connect() to connect or reconnect 
	// to the device after disconnected.
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.Disconnect(m_hDevice);
	WLOGD(_T("Disconnect\n"));
	setBtnStatus(SL_STATUS_DISCONNECTED);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Backup Function.
// -----------------------------------------------------------------------
void CBackupExDlg::OnBnClickedButtonBackup()
{
	if(m_ctrlXnsDevice.GetDeviceStatus(m_hDevice) == XDEVICE_STATUS_DISCONNECTED)
	{
		WLOGD(_T("Disconnect\n"));
		return;
	}

	if(!m_nControlId)
	{
		int nControlID = m_ctrlXnsDevice.GetVideoControlID(m_hDevice, m_nChannelIndex +1, m_nProfileIndex+1);
		m_nControlId = nControlID;
	}

	m_nProgress = -1;
	BackupSearchDlg dlg(&m_ctrlXnsDevice, m_hDevice, m_nControlId);
	INT_PTR nResult = dlg.DoModal();
	if(nResult == IDOK)
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Convert from LocalTime to Device UTC
		// Return Value : UTC time_t value.
		// -----------------------------------------------------------------------
		long tStart = m_ctrlXnsDevice.LocalTimeToDeviceUTC(
			m_hDevice,							// [in] Device handle. This value is returned from CreateDevice().
			dlg.m_nStartTime);					// [in] local time_t value
		long tEnd = m_ctrlXnsDevice.LocalTimeToDeviceUTC(m_hDevice,	dlg.m_nEndTime);
		WLOGD(_T("Backup Start:: format=%s, path=%s, (%d~%d)\n"),
			dlg.m_strFileType, m_strFile,
			tStart, tEnd);
	
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Starts backup.
		// Backup is to save the streaming data recorded in the device to the local PC.
		// -----------------------------------------------------------------------		
		long errCode = m_ctrlXnsDevice.StartBackup(
			m_hDevice,								// [in] Device handle. This value is returned from CreateDevice().
			m_nControlId,							// [in] Control ID.
			m_strFile,							// [in] Backup file name.
			dlg.m_nFileType,						// [in] Format of backup file.
			tStart,									// [in] Start time to backup on the recording data (Format: UTC time_t).
			tEnd);									// [in] End time to backup on the recording date (Format: UTC time_t).
		
		if(errCode != ERR_SUCCESS) 
		{
			WLOGD(_T("StartBackup() fail: error=%d(%s)\n"), errCode, m_ctrlXnsDevice.GetErrorString(errCode));
			return;
		}
		m_nProgress=0;
		ProgressDlg pdlg(this);
		INT_PTR nResult = pdlg.DoModal();
		if(nResult == IDOK)
		{
			WLOGD(_T("Backup completed\n"));
		}
		else
		{
			WLOGD(_T("Backup event stoped\n"));
			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Stops backup.
			// -----------------------------------------------------------------------		
			m_ctrlXnsDevice.StopBackup(
				m_hDevice,					// [in] Device handle. This value is returned from CreateDevice().
				m_nControlId);				// [in] Control ID.
			m_nProgress = -1;
			return;
		}
	}
	else
	{
		WLOGD(_T("Backup event canceled\n"));
	}
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for REC Play Function.
// -----------------------------------------------------------------------
void CBackupExDlg::OnBnClickedButtonPlay()
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Check if there exists stream source. 
	// -----------------------------------------------------------------------
	if(m_ctrlXnsWindow.IsMedia() == false)
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Creates the file reader. The file reader is used to play backup or 
		// recoding data.
		// -----------------------------------------------------------------------			
		m_hFileReader = m_ctrlXnsDevice.CreateFileReader(m_strFile);
		if(!m_hFileReader)
		{
			WLOGD(_T("No file to play\n"));
			return;
		}

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Gets the handle of the media source from the file handle. 
		// This value is used to display images using XnsWindow.
		// -----------------------------------------------------------------------
		m_hMediaSource = m_ctrlXnsDevice.GetMediaSource(m_hFileReader);

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Adds the media source handle to XnsSdkWindow. 
		// The media source handle is created by XnsSdkDevice. If the application
		// calls XnsSdkDevice::OpenMedia(), it will receive media stream from the
		// device and return the MediaSource handle. The application uses Start()
		// to forward the media source handle to XnsSdkWindow so that XnsSdkWindow
		// can obtain stream data. 
		// -----------------------------------------------------------------------
		m_ctrlXnsWindow.Start(m_hMediaSource);	
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Plays the backup file at a specified speed.
	// -----------------------------------------------------------------------
	long nErrorCode = m_ctrlXnsDevice.PlayReader(
		m_hFileReader,			// [in] Handle of the file to play. This value can be obtained using CreateFileReader().
		SPEED_1);				// [in] Play speed.

	WLOGD(_T("REC Play\n"));
	setBtnStatus(SL_STATUS_PLAY);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Media Stop Function.
// -----------------------------------------------------------------------
void CBackupExDlg::OnBnClickedButtonStop()
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Stops playing the backup file temporarily. 
	// Can resume playing using PlayReader().
	// -----------------------------------------------------------------------
	long nErrCode = m_ctrlXnsDevice.PauseReader(m_hFileReader);
	WLOGD(_T("REC pause\n"));
	setBtnStatus(SL_STATUS_STOP);
}

BEGIN_EVENTSINK_MAP(CBackupExDlg, CDialog)
	ON_EVENT(CBackupExDlg, IDC_XNSSDKDEVICECTRL, 10, CBackupExDlg::OnDeviceStatusChangedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CBackupExDlg, IDC_XNSSDKDEVICECTRL, 3, CBackupExDlg::OnConnectFailedXnssdkdevicectrl, VTS_I4 VTS_I4)
	ON_EVENT(CBackupExDlg, IDC_XNSSDKDEVICECTRL, 19, CBackupExDlg::OnBackupProgressXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CBackupExDlg, IDC_XNSSDKWINDOWCTRL, 4, CBackupExDlg::OnMediaOffXnssdkwindowctrl, VTS_NONE)
END_EVENTSINK_MAP()


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the device status has changed. It occurs if the 
// application uses Connect() to connect or reconnect to the device after 
// disconnected. When reconnecting, the third argument nDeviceStatus is 
// true, all media must be reopened using ReopenAllStream().
// -----------------------------------------------------------------------
void CBackupExDlg::OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
	if (nErrorCode != ERR_SUCCESS || nDeviceStatus != 1)
	{
		setBtnStatus(SL_STATUS_DISCONNECTED);
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
void CBackupExDlg::OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode)
{
	WLOGD(_T("Connect Failed: deviceID=%d, errcode=[%d](%s)\n"),
		nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode));
	setBtnStatus(SL_STATUS_DISCONNECTED);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs at a regular interval each time the progress of 
// multimedia data backup increases by 5%. It contains the progress (%) 
// and error code.
// -----------------------------------------------------------------------
void CBackupExDlg::OnBackupProgressXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode, long nProgress, long tStart, long tEnd)
{
	if(nErrorCode != ERR_SUCCESS)
	{
		CString strErrorCode;

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Returns description about the error code.
		// -----------------------------------------------------------------------			
		strErrorCode = m_ctrlXnsDevice.GetErrorString(nErrorCode);
		WLOGD(_T("Backup Event fail:: device id=%d, control id=%d, errorcode=%s, progress=%d, start=%d, end=%d\n"),
			nDeviceID, nControlID, strErrorCode, nProgress, tStart, tEnd);
		switch(nErrorCode)
		{
		case ERR_WRITE_EMPTY:
			WLOGD(_T("No data to be written so far.\n"));	
			break;
		case ERR_DISK_FULL:
			WLOGD(_T("No disk free space.\n"));
			break;
		}
		return;
	}
	WLOGD(_T("Backup Event success:: device id=%d, control id=%d, errorcode=%d, progress=%d, start=%d, end=%d\n"),
		nDeviceID, nControlID, nErrorCode, nProgress, tStart, tEnd);
	m_nProgress = nProgress;
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This occurs if receiving media stream is stopped or completed. 
// -----------------------------------------------------------------------
void CBackupExDlg::OnMediaOffXnssdkwindowctrl()
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Releases the file reader.
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.ReleaseFileReader(m_hFileReader);
	m_hFileReader = 0;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Stops receiving the stream data from the media source handle (hMediaSource). 
	// -----------------------------------------------------------------------
	m_ctrlXnsWindow.Stop();	
	m_hMediaSource = 0;
	WLOGW(_T("Receiving media stream is completed\n"));
	setBtnStatus(SL_STATUS_STOP);
}

void CBackupExDlg::OnDestroy()
{
	if(m_hDevice)
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Returns the connection status of the device.
		// -----------------------------------------------------------------------
		if( m_ctrlXnsDevice.GetDeviceStatus(m_hDevice) == XDEVICE_STATUS_CONNECTED )
		{
			m_ctrlXnsDevice.Disconnect(m_hDevice);
		}

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Cancels the memory space assigned for the device information by 
		// CreateDevice(). The device should be disconnected from the application
		// before this function is called.
		// -----------------------------------------------------------------------
		m_ctrlXnsDevice.ReleaseDevice(m_hDevice);
	}
	CDialog::OnDestroy();
}

// Control button enable/disable
void CBackupExDlg::setBtnStatus(SLIVE_BUTTON_STATUS nStatus)
{
	bool conn = false, disconn = false, backup = false;

	switch(nStatus)
	{
	case SL_STATUS_CONNECTED:
		conn = false;
		disconn = true;
		backup = true;
		break;
	case SL_STATUS_DISCONNECTED:
		conn = true;
		disconn = false;
		backup = false;
		break;
	case SL_STATUS_PLAY:
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(true);
		return;
	case SL_STATUS_STOP:
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(false);
		return;
	}
	
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(conn);
	GetDlgItem(IDC_COMBO_MODEL_LIST)->EnableWindow(conn);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PW)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_VNP_PORT)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_HTTP_PORT)->EnableWindow(conn);

	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(disconn);

	GetDlgItem(IDC_BUTTON_BACKUP)->EnableWindow(backup);
	SetCheckSunapi();
}


void CBackupExDlg::OnCbnSelchangeComboModelList()
{
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
	SetCheckSunapi();
}


void CBackupExDlg::OnOK()
{
	/*CDialog::OnOK();*/
}


void CBackupExDlg::OnBnClickedCheckSunapi()
{
	SetCheckSunapi();
}

void CBackupExDlg::SetCheckSunapi()
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