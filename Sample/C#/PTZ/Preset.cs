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
// @ File Name :		Preset.cs
// @ File Description : Preset Form Source Code File. 
//						Define the entire function.
///////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

// Define XNS Control.
using AxXNSSDKDEVICELib;

namespace PTZ
{
    public partial class Preset : Form
    {
        // Parent Class
        public PTZDlg parentDlg;

        // ActiveX Device Control 
        public AxXnsSdkDevice axXnsSdkDevice = null;
        
        // Device Handler
        public  int hDevice    = 0;
        public  int nControlID = 0;
        private int nError     = 0;

        private const int PRESET_NUM = 20;

        public Preset(PTZDlg parentForm, AxXnsSdkDevice axXnsSdkDevice_parent, List<PTZDlg.PresetInfo> list)
        {
            InitializeComponent();

            parentDlg = parentForm;
            axXnsSdkDevice = axXnsSdkDevice_parent;
            hDevice = parentDlg.hDevice;
            nControlID = parentDlg.nControlID;

            OnSetDialog(list);
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ User-Defined Functions.
        // for Dialog Control initialize function.
        // -----------------------------------------------------------------------
        public void OnSetDialog(List<PTZDlg.PresetInfo> list)
        {
            LISTVIEW.View = View.Details;
            LISTVIEW.Columns.Add("No.",50, HorizontalAlignment.Center);
            LISTVIEW.Columns.Add("Name.", 260, HorizontalAlignment.Center);

            if (parentDlg.listPreset.Count == 0)
            {
                return;
            }            
            
            for (int i = 0; i < parentDlg.listPreset.Count; i++)
            {                
                // Display ListView 
                ListViewItem listview = new ListViewItem(list[i].nIndex.ToString());
                listview.SubItems.Add(list[i].strName);
                LISTVIEW.Items.Add(listview);
            }           

            COMBO_INDEX.SelectedIndex = 0;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Save Prest Function.
        // ----------------------------------------------------------------------- 
        private void BTN_SAVE_Click(object sender, EventArgs e)
        {
            int nIndex = COMBO_INDEX.SelectedIndex;
            string strPreset = EIDT_PRESET_NAME.Text;

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Sets the current camera position to a preset. The position will be 
            // saved in the camera. This function is valid as long as the application 
            // is receiving media stream from the camera. 
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.SetPreset(
                hDevice,          			// [in] Device handle. 
                nControlID,		            // [in] Control ID.
                nIndex,				        // [in] Preset number to save (start with 1).
                strPreset);		            // [in] Preset name. The camera will save the name including the preset position (English only).

            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                parentDlg.m_DebugLog.WLOGD("SetPreset() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }

            // TEST
            PTZDlg.PresetInfo preset = new PTZDlg.PresetInfo();
            preset.nIndex = nIndex;
            preset.strName = strPreset;
            parentDlg.listPreset.Add(preset);


            // Display ListView 
            ListViewItem list = new ListViewItem(nIndex.ToString());
            list.SubItems.Add(strPreset);
            LISTVIEW.Items.Add(list);            

            parentDlg.m_DebugLog.ERROR_BOX("Index : " + parentDlg.listPreset[0].nIndex.ToString() + " / " + "Name : " + parentDlg.listPreset[0].strName);

            {
                COMBO_INDEX.SelectedIndex = 0;
                EIDT_PRESET_NAME.Text = "";
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Delete All Prest Function.
        // ----------------------------------------------------------------------- 
        private void BTN_DELETEALL_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Deletes all presets. This function is valid as long as 
            // the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.DeletePresetAll(
                hDevice,			        // [in] Device handle. 
                nControlID);		        // [in] Control ID.

            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                parentDlg.m_DebugLog.WLOGD("DeletePresetAll() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }

            int nItemCnt = LISTVIEW.Items.Count;

            for (int i = nItemCnt-1; i >= 0;i--)
             {
                 LISTVIEW.Items.RemoveAt(i);
             }           
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Delete Prest Function.
        // ----------------------------------------------------------------------- 
        private void BTN_DELETE_Click(object sender, EventArgs e)
        {
            int nIndex = COMBO_INDEX.SelectedIndex;
            int nItemCnt = LISTVIEW.Items.Count;

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Deletes a defined preset. This function is valid as long as the 
            // application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.DeletePreset(
                hDevice,		        	// [in] Device handle. 
                nControlID,   		        // [in] Control ID.
                nIndex);				    // [in] Preset number to save (start with 0).

            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                parentDlg.m_DebugLog.WLOGD("DeletePreset() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }

            // ListVoew Setting.
            string a = COMBO_INDEX.SelectedIndex.ToString();
            string b = null;

            for (int i = 0; i < nItemCnt; i++)
            {
                b = LISTVIEW.Items[i].SubItems[0].Text;
                parentDlg.m_DebugLog.WLOGD(b + " / " + i.ToString());

                if (a == b)
                {
                    LISTVIEW.Items.RemoveAt(i);
                    break;
                }
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# ListView Control Event.
        // Select Preset
        // -----------------------------------------------------------------------
        private void LISTVIEW_DoubleClick(object sender, EventArgs e)
        {
            int nCount = LISTVIEW.FocusedItem.Index;
            string strIndex = LISTVIEW.FocusedItem.Text;
            int nIndex = Convert.ToInt16(strIndex);

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
            nError = axXnsSdkDevice.ExecuteHPtz(hDevice, nControlID, (int)XHPTZFunction.XHPTZ_PRESET, nIndex);

            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                parentDlg.m_DebugLog.WLOGD("ExecuteHPtz() failed::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
            }
        }
    }
}
