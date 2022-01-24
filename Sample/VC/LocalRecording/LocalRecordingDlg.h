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
// LocalRecordingDlg.h : header file
//

#pragma once

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This files are installed in {$SDK path}\sample_code\include 
// You should include this files
// -----------------------------------------------------------------------


#include "XnsCommon.h"
#include "XnsDeviceInterface.h"
#include "XnsMediaInterface.h"

#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "DebugLog.h"
#include "xnssdkdevicectrl.h"
#include "xnssdkwindowctrl.h"
/////////////////////////////////////

typedef enum
{
	STATUS_DISCONNECTED = 0,
	STATUS_CONNECTED, 
	STATUS_OPEN,
	STATUS_CLOSE,
	STATUS_RECORDING,
	STATUS_STOP_RECORDING,
}BUTTON_STATUS;

#if !defined(AFX_EventDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_)
#define AFX_EventDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_

// Define Value
#define ADDRESS_MAX		4
#define EVENT_LOG		6

// Define Handle  
#define HANDLE_FAIL		0
#define MAX_HANDLE		3000

#define SPEED_1			1
/////////////////////////////////////

// CLocalRecordingDlg dialog
class CLocalRecordingDlg : public CDialog
{
public:
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// XNS Device control and Window control variables
	// -----------------------------------------------------------------------

	////////////////////// Active X Control Member Data
	CXnssdkwindowctrl m_ctrlXnsSdkWindow;									// Xns Sdk Device Control Member Data
	CXnssdkdevicectrl m_ctrlXnsSdkDevice;									// Xns Sdk Window Control Member Data
	CXnssdkwindowctrl m_ctrlXnsSdkWindow_Recording;							// Xns Sdk Recording Play Window Control Member Data

	////////////////////// Device Handler
	long m_hDevice;
	long m_hMediaSource;                                                    // Media Source Handler
	long m_nControlId;

	////////////////////// Check Connection and Destroy, Alarm
	BOOL m_bCheckConnect;
	BOOL m_bDestroy;
	BOOL m_bPlay;                                                           // Play Video Button Check
	BOOL m_bRecording;
	long m_bRecType;														// Local Record type (0:Sec, 1:Rec, 2:Avi)
	BOOL m_bPlayRecord;														// Play Local Record Check

	BOOL m_bRec2Avi;
	long m_hFileHandle;

public:
	/////////////////////// Control Member Data
	CListBox m_ctrlStatusList;												// Status List Control Member Data
	CComboBox m_ctrlModelList;												// ComboBox Control Member Data for model list
	CIPAddressCtrl m_ctrlIpAddress;											// IP Addresss Control Member Data
	CEdit m_ctrlPort;														// Port Edit Box Control Member Data
	CEdit m_ctrlHttpPort;													// HTTP Port Edit Box Control Member Data
	CEdit m_ctrlUserID;														// User ID Edit Box Control Member Data
	CEdit m_ctrlPassword;													// User Password Edit Box Control Member Data
	CButton m_ctrlSunapi;
	
	////////////////////// Control String Member Data
	CString m_strModelName;
	CString m_strPassword;													// Password String Member Data
	CString m_strId;							                            // ID String Member Data
	long m_lnPort;									                        // Port Number Member Data
	long m_lnHttpPort;														// HTTP Port Number Member Data

	/////////////////////// User-Defined
	int m_nMediaProtocol;													// TCP / UDP / Multicast
	int	m_nDeviceProtocol;													// SUNAPI / SVNP 
	int	m_nChannelIndex;
	int	m_nProfileIndex;
// Construction
public:
	CLocalRecordingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LOCALRECORDING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;


public:
	// User-Defined Functions.
	void OnInitXnsSdk(void);
	void OnInitModelList(void);
	void OnSetDialog(void);
	virtual void OnOK();

	void setBtnStatus(BUTTON_STATUS nStatus);
	void SetLocalPlayControlStatus(bool bSelectedRec);
	void SetCheckSunapi();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonStartRecording();
	afx_msg void OnBnClickedButtonStopRecording();
	afx_msg void OnBnClickedRadioSec();
	afx_msg void OnBnClickedRadioRec();
	afx_msg void OnBnClickedButtonPlayRecording();
	afx_msg void OnBnClickedRadioAvi();
	afx_msg void OnBnClickedButtonRec2avi();
	afx_msg void OnCbnSelchangeComboModelList();
	afx_msg void OnBnClickedCheckSunapi();
	DECLARE_EVENTSINK_MAP()

	void OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode);

};

#endif // #if !defined(AFX_EventDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_)