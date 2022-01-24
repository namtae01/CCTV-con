﻿///////////////////////////////////////////////////////////////////////////////////
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
// @ File Name :		LocalRecording.cs
// @ File Description : LocalRecording Form Source Code File. 
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

namespace LocalRecording
{
    public partial class LocalRecordingForm : Form
    {
        // Device Information
        private const string LOGIN_ID = "admin";
        private const string PASSWORD = "4321";
        private const string IP_ADDRESS = "192.168.1.105";
        private const string PORT_NUM = "4520";
        private const string HTTPPORT_NUM = "80";
        private const string MODEL_NAME = "Samsung Network Camera/Encoder";

        private const int TRUE          = 1;
        private const int FALSE         = 0;
        private const int NULL          = 0;
        private const int XADDRESS_IP   = 1;
        private const int SPEED_1       = 1;

        private int hDevice             = 0;
        private int hMediaSource        = 0;
        private int hFileReader         = 0;
        private int nControlID          = 0;
        private int nError              = 0;
        private string strFilePath      = "c:\\LiveVideo";
        private DebugLog m_DebugLog     = null;

        public LocalRecordingForm()
        {
            InitializeComponent();
            m_DebugLog = new DebugLog(this.LIST_LOG);
        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Load Event.
        // -----------------------------------------------------------------------
        private void LocalRecordingForm_Load(object sender, EventArgs e)
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

            nError = axXnsSdkWindow_Recording.Initialize(0, 0);
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
                EDIT_HTTPPORT.Text = HTTPPORT_NUM;
                EDIT_ID.Text = LOGIN_ID;
                EDIT_PW.Text = PASSWORD;
            }
            // Set Dialog Enable
            {
                BTN_DISCONNECT.Enabled = false;
                BTN_STOP.Enabled = false;
                BTN_PLAY.Enabled = false;
                BTN_START_RECORDING.Enabled = false;
                BTN_STOP_RECORDING.Enabled = false;
                BTN_STOP_REC_FILE.Enabled = false;
            }
            RADIO_SEC.Checked = true;
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
            int nRet = axXnsSdkDevice.ConnectNonBlock(
                hDevice,            // [in] Device handle. This value is returned from CreateDevice(). 
                FALSE,              // [in] Flag to decide where to forcibly log in or not.
                FALSE);             // [in] When the device is disconnected, 
                                    //      you can use this flag to decide if to connect again automatically. 
                                    //      If this value is 1, try to connect again.

            m_DebugLog.WLOGD("ConnectNonBlock():: ", nError, axXnsSdkDevice.GetErrorString(nError));
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
                BTN_START_RECORDING.Enabled = false;
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

