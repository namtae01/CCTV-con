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

#include "CDXnsSdkDevice.h"
#include "afxcmn.h"
#include "afxwin.h"

// PresetDlg dialog

class PresetDlg : public CDialog
{
	DECLARE_DYNAMIC(PresetDlg)

public:
	PresetDlg(CWnd* pParent = NULL);   // standard constructor
	PresetDlg(
		CDXnsSdkDevice * pDevice, 
		long hDevice, 
		long controlId, 
		CMap< int, int, CString, CString >* pMap, 
		CWnd* pParent = NULL);
	virtual ~PresetDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PRESET };
	enum { PRESET_NUM = 20 };

private:
	CDXnsSdkDevice*		m_pCtrlXnsDevice;	// XnsDevice control
	long				m_hDevice;			// Device handle
	long				m_nControlId;		// Control ID

	CMap< int, int, CString, CString > * m_pPresetList;
	CListCtrl			m_ctrlPresetList;
	CString				m_strPresetName;
	CComboBox			m_ctrlPresetCombo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickListPreset(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboPresetIndex();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedDeleteAll();
	afx_msg void OnNMDblclkListPreset(NMHDR *pNMHDR, LRESULT *pResult);
};
