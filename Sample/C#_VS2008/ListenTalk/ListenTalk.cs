///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011 by Samsung Techwin, Inc.
//
// This software is copyrighted by, and is the sole property of Samsung Techwin.
// All rigths, title, ownership, or other interests in the software remain the
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
// @ File Name :		ListenTalk.cs
// @ File Description : ListenTalk Form Source Code File. 
//						Define the entire function.
// @ File Date :		2011.08.02
// @ File Version :		Version 1.0
// @ File Writer :		Samsung-Techwin Engineer (Kang.Jeongkoo)
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
using System.IO;
using System.Threading;

using System.Media;
using HANDLE = System.IntPtr;

namespace ListenTalk
{
    public partial class ListenTalkForm : Form
    {
        private WAVEFORMATEX waveFormat;
        private const uint WAVE_MAPPER = unchecked((uint)(-1));
        private const short WAVE_FORMAT_PCM = 0x0001;
        private const uint WAVE_FORMAT_FLAG = 0x00010000;
        private IntPtr waveInHandle = IntPtr.Zero;
        private IntPtr waveInEvent = IntPtr.Zero;

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // Audio Codec PCM information
        // 1. Bits per sample, sample per seconds
        //    - 16, 8000
        //      * IMA ADPCM (SNC-570, SND-560/460V, SNP-370/3350)
        //      * G726 504X (SNC-550, SNS-100/400, SNP-1000A/3300A
        //      * G726 SNR (SNR-6400/3200)
        //      * G723 SVR
        //      * G711 IPCAM
        //      * G711U HISILICON
        //    - 16, 16000
        //      * G723
        //      * DVI4 HISILICON (SRD-1640/840/440/442)
        //    - another
        //      * 8, 8000
        // 2. Notify size
        //    - 4096
        //      * G726 504X
        //      * G726 SNR
        //    - 4000
        //      * G711 IPCAM
        //    - 6400
        //      * G723
        //    - 3200
        //      * G711U HISILICON
        //      * DVI4 HISILICON
        // -----------------------------------------------------------------------
        //SNP-1000A
        
          private const string LOGIN_ID = "admin";
          private const string PASSWORD = "4321";
          private const string IP_ADDRESS = "192.168.1.100";
          private const string PORT_NUM = "4000";
          private const string MODEL_NAME = "SNP-1000A";
          private const int CHANNEL_NUM = 1;
          private const int BIT_PER_SAMPLE = 16;
          private const int SAMPLE_PER_SEC = 8000;
          private const int BUFF_NUM = 200;
          private const int NOTIFY_SIZE = 8192;
          private const int TIME_OFFSET = 400;
         
        //IPCAM PCM INFO : SND-7080
//        private const string LOGIN_ID = "admin";
//        private const string PASSWORD = "1234";
        //private const string IP_ADDRESS = "192.168.1.101";
//        private const string PORT_NUM = "4520";
//        private const string MODEL_NAME = "SND-7080";
//        private const int CHANNEL_NUM = 1;
//        private const int BIT_PER_SAMPLE = 16;
//        private const int SAMPLE_PER_SEC = 8000;
  //      private const int BUFF_NUM = 200;
    //    private const int NOTIFY_SIZE = 4000;
      //  private const int TIME_OFFSET = 250;

        private const int TRUE = 1;
        private const int FALSE = 0;
        private const int NULL = 0;
        private const int XADDRESS_IP = 1;
        private const int CB_ERR = -1;

        private const UInt32 INFINITE = 0xFFFFFFFF;
        private const UInt32 WAIT_ABANDONED = 0x00000080;
        private const UInt32 WAIT_OBJECT_0 = 0x00000000;
        private const UInt32 WAIT_TIMEOUT = 0x00000102;



        private int hDevice = 0;
        private int hMediaSource = 0;
        private int nControlID = 0;
        private int nError = 0;
        
        private int nChannel = 0;
        private int nBps = 0;
        private int nSps = 0;
        private bool bSendAudio = false;

        //WAVE TALK

        
        byte[][] WaveBuffer = new byte[BUFF_NUM][];
        WAVEHDR[] WaveHeader = new WAVEHDR[BUFF_NUM];
        

        int curr_in = 0;
 
        bool bTerminate_thread_in = false;
        int tick_count = 0;
        int notify_size = 0;



        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Load Event.
        // -----------------------------------------------------------------------
        public ListenTalkForm()
        {
            InitializeComponent();
        }

