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
// DeviceInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "DeviceInfoDlg.h"

#include "SdkTestDlg.h"


// CDeviceInfoDlg dialog


// IPCAM SND-7080
// #define LOGIN_ID	"admin"
// #define PASSWORD	"4321"
// #define IP_ADDRESS	192,168,1,101
// #define PORT_NUM	4520
// #define MODEL_NAME	"SND-7080"

// PTZ SNP-5200H
// #define LOGIN_ID	"admin"
// #define PASSWORD	"4321"
// #define IP_ADDRESS	192,168,217,152
// #define PORT_NUM	4520
// #define MODEL_NAME	"SNP-5200H"

//DVR SRD-165X
#define LOGIN_ID	"admin"
#define PASSWORD	"5tkatjd!"
#define IP_ADDRESS	192,168,1,107
#define PORT_NUM	4520
#define HTTP_PORT_NUM 80
#define MODEL_NAME	"Samsung Network Camera/Encoder"


IMPLEMENT_DYNAMIC(CDeviceInfoDlg, CDialog)

CDeviceInfoDlg::CDeviceInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceInfoDlg::IDD, pParent)
	, m_pCtrlXnsDevice(0)
	, m_pCtrlXnsWindowLive(0)
	, m_pCtrlXnsWindowPlayback(0)
	, m_strId(LOGIN_ID)
	, m_nPort(PORT_NUM)
	, m_strPassword(PASSWORD)
	, m_strModelName(_T(""))
	, m_nDeviceProtocol(0)
	, m_nMediaProtocol(0)
	, m_nHttpPort(HTTP_PORT_NUM)
{
	if(pParent)
	{
		CSdkTestDlg *ptr = dynamic_cast<CSdkTestDlg *>(pParent);
		m_pCtrlXnsDevice = &(ptr->m_ctrlXnsDevice);
		m_pCtrlXnsWindowLive = &(ptr->m_ctrlXnsWindowLive);
		m_pCtrlXnsWindowPlayback = &(ptr->m_ctrlXnsWindowPlayback);
		m_pCtrlEditLog = ptr->m_pCtrlEditLog;
		m_pCtrlEditEvent = ptr->m_pCtrlEditEvent;
		m_pHDevice = &(ptr->m_hDevice);
		m_pHMediaSource = &(ptr->m_hMediaSource);
		m_pHMediaSourcePlayback = &(ptr->m_hMediaSourcePlayback);
		m_pNControlId = &(ptr->m_nControlId);
	}

}

CDeviceInfoDlg::~CDeviceInfoDlg()
{
}

void CDeviceInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODEL_LIST, m_ctrlModelList);
	DDX_Text(pDX, IDC_EDIT_ID, m_strId);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Control(pDX, IDC_IPADDRESS, m_ctrlIpAddress);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPassword);
	DDX_CBString(pDX, IDC_COMBO_MODEL_LIST, m_strModelName);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL_LIST, m_ctrlDeviceProtocol);
	DDX_CBIndex(pDX, IDC_COMBO_PROTOCOL_LIST, m_nDeviceProtocol);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL_LIST2, m_ctrlMediaProtocol);
	DDX_CBIndex(pDX, IDC_COMBO_PROTOCOL_LIST2, m_nMediaProtocol);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_nHttpPort);
}


BEGIN_MESSAGE_MAP(CDeviceInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_INIT, &CDeviceInfoDlg::OnBnClickedButtonDeviceInit)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_CREATE, &CDeviceInfoDlg::OnBnClickedButtonDeviceCreate)
	ON_BN_CLICKED(IDC_BUTTON_SET_CONNECTION_INFO, &CDeviceInfoDlg::OnBnClickedButtonSetConnectionInfo)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CDeviceInfoDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT_NONBLOCK, &CDeviceInfoDlg::OnBnClickedButtonConnectNonblock)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CDeviceInfoDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_INFO, &CDeviceInfoDlg::OnBnClickedButtonDeviceInfo)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL_INFO, &CDeviceInfoDlg::OnBnClickedButtonControlInfo)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_RELEASE, &CDeviceInfoDlg::OnBnClickedButtonDeviceRelease)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_LIST, &CDeviceInfoDlg::OnCbnSelchangeComboModelList)
	ON_CBN_SELCHANGE(IDC_COMBO_PROTOCOL_LIST, &CDeviceInfoDlg::OnCbnSelchangeComboProtocolList)
	ON_CBN_SELCHANGE(IDC_COMBO_PROTOCOL_LIST2, &CDeviceInfoDlg::OnCbnSelchangeComboProtocolList2)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS, &CDeviceInfoDlg::OnIpnFieldchangedIpaddress)
