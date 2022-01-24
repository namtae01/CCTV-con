///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2014 by Hanwha Techwin, Inc.
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
// MultiChannelDlg.h : header file
//

#pragma once
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
}BUTTON_STATUS;

#define MAXCHANNEL 16


// CMultiChannelDlg dialog
class CMultiChannelDlg : public CDialogEx
{
// Construction
public:
	CMultiChannelDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	enum { IDD = IDD_MULTICHANNEL_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// XNS Device control and Window control variables
	// -----------------------------------------------------------------------
	CXnssdkdevicectrl1	m_ctrlXnsDevice; //XnsDevice control
	CXnssdkwindowctrl1	m_ctrlXnsWindow1; //XnsWindow control
	CXnssdkwindowctrl1	m_ctrlXnsWindow2;
	CXnssdkwindowctrl1	m_ctrlXnsWindow3;
	CXnssdkwindowctrl1	m_ctrlXnsWindow4;
	CXnssdkwindowctrl1	m_ctrlXnsWindow5;
	CXnssdkwindowctrl1	m_ctrlXnsWindow6;
	CXnssdkwindowctrl1	m_ctrlXnsWindow7;
	CXnssdkwindowctrl1	m_ctrlXnsWindow8;
	CXnssdkwindowctrl1	m_ctrlXnsWindow9;
	CXnssdkwindowctrl1	m_ctrlXnsWindow10;
	CXnssdkwindowctrl1	m_ctrlXnsWindow11;
	CXnssdkwindowctrl1	m_ctrlXnsWindow12;
	CXnssdkwindowctrl1	m_ctrlXnsWindow13;
	CXnssdkwindowctrl1	m_ctrlXnsWindow14;
	CXnssdkwindowctrl1	m_ctrlXnsWindow15;
	CXnssdkwindowctrl1	m_ctrlXnsWindow16;
	CXnssdkwindowctrl1 *m_ptrXnsWindow[MAXCHANNEL];
	
	long				m_hDevice;					//Device handle
	long				m_hMediaSource[MAXCHANNEL]; //Media Stream ID
	CIPAddressCtrl		m_ctrlIpAddress;
	CString				m_strId;
	CString				m_strPasswd;
	int					m_nPort;
	CEdit				m_ctrlEditLog;
	CComboBox			m_ctrlModelList;
	CString				m_strModelName;
	CComboBox			m_comboChannel;

	int					m_nHttpPort;
	int					m_nChannelIndex;
	int					m_nProfileIndex;
	// User defined
	int					m_nDeviceProtocol;			// SUNAPI / SVNP 
	int					m_nMediaProtocol;			// TCP / UDP / MULTICAST
	
	void setBtnStatus(BUTTON_STATUS nStatus);
	void SetCheckSunapi();

public:
	DECLARE_EVENTSINK_MAP()
	void OnConnectFailedXnssdkdevicectrl1(long nDeviceID, long nErrorCode);
	void OnDeviceStatusChangedXnssdkdevicectrl1(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnDestroy();
	
	void setWindow(int nVideo);
	void setWindowPtr(void);
	void Close(void);

	afx_msg void OnCbnSelchangeComboModelList();
	virtual void OnOK();

	CButton m_ctrlSunapi;
	afx_msg void OnBnClickedCheckSunapi();

};
