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
#pragma once

#include "xnssdkwindowctrl.h"
#include "xnssdkdevicectrl.h"
#include "XnsCommon.h"
#include "XnsDeviceInterface.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"

//////////////////////////////////////////
#define CTRLID_DVR	2
#define SPEED_1		1
#define SPEED_4		4
//////////////////////////////////////////

// CPlayBackDlg dialog

class CPlayBackDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlayBackDlg)

private:
	CXnssdkwindowctrl * m_pCtrlXnsWindowLive;
	CXnssdkwindowctrl * m_pCtrlXnsWindowPlayback;
	CXnssdkdevicectrl * m_pCtrlXnsDevice;
	long				m_hDevice;
	long *				m_pHDevice;
	long				m_nControlId;
	long *				m_pNControlId;
	long				m_hMediaSource;
	long *				m_pHMediaSource;
	long				m_hMediaSourcePlayback;
	long *				m_pHMediaSourcePlayback;
	CEdit *				m_pCtrlEditLog;
	CEdit *				m_pCtrlEditEvent;

	///////////////////////////////// Control Member Data
	CDateTimeCtrl m_ctrlDate;
	CDateTimeCtrl m_ctrlStartTime;
	CDateTimeCtrl m_ctrlEndTime;

	///////////////////////////////// Time Member Data
	COleDateTime m_tDate;
	COleDateTime m_tStartTime;
	COleDateTime m_tEndTime;

	long m_nYear, m_nMonth, m_nDay;
	long m_nStartHour, m_nStartMin, m_nStartSec;
	long m_nEndHour, m_nEndMin, m_nEndSec;
	CComboBox m_ctrlPlaySpeed;
	CString m_strSpeed;

public:
	CPlayBackDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlayBackDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PLAYBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStartLocalrec();
	afx_msg void OnBnClickedButtonStopLocalrec();
	afx_msg void OnBnClickedButtonToggleDvrrec();
	afx_msg void OnBnClickedButtonCameracount();
	afx_msg void OnBnClickedButtonTimelinecount();
	afx_msg void OnBnClickedButtonTimeline();
	afx_msg void OnBnClickedButtonSearchday();
	afx_msg void OnBnClickedButtonSearchcalendar();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonSeek();
	afx_msg void OnBnClickedButtonFrameadvance();
	afx_msg void OnBnClickedButtonClearMediabuf();
	afx_msg void OnBnClickedButtonGetRemainingBufsize();
	afx_msg void OnBnClickedButtonIsBufferfull();
	afx_msg void OnBnClickedButtonIsBufferempty();
	afx_msg void OnBnClickedButtonSetBuffersize();
	afx_msg void OnBnClickedButtonGetBuffersize();
	afx_msg void OnBnClickedButtonPushmedia();
	afx_msg void OnBnClickedButtonMoveFrameadvance();
	afx_msg void OnBnClickedButtonGetPlayspeed();
	afx_msg void OnBnClickedButtonSetPlayspeed();
	void OnTimeSetting(void);
	afx_msg void OnDtnDatetimechangeDatetimepickerStart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnCloseupDatetimepickerEnd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerEnd(NMHDR *pNMHDR, LRESULT *pResult);
};
