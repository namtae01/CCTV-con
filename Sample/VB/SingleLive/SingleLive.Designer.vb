<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class SingleLive
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(SingleLive))
        Me.AxXnsSdkWindow = New AxXNSSDKWINDOWLib.AxXnsSdkWindow()
        Me.AxXnsSdkDevice = New AxXNSSDKDEVICELib.AxXnsSdkDevice()
        Me.GROUP_CONNECTION_INFO = New System.Windows.Forms.GroupBox()
        Me.BTN_DISCONNECT = New System.Windows.Forms.Button()
        Me.BTN_CONNECT = New System.Windows.Forms.Button()
        Me.TEXT_PW = New System.Windows.Forms.TextBox()
        Me.TEXT_ID = New System.Windows.Forms.TextBox()
        Me.TEXT_PORT = New System.Windows.Forms.TextBox()
        Me.TEXT_IP = New System.Windows.Forms.TextBox()
        Me.COMBO_MODEL_LIST = New System.Windows.Forms.ComboBox()
        Me.STR_PW = New System.Windows.Forms.Label()
        Me.STR_ID = New System.Windows.Forms.Label()
        Me.STR_PORT = New System.Windows.Forms.Label()
        Me.STR_IP = New System.Windows.Forms.Label()
        Me.STR_MODEL = New System.Windows.Forms.Label()
        Me.GROUP_LIVE = New System.Windows.Forms.GroupBox()
        Me.BTN_MEDIA_CLOSE = New System.Windows.Forms.Button()
        Me.BTN_STOP = New System.Windows.Forms.Button()
        Me.BTN_START = New System.Windows.Forms.Button()
        Me.BTN_MEDIA_OPEN = New System.Windows.Forms.Button()
        Me.LIST_LOG = New System.Windows.Forms.ListBox()
        Me.STR_STATUS_LOG = New System.Windows.Forms.Label()
        CType(Me.AxXnsSdkWindow, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.AxXnsSdkDevice, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.GROUP_CONNECTION_INFO.SuspendLayout()
        Me.GROUP_LIVE.SuspendLayout()
        Me.SuspendLayout()
        '
        'AxXnsSdkWindow
        '
        Me.AxXnsSdkWindow.Enabled = True
        Me.AxXnsSdkWindow.Location = New System.Drawing.Point(12, 13)
        Me.AxXnsSdkWindow.Name = "AxXnsSdkWindow"
        Me.AxXnsSdkWindow.OcxState = CType(resources.GetObject("AxXnsSdkWindow.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxXnsSdkWindow.Size = New System.Drawing.Size(444, 341)
        Me.AxXnsSdkWindow.TabIndex = 0
        '
        'AxXnsSdkDevice
        '
        Me.AxXnsSdkDevice.Enabled = True
        Me.AxXnsSdkDevice.Location = New System.Drawing.Point(403, 360)
        Me.AxXnsSdkDevice.Name = "AxXnsSdkDevice"
        Me.AxXnsSdkDevice.OcxState = CType(resources.GetObject("AxXnsSdkDevice.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxXnsSdkDevice.Size = New System.Drawing.Size(53, 18)
        Me.AxXnsSdkDevice.TabIndex = 1
        Me.AxXnsSdkDevice.Visible = False
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
        Me.GROUP_CONNECTION_INFO.Location = New System.Drawing.Point(472, 13)
        Me.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO"
        Me.GROUP_CONNECTION_INFO.Size = New System.Drawing.Size(240, 212)
        Me.GROUP_CONNECTION_INFO.TabIndex = 2
        Me.GROUP_CONNECTION_INFO.TabStop = False
        Me.GROUP_CONNECTION_INFO.Text = "Connection Information"
        '
        'BTN_DISCONNECT
        '
        Me.BTN_DISCONNECT.Location = New System.Drawing.Point(132, 174)
        Me.BTN_DISCONNECT.Name = "BTN_DISCONNECT"
        Me.BTN_DISCONNECT.Size = New System.Drawing.Size(99, 27)
        Me.BTN_DISCONNECT.TabIndex = 3
        Me.BTN_DISCONNECT.Text = "Disconnect"
        Me.BTN_DISCONNECT.UseVisualStyleBackColor = True
        '
        'BTN_CONNECT
        '
        Me.BTN_CONNECT.Location = New System.Drawing.Point(8, 174)
        Me.BTN_CONNECT.Name = "BTN_CONNECT"
        Me.BTN_CONNECT.Size = New System.Drawing.Size(99, 27)
        Me.BTN_CONNECT.TabIndex = 3
        Me.BTN_CONNECT.Text = "Connect"
        Me.BTN_CONNECT.UseVisualStyleBackColor = True
        '
        'TEXT_PW
        '
        Me.TEXT_PW.Location = New System.Drawing.Point(84, 132)
        Me.TEXT_PW.Name = "TEXT_PW"
        Me.TEXT_PW.Size = New System.Drawing.Size(147, 21)
        Me.TEXT_PW.TabIndex = 2
        Me.TEXT_PW.UseSystemPasswordChar = True
        '
        'TEXT_ID
        '
        Me.TEXT_ID.Location = New System.Drawing.Point(84, 105)
        Me.TEXT_ID.Name = "TEXT_ID"
        Me.TEXT_ID.Size = New System.Drawing.Size(147, 21)
        Me.TEXT_ID.TabIndex = 2
        '
        'TEXT_PORT
        '
        Me.TEXT_PORT.Location = New System.Drawing.Point(84, 78)
        Me.TEXT_PORT.Name = "TEXT_PORT"
        Me.TEXT_PORT.Size = New System.Drawing.Size(147, 21)
        Me.TEXT_PORT.TabIndex = 2
        '
        'TEXT_IP
        '
        Me.TEXT_IP.Location = New System.Drawing.Point(84, 51)
        Me.TEXT_IP.Name = "TEXT_IP"
        Me.TEXT_IP.Size = New System.Drawing.Size(147, 21)
        Me.TEXT_IP.TabIndex = 2
        '
        'COMBO_MODEL_LIST
        '
        Me.COMBO_MODEL_LIST.FormattingEnabled = True
        Me.COMBO_MODEL_LIST.Location = New System.Drawing.Point(84, 22)
        Me.COMBO_MODEL_LIST.Name = "COMBO_MODEL_LIST"
        Me.COMBO_MODEL_LIST.Size = New System.Drawing.Size(147, 20)
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
        'GROUP_LIVE
        '
        Me.GROUP_LIVE.Controls.Add(Me.BTN_MEDIA_CLOSE)
        Me.GROUP_LIVE.Controls.Add(Me.BTN_STOP)
        Me.GROUP_LIVE.Controls.Add(Me.BTN_START)
        Me.GROUP_LIVE.Controls.Add(Me.BTN_MEDIA_OPEN)
        Me.GROUP_LIVE.Location = New System.Drawing.Point(472, 243)
        Me.GROUP_LIVE.Name = "GROUP_LIVE"
        Me.GROUP_LIVE.Size = New System.Drawing.Size(239, 112)
        Me.GROUP_LIVE.TabIndex = 3
        Me.GROUP_LIVE.TabStop = False
        Me.GROUP_LIVE.Text = "Live Control"
        '
        'BTN_MEDIA_CLOSE
        '
        Me.BTN_MEDIA_CLOSE.Location = New System.Drawing.Point(132, 30)
        Me.BTN_MEDIA_CLOSE.Name = "BTN_MEDIA_CLOSE"
        Me.BTN_MEDIA_CLOSE.Size = New System.Drawing.Size(99, 27)
        Me.BTN_MEDIA_CLOSE.TabIndex = 3
        Me.BTN_MEDIA_CLOSE.Text = "Media Close"
        Me.BTN_MEDIA_CLOSE.UseVisualStyleBackColor = True
        '
        'BTN_STOP
        '
        Me.BTN_STOP.Location = New System.Drawing.Point(132, 72)
        Me.BTN_STOP.Name = "BTN_STOP"
        Me.BTN_STOP.Size = New System.Drawing.Size(99, 27)
        Me.BTN_STOP.TabIndex = 3
        Me.BTN_STOP.Text = "Stop"
        Me.BTN_STOP.UseVisualStyleBackColor = True
        '
        'BTN_START
        '
        Me.BTN_START.Location = New System.Drawing.Point(8, 72)
        Me.BTN_START.Name = "BTN_START"
        Me.BTN_START.Size = New System.Drawing.Size(99, 27)
        Me.BTN_START.TabIndex = 3
        Me.BTN_START.Text = "Start"
        Me.BTN_START.UseVisualStyleBackColor = True
        '
        'BTN_MEDIA_OPEN
        '
        Me.BTN_MEDIA_OPEN.Location = New System.Drawing.Point(8, 30)
        Me.BTN_MEDIA_OPEN.Name = "BTN_MEDIA_OPEN"
        Me.BTN_MEDIA_OPEN.Size = New System.Drawing.Size(99, 27)
        Me.BTN_MEDIA_OPEN.TabIndex = 3
        Me.BTN_MEDIA_OPEN.Text = "Media Open"
        Me.BTN_MEDIA_OPEN.UseVisualStyleBackColor = True
        '
        'LIST_LOG
        '
        Me.LIST_LOG.FormattingEnabled = True
        Me.LIST_LOG.ItemHeight = 12
        Me.LIST_LOG.Location = New System.Drawing.Point(12, 384)
        Me.LIST_LOG.Name = "LIST_LOG"
        Me.LIST_LOG.Size = New System.Drawing.Size(700, 196)
        Me.LIST_LOG.TabIndex = 4
        '
        'STR_STATUS_LOG
        '
        Me.STR_STATUS_LOG.AutoSize = True
        Me.STR_STATUS_LOG.Location = New System.Drawing.Point(12, 366)
        Me.STR_STATUS_LOG.Name = "STR_STATUS_LOG"
        Me.STR_STATUS_LOG.Size = New System.Drawing.Size(65, 12)
        Me.STR_STATUS_LOG.TabIndex = 0
        Me.STR_STATUS_LOG.Text = "Status Log"
        '
        'SingleLive
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(728, 594)
        Me.Controls.Add(Me.LIST_LOG)
        Me.Controls.Add(Me.GROUP_LIVE)
        Me.Controls.Add(Me.GROUP_CONNECTION_INFO)
        Me.Controls.Add(Me.AxXnsSdkDevice)
        Me.Controls.Add(Me.AxXnsSdkWindow)
        Me.Controls.Add(Me.STR_STATUS_LOG)
        Me.Name = "SingleLive"
        Me.Text = "SingleLive"
        CType(Me.AxXnsSdkWindow, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.AxXnsSdkDevice, System.ComponentModel.ISupportInitialize).EndInit()
        Me.GROUP_CONNECTION_INFO.ResumeLayout(False)
        Me.GROUP_CONNECTION_INFO.PerformLayout()
        Me.GROUP_LIVE.ResumeLayout(False)
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents AxXnsSdkWindow As AxXNSSDKWINDOWLib.AxXnsSdkWindow
    Friend WithEvents AxXnsSdkDevice As AxXNSSDKDEVICELib.AxXnsSdkDevice
    Friend WithEvents GROUP_CONNECTION_INFO As System.Windows.Forms.GroupBox
    Friend WithEvents STR_MODEL As System.Windows.Forms.Label
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
    Friend WithEvents GROUP_LIVE As System.Windows.Forms.GroupBox
    Friend WithEvents BTN_MEDIA_CLOSE As System.Windows.Forms.Button
    Friend WithEvents BTN_STOP As System.Windows.Forms.Button
    Friend WithEvents BTN_START As System.Windows.Forms.Button
    Friend WithEvents BTN_MEDIA_OPEN As System.Windows.Forms.Button
    Friend WithEvents LIST_LOG As System.Windows.Forms.ListBox
    Friend WithEvents STR_STATUS_LOG As System.Windows.Forms.Label

End Class
