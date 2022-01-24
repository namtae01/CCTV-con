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
// SdkTestDlg.h : header file
//

#pragma once
#include "XnsCommon.h"
#include "xnssdkwindowctrl.h"
#include "xnssdkdevicectrl.h"

#include "SdkTest.h"
#include "DeviceInfoDlg.h"
#include "MediaStreamDlg.h"
#include "PlayBackDlg.h"
#include "AudioDlg.h"
#include "PtzDlg.h"
#include "PresetDlg.h"
#include "BackupDlg.h"
#include "DeviceMiscDlg.h"
#include "WinStartDlg.h"
#include "ControlZoomDlg.h"
#include "ControlVolDlg.h"
#include "DisplayInfoDlg.h"
#include "WinMiscDlg.h"
#include "ChangePwDlg.h"

#include "afxwin.h"
#include "afxmt.h"

// Macro for logging
#define DBG_LOG(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("(%S:%d)"), __FUNCTION__, __LINE__);	\
	strMessage.AppendFormat(__VA_ARGS__);\
	OutputDebugString(strMessage);\
}while(0);

#define MSG_BOX(...) do{\
	CString strMessage = _T("");\
	strMessage.Format(__VA_ARGS__);\
	AfxMessageBox(strMessage);\
}while(0);

#define WLOGD(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("[XnsSdkDevice] "));\
	strMessage.AppendFormat(__VA_ARGS__);\
	long nLen = m_pCtrlEditLog->GetWindowTextLength(); \
	if( ((UINT)nLen+strMessage.GetLength()) > (m_pCtrlEditLog->GetLimitText()) ) \
	{	\
		m_pCtrlEditLog->SetWindowText(_T("------ Edit box clear ------\n")); \
		nLen = m_pCtrlEditEvent->GetWindowTextLength(); \
	} \
	m_pCtrlEditLog->SetFocus(); \
	m_pCtrlEditLog->SetSel(nLen, nLen); \
	m_pCtrlEditLog->ReplaceSel(strMessage); \
}while(0);

#define WLOGW(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("[XnsSdkWindow] "));\
	strMessage.AppendFormat(__VA_ARGS__);\
	long nLen = m_pCtrlEditLog->GetWindowTextLength(); \
	if( ((UINT)nLen+strMessage.GetLength()) > (m_pCtrlEditLog->GetLimitText()) ) \
	{	\
		m_pCtrlEditLog->SetWindowText(_T("------ Edit box clear ------\n")); \
		nLen = m_pCtrlEditEvent->GetWindowTextLength(); \
	} \
	m_pCtrlEditLog->SetFocus(); \
	m_pCtrlEditLog->SetSel(nLen, nLen); \
	m_pCtrlEditLog->ReplaceSel(strMessage); \
}while(0);

#define ELOGD(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("[XnsSdkDevice] "));\
	strMessage.AppendFormat(__VA_ARGS__);\
	m_cCS.Lock(); \
	long nLen = m_pCtrlEditEvent->GetWindowTextLength(); \
	if( ((UINT)nLen+strMessage.GetLength()) > (m_pCtrlEditEvent->GetLimitText()) ) \
	{	\
		m_pCtrlEditEvent->SetWindowText(_T("------ Edit box clear ------\n")); \
		nLen = m_pCtrlEditEvent->GetWindowTextLength(); \
	} \
	m_pCtrlEditEvent->SetFocus(); \
	m_pCtrlEditEvent->SetSel(nLen, nLen); \
	m_pCtrlEditEvent->ReplaceSel(strMessage); \
	m_cCS.Unlock(); \
}while(0);

#define ELOGDNOLOCK(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("[XnsSdkDevice] "));\
	strMessage.AppendFormat(__VA_ARGS__);\
	long nLen = m_pCtrlEditEvent->GetWindowTextLength(); \
	if( ((UINT)nLen+strMessage.GetLength()) > (m_pCtrlEditEvent->GetLimitText()) ) \
	{	\
	m_pCtrlEditEvent->SetWindowText(_T("------ Edit box clear ------\n")); \
	nLen = m_pCtrlEditEvent->GetWindowTextLength(); \
	} \
	m_pCtrlEditEvent->SetFocus(); \
	m_pCtrlEditEvent->SetSel(nLen, nLen); \
	m_pCtrlEditEvent->ReplaceSel(strMessage); \
}while(0);

