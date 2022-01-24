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



///////////////////////////////////////
#define DISPLAY_VAlUE	10
#define ON				1
#define OFF				0
///////////////////////////////////////

// CDeviceInfoDlg dialog

class CDeviceInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeviceInfoDlg)

public:
	CDeviceInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDeviceInfoDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONFIG };

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
	afx_msg void OnBnClickedButtonDeviceInit();
	afx_msg void OnBnClickedButtonDeviceCreate();
	afx_msg void OnBnClickedButtonSetConnectionInfo();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonConnectNonblock();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonDeviceInfo();
	afx_msg void OnBnClickedButtonControlInfo();
	afx_msg void OnBnClickedButtonDeviceRelease();
	virtual BOOL OnInitDialog();
private:
	CComboBox		m_ctrlModelList;
	CString			m_strId;
	CString			m_strPassword;
	int				m_nPort;
	CIPAddressCtrl	m_ctrlIpAddress;
	CString			m_strModelName;
public:
	CComboBox m_ctrlDeviceProtocol;
	int m_nDeviceProtocol;
	CComboBox m_ctrlMediaProtocol;
	int m_nMediaProtocol;
	int m_nHttpPort;
	afx_msg void OnCbnSelchangeComboModelList();
	afx_msg void OnCbnSelchangeComboProtocolList();
	afx_msg void OnCbnSelchangeComboProtocolList2();
	void ReconnectNewPw(CString strNewPw);
	afx_msg void OnIpnFieldchangedIpaddress(NMHDR *pNMHDR, LRESULT *pResult);
};
