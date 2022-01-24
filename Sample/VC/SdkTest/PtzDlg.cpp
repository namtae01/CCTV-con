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
// PtzDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTest.h"
#include "PtzDlg.h"

#include "SdkTestDlg.h"


// CPtzDlg dialog

IMPLEMENT_DYNAMIC(CPtzDlg, CDialog)

CPtzDlg::CPtzDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPtzDlg::IDD, pParent)
	, m_nPan(0)
	, m_nTilt(0)
	, m_nZoom(0)
	, m_nFreeX(0)
	, m_nFreeY(0)
	, m_nPtzSpeed(50)
	, m_bMenuControl(0)
	, m_bAreaZoom(0)
	, m_bOsd(TRUE)
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
		m_pBAreaZoom = &(ptr->m_bAreaZoom);
	}
}

CPtzDlg::~CPtzDlg()
{
}

void CPtzDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_AUTOSCAN, m_ctrlScan);
	DDX_Control(pDX, IDC_COMBO_AUTOPAN, m_ctrlAutoPan);
	DDX_Control(pDX, IDC_COMBO_PATTERN, m_ctrlPattern);
	DDX_Text(pDX, IDC_EDIT_PAN, m_nPan);
	DDX_Text(pDX, IDC_EDIT_TILT, m_nTilt);
	DDX_Text(pDX, IDC_EDIT_ZOOM, m_nZoom);
	DDX_Text(pDX, IDC_EDIT_FREE_MOVE_X, m_nFreeX);
	DDX_Text(pDX, IDC_EDIT_FREE_MOVE_Y, m_nFreeY);
	DDX_Slider(pDX, IDC_SLIDER_PTZ_SPEED, m_nPtzSpeed);
	DDV_MinMaxInt(pDX, m_nPtzSpeed, 1, 100);
	DDX_Check(pDX, IDC_CHECK_OSD_ON, m_bOsd);
}