        private void ListenTalkForm_Load(object sender, EventArgs e)
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
            WLOGD(nError, axXnsSdkDevice.GetErrorString(nError));

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Initializes the XnsSdkWindow control. 
            // Namely, this will specify the window handle in order to display 
            // images on the screen. 
            // -----------------------------------------------------------------------
            nError = axXnsSdkWindow.Initialize(0, 0);
            WLOGW(nError, axXnsSdkDevice.GetErrorString(nError));

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
                // -----------------------------------------------------------------------
                // Returns the handle of the Find array. 
                // Returns NULL(0) if no model list is found.
                int hFind = axXnsSdkDevice.FindModel("samsung");

                // Returns the length of the array that is created using FindVendor(), 
                // FindModel(), and FindDevice().
                int hFindSize = axXnsSdkDevice.GetFindSize(hFind);

                System.String strModel = null;
                for (int i = 0; i < hFindSize; i++)
                {
                    // Reurns data of nIndex from the array created using FindVendor() 
                    // and FindModel(). If nIndex is larger than the actual array, 
                    // "" will be returned.
                    strModel = axXnsSdkDevice.GetFindString(hFind, i);
                    COMBO_MODELLIST.Items.Add(strModel);
                }

                // Closes the Find command. Releases the memory space assinged by FindXXX().
                axXnsSdkDevice.CloseFind(hFind);

                COMBO_MODELLIST.SelectedIndex = 0;
                int idx = COMBO_MODELLIST.FindStringExact(MODEL_NAME, 0);
                if (idx != -1)
                {
                    COMBO_MODELLIST.SelectedIndex = idx;
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
                BTN_STOP.Enabled = false;
                BTN_PLAY.Enabled = false;
                BTN_SEND_AUDIO.Enabled = false;
                BTN_STOP_AUDIO.Enabled = false;
            }

            // Channel ComboBox Setting
            {
                COMBO_CHANNEL.Items.Add("1");
                COMBO_CHANNEL.Items.Add("2");
                COMBO_CHANNEL.SelectedIndex = 0;
                int idx = COMBO_CHANNEL.FindStringExact(CHANNEL_NUM.ToString(), 0);
                if (idx != CB_ERR)
                {
                    COMBO_CHANNEL.SelectedIndex = idx;
                }
            }

            // Bit per Sample ComboBox Setting
            {
                COMBO_BIT_PER_SAMPLE.Items.Add("8");
                COMBO_BIT_PER_SAMPLE.Items.Add("16");
                COMBO_BIT_PER_SAMPLE.Items.Add("32");
                COMBO_BIT_PER_SAMPLE.SelectedIndex = 0;
                int idx = COMBO_BIT_PER_SAMPLE.FindStringExact(BIT_PER_SAMPLE.ToString(), 0);
                if (idx != CB_ERR)
                {
                    COMBO_BIT_PER_SAMPLE.SelectedIndex = idx;
                }
            }

