///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2014 by Hanwha Techwin, Inc.
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
// @ File Name :		VideoRawData.cs
// @ File Description : VideoRawData Form Source Code File. 
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
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

// Define XNS Control.
using XNSSDKWINDOWLib;
using XNSSDKDEVICELib;

// Define XNS Sample Log
using XNSSAMPLELOGLib;

namespace VideoLawData
{
    public partial class VideoRawData : Form
    {
        // Device Information
        private const string LOGIN_ID = "admin";
        private const string PASSWORD = "4321";
        private const string IP_ADDRESS = "192.168.1.105";
        private const string PORT_NUM = "4520";
        private const string HTTPPORT_NUM = "80";
        private const string MODEL_NAME = "Samsung Network Camera/Encoder";

        private const int TRUE = 1;
        private const int FALSE = 0;
        private const int NULL = 0;
        private const int XADDRESS_IP = 1;

        private int hDevice = 0;
        private int hMediaSource = 0;
        private int nControlID = 0;
        private int nError = 0;
        private DebugLog m_DebugLog = null;

        public int XVIDEO_PIXEL_R565 = 0x0003; // 16Bit, R565
        public int XVIDEO_PIXEL_BGRA = 0x0006; // 32Bit, with Alpha Channel

        public VideoRawData()
        {
            InitializeComponent();
            m_DebugLog = new DebugLog(this.LIST_LOG);
            PICTURE_BOX.SizeMode = PictureBoxSizeMode.StretchImage;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Load Event.
        // -----------------------------------------------------------------------
        private void VideoRawData_Load(object sender, EventArgs e)
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
                EDIT_HTTPPORT.Text = HTTPPORT_NUM;
                EDIT_ID.Text = LOGIN_ID;
                EDIT_PW.Text = PASSWORD;
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
                FALSE,              // [in] Flag to decide where to forcibly log in or not.
                FALSE);             // [in] When the device is disconnected, you can use this flag to decide
                                    //      if to connect again automatically. If this value is 1, try to connect again.
            m_DebugLog.WLOGD("ConnectNonBlock():: ", nError, axXnsSdkDevice.GetErrorString(nError));

//             if (nError == (int)XErrorCode.ERR_SUCCESS)
//             {
//                 BTN_CONNECT.Enabled = false;
//                 BTN_DISCONNECT.Enabled = true;
//                 BTN_PLAY.Enabled = true;
//             }
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
                    if ((axXnsSdkDevice.GetControlCapability(hDevice, i + 4, ((int)XUnitCap.XCTL_CAP_LIVE)) == TRUE))
                    {
                        nError = axXnsSdkDevice.OpenMedia(hDevice, i + 4, ((int)XMediaType.XMEDIA_LIVE), 0, 0, ref hMediaSource);
                        if (nError == (int)XErrorCode.ERR_SUCCESS)
                        {
                            m_DebugLog.WLOGD("Media Open Success.");
                            nControlID = i + 4;
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
        // @ C# WinForm CheckBox Event.
        // for VideoRawData Function.
        // ----------------------------------------------------------------------- 
        private void CHECK_VIEW_CheckedChanged(object sender, EventArgs e)
        {
            if (CHECK_VIEW.Checked == true)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Uses this function to receive decoded video raw data. When this 
                // function is called, OnVideoRawDataReceived() Event will be occurred.
                // -----------------------------------------------------------------------
                axXnsSdkWindow.SetVideoRawDataReceived(hMediaSource);
            }
            else
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Uses this function to cancel SetVideoRawDataReceived() call. When this 
                // function is called, OnVideoRawDataReceived() Event will not be occurred.
                // -----------------------------------------------------------------------
                axXnsSdkWindow.UnSetVideoRawDataReceived(hMediaSource);
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
                BTN_CONNECT.Enabled = false;
                BTN_DISCONNECT.Enabled = true;
                BTN_PLAY.Enabled = true;
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
        // This event occurs when the application receives the frame data. 
        // If the application uses OpenStream() to request stream data, 
        // then the frame data will be transferred through this event.
        // -----------------------------------------------------------------------       
        private void axXnsSdkDevice_OnNewMedia(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnNewMediaEvent e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Transfers stream data to XnsSdkWindow so that the media stream will be 
            // displayed on the window after decoded. If XnsSdkDevice::OpenStream 
            // is called, the stream data will be transferred to the application from
            // the OnNewMedia event. Then, the application should use PushMedia 
            // to forward the stream data to XnsSdkWindow for decoding so that 
            // the video is properly displayed on the screen. This function is 
            // valid only within the event handler of the OnNewMedia event.
            // -----------------------------------------------------------------------
            axXnsSdkWindow.PushMedia(e.hMediaData);
        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // This event is occurred when the decoded video data is made. To receive 
        // this event, you should call SetVideoRawDataReceived() function in advance.
        // To cancel receiving event, use UnsetVidoRawDataReceived.
        // -----------------------------------------------------------------------      
        private void axXnsSdkWindow_OnVideoRawDataReceived(object sender, AxXNSSDKWINDOWLib._DXnsSdkWindowEvents_OnVideoRawDataReceivedEvent e)
        {
            IntPtr pVideoData = new IntPtr(e.pVideoData);
            int stride = 0;
            int bitmap_format = 0;

            int pixel_format = axXnsSdkWindow.GetVideoPixelFormat();
            if (pixel_format == XVIDEO_PIXEL_BGRA)
            {
                stride = 4 * e.nWidth;
                bitmap_format = (int)PixelFormat.Format32bppArgb;
            }
            else if (pixel_format == XVIDEO_PIXEL_R565)
            {
                stride = 2 * e.nWidth;
                bitmap_format = (int)PixelFormat.Format16bppRgb565;
            }

            Bitmap bitmap = new Bitmap(e.nWidth, e.nHeight, stride, (PixelFormat)bitmap_format, pVideoData);
            PICTURE_BOX.Image = bitmap;
        }
    }
}
