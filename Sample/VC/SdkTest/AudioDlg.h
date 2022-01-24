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

// CAudioDlg dialog

class CAudioDlg : public CDialog
{
	DECLARE_DYNAMIC(CAudioDlg)

public:
	CAudioDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAudioDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_AUDIO_ALARM };

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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bSetTalk;
	BOOL m_bSetListen;
	BOOL m_bSetAlarm;
public:
	afx_msg void OnBnClickedCheckSetTalk();
	afx_msg void OnBnClickedCheckSetListen();
	afx_msg void OnBnClickedCheckSetAlarm();
	afx_msg void OnBnClickedButtonSendAudioData();
	afx_msg void OnBnClickedButtonStopAudioData();
private:
	CComboBox m_ctrlChannel;
	CComboBox m_ctrlBps;
	CComboBox m_ctrlSps;
	long m_nSendBytes;
	CString m_strChannel;
	CString m_strBps;
	CString m_strSps;
	bool	m_bSendAudio;
	long	m_nBeepControlId;
	
public:
	virtual BOOL OnInitDialog();

	friend UINT WaveInThreadProc(void *param);
};
