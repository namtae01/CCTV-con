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
// DeviceMiscDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "DeviceMiscDlg.h"

#include "SdkTestDlg.h"

// CDeviceMiscDlg dialog

IMPLEMENT_DYNAMIC(CDeviceMiscDlg, CDialog)

CDeviceMiscDlg::CDeviceMiscDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceMiscDlg::IDD, pParent)
	, m_nPort(0)
	, m_nHttpPort(0)
	, m_strMac(_T(""))
	, m_strPassword(_T(""))
	, m_nDiscardSec(0)
	, m_strXmlKey(_T(""))
	, m_strXmlValue(_T(""))
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

CDeviceMiscDlg::~CDeviceMiscDlg()
{
}

void CDeviceMiscDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIME_DATE, m_ctrlDate);
	DDX_Control(pDX, IDC_DATETIME_TIME, m_ctrlTime);
	DDX_Control(pDX, IDC_IPADDRESS_IP_INSTALL_IP, m_ctrlIp);
	DDX_Control(pDX, IDC_IPADDRESS_IP_INSTALL_SUBNET, m_ctrlSubnetMask);
	DDX_Control(pDX, IDC_IPADDRESS_IP_INSTALL_GATEWAY, m_ctrlGateway);
	DDX_Text(pDX, IDC_EDIT_IP_INSTALL_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_IP_INSTALL_HTTP_PORT, m_nHttpPort);
	DDX_Text(pDX, IDC_EDIT_IP_INSTALL_MAC_ADDRESS, m_strMac);
	DDX_Text(pDX, IDC_EDIT_IP_INSTALL_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_EVENT_DISCARD_TIME, m_nDiscardSec);
	DDX_Control(pDX, IDC_COMBO_DISCARD_EVENT_TYPE, m_ctrlEventType);
	DDX_Text(pDX, IDC_EDIT_XML_KEY, m_strXmlKey);
	DDX_Text(pDX, IDC_EDIT_XML_VALUE, m_strXmlValue);
}


BOOL CDeviceMiscDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlEventType.AddString(_T("ALL"));
	m_ctrlEventType.AddString(_T("ALARM"));
	m_ctrlEventType.AddString(_T("MOTION"));
	m_ctrlEventType.AddString(_T("VIDEOLOSS"));
	m_ctrlEventType.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



BEGIN_MESSAGE_MAP(CDeviceMiscDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DATE_TO_TIME_T, &CDeviceMiscDlg::OnBnClickedButtonDateToTimeT)
	ON_BN_CLICKED(IDC_BUTTON_MISC_AUTOSCAN, &CDeviceMiscDlg::OnBnClickedButtonMiscAutoscan)
	ON_BN_CLICKED(IDC_BUTTON_IP_INSTALL, &CDeviceMiscDlg::OnBnClickedButtonIpInstall)
	ON_BN_CLICKED(IDC_BUTTON_SET_EVENT_DISCARD_TIME, &CDeviceMiscDlg::OnBnClickedButtonSetEventDiscardTime)
	ON_BN_CLICKED(IDC_BUTTON_XML_READ_CONFIG, &CDeviceMiscDlg::OnBnClickedButtonXmlReadConfig)
	ON_BN_CLICKED(IDC_BUTTON_XML_WRITE_CONFIG, &CDeviceMiscDlg::OnBnClickedButtonXmlWriteConfig)
	ON_BN_CLICKED(IDC_BUTTON_XML_DELETE_CONFIG, &CDeviceMiscDlg::OnBnClickedButtonXmlDeleteConfig)
	ON_BN_CLICKED(IDC_BUTTON_XML_FIND_CONFIG_CHILD, &CDeviceMiscDlg::OnBnClickedButtonXmlFindConfigChild)
	ON_CBN_SELCHANGE(IDC_COMBO_DISCARD_EVENT_TYPE, &CDeviceMiscDlg::OnCbnSelchangeComboDiscardEventType)
END_MESSAGE_MAP()


// CDeviceMiscDlg message handlers

void CDeviceMiscDlg::OnBnClickedButtonDateToTimeT()
{
	GET_XNS_PARAM()

	long nYear, nMonth, nDay, nHour, nMin, nSec;
	CTime dayTime;
	m_ctrlDate.GetTime(dayTime);
	nYear = dayTime.GetYear();
	nMonth = dayTime.GetMonth();

	m_ctrlTime.GetTime(dayTime);
	nDay = dayTime.GetDay();
	nHour = dayTime.GetHour();
	nMin = dayTime.GetMinute();
	nSec = dayTime.GetSecond();

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the date (MM/DD/YY) and time (HH:MM:SS) to the time_t format.
	// -----------------------------------------------------------------------
	long ttime = m_pCtrlXnsDevice->DateToTimet(nYear, nMonth, nDay, nHour, nMin, nSec);
	WLOGD(_T("DateToTimet():: time_t = %d\n"), ttime);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
	// -----------------------------------------------------------------------
	m_pCtrlXnsDevice->TimetToDate(ttime, &nYear, &nMonth, &nDay, &nHour, &nMin, &nSec);
	WLOGD(_T("TimetToDate():: %04d-%02d-%2d %02d:%02d:00\n"), 
		nYear, nMonth, nDay, nHour, nMin);

	long utctime = m_pCtrlXnsDevice->LocalTimeToDeviceUTC(m_hDevice, ttime);
	WLOGD(_T("LocalTimeToDeviceUTC():: utcTime=%d\n"), utctime);

	long sttime = m_pCtrlXnsDevice->UTCToDeviceLocalTime(m_hDevice, utctime);
	WLOGD(_T("UTCToDeviceLocalTime():: localTime=%d\n"), sttime);



}