BOOL CPtzDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	GetDlgItem(IDC_BUTTON_UP)->SetWindowTextW(_T("¡è"));
	GetDlgItem(IDC_BUTTON_UPRIGHT)->SetWindowTextW(_T("¢Ö"));
	GetDlgItem(IDC_BUTTON_UPLEFT)->SetWindowTextW(_T("¢Ø"));
	GetDlgItem(IDC_BUTTON_DOWN)->SetWindowTextW(_T("¡é"));
	GetDlgItem(IDC_BUTTON_DOWNRIGHT)->SetWindowTextW(_T("¢Ù"));
	GetDlgItem(IDC_BUTTON_DOWNLEFT)->SetWindowTextW(_T("¢×"));
	GetDlgItem(IDC_BUTTON_LEFT)->SetWindowTextW(_T("¡ç"));
	GetDlgItem(IDC_BUTTON_RIGHT)->SetWindowTextW(_T("¡æ"));

	// Scan combo list
	m_ctrlScan.AddString(_T("None"));
	for(int i=0;i<6;i++)
	{
		CString strIndex;
		strIndex.Format(_T("Scan [%d]"), i+1);
		m_ctrlScan.AddString(strIndex);
	}
	m_ctrlScan.SetCurSel(0);

	// auto pan combo list
	m_ctrlAutoPan.AddString(_T("None"));
	for(int i=0;i<4;i++)
	{
		CString strIndex;
		strIndex.Format(_T("Auto pan[%d]"), i+1);
		m_ctrlAutoPan.AddString(strIndex);
	}
	m_ctrlAutoPan.SetCurSel(0);

	// pattern combo list
	m_ctrlPattern.AddString(_T("None"));
	for(int i=0;i<4;i++)
	{
		CString strIndex;
		strIndex.Format(_T("Pattern[%d]"), i+1);
		m_ctrlPattern.AddString(strIndex);
	}
	m_ctrlPattern.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CPtzDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_MENU_ON, &CPtzDlg::OnBnClickedCheckMenuOn)
	ON_BN_CLICKED(IDC_BUTTON_MENU_UP, &CPtzDlg::OnBnClickedButtonMenuUp)
	ON_BN_CLICKED(IDC_BUTTON_MENU_DOWN, &CPtzDlg::OnBnClickedButtonMenuDown)
	ON_BN_CLICKED(IDC_BUTTON_MENU_LEFT, &CPtzDlg::OnBnClickedButtonMenuLeft)
	ON_BN_CLICKED(IDC_BUTTON_MENU_RIGHT, &CPtzDlg::OnBnClickedButtonMenuRight)
	ON_BN_CLICKED(IDC_BUTTON_MENU_ENTER, &CPtzDlg::OnBnClickedButtonMenuEnter)
	ON_BN_CLICKED(IDC_BUTTON_MENU_CANCEL, &CPtzDlg::OnBnClickedButtonMenuCancel)
	ON_BN_CLICKED(IDC_BUTTON_FREE_MOVE, &CPtzDlg::OnBnClickedButtonFreeMove)
	ON_BN_CLICKED(IDC_CHECK_AREAZOOM, &CPtzDlg::OnBnClickedCheckAreazoom)
	ON_BN_CLICKED(IDC_BUTTON_PRESET, &CPtzDlg::OnBnClickedButtonPreset)
	ON_BN_CLICKED(IDC_BUTTON_GET_PTZ, &CPtzDlg::OnBnClickedButtonGetPtz)
	ON_BN_CLICKED(IDC_BUTTON_SET_PTZ, &CPtzDlg::OnBnClickedButtonSetPtz)
	ON_BN_CLICKED(IDC_BUTTON_ZOOM_1X, &CPtzDlg::OnBnClickedButtonZoom1x)
	ON_CBN_SELCHANGE(IDC_COMBO_AUTOSCAN, &CPtzDlg::OnCbnSelchangeComboAutoscan)
	ON_CBN_SELCHANGE(IDC_COMBO_AUTOPAN, &CPtzDlg::OnCbnSelchangeComboAutopan)
	ON_CBN_SELCHANGE(IDC_COMBO_PATTERN, &CPtzDlg::OnCbnSelchangeComboPattern)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CPtzDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_UPLEFT, &CPtzDlg::OnBnClickedButtonUpleft)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CPtzDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLEFT, &CPtzDlg::OnBnClickedButtonDownleft)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CPtzDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_DOWNRIGHT, &CPtzDlg::OnBnClickedButtonDownright)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CPtzDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_UPRIGHT, &CPtzDlg::OnBnClickedButtonUpright)
	ON_BN_CLICKED(IDC_BUTTON_ZOOM_IN, &CPtzDlg::OnBnClickedButtonZoomIn)
	ON_BN_CLICKED(IDC_BUTTON_ZOOM_OUT, &CPtzDlg::OnBnClickedButtonZoomOut)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CPtzDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_CHECK_OSD_ON, &CPtzDlg::OnBnClickedCheckOsdOn)
END_MESSAGE_MAP()


// CPtzDlg message handlers

