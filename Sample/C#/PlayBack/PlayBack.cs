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
// @ File Name :		PlayBack.cs
// @ File Description : PlayBack Form Source Code File. 
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
using XNSSDKWINDOWLib;
using XNSSDKDEVICELib;
// Define XNS Sample Log
using XNSSAMPLELOGLib;

namespace PlayBack
{
    public partial class PlayBackForm : Form
    {
        // Device Information
        private const string LOGIN_ID       = "admin";
        private const string PASSWORD       = "love081379";
        private const string IP_ADDRESS     = "192.168.217.103";
        private const string PORT_NUM       = "554";
        private const string HTTPPORT_NUM   = "80";
        private const string MODEL_NAME     = "Samsung Network Camera/Encoder";

        private const int TRUE          = 1;
        private const int FALSE         = 0;
        private const int NULL          = 0;
        private const int XADDRESS_IP   = 1;

        private const int STATE_STOP    = 0;
        private const int STATE_PLAY    = 1;
        private const int STATE_BACK    = 2;
        private int nPlayStatus         = 0;

        private int nYear               = 0;
        private int nMonth              = 0;
        private List<int> StartTime     = new List<int>();
        private List<int> EndTime       = new List<int>();

        private int hDevice             = 0;
        private int hMediaSource        = 0;
        private int nControlID          = 0;
        private int nError              = 0;
        private double dPlaySpeed       = 1.0;
        private DebugLog m_DebugLog     = null;

