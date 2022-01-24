///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011 by Samsung Techwin, Inc.
//
// This software is copyrighted by, and is the sole property of Samsung Techwin.
// All rights, title, ownership, or other interests in the software remain the
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
// @ File Name :		Event.cs
// @ File Description : Event Form Source Code File. 
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

namespace Event
{
    public partial class EventForm : Form
    {
        // Device Information
        private const string LOGIN_ID       = "admin";
        private const string PASSWORD       = "11111111";
        private const string IP_ADDRESS     = "192.168.2.6";
        private const string PORT_NUM       = "4000";
        private const string MODEL_NAME     = "SNR-3200";

        private const int TRUE              = 1;
        private const int FALSE             = 0;
        private const int NULL              = 0;
        private const int XADDRESS_IP       = 1;
        private const int ALARM_OFF         = 0;
        private const int ALARM_ON          = 1;

        private int hDevice                 = 0;
        private int hMediaSource            = 0;
        private int nControlID              = 0;
        private int nError                  = 0;
        private int nAlarmBeep_CtrID        = 0;
        private int nIndex_Sensor           = 0;
        private int nIndex_Motion           = 0;
        private int nIndex_InteligentVideo  = 0;
        private int nIndex_VideoLoss        = 0;
        private int nIndex_SystemLog        = 0;
        private int nIndex_DeviceLog        = 0;
        private int nIndex_AllLog           = 0;
        private DebugLog m_DebugLog = null;

        public EventForm()
        {
            InitializeComponent();
            m_DebugLog = new DebugLog(this.LIST_LOG);
        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Load Event.
        // -----------------------------------------------------------------------
        private void EventForm_Load(object sender, EventArgs e)
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
                EDIT_ID.Text    = LOGIN_ID;
                EDIT_PW.Text    = PASSWORD;
            }

