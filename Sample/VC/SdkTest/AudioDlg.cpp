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
/// http://security.hanwhatechwin.com/
///////////////////////////////////////////////////////////////////////////////////
// AudioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "AudioDlg.h"

#include "SdkTestDlg.h"

// import winmm.lib
#pragma comment(lib, "winmm")
#include <mmsystem.h>

// CAudioDlg dialog

IMPLEMENT_DYNAMIC(CAudioDlg, CDialog)

CAudioDlg::CAudioDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAudioDlg::IDD, pParent)
	, m_bSetTalk(FALSE)
	, m_bSetListen(FALSE)
	, m_bSetAlarm(FALSE)
	, m_nSendBytes(4000)
	, m_strChannel(_T("1"))
	, m_strBps(_T("8"))
	, m_strSps(_T("8000"))
	, m_bSendAudio(0)
	, m_nBeepControlId(0)
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

CAudioDlg::~CAudioDlg()
{
}


BOOL CAudioDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_SET_TALK, m_bSetTalk);
	DDX_Check(pDX, IDC_CHECK_SET_LISTEN, m_bSetListen);
	DDX_Check(pDX, IDC_CHECK_SET_ALARM, m_bSetAlarm);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ctrlChannel);
	DDX_Control(pDX, IDC_COMBO_BIT_PER_SAMPLE, m_ctrlBps);
	DDX_Control(pDX, IDC_COMBO_SAMPLE_PER_SECOND, m_ctrlSps);
	DDX_Text(pDX, IDC_EDIT_SEND_BYTES, m_nSendBytes);
	DDX_CBString(pDX, IDC_COMBO_CHANNEL, m_strChannel);
	DDX_CBString(pDX, IDC_COMBO_BIT_PER_SAMPLE, m_strBps);
	DDX_CBString(pDX, IDC_COMBO_SAMPLE_PER_SECOND, m_strSps);
}


BEGIN_MESSAGE_MAP(CAudioDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_SET_TALK, &CAudioDlg::OnBnClickedCheckSetTalk)
	ON_BN_CLICKED(IDC_CHECK_SET_LISTEN, &CAudioDlg::OnBnClickedCheckSetListen)
	ON_BN_CLICKED(IDC_CHECK_SET_ALARM, &CAudioDlg::OnBnClickedCheckSetAlarm)
	ON_BN_CLICKED(IDC_BUTTON_SEND_AUDIO_DATA, &CAudioDlg::OnBnClickedButtonSendAudioData)
	ON_BN_CLICKED(IDC_BUTTON_STOP_AUDIO_DATA, &CAudioDlg::OnBnClickedButtonStopAudioData)
END_MESSAGE_MAP()


void CAudioDlg::OnBnClickedCheckSetTalk()
{
	GET_XNS_PARAM()

	UpdateData(TRUE);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Turns on or off the Talk function. Talk can enable the device to play 
	// the audio source. The application should use SendAudioData() to 
	// transfer the audio source that it wants to play. Talk is available 
	// only in live streaming mode and only if the control module supports 
	// XCTL_CAP_TALK capability. 
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->SetTalk(m_hDevice, m_nControlId, m_bSetTalk);
	WLOGD(_T("SetTalk():: flag=%d, ret=%d(%s)\n"), 
		m_bSetTalk, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));

}

