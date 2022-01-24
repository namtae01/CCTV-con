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
// 
///////////////////////////////////////////////////////////////////////////////////
// @ File Name :		SingleLive.cs
// @ File Description : SingleLive Form Source Code File. 
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

namespace SingleLive
{
    enum SingleLive_ButtonStatus
    {
        SL_STATUS_CONNECTED = 0,
        SL_STATUS_DISCONNECTED,
        SL_STATUS_OPEN,
        SL_STATUS_CLOSE,
        SL_STATUS_START,
        SL_STATUS_STOP
    }
    public partial class SingleLiveDlg : Form
    {
        // Device Information
        private const string LOGIN_ID   = "admin";
        private const string PASSWORD   = "q1w2e3r4t5y6";
        private const string IP_ADDRESS = "192.168.217.225";
        private const string PORT_NUM   = "554";
        private const string HTTPPORT_NUM = "80";
        private const string MODEL_NAME = "Samsung NVR";

        private const int TRUE          = 1;
        private const int FALSE         = 0;
        private const int NULL          = 0;
        private const int XADDRESS_IP   = 1;

        private int hDevice             = 0;
        private int hMediaSource        = 0;
        private int nControlID          = 0;
        private int nError              = 0;
        private int nDeviceProtocol     = 0;
        private int nMediaProtocol      = 0;
        private bool bSupportedSnapi    = false;
        private DebugLog m_DebugLog     = null;
         
