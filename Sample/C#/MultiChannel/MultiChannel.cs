using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Text;
using System.Diagnostics;
using System.Drawing;

// Define XNS Control.
using XNSSDKWINDOWLib;
using XNSSDKDEVICELib;
using XNSSAMPLELOGLib;

namespace MultiChannel
{
    public partial class MultiChannel : Form
    {
        private const string LOGIN_ID = "admin";
        private const string PASSWORD = "5hanwha!";
        private const string IP_ADDRESS = "192.168.217.120";
        private const string PORT_NUM = "554";
        private const string HTTPPORT_NUM = "80";
        private const string MODEL_NAME = "Samsung NVR";

        private const int TRUE = 1;
        private const int FALSE = 0;
        private const int NULL = 0;
        private const int XADDRESS_IP = 1;

        private int hDevice = 0;
        private int nControlID = 0;
        private int nError = 0;
        
        private DebugLog m_DebugLog = null;

        private int nChannelIndex = 0;
        private int nProfileIndex = 0;
        private const int MAXCHANNEL = 16;
        private AxXNSSDKWINDOWLib.AxXnsSdkWindow[] axXnsSdkWindowList = new AxXNSSDKWINDOWLib.AxXnsSdkWindow[MAXCHANNEL];
        private int[] hMediaSource = new int[MAXCHANNEL];

        public MultiChannel()
        {
            InitializeComponent();
            m_DebugLog = new DebugLog(this.LIST_LOG);
        }

        private void MultiChannel_Load(object sender, EventArgs e)
        {
            nError = axXnsSdkDevice1.Initialize();
            m_DebugLog.WLOGD("Initialize():: ", nError, axXnsSdkDevice1.GetErrorString(nError));

            setWindowList();

            for (int i = 0; i < MAXCHANNEL; i++)
            {
                axXnsSdkWindowList[i].Initialize(NULL, NULL);
                hMediaSource[i] = 0;
            }
            OnSetDialog();
        }

        public void OnSetDialog()
        {
            int hFind = axXnsSdkDevice1.FindModel("Samsung");
            int hFindSize = axXnsSdkDevice1.GetFindSize(hFind);

            System.String strModel = null;
            for (int i = 0; i < hFindSize; i++)
            {
                strModel = axXnsSdkDevice1.GetFindString(hFind, i);
                COMBO_MODELLIST.Items.Add(strModel);
            }

            axXnsSdkDevice1.CloseFind(hFind);

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

            COMBO_CHANNEL.Items.Add("1");
            COMBO_CHANNEL.Items.Add("4");
            COMBO_CHANNEL.Items.Add("9");
            COMBO_CHANNEL.Items.Add("16");
        }

        private void BTN_CONNECT_Click(object sender, EventArgs e)
        {
            string strModel = (System.String)COMBO_MODELLIST.SelectedItem;
            string strIpAddress = EDIT_IP.Text;
            int nPort = int.Parse(EDIT_PORT.Text);
            int nHttpPort = int.Parse(EDIT_HTTPPORT.Text);
            string strID = EDIT_ID.Text;
            string strPW = EDIT_PW.Text;

            int device_id = axXnsSdkDevice1.CreateDeviceEx();
            hDevice = axXnsSdkDevice1.GetDeviceHandle(device_id);

            if (hDevice == NULL)
            {
                m_DebugLog.WLOGD("CreateDevice() fail");
                return;
            }

            this.axXnsSdkDevice1.SetConnectionInfo2(
                 hDevice,            // [in] Device handle. This value is returned from CreateDevice().
                 "Samsung",          // [in] Fixed as 'Samsung'. The maximum length allowed is 126-byte.
                 strModel,           // [in] Name of model to connect to. The maximum length allowed is 126-byte.
                 XADDRESS_IP,        // [in] Address type
                 strIpAddress,       // [in] Actual address according to nAddressType. 
                 nPort,              // [in] Port number
                 nHttpPort,          // [in] Port number for web access
                 strID,              // [in] Login ID. The maximum length allowed is 62-byte
                 strPW,              // [in] Login password. The maximum length allowed is 18-byte
                 0,
                 0);         

            nError = axXnsSdkDevice1.ConnectNonBlock(
                hDevice,            // [in] Device handle. This value is returned from CreateDevice(). 
                FALSE,              // [in] Flag to decide where to forcibly log in or not.
                FALSE);             // [in] When the device is disconnected, you can use this flag to decide
            //      if to connect again automatically. If this value is 1, try to connect again.
            m_DebugLog.WLOGD("ConnectNonBlock():: ", nError, axXnsSdkDevice1.GetErrorString(nError));
        }


        private void BTN_DISCONNECT_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < MAXCHANNEL; i++)
            {
                if (hMediaSource[i] != 0)
                {
                    axXnsSdkWindowList[i].Stop();
                    axXnsSdkDevice1.CloseMedia(hDevice, hMediaSource[i]);
                    hMediaSource[i] = 0;
                }
            }
            nError = axXnsSdkDevice1.Disconnect(hDevice);
            m_DebugLog.WLOGD("Disconnect");

