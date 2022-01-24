
// MetaDataDlg.cpp 
//

#include "stdafx.h"
#include "MetaData.h"
#include "MetaDataDlg.h"
#include "afxdialogex.h"

#include "XnsCommon.h"
#include "XnsDeviceInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

#define LOGIN_ID		"admin"
#define PASSWORD		"5tkatjd!"
#define IP_ADDRESS		192,168,7,11
#define PORT_NUM		4520
#define HTTP_PORT_NUM	80
#define MODEL_NAME		"Samsung Network Camera/Encoder"



CMetaDataDlg::CMetaDataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMetaDataDlg::IDD, pParent)
	, m_hDevice(0)
	, m_nControlId(0)
	, m_hMediaSource(0)
	, m_nDeviceProtocol(0)
	, m_nMediaProtocol(0)
	, m_nChannelIndex(0)
	, m_nProfileIndex(0)
	, m_nHttpPort(HTTP_PORT_NUM)
	, m_nPort(PORT_NUM)
	, m_strId(_T(LOGIN_ID))
	, m_strPasswd(_T(PASSWORD))
	, m_strModelName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMetaDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_XNSSDKWINDOWCTRL1, m_ctrlXnsWindow);
	DDX_Control(pDX, IDC_XNSSDKDEVICECTRL1, m_ctrlXnsDevice);
	DDX_Control(pDX, IDC_COMBO_MODEL_LIST, m_ctrlModelList);
	DDX_Control(pDX, IDC_IPADDRESS, m_ctrlIpAddress);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_nHttpPort);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_ID, m_strId);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPasswd);
	DDX_CBString(pDX, IDC_COMBO_MODEL_LIST, m_strModelName);
	DDX_Control(pDX, IDC_LIST_LOG, m_ctrlStatusList);
	DDX_Control(pDX, IDC_LIST_META_DATA, m_ctrlMetadataList);
	DDX_Control(pDX, IDC_CHECK_SUNAPI, m_ctrlSunapi);
}

BEGIN_MESSAGE_MAP(CMetaDataDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMetaDataDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CMetaDataDlg::OnBnClickedButtonDisconnect)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMetaDataDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMetaDataDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CMetaDataDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMetaDataDlg::OnBnClickedButtonStop)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CMetaDataDlg::OnCbnSelchangeComboModelList)
	ON_BN_CLICKED(IDC_CHECK_SUNAPI, &CMetaDataDlg::OnBnClickedCheckSunapi)
END_MESSAGE_MAP()

BOOL CMetaDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	m_ctrlIpAddress.SetAddress(IP_ADDRESS);

	long nRet = m_ctrlXnsDevice.Initialize();
	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("Initialize() fail: errno=[%d]\n"), nRet);
	}
	DBG_LOG(_T("Start\n"));

	nRet = m_ctrlXnsWindow.Initialize(0,0);
	if(nRet != ERR_SUCCESS)
	{
		WLOGW(_T("Initialize() return=[%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
	}

	long nFind = m_ctrlXnsDevice.FindModel(_T("samsung"));

	long nCount = m_ctrlXnsDevice.GetFindSize(nFind);

	CString strModel;
	for(int i = 0; i<nCount ; i++)
	{
		strModel = m_ctrlXnsDevice.GetFindString(nFind, i);
		m_ctrlModelList.AddString(strModel);
	}
	m_ctrlXnsDevice.CloseFind(nFind);

	m_ctrlModelList.SetCurSel(0);
	int idx = m_ctrlModelList.FindStringExact(0, _T(MODEL_NAME));
	if(idx != CB_ERR)
	{
		m_ctrlModelList.SetCurSel(idx);
		m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
		if(m_strModelName == "Samsung Network Camera/Encoder"){
			
		}

		UpdateData(FALSE);
	}


	UpdateData(TRUE);


	setBtnStatus(STATUS_DISCONNECTED);
	
	return TRUE; 
}

void CMetaDataDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CMetaDataDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CMetaDataDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMetaDataDlg::OnBnClickedButtonConnect()
{
	UpdateData(TRUE);
	CString strIpAddress;
	BYTE a1, a2, a3, a4;
	m_ctrlIpAddress.GetAddress(a1, a2, a3, a4);
	strIpAddress.Format(_T("%d.%d.%d.%d"), a1, a2, a3, a4);

	if(m_hDevice !=0 )
	{
		m_ctrlXnsDevice.ReleaseDevice(m_hDevice);
		m_hDevice = NULL;
	}

	long device_id = m_ctrlXnsDevice.CreateDeviceEx();
	m_hDevice = m_ctrlXnsDevice.GetDeviceHandle(device_id);

	if(m_hDevice == 0)
	{
		WLOGD(_T("CreateDevice() fail\n"));
	}

	m_ctrlXnsDevice.SetConnectionInfo2(
		m_hDevice,
		_T("Samsung"),
		m_strModelName,
		XADDRESS_IP,
		strIpAddress,
		m_nPort,
		m_nHttpPort,
		m_strId,
		m_strPasswd,
		m_nDeviceProtocol,
		m_nMediaProtocol
		);

	WLOGD(_T("Connect. IP=%s, VPN port=%d, HTTP port=%d, Id=%s, Password=%s, Device protocol=%d, Media protocol=%d\n"), 
		strIpAddress, m_nPort, m_nHttpPort, m_strId, m_strPasswd, m_nDeviceProtocol, m_nMediaProtocol);

	long nRet = m_ctrlXnsDevice.ConnectNonBlock(
		m_hDevice,
		TRUE,
		TRUE);

	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("ConnectNonBlock() fail: errno=[%d](%s)\n"), nRet, m_ctrlXnsDevice.GetErrorString(nRet));
		setBtnStatus(STATUS_DISCONNECTED);
	}

}