        public SingleLiveDlg()
        {
            InitializeComponent();
            m_DebugLog = new DebugLog(this.LIST_LOG);

        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Load Event.
        // -----------------------------------------------------------------------
        private void SingleLiveDlg_Load(object sender, EventArgs e)
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
            // ModelList ComboBox Setting.
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

            // Media Protocol List COmboBox Setting
            {
                COMBO_MPROTOCOLLIST.Items.Add("TCP");
                COMBO_MPROTOCOLLIST.Items.Add("UDP");
                COMBO_MPROTOCOLLIST.Items.Add("MULTICAST");
                COMBO_MPROTOCOLLIST.Items.Add("HTTP");
                COMBO_MPROTOCOLLIST.SelectedIndex = 0;
            }

            if ((System.String)COMBO_MODELLIST.SelectedItem == "Samsung Network Camera/Encoder" 
                || (System.String)COMBO_MODELLIST.SelectedItem == "Samsung NVR")
                bSupportedSnapi = true;
                
            // Set User Information Edit Box
            {
                EDIT_IP.Text    = IP_ADDRESS;
                EDIT_PORT.Text  = PORT_NUM;
                EDIT_HTTPPORT.Text = HTTPPORT_NUM;
                EDIT_ID.Text    = LOGIN_ID;
                EDIT_PW.Text    = PASSWORD;
            }
            setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_DISCONNECTED);
            SetProtocol();
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

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Sets the device information so that the application can connect 
            // to the device.
            // -----------------------------------------------------------------------
            SetProtocol();
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
                nMediaProtocol);             

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
                FALSE,              // [in] Flag to decide where to forcibly log in or not.
                FALSE);             // [in] When the device is disconnected, you can use this flag to decide
                                    //      if to connect again automatically. If this value is 1, try to connect again.
            m_DebugLog.WLOGD("ConnectNonBlock():: ", nError, axXnsSdkDevice.GetErrorString(nError));

            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("ConnectNonBlock() fail: errno=[%d](%s)\n",
                    nError, axXnsSdkDevice.GetErrorString(nError));
                setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_DISCONNECTED);
            }
            else
            {
                m_DebugLog.WLOGD("ConnectNonBlock():: ", nError, axXnsSdkDevice.GetErrorString(nError));
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
                setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_DISCONNECTED);
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Media Open Function.
        // ----------------------------------------------------------------------- 
        private void BTN_MEDIAOPEN_Click(object sender, EventArgs e)
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
            //
            // < DVR/NVR control module structure >
            // +------------------------------------------------------------
            // Control Module(Device, 1) ----------------- Control ID : 1
            // |---- Control Module(Camera, 1) ----------- Control ID : 2
            // |---- Control Module(Camera, 2) ----------- Control ID : 3
            // |---- Control Module(Camera, 3) ----------- Control ID : 4
            // |---- ....
            // |---- Control Module(Camera,16) ----------- Control ID : 17
            // |---- Control Module(Sensor-in, 1) -------- Control ID : 18
            // |---- ...
            // |---- Control Module(Sensor-in, 16) ------- Control ID : 34
            // |---- Control Module(Digital-out, 1) ------ Control ID : 35
            // |---- ...
            // |---- Control Module(Digital-out, 4) ------ Control ID : 38
            // +------------------------------------------------------------
            //
            // < Network Camera control module structure >
            // +------------------------------------------------------------
            // Control Module(Device, 1) ----------------- Control ID : 1
            // |---- Control Module(Camera, 1) ----------- Control ID : 2
            //       |--- Control Module(Video, 1) ------- Control ID : 3
            //       |--- Control Module(Video, 2) ------- Control ID : 4
            //       |--- ...
            //       |--- Control Module(Video, 10) ------ Control ID : 12
            //       |--- Control Module(Sensor-in, 1) --- Control ID : 13
            //       |--- Control Module(Digital-out, 1) - Control ID : 14
            // +------------------------------------------------------------
            //
            //< MultiProfile DVR/NVR control module structure >
            // +------------------------------------------------------------
            // Control Module(Device, 1) ----------------- Control ID : 1
            // |---- Control Module(Camera, 1) ----------- Control ID : 2
            //       |--- Control Module(Video, 1) ------- Control ID : 3
            //       |--- ...
            // |---- Control Module(Camera, 2) ----------- Control ID : 
            //       |--- Control Module(Video, 1) ------- Control ID : 
            //       |--- ...
            // |---- ...
            // |---- Control Module(Sensor-in, 16) ------- Control ID : 
            // |---- Control Module(Digital-out, 1) ---D:\SVN\ActiveX_SDK\source\Sample\C#_WPF\SingleLive\DebugLog.cs--- Control ID : 
            // |---- ...
            // |---- Control Module(Digital-out, 4) ------ Control ID : 	
            // +------------------------------------------------------------ 
            //
            // -----------------------------------------------------------------------
            nControlID = axXnsSdkDevice.GetVideoControlID(hDevice, COMBO_CHANNEL.SelectedIndex + 1, COMBO_PROFILE.SelectedIndex + 1);
            
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
            if (axXnsSdkDevice.OpenMedia(hDevice, nControlID, (int)XMediaType.XMEDIA_LIVE, 0, 0, ref hMediaSource) == (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGW("Open media...control id=["+nControlID+"]\n");
                setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_OPEN);
                return;
            }


                       
                    
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Media Close Function.
        // ----------------------------------------------------------------------- 
        private void BTN_MEDIACLOSE_Click(object sender, EventArgs e)
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
                    setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_CLOSE);
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
        // for Start Function.
        // ----------------------------------------------------------------------- 
        private void BTN_START_Click(object sender, EventArgs e)
        {
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
                    setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_START);
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
            if (hMediaSource != NULL)
            {
                m_DebugLog.WLOGW("Media Play Stopped.");
                setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_STOP);
            }
        }

        // Control button enable/disable
        void setBtnStatus(SingleLive_ButtonStatus nStatus)
        {
            bool conn = false, disconn = false, start = false, stop = false, close = false, open = false, channel=false, profile=false;
            switch (nStatus)
            {
                case SingleLive_ButtonStatus.SL_STATUS_CONNECTED:
                    disconn = true;
                    open = true;
                    channel = true;
                    profile = true;
                    break;
                case SingleLive_ButtonStatus.SL_STATUS_DISCONNECTED:
                    conn = true;
                    break;
                case SingleLive_ButtonStatus.SL_STATUS_OPEN:
                    disconn = true;
                    close = true;
                    start = true;
                    break;
                case SingleLive_ButtonStatus.SL_STATUS_CLOSE:
                    disconn = true;
                    open = true;
                    channel = true;
                    profile = true;
                    break;
                case SingleLive_ButtonStatus.SL_STATUS_START:
                    disconn = true;
                    close = true;
                    stop = true;
                    break;
                case SingleLive_ButtonStatus.SL_STATUS_STOP:
                    disconn = true;
                    close = true;
                    start = true;
                    break;
            }

            Button_Connect.Enabled = conn;
            COMBO_MODELLIST.Enabled = conn;
            EDIT_IP.Enabled = conn;
            EDIT_ID.Enabled = conn;
            EDIT_PW.Enabled = conn;
            EDIT_PORT.Enabled = conn;
            EDIT_HTTPPORT.Enabled = conn;
            CHECKBOX_SUNAPI.Enabled = conn;
            COMBO_MPROTOCOLLIST.Enabled = conn;

            Button_Disconnect.Enabled = disconn;
            Button_Media_Open.Enabled = open;
            Button_Media_Close.Enabled = close;
            Button_Start.Enabled = start;
            Button_Stop.Enabled = stop;
            COMBO_CHANNEL.Enabled = channel;
            COMBO_PROFILE.Enabled = profile;
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
            if ((e.nErrorCode == (int)XErrorCode.ERR_SUCCESS) && (e.nDeviceStatus == 1))
            {                
                COMBO_CHANNEL.Items.Clear();
                int nChannelCount = axXnsSdkDevice.GetControlCount(hDevice, (int)XModelType.XCTL_CAMERA);
               // String ChannelIndex;
                for (int i = 1; i <= nChannelCount; ++i)
                {
                    COMBO_CHANNEL.Items.Add(i);
                }
                COMBO_CHANNEL.SelectedIndex = 0;

                COMBO_PROFILE.Items.Clear();
                int nProfileCount = axXnsSdkDevice.GetControlCount(hDevice, (int)XModelType.XCTL_VIDEO) / nChannelCount;
               // CString ProfileIndex;
                for (int i = 1; i <= nProfileCount; ++i)
                {
                    COMBO_PROFILE.Items.Add(i);
                }

                m_DebugLog.WLOGD("Connected...");
                setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_CONNECTED);
                if (nProfileCount != 0)
                    COMBO_PROFILE.SelectedIndex = 0;
                else
                    COMBO_PROFILE.Enabled=false;
            }
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

        private void COMBO_MODELLIST_SelectedIndexChanged(object sender, EventArgs e)
        {
            if ((System.String)COMBO_MODELLIST.SelectedItem == "Samsung Network Camera/Encoder" || (System.String)COMBO_MODELLIST.SelectedItem == "Samsung NVR")
            {
                bSupportedSnapi = true;
            }
            else
            {
                bSupportedSnapi = false;
            }
            SetProtocol();
        }

        private void CHECKBOX_SUNAPI_CheckedChanged(object sender, EventArgs e)
        {
            SetProtocol();
        }

        private void SetProtocol()
        {
            CHECKBOX_SUNAPI.Enabled = false;
            COMBO_MPROTOCOLLIST.Enabled = false;
            nDeviceProtocol = 0;
            nMediaProtocol = 0;

            if (bSupportedSnapi == true)
            {
                CHECKBOX_SUNAPI.Enabled = true;
                if (CHECKBOX_SUNAPI.Checked == true)
                {
                    nDeviceProtocol = (int)XDeviceProtocolType.XDEVICE_PROTOCOL_SUNAPI;
                    COMBO_MPROTOCOLLIST.Enabled = true;
                    switch ((System.String)COMBO_MPROTOCOLLIST.SelectedItem)
                    {
                        case "TCP":
                            nMediaProtocol = (int)XMediaProtocolType.XMEDIA_PROTOCOL_TCP;
                            break;
                        case "UDP":
                            nMediaProtocol = (int)XMediaProtocolType.XMEDIA_PROTOCOL_UDP;
                            break;
                        case "MULTICAST":
                            nMediaProtocol = (int)XMediaProtocolType.XMEDIA_PROTOCOL_MULTICAST;
                            break;
                        case "HTTP":
                            nMediaProtocol = (int)XMediaProtocolType.XMEDIA_PROTOCOL_TCP_HTTP;
                            break;
                    }
                }
            }
        }
    }
}
