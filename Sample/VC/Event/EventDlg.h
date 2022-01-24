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
// EventDlg.h : header file
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
#include "xnssdkwindowctrl1.h"
#include "xnssdkdevicectrl1.h"

#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "DebugLog.h"
/////////////////////////////////////

#if !defined(AFX_EventDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_)
#define AFX_EventDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_

// Define Value
#define ADDRESS_MAX		4
#define EVENT_LOG		7

// Define Handle  
#define HANDLE_FAIL		0
#define MAX_HANDLE		3000

// Tab Control Index
#define INDEX_ALARM		0
#define INDEX_MOTION	1
#define INDEX_IV		2
#define INDEX_VIDEOLOSS	3
#define INDEX_SYSTEM	4
#define INDEX_DEVICE	5
#define INDEX_AMD		6

// Alarm Control On & Off
#define ALARM_OFF		0
#define ALARM_ON		1
/////////////////////////////////////


// CEventDlg dialog
class CEventDlg : public CDialog
{
public:
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// XNS Device control and Window control variables
	// -----------------------------------------------------------------------

	////////////////////// Active X Control Member Data
	CXnssdkwindowctrl1 m_ctrlXnsSdkWindow;									// Xns Sdk Device Control Member Data
	CXnssdkdevicectrl1 m_ctrlXnsSdkDevice;									// Xns Sdk Window Control Member Data

	////////////////////// Device Handler
	long m_hDevice;
	long m_hMediaSource;                                                    // Media Source Handler
	long m_nAlarmControlId;
	long m_nControlId;

public:
	/////////////////////// Control Member Data
	CComboBox m_ctrlModelList;												// ComboBox Control Member Data														
	CIPAddressCtrl m_ctrlIpAddress;											// IP Addresss Control Member Data
	CEdit m_ctrlPort;														// Port Edit Box Control Member Data
	CEdit m_ctrlHttpPort;													// HTTP Port Edit Box Control Member Data
	CEdit m_ctrlUserID;														// User ID Edit Box Control Member Data
	CEdit m_ctrlPassword;													// // User Password Edit Box Control Member Data
	CButton m_ctrlSunapi;
	
	////////////////////// Control String Member Data
	CString	m_strModelName;													
	CString m_strPassword;													// Password String Member Data
	CString m_strUrl;						                                // URL String Member Data
	CString m_strId;							                            // ID String Member Data
	int m_nDeviceProtocol;
	int m_nMediaProtocol;
	long m_lnPort;									                        // Port Number Member Data
	long m_lnHttpPort;														// HTTP Port Number Member Data
	int	m_nChannelIndex;
	int	m_nProfileIndex;
public:
	////////////////////// for Play Video Data
	long m_nErrorCode;                                                      // Error Code 
	long m_nDeviceStatus;                                                   // Device Status
	BOOL m_bPlay;                                                           // Play Video Button Check

	////////////////////// Check Connection and Destroy, Alarm
	BOOL m_bCheckConnect;
	BOOL m_bDestroy;
	BOOL m_bAlarm;
	int m_nDeviceCount;

	////////////////////// About Event Log
	CTabCtrl m_ctrlTab;														// Event Log Tab Control Member Data

	CListBox m_ctrlStatusList;												// Status List Control Member Data
	CListBox m_ctrlSensorLog;												
	CListBox m_ctrlMotionLog;
	CListBox m_ctrlIVLog;
	CListBox m_ctrlVideoLossLog;
	CListBox m_ctrlSystemLog;		
	CListBox m_ctrlDeviceLog;
	CListBox m_ctrlAMDLog;

	int m_nIndex_Sensor;
	int m_nIndex_Motion;
	int m_nIndex_IV;
	int m_nIndex_VideoLoss;
	int m_nIndex_System;
	int m_nIndex_Device;

	// Construction
public:
	CEventDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_ALARM_EVENT_DIALOG };

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

public:
	// User-Defined Functions.
	void OnInitXnsSdk(void);
	void OnInitModelList(void);
	void OnSetDialog(void);
	void OnEnableControlWindow(BOOL bCheck);
	void SetCheckSunapi();
	void OnSetEventlogList(int nStatus);

	// Device Control Event Functions.
	void OnDeviceStatusChangedXnssdkdevicectrl1(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnConnectFailedXnssdkdevicectrl1(long nDeviceID, long nErrorCode);
	void OnMotionEventXnssdkdevicectrl1(long nDeviceID, long nControlID, long tEventUTC);
	void OnSensorEventXnssdkdevicectrl1(long nDeviceID, long nControlID, long nSensorNumber, long tEventUTC);
	void OnVideoLossEventXnssdkdevicectrl1(long nDeviceID, long nControlID, long tEventUTC);
	void OnControlRemoteNameChangedXnssdkdevicectrl1(long nDeviceID, long nControlID);
	void OnControlLocalNameChangedXnssdkdevicectrl1(long nDeviceID, long nControlID);
	void OnControlStatusChangedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nErrorCode, long nStatusMask);
	void OnIvOccurEventXnssdkdevicectrl1(long nDeviceID, long nControlID, long tEventUTC, long nIvType);
	void OnPasswordChangedXnssdkdevicectrl1(long nDeviceID, LPCTSTR szID);

	// MFC Window Control Functions. 
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnDestroy();
	afx_msg void OnTcnSelchangeTabEvent(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedCheckSetAlarm();
	DECLARE_EVENTSINK_MAP()
	void OnAlarmOutControlFailedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nErrorCode);
	void OnFaceDetectionEventChangedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nSubEvent, long tEventUTC, long nParam1, long nParam2, long nParam3, long nParam4, LPCTSTR description, LPCTSTR strParam);
	void OnTrackingEventChangedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nSubEvent, long tEventUTC, long nParam1, long nParam2, long nParam3, long nParam4, LPCTSTR description, LPCTSTR strParam);
	void OnAudioDetectionEventChangedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nSubEvent, long tEventUTC, long nParam1, long nParam2, long nParam3, long nParam4, LPCTSTR description, LPCTSTR strParam);
	void OnAMDEventChangedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nSubEvent, long tEventUTC, long nParam1, long nParam2, long nParam3, long nParam4, LPCTSTR description, LPCTSTR strParam);
	void OnSystemEventChangedXnssdkdevicectrl1(long nDeviceID, long nControlID, long nSubEvent, long tEventUTC, long nParam1, long nParam2, long nParam3, long nParam4, LPCTSTR description, LPCTSTR strParam);
	void OnVideoLossEndXnssdkdevicectrl1(long nDeviceID, long nControlID, long tEventUTC);

	afx_msg void OnCbnSelchangeComboModelList();

	virtual void OnOK();
	afx_msg void OnBnClickedCheckSunapi();
};

#endif // #if !defined(AFX_EventDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_)