void CPtzDlg::OnBnClickedCheckMenuOn()
{
	GET_XNS_PARAM()

	m_bMenuControl = !m_bMenuControl;

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns the capabilities of the control module.
	// -----------------------------------------------------------------------
	long bCap = m_pCtrlXnsDevice->GetControlCapability(
		m_hDevice,				// Device handle
		m_nControlId,			// Control ID
		XCTL_CAP_CAM_MENU		// Capability ID
		);
	WLOGD(_T("GetControlCapability:: XCTL_CAP_CAM_MENU: controlID=%d, bcap=%d\n"),
		m_nControlId, bCap);


	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Controls the OSD menus of the camera. This function is valid as long 
	// as the application is receiving media stream from the camera.(ex.SND-5080)
	// -----------------------------------------------------------------------
	//  Command			Value	Description
	// -----------------------------------------------------------------------
	//	XMENU_UP		1		Menu up.
	//	XMENU_DOWN		2		Menu down.
	//	XMENU_LEFT		3		Menu left or prev menu.
	//	XMENU_RIGHT		4		Menu right or next menu.
	//	XMENU_ENTER		5		Menu enter, select.
	//	XMENU_ON		6		Menu on.
	//	XMENU_OFF		7		Menu off.
	//	XMENU_CANCEL	8		Cancel (Changes are not saved).
	// -----------------------------------------------------------------------
	int nRet = m_pCtrlXnsDevice->ControlMenu(
		m_hDevice,
		m_nControlId,
		(m_bMenuControl?XMENU_ON:XMENU_OFF)
		);
	WLOGD(_T("ControlMenu():: opt=%s, ret=[%d](%s)\n"), 
		(m_bMenuControl?_T("XMENU_ON"):_T("XMENU_OFF")),
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CPtzDlg::OnBnClickedButtonMenuUp()
{
	GET_XNS_PARAM()
	
	int nRet = m_pCtrlXnsDevice->ControlMenu(
		m_hDevice,
		m_nControlId,
		XMENU_UP
		);
	WLOGD(_T("ControlMenu():: opt=XMENU_UP, ret=[%d](%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CPtzDlg::OnBnClickedButtonMenuDown()
{
	GET_XNS_PARAM()

	int nRet = m_pCtrlXnsDevice->ControlMenu(
		m_hDevice,
		m_nControlId,
		XMENU_DOWN
		);
	WLOGD(_T("ControlMenu():: opt=XMENU_DOWN, ret=[%d](%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CPtzDlg::OnBnClickedButtonMenuLeft()
{
	GET_XNS_PARAM()

	int nRet = m_pCtrlXnsDevice->ControlMenu(
		m_hDevice,
		m_nControlId,
		XMENU_LEFT
		);
	WLOGD(_T("ControlMenu():: opt=XMENU_LEFT, ret=[%d](%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CPtzDlg::OnBnClickedButtonMenuRight()
{
	GET_XNS_PARAM()

	int nRet = m_pCtrlXnsDevice->ControlMenu(
		m_hDevice,
		m_nControlId,
		XMENU_RIGHT
		);
	WLOGD(_T("ControlMenu():: opt=XMENU_RIGHT, ret=[%d](%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CPtzDlg::OnBnClickedButtonMenuEnter()
{
	GET_XNS_PARAM()

	int nRet = m_pCtrlXnsDevice->ControlMenu(
		m_hDevice,
		m_nControlId,
		XMENU_ENTER
		);
	WLOGD(_T("ControlMenu():: opt=XMENU_ENTER, ret=[%d](%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CPtzDlg::OnBnClickedButtonMenuCancel()
{
	GET_XNS_PARAM()

	int nRet = m_pCtrlXnsDevice->ControlMenu(
		m_hDevice,
		m_nControlId,
		XMENU_CANCEL
		);
	WLOGD(_T("ControlMenu():: opt=XMENU_CANCEL, ret=[%d](%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CPtzDlg::OnBnClickedButtonFreeMove()
{
	GET_XNS_PARAM()

	UpdateData(TRUE);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Moves the camera to any PTZ position. This function is valid as long 
	// as the application is receiving media stream from the camera. 
	// -----------------------------------------------------------------------
	int nRet = m_pCtrlXnsDevice->ControlPtzFreeMove(
		m_hDevice, 
		m_nControlId, 
		m_nFreeX, 
		m_nFreeY
		);

	WLOGD(_T("ControlPtzFreeMove():: x=%d, y=%d, ret=%d(%s)\n"),
		m_nFreeX, m_nFreeY, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CPtzDlg::OnBnClickedCheckAreazoom()
{
	GET_XNS_PARAM()

	m_bAreaZoom = !m_bAreaZoom;
	WLOGD(_T("Area Zoom flag = %d\n"), m_bAreaZoom);
	*m_pBAreaZoom = m_bAreaZoom;
}

void CPtzDlg::OnBnClickedButtonPreset()
{
	GET_XNS_PARAM()
	
	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Gets the preset list. A preset is a user-defined position of the camera. 
	// The number of presets available varies depending on the model. 
	// However, the XNS ActiveX library can support up to 20 presets. 
	// The result of this function will be forwarded by the OnGetPresetList 
	// event. This function is valid as long as the application is receiving 
	// media stream from the camera.
	// -----------------------------------------------------------------------
	int nRet = m_pCtrlXnsDevice->GetPresetList(m_hDevice, m_nControlId);
	if(nRet != ERR_SUCCESS)
	{
		WLOGD(_T("GetPresetList() fail. ret=[%d](%s)\n"), 
			nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
		return;
	}
}

void CPtzDlg::OnBnClickedButtonGetPtz()
{
	GET_XNS_PARAM();

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Returns an absolute coordinate of the camera, is available when 
	// application receives media stream from the camera. 
	// The value themselves could be read by using OnGetPtzPos event handler. 
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->GetPtzPos(m_hDevice, m_nControlId);
	WLOGD(_T("GetPtzPos():: ret = %d(%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CPtzDlg::OnBnClickedButtonSetPtz()
{
	GET_XNS_PARAM()

	UpdateData(true);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Change the absolute coordinate of the camera, 
	// is available when application receives media stream from the camera.
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->SetPtzPos(
		m_hDevice, 
		m_nControlId, 
		m_nPan, 
		m_nTilt, 
		m_nZoom
		);

	WLOGD(_T("SetPtzPos():: ret = %d(%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CPtzDlg::OnBnClickedButtonZoom1x()
{
	GET_XNS_PARAM()

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Performs the zoom-1x. This function is valid as long as the application 
	// is receiving media stream from the camera.
	// Parameters
	// - hDevice
	//   [in] Device handle. This value is returned from CreateDevice().
	// - nControlID
	//	 [in] Control ID.
	// -----------------------------------------------------------------------
	long nRet = m_pCtrlXnsDevice->Zoom1X(m_hDevice, m_nControlId);
	WLOGD(_T("Zoom1X():: ret = %d(%s)\n"), 
		nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}




void CPtzDlg::moveCamera(const int nCommand)
{
	GET_XNS_PARAM()

	long ret;
	UpdateData(TRUE);

	if( nCommand != XPTZ_STOP)
	{
		ret = m_pCtrlXnsDevice->ControlPtz(m_hDevice, m_nControlId, XPTZ_STOP, 30);
		{
			WLOGD(_T("ControlPtz():: XPTZ_STOP: ret=%d(%s)\n"), 
				ret, m_pCtrlXnsDevice->GetErrorString(ret));
		}
	}

	// Returns the capabilities of the control module.
	long bIsCap = m_pCtrlXnsDevice->GetControlCapability(m_hDevice, m_nControlId, XCTL_CAP_PTZ_SPEED);
	WLOGD(_T("GetControlCapability():: XCTL_CAP_PTZ_SPEED: ret=%d\n"), bIsCap);

	// [ XNS ACTIVEX HELP ]
	// -----------------------------------------------------------------------
	// Moves the camera to the predefined PTZ position. This function is 
	// valid as long as the application is receiving media stream from the 
	// camera. 
	// -----------------------------------------------------------------------
	//	Command			Value	Description
	// -----------------------------------------------------------------------
	//	XPTZ_UP			1		Tilt up
	//	XPTZ_DOWN		2		Tilt down
	//	XPTZ_LEFT		3		Pan left
	//	XPTZ_RIGHT		4		Pan right
	//	XPTZ_UPLEFT		5		Tilt up and pan left
	//	XPTZ_UPRIGHT	6		Tilt up and pan right
	//	XPTZ_DOWNLEFT	7		Tilt down and pan left
	//	XPTZ_DOWNRIGHT	8		Tilt down and pan right
	//	XPTZ_ZOOMIN		9		Zoom in
	//	XPTZ_ZOOMOUT	10		Zoom out
	//	XPTZ_STOP		11		Stop the PTZ moving
	//	XPTZ_FOCUS_NEAR	12		Focus near
	//	XPTZ_FOCUS_FAR	13		Focus far
	//	XPTZ_FOCUS_STOP	14		Stop focus moving
	//	XPTZ_IRIS_OPEN	15		Open iris
	//	XPTZ_IRIS_CLOSE	16		Close iris
	// -----------------------------------------------------------------------
	if (bIsCap)
	{
		ret = m_pCtrlXnsDevice->ControlPtz(
			m_hDevice,		// [in] Device handle. This value is returned from CreateDevice().
			m_nControlId,	// [in] Control ID.
			nCommand,		// [in] PTZ command 
			m_nPtzSpeed		// [in] If nPtzCommand is a speed-related command, 
							// this value indicates the PTZ operation speed. 
							// (1~100) This value is valid only if the camera 
							// supports the XCTL_CAP_PTZ_SPEED capability.
			);
		WLOGD(_T("ControlPtz():: controlID=%d, command=%d, speed=%d, ret=%d(%s)\n"), 
			ret, m_nControlId, nCommand, m_nPtzSpeed, m_pCtrlXnsDevice->GetErrorString(ret));
	}
	else
	{
		ret = m_pCtrlXnsDevice->ControlPtz(m_hDevice, m_nControlId, nCommand, 30);
		WLOGD(_T("ControlPtz():: controlID=%d, command=%d, speed=%d, ret=%d(%s)\n"), 
			ret, m_nControlId, nCommand, 30, m_pCtrlXnsDevice->GetErrorString(ret));
	}

}

void CPtzDlg::OnCbnSelchangeComboAutoscan()
{
	GET_XNS_PARAM()

	int nIndex = m_ctrlScan.GetCurSel();
	if (nIndex == 0)
	{
		// stop action
		moveCamera(XPTZ_UP);
		return;
	}


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
		XHPTZ_SCAN,
		nIndex
		);

	WLOGD(_T("ExecuteHPtz():: XHPTZ_SCAN: nIndex=%d, ret=%d(%s)\n"),
		nIndex, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));

}

void CPtzDlg::OnCbnSelchangeComboAutopan()
{
	GET_XNS_PARAM()

	int nIndex = m_ctrlAutoPan.GetCurSel();
	if (nIndex == 0)
	{
		// stop action
		moveCamera(XPTZ_UP);
		return;
	}

	long nRet = m_pCtrlXnsDevice->ExecuteHPtz(
		m_hDevice,
		m_nControlId,
		XHPTZ_AUTOPAN,
		nIndex
		);

	WLOGD(_T("ExecuteHPtz():: XHPTZ_AUTOPAN: nIndex=%d, ret=%d(%s)\n"),
		nIndex, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
}

void CPtzDlg::OnCbnSelchangeComboPattern()
{
	GET_XNS_PARAM()

	int nIndex = m_ctrlPattern.GetCurSel();
	if (nIndex == 0)
	{
		// stop action
		moveCamera(XPTZ_UP);
		return;
	}

	long nRet = m_pCtrlXnsDevice->ExecuteHPtz(
		m_hDevice,
		m_nControlId,
		XHPTZ_PATTERN,
		nIndex
		);

	WLOGD(_T("ExecuteHPtz():: XHPTZ_PATTERN: nIndex=%d, ret=%d(%s)\n"),
		nIndex, nRet, m_pCtrlXnsDevice->GetErrorString(nRet));
	
}

void CPtzDlg::OnBnClickedButtonUp()
{
	moveCamera(XPTZ_UP);
}

void CPtzDlg::OnBnClickedButtonUpleft()
{
	moveCamera(XPTZ_UPLEFT);
}

void CPtzDlg::OnBnClickedButtonLeft()
{
	moveCamera(XPTZ_LEFT);
}

void CPtzDlg::OnBnClickedButtonDownleft()
{
	moveCamera(XPTZ_DOWNLEFT);
}

void CPtzDlg::OnBnClickedButtonDown()
{
	moveCamera(XPTZ_DOWN);
}

void CPtzDlg::OnBnClickedButtonDownright()
{
	moveCamera(XPTZ_DOWNRIGHT);
}

void CPtzDlg::OnBnClickedButtonRight()
{
	moveCamera(XPTZ_RIGHT);
}

void CPtzDlg::OnBnClickedButtonUpright()
{
	moveCamera(XPTZ_UPRIGHT);
}

void CPtzDlg::OnBnClickedButtonZoomIn()
{
	moveCamera(XPTZ_ZOOMIN);
}

void CPtzDlg::OnBnClickedButtonZoomOut()
{
	moveCamera(XPTZ_ZOOMOUT);
}

void CPtzDlg::OnBnClickedButtonStop()
{
	moveCamera(XPTZ_STOP);
}

void CPtzDlg::OnBnClickedCheckOsdOn()
{
	GET_XNS_PARAM()
	UpdateData(true);
	m_pCtrlXnsWindowLive->SetOSDOnOff(OSD_ALL, m_bOsd);
	WLOGW(_T("SetOSDOnOff():: OSD_ALL: FLAG=%d\n"), m_bOsd);
}
