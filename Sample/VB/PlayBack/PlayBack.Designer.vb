<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class PlayBack
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(PlayBack))
        Me.AxXnsSdkWindow = New AxXNSSDKWINDOWLib.AxXnsSdkWindow
        Me.AxXnsSdkDevice = New AxXNSSDKDEVICELib.AxXnsSdkDevice
        Me.GROUP_RECORD_FILE = New System.Windows.Forms.GroupBox
        Me.MONTH_CALENDAR = New System.Windows.Forms.MonthCalendar
        Me.BTN_CHECK_CALENDAR = New System.Windows.Forms.Button
        Me.GROUP_CONNECTION_INFO = New System.Windows.Forms.GroupBox
        Me.BTN_DISCONNECT = New System.Windows.Forms.Button
        Me.BTN_CONNECT = New System.Windows.Forms.Button
        Me.TEXT_PW = New System.Windows.Forms.TextBox
        Me.TEXT_ID = New System.Windows.Forms.TextBox
        Me.TEXT_PORT = New System.Windows.Forms.TextBox
        Me.TEXT_IP = New System.Windows.Forms.TextBox
        Me.COMBO_MODEL_LIST = New System.Windows.Forms.ComboBox
        Me.STR_PW = New System.Windows.Forms.Label
        Me.STR_ID = New System.Windows.Forms.Label
        Me.STR_PORT = New System.Windows.Forms.Label
        Me.STR_IP = New System.Windows.Forms.Label
        Me.STR_MODEL = New System.Windows.Forms.Label
        Me.LIST_LOG = New System.Windows.Forms.ListBox
        Me.STR_STATUS_LOG = New System.Windows.Forms.Label
        Me.GROUP_PLAY_RECORD_FILE = New System.Windows.Forms.GroupBox
        Me.COMBO_SPEED = New System.Windows.Forms.ComboBox
        Me.STR_TIME = New System.Windows.Forms.Label
        Me.BTN_NPLAY = New System.Windows.Forms.Button
        Me.TRACKBAR_PLAY = New System.Windows.Forms.TrackBar
        Me.BTN_PLAY = New System.Windows.Forms.Button
        Me.BTN_STOP = New System.Windows.Forms.Button
        Me.LIST_RECORD_FILE = New System.Windows.Forms.ListBox
        Me.BTN_REWARD = New System.Windows.Forms.Button
        Me.BTN_NREWARD = New System.Windows.Forms.Button
        CType(Me.AxXnsSdkWindow, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.AxXnsSdkDevice, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.GROUP_RECORD_FILE.SuspendLayout()
        Me.GROUP_CONNECTION_INFO.SuspendLayout()
        Me.GROUP_PLAY_RECORD_FILE.SuspendLayout()
        CType(Me.TRACKBAR_PLAY, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'AxXnsSdkWindow
        '
        Me.AxXnsSdkWindow.Enabled = True
        Me.AxXnsSdkWindow.Location = New System.Drawing.Point(11, 11)
        Me.AxXnsSdkWindow.Name = "AxXnsSdkWindow"
        Me.AxXnsSdkWindow.OcxState = CType(resources.GetObject("AxXnsSdkWindow.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxXnsSdkWindow.Size = New System.Drawing.Size(428, 352)
        Me.AxXnsSdkWindow.TabIndex = 0
        '
        'AxXnsSdkDevice
        '
        Me.AxXnsSdkDevice.Enabled = True
        Me.AxXnsSdkDevice.Location = New System.Drawing.Point(382, 369)
        Me.AxXnsSdkDevice.Name = "AxXnsSdkDevice"
        Me.AxXnsSdkDevice.OcxState = CType(resources.GetObject("AxXnsSdkDevice.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxXnsSdkDevice.Size = New System.Drawing.Size(57, 21)
        Me.AxXnsSdkDevice.TabIndex = 1
        Me.AxXnsSdkDevice.Visible = False
        '
        'GROUP_RECORD_FILE
        '
        Me.GROUP_RECORD_FILE.Controls.Add(Me.MONTH_CALENDAR)
        Me.GROUP_RECORD_FILE.Controls.Add(Me.BTN_CHECK_CALENDAR)
        Me.GROUP_RECORD_FILE.Location = New System.Drawing.Point(454, 214)
        Me.GROUP_RECORD_FILE.Name = "GROUP_RECORD_FILE"
        Me.GROUP_RECORD_FILE.Size = New System.Drawing.Size(237, 222)
        Me.GROUP_RECORD_FILE.TabIndex = 5
        Me.GROUP_RECORD_FILE.TabStop = False
        Me.GROUP_RECORD_FILE.Text = "Check Calendar"
        '
        'MONTH_CALENDAR
        '
        Me.MONTH_CALENDAR.Location = New System.Drawing.Point(8, 50)
        Me.MONTH_CALENDAR.Name = "MONTH_CALENDAR"
        Me.MONTH_CALENDAR.TabIndex = 8
        '
        'BTN_CHECK_CALENDAR
        '
        Me.BTN_CHECK_CALENDAR.Location = New System.Drawing.Point(8, 20)
        Me.BTN_CHECK_CALENDAR.Name = "BTN_CHECK_CALENDAR"
        Me.BTN_CHECK_CALENDAR.Size = New System.Drawing.Size(220, 23)
        Me.BTN_CHECK_CALENDAR.TabIndex = 7
        Me.BTN_CHECK_CALENDAR.Text = "Check Calendar"
        Me.BTN_CHECK_CALENDAR.UseVisualStyleBackColor = True
        '
        'GROUP_CONNECTION_INFO
        '
        Me.GROUP_CONNECTION_INFO.Controls.Add(Me.BTN_DISCONNECT)
        Me.GROUP_CONNECTION_INFO.Controls.Add(Me.BTN_CONNECT)
        Me.GROUP_CONNECTION_INFO.Controls.Add(Me.TEXT_PW)
        Me.GROUP_CONNECTION_INFO.Controls.Add(Me.TEXT_ID)
        Me.GROUP_CONNECTION_INFO.Controls.Add(Me.TEXT_PORT)
        Me.GROUP_CONNECTION_INFO.Controls.Add(Me.TEXT_IP)
        Me.GROUP_CONNECTION_INFO.Controls.Add(Me.COMBO_MODEL_LIST)
        Me.GROUP_CONNECTION_INFO.Controls.Add(Me.STR_PW)
        Me.GROUP_CONNECTION_INFO.Controls.Add(Me.STR_ID)
        Me.GROUP_CONNECTION_INFO.Controls.Add(Me.STR_PORT)
        Me.GROUP_CONNECTION_INFO.Controls.Add(Me.STR_IP)
        Me.GROUP_CONNECTION_INFO.Controls.Add(Me.STR_MODEL)
        Me.GROUP_CONNECTION_INFO.Location = New System.Drawing.Point(454, 11)
        Me.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO"
        Me.GROUP_CONNECTION_INFO.Size = New System.Drawing.Size(237, 197)
        Me.GROUP_CONNECTION_INFO.TabIndex = 4
        Me.GROUP_CONNECTION_INFO.TabStop = False
        Me.GROUP_CONNECTION_INFO.Text = "Connection Information"
        '
        'BTN_DISCONNECT
        '
        Me.BTN_DISCONNECT.Location = New System.Drawing.Point(129, 165)
        Me.BTN_DISCONNECT.Name = "BTN_DISCONNECT"
        Me.BTN_DISCONNECT.Size = New System.Drawing.Size(99, 23)
        Me.BTN_DISCONNECT.TabIndex = 6
        Me.BTN_DISCONNECT.Text = "Disconnect"
        Me.BTN_DISCONNECT.UseVisualStyleBackColor = True
        '
        'BTN_CONNECT
        '
        Me.BTN_CONNECT.Location = New System.Drawing.Point(9, 165)
        Me.BTN_CONNECT.Name = "BTN_CONNECT"
        Me.BTN_CONNECT.Size = New System.Drawing.Size(99, 23)
        Me.BTN_CONNECT.TabIndex = 6
        Me.BTN_CONNECT.Text = "Connect"
        Me.BTN_CONNECT.UseVisualStyleBackColor = True
        '
        'TEXT_PW
        '
        Me.TEXT_PW.Location = New System.Drawing.Point(84, 132)
        Me.TEXT_PW.Name = "TEXT_PW"
        Me.TEXT_PW.Size = New System.Drawing.Size(144, 21)
        Me.TEXT_PW.TabIndex = 5
        Me.TEXT_PW.UseSystemPasswordChar = True
        '
        'TEXT_ID
        '
        Me.TEXT_ID.Location = New System.Drawing.Point(84, 105)
        Me.TEXT_ID.Name = "TEXT_ID"
        Me.TEXT_ID.Size = New System.Drawing.Size(144, 21)
        Me.TEXT_ID.TabIndex = 4
        '
        'TEXT_PORT
        '
        Me.TEXT_PORT.Location = New System.Drawing.Point(84, 78)
        Me.TEXT_PORT.Name = "TEXT_PORT"
        Me.TEXT_PORT.Size = New System.Drawing.Size(144, 21)
        Me.TEXT_PORT.TabIndex = 3
        '
        'TEXT_IP
        '
        Me.TEXT_IP.Location = New System.Drawing.Point(84, 51)
        Me.TEXT_IP.Name = "TEXT_IP"
        Me.TEXT_IP.Size = New System.Drawing.Size(144, 21)
        Me.TEXT_IP.TabIndex = 2
        '
        'COMBO_MODEL_LIST
        '
        Me.COMBO_MODEL_LIST.FormattingEnabled = True
        Me.COMBO_MODEL_LIST.Location = New System.Drawing.Point(84, 22)
        Me.COMBO_MODEL_LIST.Name = "COMBO_MODEL_LIST"
        Me.COMBO_MODEL_LIST.Size = New System.Drawing.Size(144, 20)
        Me.COMBO_MODEL_LIST.TabIndex = 1
        '
        'STR_PW
        '
        Me.STR_PW.AutoSize = True
        Me.STR_PW.Location = New System.Drawing.Point(6, 135)
        Me.STR_PW.Name = "STR_PW"
        Me.STR_PW.Size = New System.Drawing.Size(67, 12)
        Me.STR_PW.TabIndex = 0
        Me.STR_PW.Text = "PW          :"
        '
        'STR_ID
        '
        Me.STR_ID.AutoSize = True
        Me.STR_ID.Location = New System.Drawing.Point(6, 108)
        Me.STR_ID.Name = "STR_ID"
        Me.STR_ID.Size = New System.Drawing.Size(68, 12)
        Me.STR_ID.TabIndex = 0
        Me.STR_ID.Text = "ID            :"
        '
        'STR_PORT
        '
        Me.STR_PORT.AutoSize = True
        Me.STR_PORT.Location = New System.Drawing.Point(6, 81)
        Me.STR_PORT.Name = "STR_PORT"
        Me.STR_PORT.Size = New System.Drawing.Size(68, 12)
        Me.STR_PORT.TabIndex = 0
        Me.STR_PORT.Text = "VNP Port  :"
        '
        'STR_IP
        '
        Me.STR_IP.AutoSize = True
        Me.STR_IP.Location = New System.Drawing.Point(6, 54)
        Me.STR_IP.Name = "STR_IP"
        Me.STR_IP.Size = New System.Drawing.Size(68, 12)
        Me.STR_IP.TabIndex = 0
        Me.STR_IP.Text = "IP            :"
        '
        'STR_MODEL
        '
        Me.STR_MODEL.AutoSize = True
        Me.STR_MODEL.Location = New System.Drawing.Point(6, 25)
        Me.STR_MODEL.Name = "STR_MODEL"
        Me.STR_MODEL.Size = New System.Drawing.Size(68, 12)
        Me.STR_MODEL.TabIndex = 0
        Me.STR_MODEL.Text = "Model      :"
        '
        'LIST_LOG
        '
        Me.LIST_LOG.FormattingEnabled = True
        Me.LIST_LOG.HorizontalScrollbar = True
        Me.LIST_LOG.ItemHeight = 12
        Me.LIST_LOG.Location = New System.Drawing.Point(11, 396)
        Me.LIST_LOG.Name = "LIST_LOG"
        Me.LIST_LOG.Size = New System.Drawing.Size(427, 292)
        Me.LIST_LOG.TabIndex = 6
        '
        'STR_STATUS_LOG
        '
        Me.STR_STATUS_LOG.AutoSize = True
        Me.STR_STATUS_LOG.Location = New System.Drawing.Point(12, 378)
        Me.STR_STATUS_LOG.Name = "STR_STATUS_LOG"
        Me.STR_STATUS_LOG.Size = New System.Drawing.Size(65, 12)
        Me.STR_STATUS_LOG.TabIndex = 7
        Me.STR_STATUS_LOG.Text = "Status Log"
        '
        'GROUP_PLAY_RECORD_FILE
        '
        Me.GROUP_PLAY_RECORD_FILE.Controls.Add(Me.COMBO_SPEED)
        Me.GROUP_PLAY_RECORD_FILE.Controls.Add(Me.STR_TIME)
        Me.GROUP_PLAY_RECORD_FILE.Controls.Add(Me.BTN_NPLAY)
        Me.GROUP_PLAY_RECORD_FILE.Controls.Add(Me.TRACKBAR_PLAY)
        Me.GROUP_PLAY_RECORD_FILE.Controls.Add(Me.BTN_PLAY)
        Me.GROUP_PLAY_RECORD_FILE.Controls.Add(Me.BTN_STOP)
        Me.GROUP_PLAY_RECORD_FILE.Controls.Add(Me.LIST_RECORD_FILE)
        Me.GROUP_PLAY_RECORD_FILE.Controls.Add(Me.BTN_REWARD)
        Me.GROUP_PLAY_RECORD_FILE.Controls.Add(Me.BTN_NREWARD)
        Me.GROUP_PLAY_RECORD_FILE.Location = New System.Drawing.Point(454, 442)
        Me.GROUP_PLAY_RECORD_FILE.Name = "GROUP_PLAY_RECORD_FILE"
        Me.GROUP_PLAY_RECORD_FILE.Size = New System.Drawing.Size(237, 246)
        Me.GROUP_PLAY_RECORD_FILE.TabIndex = 8
        Me.GROUP_PLAY_RECORD_FILE.TabStop = False
        Me.GROUP_PLAY_RECORD_FILE.Text = "Play Record File"
        '
        'COMBO_SPEED
        '
        Me.COMBO_SPEED.FormattingEnabled = True
        Me.COMBO_SPEED.Location = New System.Drawing.Point(8, 218)
        Me.COMBO_SPEED.Name = "COMBO_SPEED"
        Me.COMBO_SPEED.Size = New System.Drawing.Size(219, 20)
        Me.COMBO_SPEED.TabIndex = 4
        '
        'STR_TIME
        '
        Me.STR_TIME.AutoSize = True
        Me.STR_TIME.Location = New System.Drawing.Point(185, 150)
        Me.STR_TIME.Name = "STR_TIME"
        Me.STR_TIME.Size = New System.Drawing.Size(49, 12)
        Me.STR_TIME.TabIndex = 20
        Me.STR_TIME.Text = "00:00:00"
        '
        'BTN_NPLAY
        '
        Me.BTN_NPLAY.Location = New System.Drawing.Point(187, 185)
        Me.BTN_NPLAY.Name = "BTN_NPLAY"
        Me.BTN_NPLAY.Size = New System.Drawing.Size(41, 27)
        Me.BTN_NPLAY.TabIndex = 19
        Me.BTN_NPLAY.Text = ">|"
        Me.BTN_NPLAY.UseVisualStyleBackColor = True
        '
        'TRACKBAR_PLAY
        '
        Me.TRACKBAR_PLAY.Location = New System.Drawing.Point(2, 138)
        Me.TRACKBAR_PLAY.Name = "TRACKBAR_PLAY"
        Me.TRACKBAR_PLAY.Size = New System.Drawing.Size(170, 45)
        Me.TRACKBAR_PLAY.TabIndex = 1
        '
        'BTN_PLAY
        '
        Me.BTN_PLAY.Location = New System.Drawing.Point(143, 185)
        Me.BTN_PLAY.Name = "BTN_PLAY"
        Me.BTN_PLAY.Size = New System.Drawing.Size(41, 27)
        Me.BTN_PLAY.TabIndex = 18
        Me.BTN_PLAY.Text = ">"
        Me.BTN_PLAY.UseVisualStyleBackColor = True
        '
        'BTN_STOP
        '
        Me.BTN_STOP.Location = New System.Drawing.Point(98, 185)
        Me.BTN_STOP.Name = "BTN_STOP"
        Me.BTN_STOP.Size = New System.Drawing.Size(41, 27)
        Me.BTN_STOP.TabIndex = 15
        Me.BTN_STOP.Text = "||"
        Me.BTN_STOP.UseVisualStyleBackColor = True
        '
        'LIST_RECORD_FILE
        '
        Me.LIST_RECORD_FILE.FormattingEnabled = True
        Me.LIST_RECORD_FILE.ItemHeight = 12
        Me.LIST_RECORD_FILE.Location = New System.Drawing.Point(8, 20)
        Me.LIST_RECORD_FILE.Name = "LIST_RECORD_FILE"
        Me.LIST_RECORD_FILE.Size = New System.Drawing.Size(219, 112)
        Me.LIST_RECORD_FILE.TabIndex = 0
        '
        'BTN_REWARD
        '
        Me.BTN_REWARD.Location = New System.Drawing.Point(53, 185)
        Me.BTN_REWARD.Name = "BTN_REWARD"
        Me.BTN_REWARD.Size = New System.Drawing.Size(41, 27)
        Me.BTN_REWARD.TabIndex = 16
        Me.BTN_REWARD.Text = "<"
        Me.BTN_REWARD.UseVisualStyleBackColor = True
        '
        'BTN_NREWARD
        '
        Me.BTN_NREWARD.Location = New System.Drawing.Point(8, 185)
        Me.BTN_NREWARD.Name = "BTN_NREWARD"
        Me.BTN_NREWARD.Size = New System.Drawing.Size(41, 27)
        Me.BTN_NREWARD.TabIndex = 17
        Me.BTN_NREWARD.Text = "|<"
        Me.BTN_NREWARD.UseVisualStyleBackColor = True
        '
        'PlayBack
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(704, 700)
        Me.Controls.Add(Me.GROUP_PLAY_RECORD_FILE)
        Me.Controls.Add(Me.STR_STATUS_LOG)
        Me.Controls.Add(Me.LIST_LOG)
        Me.Controls.Add(Me.GROUP_RECORD_FILE)
        Me.Controls.Add(Me.GROUP_CONNECTION_INFO)
        Me.Controls.Add(Me.AxXnsSdkDevice)
        Me.Controls.Add(Me.AxXnsSdkWindow)
        Me.Name = "PlayBack"
        Me.Text = "PlayBack"
        CType(Me.AxXnsSdkWindow, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.AxXnsSdkDevice, System.ComponentModel.ISupportInitialize).EndInit()
        Me.GROUP_RECORD_FILE.ResumeLayout(False)
        Me.GROUP_CONNECTION_INFO.ResumeLayout(False)
        Me.GROUP_CONNECTION_INFO.PerformLayout()
        Me.GROUP_PLAY_RECORD_FILE.ResumeLayout(False)
        Me.GROUP_PLAY_RECORD_FILE.PerformLayout()
        CType(Me.TRACKBAR_PLAY, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents AxXnsSdkWindow As AxXNSSDKWINDOWLib.AxXnsSdkWindow
    Friend WithEvents AxXnsSdkDevice As AxXNSSDKDEVICELib.AxXnsSdkDevice
    Friend WithEvents GROUP_RECORD_FILE As System.Windows.Forms.GroupBox
    Friend WithEvents MONTH_CALENDAR As System.Windows.Forms.MonthCalendar
    Friend WithEvents BTN_CHECK_CALENDAR As System.Windows.Forms.Button
    Friend WithEvents GROUP_CONNECTION_INFO As System.Windows.Forms.GroupBox
    Friend WithEvents BTN_DISCONNECT As System.Windows.Forms.Button
    Friend WithEvents BTN_CONNECT As System.Windows.Forms.Button
    Friend WithEvents TEXT_PW As System.Windows.Forms.TextBox
    Friend WithEvents TEXT_ID As System.Windows.Forms.TextBox
    Friend WithEvents TEXT_PORT As System.Windows.Forms.TextBox
    Friend WithEvents TEXT_IP As System.Windows.Forms.TextBox
    Friend WithEvents COMBO_MODEL_LIST As System.Windows.Forms.ComboBox
    Friend WithEvents STR_PW As System.Windows.Forms.Label
    Friend WithEvents STR_ID As System.Windows.Forms.Label
    Friend WithEvents STR_PORT As System.Windows.Forms.Label
    Friend WithEvents STR_IP As System.Windows.Forms.Label
    Friend WithEvents STR_MODEL As System.Windows.Forms.Label
    Friend WithEvents LIST_LOG As System.Windows.Forms.ListBox
    Friend WithEvents STR_STATUS_LOG As System.Windows.Forms.Label
    Friend WithEvents GROUP_PLAY_RECORD_FILE As System.Windows.Forms.GroupBox
    Friend WithEvents TRACKBAR_PLAY As System.Windows.Forms.TrackBar
    Friend WithEvents LIST_RECORD_FILE As System.Windows.Forms.ListBox
    Friend WithEvents COMBO_SPEED As System.Windows.Forms.ComboBox
    Private WithEvents STR_TIME As System.Windows.Forms.Label
    Private WithEvents BTN_NPLAY As System.Windows.Forms.Button
    Private WithEvents BTN_PLAY As System.Windows.Forms.Button
    Private WithEvents BTN_STOP As System.Windows.Forms.Button
    Private WithEvents BTN_REWARD As System.Windows.Forms.Button
    Private WithEvents BTN_NREWARD As System.Windows.Forms.Button

End Class
