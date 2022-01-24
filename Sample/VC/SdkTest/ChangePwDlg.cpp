// ChangePwDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SdkTest.h"
#include "ChangePwDlg.h"
//#include "afxdialogex.h"
#include "SdkTestDlg.h"


IMPLEMENT_DYNAMIC(CChangePwDlg, CDialog)

CChangePwDlg::CChangePwDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangePwDlg::IDD, pParent)
	, m_strCurrentPw(_T(""))
	, m_strNewPw(_T(""))
	, m_strConfirmPw(_T(""))
{
	if(pParent)
	{
		CSdkTestDlg *ptr = dynamic_cast<CSdkTestDlg *>(pParent);
		m_pCtrlXnsWindowLive = &(ptr->m_ctrlXnsWindowLive);
		m_pCtrlXnsWindowPlayback = &(ptr->m_ctrlXnsWindowPlayback);
		m_pCtrlXnsDevice = &(ptr->m_ctrlXnsDevice);
		m_pCtrlEditLog = ptr->m_pCtrlEditLog;
		m_pHDevice = &(ptr->m_hDevice);
		m_pHMediaSource = &(ptr->m_hMediaSource);
		m_pHMediaSourcePlayback = &(ptr->m_hMediaSourcePlayback);
		m_pNControlId = &(ptr->m_nControlId);
	}
}

CChangePwDlg::~CChangePwDlg()
{
}

void CChangePwDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CURRENT_PW, m_strCurrentPw);
	DDX_Text(pDX, IDC_EDIT_NEW_PW, m_strNewPw);
	DDX_Text(pDX, IDC_EDIT_CONFIRM_PW, m_strConfirmPw);
}


BEGIN_MESSAGE_MAP(CChangePwDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_PW, &CChangePwDlg::OnBnClickedButtonChangePw)
END_MESSAGE_MAP()


// CChangePwDlg 메시지 처리기입니다.


void CChangePwDlg::OnBnClickedButtonChangePw()
{
	GET_XNS_PARAM()
	UpdateData(TRUE);
	int nErrorCode = m_pCtrlXnsDevice->ChangeDeviceAdminPassword(m_hDevice, m_strCurrentPw, m_strNewPw, m_strConfirmPw);
	WLOGD(_T("Current PW=%s, New PW=%s, Confirm PW=%s, errcode=[%d](%s)\n"),
		m_strCurrentPw, m_strNewPw, m_strConfirmPw, nErrorCode, m_pCtrlXnsDevice->GetErrorString(nErrorCode));
}
