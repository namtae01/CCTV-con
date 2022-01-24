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
// http://security.hanwhatechwin.com/
///////////////////////////////////////////////////////////////////////////////////
// ControlZoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "ControlZoomDlg.h"

#include "SdkTestDlg.h"


// CControlZoomDlg dialog

IMPLEMENT_DYNAMIC(CControlZoomDlg, CDialog)

CControlZoomDlg::CControlZoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControlZoomDlg::IDD, pParent)
	, m_nX(0)
	, m_nY(0)
	, m_nLevel(0)
	, m_fX(0)
	, m_fY(0)
	, m_fWidth(0)
	, m_fHeight(0)
{
	if(pParent)
	{
		CSdkTestDlg *ptr = dynamic_cast<CSdkTestDlg *>(pParent);
		m_pCtrlXnsDevice = &(ptr->m_ctrlXnsDevice);
		m_pCtrlXnsWindowLive = &(ptr->m_ctrlXnsWindowLive);
		m_pCtrlXnsWindowPlayback = &(ptr->m_ctrlXnsWindowPlayback);
		m_pCtrlEditLog = ptr->m_pCtrlEditLog;
		m_pCtrlEditEvent = ptr->m_pCtrlEditEvent;
		m_pHDevice = &(ptr->m_hDevice);
		m_pHMediaSource = &(ptr->m_hMediaSource);
		m_pHMediaSourcePlayback = &(ptr->m_hMediaSourcePlayback);
		m_pNControlId = &(ptr->m_nControlId);
	}
}

CControlZoomDlg::~CControlZoomDlg()
{
}

void CControlZoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ZOOM_LEVEL_X, m_nX);
	DDX_Text(pDX, IDC_EDIT_ZOOM_LEVEL_Y, m_nY);
	DDX_Text(pDX, IDC_EDIT_ZOOM_LEVEL_LEVEL, m_nLevel);
	DDX_Text(pDX, IDC_EDIT_ZOOM_RATE_X, m_fX);
	DDX_Text(pDX, IDC_EDIT_ZOOM_RATE_Y, m_fY);
	DDX_Text(pDX, IDC_EDIT_ZOOM_RATE_W, m_fWidth);
	DDX_Text(pDX, IDC_EDIT_ZOOM_RATE_H, m_fHeight);
}


BEGIN_MESSAGE_MAP(CControlZoomDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_GET_ZOOM_INFO, &CControlZoomDlg::OnBnClickedButtonGetZoomInfo)
	ON_BN_CLICKED(IDC_BUTTON_GET_ZOOM_LEVEL, &CControlZoomDlg::OnBnClickedButtonGetZoomLevel)
	ON_BN_CLICKED(IDC_BUTTON_GET_ZOOM_RATE, &CControlZoomDlg::OnBnClickedButtonGetZoomRate)
	ON_BN_CLICKED(IDC_BUTTON_GET_ZOOM_CLEAR, &CControlZoomDlg::OnBnClickedButtonGetZoomClear)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_CONFIG, &CControlZoomDlg::OnBnClickedButtonImportConfig)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_CONFIG, &CControlZoomDlg::OnBnClickedButtonExportConfig)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CControlZoomDlg::OnBnClickedButtonUpdate)
END_MESSAGE_MAP()


// CControlZoomDlg message handlers

void CControlZoomDlg::OnBnClickedButtonGetZoomInfo()
{
	GET_XNS_PARAM()

	double lfX, lfY, lfWidth, lfHeight;
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns the ratio of the currently set digital zoom. 
	// -----------------------------------------------------------------------
	long nZoomFactor = m_pCtrlXnsWindowLive->GetZoomInfo(
		&lfX,		// [out] Use the zoom ratio to calculate the top left X coordinate.
		&lfY,		// [out] Use the zoom ratio to calculate the top left Y coordinate.
		&lfWidth,	// [out] Use the zoom ratio to calculate the width.
		&lfHeight	// [out] Use the zoom ratio to calculate the height.
		);
	WLOGW(_T("GetZoomInfo():: x=%.2f, y=%.2f, width=%.2f, height=%.2f, zoom=%d\n"),
		lfX, lfY, lfWidth, lfHeight, nZoomFactor);
}

void CControlZoomDlg::OnBnClickedButtonGetZoomLevel()
{
	GET_XNS_PARAM()
	UpdateData(TRUE);
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Controls the digital zoom. 
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsWindowLive->ZoomLevel(m_nX, m_nY, m_nLevel);
	WLOGW(_T("ZoomLevel():: x=%d, y=%d, level=%d, ret=%d(%s)\n"), 
		m_nX, m_nY, m_nLevel, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));

}

void CControlZoomDlg::OnBnClickedButtonGetZoomRate()
{
	GET_XNS_PARAM()
	UpdateData(TRUE);
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Controls the digital zoom. 
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsWindowLive->ZoomRate(m_fX, m_fY, m_fWidth, m_fHeight);
	WLOGW(_T("ZoomRate():: x=%.2f, y=%.2f, width=%.2f, height=%.2f, ret=%d(%s)\n"),
		m_fX, m_fY, m_fWidth, m_fHeight, 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CControlZoomDlg::OnBnClickedButtonGetZoomClear()
{
	GET_XNS_PARAM()
	UpdateData(TRUE);
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Controls the digital zoom. 
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsWindowLive->ZoomLevel(m_nX, m_nY, m_nLevel);
	WLOGW(_T("ZoomLevel():: x=%d, y=%d, level=%d, ret=%d(%s)\n"), 
		m_nX, m_nY, m_nLevel, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CControlZoomDlg::OnBnClickedButtonImportConfig()
{
	GET_XNS_PARAM();
	CString strConfig = _T("C:\\SdkTestConfig.dat");
	
	long nRet = m_pCtrlXnsDevice->ImportConfig(m_hDevice, strConfig, TRUE);
	WLOGD(_T("ImportConfig():: file=%s, ret=%d(%s)\n"), 
		strConfig, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CControlZoomDlg::OnBnClickedButtonExportConfig()
{
	GET_XNS_PARAM();
	CString strConfig = _T("C:\\SdkTestConfig.dat");

	long nRet = m_pCtrlXnsDevice->ExportConfig(m_hDevice, strConfig);
	WLOGD(_T("ExportConfig():: file=%s, ret=%d(%s)\n"), 
		strConfig, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CControlZoomDlg::OnBnClickedButtonUpdate()
{
	GET_XNS_PARAM();
	CFileDialog fdlg(TRUE);
	INT_PTR nResult = fdlg.DoModal();
	if(nResult == IDOK)
	{
		CString strFile = fdlg.GetPathName();
		long nRet = m_pCtrlXnsDevice->UploadSoftware(m_hDevice, strFile);
		WLOGD(_T("UploadSoftware():: file=%s, ret=%d(%s)\n"),
			strFile, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
	}
}
