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
#define INDEX_REC	0
#define INDEX_SEC	1
#define SPEED_1		1
//////////////////////////////////////////

// CBackupDlg dialog

class CBackupDlg : public CDialog
{
	DECLARE_DYNAMIC(CBackupDlg)

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

private:
	///////////////////////////////// Control Member Data
	CDateTimeCtrl m_ctrlDate;
	CDateTimeCtrl m_ctrlStartTime;
	CDateTimeCtrl m_ctrlEndTime;
	CComboBox m_ctrlBackupType;

	///////////////////////////////// Time Member Data
	COleDateTime m_tDate;
	COleDateTime m_tStartTime;
	COleDateTime m_tEndTime;

	long m_nYear, m_nMonth, m_nDay;
	long m_nStartHour, m_nStartMin, m_nStartSec;
	long m_nEndHour, m_nEndMin, m_nEndSec;

	///////////////////////////////// Backup File Name
	CString strFile;
	long m_hFileReader;					// File Reader Header.

public:
	CBackupDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBackupDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_BACKUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonStopBackup();
	afx_msg void OnBnClickedButtonStartBackup();
	virtual BOOL OnInitDialog();
	afx_msg void OnDtnDatetimechangeDatetimepickerBackupEndtime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerBackupStarttime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerBackupDate(NMHDR *pNMHDR, LRESULT *pResult);

	void OnTimeSetting();
	afx_msg void OnBnClickedButtonCreateFilereader();
	afx_msg void OnBnClickedButtonReleaseFilereader();
	afx_msg void OnBnClickedButtonPlayReader();
	afx_msg void OnBnClickedButtonStopReader();
	afx_msg void OnBnClickedButtonGetFilename();
	afx_msg void OnBnClickedButtonGetTimelinehandle();
	afx_msg void OnBnClickedButtonGetMediasource();
};
