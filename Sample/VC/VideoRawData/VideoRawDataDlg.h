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
// @ File Name :		VideoRawDataDlg.h
// @ File Description : VideoRawData Dialog Header File. 
// @ File Date :		2011.07.04
// @ File Version :		Version 1.0
// @ File Writer :		Samsung-Techwin Engineer (Son.myung-hwa)
///////////////////////////////////////////////////////////////////////////////////

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
	STATUS_PLAY,
	STATUS_STOP
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

#define MAX_WIDTH 2560
#define MAX_HEIGHT 2048
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////
//typedef void (*CALLBACK_FUNC)(long hMediaSource, long nWidth, long nHeight, long nFrameSize, unsigned char* pVideo);

// CVideoRawDataDlg dialog
class CVideoRawDataDlg : public CDialog
{
public:
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// XNS Device control and Window control variables
	// -----------------------------------------------------------------------

	////////////////////// Active X Control Member Data
	CXnssdkwindowctrl m_ctrlXnsSdkWindow;									// Xns Sdk Device Control Member Data
	CXnssdkdevicectrl m_ctrlXnsSdkDevice;									// Xns Sdk Window Control Member Data

	////////////////////// Device Handler
	long m_hDevice;
	long m_hMediaSource;                                                    // Media Source Handler

	////////////////////// Check Connection and Destroy, Alarm
	BOOL m_bCheckConnect;													// Connect Check
	BOOL m_bDestroy;														// Dialog Destroy Check 
	BOOL m_bPlay;                                                           // Play Video Button Check

public:
	/////////////////////// Control Member Data
	CListBox m_ctrlStatusList;												// Status List Control Member Data
	CComboBox m_ctrlModelList;												// ComboBox Control Member Data
	CIPAddressCtrl m_ctrlIpAddress;											// IP Addresss Control Member Data
	CEdit m_ctrlPort;														// Port Edit Box Control Member Data
	CEdit m_ctrlUserID;														// User ID Edit Box Control Member Data
	CEdit m_ctrlPassword;	
	CButton m_ctrlSunapi;
	
	////////////////////// Control String Member Data
	CString m_strPassword;													// Password String Member Data
	CString m_strId;							                            // ID String Member Data
	long m_lnPort;									                        // Port Number Member Data
	int m_nMediaProtocol;
	int m_nHttpPort;
	int m_nDeviceProtocol;
	CString m_strModelName;

	CALLBACK_FUNC m_pCallbackFunc;											// Function pointer Member Data

	////////////////////// Low Data Image Member Data
	BITMAPINFOHEADER m_bmiHeader;
	unsigned char* m_pVideoBuf;
	long m_nImageIndex;
	long m_nWidth;
	long m_nHeight;
	BOOL m_bHasImage;

// Construction
public:
	CVideoRawDataDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VIDEO_LOWDATA_DIALOG };

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
	void OnVideoFrame(long hMediaSource, long nWidth, long nHeight, long nFrameSize, unsigned char* pVideo);

	// CallBack Function
	friend void ReceiveDecodingVideoFrame(long hMediaSource, long nWidth, long nHeight, long nFrameSize, unsigned char* pVideo);

	// Device Control Event Functions.
	void OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode);

	
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

	// MFC Window Control Functions. 
	afx_msg void OnCbnSelchangeComboModelList();
	afx_msg void OnBnClickedCheckSunapi();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedCheckRawVideo();

	DECLARE_EVENTSINK_MAP()
	void OnVideoRawDataReceivedXnssdkwindowctrl(long nDeviceID, long nControlID, long nWidth, long nHeight, long nVideoSize, long pVideoData);
	
	CButton m_ViewRawVideoCheckBox;
	void OnEventStatusChangedXnssdkwindowctrl(long nOldEventStatus, long nNewEventStatus);
	void OnVideoLossEventXnssdkdevicectrl(long nDeviceID, long nControlID, long tEventUTC);
	void OnNewMediaXnssdkdevicectrl(long nDeviceID, long nControlID, long nMediaType, long hMediaData, long nInputType, long nFrameType, long nFrameTime, long nFrameSize, long nTimestamp);
	
	virtual void OnOK();
	void setBtnStatus(BUTTON_STATUS nStatus);
	void SetCheckSunapi();
};

#endif // #if !defined(AFX_EventDLG_H__B283497E_A217_40B1_AE0D_DBB6F8F63A24__INCLUDED_)