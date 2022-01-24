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
// KOREA
// http://security.hanwhatechwin.com/
///////////////////////////////////////////////////////////////////////////////////
#pragma once

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This files are installed in {$SDK path}\sample_code\include 
// You should include this files
// -----------------------------------------------------------------------


#include "xnssdkwindowctrl1.h"
#include "xnssdkdevicectrl1.h"
#include "afxwin.h"
#include "afxcmn.h"

typedef enum
{
	STATUS_DISCONNECTED = 0,
	STATUS_CONNECTED, 
	STATUS_OPEN,
	STATUS_CLOSE,
	STATUS_PLAY,
	STATUS_STOP
}BUTTON_STATUS;


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

// Macro for ListBox control (Device control)
#define WLOGD(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("[XnsSdkDevice] "));\
	strMessage.AppendFormat(__VA_ARGS__);\
	m_ctrlStatusList.AddString(strMessage);\
	m_ctrlStatusList.SetCurSel(m_ctrlStatusList.GetCount()-1);\
}while(0);

// Macro for ListBox control (Window control)
#define WLOGW(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("[XnsSdkWindow] "));\
	strMessage.AppendFormat(__VA_ARGS__);\
	m_ctrlStatusList.AddString(strMessage);\
	m_ctrlStatusList.SetCurSel(m_ctrlStatusList.GetCount()-1);\
}while(0);

// Macro for ListBox control (Metadata)
#define WLOGM(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("[MetaData] "));\
	strMessage.AppendFormat(__VA_ARGS__);\
	m_ctrlMetadataList.AddString(strMessage);\
	m_ctrlMetadataList.SetCurSel(m_ctrlMetadataList.GetCount()-1);\
}while(0);


class CMetaDataDlg : public CDialogEx
{
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// XNS Device control and Window control variables
	// -----------------------------------------------------------------------

// Construction
public:
	CMetaDataDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// Dialog Data
	enum { IDD = IDD_METADATA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:

	////////////////////// Active X Control Member Data
	CXnssdkwindowctrl1	m_ctrlXnsWindow;
	CXnssdkdevicectrl1	m_ctrlXnsDevice;

	////////////////////// Device Handler
	long				m_hDevice;
	long				m_hMediaSource;
	long				m_nControlId;
	
	/////////////////////// Control Member Data
	CComboBox			m_ctrlModelList;
	CIPAddressCtrl		m_ctrlIpAddress;
	int					m_nHttpPort;
	int					m_nPort;
	CString				m_strId;
	CString				m_strPasswd;
	CString				m_strModelName;
	CListBox			m_ctrlStatusList;
	CListBox			m_ctrlMetadataList;
	CButton				m_ctrlSunapi;

	/////////////////////// User-defined
	int					m_nDeviceProtocol;			// SUNAPI / SVNP 
	int					m_nMediaProtocol;			// TCP / UDP / MULTICAST
	int					m_nChannelIndex;
	int					m_nProfileIndex;
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnCbnSelchangeComboModelList();
	afx_msg void OnBnClickedCheckSunapi();
	DECLARE_EVENTSINK_MAP()

	void OnDeviceStatusChangedXnssdkdevicectrl1(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnConnectFailedXnssdkdevicectrl1(long nDeviceID, long nErrorCode);
	void OnNewMediaXnssdkdevicectrl1(long nDeviceID, long nControlID, long nMediaType, long hMediaData, long nInputType, long nFrameType, long nFrameTime, long nFrameSize, long nTimestamp);

	// User defined
	void setBtnStatus(BUTTON_STATUS nStatus);
	void SetCheckSunapi();	
	virtual void OnOK();
};