#define ELOGW(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("[XnsSdkWindow] "));\
	strMessage.AppendFormat(__VA_ARGS__);\
	m_cCS.Lock(); \
	long nLen = m_pCtrlEditEvent->GetWindowTextLength(); \
	if( ((UINT)nLen+strMessage.GetLength()) > (m_pCtrlEditEvent->GetLimitText()) ) \
	{	\
		m_pCtrlEditEvent->SetWindowText(_T("------ Edit box clear ------\n")); \
		nLen = m_pCtrlEditEvent->GetWindowTextLength(); \
	} \
	m_pCtrlEditEvent->SetFocus(); \
	m_pCtrlEditEvent->SetSel(nLen, nLen); \
	m_pCtrlEditEvent->ReplaceSel(strMessage); \
	m_cCS.Unlock(); \
}while(0);

#define GET_XNS_PARAM() do{ \
	if(m_pHDevice) m_hDevice = *m_pHDevice; \
	if(m_pNControlId) m_nControlId = *m_pNControlId; \
	if(m_pHMediaSource) m_hMediaSource = *m_pHMediaSource; \
	if(m_pHMediaSourcePlayback) m_hMediaSourcePlayback = *m_pHMediaSourcePlayback; \
}while(0);

// CSdkTestDlg dialog
class CSdkTestDlg : public CDialog
{
// Construction
public:
	CSdkTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SDKTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


private:
	CDeviceInfoDlg *	m_pDlgDeviceInfo;
	
	CPlayBackDlg *		m_pDlgPlayBack;
	CAudioDlg *			m_pAudioDlg;
	CPtzDlg *			m_pPtz;
	CBackupDlg *		m_pBackup;
	CDeviceMiscDlg *	m_pDeviceMisc;
	CWinStartDlg *		m_pWindowInit;
	CControlZoomDlg *	m_pControlZoom;
	CControlVolDlg *	m_pControlVol;
	CDisplayInfo *		m_pDisplayInfo;
	CWinMiscDlg *		m_pWinMisc;
	CMediaStreamDlg *	m_pDlgMediaStream;
	CChangePwDlg*		m_pChangePw;
	CMapStringToString	m_AutoSearchMap;

	CCriticalSection	m_cCS;
	CCriticalSection	m_cCS2;
	bool				m_bLmouseDown;
	long				m_nStartX;
	long				m_nStartY;
	long				m_nEndX;
	long				m_nEndY;
	
	void OpenChildDialog();
	void CloseChildDialog();

public:
	CXnssdkwindowctrl	m_ctrlXnsWindowLive;
	CXnssdkwindowctrl	m_ctrlXnsWindowPlayback;
	CXnssdkdevicectrl	m_ctrlXnsDevice;
	long				m_hDevice;
	long				m_nControlId;
	long				m_hMediaSource;
	long				m_hMediaSourcePlayback;
	CEdit				m_ctrlEditLog;
	CEdit				m_ctrlEditEvent;
	CEdit *				m_pCtrlEditLog;
	CEdit *				m_pCtrlEditEvent;

	bool				m_bAreaZoom;
	
