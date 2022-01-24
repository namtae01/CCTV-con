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
// NVRTextLiveDlg.h : header file
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
	STATUS_TEXT_OPEN,
	STATUS_TEXT_CLOSE,
}BUTTON_STATUS;

// CNVRTextLiveDlg dialog
class CNVRTextLiveDlg : public CDialog
{
// Construction
public:
	CNVRTextLiveDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NVRTEXTLIVE_DIALOG };

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
	long				m_nTextControlId;	// TEXT Control ID

	CComboBox			m_ctrlModelList;
	CComboBox			m_ctrlChannel;
	CComboBox			m_ctrlProfile;
	CComboBox			m_ctrlTextList;

	CButton				m_ctrlSunapi;

	CString				m_strModelName;
	CIPAddressCtrl		m_ctrlIpAddress;
	int					m_nDeviceProtocol;	// SUNAPI / Unknown
	
	int					m_nPort;
	int					m_nhttpPort;
	CString				m_strId;
	CString				m_strPasswd;
	bool				m_bIsMediaPlay;
	BOOL				m_bSupportedSunapi;   // TRUE / FALSE

	CEdit				m_ctrlEditLog;
	CEdit				m_ctrlTextLog;
	int					m_nChannelIndex;
	int					m_nProfileIndex;
	int					m_nTextIndex;

public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnCbnSelchangeComboModelList();

	void SetDeviceProtocol();
	void setBtnStatus(BUTTON_STATUS nStatus);

	DECLARE_EVENTSINK_MAP()
	void OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode);	
	
	virtual void OnOK();
	afx_msg void OnBnClickedCheckSunapi();
	afx_msg void OnBnClickedButtonOpenText();
	afx_msg void OnBnClickedButtonCloseText();
	void OnNewMediaXnssdkdevicectrl(long nDeviceID, long nControlID, long nMediaType, long hMediaData, long nInputType, long nFrameType, long nFrameTime, long nFrameSize, long nTimestamp);
	void OnTextOccurXnssdkdevicectrl(long nDeviceID, long nControlID, long tEventUTC, long tPlayUTC, LPCTSTR szValue);
};
