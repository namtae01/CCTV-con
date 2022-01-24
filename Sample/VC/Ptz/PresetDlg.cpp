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
// PresetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ptz.h"
#include "PresetDlg.h"

// [ XNS ACTIVEX HELP ]
// -----------------------------------------------------------------------
// This files are installed in {$SDK path}\sample_code\include 
// You should include this files
// -----------------------------------------------------------------------
#include "XnsCommon.h"
#include "XnsDeviceInterface.h"


#ifndef DBG_LOG
// Macro for OutputDebugString()
#define DBG_LOG(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("(%S:%d)"), __FUNCTION__, __LINE__);	\
	strMessage.AppendFormat(__VA_ARGS__);\
	OutputDebugString(strMessage);\
}while(0);
#endif

// PresetDlg dialog

IMPLEMENT_DYNAMIC(PresetDlg, CDialog)

PresetDlg::PresetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PresetDlg::IDD, pParent)
	, m_pCtrlXnsDevice(0)
	, m_hDevice(0)
	, m_nControlId(0)
	, m_pPresetList(0)
	, m_strPresetName(_T(""))
{
}

PresetDlg::PresetDlg(
		  CDXnsSdkDevice * pDevice, 
		  long hDevice, 
		  long controlId, 
		  CMap< int, int, CString, CString >* pMap, 
		  CWnd* pParent/* = NULL*/)
	: CDialog(PresetDlg::IDD, pParent)
	, m_pCtrlXnsDevice(pDevice)
	, m_hDevice(hDevice)
	, m_nControlId(controlId)
	, m_pPresetList(pMap)
{
}

PresetDlg::~PresetDlg()
{
}

void PresetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PRESET, m_ctrlPresetList);
	DDX_Control(pDX, IDC_COMBO_PRESET_INDEX, m_ctrlPresetCombo);
	DDX_Text(pDX, IDC_EDIT_PRESET_NAME, m_strPresetName);
}


BEGIN_MESSAGE_MAP(PresetDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PRESET, &PresetDlg::OnNMClickListPreset)
	ON_CBN_SELCHANGE(IDC_COMBO_PRESET_INDEX, &PresetDlg::OnCbnSelchangeComboPresetIndex)
	ON_BN_CLICKED(ID_SAVE, &PresetDlg::OnBnClickedSave)
	ON_BN_CLICKED(ID_DELETE, &PresetDlg::OnBnClickedDelete)
	ON_BN_CLICKED(ID_DELETE_ALL, &PresetDlg::OnBnClickedDeleteAll)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PRESET, &PresetDlg::OnNMDblclkListPreset)
END_MESSAGE_MAP()


// PresetDlg message handlers