            // Set Dialog Enable
            {
                BTN_DISCONNECT.Enabled          = false;
                BTN_STOP.Enabled                = false;
                BTN_PLAY.Enabled                = false;
                CHECKBOX_ALARM_BEEP_ON.Enabled  = false;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ User-Defined Functions.
        // for EventLog function.
        // -----------------------------------------------------------------------
        private void PrintEventLog(int tEventUTC, string strEvent)
        {
            int Year = 0, Mon = 0, Day = 0;
            int Hour = 0, Min = 0, Sec = 0;

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Converts local UTC t_time to t_time. 
            // Return Value : Number of blocks of the recording data in the timeline. 
            // -----------------------------------------------------------------------
            int tLocal = axXnsSdkDevice.UTCToDeviceLocalTime(
                hDevice,			// [in] Device handle. This value is returned from CreateDevice(). 
                tEventUTC);			// [in] local time_t value

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
            // -----------------------------------------------------------------------
            axXnsSdkDevice.TimetToDate(
                tLocal,				// [in] Data in time_t format to convert.
                ref Year,			// [out] Year
                ref Mon,			// [out] Month
                ref Day,			// [out] Day
                ref Hour,			// [out] Hour
                ref Min,			// [out] Minute
                ref Sec);			// [out] Second

            DateTime dt = new DateTime(Year, Mon, Day, Hour, Min, Sec);
            ListBox lb = new ListBox();
            int nIndex = 0;
            nIndex_AllLog++;

            switch (strEvent)
            {
                case "Alarm":
                    nIndex = ++nIndex_Sensor;
                    lb = LIST_ALARM;
                    break;
                case "Motion":
                    nIndex = ++nIndex_Motion;
                    lb = LIST_MOTION;
                    break;
                case "Inteligent Video":
                    nIndex = ++nIndex_InteligentVideo;
                    lb = LIST_INTELIGENT_VIDEO;
                    break;
                case "Video Loss":
                    nIndex = ++nIndex_VideoLoss;
                    lb = LIST_VIDEO_LOSS;
                    break;
                case "System Log":
                    nIndex = ++nIndex_SystemLog;
                    lb = LIST_SYSTEM_LOG;
                    break;
                case "Device Log":
                    nIndex = ++nIndex_DeviceLog;
                    lb = LIST_DEVICE_LOG;
                    break;
            }

            string strList = "["+ strEvent +"][" + nIndex.ToString() + "] / [Time(Remote) : " + String.Format("{0:g}", dt) +"]";
            string strAllLog = "[" + strEvent + "][" + nIndex_AllLog.ToString() + "] / [Time(Remote) : " + String.Format("{0:g}", dt) + "]";

            lb.Items.Add(strList);
            LIST_ALL.Items.Add(strAllLog);
        }
        

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Device Connect Function.
        // ----------------------------------------------------------------------- 
        private void BTN_CONNECT_Click(object sender, EventArgs e)
        {
            string strModel = (System.String)COMBO_MODELLIST.SelectedItem;
            string strIpAddress = EDIT_IP.Text;
            int nPort = int.Parse(EDIT_PORT.Text);
            string strID = EDIT_ID.Text;
            string strPW = EDIT_PW.Text;

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Assigns memory space for saving device information. 
            // This function will return the device handle, which the application 
            // can use to control the device.
            // [in] Device ID The value should be a greater integer than 0.
            // Minimum value: 1 , Maximum value: 3000
            // -----------------------------------------------------------------------
            hDevice = axXnsSdkDevice.CreateDevice(1);
            if (hDevice == NULL)
            {
                m_DebugLog.WLOGD("CreateDevice() fail");
                return;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Sets the device information so that the application can connect 
            // to the device.
            // -----------------------------------------------------------------------
            this.axXnsSdkDevice.SetConnectionInfo(
                hDevice,            // [in] Device handle. This value is returned from CreateDevice().
                "Samsung",          // [in] Fixed as 'Samsung'. The maximum length allowed is 126-byte.
                strModel,           // [in] Name of model to connect to. The maximum length allowed is 126-byte.
                XADDRESS_IP,        // [in] Address type
                strIpAddress,       // [in] Actual address according to nAddressType. 
                nPort,              // [in] Port number
                0,                  // [in] Port number for web access
                strID,              // [in] Login ID. The maximum length allowed is 62-byte
                strPW);             // [in] Login password. The maximum length allowed is 18-byte

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
                TRUE);             // [in] When the device is disconnected, 
                                    //      you can use this flag to decide if to connect again automatically. 
                                    //      If this value is 1, try to connect again.
            m_DebugLog.WLOGD("ConnectNonBlock():: ", nError, axXnsSdkDevice.GetErrorString(nError));

            if (nError == (int)XErrorCode.ERR_SUCCESS)
            {
                BTN_CONNECT.Enabled = false;
                BTN_DISCONNECT.Enabled = true;
                BTN_PLAY.Enabled = true;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Device DisConnect Function.
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
                BTN_PLAY.Enabled = false;
                BTN_STOP.Enabled = false;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Play Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PLAY_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the connection status of the device.
            // -----------------------------------------------------------------------
            if (axXnsSdkDevice.GetDeviceStatus(hDevice) != ((int)XConnect.XDEVICE_STATUS_CONNECTED))
            {
                m_DebugLog.WLOGD("Not connected");
                return;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the type of control module corresponding to the control ID.
            // Control Module : DVR Check
            // -----------------------------------------------------------------------
            if (axXnsSdkDevice.GetControlType(hDevice, 1) == (int)XModelType.XCTL_DVR)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Returns the number of control modules. 
                // The application can get the number of specific type of control modules, 
                // and can get also the whole number of video recorders or cameras.
                // -----------------------------------------------------------------------
                int nCount = axXnsSdkDevice.GetControlCount(hDevice, (int)XModelType.XCTL_CAMERA);
                for (int i = 0; i < nCount; i++)
                {
                    // [ XNS ACTIVEX HELP ]
                    // -----------------------------------------------------------------------
                    // Returns the capabilities of the control module.
                    // -----------------------------------------------------------------------
                    if ((axXnsSdkDevice.GetControlCapability(hDevice, i + 2, ((int)XUnitCap.XCTL_CAP_LIVE)) != FALSE))
                    {
                        // [ XNS ACTIVEX HELP ]
                        // -----------------------------------------------------------------------
                        // When called, it will start getting media streams from the device.
                        // The receiving media streams will, then, be forwarded to the XnsSdkWindow 
                        // component that will play the streams after decoding.
                        // phMediaSource is needed to link the stream data with XnsSdkWindow. 
                        // The value can be obtained from a parameter (out-parameter) of OpenMedia(). 
                        // When XnsSdkWindow receives this value, it can get stream data from the device.
                        // phMediaSource is also used for controlling playback of multimedia files. 
                        // As a result, the application should keep this value at all times.
                        // -----------------------------------------------------------------------
                        nError = axXnsSdkDevice.OpenMedia(hDevice, i + 2, ((int)XMediaType.XMEDIA_LIVE), 0, 0, ref hMediaSource);
                        if (nError == (int)XErrorCode.ERR_SUCCESS)
                        {
                            m_DebugLog.WLOGD("Media Open Success.");
                            nControlID = i + 2;
                        }
                        else
                        {
                            m_DebugLog.WLOGD("Media Open Failed.ret=" + nError.ToString() + "[" + axXnsSdkDevice.GetErrorString(nError) + "]");
                        }
                        break;
                    }
                }
            }
            // Control Module : Network Camera or Encoder Box (Video Server)
            else if ((axXnsSdkDevice.GetControlType(hDevice, 1) == ((int)XModelType.XCTL_NETCAM)) ||
                 (axXnsSdkDevice.GetControlType(hDevice, 1) == ((int)XModelType.XCTL_ENCODER)))
            {
                int nCount = axXnsSdkDevice.GetControlCount(hDevice, (int)XModelType.XCTL_VIDEO);
                for (int i = 0; i < nCount; i++)
                {
                    if ((axXnsSdkDevice.GetControlCapability(hDevice, i + 3, ((int)XUnitCap.XCTL_CAP_LIVE)) == TRUE))
                    {
                        nError = axXnsSdkDevice.OpenMedia(hDevice, i + 3, ((int)XMediaType.XMEDIA_LIVE), 0, 0, ref hMediaSource);
                        if (nError == (int)XErrorCode.ERR_SUCCESS)
                        {
                            m_DebugLog.WLOGD("Media Open Success.");
                            nControlID = i + 3;
                        }
                        else
                        {
                            m_DebugLog.WLOGD("Media Open Failed.ret=" + nError + "[" + axXnsSdkDevice.GetErrorString(nError) + "]");
                        }
                        break;
                    }
                }
            }
            

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Adds the media source handle to XnsSdkWindow. 
            // The media source handle is created by XnsSdkDevice. 
            // If the application calls XnsSdkDevice::OpenMedia(), 
            // it will receive media stream from the device and return the MediaSource 
            // handle. The application uses uses Start() to forward the mediasource 
            // handle to XnsSdkWindow so that XnsSdkWindow can obtain stream data. 
            // -----------------------------------------------------------------------
            nError = axXnsSdkWindow.Start(hMediaSource);
            switch (nError)
            {
                case (int)XErrorCode.ERR_SUCCESS:
                    BTN_PLAY.Enabled = false;
                    BTN_STOP.Enabled = true;
                    m_DebugLog.WLOGW("Media Play Success.");
                    break;
                default:
                    m_DebugLog.WLOGW("Media Play Failed.");
                    break;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Stop Function.
        // ----------------------------------------------------------------------- 
        private void BTN_STOP_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Stops receiving the stream data from the media source handle.  
            // -----------------------------------------------------------------------
            hMediaSource = axXnsSdkWindow.Stop();
            m_DebugLog.WLOGW("Media Play Stopped.");

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Terminates transferring media stream data from the device. The media 
            // stream data will be separated by hMediaSource 
            // (i.e., phMediaSource of OpenMedia()).
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.CloseMedia(hDevice, hMediaSource);
            switch (nError)
            {
                case (int)XErrorCode.ERR_SUCCESS:
                    hMediaSource = 0;
                    BTN_PLAY.Enabled = true;
                    BTN_STOP.Enabled = false;
                    m_DebugLog.WLOGD("Media Close Success.");
                    break;
                default:
                    m_DebugLog.WLOGD("Media Close Failed.");
                    break;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Event log clear Function.
        // ----------------------------------------------------------------------- 
        private void BTN_EVENT_LOG_CLEAR_Click(object sender, EventArgs e)
        {
            nIndex_Sensor           = 0;
            nIndex_Motion           = 0;
            nIndex_InteligentVideo  = 0;
            nIndex_VideoLoss        = 0;
            nIndex_SystemLog        = 0;
            nIndex_DeviceLog        = 0;
            nIndex_AllLog           = 0;

            LIST_ALARM.Items.Clear();
            LIST_MOTION.Items.Clear();
            LIST_INTELIGENT_VIDEO.Items.Clear();
            LIST_VIDEO_LOSS.Items.Clear();
            LIST_SYSTEM_LOG.Items.Clear();
            LIST_DEVICE_LOG.Items.Clear();
            LIST_ALL.Items.Clear();
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // For an alarm occurs.
        // -----------------------------------------------------------------------
        private void CHECKBOX_ALARM_BEEP_ON_CheckedChanged(object sender, EventArgs e)
        {
            // Search all device.
            if (nAlarmBeep_CtrID == 0)
            {
                // -----------------------------------------------------------------------
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Returns the number of control modules. 
                // The application can get the number of specific type of control modules, 
                // and can get also the whole number of video recorders or cameras.
                // -----------------------------------------------------------------------
                int nCount = axXnsSdkDevice.GetControlCount(hDevice, (int)XModelType.XCTL_ALL);
                for (int i = 1; i <= nCount; i++)
                {
                    // Returns the type of control module corresponding to the control ID.
                    int nType = axXnsSdkDevice.GetControlType(hDevice, i);
                    m_DebugLog.WLOGD("GetControlType():: controlType=(" + i + ")[" + nType + "]");
                    if (nType == (int)XModelType.XCTL_ALARM_BEEP)
                    {
                        m_DebugLog.WLOGD("GetControlType():: Beep control id=" + i);
                        nAlarmBeep_CtrID = i;
                        break;
                    }
                }
            }

            if (CHECKBOX_ALARM_BEEP_ON.Checked == true)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Turns on or off the alarm-out device (also called digital-out device). 
                // To enable this function, 
                // the control module should support the XCTL_CAP_ALARM_ONOFF capability.
                // -----------------------------------------------------------------------
                axXnsSdkDevice.SetAlarm(
                    hDevice,			// [in] Device handle. This value is returned from CreateDevice().
                    nAlarmBeep_CtrID,	// [in] Alarm Beef Control ID.
                    ALARM_ON);			// [in] Status of the alarm device.
            }
            else if(CHECKBOX_ALARM_BEEP_ON.Checked == false)
            {
                axXnsSdkDevice.SetAlarm(hDevice, nAlarmBeep_CtrID, ALARM_OFF);		        
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

            nIndex_SystemLog++;
            nIndex_AllLog++;

            string strSystemLog = "[System Log][" + nIndex_SystemLog.ToString();
            string strAllLog = "[AllLog][" + nIndex_AllLog.ToString();

            if ((e.nErrorCode == (int)XErrorCode.ERR_SUCCESS) && (e.nDeviceStatus == 1))
            {
                m_DebugLog.WLOGD("Connected...");
            }
            else
            {
                LIST_SYSTEM_LOG.Items.Add(strSystemLog + "] / [Device Connection Failed.]");
                LIST_ALL.Items.Add(strAllLog + "] / [Device Connection Failed.]");
                m_DebugLog.WLOGD("Disconnected...");
                return;
            }
            
            LIST_SYSTEM_LOG.Items.Add(strSystemLog + "] / [Device Connection Successed.]");
            LIST_ALL.Items.Add(strAllLog + "] / [Device Connection Successed.]");
            
            BTN_CONNECT.Enabled = false;
            BTN_DISCONNECT.Enabled = true;
            BTN_PLAY.Enabled = true;
            CHECKBOX_ALARM_BEEP_ON.Enabled = true;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // If the application has failed in non-blocking connection using 
        // ConnectNonBlock(), the OnConnectFailed event occurs. 
        // As Connect() returns an immediate error message if failed, 
        // it does not trigger this event.
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnConnectFailed(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEvent e)
        {
            m_DebugLog.WLOGD("OnConnectFailed() EVENT:: device_id=" + e.nDeviceID +
                ", error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
            
            nIndex_SystemLog++;
            nIndex_AllLog++;

            string strSystemLog = "[System Log][" + nIndex_SystemLog.ToString() + "] / [" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]";
            string strAllLog = "[AllLog][" + nIndex_AllLog.ToString() + "] / ["  + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]";

            LIST_SYSTEM_LOG.Items.Add(strSystemLog);
            LIST_ALL.Items.Add(strAllLog);
        }
    

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This event occurs if the application has failed to control the alarm-out.
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnAlarmOutControlFailed(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnAlarmOutControlFailedEvent e)
        {
            nIndex_Sensor++;
            nIndex_AllLog++;

            string strAlarm = "[Alarm][" + nIndex_Sensor.ToString() + "] / [" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]";
            string strAllLog = "[Alarm][" + nIndex_AllLog + "] / [" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]";
            
            LIST_ALARM.Items.Add(strAlarm);
            LIST_ALL.Items.Add(strAllLog);
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This events informs that a sensor-in (i.e., alarm-in) 
        // event occurs from the device.
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnSensorEvent(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnSensorEventEvent e)
        {
            PrintEventLog(e.tEventUTC, "Alarm");
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This event informs that a motion event occurs from the device.
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnMotionEvent(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnMotionEventEvent e)
        {
            PrintEventLog(e.tEventUTC, "Motion");
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This events informs that IV event occurs at device.
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnIvOccurEvent(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnIvOccurEventEvent e)
        {
            PrintEventLog(e.tEventUTC, "Inteligent Video");
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This event informs that a video loss event occurs from the device.
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnVideoLossEvent(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnVideoLossEventEvent e)
        {
            PrintEventLog(e.tEventUTC, "Video Loss");
        }


        //////////////////////////////////////////////////////////////////////////
        // Device Log

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This event occurs if a control module of DVR has been renamed.
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnControlRemoteNameChanged(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnControlRemoteNameChangedEvent e)
        {
            nIndex_DeviceLog++;
            nIndex_AllLog++;

            string strDeviceLog = "[Device Log][" + nIndex_DeviceLog.ToString() + "] / [Control module of DVR has been renamed.]";
            string strAllLog = "[Device Log][" + nIndex_AllLog.ToString() + "] / [Control module of DVR has been renamed.]";

            LIST_DEVICE_LOG.Items.Add(strDeviceLog);
            LIST_ALL.Items.Add(strAllLog);
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // If the control module is renamed in the local PC, 
        // the ActiveX object will trigger the OnControlLocalNameChanged event.
        // The event will also occur if the application tries to rename 
        // the control module using ChangeControlLocalName().
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnControlLocalNameChanged(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnControlLocalNameChangedEvent e)
        {
            nIndex_DeviceLog++;
            nIndex_AllLog++;

            string strDeviceLog = "[Device Log][" + nIndex_DeviceLog.ToString() + "] / [The control module is renamed in the local PC.]";
            string strAllLog = "[Device Log][" + nIndex_AllLog.ToString() + "] / [The control module is renamed in the local PC.]";

            LIST_DEVICE_LOG.Items.Add(strDeviceLog);
            LIST_ALL.Items.Add(strAllLog);
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This event occurs if a control module of DVR has been renamed.
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnControlStatusChanged(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnControlStatusChangedEvent e)
        {
            nIndex_DeviceLog++;
            nIndex_AllLog++;

            string strDeviceLog = "[Device Log][" + nIndex_DeviceLog.ToString() + "] / [The device status(or capability) changed.]";
            string strAllLog = "[Device Log][" + nIndex_AllLog.ToString() + "] / [The device status(or capability) changed.]";

            LIST_DEVICE_LOG.Items.Add(strDeviceLog);
            LIST_ALL.Items.Add(strAllLog);
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This event occurs if a control module of DVR has been renamed.
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnPasswordChanged(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnPasswordChangedEvent e)
        {
            nIndex_DeviceLog++;
            nIndex_AllLog++;

            string strDeviceLog = "[Device Log][" + nIndex_DeviceLog.ToString() + "] / [The password for DVR has changed.]";
            string strAllLog = "[Device Log][" + nIndex_AllLog.ToString() + "] / [The password for DVR has changed.]";

            LIST_DEVICE_LOG.Items.Add(strDeviceLog);
            LIST_ALL.Items.Add(strAllLog);
        }
    }
}
