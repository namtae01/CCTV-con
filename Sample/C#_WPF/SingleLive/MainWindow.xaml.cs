using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;

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

    public partial class MainWindow : Window
    {
        AxXNSSDKDEVICELib.AxXnsSdkDevice AxXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
        AxXNSSDKWINDOWLib.AxXnsSdkWindow AxXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
          

        // Device Information
        private const string LOGIN_ID = "admin";
        private const string PASSWORD = "4321";
        private const string IP_ADDRESS = "192.168.1.106";
        private const string PORT_NUM = "4520";
        private const string HTTPPORT_NUM = "80";
        private const string MODEL_NAME = "Samsung Network Camera/Encoder";

        private const int TRUE = 1;
        private const int FALSE = 0;
        private const int NULL = 0;
        private const int XADDRESS_IP = 1;

        private int nDeviceProtocol = 0;
        private int nMediaProtocol = 0;
        private int hDevice = 0;
        private int hMediaSource = 0;
        private int nControlID = 0;
        private int nError = 0;
        private DebugLog m_DebugLog = null;

        public MainWindow()
        {
            InitializeComponent();
            m_DebugLog = new DebugLog(this.List_Log);

        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            DevicectrlHost.Child = AxXnsSdkDevice;
            int nError = AxXnsSdkDevice.Initialize();
            m_DebugLog.WLOGD("Initialize():: ", nError, AxXnsSdkDevice.GetErrorString(nError));

            WindowctrlHost1.Child = AxXnsSdkWindow;
            nError = AxXnsSdkWindow.Initialize(0,0);
            m_DebugLog.WLOGW("Initialize():: ", nError, AxXnsSdkDevice.GetErrorString(nError));

            AxXnsSdkDevice.OnDeviceStatusChanged +=new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(AxXnsSdkDevice_OnDeviceStatusChanged);
            AxXnsSdkDevice.OnConnectFailed +=new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(AxXnsSdkDevice_OnConnectFailed);

            SetDialog();
        }

        public void SetDialog()
        {
            {
                int hFind = AxXnsSdkDevice.FindModel("samsung");

                int hFindSize = AxXnsSdkDevice.GetFindSize(hFind);

                System.String strModel = null;
                for (int i = 0; i < hFindSize; i++)
                {
                    strModel = AxXnsSdkDevice.GetFindString(hFind, i);
                    Combo_Model.Items.Add(strModel);
                }

                AxXnsSdkDevice.CloseFind(hFind);

                Combo_Model.SelectedItem = MODEL_NAME;
            }

            // Set User Information Edit Box
            {
                Edit_Ip.Text = IP_ADDRESS;
                Edit_Device_Port.Text = PORT_NUM;
                Edit_Http_Port.Text = HTTPPORT_NUM;
                Edit_Id.Text = LOGIN_ID;
                Edit_Pw.Password = PASSWORD;
            }
            setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_DISCONNECTED);
        }

        private void Button_Connect_Click(object sender, RoutedEventArgs e)
        {
            string strModel = (System.String)Combo_Model.SelectedItem;
            string strIpAddress = Edit_Ip.Text;
            int nPort = int.Parse(Edit_Device_Port.Text);
            int nHttpPort = int.Parse(Edit_Http_Port.Text);
            string strID = Edit_Id.Text;
            string strPW = Edit_Pw.Password;
          
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Assigns memory space for saving device information. 
            // This function will return the device handle, which the application 
            // can use to control the device.
            // [in] Device ID The value should be a greater integer than 0.
            // Minimum value: 1 , Maximum value: 3000
            // -----------------------------------------------------------------------
            int device_id = AxXnsSdkDevice.CreateDeviceEx();
            hDevice = AxXnsSdkDevice.GetDeviceHandle(device_id);

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
            this.AxXnsSdkDevice.SetConnectionInfo2(
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
            nError = AxXnsSdkDevice.ConnectNonBlock(
                hDevice,            // [in] Device handle. This value is returned from CreateDevice(). 
                0,              // [in] Flag to decide where to forcibly log in or not.
                0);             // [in] When the device is disconnected, you can use this flag to decide
            //      if to connect again automatically. If this value is 1, try to connect again.
	        if(nError != (int)XErrorCode.ERR_SUCCESS)
	        {
		        m_DebugLog.WLOGD("ConnectNonBlock() fail: errno=[%d](%s)\n", 
			        nError, AxXnsSdkDevice.GetErrorString(nError));
		        setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_DISCONNECTED);
	        }
	        else
	        {
                m_DebugLog.WLOGD("ConnectNonBlock():: ", nError, AxXnsSdkDevice.GetErrorString(nError));
	        }	
            
        }

        private void Button_Disconnect_Click(object sender, RoutedEventArgs e)
        {
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Check if there exists stream source.
            // -----------------------------------------------------------------------
            if (AxXnsSdkWindow.IsMedia() == TRUE)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Stops receiving the stream data from the media source handle.  
                // -----------------------------------------------------------------------
                hMediaSource = AxXnsSdkWindow.Stop();
            }

            if (hMediaSource != 0)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Terminates transferring media stream data from the device. The media 
                // stream data will be separated by hMediaSource 
                // (i.e., phMediaSource of OpenMedia()).
                // -----------------------------------------------------------------------
                AxXnsSdkDevice.CloseMedia(hDevice, hMediaSource);
                hMediaSource = 0;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Disconnects from the device.
            // -----------------------------------------------------------------------
            nError = AxXnsSdkDevice.Disconnect(hDevice);
            m_DebugLog.WLOGD("Disconnect():: ", nError, AxXnsSdkDevice.GetErrorString(nError));

            if (nError == (int)XErrorCode.ERR_SUCCESS)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Cancels the memory space assigned for the device information by 
                // CreateDevice(). The device should be disconnected from the application 
                // before this function is called.
                // -----------------------------------------------------------------------
                AxXnsSdkDevice.ReleaseDevice(hDevice);
                setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_DISCONNECTED);
            }
        }

        private void Button_Media_Open_Click(object sender, RoutedEventArgs e)
        {
            if (AxXnsSdkDevice.GetDeviceStatus(hDevice) != ((int)XConnect.XDEVICE_STATUS_CONNECTED))
            {
                m_DebugLog.WLOGD("Not connected");
                return;
            }

            if (hMediaSource !=0)
            {
                m_DebugLog.WLOGD("Media stream was already opened.. close and reopen\n");
                AxXnsSdkDevice.CloseMedia(hDevice, hMediaSource);
                hMediaSource = 0;
            }

            int nChannel = 1;
            int nProfile = 2;
            nControlID = AxXnsSdkDevice.GetVideoControlID(hDevice, nChannel, nProfile);

            AxXnsSdkDevice.OpenMedia(hDevice, nControlID, ((int)XMediaType.XMEDIA_LIVE), 0, 0, ref hMediaSource);

            if (nError == (int)XErrorCode.ERR_SUCCESS)
            {
                m_DebugLog.WLOGD("Media Open Success.");
                setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_OPEN);
            }
            else
            {
                m_DebugLog.WLOGD("Media Open Failed.ret=" + nError.ToString() + "[" + AxXnsSdkDevice.GetErrorString(nError) + "]");
            }
        }


        private void Button_Media_Close_Click(object sender, RoutedEventArgs e)
        {
            if (hMediaSource==0)
            {
                m_DebugLog.WLOGD("May be device is not opened\n");
                setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_CLOSE);
                return;
            }
            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Check if there exists stream source.
            // -----------------------------------------------------------------------
            if (AxXnsSdkWindow.IsMedia() == TRUE)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Stops receiving the stream data from the media source handle.  
                // -----------------------------------------------------------------------
                hMediaSource = AxXnsSdkWindow.Stop();
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Terminates transferring media stream data from the device. The media 
            // stream data will be separated by hMediaSource 
            // (i.e., phMediaSource of OpenMedia()).
            // -----------------------------------------------------------------------
            nError = AxXnsSdkDevice.CloseMedia(hDevice, hMediaSource);
            switch (nError)
            {
                case (int)XErrorCode.ERR_SUCCESS:
                    hMediaSource = 0;
                    m_DebugLog.WLOGD("Media Close Success.");
                    setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_CLOSE);
                    break;
                default:
                    m_DebugLog.WLOGD("Media Close Failed.");
                    break;
            }
        }

        private void Button_Start_Click(object sender, RoutedEventArgs e)
        {
            if (hMediaSource == 0)
            {
                m_DebugLog.WLOGD("Media stream was not opened\n");
                return;
            }
            if (AxXnsSdkWindow.IsMedia() == TRUE)
            {
                m_DebugLog.WLOGW("Media stream is already played\n");
                return;
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
            nError = AxXnsSdkWindow.Start(hMediaSource);
            switch (nError)
            {
                case (int)XErrorCode.ERR_SUCCESS:
                    m_DebugLog.WLOGW("Media Play Success.");
                    setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_START);
                    break;
                default:
                    m_DebugLog.WLOGW("Media Play Failed.");
                    break;
            }
        }


        private void Button_Stop_Click(object sender, RoutedEventArgs e)
        {
            if (hMediaSource == 0)
            {
                m_DebugLog.WLOGD("Media stream was not opened\n");
                return;
            }

            if (AxXnsSdkWindow.IsMedia() != TRUE)
            {
                m_DebugLog.WLOGW("Media stream is not played\n");
                return;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Stops receiving the stream data from the media source handle.  
            // -----------------------------------------------------------------------
            hMediaSource = AxXnsSdkWindow.Stop();
            if (hMediaSource != 0)
            {
                m_DebugLog.WLOGW("Media Play Stopped.");
                setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_STOP);
            }
        }

        // Control button enable/disable
    void setBtnStatus(SingleLive_ButtonStatus nStatus)
    {
        bool conn = true, disconn = true, start = true, stop = true, close = true, open = true;//, model = true, d_protocol = true, m_protocol = true;
	    switch(nStatus)
	    {
            case SingleLive_ButtonStatus.SL_STATUS_CONNECTED:
                conn = false;
                disconn = true;
                open = true;
                close = false;
                start = false;
                stop = false;
                break;
            case SingleLive_ButtonStatus.SL_STATUS_DISCONNECTED:
                conn = true;
                disconn = false;
                open = false;
                close = false;
                start = false;
                stop = false;
                break;
            case SingleLive_ButtonStatus.SL_STATUS_OPEN:
                conn = false;
                disconn = true;
                open = false;
                close = true;
                start = true;
                stop = false;
                break;
            case SingleLive_ButtonStatus.SL_STATUS_CLOSE:
                conn = false;
                disconn = true;
                open = true;
                close = false;
                start = false;
                stop = false;
                break;
            case SingleLive_ButtonStatus.SL_STATUS_START:
                conn = false;
                disconn = true;
                open = false;
                close = true;
                start = false;
                stop = true;
                break;
            case SingleLive_ButtonStatus.SL_STATUS_STOP:
                conn = false;
                disconn = true;
                open = false;
                close = true;
                start = true;
                stop = false;
                break;
	    }

        Combo_Model.IsEnabled = conn;
        Edit_Ip.IsEnabled = conn;
        Edit_Device_Port.IsEnabled = conn;
        Edit_Http_Port.IsEnabled = conn;
        Edit_Id.IsEnabled = conn;
        Edit_Pw.IsEnabled = conn;
        
        Button_Connect.IsEnabled = conn;
        Button_Disconnect.IsEnabled = disconn;
        Button_Media_Open.IsEnabled = open;
        Button_Media_Close.IsEnabled = close;
        Button_Start.IsEnabled = start;
        Button_Stop.IsEnabled = stop;

        SetCheckSunapi();
    }

        private void AxXnsSdkDevice_OnDeviceStatusChanged(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEvent e)
        {
            m_DebugLog.WLOGD("OnDeviceStatusChanged() EVENT:: device_id=" + e.nDeviceID + ", status=" + e.nDeviceStatus +
               ", error=" + e.nErrorCode + "[" + AxXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
            if ((e.nErrorCode == (int)XErrorCode.ERR_SUCCESS) && (e.nDeviceStatus == 1))
            {
                setBtnStatus(SingleLive_ButtonStatus.SL_STATUS_CONNECTED);
                m_DebugLog.WLOGD("Connected...");
            }
        }

        private void AxXnsSdkDevice_OnConnectFailed(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEvent e)
        {
            m_DebugLog.WLOGD("OnConnectFailed() EVENT:: device_id=" + e.nDeviceID +
                 ", error=" + e.nErrorCode + "[" + AxXnsSdkDevice.GetErrorString(e.nErrorCode) + "]");
        }

        private void Combo_Model_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            SetCheckSunapi();
        }

        private void checkBox_Sunapi_Checked(object sender, RoutedEventArgs e)
        {
            SetCheckSunapi();
        }

        private void SetCheckSunapi()
        {
            checkBox_Sunapi.IsEnabled = false;

            nDeviceProtocol = (int)XDeviceProtocolType.XDEVICE_PROTOCOL_UNKNOWN;
            
            string strModel = (System.String)Combo_Model.SelectedItem;

            if (strModel == "Samsung Network Camera/Encoder" || strModel == "Samsung NVR")
            {
                if (checkBox_Sunapi.IsChecked == true)
                    nDeviceProtocol = (int)XDeviceProtocolType.XDEVICE_PROTOCOL_SUNAPI;
                if (AxXnsSdkDevice.GetDeviceStatus(hDevice) != (int)XConnect.XDEVICE_STATUS_CONNECTED)
                    checkBox_Sunapi.IsEnabled = true;
            }
        }
    }
}