BOOL PresetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here


	m_ctrlPresetList.InsertColumn(0, _T("No"), LVCFMT_LEFT, 100);
	m_ctrlPresetList.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 180);
	m_ctrlPresetList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_ctrlPresetList.SetExtendedStyle( LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	

	m_ctrlPresetList.SetItemCount(PRESET_NUM);
	if(m_pPresetList!=NULL) 
	{
		int j=0;
		for(int i=1;i<=PRESET_NUM;i++)
		{
			CString strName;
			CString strIndex;
			strIndex.Format(_T("%d"), i);
			m_ctrlPresetCombo.InsertString(i-1, strIndex);
			if(m_pPresetList->Lookup(i,strName)==TRUE)
			{
				m_ctrlPresetList.InsertItem(j, strIndex);
				m_ctrlPresetList.SetItemText(j, 1, strName);	
				j++;
			}
		}	
	}
	m_ctrlPresetCombo.SetCurSel(0);
	OnCbnSelchangeComboPresetIndex();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void PresetDlg::OnNMClickListPreset(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE *>(pNMHDR);
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CString strIndex = m_ctrlPresetList.GetItemText(pNMListView->iItem, 0);
	m_strPresetName = m_ctrlPresetList.GetItemText(pNMListView->iItem, 1);
	m_ctrlPresetCombo.SelectString(0, strIndex);
	UpdateData(false);
	*pResult = 0;
}

void PresetDlg::OnCbnSelchangeComboPresetIndex()
{
	// TODO: Add your control notification handler code here
	if(m_pPresetList == NULL)
	{
		return;
	}
	int nIndex = m_ctrlPresetCombo.GetCurSel();
	CString strIndex;
	m_ctrlPresetCombo.GetLBText(nIndex, strIndex);
	nIndex = _ttoi(strIndex);

	m_strPresetName = "";
	m_pPresetList->Lookup(nIndex, m_strPresetName);
	UpdateData(FALSE);
}

void PresetDlg::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int nIndex = m_ctrlPresetCombo.GetCurSel();
	CString strIndex;
	m_ctrlPresetCombo.GetLBText(nIndex, strIndex);
	nIndex = _ttoi(strIndex);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Sets the current camera position to a preset. The position will be 
	// saved in the camera. This function is valid as long as the application 
	// is receiving media stream from the camera. 
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->SetPreset(
		m_hDevice,			// [in] Device handle. 
		m_nControlId,		// [in] Control ID.
		nIndex,				// [in] Preset number to save (start with 1).
		m_strPresetName		// [in] Preset name. The camera will save the name 
							//      including the preset position (English only).
		);
	if(nRet != ERR_SUCCESS)
	{
		DBG_LOG(_T("SetPreset() fail: ret=[%d](%s)\n"), 
			nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
		return;
	}


	m_pPresetList->SetAt(nIndex, m_strPresetName);

	LVFINDINFO info;
	info.flags = LVFI_STRING;
	info.psz = strIndex;
	if((nIndex=m_ctrlPresetList.FindItem(&info)) != -1 )
	{
		m_ctrlPresetList.SetItemText(nIndex, 1, m_strPresetName);
	}
	else
	{
		nIndex = m_pPresetList->GetCount();
		m_ctrlPresetList.InsertItem(nIndex-1, strIndex);
		m_ctrlPresetList.SetItemText(nIndex-1, 1, m_strPresetName);
	}

}

void PresetDlg::OnBnClickedDelete()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	long nIndex = m_ctrlPresetCombo.GetCurSel()+1;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Deletes a defined preset. This function is valid as long as the 
	// application is receiving media stream from the camera.
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->DeletePreset(
		m_hDevice,			// [in] Device handle. 
		m_nControlId,		// [in] Control ID.
		nIndex				// [in] Preset number to save (start with 0).
		);
	if(nRet != ERR_SUCCESS)
	{
		DBG_LOG(_T("DeletePreset() fail: ret=[%d](%s)\n"), 
			nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
		return;
	}

	m_pPresetList->RemoveKey(nIndex);
	CString strIndex;
	strIndex.Format(_T("%d"), nIndex);

	LVFINDINFO info;
	info.flags = LVFI_STRING;
	info.psz = strIndex;
	if((nIndex=m_ctrlPresetList.FindItem(&info)) != -1 )
	{
		m_ctrlPresetList.DeleteItem(nIndex);
	}
}

void PresetDlg::OnBnClickedDeleteAll()
{
	// TODO: Add your control notification handler code here

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Deletes all presets. This function is valid as long as 
	// the application is receiving media stream from the camera.
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->DeletePresetAll(
		m_hDevice,			// [in] Device handle. 
		m_nControlId		// [in] Control ID.
		);
	if(nRet != ERR_SUCCESS)
	{
		DBG_LOG(_T("DeletePresetAll() fail: ret=[%d](%s)\n"), 
			nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
		return;
	}

	m_pPresetList->RemoveAll();
	m_ctrlPresetList.DeleteAllItems();
}


void PresetDlg::OnNMDblclkListPreset(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CString strIndex = m_ctrlPresetList.GetItemText(pNMListView->iItem, 0);
	m_strPresetName = m_ctrlPresetList.GetItemText(pNMListView->iItem, 1);
	m_ctrlPresetCombo.SelectString(0, strIndex);


	int nIndex = _ttoi(strIndex);
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Performs operations of Preset, Autopan, Scan and Pattern. 
	// This function is valid as long as the application is receiving 
	// media stream from the camera.
	// 
	// Parameters
	// - hDevice
	//	 [in] Device handle. This value is returned from CreateDevice().
	//	nControlID
	//	 [in] Control ID.
	// - nType
	//	 [in] Camera operations.
	//	 * XHPTZ_PRESET(1): Preset
	//	 * XHPTZ_AUTOPAN(2): Autopan(Swing)
	//	 * XHPTZ_SCAN(3): Scan
	//	 * XHPTZ_PATTERN(4): Pattern
	// - nNumber
	//	 [in] Index of camera's list of features (Preset, AutoPan, Scan, Pattern). 
	//        (start with 1) For instance, if multiple presets are defined, 
	//        a list of presets will be created and the user should specify 
	//        the index of the list.
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->ExecuteHPtz(
		m_hDevice,
		m_nControlId,
		XHPTZ_PRESET,
		nIndex
		);
	if(nRet != ERR_SUCCESS)
	{
		DBG_LOG(_T("ExecuteHPtz() failed: ret=[%d](%s)\n"),
			nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
	}

	*pResult = 0;
}
