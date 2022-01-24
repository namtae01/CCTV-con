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
// @ File Name :		MultipleConnect.cs
// @ File Description : MultipleConnect Form Source Code File. 
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

namespace MultipleConnect
{
    public partial class MultipleConnectForm : Form
    {
        // Device Information
        private const string LOGIN_ID   = "1";
        private const string PASSWORD   = "1";
        private const string IP_ADDRESS = "192.168.0.131";
        private const string PORT_NUM   = "554";
        private const string MODEL_NAME = "SRD-165X";

        private const int TRUE          = 1;
        private const int FALSE         = 0;
        private const int NULL          = 0;
        private const int XADDRESS_IP   = 1;
        private const int SPEED_1       = 1;

        
        private int nControlID          = 0;
        private int nError              = 0;
        private int nSelItem            = -1;
        private bool[] bWindowCtrl      = new bool[4] { false, false, false, false };
        private DebugLog m_DebugLog     = null;
        private AxXNSSDKWINDOWLib.AxXnsSdkWindow xnsSdkWin;

        // Device Information structure
        struct DEVICEINFO
        {
            public int      nDeviceID;          // Device ID
            public string   strModel;			// Model name
            public string   strIpAddress;		// IP Address
            public int      nPort;				// Port number
            public string   strId;			    // User ID
            public string   strPasswd;		    // Password
            public int      hDevice;			// Device handle
            public int       hMediaSource;		// Media stream ID
        }

        private List<DEVICEINFO> DevInfo = new List<DEVICEINFO>();

