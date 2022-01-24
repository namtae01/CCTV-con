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
///////////////////////////////////////////////////////////////////////////////////
// MultipleConnectDlg.h : header file
//

#pragma once
#include "xnssdkdevicectrl.h"
#include "xnssdkwindowctrl.h"
#include "afxwin.h"
#include "afxcmn.h"

// Device Information Struct
typedef struct DEVICEINFO
{
	bool bIsDevice;				
	int nDevice;			
	CString strModel;			// Model name
	int nDeviceProtocol;
	int nMediaProtocol;
	CString strIpAddress;		// IP Address
	int nPort;					// Port number
	int nHttpPort;
	CString strId;				// User ID
	CString strPasswd;			// Password
	long hDevice;				// Device handle
	long hMediaSource;			// Media stream ID
	bool bIsMediaPlay;			// Media play Status
} DEVICEINFO;

typedef enum
{
	STATUS_DISCONNECTED = 0,
	STATUS_CONNECTED, 
	STATUS_OPEN,
	STATUS_CLOSE,
}BUTTON_STATUS;

// CMultipleConnectDlg dialog
class CMultipleConnectDlg : public CDialog
{
// Construction
public:
	CMultipleConnectDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MULTIPLECONNECT_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

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
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// XNS Device control and Window control variables
	// -----------------------------------------------------------------------
	DEVICEINFO			DevInfo[4];				// Device information	
	CXnssdkdevicectrl	m_ctrlXnsDevice;		// XnsDevice control
	CXnssdkwindowctrl	m_ctrlXnsWindow;		// XnsWindow control1
	CXnssdkwindowctrl	m_ctrlXnsWindow2;		// XnsWindow control2
	CXnssdkwindowctrl	m_ctrlXnsWindow3;		// XnsWindow control3
	CXnssdkwindowctrl	m_ctrlXnsWindow4;		// XnsWindow control4
	CXnssdkwindowctrl	*m_ptrXnsWindow;		// XnsWindow control pointer
	
	CComboBox			m_ctrlModelList;		// ComboBox
	CListCtrl			m_ctrlListDevice;		// List	Control
	CEdit				m_ctrlEditLog;			// Edit Control
	CButton				m_ctrlSunapi;

	CString				m_strModelName;			// Model Name
	CIPAddressCtrl		m_ctrlIpAddress;		// IP Address
	int					m_nPort;				// Port Number
	CString				m_strId;				// User ID
	CString				m_strPasswd;			// Password
	long				m_hDevice;				// Device handle
	int					m_nSelItem;				// Selected Item
	int					m_nHttpPort;

	bool				m_bWindowCtrl1;					
	bool				m_bWindowCtrl2;
	bool				m_bWindowCtrl3;
	bool				m_bWindowCtrl4;

	// User defined
	int					m_nDeviceProtocol;	// SUNAPI / SVNP 
	int					m_nMediaProtocol;	// TCP / UDP / MULTICAST
	int					m_nChannelIndex;
	int					m_nProfileIndex;
	long				m_nControlId;
public:
	void CreateDeviceList(void);
	void RefreshDeviceList(void);
	int getWindowCtrl(void);
	void setFalseWindowCtrl(int WindowCtrl);
	void setTrueWindowCtrl(int WindowCtrl);
	void setCtrlXnsWindow(int m_nSelItem);
	bool IsEmptyWindowCtrl(void);
	bool ExceptionHandling(void);
	void InitDeviceInfo(int m_nSelItem);

	afx_msg void OnBnClickedButtonAdd(void);
	afx_msg void OnBnClickedButtonRemove(void);
	afx_msg void OnBnClickedButtonConnect(void);
	afx_msg void OnBnClickedButtonDisconnect(void);
	afx_msg void OnBnClickedButtonPlay(void);
	afx_msg void OnBnClickedButtonStop(void);
	afx_msg void OnNMClickListDevice(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboModelList();
	afx_msg void OnBnClickedCheckSunapi();
	afx_msg void OnDestroy();

	DECLARE_EVENTSINK_MAP()
	void OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode);
	
	virtual void OnOK();
	
	void SetCheckSunapi();
	
};
