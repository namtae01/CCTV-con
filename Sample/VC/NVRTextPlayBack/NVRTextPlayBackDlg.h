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
// NVRTextPlayBackDlg.h : header file
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

typedef enum{ 
	STATUS_DISCONNECTED = 0, 
	STATUS_CONNECTED,  
}BUTTON_STATUS;
/////////////////////////////////////

#if !defined(AFX_NVRTextPlayBackDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_)
#define AFX_NVRTextPlayBackDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_

// Define Value
#define ADDRESS_MAX 4
#define MONTH_MAX   31

// Define Play Speed ComboBox List
#define SPEED_1     0
#define SPEED_2     1
#define SPEED_4     2
#define SPEED_8     3
#define SPEED_16    4
#define SPEED_32    5
#define SPEED_64    6

// Define Play Forward & Backward
#define PLAY_FORWARD   1
#define PLAY_BACKWARD -1

// Define Handle  
#define HANDLE_FAIL 0
#define MAX_HANDLE  3000
/////////////////////////////////////

// Record Struct
typedef struct sRecDataInfo
{
	long tStartTime;
	long tEndTime;
	long nRecType;
} sRecDataInfo;
/////////////////////////////////////


// CNVRTextPlayBackDlg dialog
class CNVRTextPlayBackDlg : public CDialog
{
public:
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// XNS Device control and Window control variables
	// -----------------------------------------------------------------------

	////////////////////// Active X Control Member Data
	CXnssdkwindowctrl1 m_ctrlXnsWindow;			// Xns Sdk Device Control Member Data
	CXnssdkdevicectrl1 m_ctrlXnsDevice;			// Xns Sdk Window Control Member Data

	////////////////////// Device Handler
	long m_hDevice;									// Device handle
	long m_nControlId;								// Control ID
	long m_nTextControlId;							// TEXT Control ID

public:
	/////////////////////// Control Member Data
	CComboBox m_ctrlModelList;						// ComboBox Control Member Data
	CIPAddressCtrl m_ctrlIpAddress;					// IP Addresss Control Member Data
	CEdit m_ctrlPort;								// Port Edit Box Control Member Data

	CEdit m_ctrlEditLog;							// Status List Box Control Member Data 											
	CListBox m_ctrlRecDataList;						// Record Data List Control Member Data (For Record File)
	CListBox m_ctrlRecTextList;
	CSliderCtrl m_ctrlTimebar;						// Recorder Time Bar Slide Control Member Data
	CComboBox m_ctrlPlaySpeedCombo;					// Play Speed Select Combo Box Control Member Data
	CComboBox m_ctrlTrackNum;
	CComboBox m_ctrlTextList;
	CMonthCalCtrl m_ctrlMonthCalendar;				// Calendar Control Member Data
	CMonthCalCtrl m_ctrlMonthCalendarText;			// Text Calendar Control Member Data
	CButton	m_ctrlSunapi;
	CButton	m_ctrlAllMatch;
	CEdit m_ctrlTextLog;


	////////////////////// Control String Member Data
	CString m_strModelName;
	CString m_strId;							    // ID String Member Data
	CString m_strPw;								// Password String Member Data
	CString m_strUrl;						        // URL String Member Data
	CString m_strSearchText;
	
	long m_nPort;									// Port Number Member Data
	int m_nHttpPort;
	CEdit m_ctrlHttpPort;

	////////////////////// Control Protocol
	int	m_nDeviceProtocol;							// SUNAPI / SVNP 
	BOOL m_bSupportedSunapi;						// TRUE / FALSE

public:
	////////////////////// for Play Video Data
	long m_nErrorCode;                             // Error Code 
	long m_nDeviceStatus;                          // Device Status
	BOOL m_bPlay;                                  // Play Video Button Check

	////////////////////// About Record
	sRecDataInfo *m_pRecDataInfo;                  // Record Information Struct Member Data 
	long m_hMediaSource;                           // Media Source Handler
	long m_nForwardSpeed;                          // Forward Speed Member Data
	long m_nBackwardSpeed;                         // Backward Speed Member Data
	CString m_strCurTime;                          // Time Bar Static Member Data 

	////////////////////// Record Data Time
	int m_nYear, m_nMonth, m_nDay;
	long m_startHour, m_startMin, m_startSec;
	long m_endHour, m_endMin, m_endSec;
	SYSTEMTIME m_seltime;
	long m_stratTime;
	long m_endTime;
	UINT m_nTrackValue[30];
	int m_nTrackNum;
	int m_nTextIndex;
	long m_nTextList;

	////////////////////// Check Connection and Destroy
	bool m_bCheckConnect;
	bool m_bDestroy;


	// Construction
public:
	CNVRTextPlayBackDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_NVRTEXTPLAYBACK_DIALOG };

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

	// Device Control Event Functions.
	void OnDeviceStatusChangedXnssdkdevicectrl1(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnSearchCalendarXnssdkdevicectrl1(long nDeviceID, long nControlID, long nRecDay);
	void OnSearchDayXnssdkdevicectrl1(long nDeviceID, long nControlID, long hTimeline);
	void OnConnectFailedXnssdkdevicectrl1(long nDeviceID, long nErrorCode);
	void OnFrameTimeChangedXnssdkwindowctrl1(long tFrameTime);

	// MFC Window Control Functions. 
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonCheckCalendar2();
	afx_msg void OnLbnDblclkListRecdata();
	afx_msg void OnBnClickedButtonStepBack();
	afx_msg void OnBnClickedButtonBp();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonFor();
	afx_msg void OnDestroy();
//	afx_msg void OnLbnSelchangeListRecdata();
	afx_msg void OnCbnSelchangeComboPlaySpeed();
	afx_msg void OnMcnSelectMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderRectime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboTrack();
	afx_msg void OnCbnSelchangeComboModelList();
	DECLARE_EVENTSINK_MAP()

	void OnSearchOverLapXnssdkdevicectrl1(long nDeviceID, long tStart, long tEnd, long nTrackNum, long nTrackValue);
	virtual void OnOK();

	void SetDeviceProtocol();
	void setBtnStatus(BUTTON_STATUS nStatus);
	
	
	afx_msg void OnBnClickedCheckSunapi();
	afx_msg void OnBnClickedButtonOpenText();
	afx_msg void OnBnClickedButtonCloseText();
	void OnNewMediaXnssdkdevicectrl1(long nDeviceID, long nControlID, long nMediaType, long hMediaData, long nInputType, long nFrameType, long nFrameTime, long nFrameSize, long nTimestamp);
	afx_msg void OnBnClickedButtonCheckCalendarText();
//	afx_msg void OnLbnDblclkListRecdataText();
	afx_msg void OnMcnSelectMonthcalendarText(NMHDR *pNMHDR, LRESULT *pResult);
	void OnSearchTextCalendarXnssdkdevicectrl1(long nDeviceID, long nControlID, long nRecDay);
	void OnSearchTextListXnssdkdevicectrl1(long nDeviceID, long nControlID, LPCTSTR szLinkChannel, long tEventTime, long tPlayTime, LPCTSTR szText, long reserved);
	void OnEndSearchTextXnssdkdevicectrl1(long nDeviceID, long nControlID, long nErrorCode);
//	afx_msg void OnBnClickedButtonStartBackup();
//	afx_msg void OnBnClickedButtonCancelBackup();
};

#endif // #if !defined(AFX_NVRTextPlayBackDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_)