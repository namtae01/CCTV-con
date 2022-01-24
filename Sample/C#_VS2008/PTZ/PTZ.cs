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
// @ File Name :		PTZ.cs
// @ File Description : PTZ Form Source Code File. 
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

// Using List 
using System.Collections;
using System.Diagnostics;

// Define XNS Control.
using XNSSDKWINDOWLib;
using XNSSDKDEVICELib;
// Define XNS Sample Log
using XNSSAMPLELOGLib;

namespace PTZ
{
    public partial class PTZDlg : Form
    {
        // Device Information
        private const string LOGIN_ID = "admin";
        private const string PASSWORD = "4321";
        private const string IP_ADDRESS = "192.168.103.8";
        private const string PORT_NUM = "4520";
        private const string MODEL_NAME = "SPE-100";

        // struct Preset Information.
        public struct PresetInfo
        {
            public int nIndex;
            public string strName;
        }

        public List<PresetInfo> listPreset = new List<PresetInfo>();

        private const int TRUE        = 1;
        private const int FALSE       = 0;
        private const int NULL        = 0;
        private const int XADDRESS_IP = 1;
        private const int MAX_DEVICE  = 3000;
        private const int PTZ_SPEED   = 50;

        public  int hDevice           = 0;
        public  int hMediaSource      = 0;
        public  int nControlID        = 0;
        private int nPtzSpeed         = 0;
        private int nStartX           = 0;
        private int nStartY           = 0;
        private int nEndX             = 0;
        private int nEndY             = 0;
        private int nPan              = 0;
        private int nTilt             = 0;
        private int nZoom             = 0;
        private int nSpeed            = 0;

        private bool bMouseDown       = false;

        private int nError = 0;

        private const int ERR_TALK_ALREADY_USE = 0x000000c2;
        public DebugLog m_DebugLog = null;

        public PTZDlg()
        {
            InitializeComponent();
            m_DebugLog = new DebugLog(this.LIST_LOG);
        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Load Event.
        // -----------------------------------------------------------------------
        private void PTZDlg_Load(object sender, EventArgs e)
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
                EDIT_IP.Text = IP_ADDRESS;
                EDIT_PORT.Text = PORT_NUM;
                EDIT_ID.Text = LOGIN_ID;
                EDIT_PW.Text = PASSWORD;
            }

            // Set Dialog Enable
            {
                BTN_DISCONNECT.Enabled = false;
                BTN_MEDIAOPEN.Enabled = false;
                BTN_MEDIACLOSE.Enabled = false;
                BTN_START.Enabled = false;
                BTN_STOP.Enabled = false;

                BTN_UP.Enabled = false;
                BTN_RIGHT.Enabled = false;
                BTN_DOWN.Enabled = false;
                BTN_LEFT.Enabled = false;
                BTN_ENTER.Enabled = false;
                BTN_CANCEL.Enabled = false;
                CHECK_MENU.Enabled = false;
                COMBO_SCAN.Enabled = false;
                COMBO_AUTOPAN.Enabled = false;
                BTN_PRESET.Enabled = false;
                CHECK_AREAZOOM.Enabled = false;
                BTN_ZOOM1X.Enabled = false;
                BTN_GETPTZ.Enabled = false;
                BTN_SETPTZ.Enabled = false;
                BTN_PTZ_UP.Enabled = false;
                BTN_PTZ_UPRIGHT.Enabled = false;
                BTN_PTZ_RIGHT.Enabled = false;
                BTN_PTZ_DOWNRIGHT.Enabled = false;
                BTN_PTZ_DOWN.Enabled = false;
                BTN_PTZ_DOWNLEFT.Enabled = false;
                BTN_PTZ_LEFT.Enabled = false;
                BTN_PTZ_UPLEFT.Enabled = false;
                BTN_PTZ_STOP.Enabled = false;
                BTN_PTZ_ZOOMIN.Enabled = false;
                BTN_PTZ_ZOOMOUT.Enabled = false;
                TRACKBAR_PTZ_SPEED.Enabled = false;
            }

            COMBO_SCAN.SelectedIndex = 0;
            COMBO_AUTOPAN.SelectedIndex = 0;
            
            nPtzSpeed = PTZ_SPEED;
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
                FALSE,              // [in] Flag to decide where to forcibly log in or not.
                FALSE);             // [in] When the device is disconnected, you can use this flag to decide
                                    //      if to connect again automatically. If this value is 1, try to connect again.
            m_DebugLog.WLOGD("ConnectNonBlock():: ", nError, axXnsSdkDevice.GetErrorString(nError));

