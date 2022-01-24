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
#include "NVRTextPlayBack.h"
#include "NVRTextPlayBackDlg.h"

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


// SUNAPI NVR SRN-2000
#define LOGIN_ID		"admin"
#define PASSWORD		"5thsznssla!"
#define IP_ADDRESS		192,168,217,120
#define PORT_NUM		554
#define HTTP_PORT_NUM	80
#define MODEL_NAME		"Samsung NVR"


// CNVRTextPlayBackDlg dialog
CNVRTextPlayBackDlg::CNVRTextPlayBackDlg(CWnd* pParent /*=NULL*/)
: CDialog(CNVRTextPlayBackDlg::IDD, pParent)
	, m_strModelName(_T(""))
	, m_nPort(PORT_NUM)
	, m_nHttpPort(HTTP_PORT_NUM)
	, m_strId(_T(LOGIN_ID))
	, m_strPw(_T(PASSWORD))
	, m_strUrl(_T(""))
	, m_hDevice(0)
	, m_bCheckConnect(FALSE)
	, m_pRecDataInfo(NULL)
	, m_hMediaSource(0)
	, m_nForwardSpeed(1)
	, m_nBackwardSpeed(1)
	, m_bPlay(FALSE)
	, m_strCurTime(_T(""))
	, m_bDestroy(FALSE)
	, m_nControlId(0)
	, m_nTrackNum(0)
	, m_nDeviceProtocol(0)
	, m_bSupportedSunapi(0)
	, m_nTextControlId(0)
	, m_nTextIndex(0)
	, m_nTextList(0)
	, m_strSearchText(_T(""))
{
	for(int i = 0; i < 30; i ++)
	{
		m_nTrackValue[i] = 0;
	}
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNVRTextPlayBackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//////////////////////////////////////////////////////////////////////////
	// Active X Control 
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL1, m_ctrlXnsWindow);
	DDX_Control(pDX, IDC_XNSSDKDEVICECTRL1, m_ctrlXnsDevice);

	//////////////////////////////////////////////////////////////////////////
	// Control Member 
	DDX_Control(pDX, IDC_COMBO_MODEL_LIST, m_ctrlModelList);
	DDX_Control(pDX, IDC_IPADDRESS, m_ctrlIpAddress);
	DDX_Control(pDX, IDC_EDIT_PORT, m_ctrlPort);
	DDX_Control(pDX, IDC_EDIT_PORT2, m_ctrlHttpPort);
	DDX_Control(pDX, IDC_EDIT_LOG_WIN, m_ctrlEditLog);
	DDX_Control(pDX, IDC_LIST_RECDATA, m_ctrlRecDataList);
	DDX_Control(pDX, IDC_LIST_RECDATA_TEXT, m_ctrlRecTextList);
	DDX_Control(pDX, IDC_SLIDER_RECTIME, m_ctrlTimebar);
	DDX_Control(pDX, IDC_COMBO_PLAY_SPEED, m_ctrlPlaySpeedCombo);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_ctrlMonthCalendar);
	DDX_Control(pDX, IDC_MONTHCALENDAR_TEXT, m_ctrlMonthCalendarText);
	DDX_Control(pDX, IDC_COMBO_TRACK, m_ctrlTrackNum);
	DDX_Control(pDX, IDC_CHECK_SUNAPI, m_ctrlSunapi);
	DDX_Control(pDX, IDC_COMBO_TEXT, m_ctrlTextList);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_ctrlTextLog);
	DDX_Control(pDX, IDC_CHECK_ALL_MATCH, m_ctrlAllMatch);

	//////////////////////////////////////////////////////////////////////////
	// Text Control
	DDX_Text(pDX, IDC_EDIT_ID, m_strId);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPw);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_nHttpPort);
	DDX_CBIndex(pDX, IDC_COMBO_TEXT, m_nTextIndex);
	DDX_Text(pDX, IDC_EDIT_SEARCH_TEXT, m_strSearchText);
}


//////////////////////////////////////////////////////////////////////////////
// MFC Control Message Map
BEGIN_MESSAGE_MAP(CNVRTextPlayBackDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CNVRTextPlayBackDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CNVRTextPlayBackDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_CALENDAR, &CNVRTextPlayBackDlg::OnBnClickedButtonCheckCalendar2)
	ON_NOTIFY(MCN_SELECT, IDC_MONTHCALENDAR1, &CNVRTextPlayBackDlg::OnMcnSelectMonthcalendar1)
	ON_LBN_DBLCLK(IDC_LIST_RECDATA, &CNVRTextPlayBackDlg::OnLbnDblclkListRecdata)
	ON_BN_CLICKED(IDC_BUTTON_STEP_BACK, &CNVRTextPlayBackDlg::OnBnClickedButtonStepBack)
	ON_BN_CLICKED(IDC_BUTTON_BP, &CNVRTextPlayBackDlg::OnBnClickedButtonBp)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CNVRTextPlayBackDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_FOR, &CNVRTextPlayBackDlg::OnBnClickedButtonFor)
	ON_WM_DESTROY()

	ON_CBN_SELCHANGE(IDC_COMBO_PLAY_SPEED, &CNVRTextPlayBackDlg::OnCbnSelchangeComboPlaySpeed)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_RECTIME, &CNVRTextPlayBackDlg::OnNMReleasedcaptureSliderRectime)
	ON_CBN_SELCHANGE(IDC_COMBO_TRACK, &CNVRTextPlayBackDlg::OnCbnSelchangeComboTrack)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CNVRTextPlayBackDlg::OnCbnSelchangeComboModelList)
	ON_BN_CLICKED(IDC_CHECK_SUNAPI, &CNVRTextPlayBackDlg::OnBnClickedCheckSunapi)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_TEXT, &CNVRTextPlayBackDlg::OnBnClickedButtonOpenText)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_TEXT, &CNVRTextPlayBackDlg::OnBnClickedButtonCloseText)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_CALENDAR_TEXT, &CNVRTextPlayBackDlg::OnBnClickedButtonCheckCalendarText)
	ON_NOTIFY(MCN_SELECT, IDC_MONTHCALENDAR_TEXT, &CNVRTextPlayBackDlg::OnMcnSelectMonthcalendarText)

