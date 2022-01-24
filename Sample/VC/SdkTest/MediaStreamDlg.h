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
// BackupSearchDlg.h : header file
//

#pragma once

// xns header files
#include "XnsCommon.h"
#include "XnsDeviceInterface.h"
#include "xnssdkdevicectrl.h"
#include "xnssdkwindowctrl.h"
#include "afxdtctl.h"


// CMediaStreamDlg dialog

class CMediaStreamDlg : public CDialog
{
public:
	CMediaStreamDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMediaStreamDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_MEDIA_STREAM };
	DECLARE_DYNAMIC(CMediaStreamDlg)

private:
	CXnssdkdevicectrl *		m_pCtrlXnsDevice;			// Xns SDK Device Control
	CXnssdkwindowctrl *		m_pCtrlXnsWindowLive;		// xns SDK Live Window Control
	CXnssdkwindowctrl *		m_pCtrlXnsWindowPlayback;	// xns SDK Playback Window Control
	long					m_hDevice;					// Device Handle
	long *					m_pHDevice;					
	long					m_nControlId;				// Control ID
	long *					m_pNControlId;
	long					m_hMediaSource;				// Media stream ID
	long *					m_pHMediaSource;
	long					m_hMediaSourcePlayback;
	long *					m_pHMediaSourcePlayback;
	CEdit *					m_pCtrlEditLog;				// Log Edit Control
	CEdit *					m_pCtrlEditEvent;			// Event Edit Control

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAcquireMediaAuthority(void);
	afx_msg void OnBnClickedButtonReleaseMediaAuthority();
	afx_msg void OnBnClickedButtonOpenMedia();
	afx_msg void OnBnClickedButtonCloseMedia();
	afx_msg void OnBnClickedButtonOpenStream();
	afx_msg void OnBnClickedButtonCloseStream();
	afx_msg void OnBnClickedButtonSuspendStream();
	afx_msg void OnBnClickedButtonSuspendAllStream();
	afx_msg void OnBnClickedButtonResumeStream();
	afx_msg void OnBnClickedButtonResumeAllStream();
	afx_msg void OnBnClickedButtonReopenAllStream();
	afx_msg void OnBnClickedButtonIsPlaying();
	afx_msg void OnBnClickedButtonHasAuthority();
	afx_msg void OnBnClickedButtonOpenMediaEx();
private:
	int m_nCid;
};
