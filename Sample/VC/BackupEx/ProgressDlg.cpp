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
// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BackupEx.h"
#include "ProgressDlg.h"


// ProgressDlg dialog

IMPLEMENT_DYNAMIC(ProgressDlg, CDialog)

ProgressDlg::ProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ProgressDlg::IDD, pParent)
	, m_pBackupExDlg(NULL)
	, m_strPercent(_T(""))
{
}

ProgressDlg::ProgressDlg(class CBackupExDlg * pDlg, CWnd* pParent /*=NULL*/)
	: CDialog(ProgressDlg::IDD, pParent)
{
	m_pBackupExDlg = pDlg;
}

ProgressDlg::~ProgressDlg()
{
}

void ProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Text(pDX, IDC_STR_PERCENT, m_strPercent);
}

BEGIN_MESSAGE_MAP(ProgressDlg, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PROGRESS_CANCEL, &ProgressDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

// ProgressDlg message handlers
BOOL ProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_Progress.SetRange(0,100);
	m_Progress.SetPos(0);
	SetTimer(0, 500, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void ProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 0 && m_pBackupExDlg != NULL)
	{
		long nProgress = m_pBackupExDlg->m_nProgress;
		if(nProgress < 0) 
		{
			KillTimer(nIDEvent);
			OnCancel();
		}
		if(nProgress >= 100) 
		{
			KillTimer(nIDEvent);
			OnOK();
		}
		m_strPercent.Format(_T("%d %%"), nProgress);
		m_Progress.SetPos(nProgress);
		UpdateData(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}

void ProgressDlg::OnBnClickedCancel()
{
	OnCancel();
}
