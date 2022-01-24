'///////////////////////////////////////////////////////////////////////////////////
'// Copyright(c) 2011 by Samsung Techwin, Inc.
'//
'// This software is copyrighted by, and is the sole property of Samsung Techwin.
'// All rights, title, ownership, or other interests in the software remain the
'// property of Samsung Techwin. This software may only be used in accordance with
'// the corresponding license agreement. Any unauthorized use, duplication,
'// transmission, distribution, or disclosure of this software is expressly
'// forbidden.
'//
'// This Copyright notice may not be removed or modified without prior written
'// consent of Samsung Techwin.
'//
'// Samsung Techwin reserves the right to modify this software without notice.
'//
'// Samsung Techwin, Inc.
'// KOREA
'// http://www.samsungtechwin.co.kr
'///////////////////////////////////////////////////////////////////////////////////
'// @ File Name :		 SingleLive.vb
'// @ File Description : SingleLive Form Source Code File. 
'//						 Define the entire function.
'///////////////////////////////////////////////////////////////////////////////////

Partial Public Class SingleLive
    Private Const MODEL_NAME As String = "SNV-3080"
    Private Const IP_ADDRESS As String = "192.168.0.28"
    Private Const PORT_NUM As String = "60001"
    Private Const LOGIN_ID As String = "admin"
    Private Const PASSWORD As String = "4321"

    Private Const XADDRESS_IP As Integer = 1

    Dim hDevice As Integer = 0
    Dim hMediaSource As Integer = 0
    Dim nControlID As Integer = 0
    Dim nError As Integer = 0

    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Load Event.
    ' -----------------------------------------------------------------------
    Private Sub SingleLive_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Initializes the DLL files. 
        ' For this, XnsActiveX library requires config.xml, device.xml, 
        ' and xns.xml files and the DLL file list should be mentioned 
        ' in Xns.xml file. The path of the DLL file can not exceed 512 bytes
        ' in length. The XnsActiveX library searches for xns.xml using 
        ' XnsSDKDevice.ocx installed in "{$SDK path}\Config" folder.
        ' -----------------------------------------------------------------------
        nError = AxXnsSdkDevice.Initialize()
        WLOGD("Initialize():: " + "(" + nError.ToString + ") [" + AxXnsSdkDevice.GetErrorString(nError) + "]")

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Initializes the XnsSdkWindow control. 
        ' Namely, this will specify the window handle in order to display 
        ' images on the screen. 
        ' -----------------------------------------------------------------------
        AxXnsSdkWindow.Initialize(0, 0)
        WLOGW("Initialize():: " + "(" + nError.ToString + ") [" + AxXnsSdkDevice.GetErrorString(nError) + "]")

        '///////////////////////////
        ' ModelList ComboBox Setting

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Reads device list from {$SDK path}\Bin\Config\xns.xml. 
        ' Finds information mentioned in the configuration file before returning. 
        ' To enable this function, follow the steps below:
        ' < Procedure >
        ' Step 1. 	Use FindVendor(), FindModel(), FindDevice() to start searching.
        ' Step 2. 	Use GetFindSize to get the array size.
        ' Step 3. 	Use GetFindString() to obtain the vendor name and model name.
        ' Step 4. 	Use GetFindLong() and GetFindDouble0 to obtain the device ID. 
        '			(Repeat this process if necessary)
        ' Step 5. 	Call CloseFind0 to end the search.
        ' Returns the handle of the Find array. 
        ' Returns NULL(0) if no model list is found.
        ' -----------------------------------------------------------------------
        Dim hFind As Integer = AxXnsSdkDevice.FindModel("samsung")

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Returns the length of the array that is created using FindVendor(), 
        ' FindModel(), and FindDevice().
        ' -----------------------------------------------------------------------
        Dim hFindSize As Integer = AxXnsSdkDevice.GetFindSize(hFind)

        Dim strModel As String
        Dim i As Integer
        For i = 0 To hFindSize - 1
            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Reurns data of nIndex from the array created using FindVendor() 
            ' and FindModel(). If nIndex is larger than the actual array, 
            ' "" will be returned.
            ' -----------------------------------------------------------------------
            strModel = AxXnsSdkDevice.GetFindString(hFind, i)
            COMBO_MODEL_LIST.Items.Add(strModel)
        Next i

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Closes the Find command. Releases the memory space assinged by FindXXX().
        ' -----------------------------------------------------------------------
        AxXnsSdkDevice.CloseFind(hFind)

        COMBO_MODEL_LIST.SelectedIndex = 0
        Dim index = COMBO_MODEL_LIST.FindStringExact(MODEL_NAME, 0)
        If index <> -1 Then
            COMBO_MODEL_LIST.SelectedIndex = index
        End If

        ' Set User Information Text Box
        TEXT_IP.Text = IP_ADDRESS
        TEXT_PORT.Text = PORT_NUM
        TEXT_ID.Text = LOGIN_ID
        TEXT_PW.Text = PASSWORD

        'Set Button Enable
        BTN_DISCONNECT.Enabled = False
        BTN_MEDIA_OPEN.Enabled = False
        BTN_MEDIA_CLOSE.Enabled = False
        BTN_START.Enabled = False
        BTN_STOP.Enabled = False
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Button Event.
    ' for Device Connect Function.
    ' ----------------------------------------------------------------------- 
    Private Sub BTN_CONNECT_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTN_CONNECT.Click
        Dim strModel As String = COMBO_MODEL_LIST.SelectedItem
        Dim strIpAddress As String = TEXT_IP.Text
        Dim nPort As Integer = Integer.Parse(TEXT_PORT.Text)
        Dim strID As String = TEXT_ID.Text
        Dim strPW As String = TEXT_PW.Text

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Assigns memory space for saving device information. 
        ' This function will return the device handle, which the application 
        ' can use to control the device.
        ' [in] Device ID The value should be a greater integer than 0.
        ' Minimum value: 1 , Maximum value: 3000
        ' -----------------------------------------------------------------------
        hDevice = AxXnsSdkDevice.CreateDevice(1)
        If hDevice = 0 Then
            WLOGD("CreateDevice() fail")
            Return
        End If

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Sets the device information so that the application can connect 
        ' to the device.
        ' -----------------------------------------------------------------------
        AxXnsSdkDevice.SetConnectionInfo(hDevice, "samsung", strModel, XADDRESS_IP, strIpAddress, nPort, 0, strID, strPW)

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Enables the application to connect to the device using the connection 
        ' information. You can use SetConnectionInfo() to configure the 
        ' connection settings. This function performs as non-blocking function, 
        ' and will be returned immediately even if the connection is not 
        ' completed. The connection result will be transferred through the event. 
        ' When connection is made successfully, the OnDeviceStatusChanged() event
        ' will occur. When failed, the OnConnectFailed event occurs.
        ' -----------------------------------------------------------------------
        nError = AxXnsSdkDevice.ConnectNonBlock(hDevice, False, False)
        WLOGD("ConnectNonBlock():: " + "(" + nError.ToString + ") [" + AxXnsSdkDevice.GetErrorString(nError) + "]")

        If nError = 0 Then
            BTN_CONNECT.Enabled = False
            BTN_DISCONNECT.Enabled = True
            BTN_MEDIA_OPEN.Enabled = True
        End If
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Button Event.
    ' for Device DisConnect Function.
    ' ----------------------------------------------------------------------- 
    Private Sub BTN_DISCONNECT_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTN_DISCONNECT.Click
        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Check if there exists stream source.
        ' -----------------------------------------------------------------------
        If AxXnsSdkWindow.IsMedia() = True Then
            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Stops receiving the stream data from the media source handle.  
            ' -----------------------------------------------------------------------
            hMediaSource = AxXnsSdkWindow.Stop()
        End If

        If hMediaSource <> 0 Then
            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Terminates transferring media stream data from the device. The media 
            ' stream data will be separated by hMediaSource 
            ' (i.e., phMediaSource of OpenMedia()).
            ' -----------------------------------------------------------------------
            AxXnsSdkDevice.CloseMedia(hDevice, hMediaSource)
            hMediaSource = 0
        End If

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Disconnects from the device.
        ' -----------------------------------------------------------------------
        nError = AxXnsSdkDevice.Disconnect(hDevice)
        WLOGD("Disconnect():: " + "(" + nError.ToString + ") [" + AxXnsSdkDevice.GetErrorString(nError) + "]")

        If nError = XErrorCode.ERR_SUCCESS Then
            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Cancels the memory space assigned for the device information by 
            ' CreateDevice(). The device should be disconnected from the application 
            ' before this function is called.
            ' -----------------------------------------------------------------------
            AxXnsSdkDevice.ReleaseDevice(hDevice)

            BTN_CONNECT.Enabled = True
            BTN_DISCONNECT.Enabled = False
            BTN_MEDIA_OPEN.Enabled = False
            BTN_MEDIA_CLOSE.Enabled = False
            BTN_START.Enabled = False
            BTN_STOP.Enabled = False
        End If
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Button Event.
    ' for Media Open Function.
    ' ----------------------------------------------------------------------- 
    Private Sub BTN_MEDIA_OPEN_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTN_MEDIA_OPEN.Click
        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Returns the connection status of the device.
        ' -----------------------------------------------------------------------
        If AxXnsSdkDevice.GetDeviceStatus(hDevice) <> XConnect.XDEVICE_STATUS_CONNECTED Then
            WLOGD("Not connected")
            Return
        End If

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Returns the type of control module corresponding to the control ID.
        ' Control Module : DVR Check
        ' -----------------------------------------------------------------------
        If AxXnsSdkDevice.GetControlType(hDevice, 1) = XModelType.XCTL_DVR Then
            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Returns the number of control modules. 
            ' The application can get the number of specific type of control modules, 
            ' and can get also the whole number of video recorders or cameras.
            ' -----------------------------------------------------------------------
            Dim nCount As Integer = AxXnsSdkDevice.GetControlCount(hDevice, XModelType.XCTL_CAMERA)

            Dim i As Integer
            For i = 0 To nCount - 1
                ' [ XNS ACTIVEX HELP ]
                ' -----------------------------------------------------------------------
                ' Returns the capabilities of the control module.
                ' -----------------------------------------------------------------------
                If AxXnsSdkDevice.GetControlCapability(hDevice, i + 2, XUnitCap.XCTL_CAP_LIVE) <> 0 Then
                    ' [ XNS ACTIVEX HELP ]
                    ' -----------------------------------------------------------------------
                    ' When called, it will start getting media streams from the device.
                    ' The receiving media streams will, then, be forwarded to the XnsSdkWindow 
                    ' component that will play the streams after decoding.
                    ' phMediaSource is needed to link the stream data with XnsSdkWindow. 
                    ' The value can be obtained from a parameter (out-parameter) of OpenMedia(). 
                    ' When XnsSdkWindow receives this value, it can get stream data from the device.
                    ' phMediaSource is also used for controlling playback of multimedia files. 
                    ' As a result, the application should keep this value at all times.
                    ' -----------------------------------------------------------------------
                    nError = AxXnsSdkDevice.OpenMedia(hDevice, i + 2, XMediaType.XMEDIA_LIVE, 0, 0, hMediaSource)

                    If nError = XErrorCode.ERR_SUCCESS Then
                        WLOGD("Media Open Success.")
                        BTN_MEDIA_OPEN.Enabled = False
                        BTN_MEDIA_CLOSE.Enabled = True
                        BTN_START.Enabled = True
                        BTN_STOP.Enabled = False
                        nControlID = i + 2
                    Else
                        WLOGD("Media Open Failed.ret = (" + nError.ToString + ") [" + AxXnsSdkDevice.GetErrorString(nError) + "]")
                    End If
                    Return
                End If
            Next i
            ' Control Module : Network Camera or Encoder Box (video Server)
        ElseIf AxXnsSdkDevice.GetControlType(hDevice, 1) = XModelType.XCTL_NETCAM Or AxXnsSdkDevice.GetControlType(hDevice, 1) = XModelType.XCTL_ENCODER Then
            Dim nCount As Integer = AxXnsSdkDevice.GetControlCount(hDevice, XModelType.XCTL_VIDEO)
            Dim i As Integer
            For i = 0 To nCount - 1
                If AxXnsSdkDevice.GetControlCapability(hDevice, i + 3, XUnitCap.XCTL_CAP_LIVE) <> 0 Then
                    nError = AxXnsSdkDevice.OpenMedia(hDevice, i + 3, XMediaType.XMEDIA_LIVE, 0, 0, hMediaSource)
                    If nError = XErrorCode.ERR_SUCCESS Then
                        WLOGD("Media Open Success.")
                        BTN_MEDIA_OPEN.Enabled = False
                        BTN_MEDIA_CLOSE.Enabled = True
                        BTN_START.Enabled = True
                        BTN_STOP.Enabled = False
                        nControlID = i + 3
                    Else
                        WLOGD("Media Open Failed.ret = (" + nError.ToString + ") [" + AxXnsSdkDevice.GetErrorString(nError) + "]")
                    End If
                    Return
                End If
            Next i
        End If
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Button Event.
    ' for Media Close Function.
    ' ----------------------------------------------------------------------- 
    Private Sub BTN_MEDIA_CLOSE_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTN_MEDIA_CLOSE.Click
        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Check if there exists stream source.
        ' -----------------------------------------------------------------------
        If AxXnsSdkWindow.IsMedia() = True Then
            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Stops receiving the stream data from the media source handle.  
            ' -----------------------------------------------------------------------
            hMediaSource = AxXnsSdkWindow.Stop()
        End If

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Terminates transferring media stream data from the device. The media 
        ' stream data will be separated by hMediaSource 
        ' (i.e., phMediaSource of OpenMedia()).
        ' -----------------------------------------------------------------------
        nError = AxXnsSdkDevice.CloseMedia(hDevice, hMediaSource)
        If nError = XErrorCode.ERR_SUCCESS Then
            hMediaSource = 0
            BTN_MEDIA_OPEN.Enabled = True
            BTN_MEDIA_CLOSE.Enabled = False
            BTN_START.Enabled = False
            BTN_STOP.Enabled = False
            WLOGD("Media Close Success.")
        Else
            WLOGD("Media Close Failed.")
        End If
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Button Event.
    ' for Start Function.
    ' ----------------------------------------------------------------------- 
    Private Sub BTN_START_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTN_START.Click
        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Adds the media source handle to XnsSdkWindow. 
        ' The media source handle is created by XnsSdkDevice. 
        ' If the application calls XnsSdkDevice::OpenMedia(), 
        ' it will receive media stream from the device and return the MediaSource 
        ' handle. The application uses uses Start() to forward the mediasource 
        ' handle to XnsSdkWindow so that XnsSdkWindow can obtain stream data. 
        ' -----------------------------------------------------------------------
        nError = AxXnsSdkWindow.Start(hMediaSource)
        If nError = XErrorCode.ERR_SUCCESS Then
            BTN_START.Enabled = False
            BTN_STOP.Enabled = True
            WLOGW("Media Play Success.")
        Else
            WLOGW("Media Play Failed.")
        End If
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Button Event.
    ' for Stop Function.
    ' ----------------------------------------------------------------------- 
    Private Sub BTN_STOP_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTN_STOP.Click
        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Stops receiving the stream data from the media source handle.  
        ' -----------------------------------------------------------------------
        hMediaSource = AxXnsSdkWindow.Stop()
        If hMediaSource <> 0 Then
            BTN_START.Enabled = True
            BTN_STOP.Enabled = False
            BTN_MEDIA_CLOSE.Enabled = True
            WLOGW("Media Play Stopped.")
        End If
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ Device Control Event.
    ' This event occurs if the device status has changed. It occurs if the 
    ' application uses Connect() to connect or reconnect to the device after 
    ' disconnected. When reconnecting, the third argument nDeviceStatus is 
    ' true, all media must be reopened using ReopenAllStream().
    ' -----------------------------------------------------------------------
    Private Sub AxXnsSdkDevice_OnDeviceStatusChanged(ByVal sender As System.Object, ByVal e As AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEvent) Handles AxXnsSdkDevice.OnDeviceStatusChanged
        Dim strRet As String
        strRet = "OnDeviceStatusChanged() EVENT:: device_id=" + e.nDeviceID.ToString + ", status=" + e.nDeviceStatus.ToString
        WLOGD(strRet + ", error=" + e.nErrorCode.ToString + "[" + AxXnsSdkDevice.GetErrorString(e.nErrorCode) + "]")

        If e.nErrorCode = XErrorCode.ERR_SUCCESS Or e.nDeviceStatus = 1 Then
            WLOGD("Connected...")
        End If
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ Device Control Event.
    ' If the application has failed in non-blocking connection using ConnectNonBlock(), 
    ' the OnConnectFailed event occurs. 
    ' As Connect() returns an immediate error message if failed, 
    ' it does not trigger this event.
    ' -----------------------------------------------------------------------
    Private Sub AxXnsSdkDevice_OnConnectFailed(ByVal sender As System.Object, ByVal e As AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEvent) Handles AxXnsSdkDevice.OnConnectFailed
        WLOGD("OnConnectFailed() EVENT:: device_id=" + e.nDeviceID.ToString + ", error=" + e.nErrorCode.ToString + "[" + AxXnsSdkDevice.GetErrorString(e.nErrorCode) + "]")
    End Sub
End Class
