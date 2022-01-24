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
// @ File Name :		MainForm.cs
// @ File Description : UserAccount Form Source Code File. 
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
using System.Diagnostics;
using System.Xml;
using System.Xml.Serialization;
using System.IO;

// Define XNS Control.
using XNSSDKWINDOWLib;
using XNSSDKDEVICELib;

// Define XNS Sample Log
using XNSSAMPLELOGLib;

namespace UserAccount
{
    public partial class MainForm : Form
    {
        // Device Information
        private const string LOGIN_ID   = "admin";
        private const string PASSWORD   = "1111qqqq";
        private const string IP_ADDRESS = "192.168.31.197";
        private const string PORT_NUM   = "4520";
        private const string MODEL_NAME = "Samsung DVR";

        private const int TRUE          = 1;
        private const int FALSE         = 0;
        private const int NULL          = 0;
        private const int XADDRESS_IP   = 1;

        private int hDevice             = 0;
        private int hMediaSource        = 0;
        private int nControlID          = 0;
        private int nError              = 0;
        
        private int nDeviceID = 1;
        private string savePath = "";
        private DebugLog m_DebugLog = null;

        public MainForm()
        {
            InitializeComponent();
            m_DebugLog = new DebugLog(this.LIST_LOG);
        }

        private void InitSDK()
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
        }