            if (nError == (int)XErrorCode.ERR_SUCCESS)
            {
                BTN_CONNECT.Enabled = false;
                BTN_DISCONNECT.Enabled = true;
                BTN_MEDIAOPEN.Enabled = true;
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

                BTN_CONNECT.Enabled = true;
                BTN_DISCONNECT.Enabled = false;
                BTN_MEDIAOPEN.Enabled = false;
                BTN_MEDIACLOSE.Enabled = false;
                BTN_START.Enabled = false;
                BTN_STOP.Enabled = false;

                BTN_UP.Enabled = false;
                BTN_RIGHT.Enabled = false;
                BTN_DOWN.Enabled = false;
                BTN_LEFT.Enabled = false;
                BTN_ENTER.Enabled = false;
                BTN_CANCEL.Enabled = false;
                CHECK_MENU.Enabled = false;
                COMBO_SCAN.Enabled = false;
                COMBO_AUTOPAN.Enabled = false;
                BTN_PRESET.Enabled = false;
                CHECK_AREAZOOM.Enabled = false;
                BTN_ZOOM1X.Enabled = false;
                BTN_GETPTZ.Enabled = false;
                BTN_SETPTZ.Enabled = false;
                BTN_PTZ_UP.Enabled = false;
                BTN_PTZ_UPRIGHT.Enabled = false;
                BTN_PTZ_RIGHT.Enabled = false;
                BTN_PTZ_DOWNRIGHT.Enabled = false;
                BTN_PTZ_DOWN.Enabled = false;
                BTN_PTZ_DOWNLEFT.Enabled = false;
                BTN_PTZ_LEFT.Enabled = false;
                BTN_PTZ_UPLEFT.Enabled = false;
                BTN_PTZ_STOP.Enabled = false;
                BTN_PTZ_ZOOMIN.Enabled = false;
                BTN_PTZ_ZOOMOUT.Enabled = false;
                TRACKBAR_PTZ_SPEED.Enabled = false;
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
                            BTN_MEDIAOPEN.Enabled = false;
                            BTN_MEDIACLOSE.Enabled = true;
                            BTN_START.Enabled = true;
                            BTN_STOP.Enabled = false;
                            nControlID = i + 2;
                        }
                        else
                        {
                            m_DebugLog.WLOGD("Media Open Failed.ret=" + nError.ToString() + "[" + axXnsSdkDevice.GetErrorString(nError) + "]");
                        }
                        return;
                    }
                }
            }
            // Control Module : Network Camera or Encoder Box (video Server)
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
                            BTN_MEDIAOPEN.Enabled = false;
                            BTN_MEDIACLOSE.Enabled = true;
                            BTN_START.Enabled = true;
                            BTN_STOP.Enabled = false;
                            nControlID = i + 3;
                        }
                        else
                        {
                            m_DebugLog.WLOGD("Media Open Failed.ret=" + nError + "[" + axXnsSdkDevice.GetErrorString(nError) + "]");
                        }
                        return;
                    }
                }
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
                    BTN_MEDIAOPEN.Enabled = true;
                    BTN_MEDIACLOSE.Enabled = false;
                    BTN_START.Enabled = false;
                    BTN_STOP.Enabled = false;

                    BTN_UP.Enabled = false;
                    BTN_RIGHT.Enabled = false;
                    BTN_DOWN.Enabled = false;
                    BTN_LEFT.Enabled = false;
                    BTN_ENTER.Enabled = false;
                    BTN_CANCEL.Enabled = false;
                    CHECK_MENU.Enabled = false;
                    COMBO_SCAN.Enabled = false;
                    COMBO_AUTOPAN.Enabled = false;
                    BTN_PRESET.Enabled = false;
                    CHECK_AREAZOOM.Enabled = false;
                    BTN_ZOOM1X.Enabled = false;
                    BTN_GETPTZ.Enabled = false;
                    BTN_SETPTZ.Enabled = false;
                    BTN_PTZ_UP.Enabled = false;
                    BTN_PTZ_UPRIGHT.Enabled = false;
                    BTN_PTZ_RIGHT.Enabled = false;
                    BTN_PTZ_DOWNRIGHT.Enabled = false;
                    BTN_PTZ_DOWN.Enabled = false;
                    BTN_PTZ_DOWNLEFT.Enabled = false;
                    BTN_PTZ_LEFT.Enabled = false;
                    BTN_PTZ_UPLEFT.Enabled = false;
                    BTN_PTZ_STOP.Enabled = false;
                    BTN_PTZ_ZOOMIN.Enabled = false;
                    BTN_PTZ_ZOOMOUT.Enabled = false;
                    TRACKBAR_PTZ_SPEED.Enabled = false;
                    
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
                    BTN_START.Enabled = false;
                    BTN_STOP.Enabled = true;

                    BTN_UP.Enabled = true;
                    BTN_RIGHT.Enabled = true;
                    BTN_DOWN.Enabled = true;
                    BTN_LEFT.Enabled = true;
                    BTN_ENTER.Enabled = true;
                    BTN_CANCEL.Enabled = true;
                    CHECK_MENU.Enabled = true;
                    COMBO_SCAN.Enabled = true;
                    COMBO_AUTOPAN.Enabled = true;
                    BTN_PRESET.Enabled = true;
                    CHECK_AREAZOOM.Enabled = true;
                    BTN_ZOOM1X.Enabled = true;
                    BTN_GETPTZ.Enabled = true;
                    BTN_SETPTZ.Enabled = true;
                    BTN_PTZ_UP.Enabled = true;
                    BTN_PTZ_UPRIGHT.Enabled = true;
                    BTN_PTZ_RIGHT.Enabled = true;
                    BTN_PTZ_DOWNRIGHT.Enabled = true;
                    BTN_PTZ_DOWN.Enabled = true;
                    BTN_PTZ_DOWNLEFT.Enabled = true;
                    BTN_PTZ_LEFT.Enabled = true;
                    BTN_PTZ_UPLEFT.Enabled = true;
                    BTN_PTZ_STOP.Enabled = true;
                    BTN_PTZ_ZOOMIN.Enabled = true;
                    BTN_PTZ_ZOOMOUT.Enabled = true;
                    TRACKBAR_PTZ_SPEED.Enabled = true;

                    COMBO_SCAN.SelectedIndex = 0;
                    COMBO_AUTOPAN.SelectedIndex = 0;
                    TRACKBAR_PTZ_SPEED.Value = 50;
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
                BTN_START.Enabled = true;
                BTN_STOP.Enabled = false;
                BTN_MEDIACLOSE.Enabled = true;

                BTN_UP.Enabled = false;
                BTN_RIGHT.Enabled = false;
                BTN_DOWN.Enabled = false;
                BTN_LEFT.Enabled = false;
                BTN_ENTER.Enabled = false;
                BTN_CANCEL.Enabled = false;
                CHECK_MENU.Enabled = false;
                COMBO_SCAN.Enabled = false;
                COMBO_AUTOPAN.Enabled = false;
                BTN_PRESET.Enabled = false;
                CHECK_AREAZOOM.Enabled = false;
                BTN_ZOOM1X.Enabled = false;
                BTN_GETPTZ.Enabled = false;
                BTN_SETPTZ.Enabled = false;
                BTN_PTZ_UP.Enabled = false;
                BTN_PTZ_UPRIGHT.Enabled = false;
                BTN_PTZ_RIGHT.Enabled = false;
                BTN_PTZ_DOWNRIGHT.Enabled = false;
                BTN_PTZ_DOWN.Enabled = false;
                BTN_PTZ_DOWNLEFT.Enabled = false;
                BTN_PTZ_LEFT.Enabled = false;
                BTN_PTZ_UPLEFT.Enabled = false;
                BTN_PTZ_STOP.Enabled = false;
                BTN_PTZ_ZOOMIN.Enabled = false;
                BTN_PTZ_ZOOMOUT.Enabled = false;
                TRACKBAR_PTZ_SPEED.Enabled = false;

                m_DebugLog.WLOGW("Media Play Stopped.");
            }
        }


        // -------------------------------- PTZ control Button Click.
        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ move Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PTZ_UPLEFT_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module. 
            // Return True : Device capability support. (False : Not support)
            // -----------------------------------------------------------------------
            int bIsCap = axXnsSdkDevice.GetControlCapability(hDevice, (int)XPTZControl.XPTZ_UPLEFT, (int)XUnitCap.XCTL_CAP_PTZ_SPEED);
            m_DebugLog.WLOGD("GetControlCapability() :", bIsCap, axXnsSdkDevice.GetErrorString(bIsCap));


            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Moves the camera to the predefined PTZ position. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlPtz(hDevice, nControlID, (int)XPTZControl.XPTZ_UPLEFT, nPtzSpeed);
            m_DebugLog.WLOGD("[Message] Move UpLeft !", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ move Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PTZ_UP_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module. 
            // Return True : Device capability support. (False : Not support)
            // -----------------------------------------------------------------------
            int bIsCap = axXnsSdkDevice.GetControlCapability(hDevice, (int)XPTZControl.XPTZ_UP, (int)XUnitCap.XCTL_CAP_PTZ_SPEED);
            m_DebugLog.WLOGD("GetControlCapability() :", bIsCap, axXnsSdkDevice.GetErrorString(bIsCap));


            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Moves the camera to the predefined PTZ position. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlPtz(hDevice, nControlID, (int)XPTZControl.XPTZ_UP, nPtzSpeed);
            m_DebugLog.WLOGD("[Message] Move Up !", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ move Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PTZ_UPRIGHT_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module. 
            // Return True : Device capability support. (False : Not support)
            // -----------------------------------------------------------------------
            int bIsCap = axXnsSdkDevice.GetControlCapability(hDevice, (int)XPTZControl.XPTZ_UPRIGHT, (int)XUnitCap.XCTL_CAP_PTZ_SPEED);
            m_DebugLog.WLOGD("GetControlCapability() :", bIsCap, axXnsSdkDevice.GetErrorString(bIsCap));


            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Moves the camera to the predefined PTZ position. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlPtz(hDevice, nControlID, (int)XPTZControl.XPTZ_UPRIGHT, nPtzSpeed);
            m_DebugLog.WLOGD("[Message] Move UpRight !", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ move Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PTZ_LEFT_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module. 
            // Return True : Device capability support. (False : Not support)
            // -----------------------------------------------------------------------
            int bIsCap = axXnsSdkDevice.GetControlCapability(hDevice, (int)XPTZControl.XPTZ_LEFT, (int)XUnitCap.XCTL_CAP_PTZ_SPEED);
            m_DebugLog.WLOGD("GetControlCapability() :", bIsCap, axXnsSdkDevice.GetErrorString(bIsCap));


            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Moves the camera to the predefined PTZ position. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlPtz(hDevice, nControlID, (int)XPTZControl.XPTZ_LEFT, nPtzSpeed);
            m_DebugLog.WLOGD("[Message] Move Left !", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ move Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PTZ_RIGHT_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module. 
            // Return True : Device capability support. (False : Not support)
            // -----------------------------------------------------------------------
            int bIsCap = axXnsSdkDevice.GetControlCapability(hDevice, (int)XPTZControl.XPTZ_RIGHT, (int)XUnitCap.XCTL_CAP_PTZ_SPEED);
            m_DebugLog.WLOGD("GetControlCapability() :", bIsCap, axXnsSdkDevice.GetErrorString(bIsCap));


            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Moves the camera to the predefined PTZ position. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlPtz(hDevice, nControlID, (int)XPTZControl.XPTZ_RIGHT, nPtzSpeed);
            m_DebugLog.WLOGD("[Message] Move Right !", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ move Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PTZ_DOWNLEFT_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module. 
            // Return True : Device capability support. (False : Not support)
            // -----------------------------------------------------------------------
            int bIsCap = axXnsSdkDevice.GetControlCapability(hDevice, (int)XPTZControl.XPTZ_DOWNLEFT, (int)XUnitCap.XCTL_CAP_PTZ_SPEED);
            m_DebugLog.WLOGD("GetControlCapability() :", bIsCap, axXnsSdkDevice.GetErrorString(bIsCap));


            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Moves the camera to the predefined PTZ position. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlPtz(hDevice, nControlID, (int)XPTZControl.XPTZ_DOWNLEFT, nPtzSpeed);
            m_DebugLog.WLOGD("[Message] Move DownLeft !", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ move Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PTZ_DOWN_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module. 
            // Return True : Device capability support. (False : Not support)
            // -----------------------------------------------------------------------
            int bIsCap = axXnsSdkDevice.GetControlCapability(hDevice, (int)XPTZControl.XPTZ_DOWN, (int)XUnitCap.XCTL_CAP_PTZ_SPEED);
            m_DebugLog.WLOGD("GetControlCapability() :", bIsCap, axXnsSdkDevice.GetErrorString(bIsCap));


            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Moves the camera to the predefined PTZ position. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlPtz(hDevice, nControlID, (int)XPTZControl.XPTZ_DOWN, nPtzSpeed);
            m_DebugLog.WLOGD("[Message] Move Down !", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ move Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PTZ_DOWNRIGHT_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module. 
            // Return True : Device capability support. (False : Not support)
            // -----------------------------------------------------------------------
            int bIsCap = axXnsSdkDevice.GetControlCapability(hDevice, (int)XPTZControl.XPTZ_DOWNRIGHT, (int)XUnitCap.XCTL_CAP_PTZ_SPEED);
            m_DebugLog.WLOGD("GetControlCapability() :", bIsCap, axXnsSdkDevice.GetErrorString(bIsCap));


            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Moves the camera to the predefined PTZ position. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlPtz(hDevice, nControlID, (int)XPTZControl.XPTZ_DOWNRIGHT, nPtzSpeed);
            m_DebugLog.WLOGD("[Message] Move DownRight !", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ move Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PTZ_STOP_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module. 
            // Return True : Device capability support. (False : Not support)
            // -----------------------------------------------------------------------
            int bIsCap = axXnsSdkDevice.GetControlCapability(hDevice, (int)XPTZControl.XPTZ_STOP, (int)XUnitCap.XCTL_CAP_PTZ_SPEED);
            m_DebugLog.WLOGD("GetControlCapability() :", bIsCap, axXnsSdkDevice.GetErrorString(bIsCap));


            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Moves the camera to the predefined PTZ position. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlPtz(hDevice, nControlID, (int)XPTZControl.XPTZ_STOP, nPtzSpeed);
            m_DebugLog.WLOGD("[Message] Move Stop !", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ Zoom Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PTZ_ZOOMIN_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module. 
            // Return True : Device capability support. (False : Not support)
            // -----------------------------------------------------------------------
            int bIsCap = axXnsSdkDevice.GetControlCapability(hDevice, (int)XPTZControl.XPTZ_ZOOMIN, (int)XUnitCap.XCTL_CAP_PTZ_SPEED);
            m_DebugLog.WLOGD("GetControlCapability() :", bIsCap, axXnsSdkDevice.GetErrorString(bIsCap));


            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Moves the camera to the predefined PTZ position. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlPtz(hDevice, nControlID, (int)XPTZControl.XPTZ_ZOOMIN, nPtzSpeed);
            m_DebugLog.WLOGD("[Message] Move ZoomIn !", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ Zoom Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PTZ_ZOOMOUT_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module. 
            // Return True : Device capability support. (False : Not support)
            // -----------------------------------------------------------------------
            int bIsCap = axXnsSdkDevice.GetControlCapability(
                hDevice,                                    // [in] Device handle. This value is returned from CreateDevice().
                (int)XPTZControl.XPTZ_ZOOMOUT,              // [in] Control ID.
                (int)XUnitCap.XCTL_CAP_PTZ_SPEED);          // [in] Capability ID.
            m_DebugLog.WLOGD("GetControlCapability() :", bIsCap, axXnsSdkDevice.GetErrorString(bIsCap));


            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Moves the camera to the predefined PTZ position. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlPtz(
                hDevice,                        // [in] Device handle. This value is returned from CreateDevice().
                nControlID,                     // [in] Control ID.
                (int)XPTZControl.XPTZ_ZOOMOUT,  // [in] PTZ command.
                nPtzSpeed);                     // [in] If nPtzCommand is a speed-related command, this value indicates the PTZ operation speed.
            m_DebugLog.WLOGD("[Message] Move ZoomOut !", nError, axXnsSdkDevice.GetErrorString(nError));
        }
        

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ Zoom Function.
        // ----------------------------------------------------------------------- 
        private void BTN_ZOOM1X_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Performs the zoom-1x. This function is valid as long as the application 
            // is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.Zoom1X(
                hDevice,                    // [in] Device handle. This value is returned from CreateDevice(). 
                nControlID);                // [in] Control ID.
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("AreaZoom() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Get PTZ Setting value.
        // ----------------------------------------------------------------------- 
        private void BTN_GETPTZ_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns an absolute coordinate of the camera, is available when 
            // application receives media stream from the camera. 
            // The value themselves could be read by using OnGetPtzPos event handler. 
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.GetPtzPos(
                hDevice,                    // [in] Device handle. This value is returned from CreateDevice().
                nControlID);                // [in] Control ID.
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("GetPtzPos() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ Setting value.
        // ----------------------------------------------------------------------- 
        private void BTN_SETPTZ_Click(object sender, EventArgs e)
        {
            nPan = Convert.ToInt32(EDIT_PTZ_PAN.Text);
            nTilt = Convert.ToInt32(EDIT_PTZ_TILT.Text);
            nZoom = Convert.ToInt32(EDIT_PTZ_ZOOM.Text);

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Change the absolute coordinate of the camera, 
            // is available when application receives media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.SetPtzPos(
                            hDevice,                    // [in] Device handle. This value is returned from CreateDevice(). 
                            nControlID,                 // [in] Control ID.
                            nPan,                       // [in] absolute coordinate of Pan.
                            nTilt,                      // [in] absolute coordinate of Tilt.
                            nZoom);                     // [in] absolute coordinate of Zoom.

            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("SetPtzPos() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm TracBar control Event.
        // for PTZ speed setting value.
        // ----------------------------------------------------------------------- 
        private void TRACKBAR_PTZ_SPEED_MouseCaptureChanged(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Moves the camera to the predefined PTZ position. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlPtz(hDevice, nControlID, (int)XPTZControl.XPTZ_STOP, nPtzSpeed);
            
            nPtzSpeed = TRACKBAR_PTZ_SPEED.Value;
            m_DebugLog.WLOGD("Chenged PTZ Spped = " + nPtzSpeed);
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ Area zoom setting.
        // ----------------------------------------------------------------------- 
        private void CHECK_AREAZOOM_CheckedChanged(object sender, EventArgs e)
        {
            if (CHECK_AREAZOOM.Checked == true)
            {
                m_DebugLog.WLOGD("AreaZoom : TRUE");
            }
            else
            {
                m_DebugLog.WLOGD("AreaZoom : FALSE");
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ Area zoom setting.
        // ----------------------------------------------------------------------- 
        private void COMBO_SCAN_SelectedIndexChanged(object sender, EventArgs e)
        {
            int nIndex = COMBO_SCAN.SelectedIndex;
            if (nIndex == NULL)
            {
                return;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Performs operations of Preset, Autopan, Scan and Pattern. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // // Camera operations : XHPTZ_SCAN(3) - Scan
            // ----------------------------------------------------------------------- 
            nError = axXnsSdkDevice.ExecuteHPtz(
                hDevice,                        // [in] Device handle. This value is returned from CreateDevice().
                nControlID,                     // [in] Control ID.
                (int)XHPTZFunction.XHPTZ_SCAN,  //[in] Camera operations.
                nIndex);                        // [in] Index of camera's list of features (Preset, AutoPan, Scan, Pattern).
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("ExecuteHPtz() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                COMBO_SCAN.SelectedIndex = 0;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ Area zoom setting.
        // ----------------------------------------------------------------------- 
        private void COMBO_AUTOPAN_SelectedIndexChanged(object sender, EventArgs e)
        {
            int nIndex = COMBO_AUTOPAN.SelectedIndex;
            if (nIndex == NULL)
            {
                return;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Performs operations of Preset, Autopan, Scan and Pattern. 
            // This function is valid as long as the application is receiving media stream from the camera.
            // Camera operations : XHPTZ_AUTOPAN(2) - Autopan(Swing)
            // ----------------------------------------------------------------------- 
            nError = axXnsSdkDevice.ExecuteHPtz(
                hDevice,                            // [in] Device handle. This value is returned from CreateDevice().
                nControlID,                         // [in] Control ID.
                (int)XHPTZFunction.XHPTZ_AUTOPAN,   // [in] Camera operations.
                nIndex);                            // [in] Index of camera's list of features (Preset, AutoPan, Scan, Pattern).

            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("ExecuteHPtz() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                COMBO_AUTOPAN.SelectedIndex = 0;
                return;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for PTZ Preset.
        // ----------------------------------------------------------------------- 
        private void BTN_PRESET_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Gets the preset list. A preset is a user-defined position of the camera. 
            // The number of presets available varies depending on the model. 
            // However, the XNS ActiveX library can support up to 20 presets. 
            // The result of this function will be forwarded by the OnGetPresetList event.
            // This function is valid as long as the application 
            // is receiving media stream from the camera.
            // ----------------------------------------------------------------------- 
            nError = axXnsSdkDevice.GetPresetList(
                hDevice,                            // [in] Device handle. This value is returned from CreateDevice().
                nControlID);                        // [in] Control ID.
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("GetPresetList() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                COMBO_AUTOPAN.SelectedIndex = 0;
                return;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Check Button Event.
        // PTZ OSD Menu.
        // ----------------------------------------------------------------------- 
        private void CHECK_MENU_CheckedChanged(object sender, EventArgs e)
        {
            int nMenu = 0; 

            if (CHECK_MENU.Checked == false)
            {
                nMenu = (int)XPTZMenu.XMENU_OFF;
                m_DebugLog.WLOGD("OSD Menu : FALSE");
            }
            else
            {
                nMenu = (int)XPTZMenu.XMENU_ON;
                m_DebugLog.WLOGD("OSD Menu : TRUE");
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the capabilities of the control module. 
            // Return True : Device capability support. (False : Not support)
            // -----------------------------------------------------------------------
            int bIsCap = axXnsSdkDevice.GetControlCapability(
                hDevice,                                    // [in] Device handle. This value is returned from CreateDevice().
                nControlID,                                 // [in] Control ID.
                (int)XUnitCap.XCTL_CAP_CAM_MENU);           // [in] Capability ID.

            m_DebugLog.WLOGD("GetControlCapability() :", bIsCap, axXnsSdkDevice.GetErrorString(bIsCap));

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
            nError = axXnsSdkDevice.ControlMenu(
                hDevice,                        // [in] Device handle. This value is returned from CreateDevice().
                nControlID,                     // [in] Control ID.
                nMenu);                         // [in] Command to control the OSD menus.
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("ControlMenu() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // PTZ OSD Menu : Enter.
        // ----------------------------------------------------------------------- 
        private void BTN_ENTER_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Controls the OSD menus of the camera. This function is valid as long 
            // as the application is receiving media stream from the camera.(ex.SND-5080)
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlMenu(
                hDevice,                        // [in] Device handle. This value is returned from CreateDevice().
                nControlID,                     // [in] Control ID.
                (int)XPTZMenu.XMENU_ENTER);     // [in] Command to control the OSD menus.
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("ControlMenu() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // PTZ OSD Menu : Cancel.
        // ----------------------------------------------------------------------- 
        private void BTN_CANCEL_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Controls the OSD menus of the camera. This function is valid as long 
            // as the application is receiving media stream from the camera.(ex.SND-5080)
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlMenu(
                hDevice,                        // [in] Device handle. This value is returned from CreateDevice().
                nControlID,                     // [in] Control ID.
                (int)XPTZMenu.XMENU_CANCEL);    // [in] Command to control the OSD menus.
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("ControlMenu() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // PTZ OSD Menu : UP.
        // ----------------------------------------------------------------------- 
        private void BTN_UP_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Controls the OSD menus of the camera. This function is valid as long 
            // as the application is receiving media stream from the camera.(ex.SND-5080)
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlMenu(
                hDevice,                        // [in] Device handle. This value is returned from CreateDevice().
                nControlID,                     // [in] Control ID.
                (int)XPTZMenu.XMENU_UP);        // [in] Command to control the OSD menus.
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("ControlMenu() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // PTZ OSD Menu : Down.
        // -----------------------------------------------------------------------
        private void BTN_DOWN_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Controls the OSD menus of the camera. This function is valid as long 
            // as the application is receiving media stream from the camera.(ex.SND-5080)
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlMenu(
                hDevice,                        // [in] Device handle. This value is returned from CreateDevice().
                nControlID,                     // [in] Control ID.
                (int)XPTZMenu.XMENU_DOWN);      // [in] Command to control the OSD menus.
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("ControlMenu() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // PTZ OSD Menu : Left.
        // -----------------------------------------------------------------------
        private void BTN_LEFT_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Controls the OSD menus of the camera. This function is valid as long 
            // as the application is receiving media stream from the camera.(ex.SND-5080)
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlMenu(
                hDevice,                        // [in] Device handle. This value is returned from CreateDevice().
                nControlID,                     // [in] Control ID.
                (int)XPTZMenu.XMENU_LEFT);      // [in] Command to control the OSD menus.
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("ControlMenu() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // PTZ OSD Menu : Right.
        // -----------------------------------------------------------------------
        private void BTN_RIGHT_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Controls the OSD menus of the camera. This function is valid as long 
            // as the application is receiving media stream from the camera.(ex.SND-5080)
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.ControlMenu(
                hDevice,                        // [in] Device handle. This value is returned from CreateDevice().
                nControlID,                     // [in] Control ID.
                (int)XPTZMenu.XMENU_RIGHT);     // [in] Command to control the OSD menus.
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("ControlMenu() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
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
            if ((e.nErrorCode == (int)XErrorCode.ERR_SUCCESS) && (e.nDeviceStatus == 1))
            {
                m_DebugLog.WLOGD("Connected...");
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


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This event occurs if the PTZ control has failed.
        // ----------------------------------------------------------------------- 
        private void axXnsSdkDevice_OnPtzControlFailed(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnPtzControlFailedEvent e)
        {
            m_DebugLog.WLOGD("PTZ Control Failed !" + e.nControlID + " " + e.nDeviceID + " " + e.nErrorCode + " ");
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This event occurs when GetPtzPos() is called. One of the parameter 
        // of event handler is the handle of preset list, which used to get the 
        // absolute coordinate of camera.
        //
        // Parameters
        // - nDeviceID
        //   [in] Device ID.
        // - nControlID
        //   [in] Control ID.
        // - nErrorCode
        //   [in] return value. 
        // - nPan
        //   [in] Absolute value of Pan. 
        // - nTilt
        //   [in] Absolute value of Tilt. 
        // - nZoom
        //   [in] Absolute value of Zoom. 
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnGetPtzPos(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnGetPtzPosEvent e)
        {
            nPan = e.nPan;
            nTilt = e.nTilt;
            nZoom = e.nZoom;

            EDIT_PTZ_PAN.Text = nPan.ToString();
            EDIT_PTZ_TILT.Text = nTilt.ToString();
            EDIT_PTZ_ZOOM.Text = nZoom.ToString();
            m_DebugLog.WLOGD("OnGetPtzPos()");
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Device Control Event.
        // This event occurs if GetPresetList() is called, the handle of the 
        // preset list will be forwarded to the parameter of event handler. 
        // This handle is input as a parameter of GetPresetCount(), 
        // and is used to get information about the preset. 
        // -----------------------------------------------------------------------
        private void axXnsSdkDevice_OnGetPresetList(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnGetPresetListEvent e)
        {
            string strPreset = null;
            int nNumber = 0;

            int nPresetCnt = axXnsSdkDevice.GetPresetCount(e.hPresetListList);
            PTZDlg.PresetInfo preset = new PTZDlg.PresetInfo();

            listPreset.Clear();
            for (int i = 0; i < nPresetCnt; i++)
            {
                strPreset = axXnsSdkDevice.GetPreset(
                    e.hPresetListList,
                    i,
                    ref nNumber);

                m_DebugLog.WLOGD("Index: " + nNumber.ToString() + " " + "Name: " + strPreset);

                preset.nIndex = nNumber;
                preset.strName = strPreset;
                listPreset.Add(preset);
            }

            Preset dlg = new Preset(this, axXnsSdkDevice, listPreset);
            dlg.ShowDialog();
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Window Control Event.
        // This event occurs if a left button on the mouse is pressed in XnSdkWindow. 
        // This event is valid only if both XnsSdkWindow handle and 
        // parent window handle are reset to Null.
        // ----------------------------------------------------------------------- 
        private void axXnsSdkWindow_OnLButtonDown(object sender, AxXNSSDKWINDOWLib._DXnsSdkWindowEvents_OnLButtonDownEvent e)
        {
            bMouseDown = true;

            if (CHECK_AREAZOOM.Checked == false)
            {
                return;
            }            

            nStartX = e.nX;
            nStartY = e.nY;

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Uses the blue brush to draw a rectangle on XnsSdkWindow. 
            // If this function is called more than twice, the existing rectangle 
            // will be replaced with a new one.
            // -----------------------------------------------------------------------
            axXnsSdkWindow.DrawRect(
                nStartX,			// [in] X-axis coordinate of top left.
                nStartY,			// [in] Y-axis coordinate of top left.
                0,					// [in] Width of the rectangle.
                0);					// [in] Height of the rectangle.
        }

        
        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Window Control Event.
        // This event occurs if the left mouse button is pressed and released in XnSdkWindow. 
        // This event is valid only if both XnsSdkWindow handle and 
        // parent window handle are reset to Null.
        // ----------------------------------------------------------------------- 
        private void axXnsSdkWindow_OnLButtonUp(object sender, AxXNSSDKWINDOWLib._DXnsSdkWindowEvents_OnLButtonUpEvent e)
        {
            if (CHECK_AREAZOOM.Checked == false)
            {
                return;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the width of the source image. 
            // -----------------------------------------------------------------------
            int nImageWidth = axXnsSdkWindow.GetImageWidth();
            
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the height of the source image.
            // -----------------------------------------------------------------------
            int nImageHeight = axXnsSdkWindow.GetImageHeight();

            nEndX = e.nX;
            nEndY = e.nY;

            axXnsSdkWindow.ClearDraw();
            m_DebugLog.WLOGD(nEndX + " " + nEndY);

            int nWindowWidth = axXnsSdkWindow.ClientRectangle.Width;
            int nWindowHeight = axXnsSdkWindow.ClientRectangle.Height;

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Set up AreaZoom feature, which is available when application 
            // receives media stream from the camera. 
            // Moves the camera to the Area zoom position. 
            // This function is valid as long as the application is receiving 
            // media stream from the camera. 
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.AreaZoom(
                hDevice,			// Device handle. This value is returned from CreateDevice().
                nControlID, 		// Control ID.
                nStartX,			// X-axis start position
                nStartY,			// Y-axis start position
                nEndX,  			// X-axis end position
                nEndY,  			// Y-axis end position
                nWindowWidth,		// Window width
                nWindowHeight,		// Window height
                nImageWidth,		// Image width
                nImageHeight);		// Image height
            
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("AreaZoom() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }

            bMouseDown = false;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ Window Control Event.
        // This event occurs if the mouse pointer is moving. This event is valid only 
        // if both XnsSdkWindow handle and parent window handle are reset to Null.
        // ----------------------------------------------------------------------- 
        private void axXnsSdkWindow_OnMouseMove(object sender, AxXNSSDKWINDOWLib._DXnsSdkWindowEvents_OnMouseMoveEvent e)
        {
            if ((CHECK_AREAZOOM.Checked == false) || (bMouseDown == false))
            {
                return;
            }

            // [ XNS ACTIVEX HELP ]
	        // -----------------------------------------------------------------------
	        // Uses the blue brush to draw a rectangle on XnsSdkWindow. 
	        // If this function is called more than twice, the existing rectangle 
	        // will be replaced with a new one.
	        // -----------------------------------------------------------------------
            axXnsSdkWindow.DrawRect(
                nStartX,			// [in] X-axis coordinate of top left.
                nStartY,			// [in] Y-axis coordinate of top left.
                e.nX - nStartX,		// [in] Width of the rectangle.
                e.nY - nStartY);    // [in] Height of the rectangle.
        }

        private void axXnsSdkDevice_OnGetPtzPosSpeed(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnGetPtzPosSpeedEvent e)
        {
            nPan = e.nPan;
            nTilt = e.nTilt;
            nZoom = e.nZoom;
            nSpeed = e.nSpeed;

            EDIT_PTZ_PAN.Text = nPan.ToString();
            EDIT_PTZ_TILT.Text = nTilt.ToString();
            EDIT_PTZ_ZOOM.Text = nZoom.ToString();
            EDIT_PTZ_SPEED.Text = nSpeed.ToString();
            m_DebugLog.WLOGD("OnGetPtzPosSpeed()");
            
        }

        private void BTN_GETPTZ2_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns an absolute coordinate of the camera, is available when 
            // application receives media stream from the camera. 
            // The value themselves could be read by using OnGetPtzPos event handler. 
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.GetPtzPosSpeed(
                hDevice,                    // [in] Device handle. This value is returned from CreateDevice().
                nControlID);                // [in] Control ID.
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("GetPtzPosSpeed() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
            }
        }

        private void BTN_SETPTZ2_Click(object sender, EventArgs e)
        {
            nPan = Convert.ToInt32(EDIT_PTZ_PAN.Text);
            nTilt = Convert.ToInt32(EDIT_PTZ_TILT.Text);
            nZoom = Convert.ToInt32(EDIT_PTZ_ZOOM.Text);
            nSpeed = Convert.ToInt32(EDIT_PTZ_SPEED.Text);

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Change the absolute coordinate of the camera, 
            // is available when application receives media stream from the camera.
            // -----------------------------------------------------------------------
            nError = axXnsSdkDevice.SetPtzPosSpeed(
                hDevice,                    // [in] Device handle. This value is returned from CreateDevice(). 
                nControlID,                 // [in] Control ID.
                nPan,                       // [in] absolute coordinate of Pan.
                nTilt,                      // [in] absolute coordinate of Tilt.
                nZoom,                      // [in] moving speed
                nSpeed);

            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("SetPtzPosSpeed() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
            }
        }

        private void BTN_RESTART_Click(object sender, EventArgs e)
        {
            nError = axXnsSdkDevice.PowerRestart(hDevice);
            if (nError != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("PowerRestart() fail::", "nError", nError, axXnsSdkDevice.GetErrorString(nError));
            }
        }

        private void axXnsSdkDevice_OnPowerRestart(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnPowerRestartEvent e)
        {
            m_DebugLog.WLOGD("OnPowerRestart() EVENT:: device_id=" + e.nDeviceID +
               ", error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
        }
    }
}