        public PlayBackForm()
        {
            InitializeComponent();
            m_DebugLog = new DebugLog(this.LIST_LOG);
        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Load Event.
        // -----------------------------------------------------------------------
        private void PlayBackForm_Load(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Initializes the DLL files. 
            // For this, XnsActiveX library requires config.xml, device.xml, 
            // and xns.xml files and the DLL file list should be mentioned 
            // in Xns.xml file. The path of the DLL file can not exceed 512 bytes
            // in length. The XnsActiveX library searches for xns.xml using 
            // XnsSDKDevice.ocx installed in "{$SDK path}\Config" folder.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.Initialize();
            m_DebugLog.WLOGD("Initialize():: ", nError, axXnsSdkDevice.GetErrorString(nError));


            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Initializes the XnsSdkWindow control. 
            // Namely, this will specify the window handle in order to display 
            // images on the screen. 
            // -----------------------------------------------------------------------
            nError = axXnsSdkWindow.Initialize(0, 0);
            m_DebugLog.WLOGW("Initialize():: ", nError, axXnsSdkDevice.GetErrorString(nError));

            // Dialog Setting.
            OnSetDialog();
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ User-Defined Functions.
        // for Dialog Control initialize function.
        // -----------------------------------------------------------------------
        public void OnSetDialog()
        {
            // ModelList ComboBax Setting.
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Reads device list from {$SDK path}\Bin\Config\xns.xml. 
                // Finds information mentioned in the configuration file before returning. 
                // To enable this function, follow the steps below:
                // < Procedure >
                // Step 1. 	Use FindVendor(), FindModel(), FindDevice() to start searching.
                // Step 2. 	Use GetFindSize to get the array size.
                // Step 3. 	Use GetFindString() to obtain the vendor name and model name.
                // Step 4. 	Use GetFindLong() and GetFindDouble0 to obtain the device ID. 
                //			(Repeat this process if necessary)
                // Step 5. 	Call CloseFind0 to end the search.
                // Returns the handle of the Find array. 
                // Returns NULL(0) if no model list is found.
                // -----------------------------------------------------------------------
                int hFind = axXnsSdkDevice.FindModel("samsung");

                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Returns the length of the array that is created using FindVendor(), 
                // FindModel(), and FindDevice().
                // -----------------------------------------------------------------------
                int hFindSize = axXnsSdkDevice.GetFindSize(hFind);

                System.String strModel = null;
                for (int i = 0; i < hFindSize; i++)
                {
                    // [ XNS ACTIVEX HELP ]
                    // -----------------------------------------------------------------------
                    // Reurns data of nIndex from the array created using FindVendor() 
                    // and FindModel(). If nIndex is larger than the actual array, 
                    // "" will be returned.
                    // -----------------------------------------------------------------------
                    strModel = axXnsSdkDevice.GetFindString(hFind, i);
                    COMBO_MODELLIST.Items.Add(strModel);
                }

                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Closes the Find command. Releases the memory space assinged by FindXXX().
                // -----------------------------------------------------------------------
                axXnsSdkDevice.CloseFind(hFind);

                COMBO_MODELLIST.SelectedIndex = 0;
                int index = COMBO_MODELLIST.FindStringExact(MODEL_NAME, 0);
                if (index != -1)
                {
                    COMBO_MODELLIST.SelectedIndex = index;
                }
            }

            // Set User Information Edit Box
            {
                EDIT_IP.Text    = IP_ADDRESS;
                EDIT_PORT.Text  = PORT_NUM;
                EDIT_HTTPPORT.Text = HTTPPORT_NUM;
                EDIT_ID.Text    = LOGIN_ID;
                EDIT_PW.Text    = PASSWORD;
            }

            // Speed ComboBox Setting
            {
                COMBO_SPEED.Items.Add("1X");
                COMBO_SPEED.Items.Add("2X");
                COMBO_SPEED.Items.Add("4X");
                COMBO_SPEED.Items.Add("8X");
                COMBO_SPEED.Items.Add("16X");
                COMBO_SPEED.Items.Add("32X");
            }

            // Set Dialog Enable
            {
                BTN_DISCONNECT.Enabled = false;
                BTN_CHECK_CALENDAR.Enabled = false;
                BTN_NREWARD.Enabled = false;
                BTN_REWARD.Enabled = false;
                BTN_STOP.Enabled = false;
                BTN_PLAY.Enabled = false;
                BTN_NPLAY.Enabled = false;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Device Connect Function.
        // ----------------------------------------------------------------------- 
        private void BTN_CONNECT_Click(object sender, EventArgs e)
        {
            string strModel     = (System.String)COMBO_MODELLIST.SelectedItem;
            string strIpAddress = EDIT_IP.Text;
            int nPort           = int.Parse(EDIT_PORT.Text);
            int nHttpPort       = int.Parse(EDIT_HTTPPORT.Text);
            string strID        = EDIT_ID.Text;
            string strPW        = EDIT_PW.Text;
            int nDeviceProtocol = 0;

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Assigns memory space for saving device information. 
            // This function will return the device handle, which the application 
            // can use to control the device.
            // [in] Device ID The value should be a greater integer than 0.
            // Minimum value: 1 , Maximum value: 3000
            // -----------------------------------------------------------------------
            int device_id = axXnsSdkDevice.CreateDeviceEx();
            hDevice = axXnsSdkDevice.GetDeviceHandle(device_id);

            if (hDevice == NULL)
            {
                m_DebugLog.WLOGD("CreateDevice() fail");
                return;
            }

            if (CHECKBOX_SUNAPI.Checked == true &&
                (strModel == "Samsung Network Camera/Encoder" || strModel == "Samsung NVR"))
            {
                nDeviceProtocol = (int)XDeviceProtocolType.XDEVICE_PROTOCOL_SUNAPI;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Sets the device information so that the application can connect 
            // to the device.
            // -----------------------------------------------------------------------
            this.axXnsSdkDevice.SetConnectionInfo2(
                hDevice,            // [in] Device handle. This value is returned from CreateDevice().
                "Samsung",          // [in] Fixed as 'Samsung'. The maximum length allowed is 126-byte.
                strModel,           // [in] Name of model to connect to. The maximum length allowed is 126-byte.
                XADDRESS_IP,        // [in] Address type
                strIpAddress,       // [in] Actual address according to nAddressType. 
                nPort,              // [in] Port number
                nHttpPort,          // [in] Port number for web access
                strID,              // [in] Login ID. The maximum length allowed is 62-byte
                strPW,              // [in] Login password. The maximum length allowed is 18-byte
                nDeviceProtocol,
                0);                 

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Enables the application to connect to the device using the connection 
            // information. You can use SetConnectionInfo() to configure the 
            // connection settings. This function performs as non-blocking function, 
            // and will be returned immediately even if the connection is not 
            // completed. The connection result will be transferred through the event. 
            // When connection is made successfully, the OnDeviceStatusChanged() event
            // will occur. When failed, the OnConnectFailed event occurs.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ConnectNonBlock(
                hDevice,            // [in] Device handle. This value is returned from CreateDevice(). 
                TRUE,              // [in] Flag to decide where to forcibly log in or not.
                TRUE);             // [in] When the device is disconnected, you can use this flag to decide
                                    //      if to connect again automatically. If this value is 1, try to connect again.
            m_DebugLog.WLOGD("ConnectNonBlock():: ", nError, axXnsSdkDevice.GetErrorString(nError));

            if (nError == (int)XErrorCode.ERR_SUCCESS)
            {
                BTN_CONNECT.Enabled = false;
                BTN_DISCONNECT.Enabled = true;
                BTN_CHECK_CALENDAR.Enabled = true;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Device Disconnect Function.
        // ----------------------------------------------------------------------- 
        private void BTN_DISCONNECT_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Check if there exists stream source.
            // -----------------------------------------------------------------------
            if (axXnsSdkWindow.IsMedia() == TRUE)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Stops receiving the stream data from the media source handle.  
                // -----------------------------------------------------------------------
                hMediaSource = axXnsSdkWindow.Stop();
            }

            if (hMediaSource != 0)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Terminates transferring media stream data from the device. The media 
                // stream data will be separated by hMediaSource 
                // (i.e., phMediaSource of OpenMedia()).
                // -----------------------------------------------------------------------
                axXnsSdkDevice.CloseMedia(hDevice, hMediaSource);
                hMediaSource = 0;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Disconnects from the device.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.Disconnect(hDevice);
            m_DebugLog.WLOGD("Disconnect():: ", nError, axXnsSdkDevice.GetErrorString(nError));

            if (nError == (int)XErrorCode.ERR_SUCCESS)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Cancels the memory space assigned for the device information by 
                // CreateDevice(). The device should be disconnected from the application 
                // before this function is called.
                // -----------------------------------------------------------------------
                axXnsSdkDevice.ReleaseDevice(hDevice);

                BTN_CONNECT.Enabled = true;
                BTN_DISCONNECT.Enabled = false;
                BTN_CHECK_CALENDAR.Enabled = false;
                BTN_NREWARD.Enabled = false;
                BTN_REWARD.Enabled = false;
                BTN_STOP.Enabled = false;
                BTN_PLAY.Enabled = false;
                BTN_NPLAY.Enabled = false;

                MONTH_CALENDAR.RemoveAllBoldedDates();
                MONTH_CALENDAR.UpdateBoldedDates();
                LISTBOX_RECORD_FILE.Items.Clear();
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Check Calendar Function.
        // ----------------------------------------------------------------------- 
        private void BTN_CHECK_CALENDAR_Click(object sender, EventArgs e)
        {
            nYear = MONTH_CALENDAR.SelectionStart.Year;
            nMonth = MONTH_CALENDAR.SelectionStart.Month;
            
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Converts the date (MM/DD/YY) and time (HH:MM:SS) to the time_t format.
            // -----------------------------------------------------------------------
            int TargetMonth = axXnsSdkDevice.DateToTimet(nYear, nMonth, 1, 0, 0, 0);
            
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Covert local time to UTC time. 
            // -----------------------------------------------------------------------
            TargetMonth = axXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, TargetMonth);

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Acquires the permission to play the recorded multimedia.
            // The application should acquire the permission using this function 
            // before it can play video.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.AcquireMediaAuthority(hDevice);
            if(nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("AcquireMediaAuthority() fail. errorcode =", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }
            m_DebugLog.WLOGD("Search Calendar, target year="+nYear.ToString()+" month="+nMonth.ToString());

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Gets the video recording dates from a specific month. The result of 
            // this function can be obtained from the OnSearchCalendar event.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.SearchCalendar(
                hDevice,            // [in] Device handle. This value is returned from CreateDevice().
                nControlID,         // [in] Control ID.
                TargetMonth);       // [in] First day of a specific month. Format: 4-byte time_t.
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("SearchCalendar() fail. errorcode =", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // Go previous time Function.
        // ----------------------------------------------------------------------- 
        private void BTN_NREWARD_Click(object sender, EventArgs e)
        {
           	m_DebugLog.WLOGD("Go previous time");
        	if(nControlID == 0)
        	{
                m_DebugLog.ERROR_BOX("No record list..");
        		return;
        	}

            int currIndex = TRACKBAR_PLAY.Value; 
            int min = TRACKBAR_PLAY.Minimum;
            int max = TRACKBAR_PLAY.Maximum;
        	int offset = (int)((max-min)/10);

        	currIndex = currIndex - offset;
        	if(currIndex < min)
            {
        		currIndex = min;
            }
        	TRACKBAR_PLAY.Value = currIndex;

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Covert local time to UTC time. 
            // -----------------------------------------------------------------------
        	currIndex = axXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, currIndex);

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Searches for a specific time point of the media stream.
            // -----------------------------------------------------------------------
        	axXnsSdkDevice.Seek(hDevice, nControlID, currIndex);
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Back Function.
        // ----------------------------------------------------------------------- 
        private void BTN_REWARD_Click(object sender, EventArgs e)
        {
            m_DebugLog.WLOGD("Back");
            if (nControlID == 0)
            {
                m_DebugLog.ERROR_BOX("No record list..");
                return;
            }

            if (dPlaySpeed > 0)
            {
                dPlaySpeed *= -1;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Plays the multimedia at a specified speed.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.Play(hDevice, nControlID, dPlaySpeed);
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("Play() fail. errorcode =" + nError + " " + axXnsSdkDevice.GetErrorString(nError));
            }
            nPlayStatus = STATE_BACK;
            BTN_REWARD.Enabled = false;
            BTN_STOP.Enabled = true;
            BTN_PLAY.Enabled = true;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Stop video Function.
        // ----------------------------------------------------------------------- 
        private void BTN_STOP_Click(object sender, EventArgs e)
        {
            m_DebugLog.WLOGD("Stop");
            if (nControlID == 0)
            {
                m_DebugLog.ERROR_BOX("No record list..");
                return;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Stops playing the media stream temporarily.
            // -----------------------------------------------------------------------
            axXnsSdkDevice.Pause(hDevice, nControlID);

            nPlayStatus = STATE_STOP;
            BTN_STOP.Enabled = false;
            BTN_PLAY.Enabled = true;
            BTN_REWARD.Enabled = true;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Play video Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PLAY_Click(object sender, EventArgs e)
        {
            if (TRACKBAR_PLAY.Value == TRACKBAR_PLAY.Maximum)
            {
                return;
            }

            m_DebugLog.WLOGD("Play");
            if (nControlID == 0)
            {
                m_DebugLog.ERROR_BOX("No record list..");
                return;
            }

            if (dPlaySpeed < 0)
            {
                dPlaySpeed *= -1;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Plays the multimedia at a specified speed.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.Play(hDevice, nControlID, dPlaySpeed);
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("Play() fail. errorcode =" + nError + " " + axXnsSdkDevice.GetErrorString(nError));
                return;
            }

            nPlayStatus = STATE_PLAY;
            BTN_PLAY.Enabled = false;
            BTN_STOP.Enabled = true;
            BTN_REWARD.Enabled = true;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // Go next time Function.
        // ----------------------------------------------------------------------- 
        private void BTN_NPLAY_Click(object sender, EventArgs e)
        {
          	m_DebugLog.WLOGD("Go next time");
        	if(nControlID == 0)
	        {
		        m_DebugLog.ERROR_BOX("No record list..");
        		return;
        	}

	        int currIndex = TRACKBAR_PLAY.Value; 
	        int min = TRACKBAR_PLAY.Minimum;
            int max = TRACKBAR_PLAY.Maximum;;
	        int offset = (int)((max-min)/10);
	        
            currIndex = currIndex + offset;
            if(currIndex > max)
            {
		        currIndex = max;
            }
            TRACKBAR_PLAY.Value = currIndex;

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Covert local time to UTC time. 
            // -----------------------------------------------------------------------
	        currIndex = axXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, currIndex);

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Searches for a specific time point of the media stream.
            // -----------------------------------------------------------------------
            axXnsSdkDevice.Seek(hDevice, nControlID, currIndex);
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm ComboBox Event.
        // Selected index changed Function.
        // ----------------------------------------------------------------------- 
        private void COMBO_SPEED_SelectedIndexChanged(object sender, EventArgs e)
        {
            int index = COMBO_SPEED.SelectedIndex;

            switch(index)
            {
                case 0:
                    dPlaySpeed = 1.0;
                    break;
                case 1:
                    dPlaySpeed = 2.0;
                    break;
                case 2:
                    dPlaySpeed = 4.0;
                    break;
                case 3:
                    dPlaySpeed = 8.0;
                    break;
                case 4:
                    dPlaySpeed = 16.0;
                    break;
                case 5:
                    dPlaySpeed = 32.0;
                    break;
            }
            m_DebugLog.WLOGD("Play Speed = " + dPlaySpeed);

            if(nControlID != 0)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Informs if the media stream is currently playing.
                // ----------------------------------------------------------------------- 
                if(axXnsSdkDevice.IsPlaying(hDevice) != FALSE)
                {
                    axXnsSdkDevice.Pause(hDevice, nControlID);
                    if (nPlayStatus == STATE_PLAY)
                    {
                        m_DebugLog.WLOGD("Play");
                        if (nControlID == 0)
                        {
                            m_DebugLog.ERROR_BOX("No record list..");
                            return;
                        }
                        if (dPlaySpeed < 0)
                        {
                            dPlaySpeed *= -1;
                        }

                        int nErrorCode = axXnsSdkDevice.Play(hDevice, nControlID, dPlaySpeed);
                        if (nErrorCode != (int)XErrorCode.ERR_SUCCESS)
                        {
                            m_DebugLog.WLOGD("Play() fail. errorcode =" + nErrorCode.ToString() + " " + axXnsSdkDevice.GetErrorString(nErrorCode));
                        }
                        nPlayStatus = STATE_PLAY;
                    }
                    else if(nPlayStatus == STATE_BACK)
                    {
                        m_DebugLog.WLOGD("Back");
                        if (nControlID == 0)
                        {
                            m_DebugLog.ERROR_BOX("No record list..");
                            return;
                        }

                        if (dPlaySpeed > 0)
                        {
                            dPlaySpeed *= -1;
                        }

                        int nErrorCode = axXnsSdkDevice.Play(hDevice, nControlID, dPlaySpeed);
                        if (nErrorCode != (int)XErrorCode.ERR_SUCCESS)
                        {
                            m_DebugLog.WLOGD("Play() fail. errorcode =" + nErrorCode.ToString() + " " + axXnsSdkDevice.GetErrorString(nErrorCode));
                        }
                        nPlayStatus = STATE_BACK;
                    }
                }
            }
        }
 

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This event occurs if the device status has changed. It occurs if the 
        // application uses Connect() to connect or reconnect to the device after 
        // disconnected. When reconnecting, the third argument nDeviceStatus is 
        // true, all media must be reopened using ReopenAllStream().
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnDeviceStatusChanged(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEvent e)
        {
            m_DebugLog.WLOGD("OnDeviceStatusChanged() EVENT:: device_id=" + e.nDeviceID + ", status=" + e.nDeviceStatus +
                ", error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
            if ((e.nErrorCode != (int)XErrorCode.ERR_SUCCESS) || (e.nDeviceStatus != 1))
            {
                m_DebugLog.WLOGD("Disconnected!");
                return;
            }
            
            nControlID = axXnsSdkDevice.GetVideoControlID(hDevice, 1, 1);

            BTN_CONNECT.Enabled = false;
            BTN_DISCONNECT.Enabled = true;
            BTN_CHECK_CALENDAR.Enabled = true;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // If the application has failed in non-blocking connection using ConnectNonBlock(), 
        // the OnConnectFailed event occurs. 
        // As Connect() returns an immediate error message if failed, 
        // it does not trigger this event.
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnConnectFailed(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEvent e)
        {
            m_DebugLog.WLOGD("OnConnectFailed() EVENT:: device_id=" + e.nDeviceID +
                ", error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This event occurs if the application calls SearchCalendar(), 
        // which contains the search result.  
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnSearchCalendar(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnSearchCalendarEvent e)
        {
            int nBitFlag = 0x01;
            DateTime BoldedDate; 
            int nDay;

            for (int i = 0; i < 31; i++)
            {
                if ((e.nRecDay & nBitFlag) != 0)
                {
                    nDay = i + 1;
                    BoldedDate = new DateTime(nYear, nMonth, nDay);
                    MONTH_CALENDAR.AddBoldedDate(BoldedDate);
                }
                nBitFlag <<= 1;
            }
            MONTH_CALENDAR.UpdateBoldedDates();
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Calendar Control Event.
        // This event occurs if the application calls SearchCalendar(), 
        // which contains the search result.
        // -----------------------------------------------------------------------
        private void MONTH_CALENDAR_DateSelected(object sender, DateRangeEventArgs e)
        {
            LISTBOX_RECORD_FILE.Items.Clear();
            StartTime.Clear();
            EndTime.Clear();

            int nDay = MONTH_CALENDAR.SelectionStart.Day;

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Gets the video recording dates from a specific month. 
            // The result of this function can be obtained from the OnSearchCalendar event.
            // Return Value : Converted values in time_t format.
            // -----------------------------------------------------------------------
            int tStart = axXnsSdkDevice.DateToTimet(
                nYear,					// [in] Year
                nMonth,					// [in] Month
                nDay,					// [in] Day
                0,						// [in] Hour
                0,						// [in] Minute
                0);						// [in] Second
            int tEnd = axXnsSdkDevice.DateToTimet(nYear, nMonth, nDay, 23, 59, 59);					

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Converts local t_time to UTC t_time.
            // Return Value : UTC time_t value.
            // -----------------------------------------------------------------------
            int tUTCStart = axXnsSdkDevice.LocalTimeToDeviceUTC(
                hDevice,				// [in] Device handle. This value is returned from CreateDevice().
                tStart);				// [in] local time_t value
            int tUTCEnd = axXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, tEnd);					

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Gets a list of recording data for a specific day. 
            // The result of this function can be obtained from the OnSearchDay event.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.SearchDay(
                hDevice,				// [in] Device handle. This value is returned from CreateDevice().
                nControlID,				// [in] Control ID. 
                tUTCStart,				// [in] Play start time. Format: UTC time_t.
                tUTCEnd,				// [in] Play start time. Format: UTC time_t.
                (int)XRecType.REC_TYPE_ALL);		// [in] Recording type.
                
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("SearchDay() fail. errorcode =", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This event occurs if the application calls SearchDay(), 
        // which contains the search result.  
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnSearchDay(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnSearchDayEvent e)
        {
            int nTimelineCount  = 0;
            int nRecType        = 0;
            int nRecId          = 0; 
            
            int tStart          = 0;
            int tEnd            = 0;
            int nDay            = 0;
            int StartHour = 0, StartMin = 0, StartSec = 0;
            int EndHour   = 0, EndMin   = 0, EndSec   = 0;

            int i = 0, j = 0;
            int nTotalCount = 0;
            string strType  = "";

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the number of cameras existing in the timeline.
            // Return Value : Number of the cameras(from those connected in the system)
            //                that have recording data on a specified date.  
            // -----------------------------------------------------------------------
            int nCamCount = axXnsSdkDevice.GetCameraCount(e.hTimeline);
            m_DebugLog.WLOGD("OnSearchDay Event.. nCamCount[" + nCamCount + "]");

            for (i = 0; i < nCamCount; i++)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Number of blocks of the recording data in the timeline. 
                // This value is used as a parameter of functions: 
                // GetStartTime(), GetEndTime(), GetRecordingType().
                // Return Value : Number of blocks of the recording data in the timeline. 
                // -----------------------------------------------------------------------
                nTimelineCount = axXnsSdkDevice.GetTimelineCount(e.hTimeline, i);
                for (j = 0; j < nTimelineCount; j++)
                {
                    // [ XNS ACTIVEX HELP ]
                    // -----------------------------------------------------------------------
                    // Returns information on the recording data block. 
                    // -----------------------------------------------------------------------
                    axXnsSdkDevice.GetTimeline(
                        e.hTimeline,            // [in] Timeline handle obtained from the OnSearchDay event.   
                        i,                      // [in] Camera index (start with 0).
                        j,                      // [in] Timeline index (start with 0).
                        1,                      // [in] Time type.
                        ref tStart,             // [out] Start time of the timeline block.
                        ref tEnd,               // [out] End time of the timeline block.
                        ref nRecType,           // [out] Recording type. Cause of starting the recording (see Table 3.9).
                                                //       If there is more than one cause to start recording, 
                                                //       the bit-wise ORing value will be set as valid.
                        ref nRecId);            // [out] If there are at least two data items in the same timeline, 
                                                //       this function will identify them by the ID.

                    StartTime.Add(tStart);
                    EndTime.Add(tEnd);

                    // [ XNS ACTIVEX HELP ]
                    // -----------------------------------------------------------------------
                    // Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
                    // -----------------------------------------------------------------------
                    axXnsSdkDevice.TimetToDate(
                        tStart,				    	// [in] Data in time_t format to convert.
                        ref nYear,					// [out] Year
                        ref nMonth,				    // [out] Month
                        ref nDay,					// [out] Day
                        ref StartHour,				// [out] Hour
                        ref StartMin,				// [out] Minute
                        ref StartSec);				// [out] Second
                    axXnsSdkDevice.TimetToDate(tEnd, ref nYear, ref nMonth, ref nDay, ref EndHour, ref EndMin, ref EndSec);										

                    // Print Record File List
                    switch (nRecType)
                    {
                        case (int)XRecType.REC_TYPE_NONE:
                            strType = "NON";
                            break;
                        case (int)XRecType.REC_TYPE_MOTION:
                            strType = "MOT";
                            break;
                        case (int)XRecType.REC_TYPE_ALARM:
                            strType = "ALM";
                            break;
                        case (int)XRecType.REC_TYPE_VLOSS:
                            strType = "VLS";
                            break;
                        case (int)XRecType.REC_TYPE_MANUAL:
                            strType = "MAN";
                            break;
                        case (int)XRecType.REC_TYPE_CONTINUOS:
                            strType = "CON";
                            break;
                        case (int)XRecType.REC_TYPE_ALL:
                            strType = "ALL";
                            break;
                        default:
                            strType = "OTH";
                            break;
                    }

                    LISTBOX_RECORD_FILE.Items.Add(String.Format("{0:000}", nTotalCount) + " " + strType + " | "
                        + String.Format("{0:00}", StartHour) + ":" + String.Format("{0:00}", StartMin) + ":" + String.Format("{0:00}", StartSec) 
                        + " - " + String.Format("{0:00}", EndHour) + ":" + String.Format("{0:00}", EndMin) + ":" + String.Format("{0:00}", EndSec));
                    nTotalCount++;
                }
            }
            m_DebugLog.WLOGD("OnSearchDay() Event Call!");
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm LISTBOX Control Event.
        // for Record Video Play.
        // -----------------------------------------------------------------------
        private void LISTBOX_RECORD_FILE_DoubleClick(object sender, EventArgs e)
        {
            if (axXnsSdkDevice.GetDeviceStatus(hDevice) != (int)XConnect.XDEVICE_STATUS_CONNECTED)
            {
                return;
            }

            int nIndex = LISTBOX_RECORD_FILE.SelectedIndex;
            
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Convert from LocalTime to Device UTC
            // Return Value : UTC time_t value.
            // -----------------------------------------------------------------------
            int tStart = axXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, StartTime[nIndex]);										
            int tEnd = axXnsSdkDevice.LocalTimeToDeviceUTC(hDevice,	EndTime[nIndex]);

            BTN_NREWARD.Enabled = true;
            BTN_REWARD.Enabled = true;
            BTN_STOP.Enabled = false;
            BTN_PLAY.Enabled = true;
            BTN_NPLAY.Enabled = true;

            if(hMediaSource != 0)
            {
                {
                    // [ XNS ACTIVEX HELP ]
                    // -----------------------------------------------------------------------
                    // Stops receiving the stream sata from the mediasource handle (pMediaSource).
                    // -----------------------------------------------------------------------
                    axXnsSdkWindow.Stop();

                    // [ XNS ACTIVEX HELP ]
                    // -----------------------------------------------------------------------
                    // Terminates transferring media stream data from the device. 
                    // The media stream data will be separated by hMediaSource 
                    // (i.e., phMediaSource of OpenMedia()).
                    // -----------------------------------------------------------------------
                    axXnsSdkDevice.CloseMedia(hDevice, hMediaSource);

                    hMediaSource = 0;
                    nPlayStatus = STATE_STOP;
                }
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Acquires the permission to play the recorded multimedia. 
            // The application should acquire the permission using 
            // this function before it can play video.
            // -----------------------------------------------------------------------
            axXnsSdkDevice.AcquireMediaAuthority(hDevice);

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module.
            // -----------------------------------------------------------------------
            axXnsSdkDevice.OpenMedia(
                            hDevice,								// [in] Device handle. This value is returned from CreateDevice().
                            nControlID,								// [in] Control ID of video control module.
                            (int)XMediaType.XMEDIA_PLAYBACK,	    // [in] Media type.
                            tStart,									// [in] Play start time. Format: 4-byte time_t.
                            tEnd,									// [in] Play end time. Format: 4-byte time_t.
                            ref hMediaSource);						// [out] Media stream ID.
            m_DebugLog.WLOGD("Media Open Success.");

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Adds the media source handle to XnsSdkWindow.
            // The media source handle is created by XnsSdkDevice. 
            // If the application calls XnsSdkDevice::OpenMedia(), 
            // it will receive media stream from the device and return the MediaSource handle. 
            // The application uses uses Start() to forward the mediasource handle 
            // to XnsSdkWindow so that XnsSdkWindow can obtain stream data.
            // -----------------------------------------------------------------------
            axXnsSdkWindow.Start(hMediaSource);

            m_DebugLog.WLOGW("Media Play Success.");

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Searches for a specific time point of the media stream.
            // -----------------------------------------------------------------------
            if (axXnsSdkDevice.IsPlaying(hDevice) == 0)				// Not Playing
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Informs if the media stream is currently playing.
                // -----------------------------------------------------------------------
                axXnsSdkDevice.Seek(
                    hDevice,            // [in] Device handle. This value is returned from CreateDevice(). 
                    nControlID,			// [in] Control ID.
                    tStart);			// [in] Target time. Format: 4-byte time_t.

                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Plays the multimedia at a specified speed.
                // -----------------------------------------------------------------------
//                 axXnsSdkDevice.Play(
//                     hDevice,										// [in] Device handle. This value is returned from CreateDevice().
//                     nControlID,										// [in] Control ID.
//                     1.0);

                COMBO_SPEED.SelectedIndex = 0;
            }
            TRACKBAR_PLAY.SetRange(StartTime[nIndex], EndTime[nIndex]);
            TRACKBAR_PLAY.Value = StartTime[nIndex];
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Window Control Event.
        // This event occurs if the frame time displayed on the screen is changed.
        // This happens every second video is played. 
        // -----------------------------------------------------------------------
        private void axXnsSdkWindow_OnFrameTimeChanged(object sender, AxXNSSDKWINDOWLib._DXnsSdkWindowEvents_OnFrameTimeChangedEvent e)
        {
            if (e.tFrameTime > TRACKBAR_PLAY.Maximum)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Stops playing the media stream temporarily.
                // -----------------------------------------------------------------------
                axXnsSdkDevice.Pause(hDevice, nControlID);

                int tUTCEnd = axXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, TRACKBAR_PLAY.Maximum);
                axXnsSdkDevice.Seek(hDevice, nControlID, tUTCEnd);
                e.tFrameTime = TRACKBAR_PLAY.Maximum;

                nPlayStatus = STATE_STOP;
                BTN_STOP.Enabled = false;
                BTN_PLAY.Enabled = true;
                BTN_REWARD.Enabled = true;
            }
            else if (e.tFrameTime < TRACKBAR_PLAY.Minimum)
            {
                axXnsSdkDevice.Pause(hDevice, nControlID);

                int tUTCStart = axXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, TRACKBAR_PLAY.Minimum);
                axXnsSdkDevice.Seek(hDevice, nControlID, tUTCStart);
                e.tFrameTime = TRACKBAR_PLAY.Minimum;

                nPlayStatus = STATE_STOP;
                BTN_STOP.Enabled = false;
                BTN_PLAY.Enabled = true;
                BTN_REWARD.Enabled = true;
            }

            int Year = 0, Month = 0, Day = 0, Hour = 0, Min = 0, Sec = 0;
            string strTime = "";

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // IConverts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
            // -----------------------------------------------------------------------
            axXnsSdkDevice.TimetToDate(e.tFrameTime, ref Year, ref Month, ref Day, ref Hour, ref Min, ref Sec);

            strTime = String.Format("{0:00}", Hour)+":"+String.Format("{0:00}", Min)+":"+String.Format("{0:00}", Sec);

            STR_TIME.Text = strTime;
            TRACKBAR_PLAY.Value = e.tFrameTime;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# TRACKBAR Control Event.
        // Mouse capture changed 
        // -----------------------------------------------------------------------
        private void TRACKBAR_PLAY_MouseCaptureChanged(object sender, EventArgs e)
        {
            int CurrentTime = TRACKBAR_PLAY.Value;

            if (CurrentTime < TRACKBAR_PLAY.Minimum || CurrentTime > TRACKBAR_PLAY.Maximum)
            {
                return;
            }

            CurrentTime = axXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, CurrentTime);
            axXnsSdkDevice.Seek(hDevice, nControlID, CurrentTime);
        }
    }
}
