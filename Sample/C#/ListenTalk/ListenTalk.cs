///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011 by Hanwha Techwin, Inc.
//
// This software is copyrighted by, and is the sole property of Hanwha Techwin.
// All rigths, title, ownership, or other interests in the software remain the
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
// @ File Name :		ListenTalk.cs
// @ File Description : ListenTalk Form Source Code File. 
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


namespace ListenTalk
{
    public partial class ListenTalkForm : Form
    {
        private const string LOGIN_ID = "admin";
        private const string PASSWORD = "4321";
        private const string IP_ADDRESS = "192.168.100.201";
        private const string PORT_NUM = "4520";
        private const string HTTPPORT_NUM = "80";
        private const string MODEL_NAME = "Samsung Network Camera/Encoder";
        
        private const int TRUE = 1;
        private const int FALSE = 0;
        private const int NULL = 0;
        private const int XADDRESS_IP = 1;
        private const int CB_ERR = -1;

        private int hDevice = 0;
        private int hMediaSource = 0;
        private int nControlID = 0;
        private int nError = 0;
        
        private bool bSendAudio = false;

       
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
                int hFind = axXnsSdkDevice.FindModel("Samsung");

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
                EDIT_HTTPPORT.Text = HTTPPORT_NUM;
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
        }   


        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for Device Connect Function.
        // ----------------------------------------------------------------------- 
        private void BTN_CONNECT_Click(object sender, EventArgs e)
        {
            string strModel     = null;
            string strIpAddress = EDIT_IP.Text;
            int nPort           = int.Parse(EDIT_PORT.Text);
            int nHttpPort       = int.Parse(EDIT_HTTPPORT.Text);
            string strID        = EDIT_ID.Text;
            string strPW        = EDIT_PW.Text;
            
            int nDeviceProtocol = 0;

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
                int device_id = axXnsSdkDevice.CreateDeviceEx();
                hDevice = axXnsSdkDevice.GetDeviceHandle(device_id);

                if (hDevice == NULL)
                {
                    WLOGD("CreateDevice() fail");
                    return;
                }
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

            if ((axXnsSdkDevice.GetControlType(hDevice, 1) == ((int)XModelType.XCTL_NETCAM)) ||
                 (axXnsSdkDevice.GetControlType(hDevice, 1) == ((int)XModelType.XCTL_ENCODER)))
            {
                nControlID = axXnsSdkDevice.GetVideoControlID(hDevice, 1, 2);
            }
            else
            {
                nControlID = axXnsSdkDevice.GetVideoControlID(hDevice, 1, 1);
            }

            if ((axXnsSdkDevice.GetControlCapability(hDevice, nControlID, ((int)XUnitCap.XCTL_CAP_LIVE)) == TRUE))
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
                nRet = axXnsSdkDevice.OpenMedia(hDevice, nControlID, ((int)XMediaType.XMEDIA_LIVE), 0, 0, ref hMediaSource);
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

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for SendAudio Function.
        // ----------------------------------------------------------------------- 
        private void BTN_SEND_AUDIO_Click(object sender, EventArgs e)
        {
            if (bSendAudio)
            {
                WLOGD("Already Sending audio...\n");
                return;
            }
            bSendAudio = true;
            
            int nRet = axXnsSdkDevice.SendAudioData2(hDevice, nControlID); // [in] Device handle, [in] Control ID, 
            
            if (nRet != (int)XErrorCode.ERR_SUCCESS)
            {
                WLOGD("SendAudioData2() fail: ret=[" + nRet + "](" + axXnsSdkDevice.GetErrorString(nRet) + ")");
                return;
            }
        }

        // [ XNS ACTIVEX HELP ]
        // -----------------------------------------------------------------------
        // @ C# WinForm Button Event.
        // for StopAudio Function.
        // ----------------------------------------------------------------------- 
        private void BTN_STOP_AUDIO_Click(object sender, EventArgs e)
        {
            if (!bSendAudio)
            {
                WLOGD("Already Stop audio.\n");
                return;
            }

            int nRet = axXnsSdkDevice.StopAudioData2(hDevice); // [in] Device handle. 

            if (nRet != (int)XErrorCode.ERR_SUCCESS)
            {
                WLOGD("StopAudioData2() fail: ret=[" + nRet + "](" + axXnsSdkDevice.GetErrorString(nRet) + ")");
                return;
            }

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
                bSendAudio = false;
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
            bSendAudio = false;
            WLOGD("Connect Failed: DeviceID=" + e.nDeviceID +  "errcode=" + e.nErrorCode+"["+axXnsSdkDevice.GetErrorString(e.nErrorCode)+"]");
        }

    }
}
