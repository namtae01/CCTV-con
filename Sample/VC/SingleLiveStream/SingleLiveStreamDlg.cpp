// SingleLiveStreamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SingleLiveStream.h"
#include "SingleLiveStreamDlg.h"


// Extension header of video
typedef struct									
{
	char					vendor_name[8];	
	unsigned long			major_ver;
	unsigned long			minor_ver;
	unsigned long			header_size;
	unsigned long			media_type;	

	unsigned long			camera_index;
	unsigned long			codec_type;	
	unsigned long			replay_sequence;
	unsigned long			time_stamp;	

	unsigned long			frame_size;
	unsigned long			frame_type;			
	unsigned char           igroup_count;
	unsigned char			pgroup_count;
	unsigned char           exist_bframe;
	unsigned char           bSkip;
	unsigned long			frame_rate;
	unsigned long			is_audiosrc;
	unsigned long			is_videoloss;
	unsigned long			is_alarm;
	unsigned long			is_motion;	
	unsigned long			is_motion_region;
	unsigned long			frame_width;
	unsigned long			frame_height;
	TIME_ZONE_INFORMATION	time_zone;				
	long					rec_time;

	unsigned long			water_mark[4];		

	unsigned short			is_ivevent;			
	unsigned short			reserveds;			
	unsigned long			reserved[2];		
	unsigned long			record_id;
	unsigned long           water_mark_type;    

} XNS_VIDEO_HEADER_TAG;

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
	if( ((UINT)nLen+strMessage.GetLength()) > (m_ctrlEditLog.GetLimitText()) ) \
	{	\
		m_ctrlEditLog.SetWindowText(_T("------ Edit box clear ------\n")); \
		nLen = m_ctrlEditLog.GetWindowTextLength(); \
	} \
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
	if( ((UINT)nLen+strMessage.GetLength()) > (m_ctrlEditLog.GetLimitText()) ) \
	{	\
		m_ctrlEditLog.SetWindowText(_T("------ Edit box clear ------\n")); \
		nLen = m_ctrlEditLog.GetWindowTextLength(); \
	} \
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


// CSingleLiveStreamDlg dialog
#define MODEL_NAME	"Samsung Network Camera/Encoder"
#define LOGIN_ID	"admin"
#define PASSWORD	"4321"
#define IP_ADDRESS	192,168,1,101
#define PORT_NUM	4520
#define HTTP_PORT_NUM 80


// file pointer for writing video data...
// FILE *fp = NULL;

CSingleLiveStreamDlg::CSingleLiveStreamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSingleLiveStreamDlg::IDD, pParent)
	, m_strModelName(_T(""))
	, m_nPort(PORT_NUM)
	, m_strId(_T(LOGIN_ID))
	, m_strPasswd(_T(PASSWORD))
	, m_hDevice(0)
	, m_bIsMediaPlay(0)
	, m_nChannelNo(0)
	, m_nHttpPort(HTTP_PORT_NUM)
	, m_nDeviceProtocol(0)
	, m_nMediaProtocol(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	CString strMessage = _T("");
}

void CSingleLiveStreamDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_CBIndex(pDX, IDC_COMBO_CHANNEL, m_nChannelNo);
	DDV_MinMaxInt(pDX, m_nChannelNo, 0, 16);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_nHttpPort);
	DDX_Control(pDX, IDC_CHECK_SUNAPI, m_ctrlSunapi);
}

BEGIN_MESSAGE_MAP(CSingleLiveStreamDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CSingleLiveStreamDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CSingleLiveStreamDlg::OnBnClickedButtonDisconnect)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CSingleLiveStreamDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSingleLiveStreamDlg::OnBnClickedButtonClose)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CSingleLiveStreamDlg::OnCbnSelchangeComboModelList)
	ON_BN_CLICKED(IDC_CHECK_SUNAPI, &CSingleLiveStreamDlg::OnBnClickedCheckSunapi)
END_MESSAGE_MAP()


// CSingleLiveStreamDlg message handlers