void CDeviceMiscDlg::OnBnClickedButtonMiscAutoscan()
{
	GET_XNS_PARAM()

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Requests a scan for all devices in the network.
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->AutoScan(10);
	WLOGD(_T("AutoScan():: ret = %d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CDeviceMiscDlg::OnBnClickedButtonIpInstall()
{
	GET_XNS_PARAM()

	UpdateData(TRUE);
	CString strIp = _T("");
	CString strSubnet = _T("");
	CString strGateway = _T("");
	
	m_ctrlIp.GetWindowText(strIp);
	m_ctrlSubnetMask.GetWindowText(strSubnet);
	m_ctrlGateway.GetWindowText(strGateway);
	CString strModel = m_pCtrlXnsDevice->GetModelName(m_hDevice);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Makes the network configuration for the network camera. 
	// This function is valid only for the network camera. 
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->IPInstall(
		_T("Samsung"),	// [in] Vendor name. Fixed to 'Samsung'.
		strModel,		// [in] Model name. Obsolete.
		strIp,			// [in] IP address. The maximum length allowed is 256-byte.
		strSubnet,		// [in] Subnet mask. The maximum length allowed is 256-byte.
		strGateway,		// [in] Gateway. The maximum length allowed is 256-byte.
		m_strMac,		// [in] MAC address. Fixed to 12 characters.
		m_nPort,		// [in] Port number of device.
		m_nHttpPort,	// [in] HTTP port number.
		m_strPassword	// [in] Password required for login as admin.
		);

	WLOGD(_T("IPInstall():: ip=%s, subnetMask=%s, gateway=%s, mac=%s, port=%d, httpPort=%d, password=%s, ret=%d(%s)\n"),
		strIp, strSubnet, strGateway, m_strMac, m_nPort, m_nHttpPort, m_strPassword,
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));

	
}


void CDeviceMiscDlg::OnBnClickedButtonSetEventDiscardTime()
{
	GET_XNS_PARAM()
	
	UpdateData(TRUE);
	long sel = m_ctrlEventType.GetCurSel();
	CString strType;
	long	nEventType;
	m_ctrlEventType.GetLBText(sel, strType);

	if(strType.Compare(_T("ALL"))==0)
	{
		nEventType = EVENT_ALL;
	}
	else if(strType.Compare(_T("ALARM"))==0)
	{
		nEventType = EVENT_ALARM;
	}
	else if(strType.Compare(_T("MOTION"))==0)
	{
		nEventType = EVENT_MOTION;
	}
	else if(strType.Compare(_T("VIDEOLOSS"))==0)
	{
		nEventType = EVENT_VIDEOLOSS;
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Specify the event discard time. If an event occurs within this time, 
	// the event will be deleted. 
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->SetEventDiscardTime(nEventType, m_nDiscardSec);
	WLOGD(_T("SetEventDiscardTime():: TYPE=%s, TIME=%dsec, ret=%d(%s)\n"),
		strType, m_nDiscardSec, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
	
}

void CDeviceMiscDlg::OnBnClickedButtonXmlReadConfig()
{
	GET_XNS_PARAM()

	UpdateData(TRUE);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Reads a configuration value from config.xml. 
	// -----------------------------------------------------------------------
	CString strValue = m_pCtrlXnsDevice->ReadConfigValue(m_strXmlKey);
	WLOGD(_T("ReadConfigValue():: valule=%s\n"), strValue)
}

void CDeviceMiscDlg::OnBnClickedButtonXmlWriteConfig()
{
	GET_XNS_PARAM()

	UpdateData(TRUE);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Saves the configuration values in config.xml.
	// -----------------------------------------------------------------------
	long ret = m_pCtrlXnsDevice->WriteConfigValue(m_strXmlKey, m_strXmlValue);
	WLOGD(_T("WriteConfigValue():: key=%s, valule=%s, ret=%d\n"), 
		m_strXmlKey, m_strXmlValue, ret);
}

void CDeviceMiscDlg::OnBnClickedButtonXmlDeleteConfig()
{
	GET_XNS_PARAM()

	UpdateData(TRUE);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Deletes a specific configuration item from config.xml.
	// -----------------------------------------------------------------------
	m_pCtrlXnsDevice->DeleteConfigValue(m_strXmlKey);
	WLOGD(_T("DeleteConfigValue():: key=%s\n"), m_strXmlKey)
}

void CDeviceMiscDlg::OnBnClickedButtonXmlFindConfigChild()
{
	GET_XNS_PARAM()

	UpdateData(TRUE);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Gets the child list from a specific key.
	// -----------------------------------------------------------------------
	long ret = m_pCtrlXnsDevice->FindConfigChildeKeyList(m_strXmlKey);
	WLOGD(_T("FindConfigChildeKeyList():: key=%s, ret=%d\n"), m_strXmlKey, ret);
}

void CDeviceMiscDlg::OnCbnSelchangeComboDiscardEventType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