void CMetaDataDlg::OnBnClickedButtonDisconnect()
{
	//Media Close

// 	if (m_ctrlXnsWindow.IsMedia() == TRUE)
// 	{
// 		m_hMediaSource = m_ctrlXnsWindow.Stop();
// 	}
// 
// 	if (m_hMediaSource != 0)
// 	{
// 		m_ctrlXnsDevice.CloseMedia(m_hDevice, m_hMediaSource);
// 		m_hMediaSource = 0;
// 	}

	OnBnClickedButtonClose();

	int nError = m_ctrlXnsDevice.Disconnect(m_hDevice);

	WLOGD(_T("Disconnect\n"));
	m_ctrlXnsDevice.ReleaseDevice(m_hDevice);
	setBtnStatus(STATUS_DISCONNECTED);
}



void CMetaDataDlg::OnDestroy()
{
	if(m_hDevice)
	{
		OnBnClickedButtonStop();
		OnBnClickedButtonClose();
		
		if(m_ctrlXnsDevice.GetDeviceStatus(m_hDevice) == XDEVICE_STATUS_CONNECTED)
		{
			m_ctrlXnsDevice.Disconnect(m_hDevice);
		}
		
		m_ctrlXnsDevice.ReleaseDevice(m_hDevice);
	}

	CDialogEx::OnDestroy();


}


void CMetaDataDlg::OnBnClickedButtonOpen()
{
	if(m_ctrlXnsDevice.GetDeviceStatus(m_hDevice) != XDEVICE_STATUS_CONNECTED)
	{
		WLOGD(_T("Not Connected..\n"));
		return;
	}
	if(m_hMediaSource)
	{
		WLOGD(_T("Media stream was already opend.. close and reopen\n"));
		m_ctrlXnsDevice.CloseMedia(m_hDevice, m_hMediaSource);
		m_hMediaSource = 0;
	}

	UpdateData(TRUE);

	WLOGD(_T("Open media stream::channel(%d), profile(%d)\n"), m_nChannelIndex+1, m_nProfileIndex+1);
	
	m_nControlId = m_ctrlXnsDevice.GetVideoControlID(m_hDevice, m_nChannelIndex+1, m_nProfileIndex+1);
	if( m_ctrlXnsDevice.OpenMedia(m_hDevice, m_nControlId, MEDIA_TYPE_LIVE, 0, 0, &m_hMediaSource) == ERR_SUCCESS )
	{
		WLOGW(_T("Open media...control id=[%d]\n"), m_nControlId);
		setBtnStatus(STATUS_OPEN);
		return;
	}
	
	WLOGD(_T("Invalid device..\n"));
}


