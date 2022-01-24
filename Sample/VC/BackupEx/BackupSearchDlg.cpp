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
// BackupSearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BackupEx.h"
#include "BackupSearchDlg.h"
// BackupSearchDlg dialog

IMPLEMENT_DYNAMIC(BackupSearchDlg, CDialog)

BackupSearchDlg::BackupSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(BackupSearchDlg::IDD, pParent)
	, m_StartTime(0)
	, m_EndTime(0)
	, m_Date(0)
	, m_nYear(0)
	, m_nMonth(0)
	, m_nDay(0)
	, m_nStartHour(0)
	, m_nStartMin(0)
	, m_nStartSec(0)
	, m_nEndHour(0)
	, m_nEndMin(0)
	, m_nEndSec(0)
	, m_nFileType(0)
{
	m_ctrlXnsDevice = NULL;
}
BackupSearchDlg::BackupSearchDlg( CXnssdkdevicectrl * ctrlXnsDevice, long hDevice, long nCid,
								  CWnd* pParent)
	: CDialog(BackupSearchDlg::IDD, pParent)
	, m_StartTime(0)
	, m_EndTime(0)
	, m_Date(0)	
	, m_nYear(0)
	, m_nMonth(0)
	, m_nDay(0)
	, m_nStartHour(0)
	, m_nStartMin(0)
	, m_nStartSec(0)
	, m_nEndHour(0)
	, m_nEndMin(0)
	, m_nEndSec(0)	
	, m_nRadioButtonSec(0)
	, m_nFileType(0)
{
	m_ctrlXnsDevice = ctrlXnsDevice;
	m_hDevice = hDevice;
	m_nCid = nCid;
}

BackupSearchDlg::~BackupSearchDlg()
{
}

void BackupSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DATE, m_ctrlDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_ctrlStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, m_ctrlEndTime);
	DDX_Radio(pDX, IDC_RADIO_SEC, m_nRadioButtonSec);
}

BEGIN_MESSAGE_MAP(BackupSearchDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACKUP_OK, &BackupSearchDlg::OnBnClickedButtonBackupOk)
	ON_BN_CLICKED(IDC_BUTTON_BACKUP_CANCEL, &BackupSearchDlg::OnBnClickedButtonBackupCancel)
END_MESSAGE_MAP()

BOOL BackupSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


// BackupSearchDlg message handlers

void BackupSearchDlg::OnBnClickedButtonBackupOk()
{
	UpdateData(TRUE);
	
	if(m_nRadioButtonSec == 0)
	{
		m_nFileType = SEC_WRITER;
		m_strFileType = _T("SEC");
	}
	else if(m_nRadioButtonSec == 1)
	{
		m_nFileType = REC_WRITER;
		m_strFileType = _T("REC");
	}

	m_ctrlDate.GetTime(m_Date);
	m_ctrlStartTime.GetTime(m_StartTime);
	m_ctrlEndTime.GetTime(m_EndTime);

	m_nYear = (long)m_Date.GetYear();
	m_nMonth = (long)m_Date.GetMonth();
	m_nDay = (long)m_Date.GetDay();
	m_nStartHour = (long)m_StartTime.GetHour();
	m_nStartMin = (long)m_StartTime.GetMinute();
	m_nStartSec = (long)m_StartTime.GetSecond();
	m_nEndHour = (long)m_EndTime.GetHour();
	m_nEndMin = (long)m_EndTime.GetMinute();
	m_nEndSec = (long)m_EndTime.GetSecond();

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Gets the video recording dates from a specific month. 
	// The result of this function can be obtaned from the OnSearchCalendar event.
	// Return Value : Converted values in time_t format.
	// -----------------------------------------------------------------------
	m_nStartTime = m_ctrlXnsDevice->DateToTimet(
		m_nYear,						// [in] Year
		m_nMonth,						// [in] Month
		m_nDay,							// [in] Day
		m_nStartHour,					// [in] Hour
		m_nStartMin,					// [in] Minute
		m_nStartSec);					// [in] Second
	m_nEndTime = m_ctrlXnsDevice->DateToTimet(m_nYear, m_nMonth, m_nDay, m_nEndHour, m_nEndMin, m_nEndSec);

	OnOK();
}

void BackupSearchDlg::OnBnClickedButtonBackupCancel()
{
	OnCancel();
}