END_MESSAGE_MAP()




// CDeviceInfoDlg message handlers


BOOL CDeviceInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlIpAddress.SetAddress(IP_ADDRESS);	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



void CDeviceInfoDlg::OnBnClickedButtonDeviceInit()
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
	long nRet = m_pCtrlXnsDevice->Initialize();
	WLOGD(_T("Initialize()::ret=%d(%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));


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
	long nFind = m_pCtrlXnsDevice->FindModel(_T("samsung"));
	WLOGD(_T("FindModel():: find=%d\n"), nFind);

	// Returns the length of the array that is created using FindVendor(), 
	// FindModel(), and FindDevice().
	long nCount = m_pCtrlXnsDevice->GetFindSize(nFind);
	WLOGD(_T("GetFindSize():: count=%d\n"), nCount);

	CString strModel;
	for (int i = 0 ; i < nCount ; i++)
	{
		// Reurns data of nIndex from the array created using FindVendor() 
		// and FindModel(). If nIndex is larger than the actual array, 
		// "" will be returned.
		strModel = m_pCtrlXnsDevice->GetFindString(nFind, i);
		WLOGD(_T("GetFindString():: model=(%d:%s)\n"), i, strModel);
		int idx = m_ctrlModelList.FindStringExact(0, strModel);
		if(idx == CB_ERR)
		{
			m_ctrlModelList.AddString(strModel);
		}
	}
	// Closes the Find command. Releases the memory space assinged by FindXXX().
	m_pCtrlXnsDevice->CloseFind(nFind);
	WLOGD(_T("CloseFind()\n"));

#if 1 // for test
	m_ctrlModelList.SetCurSel(0);
	int idx = m_ctrlModelList.FindStringExact(0, _T(MODEL_NAME));
	if(idx != CB_ERR) {
		m_ctrlModelList.SetCurSel(idx);
		m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), m_strModelName);
		if(m_strModelName == "Samsung Network Camera/Encoder")
		{
			m_ctrlDeviceProtocol.EnableWindow(TRUE);
		}
		UpdateData(FALSE);
	}
#endif
}

void CDeviceInfoDlg::OnBnClickedButtonDeviceCreate()
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Assigns memory space for saving device information. 
	// This function will return the device handle, which the application 
	// can use to control the device.
	// [in] Device ID The value should be a greater integer than 0.
	//      Minimum value: 1 , Maximum value: 3000
	// -----------------------------------------------------------------------

	if(*m_pHDevice==0)
	{
		*m_pHDevice = m_pCtrlXnsDevice->CreateDevice(1);
		WLOGD(_T("CreateDevice()::device id=%d\n"), *m_pHDevice);
	}
	else 
	{
		WLOGD(_T("Already create device...\n"));
	}
}

void CDeviceInfoDlg::OnBnClickedButtonSetConnectionInfo()
{
	GET_XNS_PARAM()

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
	m_pCtrlXnsDevice->SetConnectionInfo2(
		m_hDevice,					// [in] Device handle
		_T("Samsung"),				// [in] Fixed as 'Samsung'
		m_strModelName,				// [in] Name of model to connect to. The maximum length allowed is 126-byte.
		XADDRESS_IP,				// [in] Address type
		strIpAddress,				// [in] actual address according to address type.
		m_nPort,					// [in] Port number
		m_nHttpPort,							// [in] Port number for web access	
		m_strId,					// [in] Login ID
		m_strPassword,				// [in] Password
		m_nDeviceProtocol,
		m_nMediaProtocol
		);
	WLOGD(_T("SetConnectionInfo():: type=XADDRESS_IP, model=%s, ip=%s, port=%d, deviceProtocol=%d, mediaProtocol=%d\n"),
		m_strModelName, strIpAddress, m_nPort, m_nDeviceProtocol, m_nMediaProtocol); 
	WLOGD(_T("SetConnectionInfo():: id=%s, password=%s\n"),m_strId, m_strPassword);
}