        private void SetModelList()
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
                comboBoxModelName.Items.Add(strModel);
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Closes the Find command. Releases the memory space assinged by FindXXX().
            // -----------------------------------------------------------------------
            axXnsSdkDevice.CloseFind(hFind);
            comboBoxModelName.SelectedIndex = 0;

        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Load Event.
        // -----------------------------------------------------------------------
        private void MainForm_Load(object sender, EventArgs e)
        {
            InitSDK();
            SetModelList();

            // Set User Information Edit Box
            textBoxIP.Text      = IP_ADDRESS;
            textBoxPort.Text    = PORT_NUM;
            textBoxID.Text      = LOGIN_ID;
            textBoxPW.Text      = PASSWORD;

            // Set Dialog Enable
            buttonConnect.Enabled = true;
            buttonDisconnect.Enabled = false;
            buttonMediaOpen.Enabled = false;
            buttonMediaClose.Enabled = false;
        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Device Connect Function.
        // ----------------------------------------------------------------------- 
        private void buttonConnect_Click(object sender, EventArgs e)
        {
            string strModel = comboBoxModelName.SelectedItem as string;
            int nPort = int.Parse(textBoxPort.Text);

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Assigns memory space for saving device information. 
            // This function will return the device handle, which the application 
            // can use to control the device.
            // [in] Device ID The value should be a greater integer than 0.
            // Minimum value: 1 , Maximum value: 3000
            // -----------------------------------------------------------------------
            hDevice = axXnsSdkDevice.CreateDevice(nDeviceID++);
            if (hDevice == 0)
            {
                m_DebugLog.WLOGD("CreateDevice() fail");
                return;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Sets the device information so that the application can connect 
            // to the device.
            // -----------------------------------------------------------------------
            axXnsSdkDevice.SetConnectionInfo(hDevice, "Samsung", strModel, XADDRESS_IP, textBoxIP.Text, nPort, 0, textBoxID.Text, textBoxPW.Text);

            buttonConnect.Enabled = false;

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
            if ((nError = axXnsSdkDevice.ConnectNonBlock(hDevice, 0, 0)) != (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("ConnectNonBlock():: ", nError, axXnsSdkDevice.GetErrorString(nError));
                buttonConnect.Enabled = true;
            }
        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Device DisConnect Function.
        // -----------------------------------------------------------------------
        private void buttonDisconnect_Click(object sender, EventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Check if there exists stream source.
            // -----------------------------------------------------------------------
            if (axXnsSdkWindow.IsMedia() == 1)
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

                SetControlActivation("disconnect");
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

            if (e.nDeviceStatus.Equals(1))
            {
                SetControlActivation("connected");
                int nCount = 0;
                
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
                    nCount = axXnsSdkDevice.GetControlCount(hDevice, (int)XModelType.XCTL_CAMERA);
                    nControlID = 2;
                }
                else if ((axXnsSdkDevice.GetControlType(hDevice, 1) == ((int)XModelType.XCTL_NETCAM)) ||
                    (axXnsSdkDevice.GetControlType(hDevice, 1) == ((int)XModelType.XCTL_ENCODER)))
                {
                    nCount = axXnsSdkDevice.GetControlCount(hDevice, (int)XModelType.XCTL_VIDEO);
                    nControlID = 3;
                }
                SetChannelList(nCount);
            }
            else
            {
                SetControlActivation("disconnect");
            }
        }

        private void SetChannelList(int nCount)
        {

            comboBoxChannel.Items.Clear();
            for (int i = 0; i < nCount; i++)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Returns the capabilities of the control module.
                // -----------------------------------------------------------------------
                if ((axXnsSdkDevice.GetControlCapability(hDevice, i + nControlID, ((int)XUnitCap.XCTL_CAP_LIVE)) == 1))
                {
                    comboBoxChannel.Items.Add((i + 1).ToString());
                }
            }
            if (comboBoxChannel.Items.Count > 0)
                comboBoxChannel.SelectedIndex = 0;
        }

        private void SetControlActivation(string name)
        {
            if (name.Equals("disconnect"))
            {
                buttonConnect.Enabled = true;
                buttonDisconnect.Enabled = false;
                buttonMediaOpen.Enabled = false;
                buttonMediaClose.Enabled = false;
                comboBoxChannel.Enabled = false;
            }
            else if(name.Equals("connected"))
            {
                buttonConnect.Enabled = false;
                buttonDisconnect.Enabled = true;
                buttonMediaOpen.Enabled = true;
                buttonMediaClose.Enabled = false;
                comboBoxChannel.Enabled = true;
            }
            else if (name.Equals("media open"))
            {
                buttonMediaOpen.Enabled = false;
                buttonMediaClose.Enabled = true;
                comboBoxChannel.Enabled = false;
            }
            else if (name.Equals("media close"))
            {
                buttonMediaOpen.Enabled = true;
                buttonMediaClose.Enabled = false;
                comboBoxChannel.Enabled = false;
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
            buttonConnect.Enabled = true;
            m_DebugLog.WLOGD("OnConnectFailed() EVENT:: device_id=" + e.nDeviceID +
                ", error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Media Open Function.
        // ----------------------------------------------------------------------- 
        private void buttonMediaOpen_Click(object sender, EventArgs e)
        {
            if (axXnsSdkDevice.GetDeviceStatus(hDevice) != ((int)XConnect.XDEVICE_STATUS_CONNECTED))
            {
                return;
            }

            int nError = 0;
            
            if ((axXnsSdkDevice.GetControlCapability(hDevice, nControlID, ((int)XUnitCap.XCTL_CAP_LIVE)) == 1))
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
                nError = axXnsSdkDevice.OpenMedia(hDevice, nControlID, ((int)XMediaType.XMEDIA_LIVE), 0, 0, ref hMediaSource);
                if (nError == (int)XErrorCode.ERR_SUCCESS)
                {
                    SetControlActivation("media open");
                    nError = axXnsSdkWindow.Start(hMediaSource);
                }
            }
        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Media Close Function.
        // -----------------------------------------------------------------------
        private void buttonMediaClose_Click(object sender, EventArgs e)
        {
            hMediaSource = axXnsSdkWindow.Stop();
            if (hMediaSource != 0)
            {
                if (axXnsSdkWindow.IsMedia() == 1)
                {
                    hMediaSource = axXnsSdkWindow.Stop();
                }
                int nError = axXnsSdkDevice.CloseMedia(hDevice, hMediaSource);
                SetControlActivation("media close");
                hMediaSource = 0;
            }
        }

        private void buttonRestart_Click(object sender, EventArgs e)
        {
            int nError = axXnsSdkDevice.PowerRestart(hDevice);
            if(nError != (int)XErrorCode.ERR_SUCCESS)
                m_DebugLog.WLOGD("PowerRestart() error=" + nError + "[" + axXnsSdkDevice.GetErrorString(nError) + "]");
        }

        private void buttonShutDown_Click(object sender, EventArgs e)
        {
            int nError = axXnsSdkDevice.ShutDown(hDevice);
            if (nError != (int)XErrorCode.ERR_SUCCESS)
                m_DebugLog.WLOGD("ShutDown() error=" + nError + "[" + axXnsSdkDevice.GetErrorString(nError) + "]");
        }

        private void axXnsSdkDevice_OnPowerRestart(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnPowerRestartEvent e)
        {
            m_DebugLog.WLOGD("OnPowerRestart() EVENT:: error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
        }

        private void axXnsSdkDevice_OnShutDown(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnShutDownEvent e)
        {
            m_DebugLog.WLOGD("OnShutDown() EVENT:: error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
        }

        private void buttonGetCapacity_Click(object sender, EventArgs e)
        {
            int nError = axXnsSdkDevice.GetPermissionCapacity(hDevice);
            if (nError != (int)XErrorCode.ERR_SUCCESS)
                m_DebugLog.WLOGD("GetPermissionCapacity() error=" + nError + "[" + axXnsSdkDevice.GetErrorString(nError) + "]");
        }

        private void axXnsSdkDevice_OnGetPermissionCapacity(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnGetPermissionCapacityEvent e)
        {
            if (e.nErrorCode != (int)XErrorCode.ERR_SUCCESS)
                m_DebugLog.WLOGD("OnGetPermissionCapacity() EVENT:: error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
            else
            {
                m_DebugLog.WLOGD("OnGetPermissionCapacity() EVENT:: device_id" + e.nDeviceID +
                    ", MAX Group(" + e.nMaxGroup.ToString() + ") " +
                    "MAX Password(" + e.nMaxPassword.ToString() + ") " +
                    "MAX User(" + e.nMaxUser.ToString() + ") " +
                    "MAX UserID(" + e.nMaxUserID.ToString() + ") " +
                    "MAX UserName(" + e.nMaxUserName.ToString() + ") " +
                    "MAX UserPerGroup(" + e.nMaxUserPerGroup.ToString() + ") " +
                    "Min Password(" + e.nMinPassword.ToString() + ")");
            }
        }

        private void buttonGetPermission_Click(object sender, EventArgs e)
        {
            using (SaveFileDialog dlg = new SaveFileDialog())
            {
                dlg.Filter = "xml files (*.xml)|*.xml|All files(*.*)|*.*";
                dlg.FilterIndex = 1;
                dlg.RestoreDirectory = true;
                DialogResult result = dlg.ShowDialog();
                if (result.Equals(DialogResult.OK))
                {
                    savePath = dlg.FileName;
                    int nError = axXnsSdkDevice.GetPermission(hDevice);
                    if (nError != (int)XErrorCode.ERR_SUCCESS)
                        m_DebugLog.WLOGD("GetPermission() error=" + nError + "[" + axXnsSdkDevice.GetErrorString(nError) + "]");
                }
            }
        }

        private void buttonSetPermission_Click(object sender, EventArgs e)
        {
            OpenFileDialog openDlg = new OpenFileDialog();
            openDlg.Filter = "xml files (*.xml)|*.xml|All files(*.*)|*.*";
            openDlg.FilterIndex = 1;
            openDlg.RestoreDirectory = true;
            DialogResult result = openDlg.ShowDialog();
            if (result == DialogResult.OK)
            {
                string data = File.ReadAllText(openDlg.FileName);
                
                int nError = axXnsSdkDevice.SetPermission(hDevice, data);
                if (nError != (int)XErrorCode.ERR_SUCCESS)
                    m_DebugLog.WLOGD("SetPermission() error=" + nError + "[" + axXnsSdkDevice.GetErrorString(nError) + "]");
            }
        }

        private void axXnsSdkDevice_OnGetPermission(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnGetPermissionEvent e)
        {
            m_DebugLog.WLOGD("OnGetPermission() EVENT:: error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
            if (e.nErrorCode == (int)XErrorCode.ERR_SUCCESS)
            {
                try
                {
                    File.WriteAllText(savePath, e.xmlData);
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
        }

        private void axXnsSdkDevice_OnSetPermission(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnSetPermissionEvent e)
        {
            if (e.nErrorCode != (int)XErrorCode.ERR_SUCCESS)
                m_DebugLog.WLOGD("OnGetPermission() EVENT:: error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]"
                    + ", GroupName[" + e.errorGroupName + "]" + ", UserID[" + e.errorUserID + "]");
            else
                m_DebugLog.WLOGD("OnGetPermission() EVENT:: error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
        }
    }
}