void CAudioDlg::OnBnClickedCheckSetListen()
{
	GET_XNS_PARAM()

	UpdateData(TRUE);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Enable or disable the Listen icon from XnsSDKWindow control, 
	// when the Listen function is set to ON or OFF. Turns on or off the 
	// Listen function. Listen enables the application to play the audio 
	// source. To enable this function, the control module should support 
	// XCTL_CAP_LISTEN capability.  
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->SetListen(m_hDevice, m_nControlId, 
		XMEDIA_LIVE, m_bSetListen);
	WLOGD(_T("SetListen():: flag=%d, ret=%d(%s)\n"), 
		m_bSetListen, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CAudioDlg::OnBnClickedCheckSetAlarm()
{
	GET_XNS_PARAM()

	UpdateData(TRUE);

	if(m_nBeepControlId==0)
	{
		long nCount = m_pCtrlXnsDevice->GetControlCount(m_hDevice, XCTL_ALL);
		int i = 0;
		for (i=1; i<= nCount ; i++)
		{
			// Returns the type of control module corresponding to the control ID.
			long nType = m_pCtrlXnsDevice->GetControlType(m_hDevice, i);
			WLOGD(_T("GetControlType():: controlType=(%d)[%#02x]\n"), 
				i, nType);
			if(nType == XCTL_ALARM_BEEP)
			{
				WLOGD(_T("GetControlType():: Beep control id=%d\n"), i);
				m_nBeepControlId = i;
				break;
			}
		}
		if(m_nBeepControlId==0)
		{
			WLOGD(_T("GetControlType():: Not found beep control id\n"));
			return;
		}
	}

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Turns on or off the alarm-out device (also called digital-out device). 
	// To enable this function, the control module should support the 
	// XCTL_CAP_ALARM_ONOFF capability. 
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->SetAlarm(m_hDevice, m_nBeepControlId, m_bSetAlarm);
	WLOGD(_T("SetAlarm():: flag=%d, ret=%d(%s)\n"), 
		m_bSetAlarm, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}



// WAVE TALK
#define BUFF_NUM		200
#define NOTIFY_SIZE		4000
#define TIME_OFFSET		250
WAVEFORMATEX wave_format_in;
struct HWAVEIN__ *  wavein_handle;

char *abuffer[BUFF_NUM];
WAVEHDR WaveHeaderIn[BUFF_NUM];

int		curr_in = 0;
bool	terminate_thread_in = false;
HANDLE  WaveInEvent; 
long	tick_count = 0;
long	notify_size=0;

UINT WaveInThreadProc(void *param)
{
	CAudioDlg *parent = (CAudioDlg *)param;
	WaitForSingleObject(WaveInEvent, INFINITE); 
	tick_count = 0;
	while(1)
	{
		if((WaitForSingleObject(WaveInEvent, INFINITE) == WAIT_OBJECT_0) && (!terminate_thread_in) ) 
		{
			// [ XNS ACTIVEX HELP ]
			// -----------------------------------------------------------------------
			// Transfers the audio data to the device. This function is used when 
			// the application transfers the audio data to the device using Talk. 
			// Then, the audio data should be encoded to be suitable for the device. 
			// This function is valid only in live mode. 
			// -----------------------------------------------------------------------
			int nRet = parent->m_pCtrlXnsDevice->SendAudioData(
				*parent->m_pHDevice,					// [in] Device handle. This value is returned from CreateDevice()
				(long)((char *)(abuffer[curr_in])), // [in] Pointer to indicate the memory where the audio data is stored.
				notify_size,						// [in] Length of the audio data to transfer.
				tick_count							// [in] TimeStamp (msec)
				);

			SYSTEMTIME cur_time; 
			GetLocalTime(&cur_time); 
			CString timeStr;
			timeStr.Format(_T("%02d-%02d-%02d:%03ld"),cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds);

			DBG_LOG(_T("(%s)SendAudioData:: idx=%d, SEND=(%d)bytes, ret=[%d](%s)\n"), 
				timeStr, curr_in, notify_size, nRet, parent->m_pCtrlXnsDevice->GetErrorString(nRet));
			tick_count += TIME_OFFSET;


			curr_in++;
			if(curr_in >= BUFF_NUM)
			{
				curr_in = 0;
			}

			waveInUnprepareHeader (wavein_handle, &WaveHeaderIn[curr_in], sizeof(WAVEHDR));
			waveInPrepareHeader( wavein_handle, &WaveHeaderIn[curr_in], sizeof(WAVEHDR) );
			waveInAddBuffer( wavein_handle, &WaveHeaderIn[curr_in], sizeof(WAVEHDR) );
			continue;
		}
		break;
	}

	return 0;
}


void CAudioDlg::OnBnClickedButtonSendAudioData()
{
	GET_XNS_PARAM()

	if(m_bSendAudio)
	{
		WLOGD(_T("Already Sending audio...\n"));
		return;
	}

	m_bSendAudio = true;
	UpdateData(TRUE);
	int channel, bps, sps;

	channel = _ttoi(m_strChannel);
	bps = _ttoi(m_strBps);
	sps = _ttoi(m_strSps);
	WLOGD(_T("SendAudio:: channel=%d, bps=%d, sps=%d, packet=%d\n"), 
		channel, bps, sps, m_nSendBytes);

	notify_size = m_nSendBytes;

	for(int i=0; i<BUFF_NUM;i++)
	{
		if(abuffer[i]!=NULL)
		{
			delete[] abuffer[i];
			abuffer[i]=NULL;
		}
		abuffer[i] = new char[m_nSendBytes];
	}

	memset((char*)&wave_format_in,0, sizeof(wave_format_in));
	wave_format_in.wFormatTag		= WAVE_FORMAT_PCM;
	wave_format_in.nChannels		= channel;
	wave_format_in.nSamplesPerSec	= sps; 
	wave_format_in.wBitsPerSample	= bps;
	wave_format_in.nBlockAlign		= (channel*bps/8);
	wave_format_in.nAvgBytesPerSec	= (sps*wave_format_in.nBlockAlign);
	wave_format_in.cbSize			= 0;

	terminate_thread_in=false;
	curr_in = 0;
	WaveInEvent = CreateEvent(NULL, FALSE, FALSE, NULL);  
	AfxBeginThread(WaveInThreadProc, this, THREAD_PRIORITY_NORMAL , 0, 0, NULL);  

	int result = waveInOpen( &wavein_handle, WAVE_MAPPER, 
		(WAVEFORMATEX *) &wave_format_in,
		(DWORD) WaveInEvent,
		0, CALLBACK_EVENT);

	for(int i=0; i<BUFF_NUM; i++) 
	{
		WaveHeaderIn[i].lpData = abuffer[i];
		WaveHeaderIn[i].dwBufferLength = m_nSendBytes; 
		waveInPrepareHeader( wavein_handle, &WaveHeaderIn[i], sizeof(WAVEHDR) );
		waveInAddBuffer( wavein_handle, &WaveHeaderIn[i], sizeof(WAVEHDR) );
	}
	waveInStart(wavein_handle);
}

void CAudioDlg::OnBnClickedButtonStopAudioData()
{
	GET_XNS_PARAM()
	waveInStop(wavein_handle);
	waveInReset(wavein_handle);
	waveInClose(wavein_handle);
	m_bSendAudio = false;
}