BOOL CSingleLiveStreamDlg::OnInitDialog()
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
	if(idx != CB_ERR) {
		m_ctrlModelList.SetCurSel(idx);
		m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
		UpdateData(FALSE);		
	}

	m_nChannelNo = 2;
	UpdateData(FALSE);
	
	setBtnStatus(SL_STATUS_DISCONNECTED);

	// fp = fopen("C:\\test.dat", "w");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSingleLiveStreamDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSingleLiveStreamDlg::OnPaint()
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
HCURSOR CSingleLiveStreamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSingleLiveStreamDlg::OnBnClickedButtonConnect()
{
	// TODO: Add your control notification handler code here
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
		m_hDevice,					// [in] Device handle
		_T("Samsung"),				// [in] Fixed as 'Samsung'
		m_strModelName,				// [in] Name of model to connect to. The maximum length allowed is 126-byte.
		XADDRESS_IP,				// [in] Address type
		strIpAddress,				// [in] actual address according to address type.
		m_nPort,					// [in] Port number
		m_nHttpPort,							// [in] Port number for web access	
		m_strId,					// [in] Login ID
		m_strPasswd,				// [in] Password
		m_nDeviceProtocol,
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

void CSingleLiveStreamDlg::OnBnClickedButtonDisconnect()
{
	OnBnClickedButtonClose();

	// Disconnects from the device.
	m_ctrlXnsDevice.Disconnect(m_hDevice);
	WLOGD(_T("Disconnect\n"));

	m_bIsMediaPlay = false;
	setBtnStatus(SL_STATUS_DISCONNECTED);
}



BEGIN_EVENTSINK_MAP(CSingleLiveStreamDlg, CDialog)
	ON_EVENT(CSingleLiveStreamDlg, IDC_XNSSDKDEVICECTRL, 10, CSingleLiveStreamDlg::OnDeviceStatusChangedXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSingleLiveStreamDlg, IDC_XNSSDKDEVICECTRL, 3, CSingleLiveStreamDlg::OnConnectFailedXnssdkdevicectrl, VTS_I4 VTS_I4)
	ON_EVENT(CSingleLiveStreamDlg, IDC_XNSSDKDEVICECTRL, 20, CSingleLiveStreamDlg::OnNewMediaXnssdkdevicectrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs if the device status has changed. It occurs if the 
// application uses Connect() to connect or reconnect to the device after 
// disconnected. When reconnecting, the third argument nDeviceStatus is 
// true, all media must be reopened using ReopenAllStream().
// -----------------------------------------------------------------------
void CSingleLiveStreamDlg::OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
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
void CSingleLiveStreamDlg::OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode)
{
	WLOGD(_T("Disconnected: deviceID=%d, errcode=[%d](%s)\n"),
			nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode));
	setBtnStatus(SL_STATUS_DISCONNECTED);
}



