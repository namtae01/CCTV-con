namespace SingleLive
{
    partial class SingleLiveDlg
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SingleLiveDlg));
            this.GROUP_CONNECTION_INFO = new System.Windows.Forms.GroupBox();
            this.CHECKBOX_SUNAPI = new System.Windows.Forms.CheckBox();
            this.EDIT_HTTPPORT = new System.Windows.Forms.TextBox();
            this.STR_HTTPPORT = new System.Windows.Forms.Label();
            this.COMBO_MPROTOCOLLIST = new System.Windows.Forms.ComboBox();
            this.STR_PROTOCOL = new System.Windows.Forms.Label();
            this.Button_Disconnect = new System.Windows.Forms.Button();
            this.Button_Connect = new System.Windows.Forms.Button();
            this.COMBO_MODELLIST = new System.Windows.Forms.ComboBox();
            this.EDIT_PW = new System.Windows.Forms.TextBox();
            this.EDIT_ID = new System.Windows.Forms.TextBox();
            this.EDIT_PORT = new System.Windows.Forms.TextBox();
            this.EDIT_IP = new System.Windows.Forms.TextBox();
            this.STR_PW = new System.Windows.Forms.Label();
            this.STR_ID = new System.Windows.Forms.Label();
            this.STR_PORT = new System.Windows.Forms.Label();
            this.STR_IPADDRESS = new System.Windows.Forms.Label();
            this.STR_MODEL = new System.Windows.Forms.Label();
            this.GROUP_LIVE = new System.Windows.Forms.GroupBox();
            this.COMBO_PROFILE = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.COMBO_CHANNEL = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.Button_Stop = new System.Windows.Forms.Button();
            this.Button_Start = new System.Windows.Forms.Button();
            this.Button_Media_Close = new System.Windows.Forms.Button();
            this.Button_Media_Open = new System.Windows.Forms.Button();
            this.LIST_LOG = new System.Windows.Forms.ListBox();
            this.STR_STATUS = new System.Windows.Forms.Label();
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.axXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.GROUP_CONNECTION_INFO.SuspendLayout();
            this.GROUP_LIVE.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).BeginInit();
            this.SuspendLayout();
            // 
            // GROUP_CONNECTION_INFO
            // 
            this.GROUP_CONNECTION_INFO.Controls.Add(this.CHECKBOX_SUNAPI);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_HTTPPORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_HTTPPORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.COMBO_MPROTOCOLLIST);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_PROTOCOL);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.Button_Disconnect);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.Button_Connect);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.COMBO_MODELLIST);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_PW);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_ID);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_PORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_IP);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_PW);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_ID);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_PORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_IPADDRESS);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_MODEL);
            this.GROUP_CONNECTION_INFO.Location = new System.Drawing.Point(458, 12);
            this.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO";
            this.GROUP_CONNECTION_INFO.Size = new System.Drawing.Size(280, 256);
            this.GROUP_CONNECTION_INFO.TabIndex = 2;
            this.GROUP_CONNECTION_INFO.TabStop = false;
            this.GROUP_CONNECTION_INFO.Text = "Connection Information";
            // 
            // CHECKBOX_SUNAPI
            // 
            this.CHECKBOX_SUNAPI.Location = new System.Drawing.Point(88, 47);
            this.CHECKBOX_SUNAPI.Name = "CHECKBOX_SUNAPI";
            this.CHECKBOX_SUNAPI.Size = new System.Drawing.Size(78, 24);
            this.CHECKBOX_SUNAPI.TabIndex = 18;
            this.CHECKBOX_SUNAPI.Text = "SUNAPI";
            this.CHECKBOX_SUNAPI.UseVisualStyleBackColor = true;
            this.CHECKBOX_SUNAPI.CheckedChanged += new System.EventHandler(this.CHECKBOX_SUNAPI_CheckedChanged);
            // 
            // EDIT_HTTPPORT
            // 
            this.EDIT_HTTPPORT.Location = new System.Drawing.Point(85, 128);
            this.EDIT_HTTPPORT.Name = "EDIT_HTTPPORT";
            this.EDIT_HTTPPORT.Size = new System.Drawing.Size(188, 21);
            this.EDIT_HTTPPORT.TabIndex = 17;
            // 
            // STR_HTTPPORT
            // 
            this.STR_HTTPPORT.AutoSize = true;
            this.STR_HTTPPORT.Location = new System.Drawing.Point(5, 132);
            this.STR_HTTPPORT.Name = "STR_HTTPPORT";
            this.STR_HTTPPORT.Size = new System.Drawing.Size(75, 12);
            this.STR_HTTPPORT.TabIndex = 16;
            this.STR_HTTPPORT.Text = "HTTP Port  :";
            // 
            // COMBO_MPROTOCOLLIST
            // 
            this.COMBO_MPROTOCOLLIST.Enabled = false;
            this.COMBO_MPROTOCOLLIST.FormattingEnabled = true;
            this.COMBO_MPROTOCOLLIST.Location = new System.Drawing.Point(183, 48);
            this.COMBO_MPROTOCOLLIST.MaxDropDownItems = 15;
            this.COMBO_MPROTOCOLLIST.Name = "COMBO_MPROTOCOLLIST";
            this.COMBO_MPROTOCOLLIST.Size = new System.Drawing.Size(90, 20);
            this.COMBO_MPROTOCOLLIST.TabIndex = 15;
            // 
            // STR_PROTOCOL
            // 
            this.STR_PROTOCOL.AutoSize = true;
            this.STR_PROTOCOL.Location = new System.Drawing.Point(5, 51);
            this.STR_PROTOCOL.Name = "STR_PROTOCOL";
            this.STR_PROTOCOL.Size = new System.Drawing.Size(75, 12);
            this.STR_PROTOCOL.TabIndex = 13;
            this.STR_PROTOCOL.Text = "Protocol     :";
            // 
            // Button_Disconnect
            // 
            this.Button_Disconnect.Location = new System.Drawing.Point(148, 218);
            this.Button_Disconnect.Name = "Button_Disconnect";
            this.Button_Disconnect.Size = new System.Drawing.Size(118, 29);
            this.Button_Disconnect.TabIndex = 12;
            this.Button_Disconnect.Text = "Disconnect";
            this.Button_Disconnect.UseVisualStyleBackColor = true;
            this.Button_Disconnect.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // Button_Connect
            // 
            this.Button_Connect.Location = new System.Drawing.Point(18, 218);
            this.Button_Connect.Name = "Button_Connect";
            this.Button_Connect.Size = new System.Drawing.Size(118, 29);
            this.Button_Connect.TabIndex = 11;
            this.Button_Connect.Text = "Connect";
            this.Button_Connect.UseVisualStyleBackColor = true;
            this.Button_Connect.Click += new System.EventHandler(this.BTN_CONNECT_Click);
            // 
            // COMBO_MODELLIST
            // 
            this.COMBO_MODELLIST.FormattingEnabled = true;
            this.COMBO_MODELLIST.Location = new System.Drawing.Point(86, 22);
            this.COMBO_MODELLIST.MaxDropDownItems = 15;
            this.COMBO_MODELLIST.Name = "COMBO_MODELLIST";
            this.COMBO_MODELLIST.Size = new System.Drawing.Size(188, 20);
            this.COMBO_MODELLIST.Sorted = true;
            this.COMBO_MODELLIST.TabIndex = 10;
            this.COMBO_MODELLIST.SelectedIndexChanged += new System.EventHandler(this.COMBO_MODELLIST_SelectedIndexChanged);
            // 
            // EDIT_PW
            // 
            this.EDIT_PW.Location = new System.Drawing.Point(86, 184);
            this.EDIT_PW.Name = "EDIT_PW";
            this.EDIT_PW.Size = new System.Drawing.Size(188, 21);
            this.EDIT_PW.TabIndex = 9;
            this.EDIT_PW.UseSystemPasswordChar = true;
            // 
            // EDIT_ID
            // 
            this.EDIT_ID.Location = new System.Drawing.Point(86, 157);
            this.EDIT_ID.Name = "EDIT_ID";
            this.EDIT_ID.Size = new System.Drawing.Size(188, 21);
            this.EDIT_ID.TabIndex = 8;
            // 
            // EDIT_PORT
            // 
            this.EDIT_PORT.HideSelection = false;
            this.EDIT_PORT.Location = new System.Drawing.Point(85, 101);
            this.EDIT_PORT.Name = "EDIT_PORT";
            this.EDIT_PORT.Size = new System.Drawing.Size(188, 21);
            this.EDIT_PORT.TabIndex = 7;
            // 
            // EDIT_IP
            // 
            this.EDIT_IP.Location = new System.Drawing.Point(85, 74);
            this.EDIT_IP.Name = "EDIT_IP";
            this.EDIT_IP.Size = new System.Drawing.Size(188, 21);
            this.EDIT_IP.TabIndex = 6;
            // 
            // STR_PW
            // 
            this.STR_PW.AutoSize = true;
            this.STR_PW.Location = new System.Drawing.Point(7, 188);
            this.STR_PW.Name = "STR_PW";
            this.STR_PW.Size = new System.Drawing.Size(75, 12);
            this.STR_PW.TabIndex = 4;
            this.STR_PW.Text = "PW            :";
            // 
            // STR_ID
            // 
            this.STR_ID.AutoSize = true;
            this.STR_ID.Location = new System.Drawing.Point(6, 160);
            this.STR_ID.Name = "STR_ID";
            this.STR_ID.Size = new System.Drawing.Size(76, 12);
            this.STR_ID.TabIndex = 3;
            this.STR_ID.Text = "ID              :";
            // 
            // STR_PORT
            // 
            this.STR_PORT.AutoSize = true;
            this.STR_PORT.Location = new System.Drawing.Point(5, 104);
            this.STR_PORT.Name = "STR_PORT";
            this.STR_PORT.Size = new System.Drawing.Size(77, 12);
            this.STR_PORT.TabIndex = 2;
            this.STR_PORT.Text = "Device Port :";
            // 
            // STR_IPADDRESS
            // 
            this.STR_IPADDRESS.AutoSize = true;
            this.STR_IPADDRESS.Location = new System.Drawing.Point(5, 78);
            this.STR_IPADDRESS.Name = "STR_IPADDRESS";
            this.STR_IPADDRESS.Size = new System.Drawing.Size(76, 12);
            this.STR_IPADDRESS.TabIndex = 1;
            this.STR_IPADDRESS.Text = "IP              :";
            // 
            // STR_MODEL
            // 
            this.STR_MODEL.AutoSize = true;
            this.STR_MODEL.Location = new System.Drawing.Point(6, 24);
            this.STR_MODEL.Name = "STR_MODEL";
            this.STR_MODEL.Size = new System.Drawing.Size(76, 12);
            this.STR_MODEL.TabIndex = 0;
            this.STR_MODEL.Text = "Model        :";
            // 
            // GROUP_LIVE
            // 
            this.GROUP_LIVE.Controls.Add(this.COMBO_PROFILE);
            this.GROUP_LIVE.Controls.Add(this.label1);
            this.GROUP_LIVE.Controls.Add(this.COMBO_CHANNEL);
            this.GROUP_LIVE.Controls.Add(this.label2);
            this.GROUP_LIVE.Controls.Add(this.Button_Stop);
            this.GROUP_LIVE.Controls.Add(this.Button_Start);
            this.GROUP_LIVE.Controls.Add(this.Button_Media_Close);
            this.GROUP_LIVE.Controls.Add(this.Button_Media_Open);
            this.GROUP_LIVE.Location = new System.Drawing.Point(458, 274);
            this.GROUP_LIVE.Name = "GROUP_LIVE";
            this.GROUP_LIVE.Size = new System.Drawing.Size(280, 154);
            this.GROUP_LIVE.TabIndex = 3;
            this.GROUP_LIVE.TabStop = false;
            this.GROUP_LIVE.Text = "Live Control";
            // 
            // COMBO_PROFILE
            // 
            this.COMBO_PROFILE.FormattingEnabled = true;
            this.COMBO_PROFILE.Location = new System.Drawing.Point(86, 47);
            this.COMBO_PROFILE.MaxDropDownItems = 15;
            this.COMBO_PROFILE.Name = "COMBO_PROFILE";
            this.COMBO_PROFILE.Size = new System.Drawing.Size(186, 20);
            this.COMBO_PROFILE.TabIndex = 20;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 51);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(72, 12);
            this.label1.TabIndex = 19;
            this.label1.Text = "Profile       :";
            // 
            // COMBO_CHANNEL
            // 
            this.COMBO_CHANNEL.FormattingEnabled = true;
            this.COMBO_CHANNEL.Location = new System.Drawing.Point(86, 21);
            this.COMBO_CHANNEL.MaxDropDownItems = 15;
            this.COMBO_CHANNEL.Name = "COMBO_CHANNEL";
            this.COMBO_CHANNEL.Size = new System.Drawing.Size(186, 20);
            this.COMBO_CHANNEL.TabIndex = 18;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 24);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(72, 12);
            this.label2.TabIndex = 17;
            this.label2.Text = "Channel    :";
            // 
            // Button_Stop
            // 
            this.Button_Stop.Location = new System.Drawing.Point(146, 113);
            this.Button_Stop.Name = "Button_Stop";
            this.Button_Stop.Size = new System.Drawing.Size(120, 29);
            this.Button_Stop.TabIndex = 16;
            this.Button_Stop.Text = "Stop";
            this.Button_Stop.UseVisualStyleBackColor = true;
            this.Button_Stop.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // Button_Start
            // 
            this.Button_Start.Location = new System.Drawing.Point(18, 113);
            this.Button_Start.Name = "Button_Start";
            this.Button_Start.Size = new System.Drawing.Size(118, 29);
            this.Button_Start.TabIndex = 15;
            this.Button_Start.Text = "Start";
            this.Button_Start.UseVisualStyleBackColor = true;
            this.Button_Start.Click += new System.EventHandler(this.BTN_START_Click);
            // 
            // Button_Media_Close
            // 
            this.Button_Media_Close.Location = new System.Drawing.Point(146, 78);
            this.Button_Media_Close.Name = "Button_Media_Close";
            this.Button_Media_Close.Size = new System.Drawing.Size(120, 29);
            this.Button_Media_Close.TabIndex = 14;
            this.Button_Media_Close.Text = "Media Close";
            this.Button_Media_Close.UseVisualStyleBackColor = true;
            this.Button_Media_Close.Click += new System.EventHandler(this.BTN_MEDIACLOSE_Click);
            // 
            // Button_Media_Open
            // 
            this.Button_Media_Open.Location = new System.Drawing.Point(18, 78);
            this.Button_Media_Open.Name = "Button_Media_Open";
            this.Button_Media_Open.Size = new System.Drawing.Size(118, 29);
            this.Button_Media_Open.TabIndex = 13;
            this.Button_Media_Open.Text = "Media Open";
            this.Button_Media_Open.UseVisualStyleBackColor = true;
            this.Button_Media_Open.Click += new System.EventHandler(this.BTN_MEDIAOPEN_Click);
            // 
            // LIST_LOG
            // 
            this.LIST_LOG.FormattingEnabled = true;
            this.LIST_LOG.ItemHeight = 12;
            this.LIST_LOG.Location = new System.Drawing.Point(10, 437);
            this.LIST_LOG.Name = "LIST_LOG";
            this.LIST_LOG.Size = new System.Drawing.Size(728, 160);
            this.LIST_LOG.TabIndex = 4;
            // 
            // STR_STATUS
            // 
            this.STR_STATUS.AutoSize = true;
            this.STR_STATUS.Location = new System.Drawing.Point(10, 419);
            this.STR_STATUS.Name = "STR_STATUS";
            this.STR_STATUS.Size = new System.Drawing.Size(65, 12);
            this.STR_STATUS.TabIndex = 13;
            this.STR_STATUS.Text = "Status Log";
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(596, 415);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(87, 15);
            this.axXnsSdkDevice.TabIndex = 0;
            this.axXnsSdkDevice.Visible = false;
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            // 
            // axXnsSdkWindow
            // 
            this.axXnsSdkWindow.Enabled = true;
            this.axXnsSdkWindow.Location = new System.Drawing.Point(12, 12);
            this.axXnsSdkWindow.Name = "axXnsSdkWindow";
            this.axXnsSdkWindow.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow.OcxState")));
            this.axXnsSdkWindow.Size = new System.Drawing.Size(440, 339);
            this.axXnsSdkWindow.TabIndex = 1;
            // 
            // SingleLiveDlg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(750, 608);
            this.Controls.Add(this.STR_STATUS);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.GROUP_LIVE);
            this.Controls.Add(this.GROUP_CONNECTION_INFO);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Controls.Add(this.axXnsSdkWindow);
            this.Name = "SingleLiveDlg";
            this.Text = "SingleLive";
            this.Load += new System.EventHandler(this.SingleLiveDlg_Load);
            this.GROUP_CONNECTION_INFO.ResumeLayout(false);
            this.GROUP_CONNECTION_INFO.PerformLayout();
            this.GROUP_LIVE.ResumeLayout(false);
            this.GROUP_LIVE.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxXNSSDKDEVICELib.AxXnsSdkDevice axXnsSdkDevice;
        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow;
        private System.Windows.Forms.GroupBox GROUP_CONNECTION_INFO;
        private System.Windows.Forms.Label STR_PORT;
        private System.Windows.Forms.Label STR_IPADDRESS;
        private System.Windows.Forms.Label STR_MODEL;
        private System.Windows.Forms.Label STR_PW;
        private System.Windows.Forms.Label STR_ID;
        private System.Windows.Forms.ComboBox COMBO_MODELLIST;
        private System.Windows.Forms.TextBox EDIT_PW;
        private System.Windows.Forms.TextBox EDIT_ID;
        private System.Windows.Forms.TextBox EDIT_PORT;
        private System.Windows.Forms.TextBox EDIT_IP;
        private System.Windows.Forms.Button Button_Connect;
        private System.Windows.Forms.Button Button_Disconnect;
        private System.Windows.Forms.GroupBox GROUP_LIVE;
        private System.Windows.Forms.Button Button_Media_Close;
        private System.Windows.Forms.Button Button_Media_Open;
        private System.Windows.Forms.Button Button_Stop;
        private System.Windows.Forms.Button Button_Start;
        private System.Windows.Forms.ListBox LIST_LOG;
        private System.Windows.Forms.Label STR_STATUS;
        private System.Windows.Forms.TextBox EDIT_HTTPPORT;
        private System.Windows.Forms.Label STR_HTTPPORT;
        private System.Windows.Forms.ComboBox COMBO_MPROTOCOLLIST;
        private System.Windows.Forms.Label STR_PROTOCOL;
        private System.Windows.Forms.CheckBox CHECKBOX_SUNAPI;
        private System.Windows.Forms.ComboBox COMBO_PROFILE;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox COMBO_CHANNEL;
        private System.Windows.Forms.Label label2;
    }
}