	afx_msg void OnDestroy();

	
	DECLARE_EVENTSINK_MAP()
	void OnAlarmOutControlFailedXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode);
	void OnBackupProgressXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode, long nProgress, long tStart, long tEnd);
	void OnCallbackEventXnssdkdevicectrl(LPCTSTR szVendorName, LPCTSTR szModelName, LPCTSTR szAddress, long nPort, LPCTSTR szUserID, LPCTSTR szPassword, long nEventType, long nEventIndex, long tEventTime);
	void OnConnectFailedXnssdkdevicectrl(long nDeviceID, long nErrorCode);
	void OnControlCapabilityChangedXnssdkdevicectrl(long nDeviceID, long nControlID, long nCapabilityMask);
	void OnControlLocalNameChangedXnssdkdevicectrl(long nDeviceID, long nControlID);
	void OnControlRemoteNameChangedXnssdkdevicectrl(long nDeviceID, long nControlID);
	void OnControlStatusChangedXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode, long nStatusMask);
	void OnDeviceStatusChangedXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nDeviceStatus, long nHddCondition);
	void OnExportConfigProgressXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nProgress);
	void OnFanBrokenXnssdkdevicectrl(long nDeviceID);
	void OnGetMotionGridXnssdkdevicectrl(long nDeviceID, long nControlID, long nGridWidth, long nGridHeight, long pGridArray);
	void OnGetPresetListXnssdkdevicectrl(long nDeviceID, long nControlID, long hPresetListList);
	void OnGetPtzPosXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode, long nPan, long nTilt, long nZoom);
	void OnHDDFailedXnssdkdevicectrl(long nDeviceID, long nHDDNumber);
	void OnHDDFulledXnssdkdevicectrl(long nDeviceID, long nHDDNumber);
	void OnImportConfigProgressXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nProgress);
	void OnIvOccurEventXnssdkdevicectrl(long nDeviceID, long nControlID, long tEventUTC, long nIvType);
	void OnMotionEventXnssdkdevicectrl(long nDeviceID, long nControlID, long tEventUTC);
	void OnMotionSearchXnssdkdevicectrl(long nDeviceID, long nControlID, long hTimeline);
	void OnNewMediaXnssdkdevicectrl(long nDeviceID, long nControlID, long nMediaType, long hMediaData, long nInputType, long nFrameType, long nFrameTime, long nFrameSize, long nTimestamp);
	void OnPasswordChangedXnssdkdevicectrl(long nDeviceID, LPCTSTR szID);
	void OnPtzControlFailedXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode);
	void OnRecvSerialDataXnssdkdevicectrl(long nDeviceID, long nCmdID, long nRecvDataLength, long pRecvData);
	void OnSearchCalendarXnssdkdevicectrl(long nDeviceID, long nControlID, long nRecDay);
	void OnSearchDayXnssdkdevicectrl(long nDeviceID, long nControlID, long hTimeline);
	void OnSensorEventXnssdkdevicectrl(long nDeviceID, long nControlID, long nSensorNumber, long tEventUTC);
	void OnTalkFailedXnssdkdevicectrl(long nDeviceID, long nControlID, long nErrorCode);
	void OnUploadSoftwareProgressXnssdkdevicectrl(long nDeviceID, long nErrorCode, long nProgress);
	void OnVideoLossEventXnssdkdevicectrl(long nDeviceID, long nControlID, long tEventUTC);
	void OnMouseMoveXnssdkwindowctrlLive(long nFlags, long nX, long nY);
	void OnBufferEmptyXnssdkwindowctrlLive();
	void OnBufferFullXnssdkwindowctrlLive();
	void OnEventStatusChangedXnssdkwindowctrlLive(long nOldEventStatus, long nNewEventStatus);
	void OnFrameTimeChangedXnssdkwindowctrlLive(long tFrameTime);
	void OnImageResolutionChangedXnssdkwindowctrlLive(long nWidth, long nHeight);
	void OnKeyDownXnssdkwindowctrlLive(long nChar, long nRepCnt, long nFlags);
	void OnKeyUpXnssdkwindowctrlLive(long nChar, long nRepCnt, long nFlags);
	void OnLButtonDblClkXnssdkwindowctrlLive(long nFlags, long nX, long nY);
	void OnLButtonDownXnssdkwindowctrlLive(long nFlags, long nX, long nY);
	void OnLButtonUpXnssdkwindowctrlLive(long nFlags, long nX, long nY);
	void OnMediaOffXnssdkwindowctrlLive();
	void OnMediaOnXnssdkwindowctrlLive();
	void OnMouseHoverXnssdkwindowctrlLive();
	void OnMouseLeaveXnssdkwindowctrlLive();
	void OnPreBufferEmptyXnssdkwindowctrlLive();
	void OnPreBufferFullXnssdkwindowctrlLive();
	void OnRButtonDblClkXnssdkwindowctrlLive(long nFlags, long nX, long nY);
	void OnRButtonDownXnssdkwindowctrlLive(long nFlags, long nX, long nY);
	void OnRButtonUpXnssdkwindowctrlLive(long nFlags, long nX, long nY);
	void OnWindowSizeChangedXnssdkwindowctrlLive(long lWidth, long lHeight);
	void OnDeviceDetected3Xnssdkdevicectrl(LPCTSTR szVendorName, LPCTSTR szModelName, LPCTSTR szDeviceName, LPCTSTR szIP, LPCTSTR szSubnetMask, LPCTSTR szGateway, LPCTSTR szMac, long nPort, long nHttpPort, LPCTSTR szModelType, 
		BOOL bSupportIpInstall, long nNetworkMode, BOOL bDHCPIPInstall, long nDeviceProtocolType, LPCTSTR szUUID);
	void OnChangeDeviceAdminPasswordXnssdkdevicectrl(long nDeviceID, long nErrorCode);
	virtual void OnOK();
};
