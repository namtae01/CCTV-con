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
// http://security.hanwhatechwin.com/
///////////////////////////////////////////////////////////////////////////////////
// WinMiscDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "WinMiscDlg.h"


#include "SdkTestDlg.h"

// CWinMiscDlg dialog

IMPLEMENT_DYNAMIC(CWinMiscDlg, CDialog)

CWinMiscDlg::CWinMiscDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinMiscDlg::IDD, pParent)
	, m_bDisplayNoData(FALSE)
{
	if(pParent)
	{
		CSdkTestDlg *ptr = dynamic_cast<CSdkTestDlg *>(pParent);
		m_pCtrlXnsDevice = &(ptr->m_ctrlXnsDevice);
		m_pCtrlXnsWindowLive = &(ptr->m_ctrlXnsWindowLive);
		m_pCtrlXnsWindowPlayback = &(ptr->m_ctrlXnsWindowPlayback);
		m_pCtrlEditLog = ptr->m_pCtrlEditLog;
		m_pCtrlEditEvent = ptr->m_pCtrlEditEvent;
		m_pHDevice = &(ptr->m_hDevice);
		m_pHMediaSource = &(ptr->m_hMediaSource);
		m_pHMediaSourcePlayback = &(ptr->m_hMediaSourcePlayback);
		m_pNControlId = &(ptr->m_nControlId);
	}
}

CWinMiscDlg::~CWinMiscDlg()
{
}

void CWinMiscDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CURSOR_TYPE, m_ctrlCursorType);
	DDX_Check(pDX, IDC_CHECK_DISPLAY_NODATA, m_bDisplayNoData);
}

BOOL CWinMiscDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlCursorType.AddString(_T("Default"));
	m_ctrlCursorType.AddString(_T("ZoomIn"));
	m_ctrlCursorType.AddString(_T("ZoomOut"));
	m_ctrlCursorType.AddString(_T("Hand"));
	m_ctrlCursorType.AddString(_T("Grab"));
	m_ctrlCursorType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_MESSAGE_MAP(CWinMiscDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_GET_LAST_ERROR, &CWinMiscDlg::OnBnClickedButtonGetLastError)
	ON_BN_CLICKED(IDC_BUTTON_SET_CURSOR, &CWinMiscDlg::OnBnClickedButtonSetCursor)
	ON_BN_CLICKED(IDC_BUTTON_WIN_TIME_TEST, &CWinMiscDlg::OnBnClickedButtonWinTimeTest)
	ON_BN_CLICKED(IDC_CHECK_DISPLAY_NODATA, &CWinMiscDlg::OnBnClickedCheckDisplayNodata)
END_MESSAGE_MAP()


// CWinMiscDlg message handlers


void CWinMiscDlg::OnBnClickedButtonGetLastError()
{
	GET_XNS_PARAM()
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns the recent error code. 
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsWindowLive->GetLastError();
	WLOGW(_T("GetLastError():: ret=%d\n"), nRet);

}

void CWinMiscDlg::OnBnClickedButtonSetCursor()
{
	GET_XNS_PARAM()
	UpdateData(TRUE);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns the recent error code. 
	// -----------------------------------------------------------------------
	CString str;
	long type=0;
	long sel = m_ctrlCursorType.GetCurSel();
	m_ctrlCursorType.GetLBText(sel, str);
	if(str.Compare(_T("Default"))==0)
	{
		type = 0;
	}
	else if(str.Compare(_T("ZoomIn"))==0)
	{
		type = 1;
	}
	else if(str.Compare(_T("ZoomOut"))==0)
	{
		type = 2;
	}
	else if(str.Compare(_T("Hand"))==0)
	{
		type = 3;
	}
	else if(str.Compare(_T("Grab"))==0)
	{
		type = 4;
	}
	
	m_pCtrlXnsWindowLive->SetCursor(type);
	WLOGW(_T("SetCursor():: type=%s\n"), str);
}

void CWinMiscDlg::OnBnClickedButtonWinTimeTest()
{
	CTime currtime = CTime::GetCurrentTime();

	long nYear, nMonth, nDay, nHour, nMin, nSec;
	long ttime;

	nYear = currtime.GetYear();
	nMonth = currtime.GetMonth();
	nDay = currtime.GetDay();
	nHour = currtime.GetHour();
	nMin = currtime.GetMinute();
	nSec = currtime.GetSecond();

	ttime = m_pCtrlXnsWindowLive->DateToTimet(nYear, nMonth, nDay, nHour, nMin, nSec);
	WLOGW(_T("DateToTimet():: time_t=%d\n"), ttime);

	m_pCtrlXnsWindowLive->TimetToDate(ttime, &nYear, &nMonth, &nDay, &nHour, &nMin, &nSec);
	WLOGW(_T("TimetToDate():: %04d-%02d-%02d %02d:%02d:%02d\n"),
		nYear, nMonth, nDay, nHour, nMin, nSec);

}



void CWinMiscDlg::OnBnClickedCheckDisplayNodata()
{
	GET_XNS_PARAM()
	UpdateData(TRUE);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// If there is no recording data, this will display a message of "No Data". 
	// This function works properly only if the media type is in playback mode.
	// -----------------------------------------------------------------------
	m_pCtrlXnsWindowPlayback->DisplayNoData(m_bDisplayNoData);
	WLOGW(_T("DisplayNoData():: flag=%d\n"), m_bDisplayNoData);
}
