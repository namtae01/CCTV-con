///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011 by Samsung Techwin, Inc.
//
// This software is copyrighted by, and is the sole property of Samsung Techwin.
// All rigths, title, ownership, or other interests in the software remain the
// property of Samsung Techwin. This software may only be used in accordance with
// the corresponding license agreement. Any unauthorized use, duplication,
// transmission, distribution, or disclosure of this software is expressly
// forbidden.
//
// This Copyright notice may not be removed or modified without prior written
// consent of Samsung Techwin.
//
// Samsung Techwin reserves the right to modify this software without notice.
//
// Samsung Techwin, Inc.
// KOREA
// http://www.samsungtechwin.co.kr
///////////////////////////////////////////////////////////////////////////////////
// @ File Name :		BackupEx.cs
// @ File Description : BackupEx Form Source Code File. 
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

// ActiveX Device Control 
using AxXNSSDKDEVICELib;
// Define XNS Sample Log
using XNSSAMPLELOGLib;

namespace BackupEx
{
    public partial class BackupSearch : Form
    {
        // Parent Class
        public BackupExDlg parentDlg;

        // ActiveX Device Control 
        public AxXnsSdkDevice axXnsSdkDevice = null;

        // Device Handler
        public int hDevice      = 0;
        public int nControlID   = 0;
        public int nProgress    = 0;
        private int nError      = 0;
        private int tStart      = 0;
        private int tEnd        = 0;
        private bool bRecCheck  = true;
        public bool bBackup     = false;

        private const int TRUE  = 1;
        private const int FALSE = 0;
        private const int NULL  = 0;
        private const int SEC_WRITER = 1;
        private const int REC_WRITER = 2;
        private const int CTRLID_DVR = 2;
        private const int CTRLID_NET = 3;

        public BackupSearch(BackupExDlg parentForm, AxXnsSdkDevice axXnsSdkDevice_parent)
        {
            InitializeComponent();

            parentDlg       = parentForm;
            axXnsSdkDevice  = axXnsSdkDevice_parent;
            hDevice         = parentDlg.hDevice;
            nControlID      = parentDlg.nControlID;
            nProgress       = parentDlg.nProgress;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Backup start.
        // ----------------------------------------------------------------------- 
        private void BTN_START_Click(object sender, EventArgs e)
        {
            // Device Check.
            if (hDevice == NULL)
            {
                parentDlg.m_DebugLog.WLOGD("Device Hander was already created.");
                return;
            }

            bBackup = !bBackup;

            string strFilename = "c:\\BackupEx";
            int nRecChannel = ((int)SPIN_CH.Value - 1) + nControlID;

            // Date
            int nDateYear   = dateTimePicker_Date.Value.Year;
            int nDateMonth  = dateTimePicker_Date.Value.Month;
            int nDateDay    = dateTimePicker_Date.Value.Day;

            // Start Time
            int nStartHour  = dateTimePicker_StartTime.Value.Hour;
            int nStartMin   = dateTimePicker_StartTime.Value.Minute;
            int nStartSec   = dateTimePicker_StartTime.Value.Second;

            // End Time
            int nEndHour    = dateTimePicker_EndTime.Value.Hour;
            int nEndMin     = dateTimePicker_EndTime.Value.Minute;
            int nEndSec     = dateTimePicker_EndTime.Value.Second;

            parentDlg.m_DebugLog.WLOGD("Start Time : "+ nStartHour + ":" + nStartMin + ":" + nStartSec);
            parentDlg.m_DebugLog.WLOGD("End Time : " + nEndHour + ":" + nEndMin + ":" + nEndSec);

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Gets the video recording dates from a specific month. 
            // The result of this function can be obtaned from the OnSearchCalendar event.
            // Return Value : Converted values in time_t format.
            // -----------------------------------------------------------------------
            tStart = axXnsSdkDevice.DateToTimet(nDateYear, nDateMonth, nDateDay, nStartHour, nStartMin, nStartSec);
            tEnd   = axXnsSdkDevice.DateToTimet(nDateYear, nDateMonth, nDateDay, nEndHour, nEndMin, nEndSec);
           
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Convert from LocalTime to Device UTC
            // Return Value : UTC time_t value.
            // -----------------------------------------------------------------------
            // Change UTC Time.
            int tUTCstart = axXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, tStart);
            int tUTCend   = axXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, tEnd);

