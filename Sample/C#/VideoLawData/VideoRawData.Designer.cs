namespace VideoLawData
{
    partial class VideoRawData
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(VideoRawData));
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.axXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.LIST_LOG = new System.Windows.Forms.ListBox();
            this.GROUP_CONNECTION_INFO = new System.Windows.Forms.GroupBox();
            this.EDIT_HTTPPORT = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.BTN_STOP = new System.Windows.Forms.Button();
            this.BTN_PLAY = new System.Windows.Forms.Button();
            this.BTN_DISCONNECT = new System.Windows.Forms.Button();
            this.BTN_CONNECT = new System.Windows.Forms.Button();
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
            this.STR_STATUS = new System.Windows.Forms.Label();
            this.CHECK_VIEW = new System.Windows.Forms.CheckBox();
            this.PICTURE_BOX = new System.Windows.Forms.PictureBox();
            this.CHECKBOX_SUNAPI = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).BeginInit();
            this.GROUP_CONNECTION_INFO.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PICTURE_BOX)).BeginInit();
            this.SuspendLayout();
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(699, 316);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(26, 14);
            this.axXnsSdkDevice.TabIndex = 0;
            this.axXnsSdkDevice.Visible = false;
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            this.axXnsSdkDevice.OnNewMedia += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnNewMediaEventHandler(this.axXnsSdkDevice_OnNewMedia);
            // 
            // axXnsSdkWindow
            // 
            this.axXnsSdkWindow.Enabled = true;
            this.axXnsSdkWindow.Location = new System.Drawing.Point(167, 114);
            this.axXnsSdkWindow.Name = "axXnsSdkWindow";
            this.axXnsSdkWindow.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow.OcxState")));
            this.axXnsSdkWindow.Size = new System.Drawing.Size(228, 146);
            this.axXnsSdkWindow.TabIndex = 1;
            this.axXnsSdkWindow.OnVideoRawDataReceived += new AxXNSSDKWINDOWLib._DXnsSdkWindowEvents_OnVideoRawDataReceivedEventHandler(this.axXnsSdkWindow_OnVideoRawDataReceived);
            // 
            // LIST_LOG
            // 
            this.LIST_LOG.FormattingEnabled = true;
            this.LIST_LOG.ItemHeight = 12;
            this.LIST_LOG.Location = new System.Drawing.Point(11, 340);
            this.LIST_LOG.Name = "LIST_LOG";
            this.LIST_LOG.Size = new System.Drawing.Size(720, 148);
            this.LIST_LOG.TabIndex = 2;
            // 
            // GROUP_CONNECTION_INFO
            // 
            this.GROUP_CONNECTION_INFO.Controls.Add(this.CHECKBOX_SUNAPI);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_HTTPPORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.label2);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.label1);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_STOP);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_PLAY);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_DISCONNECT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_CONNECT);
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
            this.GROUP_CONNECTION_INFO.Location = new System.Drawing.Point(401, 12);
            this.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO";
            this.GROUP_CONNECTION_INFO.Size = new System.Drawing.Size(330, 298);
            this.GROUP_CONNECTION_INFO.TabIndex = 3;
            this.GROUP_CONNECTION_INFO.TabStop = false;
            this.GROUP_CONNECTION_INFO.Text = "Connection Information";
            // 
            // EDIT_HTTPPORT
            // 
            this.EDIT_HTTPPORT.Location = new System.Drawing.Point(86, 135);
            this.EDIT_HTTPPORT.Name = "EDIT_HTTPPORT";
            this.EDIT_HTTPPORT.Size = new System.Drawing.Size(238, 21);
            this.EDIT_HTTPPORT.TabIndex = 23;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 139);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(63, 12);
            this.label2.TabIndex = 22;
            this.label2.Text = "HTTP Port";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 59);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(51, 12);
            this.label1.TabIndex = 19;
            this.label1.Text = "Protocol";
            // 
            // BTN_STOP
            // 
            this.BTN_STOP.Location = new System.Drawing.Point(182, 254);
            this.BTN_STOP.Name = "BTN_STOP";
            this.BTN_STOP.Size = new System.Drawing.Size(142, 29);
            this.BTN_STOP.TabIndex = 18;
            this.BTN_STOP.Text = "Stop";
            this.BTN_STOP.UseVisualStyleBackColor = true;
            this.BTN_STOP.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // BTN_PLAY
            // 
            this.BTN_PLAY.Location = new System.Drawing.Point(15, 254);
            this.BTN_PLAY.Name = "BTN_PLAY";
            this.BTN_PLAY.Size = new System.Drawing.Size(141, 29);
            this.BTN_PLAY.TabIndex = 17;
            this.BTN_PLAY.Text = "Play";
            this.BTN_PLAY.UseVisualStyleBackColor = true;
            this.BTN_PLAY.Click += new System.EventHandler(this.BTN_PLAY_Click);
            // 
            // BTN_DISCONNECT
            // 
            this.BTN_DISCONNECT.Location = new System.Drawing.Point(182, 221);
            this.BTN_DISCONNECT.Name = "BTN_DISCONNECT";
            this.BTN_DISCONNECT.Size = new System.Drawing.Size(142, 29);
            this.BTN_DISCONNECT.TabIndex = 12;
            this.BTN_DISCONNECT.Text = "Disconnect";
            this.BTN_DISCONNECT.UseVisualStyleBackColor = true;
            this.BTN_DISCONNECT.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // BTN_CONNECT
            // 
            this.BTN_CONNECT.Location = new System.Drawing.Point(14, 221);
            this.BTN_CONNECT.Name = "BTN_CONNECT";
            this.BTN_CONNECT.Size = new System.Drawing.Size(142, 29);
            this.BTN_CONNECT.TabIndex = 11;
            this.BTN_CONNECT.Text = "Connect";
            this.BTN_CONNECT.UseVisualStyleBackColor = true;
            this.BTN_CONNECT.Click += new System.EventHandler(this.BTN_CONNECT_Click);
            // 
            // COMBO_MODELLIST
            // 
            this.COMBO_MODELLIST.FormattingEnabled = true;
            this.COMBO_MODELLIST.Location = new System.Drawing.Point(86, 29);
            this.COMBO_MODELLIST.MaxDropDownItems = 15;
            this.COMBO_MODELLIST.Name = "COMBO_MODELLIST";
            this.COMBO_MODELLIST.Size = new System.Drawing.Size(238, 20);
            this.COMBO_MODELLIST.Sorted = true;
            this.COMBO_MODELLIST.TabIndex = 10;
            // 
            // EDIT_PW
            // 
            this.EDIT_PW.Location = new System.Drawing.Point(86, 189);
            this.EDIT_PW.Name = "EDIT_PW";
            this.EDIT_PW.Size = new System.Drawing.Size(238, 21);
            this.EDIT_PW.TabIndex = 9;
            this.EDIT_PW.UseSystemPasswordChar = true;
            // 
            // EDIT_ID
            // 
            this.EDIT_ID.Location = new System.Drawing.Point(86, 162);
            this.EDIT_ID.Name = "EDIT_ID";
            this.EDIT_ID.Size = new System.Drawing.Size(238, 21);
            this.EDIT_ID.TabIndex = 8;
            // 
            // EDIT_PORT
            // 
            this.EDIT_PORT.Location = new System.Drawing.Point(86, 108);
            this.EDIT_PORT.Name = "EDIT_PORT";
            this.EDIT_PORT.Size = new System.Drawing.Size(238, 21);
            this.EDIT_PORT.TabIndex = 7;
            // 
            // EDIT_IP
            // 
            this.EDIT_IP.Location = new System.Drawing.Point(86, 81);
            this.EDIT_IP.Name = "EDIT_IP";
            this.EDIT_IP.Size = new System.Drawing.Size(238, 21);
            this.EDIT_IP.TabIndex = 6;
            // 
            // STR_PW
            // 
            this.STR_PW.AutoSize = true;
            this.STR_PW.Location = new System.Drawing.Point(13, 194);
            this.STR_PW.Name = "STR_PW";
            this.STR_PW.Size = new System.Drawing.Size(31, 12);
            this.STR_PW.TabIndex = 4;
            this.STR_PW.Text = "PW  ";
            // 
            // STR_ID
            // 
            this.STR_ID.AutoSize = true;
            this.STR_ID.Location = new System.Drawing.Point(12, 166);
            this.STR_ID.Name = "STR_ID";
            this.STR_ID.Size = new System.Drawing.Size(20, 12);
            this.STR_ID.TabIndex = 3;
            this.STR_ID.Text = "ID ";
            // 
            // STR_PORT
            // 
            this.STR_PORT.AutoSize = true;
            this.STR_PORT.Location = new System.Drawing.Point(12, 112);
            this.STR_PORT.Name = "STR_PORT";
            this.STR_PORT.Size = new System.Drawing.Size(69, 12);
            this.STR_PORT.TabIndex = 2;
            this.STR_PORT.Text = "Device Port";
            // 
            // STR_IPADDRESS
            // 
            this.STR_IPADDRESS.AutoSize = true;
            this.STR_IPADDRESS.Location = new System.Drawing.Point(12, 85);
            this.STR_IPADDRESS.Name = "STR_IPADDRESS";
            this.STR_IPADDRESS.Size = new System.Drawing.Size(20, 12);
            this.STR_IPADDRESS.TabIndex = 1;
            this.STR_IPADDRESS.Text = "IP ";
            // 
            // STR_MODEL
            // 
            this.STR_MODEL.AutoSize = true;
            this.STR_MODEL.Location = new System.Drawing.Point(12, 33);
            this.STR_MODEL.Name = "STR_MODEL";
            this.STR_MODEL.Size = new System.Drawing.Size(40, 12);
            this.STR_MODEL.TabIndex = 0;
            this.STR_MODEL.Text = "Model";
            // 
            // STR_STATUS
            // 
            this.STR_STATUS.AutoSize = true;
            this.STR_STATUS.Location = new System.Drawing.Point(9, 327);
            this.STR_STATUS.Name = "STR_STATUS";
            this.STR_STATUS.Size = new System.Drawing.Size(65, 12);
            this.STR_STATUS.TabIndex = 14;
            this.STR_STATUS.Text = "Status Log";
            // 
            // CHECK_VIEW
            // 
            this.CHECK_VIEW.AutoSize = true;
            this.CHECK_VIEW.Location = new System.Drawing.Point(173, 45);
            this.CHECK_VIEW.Name = "CHECK_VIEW";
            this.CHECK_VIEW.Size = new System.Drawing.Size(117, 16);
            this.CHECK_VIEW.TabIndex = 15;
            this.CHECK_VIEW.Text = "View Raw Video";
            this.CHECK_VIEW.UseVisualStyleBackColor = true;
            this.CHECK_VIEW.CheckedChanged += new System.EventHandler(this.CHECK_VIEW_CheckedChanged);
            // 
            // PICTURE_BOX
            // 
            this.PICTURE_BOX.Location = new System.Drawing.Point(13, 12);
            this.PICTURE_BOX.Name = "PICTURE_BOX";
            this.PICTURE_BOX.Size = new System.Drawing.Size(154, 104);
            this.PICTURE_BOX.TabIndex = 16;
            this.PICTURE_BOX.TabStop = false;
            // 
            // CHECKBOX_SUNAPI
            // 
            this.CHECKBOX_SUNAPI.Location = new System.Drawing.Point(86, 54);
            this.CHECKBOX_SUNAPI.Name = "CHECKBOX_SUNAPI";
            this.CHECKBOX_SUNAPI.Size = new System.Drawing.Size(78, 24);
            this.CHECKBOX_SUNAPI.TabIndex = 24;
            this.CHECKBOX_SUNAPI.Text = "SUNAPI";
            this.CHECKBOX_SUNAPI.UseVisualStyleBackColor = true;
            // 
            // VideoRawData
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(743, 500);
            this.Controls.Add(this.PICTURE_BOX);
            this.Controls.Add(this.CHECK_VIEW);
            this.Controls.Add(this.STR_STATUS);
            this.Controls.Add(this.GROUP_CONNECTION_INFO);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.axXnsSdkWindow);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Name = "VideoRawData";
            this.Text = "VideoRawData";
            this.Load += new System.EventHandler(this.VideoRawData_Load);
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).EndInit();
            this.GROUP_CONNECTION_INFO.ResumeLayout(false);
            this.GROUP_CONNECTION_INFO.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PICTURE_BOX)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxXNSSDKDEVICELib.AxXnsSdkDevice axXnsSdkDevice;
        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow;
        private System.Windows.Forms.ListBox LIST_LOG;
        private System.Windows.Forms.GroupBox GROUP_CONNECTION_INFO;
        private System.Windows.Forms.Button BTN_DISCONNECT;
        private System.Windows.Forms.Button BTN_CONNECT;
        private System.Windows.Forms.ComboBox COMBO_MODELLIST;
        private System.Windows.Forms.TextBox EDIT_PW;
        private System.Windows.Forms.TextBox EDIT_ID;
        private System.Windows.Forms.TextBox EDIT_PORT;
        private System.Windows.Forms.TextBox EDIT_IP;
        private System.Windows.Forms.Label STR_PW;
        private System.Windows.Forms.Label STR_ID;
        private System.Windows.Forms.Label STR_PORT;
        private System.Windows.Forms.Label STR_IPADDRESS;
        private System.Windows.Forms.Label STR_MODEL;
        private System.Windows.Forms.Button BTN_STOP;
        private System.Windows.Forms.Button BTN_PLAY;
        private System.Windows.Forms.Label STR_STATUS;
        private System.Windows.Forms.CheckBox CHECK_VIEW;
        private System.Windows.Forms.PictureBox PICTURE_BOX;
        private System.Windows.Forms.TextBox EDIT_HTTPPORT;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox CHECKBOX_SUNAPI;
    }
}

