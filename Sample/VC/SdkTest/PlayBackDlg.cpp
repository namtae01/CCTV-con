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
// PlayBackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "PlayBackDlg.h"
#include "SdkTestDlg.h"

// CPlayBackDlg dialog

IMPLEMENT_DYNAMIC(CPlayBackDlg, CDialog)

CPlayBackDlg::CPlayBackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayBackDlg::IDD, pParent)
	, m_hMediaSource(0)
	, m_pCtrlXnsDevice(0)
	, m_pCtrlXnsWindowLive(0)
	, m_pCtrlXnsWindowPlayback(0)
	, m_tDate(COleDateTime::GetCurrentTime())
	, m_tStartTime(COleDateTime::GetCurrentTime())
	, m_tEndTime(COleDateTime::GetCurrentTime())
	, m_nYear(0), m_nMonth(0), m_nDay(0)
	, m_nStartHour(0), m_nStartMin(0), m_nStartSec(0)
	, m_nEndHour(0), m_nEndMin(0), m_nEndSec(0)
	, m_strSpeed(_T("4"))
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

CPlayBackDlg::~CPlayBackDlg()
{
}

void CPlayBackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_ctrlDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_ctrlStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, m_ctrlEndTime);
	DDX_Control(pDX, IDC_COMBO_PLAY_SPEED, m_ctrlPlaySpeed);
	DDX_CBString(pDX, IDC_COMBO_PLAY_SPEED, m_strSpeed);
}


BEGIN_MESSAGE_MAP(CPlayBackDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CPlayBackDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_START_LOCALREC, &CPlayBackDlg::OnBnClickedButtonStartLocalrec)
	ON_BN_CLICKED(IDC_BUTTON_STOP_LOCALREC, &CPlayBackDlg::OnBnClickedButtonStopLocalrec)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE_DVRREC, &CPlayBackDlg::OnBnClickedButtonToggleDvrrec)
	ON_BN_CLICKED(IDC_BUTTON_SEARCHDAY, &CPlayBackDlg::OnBnClickedButtonSearchday)
	ON_BN_CLICKED(IDC_BUTTON_SEARCHCALENDAR, &CPlayBackDlg::OnBnClickedButtonSearchcalendar)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CPlayBackDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_SEEK, &CPlayBackDlg::OnBnClickedButtonSeek)
	ON_BN_CLICKED(IDC_BUTTON_FRAMEADVANCE, &CPlayBackDlg::OnBnClickedButtonFrameadvance)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_MEDIABUF, &CPlayBackDlg::OnBnClickedButtonClearMediabuf)
	ON_BN_CLICKED(IDC_BUTTON_GET_REMAINING_BUFSIZE, &CPlayBackDlg::OnBnClickedButtonGetRemainingBufsize)
	ON_BN_CLICKED(IDC_BUTTON_IS_BUFFERFULL, &CPlayBackDlg::OnBnClickedButtonIsBufferfull)
	ON_BN_CLICKED(IDC_BUTTON_IS_BUFFEREMPTY, &CPlayBackDlg::OnBnClickedButtonIsBufferempty)
	ON_BN_CLICKED(IDC_BUTTON_SET_BUFFERSIZE, &CPlayBackDlg::OnBnClickedButtonSetBuffersize)
	ON_BN_CLICKED(IDC_BUTTON_GET_BUFFERSIZE, &CPlayBackDlg::OnBnClickedButtonGetBuffersize)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_FRAMEADVANCE, &CPlayBackDlg::OnBnClickedButtonMoveFrameadvance)
	ON_BN_CLICKED(IDC_BUTTON_GET_PLAYSPEED, &CPlayBackDlg::OnBnClickedButtonGetPlayspeed)
	ON_BN_CLICKED(IDC_BUTTON_SET_PLAYSPEED, &CPlayBackDlg::OnBnClickedButtonSetPlayspeed)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_START, &CPlayBackDlg::OnDtnDatetimechangeDatetimepickerStart)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER, &CPlayBackDlg::OnDtnDatetimechangeDatetimepicker)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_END, &CPlayBackDlg::OnDtnDatetimechangeDatetimepickerEnd)
