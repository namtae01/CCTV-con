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
// BackupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "BackupDlg.h"
#include "SdkTestDlg.h"

// CBackupDlg dialog

IMPLEMENT_DYNAMIC(CBackupDlg, CDialog)

CBackupDlg::CBackupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBackupDlg::IDD, pParent)
	, m_hMediaSource(0)
	, m_hMediaSourcePlayback(0)
	, m_pCtrlXnsDevice(0)
	, m_pCtrlXnsWindowLive(0)
	, m_pCtrlXnsWindowPlayback(0)
	, m_tDate(COleDateTime::GetCurrentTime())
	, m_tStartTime(COleDateTime::GetCurrentTime())
	, m_tEndTime(COleDateTime::GetCurrentTime())
	, m_nYear(0), m_nMonth(0), m_nDay(0)
	, m_nStartHour(0), m_nStartMin(0), m_nStartSec(0)
	, m_nEndHour(0), m_nEndMin(0), m_nEndSec(0)
	, strFile(_T("c:\\SdkTest"))
	, m_hFileReader(0)
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

CBackupDlg::~CBackupDlg()
{
}

void CBackupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BACKUP_DATE, m_ctrlDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BACKUP_ENDTIME, m_ctrlStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BACKUP_STARTTIME, m_ctrlEndTime);
	DDX_Control(pDX, IDC_COMBO_BACKUP_TYPE, m_ctrlBackupType);
}


BEGIN_MESSAGE_MAP(CBackupDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_START_BACKUP, &CBackupDlg::OnBnClickedButtonStartBackup)
	ON_BN_CLICKED(IDC_BUTTON_STOP_BACKUP, &CBackupDlg::OnBnClickedButtonStopBackup)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_BACKUP_ENDTIME, &CBackupDlg::OnDtnDatetimechangeDatetimepickerBackupEndtime)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_BACKUP_STARTTIME, &CBackupDlg::OnDtnDatetimechangeDatetimepickerBackupStarttime)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_BACKUP_DATE, &CBackupDlg::OnDtnDatetimechangeDatetimepickerBackupDate)
ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_BACKUP_DATE, &CBackupDlg::OnDtnDatetimechangeDatetimepickerBackupDate)
ON_BN_CLICKED(IDC_BUTTON_CREATE_FILEREADER, &CBackupDlg::OnBnClickedButtonCreateFilereader)
ON_BN_CLICKED(IDC_BUTTON_RELEASE_FILEREADER, &CBackupDlg::OnBnClickedButtonReleaseFilereader)
ON_BN_CLICKED(IDC_BUTTON_PLAY_READER, &CBackupDlg::OnBnClickedButtonPlayReader)
ON_BN_CLICKED(IDC_BUTTON_STOP_READER, &CBackupDlg::OnBnClickedButtonStopReader)
ON_BN_CLICKED(IDC_BUTTON_GET_FILENAME, &CBackupDlg::OnBnClickedButtonGetFilename)
ON_BN_CLICKED(IDC_BUTTON_GET_TIMELINEHANDLE, &CBackupDlg::OnBnClickedButtonGetTimelinehandle)
ON_BN_CLICKED(IDC_BUTTON_GET_MEDIASOURCE, &CBackupDlg::OnBnClickedButtonGetMediasource)
END_MESSAGE_MAP()


BOOL CBackupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Control Setting.
	m_ctrlBackupType.AddString(_T("REC"));
	m_ctrlBackupType.AddString(_T("SEC"));
	m_ctrlBackupType.SetCurSel(0);

	// Time and Date Control Initialize.
	OnTimeSetting();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Backup Functions.