static __int64 GetClockCountX()
{
	LARGE_INTEGER freq, count;	
	QueryPerformanceFrequency(&freq);	// clocks per second
	QueryPerformanceCounter(&count);

	return count.QuadPart * CLOCKS_PER_SEC / freq.QuadPart;
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This event occurs when the application receives the frame data. 
// If the application uses OpenStream() to request stream data, 
// then the frame data will be transferred through this event.
// -----------------------------------------------------------------------
void CSingleLiveStreamDlg::OnNewMediaXnssdkdevicectrl(long nDeviceID, long nControlID, long nMediaType, 
		long hMediaData, long nInputType, long nFrameType, long nFrameTime, long nFrameSize, long nTimestamp)
{
	static unsigned int before_tick = 0;
	static __int64 before_clock = 0;
	static long before_timestamp = 0;

//	WLOGD(_T("OnNewMedia():: deviceID=%d, controlID=%d, mediaType=%d, inputType=%d\n"),
//			nDeviceID, nControlID, nMediaType, nInputType);
// 	WLOGD(_T("OnNewMedia():: frameType=%d, frameTime=%d, frameSize=%d, timeStatmp=%d\n"),
// 		nFrameType, nFrameTime, nFrameSize, nTimestamp);

// writing video data into a file
// 	char *ptr = (char *)hMediaData;
 	if (nInputType==XINPUT_VIDEO)
 	{
 		XNS_VIDEO_HEADER_TAG * tmp;
 		tmp = (XNS_VIDEO_HEADER_TAG *)hMediaData;
		unsigned int clock_time = tmp->water_mark[3];

		__int64 app_clock = GetClockCountX();
		if (before_tick != 0)
		{
			long timestamp_offset = nTimestamp - before_timestamp;
			//DBG_LOG(_T("TIME OFFSET = %u/%u\n"), clock_time-before_tick,
			//	app_clock-before_clock);
			//DBG_LOG(_T("TIME STAMP OFFSET = %u\n"), timestamp_offset);
		}
		before_tick = clock_time;
		before_clock = app_clock;
		before_timestamp = nTimestamp;

		long nRet = m_ctrlXnsWindow.PushMedia(hMediaData);

// 		fwrite(ptr+296, sizeof(char), nFrameSize-296, fp);
 	}
	

// 	long frame_time = m_ctrlXnsWindow.GetFrameTime(hMediaData);
// 	long frame_size = m_ctrlXnsWindow.GetFrameSize(hMediaData);
// 	long frame_type = m_ctrlXnsWindow.GetFrameType(hMediaData);
// 	long time_stamp = m_ctrlXnsWindow.GetTimeStamp(hMediaData);
// 	long input_type = m_ctrlXnsWindow.GetInputType(hMediaData);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// @ ActiveX SDK Window Control Member Function.
	// Transfers stream data to XnsSdkWindow so that the media stream 
	// will be displayed on the window after decoded.
	// If XnsSdkDevice::OpenStream is called, the stream data will be transferred 
	// to the application from the OnNewMedia event.
	// Then, the application should use PushMedia to forward the stream data to XnsSdkWindow 
	// for decoding so that the video is properly displayed on the screen. 
	// This function is valid only within the event handler of the OnNewMedia event.
	// -----------------------------------------------------------------------
	else if(nInputType == XINPUT_METADATA)
	{
		int metaDataHeaderSize = 224;
		int dataSize = nFrameSize - metaDataHeaderSize;

		byte* getData = new byte[dataSize+1];
		memset(getData, 0, sizeof(getData));

		memcpy(getData,(int*)((byte*)hMediaData+metaDataHeaderSize), dataSize+1);

		//WLOGD(_T("Disconnected: deviceID=%d, errcode=[%d](%s)\n"),

		WLOGD(_T("MetaData : %s"),(CString)getData);

	}

	

// 	WLOGW(_T("GetFrameTime() :: %d\n, GetFrameSize() :: %d\n"), frame_time, frame_size);
// 	WLOGW(_T("GetFrameType() :: %d\n, GetTimeStamp() :: %d\n"), frame_type, time_stamp);
// 	WLOGW(_T("GetInputType() :: %d\n"), input_type);
// 	WLOGW(_T("PushMedia() :: [%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
}

void CSingleLiveStreamDlg::OnDestroy()
{
	if( m_hDevice )
	{
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


void CSingleLiveStreamDlg::OnBnClickedButtonOpen()
{
	UpdateData(TRUE);
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns the type of control module corresponding to the control ID.
	//
	// < DVR control module structure >
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
	// -----------------------------------------------------------------------
	if (m_ctrlXnsDevice.GetControlType(m_hDevice, 1) & XCTL_DVR)
	{
		// 0 means that open first media stream
		if (m_nChannelNo != 0)
		{
			// DVR control id is start with 2
			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Starts receiving the media stream data from the device. The incoming media 
			// stream will then forwarded to the OnNewMedia event. The application can 
			// decode or forward this data to XnsSdkWindow before playing.
			// -----------------------------------------------------------------------
			long nRet = m_ctrlXnsDevice.OpenStream(
				m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
				m_nChannelNo+1,		// [in] Control ID of video control module. 
				MEDIA_TYPE_LIVE,	// [in] Media type.
				0,					// [in] Play start time. Format: 4-byte time_t.
				0);					// [in] Play end time. Format: 4-byte time_t.
			if(nRet != ERR_SUCCESS)
			{
				WLOGD(_T("Open stream failed..\n"));
				return;
			}

			m_nControlId = m_nChannelNo+1;
			WLOGW(_T("Open stream...control id=[%d]\n"), m_nControlId);
			setBtnStatus(SL_STATUS_OPEN);

			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Adds the media source handle to XnsSdkWindow. 
			// The media source handle is created by XnsSdkDevice. 
			// If the application calls XnsSdkDevice::OpenMedia(), 
			// it will receive media stream from the device and return the MediaSource 
			// handle. The application uses uses Start() to forward the mediasource 
			// handle to XnsSdkWindow so that XnsSdkWindow can obtain stream data. 
			// -----------------------------------------------------------------------
			m_ctrlXnsWindow.Start(0);
			return;
		}


		// Returns the number of control modules. The application can get 
		// the number of a specific type of control modules, and can get 
		// also the whole number of video recorders or cameras.
		int nCount = m_ctrlXnsDevice.GetControlCount(m_hDevice, XCTL_CAMERA);
		for(int i=0; i<nCount ; i++)
		{
			// Returns the capabilities of the control module.
			if (m_ctrlXnsDevice.GetControlCapability(m_hDevice, i+2, XCTL_CAP_LIVE) &&
				//Gets the status of the control module.
				// DVR control id is start with 2
				m_ctrlXnsDevice.GetControlStatus(m_hDevice, i+2, 1))
			{
				long nRet = m_ctrlXnsDevice.OpenStream(
					m_hDevice,			// [in] Device handle. This value is returned from CreateDevice().
					i+2,				// [in] Control ID of video control module. 
					MEDIA_TYPE_LIVE,	// [in] Media type.
					0,					// [in] Play start time. Format: 4-byte time_t.
					0);					// [in] Play end time. Format: 4-byte time_t.
			
				if(nRet != ERR_SUCCESS)
				{
					WLOGD(_T("Open stream failed..\n"));
					return;
				}
				m_nControlId = i+2;
				WLOGD(_T("Open stream...control id=[%d]\n"), m_nControlId);
				setBtnStatus(SL_STATUS_OPEN);

				m_ctrlXnsWindow.Start(0);
				return;
			}
		}
	}
	else if (m_ctrlXnsDevice.GetControlType(m_hDevice, 1) & (XCTL_NETCAM |XCTL_ENCODER))
	{
		// 0 means that open first media stream
		if (m_nChannelNo != 0)
		{
			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Starts receiving the media stream data from the device. The incoming media 
			// stream will then forwarded to the OnNewMedia event. The application can 
			// decode or forward this data to XnsSdkWindow before playing.
			// -----------------------------------------------------------------------
			// Network camera and encoder control id is start with 3
			long nRet = m_ctrlXnsDevice.OpenStream(m_hDevice, m_nChannelNo+2, MEDIA_TYPE_LIVE,	0, 0);
			if(nRet != ERR_SUCCESS)
			{
				WLOGD(_T("Open stream failed..\n"));
				return;
			}
			m_nControlId = m_nChannelNo+2;
			WLOGW(_T("Open stream...control id=[%d]\n"), m_nControlId);
			setBtnStatus(SL_STATUS_OPEN);

			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Adds the media source handle to XnsSdkWindow. 
			// The media source handle is created by XnsSdkDevice. 
			// If the application calls XnsSdkDevice::OpenMedia(), 
			// it will receive media stream from the device and return the MediaSource 
			// handle. The application uses uses Start() to forward the mediasource 
			// handle to XnsSdkWindow so that XnsSdkWindow can obtain stream data. 
			// -----------------------------------------------------------------------
			m_ctrlXnsWindow.Start(0);
			return;
		}

		
		int nCount = m_ctrlXnsDevice.GetControlCount(m_hDevice, XCTL_VIDEO);
		for(int i=1; i<nCount ; i++)
		{
			// Network camera and encoder control id is start with 3
			if (m_ctrlXnsDevice.GetControlCapability(m_hDevice, i+3, XCTL_CAP_LIVE) &&
				m_ctrlXnsDevice.GetControlStatus(m_hDevice, i+3, 1))
			{
				long nRet = m_ctrlXnsDevice.OpenStream(m_hDevice, i+3, MEDIA_TYPE_LIVE,	0, 0);
				
				if(nRet != ERR_SUCCESS)
				{
					WLOGD(_T("Open stream failed..\n"));
					return;
				}
				m_nControlId = i+3;
				WLOGD(_T("Open stream...control id=[%d]\n"), m_nControlId);
				setBtnStatus(SL_STATUS_OPEN);

				m_ctrlXnsWindow.Start(0);

				return;
			}
		}
	}
	WLOGD(_T("Invalid device..\n"));
}


void CSingleLiveStreamDlg::OnBnClickedButtonClose()
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Terminates transferring the media stream. 
	// The media stream data will be identified by the control ID.
	// -----------------------------------------------------------------------
	m_ctrlXnsDevice.CloseStream(m_hDevice, m_nControlId, XMEDIA_LIVE);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Stops receiving the stream data from the media source handle.  
	// -----------------------------------------------------------------------
	m_ctrlXnsWindow.Stop();


	WLOGD(_T("Close stream...\n"));
	m_nControlId = 0;
	setBtnStatus(SL_STATUS_CLOSE);
}

// Control button enable/disable
void CSingleLiveStreamDlg::setBtnStatus(SLIVE_BUTTON_STATUS nStatus)
{
	bool conn = false, disconn = false, close = false, open = false;
	switch(nStatus)
	{
	case SL_STATUS_CONNECTED:
		conn = false;
		disconn = true;
		open = true;
		close = false;
		break;
	case SL_STATUS_DISCONNECTED:
		conn = true;
		disconn = false;
		open = false;
		close = false;
		break;
	case SL_STATUS_OPEN:
		conn = false;
		disconn = true;
		open = false;
		close = true;
		break;
	case SL_STATUS_CLOSE:
		conn = false;
		disconn = true;
		open = true;
		close = false;
		break;
	}

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(conn);
	GetDlgItem(IDC_COMBO_MODEL_LIST)->EnableWindow(conn);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PW)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(conn);
	GetDlgItem(IDC_EDIT_PORT2)->EnableWindow(conn);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(conn);
	
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(disconn);
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(open);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(close);

	SetCheckSunapi();
}


void CSingleLiveStreamDlg::OnCbnSelchangeComboModelList()
{
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
	SetCheckSunapi();
}


void CSingleLiveStreamDlg::OnOK()
{
	//CDialog::OnOK();
}


void CSingleLiveStreamDlg::OnBnClickedCheckSunapi()
{
	SetCheckSunapi();
}

void CSingleLiveStreamDlg::SetCheckSunapi()
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