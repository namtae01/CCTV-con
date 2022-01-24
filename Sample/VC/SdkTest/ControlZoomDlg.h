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

// CControlZoomDlg dialog

class CControlZoomDlg : public CDialog
{
	DECLARE_DYNAMIC(CControlZoomDlg)

public:
	CControlZoomDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CControlZoomDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONTROL_ZOOM };

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
public:
	afx_msg void OnBnClickedButtonGetZoomInfo();
	afx_msg void OnBnClickedButtonGetZoomLevel();
	afx_msg void OnBnClickedButtonGetZoomRate();
	afx_msg void OnBnClickedButtonGetZoomClear();
private:
	int m_nX;
	int m_nY;
	int m_nLevel;
	float m_fX;
	float m_fY;
	float m_fWidth;
	float m_fHeight;
public:
	afx_msg void OnBnClickedButtonImportConfig();
	afx_msg void OnBnClickedButtonExportConfig();
	afx_msg void OnBnClickedButtonUpdate();
};