// @ Function Name : Startbackup()
// Starts backup.
// -----------------------------------------------------------------------
void CBackupDlg::OnBnClickedButtonStartBackup()
{
	GET_XNS_PARAM();

	OnTimeSetting();
	long tStart = m_pCtrlXnsDevice->DateToTimet(m_nYear, m_nMonth, m_nDay, m_nStartHour, m_nStartMin, m_nStartSec);;
	long tEnd = m_pCtrlXnsDevice->DateToTimet(m_nYear, m_nMonth, m_nDay, m_nEndHour, m_nEndMin, m_nEndSec);

	long ntStartUTC = m_pCtrlXnsDevice->LocalTimeToDeviceUTC(m_hDevice, tStart);
	long ntEndUTC = m_pCtrlXnsDevice->LocalTimeToDeviceUTC(m_hDevice, tEnd);

	
	int nBackupType = m_ctrlBackupType.GetCurSel();

	int nRet = 0;

	switch(nBackupType)
	{
	case INDEX_REC:
		nRet = m_pCtrlXnsDevice->StartBackup(m_hDevice, CTRLID_DVR, strFile, REC_WRITER, ntStartUTC, ntEndUTC);
		break;

	case INDEX_SEC:
		nRet = m_pCtrlXnsDevice->StartBackup(m_hDevice, CTRLID_DVR, strFile, SEC_WRITER, ntStartUTC, ntEndUTC);
		break;
	}

	WLOGD(_T("Startbackup():: %d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Backup Functions.
// @ Function Name : StopBackup()
// Stops backup.
// -----------------------------------------------------------------------
void CBackupDlg::OnBnClickedButtonStopBackup()
{
	GET_XNS_PARAM();

	long nRet = m_pCtrlXnsDevice->StopBackup(m_hDevice, CTRLID_DVR);
	WLOGD(_T("StopBackup():: %d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Backup Functions.
// @ Function Name : CreateFileReader()
// Creates the file reader. 
// The file reader is used to play backup or recoding data.
// -----------------------------------------------------------------------
void CBackupDlg::OnBnClickedButtonCreateFilereader()
{
	GET_XNS_PARAM();

	m_hFileReader = m_pCtrlXnsDevice->CreateFileReader(strFile);
	WLOGD(_T("CreateFileReader():: FileHeader : %d\n"), m_hFileReader);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Backup Functions.
// @ Function Name : ReleaseFileReader()
// Releases the file reader.
// -----------------------------------------------------------------------
void CBackupDlg::OnBnClickedButtonReleaseFilereader()
{
	GET_XNS_PARAM();

	m_pCtrlXnsDevice->ReleaseFileReader(m_hFileReader);
	m_hFileReader = NULL;
	WLOGD(_T("ReleaseFileReader():: FileHeader : %d\n"), m_hFileReader);

}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Backup Functions.
// @ Function Name : PlayReader()
// Creates the file reader. 
// Plays the backup file at a specified speed.
// -----------------------------------------------------------------------
void CBackupDlg::OnBnClickedButtonPlayReader()
{
	GET_XNS_PARAM();
	OnTimeSetting();

	m_pCtrlXnsWindowPlayback->Start(m_hMediaSourcePlayback);
	long nRet = m_pCtrlXnsDevice->PlayReader(m_hFileReader, SPEED_1);	
	WLOGD(_T("PlayReader():: %d(%s), MediaSource[%d]\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet), m_hMediaSourcePlayback);

}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Backup Functions.
// @ Function Name : PauseReader()
// Creates the file reader. 
// Stops playing the backup file temporarily. 
// Can resume playing using PlayReader().
// -----------------------------------------------------------------------
void CBackupDlg::OnBnClickedButtonStopReader()
{
	GET_XNS_PARAM();

	long nRet = m_pCtrlXnsDevice->PauseReader(m_hFileReader);	
	WLOGD(_T("PauseReader():: %d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Backup Functions.
// @ Function Name : GetFileName()
// Creates the file reader. 
// Returns the file name and saving path of the given file handle.
// -----------------------------------------------------------------------
void CBackupDlg::OnBnClickedButtonGetFilename()
{
	GET_XNS_PARAM();

	CString filename = m_pCtrlXnsDevice->GetFileName(m_hFileReader);
	WLOGD(_T("GetFileName():: %s\n"), filename);

}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Backup Functions.
// @ Function Name : GetTimelineHandle()
// Gets the handle of the timeline from the file handle. 
// This value is used to display videos in the recording timeline on the screen.
// -----------------------------------------------------------------------
void CBackupDlg::OnBnClickedButtonGetTimelinehandle()
{
	GET_XNS_PARAM();

	long hTimeline = m_pCtrlXnsDevice->GetTimelineHandle(m_hFileReader);
	WLOGD(_T("GetTimelineHandle():: Timeline : %d\n"), hTimeline);

}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Backup Functions.
// @ Function Name : GetMediaSource()
// Gets the handle of the media source from the file handle. 
// This value is used to display images using XnsWindow.
// -----------------------------------------------------------------------
void CBackupDlg::OnBnClickedButtonGetMediasource()
{
	GET_XNS_PARAM();

	m_hMediaSourcePlayback = m_pCtrlXnsDevice->GetMediaSource(m_hFileReader);
	WLOGD(_T("GetMediaSource():: MediaSource[%d], FileReader[%d]\n"), m_hMediaSourcePlayback, m_hFileReader);
	*m_pHMediaSourcePlayback = m_hMediaSourcePlayback;
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// @ Backup Functions.
// for Time initialize function.
// -----------------------------------------------------------------------
void CBackupDlg::OnTimeSetting(void)
{
	m_ctrlDate.GetTime(m_tDate);
	m_ctrlStartTime.GetTime(m_tStartTime);
	m_ctrlEndTime.GetTime(m_tEndTime);

	// Time Setting
	m_nYear = (long)m_tDate.GetYear();
	m_nMonth = (long)m_tDate.GetMonth();
	m_nDay = (long)m_tDate.GetDay();

	m_nStartHour = (long)m_tStartTime.GetHour();
	m_nStartMin = (long)m_tStartTime.GetMinute();
	m_nStartSec = (long)m_tStartTime.GetSecond();

	m_nEndHour = (long)m_tEndTime.GetHour();
	m_nEndMin = (long)m_tEndTime.GetMinute();
	m_nEndSec = (long)m_tEndTime.GetSecond();

	WLOGD(_T("::Test -  Day %d-%d-%d // Start %d:%d:%d //End %d:%d:%d\n"), 
		m_nYear, m_nMonth, m_nDay,
		m_nStartHour, m_nStartMin, m_nStartSec,
		m_nEndHour, m_nEndMin, m_nEndSec);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// End Time Control Change Event.
// -----------------------------------------------------------------------
void CBackupDlg::OnDtnDatetimechangeDatetimepickerBackupEndtime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	UpdateData(TRUE);
	m_tEndTime.Format(_T("%p %I:%M:%S"));

	*pResult = 0;
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// Start Time Control Change Event.
// -----------------------------------------------------------------------
void CBackupDlg::OnDtnDatetimechangeDatetimepickerBackupStarttime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	UpdateData(TRUE);
	m_tStartTime.Format(_T("%p %I:%M:%S"));

	*pResult = 0;
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// Date Control Change Event.
// -----------------------------------------------------------------------
void CBackupDlg::OnDtnDatetimechangeDatetimepickerBackupDate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	UpdateData(TRUE);
	m_tDate.Format(_T("%A, %B &d, %y"));

	*pResult = 0;
}