END_MESSAGE_MAP()


BOOL CPlayBackDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Time and Date Control Initialize.
	OnTimeSetting();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


// CPlayBackDlg message handlers

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Local Recording Functions.
// @ Function Name : StartLocalRecording()
// Starts recording the stream data in the local PC.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonStartLocalrec()
{
	GET_XNS_PARAM();

	CString strFile = _T("c:\\LiveVideo"); 
	long nRet = m_pCtrlXnsDevice->StartLocalRecording(m_hDevice, m_nControlId, strFile, REC_WRITER);
	WLOGD(_T("StartLocalRecording():: %d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Local Recording Functions.
// @ Function Name : StopLocalRecording()
// Stops recording in the local PC.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonStopLocalrec()
{
	GET_XNS_PARAM();

	long nRet = m_pCtrlXnsDevice->StopLocalRecording(m_hDevice, m_nControlId);
	WLOGD(_T("StopLocalRecording():: %d(%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Local Recording Functions.
// @ Function Name : ToggleDvrRecording()
// Starts or stops recording by DVR.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonToggleDvrrec()
{
	GET_XNS_PARAM();

	long nRet = m_pCtrlXnsDevice->ToggleDvrRecording(m_hDevice);
	WLOGD(_T("ToggleDvrRecording():: [%d](%s)\n"), nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ PlayBack Functions.
// @ Function Name : SearchDay()
// Gets a list of recording data for a specific day. 
// The result of this function can be obtained from the OnSearchDay event.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonSearchday()
{
	GET_XNS_PARAM();
	OnTimeSetting();
	
	long tStart = m_pCtrlXnsDevice->DateToTimet(m_nYear, m_nMonth, m_nDay, m_nStartHour, m_nStartMin, m_nStartSec);
	long tEnd = m_pCtrlXnsDevice->DateToTimet(m_nYear, m_nMonth, m_nDay, m_nEndHour, m_nEndMin, m_nEndSec);

	long ntStartUTC = m_pCtrlXnsDevice->LocalTimeToDeviceUTC(m_hDevice, tStart);
	long ntEndUTC = m_pCtrlXnsDevice->LocalTimeToDeviceUTC(m_hDevice, tEnd);
	
	long nRet = m_pCtrlXnsDevice->SearchDay(m_hDevice, CTRLID_DVR, ntStartUTC, ntEndUTC, REC_TYPE_ALL);
	WLOGD(_T("SearchDay():: [%d](%s)\n"),nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ PlayBack Functions.
// @ Function Name : SearchCalendar()
// Gets the video recording dates from a specific month. 
// The result of this function can be obtained from the OnSearchCalendar event.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonSearchcalendar()
{
	GET_XNS_PARAM();
	UpdateData(TRUE);
	OnTimeSetting();

	long tStart = m_pCtrlXnsDevice->DateToTimet(m_nYear, m_nMonth, 1, 0, 0, 0);
	long ntUTC = m_pCtrlXnsDevice->LocalTimeToDeviceUTC(m_hDevice, tStart);

	long nRet = m_pCtrlXnsDevice->SearchCalendar(m_hDevice, CTRLID_DVR, ntUTC);
	WLOGD(_T("SearchCalendar():: UTC=%d, ret=[%d](%s)\n"), ntUTC, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ PlayBack Functions.
// @ Function Name : Play()
// Plays the multimedia at a specified speed.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonPlay()
{
	GET_XNS_PARAM();

	long tStart = m_pCtrlXnsDevice->DateToTimet(m_nYear, m_nMonth, m_nDay, m_nStartHour, m_nStartMin, m_nStartSec);
	long tEnd = m_pCtrlXnsDevice->DateToTimet(m_nYear, m_nMonth, m_nDay, m_nEndHour, m_nEndMin, m_nEndSec);

	long ntStartUTC = m_pCtrlXnsDevice->LocalTimeToDeviceUTC(m_hDevice, tStart);
	long ntEndUTC = m_pCtrlXnsDevice->LocalTimeToDeviceUTC(m_hDevice, tEnd);


	m_pCtrlXnsDevice->OpenMedia(m_hDevice, CTRLID_DVR, MEDIA_TYPE_PLAYBACK, ntStartUTC, ntEndUTC, &m_hMediaSourcePlayback);
	m_pCtrlXnsWindowPlayback->Start(m_hMediaSourcePlayback);

	long nRet = m_pCtrlXnsDevice->Play(m_hDevice, CTRLID_DVR, SPEED_1);
	WLOGD(_T("Play():: [%d](%s)\n"),nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ PlayBack Functions.
// @ Function Name : Pause()
// Stops playing the media stream temporarily.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonPause()
{
	GET_XNS_PARAM();

	long nRet = m_pCtrlXnsDevice->Pause(m_hDevice, CTRLID_DVR);
	WLOGD(_T("Pause():: [%d](%s)\n"),nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ PlayBack Functions.
// @ Function Name : Seek()
// Searches for a specific time point of the media stream.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonSeek()
{
	GET_XNS_PARAM();
	OnTimeSetting();

	long tPos = m_pCtrlXnsDevice->DateToTimet(m_nYear, m_nMonth, m_nDay, m_nStartHour, m_nStartMin, m_nStartSec);
	long ntStartUTC = m_pCtrlXnsDevice->LocalTimeToDeviceUTC(m_hDevice, tPos);

	m_pCtrlXnsDevice->Seek(m_hDevice, CTRLID_DVR, ntStartUTC);
	WLOGD(_T("Seek():: Time Pos : %ld\n"), ntStartUTC);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ PlayBack Functions.
// @ Function Name : FrameAdvance()
// Gets the next I-frame.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonFrameadvance()
{
	GET_XNS_PARAM();

	m_pCtrlXnsDevice->FrameAdvance(m_hDevice, CTRLID_DVR, SPEED_1);
	WLOGD(_T("FrameAdvance():: Number of frames to skip : %d \n"), SPEED_1);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Control Buffer Functions.
// @ Function Name : ClearMediaBuffer()
// Clears the buffer contents.
// In playback mode, XnsSdkWindow will pile up the stream data in the buffer 
// due to a difference between transfer rate and playback speed. 
// If the application performs search with uncleared buffer, 
// the remaining contents in the buffer will be displayed after the search. 
// This function will be called to clear the buffer before performing the search.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonClearMediabuf()
{
	GET_XNS_PARAM();

	m_pCtrlXnsWindowLive->ClearMediaBuffer();
	WLOGW(_T("ClearMediaBuffer() :: Success.\n"));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Control Buffer Functions.
// @ Function Name : GetRemainingBufferSize()
// Returns the minimum number of buffers to trigger the PreBufferEmpty event. 
// (indicates the nMinRemainingSize parameter of SetBufferSize())
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonGetRemainingBufsize()
{
	GET_XNS_PARAM();

	long nRet = m_pCtrlXnsWindowLive->GetRemainingBufferSize();
	WLOGW(_T("GetRemainingBufferSize() :: Minimum number of buffers:[%d]\n"), nRet);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Control Buffer Functions.
// @ Function Name : IsBufferFull()
// Checks if the buffer is full of data.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonIsBufferfull()
{
	GET_XNS_PARAM();

	BOOL nRet = m_pCtrlXnsWindowLive->IsBufferFull();

	if (nRet == TRUE)
	{
		WLOGW(_T("IsBufferFull() :: TRUE\n"));
	}
	else
	{
		WLOGW(_T("IsBufferFull() :: FALSE\n"));
	}
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Control Buffer Functions.
// @ Function Name : IsBufferEmpty()
// Checks if the buffer is empty.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonIsBufferempty()
{
	GET_XNS_PARAM();

	BOOL nRet = m_pCtrlXnsWindowLive->IsBufferEmpty();
	
	if (nRet == TRUE)
	{
		WLOGW(_T("IsBufferEmpty() :: TRUE\n"));
	}
	else
	{
		WLOGW(_T("IsBufferEmpty() :: FALSE\n"));
	}
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Control Buffer Functions.
// @ Function Name : SetBufferSize()
// Resizes the buffer to save the video data. 
// The buffer is assigned 5MB by default until the application calls this function. 
// (where, nMinRemainingSize is 0) If the remaining number of buffers 
// (i.e, video data count) is less than nMinRemainingSize, 
// the OnPreBufferEmpty event occurs.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonSetBuffersize()
{
	GET_XNS_PARAM();
	
	long nBufferSize = 10 * 1024 * 1024;
	long nMinRemainingSize = 10;

	m_pCtrlXnsWindowLive->SetBufferSize(nBufferSize, nMinRemainingSize);
	WLOGW(_T("SetBufferSize() :: nBufferSize:[%ld], nMinRemainingSize[%d] \n"), nBufferSize, nMinRemainingSize);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Control Buffer Functions.
// @ Function Name : GetBufferSize()
// Returns the current buffer size. 
// The buffer is assigned 5MB (5x1024x1024) by default.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonGetBuffersize()
{
	GET_XNS_PARAM();

	long nRet = m_pCtrlXnsWindowLive->GetBufferSize();
	WLOGW(_T("GetBufferSize() :: %ld Byte\n"), nRet);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Control PlayBack Functions.
// @ Function Name : MoveFrameAdvance()
// Displays the next frame.
// To enable this function, the play speed should be set to 0. 
// This function is valid only if opening the stream data in playback mode. 
// This function is available only if 
// XnsSdkDevice::OpenStream() has set nType to XMEDIA_PLAYBACK.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonMoveFrameadvance()
{
	GET_XNS_PARAM();

	m_pCtrlXnsWindowLive->MoveFrameAdvance();
	WLOGW(_T("MoveFrameAdvance() :: Move Next Frame.\n"));
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Control PlayBack Functions.
// @ Function Name : GetPlaySpeed()
// Gets the play speed currently specified.
// This function is valid only if opening the stream data in playback mode. 
// This function is available only if 
// XnsSdkDevice::OpenStream() has set nType to XMEDIA_PLAYBACK.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonGetPlayspeed()
{
	GET_XNS_PARAM();

	double nRet =	m_pCtrlXnsWindowLive->GetPlaySpeed();
	WLOGW(_T("GetPlaySpeed() :: Current Play Speed %.1f\n"), nRet);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// @ Control PlayBack Functions.
// @ Function Name : SetPlaySpeed()
// Sets the play speed.
// This function has no upper or lower limit (max/min) of the play speed. 
// However, if some devices exceed the upper limit, 
// this function will set the play speed to the max automatically. 
// If the transfer rate is too low, you may encounter buffering. 
// This function is valid only if opening the stream data in playback mode. 
// This function is available only if 
// XnsSdkDevice::OpenStream() has set nType to XMEDIA_PLAYBACK.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnBnClickedButtonSetPlayspeed()
{
	GET_XNS_PARAM();
	UpdateData(TRUE);

	double dSpeed = _wtof(m_strSpeed);

	m_pCtrlXnsWindowLive->SetPlaySpeed(dSpeed);
	WLOGW(_T("SetPlaySpeed() :: Speed %.1f Setting.\n"), dSpeed);
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ User-Defined Functions.
// @ Control PlayBack Functions.
// for Time initialize function.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnTimeSetting(void)
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

	WLOGD(_T("Check Time:: Day %d-%d-%d // Start %d:%d:%d //End %d:%d:%d\n"), 
		m_nYear, m_nMonth, m_nDay,
		m_nStartHour, m_nStartMin, m_nStartSec,
		m_nEndHour, m_nEndMin, m_nEndSec);
}


// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// Start Time Control Change Event.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnDtnDatetimechangeDatetimepickerStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	UpdateData(TRUE);
	m_tStartTime.Format(_T("%p %I:%M:%S"));

	*pResult = 0;
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// End Time Control Change Event.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnDtnDatetimechangeDatetimepickerEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	UpdateData(TRUE);
	m_tEndTime.Format(_T("%p %I:%M:%S"));

	*pResult = 0;
}

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// @ MFC Window Button Control Functions.
// Date Control Change Event.
// -----------------------------------------------------------------------
void CPlayBackDlg::OnDtnDatetimechangeDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	UpdateData(TRUE);
	m_tDate.Format(_T("%A, %B &d, %y"));

	*pResult = 0;
}

