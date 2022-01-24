namespace UserAccount
{
    partial class MainForm
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.comboBoxModelName = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxIP = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxPort = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxID = new System.Windows.Forms.TextBox();
            this.textBoxPW = new System.Windows.Forms.TextBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.buttonDisconnect = new System.Windows.Forms.Button();
            this.buttonMediaOpen = new System.Windows.Forms.Button();
            this.buttonMediaClose = new System.Windows.Forms.Button();
            this.comboBoxChannel = new System.Windows.Forms.ComboBox();
            this.buttonRestart = new System.Windows.Forms.Button();
            this.buttonShutDown = new System.Windows.Forms.Button();
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.axXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.buttonGetCapacity = new System.Windows.Forms.Button();
            this.buttonGetPermission = new System.Windows.Forms.Button();
            this.buttonSetPermission = new System.Windows.Forms.Button();
            this.LIST_LOG = new System.Windows.Forms.ListBox();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).BeginInit();
            this.SuspendLayout();
            // 
            // comboBoxModelName
            // 
            this.comboBoxModelName.FormattingEnabled = true;
            this.comboBoxModelName.Location = new System.Drawing.Point(448, 15);
            this.comboBoxModelName.Name = "comboBoxModelName";
            this.comboBoxModelName.Size = new System.Drawing.Size(203, 20);
            this.comboBoxModelName.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(395, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 12);
            this.label1.TabIndex = 3;
            this.label1.Text = "Model";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(395, 56);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(16, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "IP";
            // 
            // textBoxIP
            // 
            this.textBoxIP.Location = new System.Drawing.Point(448, 50);
            this.textBoxIP.Name = "textBoxIP";
            this.textBoxIP.Size = new System.Drawing.Size(203, 21);
            this.textBoxIP.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(395, 92);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(27, 12);
            this.label3.TabIndex = 6;
            this.label3.Text = "Port";
            // 
            // textBoxPort
            // 
            this.textBoxPort.Location = new System.Drawing.Point(448, 86);
            this.textBoxPort.Name = "textBoxPort";
            this.textBoxPort.Size = new System.Drawing.Size(203, 21);
            this.textBoxPort.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(395, 128);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(16, 12);
            this.label4.TabIndex = 8;
            this.label4.Text = "ID";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(395, 164);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(23, 12);
            this.label5.TabIndex = 9;
            this.label5.Text = "PW";
            // 
            // textBoxID
            // 
            this.textBoxID.Location = new System.Drawing.Point(448, 122);
            this.textBoxID.Name = "textBoxID";
            this.textBoxID.Size = new System.Drawing.Size(203, 21);
            this.textBoxID.TabIndex = 10;
            // 
            // textBoxPW
            // 
            this.textBoxPW.Location = new System.Drawing.Point(448, 158);
            this.textBoxPW.Name = "textBoxPW";
            this.textBoxPW.PasswordChar = '*';
            this.textBoxPW.Size = new System.Drawing.Size(203, 21);
            this.textBoxPW.TabIndex = 11;
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(448, 185);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(100, 23);
            this.buttonConnect.TabIndex = 12;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // buttonDisconnect
            // 
            this.buttonDisconnect.Location = new System.Drawing.Point(554, 185);
            this.buttonDisconnect.Name = "buttonDisconnect";
            this.buttonDisconnect.Size = new System.Drawing.Size(100, 23);
            this.buttonDisconnect.TabIndex = 13;
            this.buttonDisconnect.Text = "Disconnect";
            this.buttonDisconnect.UseVisualStyleBackColor = true;
            this.buttonDisconnect.Click += new System.EventHandler(this.buttonDisconnect_Click);
            // 
            // buttonMediaOpen
            // 
            this.buttonMediaOpen.Location = new System.Drawing.Point(448, 215);
            this.buttonMediaOpen.Name = "buttonMediaOpen";
            this.buttonMediaOpen.Size = new System.Drawing.Size(100, 23);
            this.buttonMediaOpen.TabIndex = 14;
            this.buttonMediaOpen.Text = "Media Open";
            this.buttonMediaOpen.UseVisualStyleBackColor = true;
            this.buttonMediaOpen.Click += new System.EventHandler(this.buttonMediaOpen_Click);
            // 
            // buttonMediaClose
            // 
            this.buttonMediaClose.Location = new System.Drawing.Point(554, 215);
            this.buttonMediaClose.Name = "buttonMediaClose";
            this.buttonMediaClose.Size = new System.Drawing.Size(100, 23);
            this.buttonMediaClose.TabIndex = 15;
            this.buttonMediaClose.Text = "Media Close";
            this.buttonMediaClose.UseVisualStyleBackColor = true;
            this.buttonMediaClose.Click += new System.EventHandler(this.buttonMediaClose_Click);
            // 
            // comboBoxChannel
            // 
            this.comboBoxChannel.FormattingEnabled = true;
            this.comboBoxChannel.Location = new System.Drawing.Point(378, 215);
            this.comboBoxChannel.Name = "comboBoxChannel";
            this.comboBoxChannel.Size = new System.Drawing.Size(64, 20);
            this.comboBoxChannel.TabIndex = 16;
            // 
            // buttonRestart
            // 
            this.buttonRestart.Location = new System.Drawing.Point(448, 245);
            this.buttonRestart.Name = "buttonRestart";
            this.buttonRestart.Size = new System.Drawing.Size(100, 23);
            this.buttonRestart.TabIndex = 17;
            this.buttonRestart.Text = "Restart";
            this.buttonRestart.UseVisualStyleBackColor = true;
            this.buttonRestart.Click += new System.EventHandler(this.buttonRestart_Click);
            // 
            // buttonShutDown
            // 
            this.buttonShutDown.Location = new System.Drawing.Point(554, 245);
            this.buttonShutDown.Name = "buttonShutDown";
            this.buttonShutDown.Size = new System.Drawing.Size(100, 23);
            this.buttonShutDown.TabIndex = 18;
            this.buttonShutDown.Text = "Shut Down";
            this.buttonShutDown.UseVisualStyleBackColor = true;
            this.buttonShutDown.Click += new System.EventHandler(this.buttonShutDown_Click);
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(12, 305);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(100, 23);
            this.axXnsSdkDevice.TabIndex = 1;
            this.axXnsSdkDevice.Visible = false;
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            this.axXnsSdkDevice.OnPowerRestart += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnPowerRestartEventHandler(this.axXnsSdkDevice_OnPowerRestart);
            this.axXnsSdkDevice.OnShutDown += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnShutDownEventHandler(this.axXnsSdkDevice_OnShutDown);
            this.axXnsSdkDevice.OnGetPermissionCapacity += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnGetPermissionCapacityEventHandler(this.axXnsSdkDevice_OnGetPermissionCapacity);
            this.axXnsSdkDevice.OnGetPermission += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnGetPermissionEventHandler(this.axXnsSdkDevice_OnGetPermission);
            this.axXnsSdkDevice.OnSetPermission += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnSetPermissionEventHandler(this.axXnsSdkDevice_OnSetPermission);
            // 
            // axXnsSdkWindow
            // 
            this.axXnsSdkWindow.Enabled = true;
            this.axXnsSdkWindow.Location = new System.Drawing.Point(12, 12);
            this.axXnsSdkWindow.Name = "axXnsSdkWindow";
            this.axXnsSdkWindow.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow.OcxState")));
            this.axXnsSdkWindow.Size = new System.Drawing.Size(357, 286);
            this.axXnsSdkWindow.TabIndex = 0;
            // 
            // buttonGetCapacity
            // 
            this.buttonGetCapacity.Location = new System.Drawing.Point(448, 275);
            this.buttonGetCapacity.Name = "buttonGetCapacity";
            this.buttonGetCapacity.Size = new System.Drawing.Size(100, 23);
            this.buttonGetCapacity.TabIndex = 19;
            this.buttonGetCapacity.Text = "Get Capacity";
            this.buttonGetCapacity.UseVisualStyleBackColor = true;
            this.buttonGetCapacity.Click += new System.EventHandler(this.buttonGetCapacity_Click);
            // 
            // buttonGetPermission
            // 
            this.buttonGetPermission.Location = new System.Drawing.Point(448, 305);
            this.buttonGetPermission.Name = "buttonGetPermission";
            this.buttonGetPermission.Size = new System.Drawing.Size(100, 23);
            this.buttonGetPermission.TabIndex = 20;
            this.buttonGetPermission.Text = "Get Permission";
            this.buttonGetPermission.UseVisualStyleBackColor = true;
            this.buttonGetPermission.Click += new System.EventHandler(this.buttonGetPermission_Click);
            // 
            // buttonSetPermission
            // 
            this.buttonSetPermission.Location = new System.Drawing.Point(554, 305);
            this.buttonSetPermission.Name = "buttonSetPermission";
            this.buttonSetPermission.Size = new System.Drawing.Size(100, 23);
            this.buttonSetPermission.TabIndex = 22;
            this.buttonSetPermission.Text = "Set Permission";
            this.buttonSetPermission.UseVisualStyleBackColor = true;
            this.buttonSetPermission.Click += new System.EventHandler(this.buttonSetPermission_Click);
            // 
            // LIST_LOG
            // 
            this.LIST_LOG.FormattingEnabled = true;
            this.LIST_LOG.ItemHeight = 12;
            this.LIST_LOG.Location = new System.Drawing.Point(12, 338);
            this.LIST_LOG.Name = "LIST_LOG";
            this.LIST_LOG.Size = new System.Drawing.Size(641, 160);
            this.LIST_LOG.TabIndex = 23;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(665, 516);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.buttonSetPermission);
            this.Controls.Add(this.buttonGetPermission);
            this.Controls.Add(this.buttonGetCapacity);
            this.Controls.Add(this.buttonShutDown);
            this.Controls.Add(this.buttonRestart);
            this.Controls.Add(this.comboBoxChannel);
            this.Controls.Add(this.buttonMediaClose);
            this.Controls.Add(this.buttonMediaOpen);
            this.Controls.Add(this.buttonDisconnect);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.textBoxPW);
            this.Controls.Add(this.textBoxID);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.textBoxPort);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBoxIP);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboBoxModelName);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Controls.Add(this.axXnsSdkWindow);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MainForm";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.MainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow;
        private AxXNSSDKDEVICELib.AxXnsSdkDevice axXnsSdkDevice;
        private System.Windows.Forms.ComboBox comboBoxModelName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxIP;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxPort;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxID;
        private System.Windows.Forms.TextBox textBoxPW;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.Button buttonDisconnect;
        private System.Windows.Forms.Button buttonMediaOpen;
        private System.Windows.Forms.Button buttonMediaClose;
        private System.Windows.Forms.ComboBox comboBoxChannel;
        private System.Windows.Forms.Button buttonRestart;
        private System.Windows.Forms.Button buttonShutDown;
        private System.Windows.Forms.Button buttonGetCapacity;
        private System.Windows.Forms.Button buttonGetPermission;
        private System.Windows.Forms.Button buttonSetPermission;
        private System.Windows.Forms.ListBox LIST_LOG;
    }
}

