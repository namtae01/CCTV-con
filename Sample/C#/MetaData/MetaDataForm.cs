
using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Text;
using System.Diagnostics;

// Define XNS Control.
using XNSSDKWINDOWLib;
using XNSSDKDEVICELib;
using XNSSAMPLELOGLib;

namespace MetaData
{
    public partial class MetaDataForm : Form
    {

        private const string LOGIN_ID = "admin";
        private const string PASSWORD = "5tkatjd!";
        private const string IP_ADDRESS = "192.168.51.61";
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
        private DebugLog m_MetaLog = null;

        public MetaDataForm()
        {
            InitializeComponent();
            m_DebugLog = new DebugLog(this.LIST_LOG);
            m_MetaLog = new DebugLog(this.LIST_META_DATA);
        }

        private void MetaDataForm_Load(object sender, System.EventArgs e)
        {
            nError = axXnsSdkDevice.Initialize();
            m_DebugLog.WLOGD("Initialize():: ", nError, axXnsSdkDevice.GetErrorString(nError));

            nError = axXnsSdkWindow.Initialize(0, 0);
            m_DebugLog.WLOGW("Initialize():: ", nError, axXnsSdkDevice.GetErrorString(nError));

            // Dialog Setting.
            OnSetDialog();
        }

        public void OnSetDialog()
        {
            int hFind = axXnsSdkDevice.FindModel("Samsung");
            int hFindSize = axXnsSdkDevice.GetFindSize(hFind);

            System.String strModel = null;
            for (int i = 0; i < hFindSize; i++)
            {
                strModel = axXnsSdkDevice.GetFindString(hFind, i);
                COMBO_MODELLIST.Items.Add(strModel);
            }

            axXnsSdkDevice.CloseFind(hFind);

            COMBO_MODELLIST.SelectedIndex = 0;
            int index = COMBO_MODELLIST.FindStringExact(MODEL_NAME, 0);
            if (index != -1)
            {
                COMBO_MODELLIST.SelectedIndex = index;
            }
            

            EDIT_IP.Text = IP_ADDRESS;
            EDIT_PORT.Text = PORT_NUM;
            EDIT_HTTPPORT.Text = HTTPPORT_NUM;
            EDIT_ID.Text = LOGIN_ID;
            EDIT_PW.Text = PASSWORD;
        }

