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
#include "afxdtctl.h"
// CDeviceMiscDlg dialog

class CDeviceMiscDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeviceMiscDlg)

public:
	CDeviceMiscDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDeviceMiscDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_DEVICE_MISC };

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
	afx_msg void OnBnClickedButtonDateToTimeT();
	afx_msg void OnBnClickedButtonMiscAutoscan();
	afx_msg void OnBnClickedButtonIpInstall();
private:
	CDateTimeCtrl m_ctrlDate;
	CDateTimeCtrl m_ctrlTime;
	CIPAddressCtrl m_ctrlIp;
	CIPAddressCtrl m_ctrlSubnetMask;
	CIPAddressCtrl m_ctrlGateway;
	int m_nPort;
	int m_nHttpPort;
	CString m_strMac;
	CString m_strPassword;
	int m_nDiscardSec;
public:
	virtual BOOL OnInitDialog();
private:
	CComboBox m_ctrlEventType;
public:
	afx_msg void OnBnClickedButtonSetEventDiscardTime();
	afx_msg void OnBnClickedButtonXmlReadConfig();
private:
	CString m_strXmlKey;
	CString m_strXmlValue;
public:
	afx_msg void OnBnClickedButtonXmlWriteConfig();
	afx_msg void OnBnClickedButtonXmlDeleteConfig();
	afx_msg void OnBnClickedButtonXmlFindConfigChild();
	afx_msg void OnCbnSelchangeComboDiscardEventType();
};
