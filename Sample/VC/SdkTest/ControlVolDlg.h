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
// ControlVolDlg.h : header file
//

#pragma once

// xns header files
#include "xnssdkwindowctrl.h"
#include "xnssdkdevicectrl.h"
#include "XnsCommon.h"
#include "XnsDeviceInterface.h"
#include "afxwin.h"
#include "afxcmn.h"

// CControlVolDlg dialog

class CControlVolDlg : public CDialog
{
	DECLARE_DYNAMIC(CControlVolDlg)

public:
	CControlVolDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CControlVolDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONTROL_VOL };

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

	bool				m_bSound;			// Sound Flag
	long				m_nVolume;			// Sound Volume.(0~100)
	int					m_nRadioButtonBmp;	// 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSetSound();
	afx_msg void OnBnClickedButtonSetVolume();
	afx_msg void OnBnClickedButtonGetVolume();
	afx_msg void OnBnClickedButtonSaveSnapshot();
	afx_msg void OnBnClickedButtonPrintSnapshot();
};