void CMetaDataDlg::OnBnClickedButtonClose()
{
	// TODO: Add your control notification handler code here
	OnBnClickedButtonStop();

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


void CMetaDataDlg::OnBnClickedButtonPlay()
{
	int nError = m_ctrlXnsWindow.Start(m_hMediaSource);
	if(nError == ERR_SUCCESS)
	{
		WLOGD(_T("Media start success...\n"));
		setBtnStatus(STATUS_PLAY);
	}

	else
	{
		WLOGD(_T("Media start Failed...\n"));
		setBtnStatus(STATUS_CLOSE);
		return;
	}
}


void CMetaDataDlg::OnBnClickedButtonStop()
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Stops receiving the stream data from the media source handle.  
	// -----------------------------------------------------------------------
	m_ctrlXnsWindow.Stop();
	WLOGW(_T("Stop receiving stream data...\n"));
	setBtnStatus(STATUS_STOP);
}
BEGIN_EVENTSINK_MAP(CMetaDataDlg, CDialogEx)
	ON_EVENT(CMetaDataDlg, IDC_XNSSDKDEVICECTRL1, 10, CMetaDataDlg::OnDeviceStatusChangedXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CMetaDataDlg, IDC_XNSSDKDEVICECTRL1, 3, CMetaDataDlg::OnConnectFailedXnssdkdevicectrl1, VTS_I4 VTS_I4)
	ON_EVENT(CMetaDataDlg, IDC_XNSSDKDEVICECTRL1, 20, CMetaDataDlg::OnNewMediaXnssdkdevicectrl1, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


void CMetaDataDlg::OnDeviceStatusChangedXnssdkdevicectrl1(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition)
{
	if (nErrorCode != ERR_SUCCESS || nDeviceStatus != 1)
	{
		setBtnStatus(STATUS_DISCONNECTED);
		return;
	}

	WLOGD(_T("Connected: deviceID=%d, display=%s, errcode=%d, deviceStatus=%d\n"),
		nDeviceID, m_ctrlXnsDevice.GetDisplayName(m_hDevice), nErrorCode, nDeviceStatus);
	setBtnStatus(STATUS_CONNECTED);
}



void CMetaDataDlg::OnConnectFailedXnssdkdevicectrl1(long nDeviceID, long nErrorCode)
{
	WLOGD(_T("Disconnected: deviceID=%d, errcode=[%d](%s)\n"),
		nDeviceID, nErrorCode, m_ctrlXnsDevice.GetErrorString(nErrorCode));
	setBtnStatus(STATUS_DISCONNECTED);
}


void CMetaDataDlg::OnCbnSelchangeComboModelList()
{
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
	SetCheckSunapi();	
}


void CMetaDataDlg::OnNewMediaXnssdkdevicectrl1(long nDeviceID, long nControlID, long nMediaType, long hMediaData, long nInputType, long nFrameType, long nFrameTime, long nFrameSize, long nTimestamp)
{
	if(nInputType == XINPUT_VIDEO)
	{
		m_ctrlXnsWindow.PushMedia(hMediaData);
	}
	else if(nInputType == XINPUT_METADATA)
	{
		int metaDataHeaderSize = 224;
		int dataSize = nFrameSize - metaDataHeaderSize;

		byte* getData = new byte[dataSize+1];
		memset(getData, 0, sizeof(getData));

		memcpy(getData,(int*)((byte*)hMediaData+metaDataHeaderSize), dataSize+1);
 		
		WLOGM(_T("MetaData : %s"),(CString)getData);
		
	}

}


// Control button enable/disable
void CMetaDataDlg::setBtnStatus(BUTTON_STATUS nStatus)
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
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_PW)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(connect);
	GetDlgItem(IDC_EDIT_PORT2)->EnableWindow(connect);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(connect);

	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(disconnect);
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(open);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(close);
	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(play);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(stop);

	SetCheckSunapi();
}

void CMetaDataDlg::SetCheckSunapi()
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

void CMetaDataDlg::OnOK()
{
	//CDialogEx::OnOK();
}


void CMetaDataDlg::OnBnClickedCheckSunapi()
{
	SetCheckSunapi();
}
