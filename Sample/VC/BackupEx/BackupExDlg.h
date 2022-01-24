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
// BackupExDlg.h : header file
//


#pragma once
#include "xnssdkwindowctrl.h"
#include "xnssdkdevicectrl.h"
#include "afxwin.h"
#include "afxcmn.h"

// xns header file
#include "BackupSearchDlg.h"
#include "ProgressDlg.h"
#include "afxdtctl.h"

typedef enum
{
	SL_STATUS_CONNECTED = 0,
	SL_STATUS_DISCONNECTED,
	SL_STATUS_PLAY,
	SL_STATUS_STOP
}SLIVE_BUTTON_STATUS;

#define SPEED_1			1

// CBackupExDlg dialog
class CBackupExDlg : public CDialog
{
// Construction
public:
	CBackupExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DIALOG_MAIN };

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
	long				m_hFileReader;		// REC File handle
	CString				m_strFile;			// REC File name

	CComboBox			m_ctrlModelList;	
	CString				m_strModelName;
	CButton				m_ctrlSunapi;
	CIPAddressCtrl		m_ctrlIpAddress;
	int					m_nPort;
	int					m_nHttpPort;
	CString				m_strId;
	CString				m_strPasswd;
	int					m_nDeviceProtocol;
	int					m_nMediaProtocol;
	int					m_nChannelIndex;
	int					m_nProfileIndex;
public:
	
	long				m_nProgress;
	CEdit				m_ctrlEditLog;

	void setBtnStatus(SLIVE_BUTTON_STATUS nStatus);
	
	afx_msg void OnCbnSelchangeComboModelList();
	afx_msg void OnBnClickedCheckSunapi();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonBackup();
	afx_msg void OnBnClickedButtonRecplayback();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	void OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode);
	void OnBackupProgressXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode, long nProgress, long tStart, long tEnd);
	void OnMediaOffXnssdkwindowctrl();
	void SetCheckSunapi();
	virtual void OnOK();
};

