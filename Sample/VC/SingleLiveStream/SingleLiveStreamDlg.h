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
// SingleLiveStreamDlg.h : header file
//

#pragma once
#include "xnssdkwindowctrl.h"
#include "xnssdkdevicectrl.h"
#include "afxwin.h"
#include "afxcmn.h"

typedef enum
{
	SL_STATUS_CONNECTED = 0,
	SL_STATUS_DISCONNECTED,
	SL_STATUS_OPEN,
	SL_STATUS_CLOSE,
	SL_STATUS_PLAY,
	SL_STATUS_STOP
}SLIVE_BUTTON_STATUS;

// CSingleLiveStreamDlg dialog
class CSingleLiveStreamDlg : public CDialog
{
// Construction
public:
	CSingleLiveStreamDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SINGLELIVESTREAM_DIALOG };

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
	long				m_nControlId;		// Control ID

	CComboBox			m_ctrlModelList;
	CString				m_strModelName;
	CIPAddressCtrl		m_ctrlIpAddress;
	int					m_nPort;
	CString				m_strId;
	CString				m_strPasswd;
	bool				m_bIsMediaPlay;
	void setBtnStatus(SLIVE_BUTTON_STATUS nStatus);
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
//	afx_msg void OnBnClickedButtonPlay();
//	afx_msg void OnBnClickedButtonStop();
	DECLARE_EVENTSINK_MAP()
	void OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode);
	CEdit m_ctrlEditLog;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	void OnNewMediaXnssdkdevicectrl(long nDeviceID, long nControlID, long nMediaType, long hMediaData, long nInputType, long nFrameType, long nFrameTime, long nFrameSize, long nTimestamp);
	int m_nChannelNo;
	int m_nHttpPort;
	int m_nDeviceProtocol;
	int m_nMediaProtocol;
	afx_msg void OnCbnSelchangeComboModelList();
	virtual void OnOK();
	CButton m_ctrlSunapi;
	afx_msg void OnBnClickedCheckSunapi();
	void SetCheckSunapi();
};
