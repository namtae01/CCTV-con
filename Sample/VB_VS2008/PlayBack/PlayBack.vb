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
'// @ File Name :		 PlayBack.vb
'// @ File Description : PlayBack Form Source Code File. 
'//						 Define the entire function.
'///////////////////////////////////////////////////////////////////////////////////

Imports System
Imports System.Collections.Generic


Partial Public Class PlayBack
    Private Const MODEL_NAME As String = "SRD-165X"
    Private Const IP_ADDRESS As String = "192.168.0.131"
    Private Const PORT_NUM As String = "554"
    Private Const LOGIN_ID As String = "1"
    Private Const PASSWORD As String = "1"

    Private Const XADDRESS_IP As Integer = 1
    Private Const STATE_STOP As Integer = 0
    Private Const STATE_PLAY As Integer = 1
    Private Const STATE_BACK As Integer = 2

    Dim StartTime As New List(Of Integer)
    Dim EndTime As New List(Of Integer)

    Dim nPlayStatus As Integer = 0
    Dim nYear As Integer = 0
    Dim nMonth As Integer = 0
    Dim dPlaySpeed As Double = 1.0

    Dim hDevice As Integer = 0
    Dim hMediaSource As Integer = 0
    Dim nControlID As Integer = 0
    Dim nError As Integer = 0

    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Load Event.
    ' -----------------------------------------------------------------------
    Private Sub PlayBack_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
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

        ' Speed ComboBox Setting
        COMBO_SPEED.Items.Add("1X")
        COMBO_SPEED.Items.Add("2X")
        COMBO_SPEED.Items.Add("4X")
        COMBO_SPEED.Items.Add("8X")
        COMBO_SPEED.Items.Add("16X")
        COMBO_SPEED.Items.Add("32X")
        COMBO_SPEED.Enabled = False

        'Set Button Enable
        BTN_DISCONNECT.Enabled = False
        BTN_CHECK_CALENDAR.Enabled = False
        BTN_NREWARD.Enabled = False
        BTN_REWARD.Enabled = False
        BTN_STOP.Enabled = False
        BTN_PLAY.Enabled = False
        BTN_NPLAY.Enabled = False

        TRACKBAR_PLAY.Enabled = False
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
            BTN_CHECK_CALENDAR.Enabled = True
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
            hDevice = 0

            BTN_CONNECT.Enabled = True
            BTN_DISCONNECT.Enabled = False
            BTN_CHECK_CALENDAR.Enabled = False
            BTN_NREWARD.Enabled = False
            BTN_REWARD.Enabled = False
            BTN_STOP.Enabled = False
            BTN_PLAY.Enabled = False
            BTN_NPLAY.Enabled = False
            COMBO_SPEED.Enabled = False
            TRACKBAR_PLAY.Enabled = False

            MONTH_CALENDAR.RemoveAllBoldedDates()
            MONTH_CALENDAR.UpdateBoldedDates()
            LIST_RECORD_FILE.Items.Clear()
        End If
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Button Event.
    ' for Check Calendar Function.
    ' ----------------------------------------------------------------------- 
    Private Sub BTN_CHECK_CALENDAR_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTN_CHECK_CALENDAR.Click
        nYear = MONTH_CALENDAR.SelectionStart.Year
        nMonth = MONTH_CALENDAR.SelectionStart.Month

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Converts the date (MM/DD/YY) and time (HH:MM:SS) to the time_t format.
        ' -----------------------------------------------------------------------
        Dim TargetMonth As Integer = AxXnsSdkDevice.DateToTimet(nYear, nMonth, 1, 0, 0, 0)

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Covert local time to UTC time. 
        ' -----------------------------------------------------------------------
        TargetMonth = AxXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, TargetMonth)

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Acquires the permission to play the recorded multimedia.
        ' The application should acquire the permission using this function 
        ' before it can play video.
        ' -----------------------------------------------------------------------
        nError = AxXnsSdkDevice.AcquireMediaAuthority(hDevice)
        If nError <> XErrorCode.ERR_SUCCESS Then

            WLOGD("AcquireMediaAuthority() fail. errorcode =" + "(" + nError.ToString + ") [" + AxXnsSdkDevice.GetErrorString(nError) + "]")
            Return
        End If
        WLOGD("Search Calendar, target year=" + nYear.ToString() + " month=" + nMonth.ToString())

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Gets the video recording dates from a specific month. The result of 
        ' this function can be obtained from the OnSearchCalendar event.
        ' -----------------------------------------------------------------------
        nError = AxXnsSdkDevice.SearchCalendar(hDevice, nControlID, TargetMonth)
        If nError <> XErrorCode.ERR_SUCCESS Then
            WLOGD("SearchCalendar() fail. errorcode =" + "(" + nError.ToString + ") [" + AxXnsSdkDevice.GetErrorString(nError) + "]")
            Return
        End If
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Button Event.
    ' Go previous time Function.
    ' ----------------------------------------------------------------------- 
    Private Sub BTN_NREWARD_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTN_NREWARD.Click
        WLOGD("Go previous time")
        If nControlID = 0 Then
            ERROR_BOX("No record list..")
            Return
        End If

        Dim currIndex As Integer = TRACKBAR_PLAY.Value
        Dim min As Integer = TRACKBAR_PLAY.Minimum
        Dim max As Integer = TRACKBAR_PLAY.Maximum
        Dim offset As Integer = (max - min) / 10

        currIndex = currIndex - offset
        If currIndex < min Then
            currIndex = min
        End If
        TRACKBAR_PLAY.Value = currIndex

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Covert local time to UTC time. 
        ' -----------------------------------------------------------------------
        currIndex = AxXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, currIndex)

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Searches for a specific time point of the media stream.
        ' -----------------------------------------------------------------------
        AxXnsSdkDevice.Seek(hDevice, nControlID, currIndex)
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Button Event.
    ' for Back Function.
    ' ----------------------------------------------------------------------- 
    Private Sub BTN_REWARD_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTN_REWARD.Click
        WLOGD("Back")
        If nControlID = 0 Then
            ERROR_BOX("No record list..")
            Return
        End If

        If dPlaySpeed > 0 Then
            dPlaySpeed *= -1
        End If

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Plays the multimedia at a specified speed.
        ' -----------------------------------------------------------------------
        nError = AxXnsSdkDevice.Play(hDevice, nControlID, dPlaySpeed)
        If nError <> XErrorCode.ERR_SUCCESS Then
            WLOGD("Play() fail. errorcode =" + nError + " " + AxXnsSdkDevice.GetErrorString(nError))
        End If
        nPlayStatus = STATE_BACK
        BTN_REWARD.Enabled = False
        BTN_STOP.Enabled = True
        BTN_PLAY.Enabled = True
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Button Event.
    ' for Stop video Function.
    ' ----------------------------------------------------------------------- 
    Private Sub BTN_STOP_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTN_STOP.Click
        WLOGD("Stop")
        If nControlID = 0 Then
            ERROR_BOX("No record list..")
            Return
        End If

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Stops playing the media stream temporarily.
        ' -----------------------------------------------------------------------
        AxXnsSdkDevice.Pause(hDevice, nControlID)

        nPlayStatus = STATE_STOP
        BTN_STOP.Enabled = False
        BTN_PLAY.Enabled = True
        BTN_REWARD.Enabled = True
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Button Event.
    ' for Play video Function.
    ' ----------------------------------------------------------------------- 
    Private Sub BTN_PLAY_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTN_PLAY.Click
        If TRACKBAR_PLAY.Value = TRACKBAR_PLAY.Maximum Then
            Return
        End If

        WLOGD("Play")
        If nControlID = 0 Then
            ERROR_BOX("No record list..")
            Return
        End If

        If dPlaySpeed < 0 Then
            dPlaySpeed *= -1
        End If

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Plays the multimedia at a specified speed.
        ' -----------------------------------------------------------------------
        nError = AxXnsSdkDevice.Play(hDevice, nControlID, dPlaySpeed)
        If nError <> XErrorCode.ERR_SUCCESS Then
            WLOGD("Play() fail. errorcode =" + nError + " " + AxXnsSdkDevice.GetErrorString(nError))
            Return
        End If

        nPlayStatus = STATE_PLAY
        BTN_PLAY.Enabled = False
        BTN_STOP.Enabled = True
        BTN_REWARD.Enabled = True
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Button Event.
    ' Go next time Function.
    ' ----------------------------------------------------------------------- 
    Private Sub BTN_NPLAY_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTN_NPLAY.Click
        WLOGD("Go next time")
        If nControlID = 0 Then
            ERROR_BOX("No record list..")
            Return
        End If

        Dim currIndex As Integer = TRACKBAR_PLAY.Value
        Dim min As Integer = TRACKBAR_PLAY.Minimum
        Dim max As Integer = TRACKBAR_PLAY.Maximum
        Dim offset As Integer = (max - min) / 10

        currIndex = currIndex + offset
        If currIndex > max Then
            currIndex = max
        End If
        TRACKBAR_PLAY.Value = currIndex

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Covert local time to UTC time. 
        ' -----------------------------------------------------------------------
        currIndex = AxXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, currIndex)

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Searches for a specific time point of the media stream.
        ' -----------------------------------------------------------------------
        AxXnsSdkDevice.Seek(hDevice, nControlID, currIndex)
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
        Dim strRet = "OnDeviceStatusChanged() EVENT:: device_id=" + e.nDeviceID.ToString + ", status=" + e.nDeviceStatus.ToString
        WLOGD(strRet + ", error=" + e.nErrorCode.ToString + "[" + AxXnsSdkDevice.GetErrorString(e.nErrorCode) + "]")

        If e.nErrorCode <> XErrorCode.ERR_SUCCESS Or e.nDeviceStatus <> 1 Then
            WLOGD("Disconnected...")
            Return
        End If

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Returns the capabilities of the control module.
        ' -----------------------------------------------------------------------
        If AxXnsSdkDevice.GetControlCapability(hDevice, 1, XUnitCap.XCTL_CAP_FSPEED1) <> 0 Then
            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Returns the number of control modules. 
            ' The application can get the number of specific type of control modules, 
            ' and can get also the whole number of video recorders or cameras.
            ' -----------------------------------------------------------------------
            Dim nCount As Integer = AxXnsSdkDevice.GetControlCount(hDevice, XModelType.XCTL_CAMERA)
            Dim i As Integer
            For i = 0 To nCount - 1
                If AxXnsSdkDevice.GetControlCapability(hDevice, i + 2, XUnitCap.XCTL_CAP_PLAYBACK) <> 0 Then
                    nControlID = i + 2
                    Exit For
                End If
            Next i
        End If

        BTN_CONNECT.Enabled = False
        BTN_DISCONNECT.Enabled = True
        BTN_CHECK_CALENDAR.Enabled = True
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


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ Device Control Event.
    ' This event occurs if the application calls SearchCalendar(), 
    ' which contains the search result.  
    ' -----------------------------------------------------------------------
    Private Sub AxXnsSdkDevice_OnSearchCalendar(ByVal sender As System.Object, ByVal e As AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnSearchCalendarEvent) Handles AxXnsSdkDevice.OnSearchCalendar
        Dim nBitFlag As Integer = 1
        Dim BoldedDate As Date
        Dim nDay As Integer
        Dim i As Integer

        For i = 1 To 31
            If (e.nRecDay And nBitFlag) <> 0 Then
                nDay = i
                BoldedDate = New DateTime(nYear, nMonth, nDay)
                MONTH_CALENDAR.AddBoldedDate(BoldedDate)
            End If
            nBitFlag <<= 1
        Next i

        MONTH_CALENDAR.UpdateBoldedDates()
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm Calendar Control Event.
    ' This event occurs if the application calls SearchCalendar(), 
    ' which contains the search result.
    ' -----------------------------------------------------------------------
    Private Sub MONTH_CALENDAR_DateSelected(ByVal sender As System.Object, ByVal e As System.Windows.Forms.DateRangeEventArgs) Handles MONTH_CALENDAR.DateSelected
        LIST_RECORD_FILE.Items.Clear()
        StartTime.Clear()
        EndTime.Clear()

        Dim nDay As Integer = MONTH_CALENDAR.SelectionStart.Day

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Gets the video recording dates from a specific month. 
        ' The result of this function can be obtained from the OnSearchCalendar event.
        ' Return Value : Converted values in time_t format.
        ' -----------------------------------------------------------------------
        Dim tStart As Integer = AxXnsSdkDevice.DateToTimet(nYear, nMonth, nDay, 0, 0, 0)
        Dim tEnd As Integer = AxXnsSdkDevice.DateToTimet(nYear, nMonth, nDay, 23, 59, 59)

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Converts local t_time to UTC t_time.
        ' Return Value : UTC time_t value.
        ' -----------------------------------------------------------------------
        Dim tUTCStart As Integer = AxXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, tStart)
        Dim tUTCEnd As Integer = AxXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, tEnd)

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Gets a list of recording data for a specific day. 
        ' The result of this function can be obtained from the OnSearchDay event.
        ' -----------------------------------------------------------------------
        nError = AxXnsSdkDevice.SearchDay(hDevice, nControlID, tUTCStart, tUTCEnd, XRecType.REC_TYPE_ALL)

        If nError <> XErrorCode.ERR_SUCCESS Then
            WLOGD("SearchDay() fail. errorcode =" + "(" + nError.ToString + ") [" + AxXnsSdkDevice.GetErrorString(nError) + "]")
            Return
        End If
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ Device Control Event.
    ' This event occurs if the application calls SearchDay(), 
    ' which contains the search result.  
    ' -----------------------------------------------------------------------
    Private Sub AxXnsSdkDevice_OnSearchDay(ByVal sender As System.Object, ByVal e As AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnSearchDayEvent) Handles AxXnsSdkDevice.OnSearchDay
        Dim nTimelineCount As Integer = 0
        Dim nRecType As Integer = 0
        Dim nRecId As Integer = 0

        Dim tStart As Integer = 0
        Dim tEnd As Integer = 0
        Dim nDay As Integer = 0
        Dim StartHour, StartMin, StartSec As Integer
        Dim EndHour, EndMin, EndSec As Integer

        Dim i, j As Integer

        Dim nTotalCount As Integer = 0
        Dim strType As String

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Returns the number of cameras existing in the timeline.
        ' Return Value : Number of the cameras(from those connected in the system)
        '                that have recording data on a specified date.  
        ' -----------------------------------------------------------------------
        Dim nCamCount As Integer = AxXnsSdkDevice.GetCameraCount(e.hTimeline)
        WLOGD("OnSearchDay Event.. nCamCount[" + nCamCount.ToString + "]")

        For i = 0 To nCamCount - 1
            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Number of blocks of the recording data in the timeline. 
            ' This value is used as a parameter of functions: 
            ' GetStartTime(), GetEndTime(), GetRecordingType().
            ' Return Value : Number of blocks of the recording data in the timeline. 
            ' -----------------------------------------------------------------------
            nTimelineCount = AxXnsSdkDevice.GetTimelineCount(e.hTimeline, i)
            For j = 0 To nTimelineCount - 1

                ' [ XNS ACTIVEX HELP ]
                ' -----------------------------------------------------------------------
                ' Returns information on the recording data block. 
                ' -----------------------------------------------------------------------
                AxXnsSdkDevice.GetTimeline(e.hTimeline, i, j, 1, tStart, tEnd, nRecType, nRecId)

                StartTime.Add(tStart)
                EndTime.Add(tEnd)

                ' [ XNS ACTIVEX HELP ]
                ' -----------------------------------------------------------------------
                ' Converts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
                ' -----------------------------------------------------------------------
                AxXnsSdkDevice.TimetToDate(tStart, nYear, nMonth, nDay, StartHour, StartMin, StartSec)
                AxXnsSdkDevice.TimetToDate(tEnd, nYear, nMonth, nDay, EndHour, EndMin, EndSec)

                ' Print Record File List
                Select nRecType
                    Case XRecType.REC_TYPE_NONE
                        strType = "NON"
                    Case XRecType.REC_TYPE_MOTION
                        strType = "MOT"
                    Case XRecType.REC_TYPE_ALARM
                        strType = "ALM"
                    Case XRecType.REC_TYPE_VLOSS
                        strType = "VLS"
                    Case XRecType.REC_TYPE_MANUAL
                        strType = "MAN"
                    Case XRecType.REC_TYPE_CONTINUOS
                        strType = "CON"
                    Case XRecType.REC_TYPE_ALL
                        strType = "ALL"
                    Case Else
                        strType = "OTH"
                End Select

                LIST_RECORD_FILE.Items.Add(Format(nTotalCount, "00").ToString + " " + strType + " | " + Format(StartHour, "00").ToString + ":" + Format(StartMin, "00").ToString + ":" + Format(StartSec, "00").ToString + " - " + Format(EndHour, "00").ToString + ":" + Format(EndMin, "00").ToString + ":" + Format(EndSec, "00").ToString)
                nTotalCount = nTotalCount + 1
            Next j
        Next i
        WLOGD("OnSearchDay() Event Call!")
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm LISTBOX Control Event.
    ' for Record Video Play.
    ' -----------------------------------------------------------------------
    Private Sub LIST_RECORD_FILE_DoubleClick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles LIST_RECORD_FILE.DoubleClick
        If AxXnsSdkDevice.GetDeviceStatus(hDevice) <> XConnect.XDEVICE_STATUS_CONNECTED Then
            Return
        End If

        Dim nIndex As Integer = LIST_RECORD_FILE.SelectedIndex

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Convert from LocalTime to Device UTC
        ' Return Value : UTC time_t value.
        ' -----------------------------------------------------------------------
        Dim tStart As Integer = AxXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, StartTime.Item(nIndex))
        Dim tEnd As Integer = AxXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, EndTime.Item(nIndex))

        BTN_NREWARD.Enabled = True
        BTN_REWARD.Enabled = True
        BTN_STOP.Enabled = False
        BTN_PLAY.Enabled = True
        BTN_NPLAY.Enabled = True

        If hMediaSource <> 0 Then
            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Stops receiving the stream data from the mediasource handle (pMediaSource).
            ' -----------------------------------------------------------------------
            AxXnsSdkWindow.Stop()

            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Terminates transferring media stream data from the device. 
            ' The media stream data will be separated by hMediaSource 
            ' (i.e., phMediaSource of OpenMedia()).
            ' -----------------------------------------------------------------------
            AxXnsSdkDevice.CloseMedia(hDevice, hMediaSource)

            hMediaSource = 0
            nPlayStatus = STATE_STOP
        End If

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Acquires the permission to play the recorded multimedia. 
        ' The application should acquire the permission using 
        ' this function before it can play video.
        ' -----------------------------------------------------------------------
        AxXnsSdkDevice.AcquireMediaAuthority(hDevice)

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Returns the capabilities of the control module.
        ' -----------------------------------------------------------------------
        AxXnsSdkDevice.OpenMedia(hDevice, nControlID, XMediaType.XMEDIA_PLAYBACK, tStart, tEnd, hMediaSource)
        WLOGD("Media Open Success.")

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Adds the media source handle to XnsSdkWindow.
        ' The media source handle is created by XnsSdkDevice. 
        ' If the application calls XnsSdkDevice::OpenMedia(), 
        ' it will receive media stream from the device and return the MediaSource handle. 
        ' The application uses uses Start() to forward the mediasource handle 
        ' to XnsSdkWindow so that XnsSdkWindow can obtain stream data.
        ' -----------------------------------------------------------------------
        AxXnsSdkWindow.Start(hMediaSource)

        WLOGW("Media Play Success.")

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Searches for a specific time point of the media stream.
        ' -----------------------------------------------------------------------
        If AxXnsSdkDevice.IsPlaying(hDevice) = 0 Then               ' Not Playing
            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Informs if the media stream is currently playing.
            ' -----------------------------------------------------------------------
            AxXnsSdkDevice.Seek(hDevice, nControlID, tStart)

            COMBO_SPEED.SelectedIndex = 0
        End If
        TRACKBAR_PLAY.SetRange(StartTime.Item(nIndex), EndTime.Item(nIndex))
        TRACKBAR_PLAY.Value = StartTime.Item(nIndex)

        TRACKBAR_PLAY.Enabled = True
        COMBO_SPEED.Enabled = True
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ Window Control Event.
    ' This event occurs if the frame time displayed on the screen is changed.
    ' This happens every second video is played.
    ' -----------------------------------------------------------------------
    Private Sub AxXnsSdkWindow_OnFrameTimeChanged(ByVal sender As System.Object, ByVal e As AxXNSSDKWINDOWLib._DXnsSdkWindowEvents_OnFrameTimeChangedEvent) Handles AxXnsSdkWindow.OnFrameTimeChanged
        If e.tFrameTime >= TRACKBAR_PLAY.Maximum Then
            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Stops playing the media stream temporarily.
            ' -----------------------------------------------------------------------
            AxXnsSdkDevice.Pause(hDevice, nControlID)

            Dim tUTCEnd As Integer = AxXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, TRACKBAR_PLAY.Maximum)
            AxXnsSdkDevice.Seek(hDevice, nControlID, tUTCEnd)
            e.tFrameTime = TRACKBAR_PLAY.Maximum

            nPlayStatus = STATE_STOP
            BTN_STOP.Enabled = False
            BTN_PLAY.Enabled = True
            BTN_REWARD.Enabled = True
        ElseIf e.tFrameTime <= TRACKBAR_PLAY.Minimum Then
            AxXnsSdkDevice.Pause(hDevice, nControlID)

            Dim tUTCStart As Integer = AxXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, TRACKBAR_PLAY.Minimum)
            AxXnsSdkDevice.Seek(hDevice, nControlID, tUTCStart)
            e.tFrameTime = TRACKBAR_PLAY.Minimum

            nPlayStatus = STATE_STOP
            BTN_STOP.Enabled = False
            BTN_PLAY.Enabled = True
            BTN_REWARD.Enabled = True
        End If

        Dim Year As Integer, Month As Integer, Day As Integer, Hour As Integer, Min As Integer, Sec As Integer
        Dim strTime As String

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' IConverts the time_t format to the date (MM/DD/YY) and time (HH:MM:SS).
        ' -----------------------------------------------------------------------
        AxXnsSdkDevice.TimetToDate(e.tFrameTime, Year, Month, Day, Hour, Min, Sec)

        strTime = Format(Hour, "00").ToString + ":" + Format(Min, "00").ToString + ":" + Format(Sec, "00").ToString

        STR_TIME.Text = strTime
        TRACKBAR_PLAY.Value = e.tFrameTime
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB TRACKBAR Control Event.
    ' Mouse capture changed 
    ' -----------------------------------------------------------------------
    Private Sub TRACKBAR_PLAY_MouseCaptureChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TRACKBAR_PLAY.MouseCaptureChanged
        Dim CurrentTime As Integer = TRACKBAR_PLAY.Value

        If CurrentTime < TRACKBAR_PLAY.Minimum Or CurrentTime > TRACKBAR_PLAY.Maximum Then
            Return
        End If

        CurrentTime = AxXnsSdkDevice.LocalTimeToDeviceUTC(hDevice, CurrentTime)
        AxXnsSdkDevice.Seek(hDevice, nControlID, CurrentTime)
    End Sub


    ' [ XNS ACTIVEX HELP ]
    ' -----------------------------------------------------------------------
    ' @ VB WinForm ComboBox Event.
    ' Selected index changed Function.
    ' ----------------------------------------------------------------------- 
    Private Sub COMBO_SPEED_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles COMBO_SPEED.SelectedIndexChanged
        Dim index As Integer = COMBO_SPEED.SelectedIndex

        Select index
            Case 0
                dPlaySpeed = 1.0
            Case 1
                dPlaySpeed = 2.0
            Case 2
                dPlaySpeed = 4.0
            Case 3
                dPlaySpeed = 8.0
            Case 4
                dPlaySpeed = 16.0
            Case 5
                dPlaySpeed = 32.0
        End Select

        WLOGD("Play Speed = " + dPlaySpeed.ToString)

        If nControlID <> 0 Then
            ' [ XNS ACTIVEX HELP ]
            ' -----------------------------------------------------------------------
            ' Informs if the media stream is currently playing.
            ' ----------------------------------------------------------------------- 
            If AxXnsSdkDevice.IsPlaying(hDevice) <> False Then
                AxXnsSdkDevice.Pause(hDevice, nControlID)
                If nPlayStatus = STATE_PLAY Then
                    WLOGD("Play")
                    If nControlID = 0 Then
                        ERROR_BOX("No record list..")
                        Return
                    End If
                    If dPlaySpeed < 0 Then
                        dPlaySpeed *= -1
                    End If

                    nError = AxXnsSdkDevice.Play(hDevice, nControlID, dPlaySpeed)
                    If nError <> XErrorCode.ERR_SUCCESS Then
                        WLOGD("Play() fail. errorcode =" + nError + " " + AxXnsSdkDevice.GetErrorString(nError))
                        Return
                    End If
                    nPlayStatus = STATE_PLAY
                ElseIf nPlayStatus = STATE_BACK Then
                    WLOGD("Back")
                    If nControlID = 0 Then
                        ERROR_BOX("No record list..")
                        Return
                    End If
                    If dPlaySpeed > 0 Then
                        dPlaySpeed *= -1
                    End If

                    nError = AxXnsSdkDevice.Play(hDevice, nControlID, dPlaySpeed)
                    If nError <> XErrorCode.ERR_SUCCESS Then
                        WLOGD("Play() fail. errorcode =" + nError + " " + AxXnsSdkDevice.GetErrorString(nError))
                    End If
                    nPlayStatus = STATE_BACK
                End If
            End If
        End If
    End Sub
End Class

