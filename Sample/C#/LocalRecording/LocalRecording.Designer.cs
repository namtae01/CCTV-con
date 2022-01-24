namespace LocalRecording
{
    partial class LocalRecordingForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LocalRecordingForm));
            this.GROUP_CONNECTION_INFO = new System.Windows.Forms.GroupBox();
            this.EDIT_HTTPPORT = new System.Windows.Forms.TextBox();
            this.STR_HTTPPORT = new System.Windows.Forms.Label();
            this.STR_PROTOCOL = new System.Windows.Forms.Label();
            this.BTN_PLAY = new System.Windows.Forms.Button();
            this.BTN_STOP = new System.Windows.Forms.Button();
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
            this.STR_ACTIVEX_CONTROL_LOG = new System.Windows.Forms.Label();
            this.LIST_LOG = new System.Windows.Forms.ListBox();
            this.GROUP_LOCAL_RECORDING = new System.Windows.Forms.GroupBox();
            this.GROUP_RECORDING_TYPE = new System.Windows.Forms.GroupBox();
            this.RADIO_REC = new System.Windows.Forms.RadioButton();
            this.RADIO_SEC = new System.Windows.Forms.RadioButton();
            this.BTN_STOP_REC_FILE = new System.Windows.Forms.Button();
            this.BTN_PLAY_REC_FILE = new System.Windows.Forms.Button();
            this.BTN_STOP_RECORDING = new System.Windows.Forms.Button();
            this.BTN_START_RECORDING = new System.Windows.Forms.Button();
            this.axXnsSdkWindow_Recording = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.axXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.CHECKBOX_SUNAPI = new System.Windows.Forms.CheckBox();
            this.GROUP_CONNECTION_INFO.SuspendLayout();
            this.GROUP_LOCAL_RECORDING.SuspendLayout();
            this.GROUP_RECORDING_TYPE.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow_Recording)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).BeginInit();
            this.SuspendLayout();
            // 
            // GROUP_CONNECTION_INFO
            // 
            this.GROUP_CONNECTION_INFO.Controls.Add(this.CHECKBOX_SUNAPI);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_HTTPPORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_HTTPPORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_PROTOCOL);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_PLAY);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_STOP);
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
            this.GROUP_CONNECTION_INFO.Location = new System.Drawing.Point(385, 12);
            this.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO";
            this.GROUP_CONNECTION_INFO.Size = new System.Drawing.Size(326, 288);
            this.GROUP_CONNECTION_INFO.TabIndex = 5;
            this.GROUP_CONNECTION_INFO.TabStop = false;
            this.GROUP_CONNECTION_INFO.Text = "Connection Information";
            // 
            // EDIT_HTTPPORT
            // 
            this.EDIT_HTTPPORT.Location = new System.Drawing.Point(86, 135);
            this.EDIT_HTTPPORT.Name = "EDIT_HTTPPORT";
            this.EDIT_HTTPPORT.Size = new System.Drawing.Size(223, 21);
            this.EDIT_HTTPPORT.TabIndex = 16;
            // 
            // STR_HTTPPORT
            // 
            this.STR_HTTPPORT.AutoSize = true;
            this.STR_HTTPPORT.Location = new System.Drawing.Point(12, 140);
            this.STR_HTTPPORT.Name = "STR_HTTPPORT";
            this.STR_HTTPPORT.Size = new System.Drawing.Size(63, 12);
            this.STR_HTTPPORT.TabIndex = 15;
            this.STR_HTTPPORT.Text = "HTTP Port";
            // 
            // STR_PROTOCOL
            // 
            this.STR_PROTOCOL.AutoSize = true;
            this.STR_PROTOCOL.Location = new System.Drawing.Point(12, 60);
            this.STR_PROTOCOL.Name = "STR_PROTOCOL";
            this.STR_PROTOCOL.Size = new System.Drawing.Size(51, 12);
            this.STR_PROTOCOL.TabIndex = 13;
            this.STR_PROTOCOL.Text = "Protocol";
            // 
            // BTN_PLAY
            // 
            this.BTN_PLAY.Location = new System.Drawing.Point(85, 250);
            this.BTN_PLAY.Name = "BTN_PLAY";
            this.BTN_PLAY.Size = new System.Drawing.Size(106, 25);
            this.BTN_PLAY.TabIndex = 11;
            this.BTN_PLAY.Text = "Play";
            this.BTN_PLAY.UseVisualStyleBackColor = true;
            this.BTN_PLAY.Click += new System.EventHandler(this.BTN_PLAY_Click);
            // 
            // BTN_STOP
            // 
            this.BTN_STOP.Location = new System.Drawing.Point(202, 250);
            this.BTN_STOP.Name = "BTN_STOP";
            this.BTN_STOP.Size = new System.Drawing.Size(106, 25);
            this.BTN_STOP.TabIndex = 11;
            this.BTN_STOP.Text = "Stop";
            this.BTN_STOP.UseVisualStyleBackColor = true;
            this.BTN_STOP.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // BTN_DISCONNECT
            // 
            this.BTN_DISCONNECT.Location = new System.Drawing.Point(202, 219);
            this.BTN_DISCONNECT.Name = "BTN_DISCONNECT";
            this.BTN_DISCONNECT.Size = new System.Drawing.Size(106, 25);
            this.BTN_DISCONNECT.TabIndex = 11;
            this.BTN_DISCONNECT.Text = "Disconnect";
            this.BTN_DISCONNECT.UseVisualStyleBackColor = true;
            this.BTN_DISCONNECT.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // BTN_CONNECT
            // 
            this.BTN_CONNECT.Location = new System.Drawing.Point(85, 219);
            this.BTN_CONNECT.Name = "BTN_CONNECT";
            this.BTN_CONNECT.Size = new System.Drawing.Size(106, 25);
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
            this.COMBO_MODELLIST.Size = new System.Drawing.Size(223, 20);
            this.COMBO_MODELLIST.TabIndex = 10;
            // 
            // EDIT_PW
            // 
            this.EDIT_PW.Location = new System.Drawing.Point(85, 189);
            this.EDIT_PW.Name = "EDIT_PW";
            this.EDIT_PW.Size = new System.Drawing.Size(223, 21);
            this.EDIT_PW.TabIndex = 9;
            this.EDIT_PW.UseSystemPasswordChar = true;
            // 
            // EDIT_ID
            // 
            this.EDIT_ID.Location = new System.Drawing.Point(85, 162);
            this.EDIT_ID.Name = "EDIT_ID";
            this.EDIT_ID.Size = new System.Drawing.Size(223, 21);
            this.EDIT_ID.TabIndex = 8;
            // 
            // EDIT_PORT
            // 
            this.EDIT_PORT.Location = new System.Drawing.Point(85, 108);
            this.EDIT_PORT.Name = "EDIT_PORT";
            this.EDIT_PORT.Size = new System.Drawing.Size(223, 21);
            this.EDIT_PORT.TabIndex = 7;
            // 
            // EDIT_IP
            // 
            this.EDIT_IP.Location = new System.Drawing.Point(85, 81);
            this.EDIT_IP.Name = "EDIT_IP";
            this.EDIT_IP.Size = new System.Drawing.Size(223, 21);
            this.EDIT_IP.TabIndex = 6;
            // 
            // STR_PW
            // 
            this.STR_PW.AutoSize = true;
            this.STR_PW.Location = new System.Drawing.Point(12, 194);
            this.STR_PW.Name = "STR_PW";
            this.STR_PW.Size = new System.Drawing.Size(27, 12);
            this.STR_PW.TabIndex = 4;
            this.STR_PW.Text = "PW ";
            // 
            // STR_ID
            // 
            this.STR_ID.AutoSize = true;
            this.STR_ID.Location = new System.Drawing.Point(11, 167);
            this.STR_ID.Name = "STR_ID";
            this.STR_ID.Size = new System.Drawing.Size(24, 12);
            this.STR_ID.TabIndex = 3;
            this.STR_ID.Text = "ID  ";
            // 
            // STR_PORT
            // 
            this.STR_PORT.AutoSize = true;
            this.STR_PORT.Location = new System.Drawing.Point(11, 113);
            this.STR_PORT.Name = "STR_PORT";
            this.STR_PORT.Size = new System.Drawing.Size(69, 12);
            this.STR_PORT.TabIndex = 2;
            this.STR_PORT.Text = "Device Port";
            // 
            // STR_IPADDRESS
            // 
            this.STR_IPADDRESS.AutoSize = true;
            this.STR_IPADDRESS.Location = new System.Drawing.Point(11, 86);
            this.STR_IPADDRESS.Name = "STR_IPADDRESS";
            this.STR_IPADDRESS.Size = new System.Drawing.Size(40, 12);
            this.STR_IPADDRESS.TabIndex = 1;
            this.STR_IPADDRESS.Text = "IP      ";
            // 
            // STR_MODEL
            // 
            this.STR_MODEL.AutoSize = true;
            this.STR_MODEL.Location = new System.Drawing.Point(12, 33);
            this.STR_MODEL.Name = "STR_MODEL";
            this.STR_MODEL.Size = new System.Drawing.Size(44, 12);
            this.STR_MODEL.TabIndex = 0;
            this.STR_MODEL.Text = "Model ";
            // 
            // STR_ACTIVEX_CONTROL_LOG
            // 
            this.STR_ACTIVEX_CONTROL_LOG.AutoSize = true;
            this.STR_ACTIVEX_CONTROL_LOG.Location = new System.Drawing.Point(12, 298);
            this.STR_ACTIVEX_CONTROL_LOG.Name = "STR_ACTIVEX_CONTROL_LOG";
            this.STR_ACTIVEX_CONTROL_LOG.Size = new System.Drawing.Size(116, 12);
            this.STR_ACTIVEX_CONTROL_LOG.TabIndex = 12;
            this.STR_ACTIVEX_CONTROL_LOG.Text = "ActiveX Control Log";
            // 
            // LIST_LOG
            // 
            this.LIST_LOG.FormattingEnabled = true;
            this.LIST_LOG.ItemHeight = 12;
            this.LIST_LOG.Location = new System.Drawing.Point(12, 316);
            this.LIST_LOG.Name = "LIST_LOG";
            this.LIST_LOG.Size = new System.Drawing.Size(699, 88);
            this.LIST_LOG.TabIndex = 11;
            // 
            // GROUP_LOCAL_RECORDING
            // 
            this.GROUP_LOCAL_RECORDING.Controls.Add(this.GROUP_RECORDING_TYPE);
            this.GROUP_LOCAL_RECORDING.Controls.Add(this.BTN_STOP_REC_FILE);
            this.GROUP_LOCAL_RECORDING.Controls.Add(this.BTN_PLAY_REC_FILE);
            this.GROUP_LOCAL_RECORDING.Controls.Add(this.BTN_STOP_RECORDING);
            this.GROUP_LOCAL_RECORDING.Controls.Add(this.BTN_START_RECORDING);
            this.GROUP_LOCAL_RECORDING.Location = new System.Drawing.Point(385, 426);
            this.GROUP_LOCAL_RECORDING.Name = "GROUP_LOCAL_RECORDING";
            this.GROUP_LOCAL_RECORDING.Size = new System.Drawing.Size(326, 242);
            this.GROUP_LOCAL_RECORDING.TabIndex = 5;
            this.GROUP_LOCAL_RECORDING.TabStop = false;
            this.GROUP_LOCAL_RECORDING.Text = "Local Recording";
            // 
            // GROUP_RECORDING_TYPE
            // 
            this.GROUP_RECORDING_TYPE.Controls.Add(this.RADIO_REC);
            this.GROUP_RECORDING_TYPE.Controls.Add(this.RADIO_SEC);
            this.GROUP_RECORDING_TYPE.Location = new System.Drawing.Point(15, 48);
            this.GROUP_RECORDING_TYPE.Name = "GROUP_RECORDING_TYPE";
            this.GROUP_RECORDING_TYPE.Size = new System.Drawing.Size(294, 66);
            this.GROUP_RECORDING_TYPE.TabIndex = 12;
            this.GROUP_RECORDING_TYPE.TabStop = false;
            this.GROUP_RECORDING_TYPE.Text = "Recording Type";
            // 
            // RADIO_REC
            // 
            this.RADIO_REC.AutoSize = true;
            this.RADIO_REC.Location = new System.Drawing.Point(188, 30);
            this.RADIO_REC.Name = "RADIO_REC";
            this.RADIO_REC.Size = new System.Drawing.Size(48, 16);
            this.RADIO_REC.TabIndex = 0;
            this.RADIO_REC.TabStop = true;
            this.RADIO_REC.Text = "REC";
            this.RADIO_REC.UseVisualStyleBackColor = true;
            // 
            // RADIO_SEC
            // 
            this.RADIO_SEC.AutoSize = true;
            this.RADIO_SEC.Location = new System.Drawing.Point(50, 30);
            this.RADIO_SEC.Name = "RADIO_SEC";
            this.RADIO_SEC.Size = new System.Drawing.Size(48, 16);
            this.RADIO_SEC.TabIndex = 0;
            this.RADIO_SEC.TabStop = true;
            this.RADIO_SEC.Text = "SEC";
            this.RADIO_SEC.UseVisualStyleBackColor = true;
            // 
            // BTN_STOP_REC_FILE
            // 
            this.BTN_STOP_REC_FILE.Location = new System.Drawing.Point(204, 193);
            this.BTN_STOP_REC_FILE.Name = "BTN_STOP_REC_FILE";
            this.BTN_STOP_REC_FILE.Size = new System.Drawing.Size(106, 25);
            this.BTN_STOP_REC_FILE.TabIndex = 11;
            this.BTN_STOP_REC_FILE.Text = "Stop REC";
            this.BTN_STOP_REC_FILE.UseVisualStyleBackColor = true;
            this.BTN_STOP_REC_FILE.Click += new System.EventHandler(this.BTN_STOP_REC_FILE_Click);
            // 
            // BTN_PLAY_REC_FILE
            // 
            this.BTN_PLAY_REC_FILE.Location = new System.Drawing.Point(85, 193);
            this.BTN_PLAY_REC_FILE.Name = "BTN_PLAY_REC_FILE";
            this.BTN_PLAY_REC_FILE.Size = new System.Drawing.Size(106, 25);
            this.BTN_PLAY_REC_FILE.TabIndex = 11;
            this.BTN_PLAY_REC_FILE.Text = "Play REC";
            this.BTN_PLAY_REC_FILE.UseVisualStyleBackColor = true;
            this.BTN_PLAY_REC_FILE.Click += new System.EventHandler(this.BTN_PLAY_REC_FILE_Click);
            // 
            // BTN_STOP_RECORDING
            // 
            this.BTN_STOP_RECORDING.Location = new System.Drawing.Point(203, 146);
            this.BTN_STOP_RECORDING.Name = "BTN_STOP_RECORDING";
            this.BTN_STOP_RECORDING.Size = new System.Drawing.Size(106, 25);
            this.BTN_STOP_RECORDING.TabIndex = 11;
            this.BTN_STOP_RECORDING.Text = "Stop Recording";
            this.BTN_STOP_RECORDING.UseVisualStyleBackColor = true;
            this.BTN_STOP_RECORDING.Click += new System.EventHandler(this.BTN_STOP_RECORDING_Click);
            // 
            // BTN_START_RECORDING
            // 
            this.BTN_START_RECORDING.Location = new System.Drawing.Point(86, 146);
            this.BTN_START_RECORDING.Name = "BTN_START_RECORDING";
            this.BTN_START_RECORDING.Size = new System.Drawing.Size(106, 25);
            this.BTN_START_RECORDING.TabIndex = 11;
            this.BTN_START_RECORDING.Text = "Start Recording";
            this.BTN_START_RECORDING.UseVisualStyleBackColor = true;
            this.BTN_START_RECORDING.Click += new System.EventHandler(this.BTN_START_RECORDING_Click);
            // 
            // axXnsSdkWindow_Recording
            // 
            this.axXnsSdkWindow_Recording.Enabled = true;
            this.axXnsSdkWindow_Recording.Location = new System.Drawing.Point(13, 426);
            this.axXnsSdkWindow_Recording.Name = "axXnsSdkWindow_Recording";
            this.axXnsSdkWindow_Recording.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow_Recording.OcxState")));
            this.axXnsSdkWindow_Recording.Size = new System.Drawing.Size(361, 242);
            this.axXnsSdkWindow_Recording.TabIndex = 13;
            this.axXnsSdkWindow_Recording.OnMediaOff += new System.EventHandler(this.axXnsSdkWindow_Recording_OnMediaOff);
            // 
            // axXnsSdkWindow
            // 
            this.axXnsSdkWindow.Enabled = true;
            this.axXnsSdkWindow.Location = new System.Drawing.Point(12, 12);
            this.axXnsSdkWindow.Name = "axXnsSdkWindow";
            this.axXnsSdkWindow.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow.OcxState")));
            this.axXnsSdkWindow.Size = new System.Drawing.Size(362, 275);
            this.axXnsSdkWindow.TabIndex = 8;
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(348, 296);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(26, 14);
            this.axXnsSdkDevice.TabIndex = 7;
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            // 
            // CHECKBOX_SUNAPI
            // 
            this.CHECKBOX_SUNAPI.Location = new System.Drawing.Point(86, 55);
            this.CHECKBOX_SUNAPI.Name = "CHECKBOX_SUNAPI";
            this.CHECKBOX_SUNAPI.Size = new System.Drawing.Size(78, 24);
            this.CHECKBOX_SUNAPI.TabIndex = 21;
            this.CHECKBOX_SUNAPI.Text = "SUNAPI";
            this.CHECKBOX_SUNAPI.UseVisualStyleBackColor = true;
            // 
            // LocalRecordingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(723, 681);
            this.Controls.Add(this.axXnsSdkWindow_Recording);
            this.Controls.Add(this.STR_ACTIVEX_CONTROL_LOG);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.axXnsSdkWindow);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Controls.Add(this.GROUP_LOCAL_RECORDING);
            this.Controls.Add(this.GROUP_CONNECTION_INFO);
            this.Name = "LocalRecordingForm";
            this.Text = "LocalRecording";
            this.Load += new System.EventHandler(this.LocalRecordingForm_Load);
            this.GROUP_CONNECTION_INFO.ResumeLayout(false);
            this.GROUP_CONNECTION_INFO.PerformLayout();
            this.GROUP_LOCAL_RECORDING.ResumeLayout(false);
            this.GROUP_RECORDING_TYPE.ResumeLayout(false);
            this.GROUP_RECORDING_TYPE.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow_Recording)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox GROUP_CONNECTION_INFO;
        private System.Windows.Forms.Button BTN_PLAY;
        private System.Windows.Forms.Button BTN_STOP;
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
        private AxXNSSDKDEVICELib.AxXnsSdkDevice axXnsSdkDevice;
        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow;
        private System.Windows.Forms.Label STR_ACTIVEX_CONTROL_LOG;
        private System.Windows.Forms.ListBox LIST_LOG;
        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow_Recording;
        private System.Windows.Forms.GroupBox GROUP_LOCAL_RECORDING;
        private System.Windows.Forms.Button BTN_PLAY_REC_FILE;
        private System.Windows.Forms.Button BTN_STOP_RECORDING;
        private System.Windows.Forms.Button BTN_START_RECORDING;
        private System.Windows.Forms.GroupBox GROUP_RECORDING_TYPE;
        private System.Windows.Forms.RadioButton RADIO_SEC;
        private System.Windows.Forms.RadioButton RADIO_REC;
        private System.Windows.Forms.Button BTN_STOP_REC_FILE;
        private System.Windows.Forms.TextBox EDIT_HTTPPORT;
        private System.Windows.Forms.Label STR_HTTPPORT;
        private System.Windows.Forms.Label STR_PROTOCOL;
        private System.Windows.Forms.CheckBox CHECKBOX_SUNAPI;
    }
}

