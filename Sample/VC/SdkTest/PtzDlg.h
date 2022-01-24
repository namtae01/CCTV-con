///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011 by Hanwha Techwin, Inc.
//
// This software is copyrighted by, and is the sole property of Hanwha Techwin.
// All rights, title, ownership, or other interests in the software remain the
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


// CPtzDlg dialog

class CPtzDlg : public CDialog
{
	DECLARE_DYNAMIC(CPtzDlg)

public:
	CPtzDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPtzDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PTZ };

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
	void moveCamera(const int nCommand);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckMenuOn();
	afx_msg void OnBnClickedButtonMenuUp();
	afx_msg void OnBnClickedButtonMenuDown();
	afx_msg void OnBnClickedButtonMenuLeft();
	afx_msg void OnBnClickedButtonMenuRight();
	afx_msg void OnBnClickedButtonMenuEnter();
	afx_msg void OnBnClickedButtonMenuCancel();
	afx_msg void OnBnClickedButtonFreeMove();
	afx_msg void OnBnClickedCheckAreazoom();
	afx_msg void OnBnClickedButtonPreset();
	afx_msg void OnBnClickedButtonGetPtz();
	afx_msg void OnBnClickedButtonSetPtz();
	afx_msg void OnBnClickedButtonZoom1x();
private:
	CComboBox	m_ctrlScan;
	CComboBox	m_ctrlAutoPan;
	CComboBox	m_ctrlPattern;
	int			m_nPan;
	int			m_nTilt;
	int			m_nZoom;
	bool		m_bMenuControl;
	bool		m_bAreaZoom;
	bool*		m_pBAreaZoom;
	int			m_nFreeX;
	int			m_nFreeY;
	int			m_nPtzSpeed;
public:
	virtual BOOL OnInitDialog();

	
	afx_msg void OnCbnSelchangeComboAutoscan();
	afx_msg void OnCbnSelchangeComboAutopan();
	afx_msg void OnCbnSelchangeComboPattern();
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonUpleft();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonDownleft();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonDownright();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonUpright();
	afx_msg void OnBnClickedButtonZoomIn();
	afx_msg void OnBnClickedButtonZoomOut();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedCheckOsdOn();
private:
	BOOL m_bOsd;
};
