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
// PtzDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "CDXnsSdkDevice.h"
#include "CDXnsSdkWindow.h"

typedef enum
{
	SL_STATUS_CONNECTED = 0,
	SL_STATUS_DISCONNECTED,
}SLIVE_BUTTON_STATUS;

// CPtzDlg dialog
class CPtzDlg : public CDialog
{
// Construction
public:
	CPtzDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PTZ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// XNS Device control and Window control variables
	// -----------------------------------------------------------------------
	CDXnsSdkWindow		m_ctrlXnsWindow;	// XnsWindow control
	CDXnsSdkDevice		m_ctrlXnsDevice;	// XnsDevice control
	long				m_hDevice;			// Device handle
	long				m_hMediaSource;		// Media stream ID
	long				m_nControlId;		// Control ID

	CComboBox			m_ctrlModelList;
	CString				m_strModelName;
	CIPAddressCtrl		m_ctrlIpAddress;
	int					m_nPort;
	CString				m_strId;
	CString				m_strPasswd;
	bool				m_bAreaZoom;
	int					m_nStartX;
	int					m_nStartY;
	int					m_nEndX;
	int					m_nEndY;

	int					m_nPtzSpeed;
	int					m_nPan;
	int					m_nTilt;
	int					m_nZoom;
	bool				m_bMenuControl;
	CComboBox			m_ctrlAutoScan;
	CComboBox			m_ctrlAutoPan;

	bool				m_bIsMouseDown;

public:
    CString m_saveIni;
	CString m_facilID;


	void setBtnStatus(SLIVE_BUTTON_STATUS nStatus);
	void moveCamera(const int nCommand);
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	DECLARE_EVENTSINK_MAP()
	void OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode);
	CEdit m_ctrlEditLog;
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCheckAreazoom();
	void OnLButtonDownXnssdkwindowctrl(long nFlags, long nX, long nY);
	void OnLButtonUpXnssdkwindowctrl(long nFlags, long nX, long nY);
	void OnMouseMoveXnssdkwindowctrl(long nFlags, long nX, long nY);
	afx_msg void OnBnClickedButtonZoom1x();
	afx_msg void OnBnClickedButtonGetPtz();
	afx_msg void OnBnClickedButtonSetPtz();

	void OnGetPtzPosXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode, long nPan, long nTilt, long nZoom);
	afx_msg void OnBnClickedCheckMenuOn();
	afx_msg void OnBnClickedButtonMenuUp();
	afx_msg void OnBnClickedButtonMenuDown();
	afx_msg void OnBnClickedButtonMenuLeft();
	afx_msg void OnBnClickedButtonMenuRight();
	afx_msg void OnBnClickedButtonMenuEnter();
	afx_msg void OnBnClickedButtonMenuCancel();
	afx_msg void OnBnClickedButtonPreset();
	void OnGetPresetListXnssdkdevicectrl(long nDeviceID, long nControlID, long hPresetListList);

	afx_msg void OnCbnSelchangeComboAutopan();
	afx_msg void OnCbnSelchangeComboAutoscan();
	void OnGetHPtzListXnssdkdevicectrl(long nDeviceID, long nControlID, long nType, long hHptzList);
	int m_nDeviceProtocol;
	int m_nMediaProtocol;
	int m_nHttpPort;
	float m_fPan;
	float m_fTilt;
	float m_fZoom;
	afx_msg void OnBnClickedButtonGetPtzNormalize();
	afx_msg void OnBnClickedButtonSetPtzNormalize();
	void OnGetPtzPosNormalizeXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode, float fPan, float fTilt, float fZoom);
	virtual void OnOK();
	void SetCheckSunapi();
	CButton m_ctrlSunapi;
	afx_msg void OnBnClickedCheckSunapi();
	afx_msg void OnCbnSelchangeComboModelList();
	afx_msg void OnBnClickedButtonDownright();
	afx_msg void OnBnClickedButtonSnap();
};