        private void BTN_CONNECT_Click(object sender, EventArgs e)
        {
            string strModel     = (System.String)COMBO_MODELLIST.SelectedItem;
            string strIpAddress = EDIT_IP.Text;
            int nPort           = int.Parse(EDIT_PORT.Text);
            int nHttpPort       = int.Parse(EDIT_HTTPPORT.Text);
            string strID        = EDIT_ID.Text;
            string strPW        = EDIT_PW.Text;
            int nDeviceProtocol = 0;
            
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

            nError = axXnsSdkDevice.ConnectNonBlock(
                hDevice,            // [in] Device handle. This value is returned from CreateDevice(). 
                FALSE,              // [in] Flag to decide where to forcibly log in or not.
                FALSE);             // [in] When the device is disconnected, you can use this flag to decide
                                    //      if to connect again automatically. If this value is 1, try to connect again.
            m_DebugLog.WLOGD("ConnectNonBlock():: ", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        private void BTN_DISCONNECT_Click(object sender, EventArgs e)
        {
            if (axXnsSdkWindow.IsMedia() == TRUE)
            {
                hMediaSource = axXnsSdkWindow.Stop();
            }

            if (hMediaSource != 0)
            {
                axXnsSdkDevice.CloseMedia(hDevice, hMediaSource);
                hMediaSource = 0;
            }

            nError = axXnsSdkDevice.Disconnect(hDevice);
            m_DebugLog.WLOGD("Disconnect():: ", nError, axXnsSdkDevice.GetErrorString(nError));

            if (nError == (int)XErrorCode.ERR_SUCCESS)
            {
                axXnsSdkDevice.ReleaseDevice(hDevice);
            }
        }

        private void BTN_MEDIAOPEN_Click(object sender, EventArgs e)
        {
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

            nError = axXnsSdkDevice.OpenStream(hDevice, nControlID, ((int)XMediaType.XMEDIA_LIVE), 0, 0);
            if (nError == (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("Media Open Success.");
                BTN_MEDIAOPEN.Enabled = false;
                BTN_MEDIACLOSE.Enabled = true;
                BTN_START.Enabled = true;
                BTN_STOP.Enabled = false;
            }
            else
            {
                m_DebugLog.WLOGD("Media Open Failed.ret=" + nError.ToString() + "[" + axXnsSdkDevice.GetErrorString(nError) + "]");
            }
        }

        private void BTN_MEDIACLOSE_Click(object sender, EventArgs e)
        {
            if (axXnsSdkWindow.IsMedia() == TRUE)
            {
                hMediaSource = axXnsSdkWindow.Stop();
            }
            nError = axXnsSdkDevice.CloseMedia(hDevice, hMediaSource);
            switch (nError)
            {
                case (int)XErrorCode.ERR_SUCCESS:
                    hMediaSource = 0;
                    BTN_MEDIAOPEN.Enabled = true;
                    BTN_MEDIACLOSE.Enabled = false;
                    BTN_START.Enabled = false;
                    BTN_STOP.Enabled = false;
                    m_DebugLog.WLOGD("Media Close Success.");
                    break;
                default:
                    m_DebugLog.WLOGD("Media Close Failed.");
                    break;
            }
        }

        private void BTN_START_Click(object sender, EventArgs e)
        {
            nError = axXnsSdkWindow.Start(hMediaSource);
            switch (nError)
            {
                case (int)XErrorCode.ERR_SUCCESS:
                    BTN_START.Enabled = false;
                    BTN_STOP.Enabled = true;
                    m_DebugLog.WLOGW("Media Play Success.");
                    break;
                default:
                    m_DebugLog.WLOGW("Media Play Failed.");
                    break;
            }
        }

        private void BTN_STOP_Click(object sender, EventArgs e)
        {
            hMediaSource = axXnsSdkWindow.Stop();
            if (hMediaSource != NULL)
            {
                BTN_START.Enabled = true;
                BTN_STOP.Enabled = false;
                BTN_MEDIACLOSE.Enabled = true;
                m_DebugLog.WLOGW("Media Play Stopped.");
            }
        }

        private void axXnsSdkDevice_OnDeviceStatusChanged(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEvent e)
        {
            m_DebugLog.WLOGD("OnDeviceStatusChanged() EVENT:: device_id=" + e.nDeviceID + ", status=" + e.nDeviceStatus +
                ", error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
            if ((e.nErrorCode == (int)XErrorCode.ERR_SUCCESS) && (e.nDeviceStatus == 1))
            {
                m_DebugLog.WLOGD("Connected...");
            }
        }

        private void axXnsSdkDevice_OnConnectFailed(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEvent e)
        {
            m_DebugLog.WLOGD("OnConnectFailed() EVENT:: device_id=" + e.nDeviceID +
                ", error=" + e.nErrorCode + "[" + axXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
        }

        private void axXnsSdkDevice_OnNewMedia(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnNewMediaEvent e)
        {
            if (e.nInputType == (int)XInputType.XINPUT_VIDEO)
            {
                axXnsSdkWindow.PushMedia(e.hMediaData);
            }
            else if (e.nInputType == (int)XInputType.XINPUT_METADATA)
            {
                //m_DebugLog.WLOGD(e.nInputType.ToString());
              
                int metaDataHeaderSize = 224;
                int dataSize = e.nFrameSize - metaDataHeaderSize;

                byte[] getData = new byte[dataSize+1];
                
                Marshal.Copy((IntPtr)(e.hMediaData + metaDataHeaderSize), getData, 0, getData.Length);
                
                m_MetaLog.WLOGD(Encoding.Default.GetString(getData));
            }
        }   

    }
}
