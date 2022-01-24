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

// xns header files
#include "XnsCommon.h"
#include "XnsDeviceInterface.h"
#include "xnssdkdevicectrl.h"
#include "xnssdkwindowctrl.h"
#include "afxdtctl.h"

// CDisplayInfo dialog

class CDisplayInfo : public CDialog
{
	DECLARE_DYNAMIC(CDisplayInfo)
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

public:
	CDisplayInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDisplayInfo();

// Dialog Data
	enum { IDD = IDD_DIALOG_WINDOW_DISPLAYINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGetCurrentFrametime();
	afx_msg void OnBnClickedButtonFirstFrametime();
	afx_msg void OnBnClickedButtonGetFrametime();
	afx_msg void OnBnClickedButtonFramesize();
	afx_msg void OnBnClickedButtonGetFrametype();
	afx_msg void OnBnClickedButtonInputtype();
	afx_msg void OnBnClickedButtonSetBrightness();
	afx_msg void OnBnClickedButtonGetBrightness();
	afx_msg void OnBnClickedButtonSetContrast();
	afx_msg void OnBnClickedButtonGetContrast();
	afx_msg void OnBnClickedButtonSetDeinterlacemode();
	afx_msg void OnBnClickedButtonGetTimestemp();
	afx_msg void OnBnClickedButtonSetDefogmode();
};
