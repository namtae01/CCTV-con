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
// BackupSearchDlg.h : header file
//

#pragma once

// xns header files
#include "XnsCommon.h"
#include "XnsDeviceInterface.h"
#include "xnssdkdevicectrl.h"
#include "afxdtctl.h"
#include "BackupExDlg.h"

// BackupSearchDlg dialog

class BackupSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(BackupSearchDlg)

public:
	BackupSearchDlg(CWnd* pParent = NULL);   // standard constructor
	BackupSearchDlg(
		CXnssdkdevicectrl * ctrlXnsDevice, 
		long hDevice, 
		long nCid,
		CWnd* pParent = NULL);
	virtual ~BackupSearchDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_BACKUP };
private:
	CXnssdkdevicectrl * m_ctrlXnsDevice;		// Xns SDK Device Control
	
	long m_hDevice;								// Device Handle		
	long m_nCid;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	long m_nYear, m_nMonth, m_nDay;
	long m_nStartHour, m_nStartMin, m_nStartSec;
	long m_nEndHour, m_nEndMin, m_nEndSec;

	long			m_nStartTime;
	long			m_nEndTime;
	
	// Control Member Data
	CDateTimeCtrl	m_ctrlStartTime;
	CDateTimeCtrl	m_ctrlEndTime;
	CDateTimeCtrl	m_ctrlDate;
	int				m_nRadioButtonSec;

	CTime			m_Date;
	CTime			m_StartTime;
	CTime			m_EndTime;

	int				m_nFileType;
	CString			m_strFileType;

	afx_msg void OnBnClickedButtonBackupOk();
	afx_msg void OnBnClickedButtonBackupCancel();
	afx_msg void OnBnClickedButtonSearch();
};