            if (nError == (int)XErrorCode.ERR_SUCCESS)
            {
                axXnsSdkDevice1.ReleaseDevice(hDevice);
            }
        }

        private void BTN_START_Click(object sender, EventArgs e)
        {
            if (axXnsSdkDevice1.GetDeviceStatus(hDevice) != ((int)XConnect.XDEVICE_STATUS_CONNECTED))
            {
                m_DebugLog.WLOGD("Not connected");
                return;
            }

            int nVideo = 0;
            nVideo = int.Parse((System.String)COMBO_CHANNEL.SelectedItem);

            for (int i = 0; i < MAXCHANNEL; i++)
            {
                if (hMediaSource[i] != 0)
                {
                    axXnsSdkWindowList[i].Stop();
                    axXnsSdkDevice1.CloseMedia(hDevice, hMediaSource[i]);
                    hMediaSource[i] = 0;
                }
            }

            setWindow(nVideo);
            if (nVideo > MAXCHANNEL)
                nVideo = MAXCHANNEL;

            if ((axXnsSdkDevice1.GetControlType(hDevice, 1) == ((int)XModelType.XCTL_DVR)))
            {
                int nChannelCount = axXnsSdkDevice1.GetControlCount(hDevice, ((int)XModelType.XCTL_CAMERA));

                for (int i = 0; i < nChannelCount && i < MAXCHANNEL && i < nVideo; i++)
                {
                    nControlID = axXnsSdkDevice1.GetVideoControlID(hDevice, i + 1, nProfileIndex + 1);
                    if ((axXnsSdkDevice1.GetControlCapability(hDevice, nControlID, ((int)XUnitCap.XCTL_CAP_LIVE)) == TRUE))
                    {
                        axXnsSdkDevice1.OpenMedia(hDevice, nControlID, (int)XMediaType.XMEDIA_LIVE, 0, 0, ref hMediaSource[i]);
                        axXnsSdkWindowList[i].Start(hMediaSource[i]);
                        m_DebugLog.WLOGW("Open media...control id=[" + nControlID + "]\n");
                    }
                }
             
            }
            else
            {
                int nProfileCount = axXnsSdkDevice1.GetControlCount(hDevice, ((int)XModelType.XCTL_VIDEO));

                for (int i = 0; i < nProfileCount && i < MAXCHANNEL && i < nVideo; i++)
                {
                    nControlID = axXnsSdkDevice1.GetVideoControlID(hDevice, nChannelIndex + 1, i + 1);
                    if ((axXnsSdkDevice1.GetControlCapability(hDevice, nControlID, ((int)XUnitCap.XCTL_CAP_LIVE)) == TRUE))
                    {
                        axXnsSdkDevice1.OpenMedia(hDevice, nControlID, (int)XMediaType.XMEDIA_LIVE, 0, 0, ref hMediaSource[i]);
                        axXnsSdkWindowList[i].Start(hMediaSource[i]);
                        m_DebugLog.WLOGW("Open media...control id=[" + nControlID + "]\n");
                    }
                }
            }

        }

        private void BTN_STOP_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < MAXCHANNEL; i++)
            {
                if (hMediaSource[i] !=0)
                {
                    axXnsSdkWindowList[i].Stop();
                    axXnsSdkDevice1.CloseMedia(hDevice, hMediaSource[i]);
                    hMediaSource[i] = 0;
                }
            }
            m_DebugLog.WLOGD("Media Close");
        }

        private void setWindowList()
        {
            axXnsSdkWindowList[0] = axXnsSdkWindow1;
            axXnsSdkWindowList[1] = axXnsSdkWindow2;
            axXnsSdkWindowList[2] = axXnsSdkWindow3;
            axXnsSdkWindowList[3] = axXnsSdkWindow4;
            axXnsSdkWindowList[4] = axXnsSdkWindow5;
            axXnsSdkWindowList[5] = axXnsSdkWindow6;
            axXnsSdkWindowList[6] = axXnsSdkWindow7;
            axXnsSdkWindowList[7] = axXnsSdkWindow8;
            axXnsSdkWindowList[8] = axXnsSdkWindow9;
            axXnsSdkWindowList[9] = axXnsSdkWindow10;
            axXnsSdkWindowList[10] = axXnsSdkWindow11;
            axXnsSdkWindowList[11] = axXnsSdkWindow12;
            axXnsSdkWindowList[12] = axXnsSdkWindow13;
            axXnsSdkWindowList[13] = axXnsSdkWindow14;
            axXnsSdkWindowList[14] = axXnsSdkWindow15;
            axXnsSdkWindowList[15] = axXnsSdkWindow16;

            axXnsSdkWindowList[0].Location = new Point(10, 17);
            axXnsSdkWindowList[0].Width = 576;
            axXnsSdkWindowList[0].Height = 432;

            for (int i = 1; i < MAXCHANNEL; i++)
                axXnsSdkWindowList[i].Hide();   
        }

        void setWindow(int _nVideo)
        {
            for (int i = 0; i < MAXCHANNEL; i++)
                axXnsSdkWindowList[i].Hide();

            int x = 10, y = 17;
            double ratio = Math.Sqrt(System.Convert.ToDouble(_nVideo));
            int nx = 576 / (int)ratio;
            int ny = 432 / (int)ratio;

            for (int i = 0; i < MAXCHANNEL; i++)
            {
                if (i < _nVideo)
                {
                    axXnsSdkWindowList[i].Location = new Point(x, y);
                    axXnsSdkWindowList[i].Width = nx;
                    axXnsSdkWindowList[i].Height = ny;

                    if ((i + 1) % ratio == 0)
                    {
                        y += ny;
                        x = 10;
                    }
                    else
                        x += nx;
                    axXnsSdkWindowList[i].Show();
                }
            }
        }

        private void axXnsSdkDevice1_OnDeviceStatusChanged(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEvent e)
        {
            m_DebugLog.WLOGD("OnDeviceStatusChanged() EVENT:: device_id=" + e.nDeviceID + ", status=" + e.nDeviceStatus +
               ", error=" + e.nErrorCode + "[" + axXnsSdkDevice1.GetErrorString(e.nErrorCode) + "]");
            if ((e.nErrorCode == (int)XErrorCode.ERR_SUCCESS) && (e.nDeviceStatus == 1))
            {
                m_DebugLog.WLOGD("Connected...");
                COMBO_CHANNEL.SelectedIndex = 0;
            }
        }
     
    }
}