END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////
// Active X Control Message Map
BEGIN_EVENTSINK_MAP(CNVRTextPlayBackDlg, CDialog)
	ON_EVENT(CNVRTextPlayBackDlg, IDC_XNSSDKDEVICECTRL1, 10, CNVRTextPlayBackDlg::OnDeviceStatusChangedXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CNVRTextPlayBackDlg, IDC_XNSSDKDEVICECTRL1, 4, CNVRTextPlayBackDlg::OnSearchCalendarXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CNVRTextPlayBackDlg, IDC_XNSSDKDEVICECTRL1, 5, CNVRTextPlayBackDlg::OnSearchDayXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CNVRTextPlayBackDlg, IDC_XNSSDKWINDOWCTRL1, 1, CNVRTextPlayBackDlg::OnFrameTimeChangedXnssdkwindowctrl1, VTS_I4)
	ON_EVENT(CNVRTextPlayBackDlg, IDC_XNSSDKDEVICECTRL1, 3, CNVRTextPlayBackDlg::OnConnectFailedXnssdkdevicectrl1, VTS_I4 VTS_I4)
	ON_EVENT(CNVRTextPlayBackDlg, IDC_XNSSDKDEVICECTRL1, 33, CNVRTextPlayBackDlg::OnSearchOverLapXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CNVRTextPlayBackDlg, IDC_XNSSDKDEVICECTRL1, 20, CNVRTextPlayBackDlg::OnNewMediaXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
ON_EVENT(CNVRTextPlayBackDlg, IDC_XNSSDKDEVICECTRL1, 69, CNVRTextPlayBackDlg::OnSearchTextCalendarXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4)
ON_EVENT(CNVRTextPlayBackDlg, IDC_XNSSDKDEVICECTRL1, 70, CNVRTextPlayBackDlg::OnSearchTextListXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_I4)
ON_EVENT(CNVRTextPlayBackDlg, IDC_XNSSDKDEVICECTRL1, 71, CNVRTextPlayBackDlg::OnEndSearchTextXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

// CNVRTextPlayBackDlg message handlers

BOOL CNVRTextPlayBackDlg::OnInitDialog()
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

void CNVRTextPlayBackDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNVRTextPlayBackDlg::OnPaint()
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
HCURSOR CNVRTextPlayBackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// for ActiveX SDK Device control and Window Control initialize function.
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnInitXnsSdk(void)
{
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
	if (!m_hDevice)
	{
		m_hDevice = m_ctrlXnsDevice.CreateDevice(1);                 // Create Device ID
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
void CNVRTextPlayBackDlg::OnInitModelList(void)
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

	long hFind = m_ctrlXnsDevice.FindModel(_T("samsung"));			// Search Model 


	// Returns the length of the array that is created using FindVendor(), 
	// FindModel(), and FindDevice().
	long nFindSize = m_ctrlXnsDevice.GetFindSize(hFind);				// Get Array Size
	CString strModel;


	for (int i = 0; i < nFindSize; i++)
	{
		// Reurns data of nIndex from the array created using FindVendor() 
		// and FindModel(). If nIndex is larger than the actual array, 
		// "" will be returned.
		strModel = m_ctrlXnsDevice.GetFindString(hFind, i);			// Get Model Name 
		m_ctrlModelList.AddString(strModel);                            // Add Combo Box - Model Name
	}

	// Closes the Find command. Releases the memory space assinged by FindXXX().
	m_ctrlXnsDevice.CloseFind(hFind);                                // End Search 
	m_ctrlModelList.SetCurSel(0);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// for Dialog Control initialize function.
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnSetDialog(void)
{
	CString strPlaySpeed[] = {_T("X1"), _T("X2"), _T("X4"), _T("X8"), _T("X16"), _T("X32"), _T("X64")};

	m_ctrlModelList.SetCurSel(0);
	int idx = m_ctrlModelList.FindStringExact(0, _T(MODEL_NAME));
	if(idx != CB_ERR)
	{
		m_ctrlModelList.SetCurSel(idx);
		m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
		if( m_strModelName == "Samsung Network Camera/Encoder" || m_strModelName == "Samsung NVR" )
		{
			m_bSupportedSunapi = TRUE;
		}
		UpdateData(FALSE);
	}

	setBtnStatus(STATUS_DISCONNECTED);
	SetDeviceProtocol();

	m_ctrlIpAddress.SetAddress(IP_ADDRESS);

	for (int i = 0; i < 7; i++)
	{
		m_ctrlPlaySpeedCombo.AddString(strPlaySpeed[i]);
	}
	m_ctrlPlaySpeedCombo.SetCurSel(0);

	/////////////////////////////////////////////////////// Control Setting
	GetDlgItem(IDC_BUTTON_CHECK_CALENDAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_MONTHCALENDAR1)->EnableWindow(FALSE);
	GetDlgItem(IDC_MONTHCALENDAR_TEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STEP_BACK)->EnableWindow(FALSE);
	m_ctrlRecDataList.EnableWindow(FALSE);
	m_ctrlRecTextList.EnableWindow(FALSE);
	m_ctrlPlaySpeedCombo.EnableWindow(FALSE);
	m_ctrlMonthCalendar.EnableWindow(FALSE);
	m_ctrlMonthCalendarText.EnableWindow(FALSE);
	m_ctrlTimebar.EnableWindow(FALSE);

	////////////////////////////////////////////////////////// Time Setting 
// 	SYSTEMTIME startTime, endTime;
// 	time_t curtime;
// 	time(&curtime);
// 	struct tm *tmTime;
// 	tmTime = gmtime(&curtime);
// 
// 	startTime.wYear =		endTime.wYear = tmTime->tm_hour+1900;
// 	endTime.wMonth	= 1;	endTime.wMonth = tmTime->tm_mon+1;
// 	endTime.wDay = 1;		endTime.wDay = tmTime->tm_mday;
// 	endTime.wHour = 0;		endTime.wHour = endTime.wHour = tmTime->tm_hour;
// 	endTime.wMinute = 0;	endTime.wMinute = tmTime->tm_min;
// 	endTime.wSecond = 0;	endTime.wSecond = tmTime->tm_sec;

	SYSTEMTIME timeFrom;
	SYSTEMTIME timeUntil;
	int nCount = m_ctrlMonthCalendar.GetMonthRange(&timeFrom, &timeUntil, GMR_DAYSTATE);
	LPMONTHDAYSTATE pDayState;
	pDayState = new MONTHDAYSTATE[nCount];
	memset(pDayState, 0, sizeof(MONTHDAYSTATE) * nCount);
	VERIFY(m_ctrlMonthCalendar.SetDayState(3, pDayState));
	delete[] pDayState;

	SYSTEMTIME timeFromText;
	SYSTEMTIME timeUntilText;
	int nTextCount = m_ctrlMonthCalendarText.GetMonthRange(&timeFromText, &timeUntilText, GMR_DAYSTATE);
	LPMONTHDAYSTATE pDayStateText;
	pDayStateText = new MONTHDAYSTATE[nTextCount];
	memset(pDayStateText, 0, sizeof(MONTHDAYSTATE) * nTextCount);
	VERIFY(m_ctrlMonthCalendarText.SetDayState(3, pDayStateText));
	delete[] pDayStateText;

	////////////////////////////////////////////////////// Calendar Setting
// 	m_ctrlMonthCalendar.SetRange(&startTime, &endTime);
// 	{
// 		MONTHDAYSTATE mdState[3] = {0};
// 		m_ctrlMonthCalendar.SetDayState(3, mdState);
// 	}

}


void CNVRTextPlayBackDlg::OnDestroy()
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
			m_ctrlXnsWindow.Stop();
			m_bPlay = FALSE;
			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Terminates transferring media stream data from the device. 
			// The media stream data will be separated by hMediaSource 
			// (i.e., phMediaSource of OpenMedia()).
			// -----------------------------------------------------------------------
			m_ctrlXnsDevice.CloseMedia(m_hDevice, m_hMediaSource);		}

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Cancels the memory space assigned for the device information by CreateDevice().
		//  The device should be disconnected from the application before this function is called.
		// -----------------------------------------------------------------------
		if(m_bCheckConnect == TRUE)
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

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Device Connect Function.
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnBnClickedButtonConnect()
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
	m_ctrlXnsDevice.SetConnectionInfo2(
		m_hDevice,							// [in] Device handle
		_T("Samsung"),                      // [in] Fixed as 'Samsung'
		strModel,                           // [in] Name of model to connect to.
		XADDRESS_IP,                        // [in] Address type (Define Value : XADDRESS_IP = 1)
		strIpAddress,                       // [in] Actual address according to nAddressType.
		m_nPort,							// [in] Port Number
		m_nHttpPort,                        // [in] Port number for web access
		m_strId,                            // [in] User Login ID
		m_strPw,
		m_nDeviceProtocol,
		0);                                 // [in] User Login Password


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
		m_hDevice,							// [in] Device handle
		true,								// [in] Flag to decide where to forcibly log in or not.
		true);								// [in] If this value is 1, try to connect again.

	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ConnectNonBlock() fail: errno=[%d](%s)\n"), 
			nRet, m_ctrlXnsDevice.GetErrorString(nRet));
		setBtnStatus(STATUS_DISCONNECTED);
		SetDeviceProtocol();
	}
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Device DisConnect Function.
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnBnClickedButtonDisconnect()
{
	if (m_pRecDataInfo)
	{
		delete m_pRecDataInfo;
		m_pRecDataInfo = NULL;
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Stops receiving the stream data from 
	// the mediasource handle (pMediaSource).
	// -----------------------------------------------------------------------
	m_ctrlXnsWindow.Stop();

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Terminates transferring media stream data from the device. The media 
	// stream data will be separated by hMediaSource 
	// (i.e., phMediaSource of OpenMedia()).
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.CloseMedia(
		m_hDevice,														// [in] Device handle. This value is returned from CreateDevice(). 
		m_hMediaSource);												// [in] Media stream ID.

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// This event occurs if the device status has changed. 
	// It occurs if the application uses Connect() to connect or reconnect 
	// to the device after disconnected.
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.Disconnect(m_hDevice);

	WLOGD(_T("Disconnect\n"));

	m_hMediaSource = 0;													// Media Source Initialize.
	setBtnStatus(STATUS_DISCONNECTED);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Import of data recorded.
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnBnClickedButtonCheckCalendar2()
{
	UpdateData(FALSE);
	SYSTEMTIME CurTime;
	m_ctrlMonthCalendar.GetCurSel(&CurTime);
	long Year = CurTime.wYear;
	long Month = CurTime.wMonth;

	long TargetMonth = m_ctrlXnsDevice.DateToTimet(Year, Month, 1, 0, 0, 0);
	TargetMonth = m_ctrlXnsDevice.LocalTimeToDeviceUTC(m_hDevice, TargetMonth);

	long Ret = m_ctrlXnsDevice.AcquireMediaAuthority(m_hDevice);
	if(Ret != ERR_SUCCESS)
	{
		WLOGD(_T("AcquireMediaAuthority() fail. errorcode =%d(%s)\n"),
			Ret, m_ctrlXnsDevice.GetErrorString(Ret));
		return;
	}

	WLOGD(_T("Search Calendar, target year=%d, month=%d\n"), Year, Month);

	Ret = m_ctrlXnsDevice.SearchCalendar(m_hDevice, 2, TargetMonth);
	if(Ret != ERR_SUCCESS)
	{
		WLOGD(_T("SearchCalendar() fail. errorcode =%d(%s)\n"),
			Ret, m_ctrlXnsDevice.GetErrorString(Ret));
		return;
	}
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event occurs if the device status has changed. It occurs if the 
// application uses Connect() to connect or reconnect to the device after 
// disconnected. When reconnecting, the third argument nDeviceStatus is 
// true, all media must be reopened using ReopenAllStream().
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnDeviceStatusChangedXnssdkdevicectrl1(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
	if((nErrorCode != ERR_SUCCESS) || (m_bDestroy == TRUE))
		return;

	WLOGD(_T("Connected: deviceID=%d, errcode=%d, deviceStatus=%d\n"),
		nDeviceID, nErrorCode, nDeviceStatus);

	// Connect Success.
	if ((nErrorCode == ERR_SUCCESS) && (nDeviceStatus == TRUE))
	{
		m_bCheckConnect = TRUE;
		if ((m_bCheckConnect) && (!m_bDestroy))
		{
			setBtnStatus(STATUS_CONNECTED);
			WLOGD(_T("Connection Success !"));

			m_nControlId = m_ctrlXnsDevice.GetVideoControlID(m_hDevice, 1, 1);

			// text control id
			for(int i = 1; i <= m_ctrlXnsDevice.GetControlCount(m_hDevice, XCTL_ALL); ++i)
			{
				if (m_ctrlXnsDevice.GetControlType(m_hDevice, i) == XCTL_TEXT)
				{
					m_nTextControlId = i;
					break;
				}
			}
		}
	}
	// DisConnect Success.
	else if ((nErrorCode == ERR_SUCCESS) && (nDeviceStatus == FALSE))
	{
		WLOGD(_T("Connected: deviceID=%d, errcode=%d, deviceStatus=%d\n"),
			nDeviceID, nErrorCode, nDeviceStatus);

		setBtnStatus(STATUS_DISCONNECTED);
		SetDeviceProtocol();
		WLOGD(_T("DisConnection Success!\n"));
	}

	m_ctrlTextList.ResetContent();
	int nTextCount = m_ctrlXnsDevice.GetControlCount(m_hDevice, XCTL_TEXT);
	CString TextIndex;
	for( int i = 1; i <= nTextCount; ++i )
	{
		TextIndex.Format(_T("%d"), i);
		m_ctrlTextList.AddString(TextIndex);
	}
	m_ctrlTextList.SetCurSel(0);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// If the application has failed in non-blocking connection using 
// ConnectNonBlock(), the OnConnectFailed event occurs. As Connect() 
// returns an immediate error message if failed, it does not trigger 
// this event. 
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnConnectFailedXnssdkdevicectrl1(long nDeviceID, long nErrorCode)
{
	WLOGD(_T("Disconnected: deviceID=%d, errcode=[%d](%s)\n"),
		nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode));

	setBtnStatus(STATUS_DISCONNECTED);
	SetDeviceProtocol();
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event occurs if the application calls SearchCalendar(), 
// which contains the search result.
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnSearchCalendarXnssdkdevicectrl1(long nDeviceID, long nControlID, long nRecDay)
{
	CString strDay = _T("01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31\n");
	OutputDebugString(strDay);
	long nBitFlag = 0x01;
	CString strRec;

	SYSTEMTIME timeFrom;
	SYSTEMTIME timeUntil;
	int nCount = m_ctrlMonthCalendar.GetMonthRange(&timeFrom, &timeUntil, GMR_DAYSTATE);
	LPMONTHDAYSTATE pDayState;
	pDayState = new MONTHDAYSTATE[nCount];
	memset(pDayState, 0, sizeof(MONTHDAYSTATE) * nCount);
	int nIndex = (timeFrom.wDay == 1) ? 0 : 1;

	for (int i=0; i<31; i++)
	{
		if (nRecDay & nBitFlag)
		{
			strRec = " 1 ";
			pDayState[nIndex] |= 1<<i;
		}
		else
			strRec = " 0 ";

		OutputDebugString(strRec);
		nBitFlag <<=1;
	}
	OutputDebugString(_T("\n"));

	VERIFY(m_ctrlMonthCalendar.SetDayState(nCount, pDayState));
	delete[] pDayState;
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Calendar Control Functions.
// This event occurs if the application calls SearchCalendar(), 
// which contains the search result.
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnMcnSelectMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMSELCHANGE	*pSelChange = (NMSELCHANGE*)pNMHDR;
	m_seltime = pSelChange->stSelStart;
	m_nYear = m_seltime.wYear;
	m_nMonth = m_seltime.wMonth;
	m_nDay = m_seltime.wDay;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Gets the video recording dates from a specific month. 
	// The result of this function can be obtained from the OnSearchCalendar event.
	// Return Value : Converted values in time_t format.
	// -----------------------------------------------------------------------
	long tStart = m_ctrlXnsDevice.DateToTimet(
		(long)m_nYear,													// [in] Year
		(long)m_nMonth,													// [in] Month
		(long)m_nDay,													// [in] Day
		0,																// [in] Hour
		0,																// [in] Minute
		0);																// [in] Second

	long tEnd = m_ctrlXnsDevice.DateToTimet((long)m_nYear, (long)m_nMonth, (long)m_nDay,	23,	59,	59);															// [in] Second

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local t_time to UTC t_time.
	// Return Value : UTC time_t value.
	// -----------------------------------------------------------------------
	long tUTCStart = m_ctrlXnsDevice.LocalTimeToDeviceUTC(
		m_hDevice,														// [in] Device handle. This value is returned from CreateDevice().
		tStart);														// [in] local time_t value

	long tUTCEnd  = m_ctrlXnsDevice.LocalTimeToDeviceUTC(m_hDevice, tEnd);

	long ret = m_ctrlXnsDevice.SearchOverLap(m_hDevice, tUTCStart, tUTCEnd);
	if(ret != ERROR_SUCCESS)
		return;

	m_ctrlXnsDevice.SearchDay(
		m_hDevice,														// [in] Device handle. This value is returned from CreateDevice().
		m_nControlId,													// [in] Control ID. 
		tUTCStart,														// [in] Play start time. Format: UTC time_t.
		tUTCEnd,														// [in] Play start time. Format: UTC time_t.
		REC_TYPE_ALL);													// [in] Recording type.	

	
// 	m_ctrlTimebar.SetRange(tUTCStart, tUTCEnd);

	*pResult = 0;
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event occurs if the application calls SearchDay(). 
// The timeline handle will be forwarded to a parameter of the event handler. 
// Some functions such as GetTimeline() use this handle as a parameter.
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnSearchDayXnssdkdevicectrl1(long nDeviceID, long nControlID, long hTimeline)
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Number of blocks of the recording data in the timeline. 
	// This value is used as a parameter of functions: 
	// GetStartTime(), GetEndTime(), GetRecordingType().
	// Return Value : Number of blocks of the recording data in the timeline. 
	// -----------------------------------------------------------------------
	long nCamCount = m_ctrlXnsDevice.GetCameraCount(hTimeline);
	long nTimelineCount = m_ctrlXnsDevice.GetTimelineCount(hTimeline, 0);
	long nRecType;
	long nRecId;

	long tStart, tEnd;
	long Year, Month, Day;
	long StartHour, StartMin, StartSec;
	long EndHour, EndMin, EndSec;

	int i, j;
	long nTotalCount = 0;
	CString strType;
	CString strBuffer=_T("");

	WLOGD(_T("OnSearchDay Event.. nControlID[%d] nCamCount[%d]\n"), nControlID, nCamCount);
	m_ctrlRecDataList.ResetContent();


	for (i=0; i<nCamCount; i++)
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Number of blocks of the recording data in the timeline. 
		// This value is used as a parameter of functions: 
		// GetStartTime(), GetEndTime(), GetRecordingType().
		// Return Value : Number of blocks of the recording data in the timeline. 
		// -----------------------------------------------------------------------
		nTimelineCount = m_ctrlXnsDevice.GetTimelineCount(hTimeline, i);
		nTotalCount += nTimelineCount;
	}

	if (m_pRecDataInfo)
	{
		delete m_pRecDataInfo;
		m_pRecDataInfo = NULL;
	}

	m_pRecDataInfo = new sRecDataInfo[nTotalCount];

	nTotalCount = 0;
	for (i=0; i<nCamCount; i++)
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Number of blocks of the recording data in the timeline. 
		// This value is used as a parameter of functions: 
		// GetStartTime(), GetEndTime(), GetRecordingType().
		// Return Value : Number of blocks of the recording data in the timeline. 
		// -----------------------------------------------------------------------
		nTimelineCount = m_ctrlXnsDevice.GetTimelineCount(hTimeline, i);
		for(j=0; j<nTimelineCount; j++)
		{
			m_ctrlXnsDevice.GetTimeline(hTimeline, i, j, XTIME_LOCAL, &tStart, &tEnd, &nRecType, &nRecId);

			DBG_LOG(_T("[%d][%d] Timeline[%d], tStart[%d], tEnd[%d]\n"), i, j, nTotalCount, tStart, tEnd);

			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
			// -----------------------------------------------------------------------
			m_ctrlXnsDevice.TimetToDate(
				tStart,												// [in] Data in time_t format to convert.
				&Year,												// [out] Year
				&Month,												// [out] Month
				&Day,												// [out] Day
				&StartHour,											// [out] Hour
				&StartMin,											// [out] Minute
				&StartSec);											// [out] Second


			m_ctrlXnsDevice.TimetToDate(
				tEnd,												// [in] Data in time_t format to convert.
				&Year,												// [out] Year 
				&Month,												// [out] Month 
				&Day,												// [out] Day 
				&EndHour,											// [out] Hour 
				&EndMin,											// [out] Minute 
				&EndSec);											// [out] Second

			// Print Record File List
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

			strBuffer.Format(_T("%02d|%s|%02d:%02d:%02d~%02d:%02d:%02d\n"),
				nTotalCount, strType, StartHour, StartMin, StartSec, EndHour, EndMin, EndSec);

			m_ctrlRecDataList.AddString(strBuffer);
			//WLOGD(strBuffer);

			m_pRecDataInfo[nTotalCount].tStartTime	= tStart;
			m_pRecDataInfo[nTotalCount].tEndTime	= tEnd;
			m_pRecDataInfo[nTotalCount].nRecType	= nRecType;
			nTotalCount++;
		}
	}

	WLOGD(_T("OnSearchDay() Event Call !\n"));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// for Record Video Play.
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnLbnDblclkListRecdata()
{
	long nIndex = m_ctrlRecDataList.GetCurSel();

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Convert from LocalTime to Device UTC
	// Return Value : UTC time_t value.
	// -----------------------------------------------------------------------
	long tStart = m_ctrlXnsDevice.LocalTimeToDeviceUTC(m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
		m_pRecDataInfo[nIndex].tStartTime);										// [in] local time_t value		
	
	long tEnd = m_ctrlXnsDevice.LocalTimeToDeviceUTC(m_hDevice,				// [in] Device handle. This value is returned from CreateDevice().
		m_pRecDataInfo[nIndex].tEndTime);										// [in] local time_t value	

	if (m_hMediaSource)
	{
		{
			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Stops receiving the stream data from the mediasource handle (pMediaSource).
			// -----------------------------------------------------------------------
			long hMediaSource = m_ctrlXnsWindow.Stop();

			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Terminates transferring media stream data from the device. 
			// The media stream data will be separated by hMediaSource 
			// (i.e., phMediaSource of OpenMedia()).
			// -----------------------------------------------------------------------
			m_ctrlXnsDevice.CloseMedia(m_hDevice, hMediaSource);

			m_bPlay = FALSE;
			m_hMediaSource = 0;
		}
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Acquires the permission to play the recorded multimedia. 
	// The application should acquire the permission using 
	// this function before it can play video.
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.AcquireMediaAuthority(m_hDevice);

	if (!m_hMediaSource)                                       
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// When called, it will start getting media streams from the device.
		// The receiving media streams will, then, be forwarded to 
		// the XnsSdkWindow component that will play the streams after decoding.
		// phMediaSource is needed to link the stream data with XnsSdkWindow. 
		// The value can be obtained from a parameter (out-parameter) of OpenMedia(). 
		// When XnsSdkWindow receives this value, it can get stream data from the device.
		// phMediaSource is also used for controlling playback of multimedia files. 
		// As a result, the application should keep this value at all times.
		// -----------------------------------------------------------------------
		m_ctrlXnsDevice.OpenMedia(
			m_hDevice,											// [in] Device handle. This value is returned from CreateDevice().
			m_nControlId,										// [in] Control ID of video control module.
			MEDIA_TYPE_PLAYBACK,								// [in] Media type.
			tStart,												// [in] Play start time. Format: 4-byte time_t.
			tEnd,												// [in] Play end time. Format: 4-byte time_t.
			&m_hMediaSource);									// [out] Media stream ID.
		WLOGD(_T("Open Media !\n"));

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Adds the media source handle to XnsSdkWindow.
		// The media source handle is created by XnsSdkDevice. 
		// If the application calls XnsSdkDevice::OpenMedia(), 
		// it will receive media stream from the device and return the MediaSource handle. 
		// The application uses uses Start() to forward the mediasource handle 
		// to XnsSdkWindow so that XnsSdkWindow can obtain stream data.
		// -----------------------------------------------------------------------
		m_ctrlXnsWindow.Start(m_hMediaSource);
		WLOGW(_T("Start !\n"));
	}


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Searches for a specific time point of the media stream.
	// -----------------------------------------------------------------------
	if (!m_ctrlXnsDevice.IsPlaying(m_hDevice))				// Not Playing
	{
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Informs if the media stream is currently playing.
		// -----------------------------------------------------------------------
		m_ctrlXnsDevice.Seek(
			m_hDevice,											// [in] Device handle. This value is returned from CreateDevice(). 
			m_nControlId,										// [in] Control ID.
			tStart);											// [in] Target time. Format: 4-byte time_t.

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Plays the multimedia at a specified speed.
		// -----------------------------------------------------------------------
		m_ctrlXnsDevice.Play(
			m_hDevice,											// [in] Device handle. This value is returned from CreateDevice().
			m_nControlId,										// [in] Control ID.
			1.0);												// [in] Play speed.
		m_bPlay = TRUE;
	}

	m_ctrlTimebar.SetRange(m_pRecDataInfo[nIndex].tStartTime, m_pRecDataInfo[nIndex].tEndTime);
	m_ctrlTimebar.SetPos(m_pRecDataInfo[nIndex].tStartTime);

	UpdateData(FALSE);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// " <| " Step Backward Button Clicked. (Pause State Gets the next I-frame)
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnBnClickedButtonStepBack()
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	//Gets the next I-frame.
	//
	m_ctrlXnsDevice.FrameAdvance(m_hDevice, m_nControlId, PLAY_BACKWARD);
	WLOGD(_T("Step Backward !\n"));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// " < " BP Button Clicked  
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnBnClickedButtonBp()
{
	m_nForwardSpeed = 1;
	m_nBackwardSpeed = 1;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Plays the multimedia at a specified speed.
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.Play(
		m_hDevice,													// [in] Device handle. This value is returned from CreateDevice().
		m_nControlId,															// [in] Control ID.
		(double)m_nBackwardSpeed * (-1.0));						// [in] Play speed.

	WLOGD(_T("Back Play !\n"));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// " || " Stop Button Clicked.
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnBnClickedButtonStop()
{
	if (m_bPlay == TRUE)
	{
		m_nForwardSpeed = 1;
		m_nBackwardSpeed = 1;

		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Stops playing the media stream temporarily.
		// -----------------------------------------------------------------------
		m_ctrlXnsDevice.Pause(
			m_hDevice,														// [in] Device handle. This value is returned from CreateDevice().
			m_nControlId);													// [in] Control ID.
		WLOGD(_T("Pause !\n"));

		m_bPlay = FALSE;
		GetDlgItem(IDC_BUTTON_STOP)->SetWindowText(_T("¢¹"));
		GetDlgItem(IDC_BUTTON_FOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STEP_BACK)->EnableWindow(TRUE);
	}
	else
	{
		m_nForwardSpeed = 1;
		m_nBackwardSpeed = 1;

		// -----------------------------------------------------------------------
		// Plays the multimedia at a specified speed.
		// -----------------------------------------------------------------------
		m_ctrlXnsDevice.Play(
			m_hDevice,														// [in] Device handle. This value is returned from CreateDevice().
			m_nControlId,													// [in] Control ID.
			1.0);															// [in] Play speed.
		WLOGW(_T("Play !\n"));

		m_bPlay = TRUE;
		GetDlgItem(IDC_BUTTON_STOP)->SetWindowText(_T("||"));
		GetDlgItem(IDC_BUTTON_FOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STEP_BACK)->EnableWindow(FALSE);
	}
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// " |> " Step Forward Button Clicked. (Pause State Gets the next I-frame)
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnBnClickedButtonFor()
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	//Gets the next I-frame.
	//
	m_ctrlXnsDevice.FrameAdvance(m_hDevice, m_nControlId, PLAY_FORWARD);
	WLOGD(_T("Step Forward !\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// Select Play Speed 
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnCbnSelchangeComboPlaySpeed()
{
	// (Index 0 : Speed 1), (1: 2), (2: 4), (3: 8), (4: 16), (5: 32), (6: 64)
	int nComboSpeed = m_ctrlPlaySpeedCombo.GetCurSel();                  

	switch(nComboSpeed)
	{
	case SPEED_1:
		m_nForwardSpeed = 1;
		break;

	case SPEED_2:
		// [ XNS ACTIVEX HELP ]
		// -----------------------------------------------------------------------
		// Returns the capabilities of the control module.
		// -----------------------------------------------------------------------
		if (m_ctrlXnsDevice.GetControlCapability(m_hDevice, 1, XCTL_CAP_FSPEED2))
		{
			WLOGD(_T("[Message] (X2) Play Speed Combo Event\n"));
			m_nForwardSpeed = 2;
		}
		else
			m_nForwardSpeed	= 1;
		break;

	case SPEED_4:
		if (m_ctrlXnsDevice.GetControlCapability(m_hDevice, 1, XCTL_CAP_FSPEED4))
		{
			WLOGD(_T("[Message] (X4) Play Speed Combo Event\n"));
			m_nForwardSpeed = 4;
		}
		else
			m_nForwardSpeed	= 1;
		break;

	case SPEED_8:
		if (m_ctrlXnsDevice.GetControlCapability(m_hDevice, 1, XCTL_CAP_FSPEED8))
		{
			WLOGD(_T("[Message] (X8) Play Speed Combo Event\n"));
			m_nForwardSpeed = 8;
		}
		else
			m_nForwardSpeed	= 1;
		break;

	case SPEED_16:
		if (m_ctrlXnsDevice.GetControlCapability(m_hDevice, 1, XCTL_CAP_FSPEED16))
		{
			WLOGD(_T("[Message] (X16) Play Speed Combo Event\n"));
			m_nForwardSpeed = 16;
		}
		else
			m_nForwardSpeed	= 1;
		break;

	case SPEED_32:
		if (m_ctrlXnsDevice.GetControlCapability(m_hDevice, 1, XCTL_CAP_FSPEED32))
		{
			WLOGD(_T("[Message] (X32) Play Speed Combo Event\n"));
			m_nForwardSpeed = 32;
		}
		else
			m_nForwardSpeed	= 1;
		break;

	case SPEED_64:
		if (m_ctrlXnsDevice.GetControlCapability(m_hDevice, 1, XCTL_CAP_FSPEED64))
		{
			WLOGD(_T("[Message] (X64) Play Speed Combo Event\n"));
			m_nForwardSpeed = 64;
		}
		else
			m_nForwardSpeed	= 1;
		break;
	}

	// -----------------------------------------------------------------------
	// Plays the multimedia at a specified speed.
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.Play(
		m_hDevice,															// [in] Device handle. This value is returned from CreateDevice().
		m_nControlId,														// [in] Control ID.
		(double)m_nForwardSpeed);											// [in] Play speed.
	WLOGW(_T("Play !\n"));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// Select Record Play Time
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnNMReleasedcaptureSliderRectime(NMHDR *pNMHDR, LRESULT *pResult)
{
	long CurrentTime = m_ctrlTimebar.GetPos();

	if (CurrentTime < m_ctrlTimebar.GetRangeMin() || CurrentTime > m_ctrlTimebar.GetRangeMax())
		return;

	if (m_ctrlXnsDevice.IsPlaying(m_hDevice))
	{
		MessageBox(_T("Please Stop playing first"), MB_OK);
		return;
	}
	CurrentTime = m_ctrlXnsDevice.LocalTimeToDeviceUTC(m_hDevice, CurrentTime);
	m_ctrlXnsDevice.Seek(m_hDevice, m_nControlId, CurrentTime);

	*pResult = 0;
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ Device Control Event.
// This event occurs if the frame time displayed on the screen is changed. 
// This happens every second video is played.
// -----------------------------------------------------------------------
void CNVRTextPlayBackDlg::OnFrameTimeChangedXnssdkwindowctrl1(long tFrameTime)
{
	long Year, Month, Day, Hour, Min, Sec;
	m_ctrlXnsDevice.TimetToDate(tFrameTime, &Year, &Month, &Day, &Hour, &Min, &Sec);
	m_strCurTime.Format(_T("%02d:%02d:%02d"), Hour, Min, Sec);
	SetDlgItemText(IDC_STR_CURTIME, m_strCurTime);

	m_ctrlTimebar.SetPos(tFrameTime);
	m_ctrlTimebar.Invalidate(FALSE);
}


void CNVRTextPlayBackDlg::OnSearchOverLapXnssdkdevicectrl1(long nDeviceID, long tStart, long tEnd, long nTrackNum, long nTrackValue)
{
	UINT* trackValue = (UINT*)nTrackValue;
	m_nTrackNum = nTrackNum;

	m_ctrlTrackNum.ResetContent();
	for(int i = 0; i < m_nTrackNum; i++)
	{
		CString strTrack;
		m_nTrackValue[i] = trackValue[i];
		strTrack.Format(_T("%d"), i);
		m_ctrlTrackNum.AddString(strTrack);
	}
	m_ctrlTrackNum.SetCurSel(0);
	m_nTrackValue[m_nTrackNum] = '\0';
}


void CNVRTextPlayBackDlg::OnCbnSelchangeComboTrack()
{
	long tStart = m_ctrlXnsDevice.DateToTimet(m_nYear, m_nMonth, m_nDay, 0, 0, 0);
	long tEnd = m_ctrlXnsDevice.DateToTimet(m_nYear, m_nMonth, m_nDay,	23,	59,	59);

	long tUTCStart = m_ctrlXnsDevice.LocalTimeToDeviceUTC(m_hDevice,	tStart);
	long tUTCEnd  = m_ctrlXnsDevice.LocalTimeToDeviceUTC(m_hDevice, tEnd);

	if(m_nTrackNum != 0)
	{
		int nTrackNum = m_ctrlTrackNum.GetCurSel();

		m_ctrlXnsDevice.SearchDayOverLap(
			m_hDevice,														// [in] Device handle. This value is returned from CreateDevice().
			m_nControlId,													// [in] Control ID. 
			tUTCStart,														// [in] Play start time. Format: UTC time_t.
			tUTCEnd,														// [in] Play start time. Format: UTC time_t.
			REC_TYPE_ALL,													// [in] Recording type.
			m_nTrackValue[nTrackNum]);										// [in] Overlapped Track Value
	}
}


void CNVRTextPlayBackDlg::OnCbnSelchangeComboModelList()
{
	CString strData;
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), strData);

	if((strData == "Samsung Network Camera/Encoder") || (strData == "Samsung NVR"))
		m_bSupportedSunapi = TRUE;
	else
		m_bSupportedSunapi = FALSE;

	SetDeviceProtocol();
}


void CNVRTextPlayBackDlg::SetDeviceProtocol()
{
	m_ctrlSunapi.EnableWindow(FALSE);
	m_nDeviceProtocol = 0;

	if (m_bSupportedSunapi == TRUE) 
	{
		m_ctrlSunapi.EnableWindow(TRUE);
		if( m_ctrlSunapi.GetCheck() )
			m_nDeviceProtocol = XDEVICE_PROTOCOL_SUNAPI;
	}
}

// Control button enable/disable
void CNVRTextPlayBackDlg::setBtnStatus(BUTTON_STATUS nStatus)
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
// 	case STATUS_OPEN:
// 		disconnect = true;
// 		close = true;
// 		play = true;
// 		break;
// 	case STATUS_CLOSE:
// 		disconnect = true;
// 		open = true;
// 		break;
// 	case STATUS_PLAY:
// 		disconnect = true;
// 		close = true;
// 		stop = true;
// 		break;
// 	case STATUS_STOP:
// 		disconnect = true;
// 		close = true;
// 		play = true;
// 		break;
	}

	// Connection Group
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(connect);
	GetDlgItem(IDC_COMBO_MODEL_LIST)->EnableWindow(connect);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_PW)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_PORT2)->EnableWindow(connect);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(connect);

	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(disconnect);
	GetDlgItem(IDC_BUTTON_CHECK_CALENDAR)->EnableWindow(disconnect);
	//GetDlgItem(IDC_COMBO_TRACK)->EnableWindow(disconnect);
	GetDlgItem(IDC_LIST_RECDATA)->EnableWindow(disconnect);
	GetDlgItem(IDC_SLIDER_RECTIME)->EnableWindow(disconnect);	
	GetDlgItem(IDC_BUTTON_STEP_BACK)->EnableWindow(disconnect);
	GetDlgItem(IDC_BUTTON_BP)->EnableWindow(disconnect);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(disconnect);
	GetDlgItem(IDC_BUTTON_FOR)->EnableWindow(disconnect);
	GetDlgItem(IDC_COMBO_PLAY_SPEED)->EnableWindow(disconnect);
	
	m_ctrlRecDataList.EnableWindow(disconnect);
	m_ctrlRecTextList.EnableWindow(disconnect);
	m_ctrlPlaySpeedCombo.EnableWindow(disconnect);
	m_ctrlMonthCalendar.EnableWindow(disconnect);
	m_ctrlMonthCalendarText.EnableWindow(disconnect);
	m_ctrlTimebar.EnableWindow(disconnect);
}

void CNVRTextPlayBackDlg::OnOK()
{
	//CDialog::OnOK();
}

void CNVRTextPlayBackDlg::OnBnClickedCheckSunapi()
{
	SetDeviceProtocol();
}


void CNVRTextPlayBackDlg::OnBnClickedButtonOpenText()
{
	//long tStart = m_ctrlXnsDevice.DateToTimet(m_nYear, m_nMonth, m_nDay, 0, 0, 0);
	//long tEnd = m_ctrlXnsDevice.DateToTimet(m_nYear, m_nMonth, m_nDay,	23,	59,	59);
	long tStart = m_ctrlXnsDevice.DateToTimet(m_nYear, m_nMonth, m_nDay, 18, 24, 0);
	long tEnd = m_ctrlXnsDevice.DateToTimet(m_nYear, m_nMonth, m_nDay,	18,	26,	00);

	long tUTCStart = m_ctrlXnsDevice.LocalTimeToDeviceUTC(m_hDevice, tStart);
	long tUTCEnd  = m_ctrlXnsDevice.LocalTimeToDeviceUTC(m_hDevice, tEnd);

	UpdateData(TRUE);
	
	if(m_nTrackNum != 0)
	{
		int nTrackNum = m_ctrlTrackNum.GetCurSel();
		if(m_ctrlXnsDevice.OpenText(m_hDevice, m_nTextControlId+m_nTextIndex, XMEDIA_TEXT_PLAYBACK, tUTCStart, tUTCEnd, m_nTrackValue[nTrackNum]) != ERR_SUCCESS)
		//if(m_ctrlXnsDevice.OpenText(m_hDevice, m_nTextControlId+m_nTextIndex, XMEDIA_TEXT_BACKUP, tUTCStart, tUTCEnd, m_nTrackValue[nTrackNum]) != ERR_SUCCESS)
		{
			WLOGD(_T("Invalid device..\n"));
			return;
		}
	}
	
	WLOGD(_T("Open text...control id=[%d]\n"), m_nTextControlId+m_nTextIndex);
}


void CNVRTextPlayBackDlg::OnBnClickedButtonCloseText()
{
	UpdateData(TRUE);
	m_ctrlXnsDevice.CloseText(m_hDevice, m_nTextControlId+m_nTextIndex, XMEDIA_TEXT_PLAYBACK);

	WLOGD(_T("Close text...control id=[%d]\n"), m_nTextControlId+m_nTextIndex);
}


void CNVRTextPlayBackDlg::OnNewMediaXnssdkdevicectrl1(long nDeviceID, long nControlID, long nMediaType, long hMediaData, long nInputType, long nFrameType, long nFrameTime, long nFrameSize, long nTimestamp)
{
	if(nInputType == XINPUT_METADATA)
	{
		int metaDataHeaderSize = 224;
		int dataSize = nFrameSize - metaDataHeaderSize;

		byte* getData = new byte[dataSize+1];
		memset(getData, 0, sizeof(getData));

		memcpy(getData,(int*)((byte*)hMediaData+metaDataHeaderSize), dataSize+1);

		WLOGTEXT(_T("%s\n"), (CString)getData);
		delete[] getData;
	}
}


void CNVRTextPlayBackDlg::OnBnClickedButtonCheckCalendarText()
{
	UpdateData(FALSE);
	SYSTEMTIME CurTime;
	m_ctrlMonthCalendar.GetCurSel(&CurTime);
	long Year = CurTime.wYear;
	long Month = CurTime.wMonth;

	long TargetMonth = m_ctrlXnsDevice.DateToTimet(Year, Month, 1, 0, 0, 0);
	TargetMonth = m_ctrlXnsDevice.LocalTimeToDeviceUTC(m_hDevice, TargetMonth);

	WLOGD(_T("Search Text Calendar, target year=%d, month=%d\n"), Year, Month);

	int nRet = m_ctrlXnsDevice.SearchTextCalendar(m_hDevice, m_nTextControlId, TargetMonth);
	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("SearchTextCalendar() fail. errorcode =%d(%s)\n"),	nRet, m_ctrlXnsDevice.GetErrorString(nRet));
		return;
	}
}


void CNVRTextPlayBackDlg::OnMcnSelectMonthcalendarText(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMSELCHANGE	*pSelChange = (NMSELCHANGE*)pNMHDR;
	m_seltime = pSelChange->stSelStart;
	m_nYear = m_seltime.wYear;
	m_nMonth = m_seltime.wMonth;
	m_nDay = m_seltime.wDay;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Gets the video recording dates from a specific month. 
	// The result of this function can be obtained from the OnSearchCalendar event.
	// Return Value : Converted values in time_t format.
	// -----------------------------------------------------------------------
	long tStart = m_ctrlXnsDevice.DateToTimet(
		(long)m_nYear,													// [in] Year
		(long)m_nMonth,													// [in] Month
		(long)m_nDay,													// [in] Day
		0,																// [in] Hour
		0,																// [in] Minute
		0);																// [in] Second

	long tEnd = m_ctrlXnsDevice.DateToTimet((long)m_nYear, (long)m_nMonth, (long)m_nDay, 23, 59, 59);															// [in] Second

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local t_time to UTC t_time.
	// Return Value : UTC time_t value.
	// -----------------------------------------------------------------------
	long tUTCStart = m_ctrlXnsDevice.LocalTimeToDeviceUTC(
		m_hDevice,														// [in] Device handle. This value is returned from CreateDevice().
		tStart);														// [in] local time_t value

	long tUTCEnd  = m_ctrlXnsDevice.LocalTimeToDeviceUTC(m_hDevice, tEnd);

	long ret = m_ctrlXnsDevice.SearchOverLap(m_hDevice, tUTCStart, tUTCEnd);
	if(ret != ERROR_SUCCESS)
		return;

	m_ctrlRecTextList.ResetContent();
	m_nTextList = 0;

	UpdateData(TRUE);

	bool isAllMatch = false;
	if( m_ctrlAllMatch.GetCheck() )
		isAllMatch = true;

	m_ctrlXnsDevice.SearchText(m_hDevice, m_nTextControlId, tUTCStart, tUTCEnd, m_nTrackValue[0], isAllMatch, false, m_strSearchText);
	*pResult = 0;
}


void CNVRTextPlayBackDlg::OnSearchTextCalendarXnssdkdevicectrl1(long nDeviceID, long nControlID, long nRecDay)
{
	CString strDay = _T("01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31\n");
	OutputDebugString(strDay);
	long nBitFlag = 0x01;
	CString strRec;
	
	SYSTEMTIME timeFrom;
	SYSTEMTIME timeUntil;
	int nCount = m_ctrlMonthCalendarText.GetMonthRange(&timeFrom, &timeUntil, GMR_DAYSTATE);
	LPMONTHDAYSTATE pDayState;
	pDayState = new MONTHDAYSTATE[nCount];
	memset(pDayState, 0, sizeof(MONTHDAYSTATE) * nCount);
	int nIndex = (timeFrom.wDay == 1) ? 0 : 1;
	
	for (int i=0; i<31; i++)
	{
		if (nRecDay & nBitFlag)
		{
			strRec = " 1 ";
			pDayState[nIndex] |= 1<<i;
		}
		else
			strRec = " 0 ";
	
		OutputDebugString(strRec);
		nBitFlag <<=1;
	}
	OutputDebugString(_T("\n"));
	
	VERIFY(m_ctrlMonthCalendarText.SetDayState(nCount, pDayState));
	delete[] pDayState;
}


void CNVRTextPlayBackDlg::OnSearchTextListXnssdkdevicectrl1(long nDeviceID, long nControlID, LPCTSTR szLinkChannel, long tEventTime, long tPlayTime, LPCTSTR szText, long reserved)
{
//	WLOGD(_T("OnSearchTextLis: DeviceID=%d, ControlID=%d, LinkChannel=%s, EventTime=%d, PlayTime=%d, TotalCount=%d, Text=%s\n"),
//		nDeviceID, nControlID, szLinkChannel, tEventTime, tPlayTime, nTotalCount, szText);

	long Year, Month, Day;
	long EventHour, EventMin, EventSec;

	CString strBuffer=_T("");
	
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts local UTC t_time to t_time. 
	// Return Value : Number of blocks of the recording data in the timeline. 
	// -----------------------------------------------------------------------
	long tLocal = m_ctrlXnsDevice.UTCToDeviceLocalTime(m_hDevice, tEventTime);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.TimetToDate(tLocal, &Year, &Month, &Day, &EventHour, &EventMin, &EventSec);
	strBuffer.Format(_T("[%d]tEvnet-%02d:%02d:%02d, Link-%s, Text-%s\n"), ++m_nTextList, EventHour, EventMin, EventSec, szLinkChannel, szText);
	
	m_ctrlRecTextList.AddString(strBuffer);

	CString temp;
	temp.AppendFormat(_T("[%d]EventTime(%d), PlayTime(%d), szText(%s)\n"), m_nTextList, tEventTime, tPlayTime, szText);
	OutputDebugString(temp);

	//DBG_LOG("[%d]EventTime(%d), PlayTime(%d), szText(%d)\n", m_nTextList, tEventTime, tPlayTime, szText);

}


void CNVRTextPlayBackDlg::OnEndSearchTextXnssdkdevicectrl1(long nDeviceID, long nControlID, long nErrorCode)
{
	WLOGD(_T("OnEndSearchText: DeviceID=%d, ControlID=%d, nErrorCode=%d\n"), nDeviceID, nControlID, nErrorCode);
}