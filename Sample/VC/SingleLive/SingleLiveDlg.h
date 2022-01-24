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
// http://www.samsungtechwin.co.kr
///////////////////////////////////////////////////////////////////////////////////
// SingleLiveDlg.h : header file
//

#pragma once
#include "xnssdkwindowctrl.h"
#include "xnssdkdevicectrl.h"
#include "afxwin.h"
#include "afxcmn.h"

typedef enum
{
	STATUS_CONNECTED = 0,
	STATUS_DISCONNECTED,
	STATUS_OPEN,
	STATUS_CLOSE,
	STATUS_PLAY,
	STATUS_STOP
}BUTTON_STATUS;

// CSingleLiveDlg dialog
class CSingleLiveDlg : public CDialog
{
// Construction
public:
	CSingleLiveDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SINGLELIVE_DIALOG };

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
	CXnssdkwindowctrl	m_ctrlXnsWindow;	// XnsWindow control
	CXnssdkdevicectrl	m_ctrlXnsDevice;	// XnsDevice control
	long				m_hDevice;			// Device handle
	long				m_hMediaSource;		// Media stream ID
	long				m_nControlId;		// Control ID

	CComboBox			m_ctrlModelList;
	CButton				m_ctrlSunapi;
	CComboBox			m_ctrlMediaProtocol;
	CIPAddressCtrl		m_ctrlIpAddress;
	CComboBox			m_ctrlChannel;
	CComboBox			m_ctrlProfile;
	CEdit				m_ctrlEditLog;

	CString				m_strModelName;
	BOOL				m_bSupportedSnapi;  // TRUE / FALSE
	int					m_nDeviceProtocol;	// SUNAPI / Unknown
	int					m_nMediaProtocol;	// TCP / UDP / MULTICAST / HTTP
	int					m_nPort;
	int					m_nHttpPort;
	CString				m_strId;
	CString				m_strPasswd;
	bool				m_bIsMediaPlay;
			
	int					m_nChannelIndex;
	int					m_nProfileIndex;

public:
	// User-Defined Functions.
	void SetDeviceProtocol();
	void setBtnStatus(BUTTON_STATUS nStatus);

	// Device Control Event Functions.
	void OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode);	

	// MFC Window Control Functions. 
	afx_msg void OnCbnSelchangeComboModelList();
	afx_msg void OnBnClickedCheckSunapi();
	afx_msg void OnCbnSelchangeComboProtocolList();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonSnapshotBmp();
	afx_msg void OnBnClickedButtonSnapshotJpeg();
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
		
	virtual void OnOK();

};