void CDeviceInfoDlg::OnBnClickedButtonConnect()
{
	GET_XNS_PARAM()

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Enables the application to connect to the device using the connection 
	// information. As the connection information should be specified using 
	// SetConnectionInfo(), this function will operate as a blocking function. 
	// If the network connection is unstable, it will take a max of 30 seconds 
	// to perform this function.
	// <Remarks>
	// When an instance of XNS ActiveX Device Control tries more than one 
	// connection to same device, MAC address conflict occurs to cause 
	// connection failure. 
	// <Caution>
	// XNS Active Device Control instance should be constructed once within 
	// a process. So be careful that you might not call this Initialize 
	// function once more.
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->Connect(
		m_hDevice,		// [in] Device handle
		TRUE,			// [in] Flag to decide where to forcibly log in or not.
		TRUE			// [in] If this value is 1, try to connect again.
		);
	WLOGD(_T("Connect()::ret=%d(%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CDeviceInfoDlg::OnBnClickedButtonConnectNonblock()
{
	GET_XNS_PARAM()

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
	long nRet = m_pCtrlXnsDevice->ConnectNonBlock(
		m_hDevice,		// [in] Device handle
		TRUE,			// [in] Flag to decide where to forcibly log in or not.
		TRUE			// [in] If this value is 1, try to connect again.
		);
	WLOGD(_T("ConnectNonBlock()::ret=%d(%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CDeviceInfoDlg::OnBnClickedButtonDisconnect()
{
	GET_XNS_PARAM()
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Disconnects from the device.
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->Disconnect(m_hDevice);
	WLOGD(_T("Disconnect()::ret=%d(%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CDeviceInfoDlg::OnBnClickedButtonDeviceRelease()
{
	GET_XNS_PARAM()
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Cancels the memory space assigned for the device information by 
	// CreateDevice(). The device should be disconnected from the application
	// before this function is called.
	// -----------------------------------------------------------------------
	m_pCtrlXnsDevice->ReleaseDevice(m_hDevice);
	*m_pHDevice = NULL;
	WLOGD(_T("ReleaseDevice()\n"));
}



void CDeviceInfoDlg::OnBnClickedButtonDeviceInfo()
{
	GET_XNS_PARAM()
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns the device ID of the given device handle.
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->GetDeviceID(m_hDevice);
	WLOGD(_T("GetDeviceID():: deivceID=%d\n"), nRet);

	// Returns the connection status of the device.
	nRet = m_pCtrlXnsDevice->GetDeviceStatus(m_hDevice);
	WLOGD(_T("GetDeviceStatus():: deviceStatus=%d\n"), nRet);

	// Returns the vendor name of the device.
	CString strName = m_pCtrlXnsDevice->GetVendorName(m_hDevice);
	WLOGD(_T("GetVendorName():: vendorName=%s\n"), strName);

	// Returns the model name of the device.
	strName = m_pCtrlXnsDevice->GetModelName(m_hDevice);
	WLOGD(_T("GetModelName():: modelName=%s\n"), strName);

	// Returns version of the device firmware. This function will be enabled 
	// after the application is connected to the device.
	strName = m_pCtrlXnsDevice->GetVersion(m_hDevice);
	WLOGD(_T("GetVersion():: version=%s\n"), strName);

	// Returns the address type specified in the device.
	nRet = m_pCtrlXnsDevice->GetAddressType(m_hDevice);
	WLOGD(_T("GetAddressType():: addressType=%d\n"), nRet);

	// Returns the IP address specified in the device.
	strName = m_pCtrlXnsDevice->GetIP(m_hDevice);
	WLOGD(_T("GetIP():: ip=%s\n"), strName);

	// Returns the MAC address specified in the device.
	strName = m_pCtrlXnsDevice->GetMac(m_hDevice);
	WLOGD(_T("GetMac():: mac=%s\n"), strName);

	// Returns URL specified in the device. The returned value is valid only 
	// if the address type (nAddressType) is XADDRESS_URL(=2).
	strName = m_pCtrlXnsDevice->GetURL(m_hDevice);
	WLOGD(_T("GetURL():: url=%s\n"), strName);

	// Returns the port number specified in the device.
	nRet = m_pCtrlXnsDevice->GetPort(m_hDevice);
	WLOGD(_T("GetPort():: port=%d\n"), nRet);

	// Returns the HTTP port number specified in the device. This port number 
	// is used when the application connects to the device using the web browser.
	nRet = m_pCtrlXnsDevice->GetHttpPort(m_hDevice);
	WLOGD(_T("GetHttpPort():: httpPort=%d\n"), nRet);

	// Returns the user ID specified in the device. This value is the 
	// same as the value set by SetConnectionInfo().
	strName = m_pCtrlXnsDevice->GetUserID(m_hDevice);
	WLOGD(_T("GetUserID():: userID=%s\n"), strName);

	// Returns the password specified for the device. This value is the 
	// same as the value set by SetConnectionInfo().
	strName = m_pCtrlXnsDevice->GetPassword(m_hDevice);
	WLOGD(_T("GetPassword():: password=%s\n"), strName);

	// Returns the last updated time for the device. You have to call this 
	// function after making at least 1 firmware update before you can get 
	// the valid value. The update time will be recorded in the device's 
	// configuration file in the local PC.
	nRet = m_pCtrlXnsDevice->GetLatestUpdateTime(m_hDevice);
	WLOGD(_T("GetLatestUpdateTime():: latest update time=%d\n"), nRet);

	// Returns the device handle corresponding to the given device ID. 
	// When an event occurs, the device ID will be forwarded to the parameter 
	// of the event handler. However, most of XnsSdkDevice functions require 
	// the device handle as a parameter. So you should use this function to 
	// convert device ID with device handler to enable those functions.
	nRet = m_pCtrlXnsDevice->GetDeviceHandle(m_hDevice);
	WLOGD(_T("GetDeviceHandle():: deviceHandle=%d\n"), nRet);

}

void CDeviceInfoDlg::OnBnClickedButtonControlInfo()
{
	GET_XNS_PARAM()

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns the number of control modules. The application can get 
	// the number of a specific type of control modules, and can get 
	// also the whole number of video recorders or cameras.
	// -----------------------------------------------------------------------
	long nCount = m_pCtrlXnsDevice->GetControlCount(m_hDevice, XCTL_ALL);
	WLOGD(_T("GetControlCount():: XCTL_ALL control count=%d\n"), nCount);

	CString strRemoteName, strLocalName;
	long	nDepth, nNumber, nParentId, nType;
	for (int i=1; i<= nCount ; i++)
	{
		// Returns the name of the control module specified in the device.
		strRemoteName = m_pCtrlXnsDevice->GetControlRemoteName(m_hDevice, i);
		WLOGD(_T("GetControlRemoteName():: remoteName=(%d)[%s]\n"), 
			i, strRemoteName);

		// Returns the name of the control module specified in the application. 
		// The default name is “IpAddress:portNumber-channelNumber". 
		// To change the name, you have to use ChangeControlLocalName().
		strLocalName = m_pCtrlXnsDevice->GetControlLocalName(m_hDevice, i);
		WLOGD(_T("GetControlLocalName():: localName=(%d)[%s]\n"), 
			i, strLocalName);

		// Returns the depth of control module corresponding to the control ID.
		nDepth = m_pCtrlXnsDevice->GetControlDepth(m_hDevice, i);
		WLOGD(_T("GetControlDepth():: controlDepth=(%d)[%d]\n"), 
			i, nDepth);

		// Returns the number of control modules corresponding to the control ID.
		nNumber = m_pCtrlXnsDevice->GetControlNumber(m_hDevice, i);
		WLOGD(_T("GetControlNumber():: controlNumber=(%d)[%d]\n"), 
			i, nNumber);

		// Returns the ID of the parent control module.
		nParentId = m_pCtrlXnsDevice->GetParentControlID(m_hDevice, i);
		WLOGD(_T("GetParentControlID():: parentID=(%d)[%d]\n"), 
			i, nParentId);

		// Changes the name of the control module specified in the local PC.
// 		strLocalName.Format(_T("[%d]Local Change Name"), i);
// 		m_pCtrlXnsDevice->ChangeControlLocalName(m_hDevice, i, strLocalName);
// 		WLOGD(_T("ChangeControlLocalName():: Name=(%d)[%s]\n"), i, strLocalName);

		// Returns the type of control module corresponding to the control ID.
		nType = m_pCtrlXnsDevice->GetControlType(m_hDevice, i);
			WLOGD(_T("GetControlType():: controlType=(%d)[%#02x]\n"), 
			i, nType);
	}


	m_nControlId = 0;
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
	if (m_pCtrlXnsDevice->GetControlType(m_hDevice, 1) & XCTL_DVR)
	{
		WLOGD(_T("GetControlType():: XCTL_DVR\n"));
		nCount = m_pCtrlXnsDevice->GetControlCount(m_hDevice, XCTL_CAMERA);
		WLOGD(_T("GetControlCount():: XCTL_CAMERA control count=%d\n"), nCount);
		for(int i=0; i<nCount ; i++)
		{
			// DVR control id is start with 2
			long cid = i+2;

			// Returns the capabilities of the control module.
			if (m_pCtrlXnsDevice->GetControlCapability(m_hDevice, cid, XCTL_CAP_LIVE) &&
				//Gets the status of the control module.
				m_pCtrlXnsDevice->GetControlStatus(m_hDevice, cid, 1))
			{
				WLOGD(_T("GetControlCapability():: XCTL_CAP_LIVE: id=%d\n"), cid);
				WLOGD(_T("GetControlStatus():: XCAMERA_STATUS (ON): id=%d\n"), cid);
				if(m_nControlId==0)
				{
					m_nControlId = cid;
				}
			}
		}
	}
	else if (m_pCtrlXnsDevice->GetControlType(m_hDevice, 1) & (XCTL_NETCAM |XCTL_ENCODER))
	{
		WLOGD(_T("GetControlType():: (XCTL_NETCAM |XCTL_ENCODER)\n"));
		nCount = m_pCtrlXnsDevice->GetControlCount(m_hDevice, XCTL_VIDEO);
		WLOGD(_T("GetControlCount():: XCTL_VIDEO control count=%d\n"), nCount);
		for(int i=0; i<nCount ; i++)
		{
			// Network camera and encoder control id is start with 3
			long cid = i+3;
			if (m_pCtrlXnsDevice->GetControlCapability(m_hDevice, cid, XCTL_CAP_LIVE) &&
				m_pCtrlXnsDevice->GetControlStatus(m_hDevice, cid, 1))
			{
				WLOGD(_T("GetControlCapability():: XCTL_CAP_LIVE: id=%d\n"), cid);
				WLOGD(_T("GetControlStatus():: XCAMERA_STATUS (ON): id=%d\n"), cid);
				if(m_nControlId==0)
				{
					m_nControlId = cid;
				}
			}
		}
	}

	WLOGD(_T("Control ID=%d\n"), m_nControlId);
	*m_pNControlId = m_nControlId;
}


void CDeviceInfoDlg::OnCbnSelchangeComboModelList()
{
	CString strData;
	m_ctrlModelList.GetLBText(m_ctrlModelList.GetCurSel(), strData);
	if((strData == "Samsung Network Camera/Encoder") && (m_nDeviceProtocol==1))
	{
		m_ctrlDeviceProtocol.EnableWindow(TRUE);
		m_ctrlMediaProtocol.EnableWindow(TRUE);
		return;
	}
	m_ctrlDeviceProtocol.EnableWindow(FALSE);
	m_ctrlMediaProtocol.EnableWindow(FALSE);
}



void CDeviceInfoDlg::OnCbnSelchangeComboProtocolList()
{
	CString strData;
	m_ctrlDeviceProtocol.GetLBText(m_ctrlDeviceProtocol.GetCurSel(), strData);

	if(strData == "SVNP")
	{
		m_nDeviceProtocol = XDEVICE_PROTOCOL_UNKNOWN;
		m_ctrlMediaProtocol.EnableWindow(FALSE);
	}
	else if(strData == "SUNAPI")
	{
		m_nDeviceProtocol = XDEVICE_PROTOCOL_SUNAPI;
		m_ctrlMediaProtocol.EnableWindow(TRUE);
	}
}



void CDeviceInfoDlg::OnCbnSelchangeComboProtocolList2()
{
	CString strData;
	m_ctrlMediaProtocol.GetLBText(m_ctrlMediaProtocol.GetCurSel(), strData);

	if(strData == "TCP")
	{
		m_nMediaProtocol = XMEDIA_PROTOCOL_TCP;
	}
	else if(strData == "UDP")
	{
		m_nMediaProtocol = XMEDIA_PROTOCOL_UDP;
	}
	else if(strData == "MULTICAST")
	{
		m_nMediaProtocol = XMEDIA_PROTOCOL_MULTICAST;
	}
}

void CDeviceInfoDlg::ReconnectNewPw(CString strNewPw)
{
	m_strPassword = strNewPw;
	UpdateData(FALSE);

	OnBnClickedButtonDisconnect();
	OnBnClickedButtonSetConnectionInfo();
	OnBnClickedButtonConnect();

}
void CDeviceInfoDlg::OnIpnFieldchangedIpaddress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
