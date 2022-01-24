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
// ListenTalkDlg.h : header file
//

#pragma once
#include "xnssdkwindowctrl.h"
#include "xnssdkdevicectrl.h"
#include "afxwin.h"
#include "afxcmn.h"

// import winmm.lib
#pragma comment(lib, "winmm")
#include <mmsystem.h>


typedef enum
{
	SL_STATUS_CONNECTED = 0,
	SL_STATUS_DISCONNECTED,
	SL_STATUS_PLAY,
	SL_STATUS_STOP
}SLIVE_BUTTON_STATUS;


// CListenTalkDlg dialog
class CListenTalkDlg : public CDialog
{
// Construction
public:
	CListenTalkDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LISTENTALK_DIALOG };

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
	CComboBox			m_ctrlModelList;
	CString				m_strModelName;
	CIPAddressCtrl		m_ctrlIpAddress;
	int					m_nPort;
	int					m_nHttpPort;
	CString				m_strId;
	CString				m_strPasswd;
	bool				m_bListen;
	bool				m_bTalk;

	void	setBtnStatus(SLIVE_BUTTON_STATUS nStatus);


public:
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// XNS Device control and Window control variables
	// -----------------------------------------------------------------------
	CXnssdkwindowctrl	m_ctrlXnsWindow;	// XnsWindow control
	CXnssdkdevicectrl	m_ctrlXnsDevice;	// XnsDevice control
	long				m_hDevice;			// Device handle
	long				m_hMediaSource;		// Media stream ID
	long				m_nControlId;		// Control ID
	CRITICAL_SECTION	m_hCritSect;

	int					m_nChannelIndex;
	int					m_nProfileIndex;
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedCheckListen();
	afx_msg void OnBnClickedCheckTalk();
	afx_msg void OnDestroy();
	CEdit m_ctrlEditLog;

	DECLARE_EVENTSINK_MAP()
	void OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode);

	afx_msg void OnBnClickedButtonRec();
	afx_msg void OnBnClickedButtonGo();

	afx_msg void OnBnClickedButtonSendAudio();
	afx_msg void OnBnClickedButtonStopAudio();

	
private:
	CComboBox m_ctrlChannel;
	CComboBox m_ctrlBps;
	CComboBox m_ctrlSps;
	long m_nSendBytes;
	int m_nBps;
	int m_nChannel;
	int m_nSps;
	bool m_bSendAudio;
	
public:
	afx_msg void OnBnClickedButtonSendAudio2();
	afx_msg void OnBnClickedButtonStopAudio2();
	int m_nDeviceProtocol;
	afx_msg void OnCbnSelchangeComboModelList();
	int m_nMediaProtocol;
	afx_msg void OnCbnSelchangeComboMprotocolList();
	virtual void OnOK();
	void SetCheckSunapi();
	CButton m_ctrlSunapi;
	afx_msg void OnBnClickedCheckSunapi();
};