            if ((axXnsSdkDevice.GetControlType(hDevice, 1) == ((int)XModelType.XCTL_NETCAM)) ||
                 (axXnsSdkDevice.GetControlType(hDevice, 1) == ((int)XModelType.XCTL_ENCODER)))
            {
                nControlID = axXnsSdkDevice.GetVideoControlID(hDevice, 1, 2);
            }
            else
            {
                nControlID = axXnsSdkDevice.GetVideoControlID(hDevice, 1, 1);
            }

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
            nError = axXnsSdkDevice.OpenMedia(hDevice, nControlID, ((int)XMediaType.XMEDIA_LIVE), 0, 0, ref hMediaSource);
            if (nError == (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("Media Open Success.");
            }
            else
            {
                m_DebugLog.WLOGD("Media Open Failed.ret=" + nError.ToString() + "[" + axXnsSdkDevice.GetErrorString(nError) + "]");
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
                    BTN_START_RECORDING.Enabled = true;
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
                    BTN_START_RECORDING.Enabled = false;
                    m_DebugLog.WLOGD("Media Close Success.");
                    break;
                default:
                    m_DebugLog.WLOGD("Media Close Failed.");
                    break;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ MFC Window Button Control Functions.
        // for Local recording stop Function.
        // -----------------------------------------------------------------------
        private void BTN_START_RECORDING_Click(object sender, EventArgs e)
        {
            if (RADIO_SEC.Checked == true)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Starts recording the stream data in the local PC.
                // -----------------------------------------------------------------------
                axXnsSdkDevice.StartLocalRecording(
                    hDevice,                // [in] Device handle. This value is returned from CreateDevice().
                    nControlID,             // [in] Control ID
                    strFilePath,            // [in] File name of the recording data to save.
                    (int)XLocalRecordingType.SEC_WRITER);   // [in] File format.
            }
            else if(RADIO_REC.Checked == true)
            {
                axXnsSdkDevice.StartLocalRecording(hDevice, nControlID, strFilePath, (int)XLocalRecordingType.REC_WRITER);
            }

            m_DebugLog.WLOGD("Record On !");

            BTN_START_RECORDING.Enabled = false;
            BTN_STOP_RECORDING.Enabled = true;
            BTN_PLAY_REC_FILE.Enabled = false;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ MFC Window Button Control Functions.
        // for Local recording stop Function.
        // -----------------------------------------------------------------------
        private void BTN_STOP_RECORDING_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Stops recording in the local PC. 
            // -----------------------------------------------------------------------
            axXnsSdkDevice.StopLocalRecording(hDevice, nControlID);

            m_DebugLog.WLOGD("Record Off !");

            BTN_START_RECORDING.Enabled = true;
            BTN_STOP_RECORDING.Enabled = false;
            BTN_PLAY_REC_FILE.Enabled = true;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ MFC Window Button Control Functions.
        // for Local recording play Function.
        // -----------------------------------------------------------------------
        private void BTN_PLAY_REC_FILE_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Check if there exists stream source. 
            // -----------------------------------------------------------------------
            if (axXnsSdkWindow_Recording.IsMedia() == FALSE)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Creates the file reader. The file reader is used to play backup or 
                // recoding data.
                // -----------------------------------------------------------------------			
                hFileReader = axXnsSdkDevice.CreateFileReader(strFilePath);
                if (hFileReader == 0)
                {
                    m_DebugLog.WLOGD("No file to play\n");
                    return;
                }

                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Gets the handle of the media source from the file handle. 
                // This value is used to display images using XnsWindow.
                // -----------------------------------------------------------------------
                hMediaSource = axXnsSdkDevice.GetMediaSource(hFileReader);

                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Adds the media source handle to XnsSdkWindow. 
                // The media source handle is created by XnsSdkDevice. If the application
                // calls XnsSdkDevice::OpenMedia(), it will receive media stream from the
                // device and return the MediaSource handle. The application uses Start()
                // to forward the media source handle to XnsSdkWindow so that XnsSdkWindow
                // can obtain stream data. 
                // -----------------------------------------------------------------------
                axXnsSdkWindow_Recording.Start(hMediaSource);
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Plays the backup file at a specified speed.
            // -----------------------------------------------------------------------
            axXnsSdkDevice.PlayReader(
                hFileReader,			// [in] Handle of the file to play. This value can be obtained using CreateFileReader().
                SPEED_1);				// [in] Play speed.
            
            m_DebugLog.WLOGD("REC Play");
            BTN_PLAY_REC_FILE.Enabled = false;
            BTN_STOP_REC_FILE.Enabled = true;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ MFC Window Button Control Functions.
        // for Local recording stop Function.
        // -----------------------------------------------------------------------
        private void BTN_STOP_REC_FILE_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Stops playing the backup file temporarily. 
            // Can resume playing using PlayReader().
            // -----------------------------------------------------------------------
            long nErrCode = axXnsSdkDevice.PauseReader(hFileReader);

            m_DebugLog.WLOGD("REC pause");
            BTN_PLAY_REC_FILE.Enabled = true;
            BTN_STOP_REC_FILE.Enabled = false;
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
                if (nError == (int)XErrorCode.ERR_SUCCESS)
                {
                    BTN_CONNECT.Enabled = false;
                    BTN_DISCONNECT.Enabled = true;
                    BTN_PLAY.Enabled = true;
                }
                m_DebugLog.WLOGD("Connected...");
            }
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
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // This occurs if receiving media stream is stopped or completed. 
        // -----------------------------------------------------------------------
        private void axXnsSdkWindow_Recording_OnMediaOff(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Releases the file reader.
            // -----------------------------------------------------------------------
            axXnsSdkDevice.ReleaseFileReader(hFileReader);
            hFileReader = 0;

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Stops receiving the stream data from the media source handle (hMediaSource). 
            // -----------------------------------------------------------------------
            axXnsSdkWindow_Recording.Stop();
            hMediaSource = 0;
            m_DebugLog.WLOGW("Receiving media stream is completed\n");
            BTN_PLAY_REC_FILE.Enabled = true;
            BTN_STOP_REC_FILE.Enabled = false;
        }
    }
}