            // Sample per Second ComboBox Setting
            {
                COMBO_SAMPLE_PER_SECOND.Items.Add("8000");
                COMBO_SAMPLE_PER_SECOND.Items.Add("16000");
                COMBO_SAMPLE_PER_SECOND.Items.Add("32000");
                COMBO_SAMPLE_PER_SECOND.SelectedIndex = 0;
                int idx = COMBO_SAMPLE_PER_SECOND.FindStringExact(SAMPLE_PER_SEC.ToString(), 0);
                if (idx != CB_ERR)
                {
                    COMBO_SAMPLE_PER_SECOND.SelectedIndex = idx;
                }
            }
            EDIT_SEND_BYTES.Text = NOTIFY_SIZE.ToString();
         
            
        }   


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Device Connect Function.
        // ----------------------------------------------------------------------- 
        private void BTN_CONNECT_Click(object sender, EventArgs e)
        {
            string strModel = null;
            string strIpAddress = EDIT_IP.Text;
            string strPort = EDIT_PORT.Text;
            string strID = EDIT_ID.Text;
            string strPW = EDIT_PW.Text;
            int nPort = int.Parse(strPort);

            strModel = (System.String)COMBO_MODELLIST.SelectedItem;

            if (hDevice == NULL)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Assigns memory space for saving device information. 
                // This function will return the device handle, which the application 
                // can use to control the device.
                // [in] Device ID The value should be a greater integer than 0.
                //      Minimum value: 1 , Maximum value: 3000
                // -----------------------------------------------------------------------
                hDevice = axXnsSdkDevice.CreateDevice(1);
                if (hDevice == NULL)
                {
                    WLOGD("CreateDevice() fail");
                    return;
                }
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
            int nRet = axXnsSdkDevice.ConnectNonBlock(
                hDevice,            // [in] Device handle. This value is returned from CreateDevice(). 
                FALSE,              // [in] Flag to decide where to forcibly log in or not.
                FALSE);             // [in] When the device is disconnected, 
                                    //      you can use this flag to decide if to connect again automatically. 
                                    //      If this value is 1, try to connect again.

            if (nRet != (int)XErrorCode.ERR_SUCCESS)
            {
                WLOGD("ConnectNonBlock() fail: errno=", nError, axXnsSdkDevice.GetErrorString(nError));
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
            // Disconnects from the device.
            // -----------------------------------------------------------------------
            int nRet = axXnsSdkDevice.Disconnect(hDevice);

            if (nRet != (int)XErrorCode.ERR_SUCCESS)
            {
                WLOGD("Disconnect Error! Code : ", nError, axXnsSdkDevice.GetErrorString(nError));
                return;
            }

            BTN_CONNECT.Enabled = true;
            BTN_DISCONNECT.Enabled = false;
            BTN_PLAY.Enabled = false;
            BTN_STOP.Enabled = false;
            WLOGD("DIsConnect! Code : ", nError, axXnsSdkDevice.GetErrorString(nError));
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Play Function.
        // ----------------------------------------------------------------------- 
        private void BTN_PLAY_Click(object sender, EventArgs e)
        {
            int nRet = 0;

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Returns the type of control module corresponding to the control ID.
            //
            // < DVR control module structure >
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
            // -----------------------------------------------------------------------
            if (axXnsSdkDevice.GetControlType(hDevice, 1) == (int)XModelType.XCTL_DVR)
            {
                // [ XNS ACTIVEX HELP ]
                // -----------------------------------------------------------------------
                // Returns the capabilities of the control module.
                // -----------------------------------------------------------------------
                int nCount = axXnsSdkDevice.GetControlCount(hDevice, (int)XModelType.XCTL_CAMERA);
                for (int i = 0; i < nCount; i++)
                {
                    if ((axXnsSdkDevice.GetControlCapability(hDevice, i + 2, ((int)XUnitCap.XCTL_CAP_LIVE)) == TRUE))
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

            // Control Module : Network Camera or Encoder Box (Video Server)
            else if ((axXnsSdkDevice.GetControlType(hDevice, 1) & ((int)XModelType.XCTL_NETCAM | (int)XModelType.XCTL_ENCODER)) != FALSE)
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
                WLOGD("Media Open Failed.");
                return;
            }
            WLOGD("Media Open Success.");

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Adds the media source handle to XnsSdkWindow. 
            // The media source handle is created by XnsSdkDevice. 
            // If the application calls XnsSdkDevice::OpenMedia(), 
            // it will receive media stream from the device and return the MediaSource 
            // handle. The application uses uses Start() to forward the mediasource 
            // handle to XnsSdkWindow so that XnsSdkWindow can obtain stream data. 
            // -----------------------------------------------------------------------
            nRet = axXnsSdkWindow.Start(hMediaSource);
            if (nRet != (int)XErrorCode.ERR_SUCCESS)
            {
                WLOGW("Media Play Failed.");
                return;
            }
            BTN_PLAY.Enabled = false;
            BTN_STOP.Enabled = true;
            WLOGW("Media Play Success.");
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
                BTN_PLAY.Enabled = true;
                BTN_STOP.Enabled = false;
                WLOGW("Media Play Stopped.");
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
                WLOGD("Media Close Failed.");
                return;
            }
            hMediaSource = 0;
            WLOGD("Media Close Success.");
        }

        // Thread
        public void WaveInThreadProc()
        {
            WaitForSingleObject(waveInEvent, INFINITE);
            tick_count = 0;
            
            while (true)
            {
                if ((WaitForSingleObject(waveInEvent,INFINITE) == WAIT_OBJECT_0)  && (!bTerminate_thread_in))
                {
                    int nRet = 0;
                    // [ XNS ACTIVEX HELP ]
                    // -----------------------------------------------------------------------
                    // Transfers the audio data to the device. This function is used when 
                    // the application transfers the audio data to the device using Talk. 
                    // Then, the audio data should be encoded to be suitable for the device. 
                    // This function is valid only in live mode. 
                    // -----------------------------------------------------------------------
//                     nRet = axXnsSdkDevice.SendAudioData(
  //                       hDevice,					// [in] Device handle. This value is returned from CreateDevice()
    //                     &WaveBuffer[curr_in], // [in] Pointer to indicate the memory where the audio data is stored.
      //                   notify_size,						// [in] Length of the audio data to transfer.
        //                 tick_count							// [in] TimeStamp (msec)
          //               );

                     
                    string cur_time = DateTime.Now.ToString("hh:mm:ss ") + DateTime.Now.Millisecond;
                    WLOGD(cur_time + "SendAudioData:: idx=" + curr_in + ", send=" + notify_size + 
                        "bytes, ret=" + nRet + axXnsSdkDevice.GetErrorString(nRet));
                    tick_count += TIME_OFFSET;
                    curr_in++;
                    if (curr_in >= BUFF_NUM)
                    {
                        curr_in = 0;
                    }

                    waveInUnprepareHeader(waveInHandle, ref WaveHeader[curr_in], (uint)Marshal.SizeOf(typeof(WAVEHDR)));
                    waveInPrepareHeader(waveInHandle, ref WaveHeader[curr_in], (uint)Marshal.SizeOf(typeof(WAVEHDR)));
                    waveInAddBuffer(waveInHandle, ref WaveHeader[curr_in], (uint)Marshal.SizeOf(typeof(WAVEHDR)));
                    continue;
                }
                break;
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for SendAudio Function.
        // ----------------------------------------------------------------------- 
        private void BTN_SEND_AUDIO_Click(object sender, EventArgs e)
        {
            if (bSendAudio == true)
            {
                WLOGD("Already Sending audio");
                return;
            }
            bSendAudio = true;

            nChannel = int.Parse((System.String)COMBO_CHANNEL.SelectedItem);
            nBps = int.Parse((System.String)COMBO_BIT_PER_SAMPLE.SelectedItem);
            nSps = int.Parse((System.String)COMBO_SAMPLE_PER_SECOND.SelectedItem);
            WLOGD("SendAudio:: channel=" + nChannel + ", bps=" + nBps +
                ", sps=" + nSps + ", packet=" + EDIT_SEND_BYTES.Text);
            notify_size = int.Parse((System.String)EDIT_SEND_BYTES.Text);

            for(int i=0; i<BUFF_NUM;i++)
	        {
		        if(WaveBuffer[i] != null)
		        {
			        WaveBuffer[i] = null;
		        }
                int nSendBytes = int.Parse(EDIT_SEND_BYTES.Text);
		        WaveBuffer[i] = new byte[nSendBytes];
	        }

           // memset((Char)ref waveFormat)
            // Initialize Record format
            waveFormat.wFormatTag       = (ushort)WAVE_FORMAT_PCM;
            waveFormat.nChannels        = (ushort)nChannel;
            waveFormat.nSamplesPerSec   = (uint)nSps;
            waveFormat.wBitsPerSample   = (ushort)nBps;
            waveFormat.nBlockAlign      = (ushort)(nChannel * nBps / 8);
            waveFormat.nAvgBytesPerSec  = (uint)(nSps * waveFormat.nBlockAlign);
            waveFormat.cbSize           = 0;

            // Create Thread for recording by event
            bTerminate_thread_in = false;
            curr_in = 0;
            waveInEvent = CreateEvent(HANDLE.Zero, false, false, null);
            Thread th = new Thread(new ThreadStart(WaveInThreadProc));
            th.Start();

            // Start Recording
            uint result = waveInOpen(ref waveInHandle, WAVE_MAPPER, ref waveFormat, waveInEvent, 0, (uint)(WaveInOpenFlags.CALLBACK_EVENT));
            for (int i = 0; i < BUFF_NUM; i++)
            {
                IntPtr unmanagedPointer = Marshal.AllocHGlobal(WaveBuffer[i].Length);
                Marshal.Copy(WaveBuffer[i], 0, unmanagedPointer, WaveBuffer[i].Length);

                WaveHeader[i].lpData = unmanagedPointer;
                WaveHeader[i].dwBufferLength = uint.Parse(EDIT_SEND_BYTES.Text);
                waveInPrepareHeader(waveInHandle, ref WaveHeader[i], (uint)Marshal.SizeOf(typeof(WAVEHDR)));
                waveInAddBuffer(waveInHandle, ref WaveHeader[i], (uint)Marshal.SizeOf(typeof(WAVEHDR)));

                // Call unmanaged code 
               // Marshal.FreeHGlobal(unmanagedPointer);
            }
            waveInStart(waveInHandle);
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for StopAudio Function.
        // ----------------------------------------------------------------------- 
        private void BTN_STOP_AUDIO_Click(object sender, EventArgs e)
        {
            waveInStop(waveInHandle);
            waveInReset(waveInHandle);
            waveInClose(waveInHandle);
            bSendAudio = false;
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm CheckBox Event.
        // for Listen Function.
        // ----------------------------------------------------------------------- 
        private void CHECK_LISTEN_CheckedChanged(object sender, EventArgs e)
        {
            if(axXnsSdkDevice.GetControlCapability(hDevice, nControlID, (int)XUnitCap.XCTL_CAP_LISTEN) == FALSE)
            {
                WLOGD("Do not support");
                return;
            }
            int bListen = FALSE;
            if (CHECK_LISTEN.Checked == true)
            {
                bListen = TRUE;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Enable or disable the Listen icon from XnsSDKWindow control, 
            // when the Listen function is set to ON or OFF. Turns on or off the 
            // Listen function. Listen enables the application to play the audio 
            // source. To enable this function, the control module should support 
            // XCTL_CAP_LISTEN capability. 
            // -----------------------------------------------------------------------
            int nRet = axXnsSdkDevice.SetListen(
                hDevice,		            	// [in] Device handle. 
                nControlID,		                // [in] Control ID,
                (int)XMediaType.XMEDIA_LIVE,	// [in] Media type.
                                                //      * XMEDIA_LIVE(=1):Live, 
                                                //      * XMEDIA_PLAYBACK(=2):Playback
                bListen);		            	// [in] Listen is activated.
                
            if (nRet != (int)XErrorCode.ERR_SUCCESS)
            {
                WLOGD("SetListen() fail: ret=["+nRet + "](" + axXnsSdkDevice.GetErrorString(nRet) + ")");
                return;
            }
            WLOGD("SetListen() flag=" + bListen);


            // Turns on or off the sound. 
            axXnsSdkWindow.SetSound(bListen);

            // Specify the volume level of the sound.
            if (bListen == TRUE)
            {
                axXnsSdkWindow.SetVolume(100);
            }
        }


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm CheckBox Event.
        // for Listen Function.
        // ----------------------------------------------------------------------- 
        private void CHECK_TALK_CheckedChanged(object sender, EventArgs e)
        {
            int bTalk = FALSE;
            if (CHECK_TALK.Checked == true)
            {
                bTalk = TRUE;
            }

            // [ XNS ACTIVEX HELP ]
            // -----------------------------------------------------------------------
            // Turns on or off the Talk function. 
            // Talk can enable the device to play the audio source. 
            // The application should use SendAudioData() to transfer the audio 
            // source that it wants to play. Talk is available only in live streaming 
            // mode and only if the control module supports XCTL_CAP_TALK capability. 
            // -----------------------------------------------------------------------
            int nRet = axXnsSdkDevice.SetTalk(
                hDevice,			// [in] Device handle.
                nControlID,		    // [in] Control ID
                bTalk);    	    	// [in] Talk is activated.
                
            if (nRet != (int)XErrorCode.ERR_SUCCESS)
            {
                WLOGD("SetTalk() fail: ret=[" + nRet + "](" + axXnsSdkDevice.GetErrorString(nRet) + ")");
                return;
            }
            WLOGD("SetTalk() flag=" + bTalk);
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
            if (e.nErrorCode != (int)XErrorCode.ERR_SUCCESS || e.nDeviceStatus != 1)
            {
                WLOGD("Disconnected!");
                return;
            }

            WLOGD("Connected: DeviceID=" + e.nDeviceID + " DeviceStatus=" + e.nDeviceStatus);

            BTN_CONNECT.Enabled = false;
            BTN_DISCONNECT.Enabled = true;
            BTN_PLAY.Enabled = true;
            BTN_SEND_AUDIO.Enabled = true;
            BTN_STOP_AUDIO.Enabled = true;
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
            WLOGD("Connect Failed: DeviceID=" + e.nDeviceID +  "errcode=" + e.nErrorCode+"["+axXnsSdkDevice.GetErrorString(e.nErrorCode)+"]");
        }
    }
}
