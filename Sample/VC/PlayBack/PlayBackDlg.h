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
// PlayBackDlg.h : header file
//

#pragma once

#include "xnssdkwindowctrl.h"
#include "xnssdkdevicectrl.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "DebugLog.h"


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This files are installed in {$SDK path}\sample_code\include 
// You should include this files
// -----------------------------------------------------------------------
#include "XnsCommon.h"
#include "XnsDeviceInterface.h"
#include "XnsMediaInterface.h"


#if !defined(AFX_PlayBackDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_)
#define AFX_PlayBackDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_


typedef enum{ 
	STATUS_DISCONNECTED = 0, 
	STATUS_CONNECTED,  
}BUTTON_STATUS;
/////////////////////////////////////

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


// CPlayBackDlg dialog
class CPlayBackDlg : public CDialog
{
private:
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// XNS Device control and Window control variables
	// -----------------------------------------------------------------------

	////////////////////// Active X Control Member Data
	CXnssdkwindowctrl	m_ctrlXnsWindow;		// XnsWindow control
	CXnssdkdevicectrl	m_ctrlXnsDevice;		// XnsDevice control

	////////////////////// Device Handler
	long				m_hDevice;				// Device handle
	long				m_nControlId;			// Control ID
	long				m_hMediaSource;         // Media Source Handler

	/////////////////////// Control Member Data
	CComboBox			m_ctrlModelList;		// ComboBox Control Member Data
	CButton				m_ctrlSunapi;
	CIPAddressCtrl		m_ctrlIpAddress;		// IP Addresss Control Member Data
	CEdit				m_ctrlEditLog;			// Status Edit Control Member Data 											
	CListBox			m_ctrlRecDataList;		// Record Data List Control Member Data (For Record File)
	CSliderCtrl			m_ctrlTimebar;			// Recorder Time Bar Slide Control Member Data
	CComboBox			m_ctrlPlaySpeedCombo;	// Play Speed Select Combo Box Control Member Data
	CComboBox			m_ctrlTrackNum;
	CMonthCalCtrl		m_ctrlMonthCalendar;	// Calendar Control Member Data
	
	////////////////////// Control String Member Data
	CString				m_strModelName;
	long				m_nPort;				// Port Number Member Data
	int					m_nHttpPort;
	CString				m_strId;				// ID String Member Data
	CString				m_strPassword;			// Password String Member Data

	////////////////////// Control Protocol
	int					m_nDeviceProtocol;		// SUNAPI / another 
	BOOL				m_bSupportedSunapi;		// TRUE / FALSE

	////////////////////// for Play Video Data
	BOOL				m_bPlay;                // Play Video Button Check

	////////////////////// About Record
	sRecDataInfo		*m_pRecDataInfo;        // Record Information Struct Member Data 
	long				m_nForwardSpeed;        // Forward Speed Member Data
	long				m_nBackwardSpeed;       // Backward Speed Member Data
	CString				m_strCurTime;           // Time Bar Static Member Data 

	////////////////////// Record Data Time
	int					m_nYear, m_nMonth, m_nDay;
	long				m_startHour, m_startMin, m_startSec;
	long				m_endHour, m_endMin, m_endSec;
	SYSTEMTIME			m_seltime;
	UINT				m_nTrackValue[30];
	int					m_nTrackNum;

	////////////////////// Check Connection and Destroy
	bool				m_bCheckConnect;
	bool				m_bDestroy;


	// Construction
public:
	CPlayBackDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_PLAYBACK_DIALOG };

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
	void SetDeviceProtocol(void);
	void setBtnStatus(BUTTON_STATUS nStatus);

	// Device Control Event Functions.
	void OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode);
	void OnSearchCalendarXnssdkdevicectrl(long nDeviceID, long nControlID, long nRecDay);
	void OnSearchDayXnssdkdevicectrl(long nDeviceID, long nControlID, long hTimeline);
	void OnFrameTimeChangedXnssdkwindowctrl(long tFrameTime);
	void OnSearchOverLapXnssdkdevicectrl(long nDeviceID, long tStart, long tEnd, long nTrackNum, long nTrackValue);

	// MFC Window Control Functions. 
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelchangeComboModelList();
	afx_msg void OnBnClickedCheckSunapi();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonCheckCalendar();
	afx_msg void OnLbnDblclkListRecdata();
	afx_msg void OnBnClickedButtonStepBack();
	afx_msg void OnBnClickedButtonBp();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonFor();
	afx_msg void OnCbnSelchangeComboPlaySpeed();
	afx_msg void OnMcnSelectMonthcalendar(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderRectime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboTrack();
	DECLARE_EVENTSINK_MAP()

	virtual void OnOK();
		
};

#endif // #if !defined(AFX_PlayBackDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_)