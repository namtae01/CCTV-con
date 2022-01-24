#pragma once
#include "afxwin.h"

#include "xnssdkwindowctrl.h"
#include "xnssdkdevicectrl.h"
#include "XnsCommon.h"
#include "XnsDeviceInterface.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"

class CChangePwDlg : public CDialog
{
	DECLARE_DYNAMIC(CChangePwDlg)

public:
	CChangePwDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChangePwDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CHANGE_PW };

private:
	CXnssdkwindowctrl * m_pCtrlXnsWindowLive;
	CXnssdkwindowctrl * m_pCtrlXnsWindowPlayback;
	CXnssdkdevicectrl * m_pCtrlXnsDevice;
	long				m_hDevice;
	long*				m_pHDevice;
	long				m_nControlId;
	long *				m_pNControlId;
	long				m_hMediaSource;
	long *				m_pHMediaSource;
	long				m_hMediaSourcePlayback;
	long *				m_pHMediaSourcePlayback;
	CEdit*				m_pCtrlEditLog;
	CEdit *				m_pCtrlEditEvent;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCurrentPw;
	CString m_strNewPw;
	CString m_strConfirmPw;
	afx_msg void OnBnClickedButtonChangePw();
};
