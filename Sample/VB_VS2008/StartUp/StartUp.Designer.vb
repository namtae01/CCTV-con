<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class StartUp
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(StartUp))
        Me.AxXnsSdkWindow = New AxXNSSDKWINDOWLib.AxXnsSdkWindow
        Me.AxXnsSdkDevice = New AxXNSSDKDEVICELib.AxXnsSdkDevice
        CType(Me.AxXnsSdkWindow, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.AxXnsSdkDevice, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'AxXnsSdkWindow
        '
        Me.AxXnsSdkWindow.Enabled = True
        Me.AxXnsSdkWindow.Location = New System.Drawing.Point(12, 12)
        Me.AxXnsSdkWindow.Name = "AxXnsSdkWindow"
        Me.AxXnsSdkWindow.OcxState = CType(resources.GetObject("AxXnsSdkWindow.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxXnsSdkWindow.Size = New System.Drawing.Size(545, 388)
        Me.AxXnsSdkWindow.TabIndex = 0
        '
        'AxXnsSdkDevice
        '
        Me.AxXnsSdkDevice.Enabled = True
        Me.AxXnsSdkDevice.Location = New System.Drawing.Point(461, 406)
        Me.AxXnsSdkDevice.Name = "AxXnsSdkDevice"
        Me.AxXnsSdkDevice.OcxState = CType(resources.GetObject("AxXnsSdkDevice.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxXnsSdkDevice.Size = New System.Drawing.Size(96, 32)
        Me.AxXnsSdkDevice.TabIndex = 1
        Me.AxXnsSdkDevice.Visible = False
        '
        'StartUp
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(569, 456)
        Me.Controls.Add(Me.AxXnsSdkDevice)
        Me.Controls.Add(Me.AxXnsSdkWindow)
        Me.Name = "StartUp"
        Me.Text = "StartUp"
        CType(Me.AxXnsSdkWindow, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.AxXnsSdkDevice, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents AxXnsSdkWindow As AxXNSSDKWINDOWLib.AxXnsSdkWindow
    Friend WithEvents AxXnsSdkDevice As AxXNSSDKDEVICELib.AxXnsSdkDevice

End Class