            // Backup Start.
            if (bBackup == true)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Returns the connection status of the device.
                // -----------------------------------------------------------------------
                if (axXnsSdkDevice.GetDeviceStatus(hDevice) == ((int)XConnect.XDEVICE_STATUS_CONNECTED))
                {
                    // [ XNS ACTIVEX HELP ]
                    // -----------------------------------------------------------------------
                    // Returns the type of control module corresponding to the control ID.
                    // Control Module : DVR Check
                    // -----------------------------------------------------------------------
                    if (axXnsSdkDevice.GetControlType(hDevice, 1) == ((int)XModelType.XCTL_DVR))
                    {
                        // [ XNS ACTIVEX HELP ]
                        // -----------------------------------------------------------------------
                        // Returns the capabilities of the control module.
                        // -----------------------------------------------------------------------
                        if ((axXnsSdkDevice.GetControlCapability(hDevice, nControlID, ((int)XUnitCap.XCTL_CAP_BACKUP)) != FALSE))
                        {
                            if (bRecCheck == true)
                            {
                                // [ XNS ACTIVEX HELP ]
                                // -----------------------------------------------------------------------
                                // Starts backup.
                                // Backup is to save the streaming data recorded in the device to the local PC.
                                // -----------------------------------------------------------------------	
                                nError = axXnsSdkDevice.StartBackup(hDevice, nRecChannel, strFilename, REC_WRITER, tUTCstart, tUTCend);
                                BTN_START.Text = "Stop";
                            }
                            else
                            {
                                nError = axXnsSdkDevice.StartBackup(hDevice, nRecChannel, strFilename, SEC_WRITER, tUTCstart, tUTCend);
                                BTN_START.Text = "Stop";
                            }
                        }
                    }
                }
            }
            // Backup Stop.
            else
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Returns the connection status of the device.
                // -----------------------------------------------------------------------
                if (axXnsSdkDevice.GetDeviceStatus(hDevice) == ((int)XConnect.XDEVICE_STATUS_CONNECTED))
                {
                    // [ XNS ACTIVEX HELP ]
                    // -----------------------------------------------------------------------
                    // Returns the type of control module corresponding to the control ID.
                    // Control Module : DVR Check
                    // -----------------------------------------------------------------------
                    if (axXnsSdkDevice.GetControlType(hDevice, 1) == ((int)XModelType.XCTL_DVR))
                    {
                        // [ XNS ACTIVEX HELP ]
                        // -----------------------------------------------------------------------
                        // Returns the capabilities of the control module.
                        // -----------------------------------------------------------------------
                        if ((axXnsSdkDevice.GetControlCapability(hDevice, nControlID, ((int)XUnitCap.XCTL_CAP_BACKUP)) != FALSE))
                        {
                            // [ XNS ACTIVEX HELP ]
                            // -----------------------------------------------------------------------
                            // Stops backup.
                            // -----------------------------------------------------------------------
                            nError = axXnsSdkDevice.StopBackup(hDevice, nRecChannel);
                        }
                    }
                }
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Check rec radio button.
        // ----------------------------------------------------------------------- 
        private void RADIO_REC_CheckedChanged(object sender, EventArgs e)
        {
            bRecCheck = true;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Check sec radio buttont.
        // ----------------------------------------------------------------------- 
        private void RADIO_SEC_CheckedChanged(object sender, EventArgs e)
        {
            bRecCheck = false;
        }
    }
}