        public MultipleConnectForm()
        {
            InitializeComponent();
            m_DebugLog = new DebugLog(this.LIST_LOG);
        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Load Event.
        // -----------------------------------------------------------------------
        private void MultipleConnectForm_Load(object sender, EventArgs e)
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
            nError = axXnsSdkWindow1.Initialize(0, 0);
            m_DebugLog.WLOGW("Initialize():: ", nError, axXnsSdkDevice.GetErrorString(nError));
            nError = axXnsSdkWindow2.Initialize(0, 0);
            m_DebugLog.WLOGW("Initialize():: ", nError, axXnsSdkDevice.GetErrorString(nError));
            nError = axXnsSdkWindow3.Initialize(0, 0);
            m_DebugLog.WLOGW("Initialize():: ", nError, axXnsSdkDevice.GetErrorString(nError));
            nError = axXnsSdkWindow4.Initialize(0, 0);
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
                BTN_REMOVE.Enabled = false;
                BTN_CONNECT.Enabled = false;
                BTN_DISCONNECT.Enabled = false;
                BTN_STOP.Enabled = false;
                BTN_PLAY.Enabled = false;
            }
         }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Device Information Add Function.
        // ----------------------------------------------------------------------- 
        private void BTN_ADD_Click(object sender, EventArgs e)
        {
            string strModel = (System.String)COMBO_MODELLIST.SelectedItem;
            string strIpAddress = EDIT_IP.Text;
            int nPort = int.Parse(EDIT_PORT.Text);
            string strID = EDIT_ID.Text;
            string strPW = EDIT_PW.Text;

            int nDeviceID = GetDeviceID();
            if (nDeviceID == 0)
            {
                m_DebugLog.WLOGD("Not enough WindowControl");
                return;
            }
            int hDevice = axXnsSdkDevice.CreateDevice(nDeviceID);
            if (hDevice == NULL)
            {
                m_DebugLog.WLOGD("CreateDevice() fail");
                return;
            }
            
            DEVICEINFO temp = new DEVICEINFO();
            temp.hDevice = hDevice;
            hDevice = 0;
            temp.nDeviceID = nDeviceID;
            temp.strModel = strModel;
            temp.strIpAddress = strIpAddress;
            temp.nPort = nPort;
            temp.strId = strID;
            temp.strPasswd = strPW;
            DevInfo.Add(temp);

            ListViewItem lv = new ListViewItem(temp.nDeviceID.ToString());
            lv.SubItems.Add(strModel);
            lv.SubItems.Add(strIpAddress);
            lv.SubItems.Add(nPort.ToString());
            lv.SubItems.Add(strID);
            lv.SubItems.Add(strPW);
            LISTVIEW_DEVICE.Items.Add(lv);

            BTN_REMOVE.Enabled = true;
            BTN_CONNECT.Enabled = true;
            BTN_DISCONNECT.Enabled = true;
            BTN_PLAY.Enabled = true;
            BTN_STOP.Enabled = true;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Device Information Remove Function.
        // ----------------------------------------------------------------------- 
        private void BTN_REMOVE_Click(object sender, EventArgs e)
        {
            if (nSelItem < 0)
            {
                m_DebugLog.WLOGD("Remove failed");
                return;
            }
            
            int nDeviceID = int.Parse(LISTVIEW_DEVICE.Items[nSelItem].SubItems[0].Text);
            DEVICEINFO result = DevInfo.Find(
                delegate(DEVICEINFO temp)
                {
                    return temp.nDeviceID == nDeviceID;
                }
                );
            int hDevice = result.hDevice;
            int hMediaSource = result.hMediaSource;
            GetXnsSdkWin(nDeviceID);

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Check if there exists stream source.
            // -----------------------------------------------------------------------
            if (xnsSdkWin.IsMedia() == TRUE)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Stops receiving the stream data from the media source handle.  
                // -----------------------------------------------------------------------
                xnsSdkWin.Stop();
            }
            if (result.hMediaSource != 0)
            {
                axXnsSdkDevice.CloseMedia(hDevice, hMediaSource);
            }
            if (axXnsSdkDevice.GetDeviceStatus(hDevice) != 0)
            {
                axXnsSdkDevice.Disconnect(hDevice);
                m_DebugLog.WLOGD("Disconnect");
            }

            DevInfo.Remove(result);
            LISTVIEW_DEVICE.Items[nSelItem].Remove();
            nSelItem = -1;
            bWindowCtrl[nDeviceID-1] = false;
            axXnsSdkDevice.ReleaseDevice(result.hDevice);
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Device Connect Function.
        // ----------------------------------------------------------------------- 
        private void BTN_CONNECT_Click(object sender, EventArgs e)
        {
            if (nSelItem < 0)
            {
                m_DebugLog.WLOGD("Connect failed");
                return;
            }

            int nDeviceID = int.Parse(LISTVIEW_DEVICE.Items[nSelItem].SubItems[0].Text);
            DEVICEINFO result = DevInfo.Find(
                delegate(DEVICEINFO temp)
                {
                    return temp.nDeviceID == nDeviceID;
                }
                );

            if (axXnsSdkDevice.GetDeviceStatus(result.hDevice) == TRUE)
            {
                m_DebugLog.WLOGD("This device is already connected");
                return;
            }

            int hDevice = result.hDevice;
            string strModel = result.strModel;
            string strIpAddress = result.strIpAddress;
            int nPort = result.nPort;
            string strID = result.strId;
            string strPW = result.strPasswd;

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
            int nRet = axXnsSdkDevice.ConnectNonBlock(
                hDevice,            // [in] Device handle. This value is returned from CreateDevice(). 
                FALSE,              // [in] Flag to decide where to forcibly log in or not.
                FALSE);             // [in] When the device is disconnected, 
                                    //      you can use this flag to decide if to connect again automatically. 
                                    //      If this value is 1, try to connect again.
            
            if (nRet != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("ConnectNonBlock() fail: errno=", nError, axXnsSdkDevice.GetErrorString(nError));
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Device DisConnect Function.
        // ----------------------------------------------------------------------- 
        private void BTN_DISCONNECT_Click(object sender, EventArgs e)
        {
            if (nSelItem < 0)
            {
                m_DebugLog.WLOGD("Disconnect failed");
                return;
            }

            int nDeviceID = int.Parse(LISTVIEW_DEVICE.Items[nSelItem].SubItems[0].Text);
            DEVICEINFO result = DevInfo.Find(
                delegate(DEVICEINFO temp)
                {
                    return temp.nDeviceID == nDeviceID;
                }
                );
            int hDevice = result.hDevice;
            int hMediaSource = result.hMediaSource;

            if (xnsSdkWin.IsMedia() == TRUE)
            {
                xnsSdkWin.Stop();
            }
            if (result.hMediaSource != 0)
            {
                axXnsSdkDevice.CloseMedia(hDevice, hMediaSource);
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Disconnects from the device.
            // -----------------------------------------------------------------------
            int nRet = axXnsSdkDevice.Disconnect(hDevice);

            if (nRet != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("Disconnect Error! Code : ", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }
            m_DebugLog.WLOGD("DIsConnect! Code : ", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Play Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PLAY_Click(object sender, EventArgs e)
        {
            if (nSelItem < 0)
            {
                m_DebugLog.WLOGD("Play failed");
                return;
            }

            int nDeviceID = int.Parse(LISTVIEW_DEVICE.Items[nSelItem].SubItems[0].Text);
            DEVICEINFO result = DevInfo.Find(
                delegate(DEVICEINFO temp)
                {
                    return temp.nDeviceID == nDeviceID;
                }
                );
            int hDevice = result.hDevice;
            int hMediaSource = 0;
            int nRet = 0;
            GetXnsSdkWin(nDeviceID);
            if (xnsSdkWin.IsMedia() == TRUE)
            {
                m_DebugLog.WLOGW("Media stream is already played");
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
                        nRet = axXnsSdkDevice.OpenMedia(hDevice, i + 2, ((int)XMediaType.XMEDIA_LIVE), 0, 0, ref hMediaSource);
                        nControlID = i + 2;
                        break;
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
                        nRet = axXnsSdkDevice.OpenMedia(hDevice, i + 3, ((int)XMediaType.XMEDIA_LIVE), 0, 0, ref hMediaSource);
                        nControlID = i + 3;
                        break;
                    }
                }
            }

            if (nRet != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("Media Open Failed.");
                return;
            }
            m_DebugLog.WLOGD("Media Open Success.");

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Adds the media source handle to XnsSdkWindow. 
            // The media source handle is created by XnsSdkDevice. 
            // If the application calls XnsSdkDevice::OpenMedia(), 
            // it will receive media stream from the device and return the MediaSource 
            // handle. The application uses uses Start() to forward the mediasource 
            // handle to XnsSdkWindow so that XnsSdkWindow can obtain stream data. 
            // -----------------------------------------------------------------------
            nRet = xnsSdkWin.Start(hMediaSource);
            if (nRet != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGW("Media Play Failed.");
                return;
            }

            m_DebugLog.WLOGW("Media Play Success.");
            result.hMediaSource = hMediaSource;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Stop Function.
        // ----------------------------------------------------------------------- 
        private void BTN_STOP_Click(object sender, EventArgs e)
        {
            if (nSelItem < 0)
            {
                m_DebugLog.WLOGD("Stop failed");
                return;
            }

            int nDeviceID = int.Parse(LISTVIEW_DEVICE.Items[nSelItem].SubItems[0].Text);
            DEVICEINFO result = DevInfo.Find(
                delegate(DEVICEINFO temp)
                {
                    return temp.nDeviceID == nDeviceID;
                }
                );
            int hDevice = result.hDevice;
            int hMediaSource = result.hMediaSource;
            GetXnsSdkWin(nDeviceID);

            if (xnsSdkWin.IsMedia() == FALSE)
            {
                m_DebugLog.WLOGW("Media stream is not played");
                return;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Stops receiving the stream data from the media source handle.  
            // -----------------------------------------------------------------------
            hMediaSource = xnsSdkWin.Stop();
            if (hMediaSource != NULL)
            {
                m_DebugLog.WLOGW("Media Play Stopped.");
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Terminates transferring media stream data from the device. The media 
            // stream data will be separated by hMediaSource 
            // (i.e., phMediaSource of OpenMedia()).
            // -----------------------------------------------------------------------
            int nRet = axXnsSdkDevice.CloseMedia(hDevice, hMediaSource);

            if (nRet != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("Media Close Failed.");
                return;
            }
            result.hMediaSource = 0;
            m_DebugLog.WLOGD("Media Close Success.");
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ User-Defined Functions.
        // for Get Device ID function.
        // -----------------------------------------------------------------------
        public int GetDeviceID()
        {
            int nDeviceID = 0;
            for (int i = 0; i < 4; i++)
            {
                if (bWindowCtrl[i] == false)
                {
                    nDeviceID = i + 1;
                    bWindowCtrl[i] = true;
                    break;
                }
            }
            return nDeviceID;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ User-Defined Functions.
        // for Get WindowControl function.
        // -----------------------------------------------------------------------
        public void GetXnsSdkWin(int nDeviceID)
        {
            switch (nDeviceID)
            {
                case 1:
                    xnsSdkWin = axXnsSdkWindow1;
                    break;
                case 2:
                    xnsSdkWin = axXnsSdkWindow2;
                    break;
                case 3:
                    xnsSdkWin = axXnsSdkWindow3;
                    break;
                case 4:
                    xnsSdkWin = axXnsSdkWindow4;
                    break;
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
        // @ C# WinForm ListView Event.
        // for Seleted Item Event
        // ----------------------------------------------------------------------- 
        private void LISTVIEW_DEVICE_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            nSelItem = e.ItemIndex;
        }
    }
}
