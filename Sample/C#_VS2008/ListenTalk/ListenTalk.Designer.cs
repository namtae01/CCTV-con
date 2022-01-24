namespace ListenTalk
{
    partial class ListenTalkForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ListenTalkForm));
            this.axXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.GROUP_CONNECTION_INFO = new System.Windows.Forms.GroupBox();
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
            this.STR_MODEL = new System.Windows.Forms.Label();
            this.STR_IP = new System.Windows.Forms.Label();
            this.BTN_PLAY = new System.Windows.Forms.Button();
            this.BTN_STOP = new System.Windows.Forms.Button();
            this.STR_CHANNEL = new System.Windows.Forms.Label();
            this.STR_ACTIVEX_CONTROL_LOG = new System.Windows.Forms.Label();
            this.LIST_LOG = new System.Windows.Forms.ListBox();
            this.CHECK_LISTEN = new System.Windows.Forms.CheckBox();
            this.CHECK_TALK = new System.Windows.Forms.CheckBox();
            this.GROUP_LIVE_CONTROL = new System.Windows.Forms.GroupBox();
            this.COMBO_BIT_PER_SAMPLE = new System.Windows.Forms.ComboBox();
            this.COMBO_SAMPLE_PER_SECOND = new System.Windows.Forms.ComboBox();
            this.COMBO_CHANNEL = new System.Windows.Forms.ComboBox();
            this.EDIT_SEND_BYTES = new System.Windows.Forms.TextBox();
            this.BTN_STOP_AUDIO = new System.Windows.Forms.Button();
            this.BTN_SEND_AUDIO = new System.Windows.Forms.Button();
            this.STR_SAMPLE = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.STR_PKT = new System.Windows.Forms.Label();
            this.STR_BITS = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).BeginInit();
            this.GROUP_CONNECTION_INFO.SuspendLayout();
            this.GROUP_LIVE_CONTROL.SuspendLayout();
            this.SuspendLayout();
            // 
            // axXnsSdkWindow
            // 
            this.axXnsSdkWindow.Enabled = true;
            this.axXnsSdkWindow.Location = new System.Drawing.Point(12, 13);
            this.axXnsSdkWindow.Name = "axXnsSdkWindow";
            this.axXnsSdkWindow.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow.OcxState")));
            this.axXnsSdkWindow.Size = new System.Drawing.Size(439, 379);
            this.axXnsSdkWindow.TabIndex = 0;
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(401, 398);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(31, 22);
            this.axXnsSdkDevice.TabIndex = 1;
            this.axXnsSdkDevice.Visible = false;
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            // 
            // GROUP_CONNECTION_INFO
            // 
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
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_MODEL);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_IP);
            this.GROUP_CONNECTION_INFO.Location = new System.Drawing.Point(466, 13);
            this.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO";
            this.GROUP_CONNECTION_INFO.Size = new System.Drawing.Size(244, 207);
            this.GROUP_CONNECTION_INFO.TabIndex = 6;
            this.GROUP_CONNECTION_INFO.TabStop = false;
            this.GROUP_CONNECTION_INFO.Text = "Connection Information";
            // 
            // BTN_DISCONNECT
            // 
            this.BTN_DISCONNECT.Location = new System.Drawing.Point(141, 172);
            this.BTN_DISCONNECT.Name = "BTN_DISCONNECT";
            this.BTN_DISCONNECT.Size = new System.Drawing.Size(90, 25);
            this.BTN_DISCONNECT.TabIndex = 11;
            this.BTN_DISCONNECT.Text = "Disconnect";
            this.BTN_DISCONNECT.UseVisualStyleBackColor = true;
            this.BTN_DISCONNECT.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // BTN_CONNECT
            // 
            this.BTN_CONNECT.Location = new System.Drawing.Point(14, 172);
            this.BTN_CONNECT.Name = "BTN_CONNECT";
            this.BTN_CONNECT.Size = new System.Drawing.Size(90, 25);
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
            this.COMBO_MODELLIST.Size = new System.Drawing.Size(145, 20);
            this.COMBO_MODELLIST.TabIndex = 10;
            // 
            // EDIT_PW
            // 
            this.EDIT_PW.Location = new System.Drawing.Point(86, 137);
            this.EDIT_PW.Name = "EDIT_PW";
            this.EDIT_PW.Size = new System.Drawing.Size(145, 21);
            this.EDIT_PW.TabIndex = 9;
            this.EDIT_PW.UseSystemPasswordChar = true;
            // 
            // EDIT_ID
            // 
            this.EDIT_ID.Location = new System.Drawing.Point(86, 110);
            this.EDIT_ID.Name = "EDIT_ID";
            this.EDIT_ID.Size = new System.Drawing.Size(145, 21);
            this.EDIT_ID.TabIndex = 8;
            // 
            // EDIT_PORT
            // 
            this.EDIT_PORT.Location = new System.Drawing.Point(86, 83);
            this.EDIT_PORT.Name = "EDIT_PORT";
            this.EDIT_PORT.Size = new System.Drawing.Size(145, 21);
            this.EDIT_PORT.TabIndex = 7;
            // 
            // EDIT_IP
            // 
            this.EDIT_IP.Location = new System.Drawing.Point(86, 56);
            this.EDIT_IP.Name = "EDIT_IP";
            this.EDIT_IP.Size = new System.Drawing.Size(145, 21);
            this.EDIT_IP.TabIndex = 6;
            // 
            // STR_PW
            // 
            this.STR_PW.AutoSize = true;
            this.STR_PW.Location = new System.Drawing.Point(13, 146);
            this.STR_PW.Name = "STR_PW";
            this.STR_PW.Size = new System.Drawing.Size(67, 12);
            this.STR_PW.TabIndex = 4;
            this.STR_PW.Text = "PW         : ";
            // 
            // STR_ID
            // 
            this.STR_ID.AutoSize = true;
            this.STR_ID.Location = new System.Drawing.Point(12, 113);
            this.STR_ID.Name = "STR_ID";
            this.STR_ID.Size = new System.Drawing.Size(68, 12);
            this.STR_ID.TabIndex = 3;
            this.STR_ID.Text = "ID           : ";
            // 
            // STR_PORT
            // 
            this.STR_PORT.AutoSize = true;
            this.STR_PORT.Location = new System.Drawing.Point(12, 86);
            this.STR_PORT.Name = "STR_PORT";
            this.STR_PORT.Size = new System.Drawing.Size(68, 12);
            this.STR_PORT.TabIndex = 2;
            this.STR_PORT.Text = "VNP Port : ";
            // 
            // STR_MODEL
            // 
            this.STR_MODEL.AutoSize = true;
            this.STR_MODEL.Location = new System.Drawing.Point(12, 32);
            this.STR_MODEL.Name = "STR_MODEL";
            this.STR_MODEL.Size = new System.Drawing.Size(68, 12);
            this.STR_MODEL.TabIndex = 0;
            this.STR_MODEL.Text = "Model     : ";
            // 
            // STR_IP
            // 
            this.STR_IP.AutoSize = true;
            this.STR_IP.Location = new System.Drawing.Point(12, 59);
            this.STR_IP.Name = "STR_IP";
            this.STR_IP.Size = new System.Drawing.Size(64, 12);
            this.STR_IP.TabIndex = 1;
            this.STR_IP.Text = "IP           :";
            // 
            // BTN_PLAY
            // 
            this.BTN_PLAY.Location = new System.Drawing.Point(14, 18);
            this.BTN_PLAY.Name = "BTN_PLAY";
            this.BTN_PLAY.Size = new System.Drawing.Size(90, 25);
            this.BTN_PLAY.TabIndex = 11;
            this.BTN_PLAY.Text = "Play";
            this.BTN_PLAY.UseVisualStyleBackColor = true;
            this.BTN_PLAY.Click += new System.EventHandler(this.BTN_PLAY_Click);
            // 
            // BTN_STOP
            // 
            this.BTN_STOP.Location = new System.Drawing.Point(141, 18);
            this.BTN_STOP.Name = "BTN_STOP";
            this.BTN_STOP.Size = new System.Drawing.Size(90, 25);
            this.BTN_STOP.TabIndex = 11;
            this.BTN_STOP.Text = "Stop";
            this.BTN_STOP.UseVisualStyleBackColor = true;
            this.BTN_STOP.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // STR_CHANNEL
            // 
            this.STR_CHANNEL.AutoSize = true;
            this.STR_CHANNEL.Location = new System.Drawing.Point(13, 79);
            this.STR_CHANNEL.Name = "STR_CHANNEL";
            this.STR_CHANNEL.Size = new System.Drawing.Size(52, 12);
            this.STR_CHANNEL.TabIndex = 1;
            this.STR_CHANNEL.Text = "Channel";
            // 
            // STR_ACTIVEX_CONTROL_LOG
            // 
            this.STR_ACTIVEX_CONTROL_LOG.AutoSize = true;
            this.STR_ACTIVEX_CONTROL_LOG.Location = new System.Drawing.Point(10, 408);
            this.STR_ACTIVEX_CONTROL_LOG.Name = "STR_ACTIVEX_CONTROL_LOG";
            this.STR_ACTIVEX_CONTROL_LOG.Size = new System.Drawing.Size(116, 12);
            this.STR_ACTIVEX_CONTROL_LOG.TabIndex = 14;
            this.STR_ACTIVEX_CONTROL_LOG.Text = "ActiveX Control Log";
            // 
            // LIST_LOG
            // 
            this.LIST_LOG.FormattingEnabled = true;
            this.LIST_LOG.ItemHeight = 12;
            this.LIST_LOG.Location = new System.Drawing.Point(12, 421);
            this.LIST_LOG.Name = "LIST_LOG";
            this.LIST_LOG.Size = new System.Drawing.Size(698, 208);
            this.LIST_LOG.TabIndex = 13;
            // 
            // CHECK_LISTEN
            // 
            this.CHECK_LISTEN.AutoSize = true;
            this.CHECK_LISTEN.Location = new System.Drawing.Point(15, 49);
            this.CHECK_LISTEN.Name = "CHECK_LISTEN";
            this.CHECK_LISTEN.Size = new System.Drawing.Size(58, 16);
            this.CHECK_LISTEN.TabIndex = 15;
            this.CHECK_LISTEN.Text = "Listen";
            this.CHECK_LISTEN.UseVisualStyleBackColor = true;
            this.CHECK_LISTEN.CheckedChanged += new System.EventHandler(this.CHECK_LISTEN_CheckedChanged);
            // 
            // CHECK_TALK
            // 
            this.CHECK_TALK.AutoSize = true;
            this.CHECK_TALK.Location = new System.Drawing.Point(141, 49);
            this.CHECK_TALK.Name = "CHECK_TALK";
            this.CHECK_TALK.Size = new System.Drawing.Size(48, 16);
            this.CHECK_TALK.TabIndex = 15;
            this.CHECK_TALK.Text = "Talk";
            this.CHECK_TALK.UseVisualStyleBackColor = true;
            this.CHECK_TALK.CheckedChanged += new System.EventHandler(this.CHECK_TALK_CheckedChanged);
            // 
            // GROUP_LIVE_CONTROL
            // 
            this.GROUP_LIVE_CONTROL.Controls.Add(this.COMBO_BIT_PER_SAMPLE);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.COMBO_SAMPLE_PER_SECOND);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.COMBO_CHANNEL);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.EDIT_SEND_BYTES);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.BTN_STOP);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.BTN_STOP_AUDIO);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.BTN_SEND_AUDIO);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.BTN_PLAY);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.CHECK_TALK);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.CHECK_LISTEN);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.STR_SAMPLE);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.label1);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.STR_PKT);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.STR_BITS);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.STR_CHANNEL);
            this.GROUP_LIVE_CONTROL.Location = new System.Drawing.Point(466, 226);
            this.GROUP_LIVE_CONTROL.Name = "GROUP_LIVE_CONTROL";
            this.GROUP_LIVE_CONTROL.Size = new System.Drawing.Size(244, 182);
            this.GROUP_LIVE_CONTROL.TabIndex = 16;
            this.GROUP_LIVE_CONTROL.TabStop = false;
            this.GROUP_LIVE_CONTROL.Text = "Live Control";
            // 
            // COMBO_BIT_PER_SAMPLE
            // 
            this.COMBO_BIT_PER_SAMPLE.FormattingEnabled = true;
            this.COMBO_BIT_PER_SAMPLE.Location = new System.Drawing.Point(171, 76);
            this.COMBO_BIT_PER_SAMPLE.Name = "COMBO_BIT_PER_SAMPLE";
            this.COMBO_BIT_PER_SAMPLE.Size = new System.Drawing.Size(60, 20);
            this.COMBO_BIT_PER_SAMPLE.TabIndex = 16;
            // 
            // COMBO_SAMPLE_PER_SECOND
            // 
            this.COMBO_SAMPLE_PER_SECOND.FormattingEnabled = true;
            this.COMBO_SAMPLE_PER_SECOND.Location = new System.Drawing.Point(67, 111);
            this.COMBO_SAMPLE_PER_SECOND.Name = "COMBO_SAMPLE_PER_SECOND";
            this.COMBO_SAMPLE_PER_SECOND.Size = new System.Drawing.Size(60, 20);
            this.COMBO_SAMPLE_PER_SECOND.TabIndex = 16;
            // 
            // COMBO_CHANNEL
            // 
            this.COMBO_CHANNEL.FormattingEnabled = true;
            this.COMBO_CHANNEL.Location = new System.Drawing.Point(67, 76);
            this.COMBO_CHANNEL.Name = "COMBO_CHANNEL";
            this.COMBO_CHANNEL.Size = new System.Drawing.Size(60, 20);
            this.COMBO_CHANNEL.TabIndex = 16;
            // 
            // EDIT_SEND_BYTES
            // 
            this.EDIT_SEND_BYTES.Location = new System.Drawing.Point(171, 111);
            this.EDIT_SEND_BYTES.Name = "EDIT_SEND_BYTES";
            this.EDIT_SEND_BYTES.Size = new System.Drawing.Size(60, 21);
            this.EDIT_SEND_BYTES.TabIndex = 9;
            // 
            // BTN_STOP_AUDIO
            // 
            this.BTN_STOP_AUDIO.Location = new System.Drawing.Point(141, 144);
            this.BTN_STOP_AUDIO.Name = "BTN_STOP_AUDIO";
            this.BTN_STOP_AUDIO.Size = new System.Drawing.Size(90, 25);
            this.BTN_STOP_AUDIO.TabIndex = 11;
            this.BTN_STOP_AUDIO.Text = "Stop Audio";
            this.BTN_STOP_AUDIO.UseVisualStyleBackColor = true;
            this.BTN_STOP_AUDIO.Click += new System.EventHandler(this.BTN_STOP_AUDIO_Click);
            // 
            // BTN_SEND_AUDIO
            // 
            this.BTN_SEND_AUDIO.Location = new System.Drawing.Point(14, 144);
            this.BTN_SEND_AUDIO.Name = "BTN_SEND_AUDIO";
            this.BTN_SEND_AUDIO.Size = new System.Drawing.Size(90, 25);
            this.BTN_SEND_AUDIO.TabIndex = 11;
            this.BTN_SEND_AUDIO.Text = "Send Audio";
            this.BTN_SEND_AUDIO.UseVisualStyleBackColor = true;
            this.BTN_SEND_AUDIO.Click += new System.EventHandler(this.BTN_SEND_AUDIO_Click);
            // 
            // STR_SAMPLE
            // 
            this.STR_SAMPLE.AutoSize = true;
            this.STR_SAMPLE.Location = new System.Drawing.Point(13, 114);
            this.STR_SAMPLE.Name = "STR_SAMPLE";
            this.STR_SAMPLE.Size = new System.Drawing.Size(48, 12);
            this.STR_SAMPLE.TabIndex = 1;
            this.STR_SAMPLE.Text = "Sample";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(143, 114);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(0, 12);
            this.label1.TabIndex = 1;
            // 
            // STR_PKT
            // 
            this.STR_PKT.AutoSize = true;
            this.STR_PKT.Location = new System.Drawing.Point(139, 114);
            this.STR_PKT.Name = "STR_PKT";
            this.STR_PKT.Size = new System.Drawing.Size(22, 12);
            this.STR_PKT.TabIndex = 1;
            this.STR_PKT.Text = "Pkt";
            // 
            // STR_BITS
            // 
            this.STR_BITS.AutoSize = true;
            this.STR_BITS.Location = new System.Drawing.Point(139, 79);
            this.STR_BITS.Name = "STR_BITS";
            this.STR_BITS.Size = new System.Drawing.Size(26, 12);
            this.STR_BITS.TabIndex = 1;
            this.STR_BITS.Text = "Bits";
            // 
            // ListenTalkForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(725, 641);
            this.Controls.Add(this.GROUP_LIVE_CONTROL);
            this.Controls.Add(this.STR_ACTIVEX_CONTROL_LOG);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.GROUP_CONNECTION_INFO);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Controls.Add(this.axXnsSdkWindow);
            this.Name = "ListenTalkForm";
            this.Text = "ListenTalk";
            this.Load += new System.EventHandler(this.ListenTalkForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
            this.GROUP_CONNECTION_INFO.ResumeLayout(false);
            this.GROUP_CONNECTION_INFO.PerformLayout();
            this.GROUP_LIVE_CONTROL.ResumeLayout(false);
            this.GROUP_LIVE_CONTROL.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow;
        private AxXNSSDKDEVICELib.AxXnsSdkDevice axXnsSdkDevice;
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
        private System.Windows.Forms.Label STR_CHANNEL;
        private System.Windows.Forms.Label STR_MODEL;
        private System.Windows.Forms.Label STR_ACTIVEX_CONTROL_LOG;
        private System.Windows.Forms.ListBox LIST_LOG;
        private System.Windows.Forms.CheckBox CHECK_LISTEN;
        private System.Windows.Forms.CheckBox CHECK_TALK;
        private System.Windows.Forms.GroupBox GROUP_LIVE_CONTROL;
        private System.Windows.Forms.ComboBox COMBO_BIT_PER_SAMPLE;
        private System.Windows.Forms.ComboBox COMBO_SAMPLE_PER_SECOND;
        private System.Windows.Forms.ComboBox COMBO_CHANNEL;
        private System.Windows.Forms.Button BTN_STOP_AUDIO;
        private System.Windows.Forms.Button BTN_SEND_AUDIO;
        private System.Windows.Forms.Label STR_IP;
        private System.Windows.Forms.Label STR_SAMPLE;
        private System.Windows.Forms.Label STR_PKT;
        private System.Windows.Forms.Label STR_BITS;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox EDIT_SEND_BYTES;
    }
}

