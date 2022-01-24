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
            this.BTN_PLAY = new System.Windows.Forms.Button();
            this.BTN_STOP = new System.Windows.Forms.Button();
            this.STR_ACTIVEX_CONTROL_LOG = new System.Windows.Forms.Label();
            this.LIST_LOG = new System.Windows.Forms.ListBox();
            this.CHECK_LISTEN = new System.Windows.Forms.CheckBox();
            this.CHECK_TALK = new System.Windows.Forms.CheckBox();
            this.GROUP_LIVE_CONTROL = new System.Windows.Forms.GroupBox();
            this.BTN_STOP_AUDIO = new System.Windows.Forms.Button();
            this.BTN_SEND_AUDIO = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.CHECKBOX_SUNAPI = new System.Windows.Forms.CheckBox();
            this.EDIT_HTTPPORT = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.BTN_DISCONNECT = new System.Windows.Forms.Button();
            this.BTN_CONNECT = new System.Windows.Forms.Button();
            this.COMBO_MODELLIST = new System.Windows.Forms.ComboBox();
            this.EDIT_PW = new System.Windows.Forms.TextBox();
            this.EDIT_ID = new System.Windows.Forms.TextBox();
            this.EDIT_PORT = new System.Windows.Forms.TextBox();
            this.EDIT_IP = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.axXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.GROUP_LIVE_CONTROL.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).BeginInit();
            this.SuspendLayout();
            // 
            // BTN_PLAY
            // 
            this.BTN_PLAY.Location = new System.Drawing.Point(18, 18);
            this.BTN_PLAY.Name = "BTN_PLAY";
            this.BTN_PLAY.Size = new System.Drawing.Size(121, 25);
            this.BTN_PLAY.TabIndex = 11;
            this.BTN_PLAY.Text = "Play";
            this.BTN_PLAY.UseVisualStyleBackColor = true;
            this.BTN_PLAY.Click += new System.EventHandler(this.BTN_PLAY_Click);
            // 
            // BTN_STOP
            // 
            this.BTN_STOP.Location = new System.Drawing.Point(157, 18);
            this.BTN_STOP.Name = "BTN_STOP";
            this.BTN_STOP.Size = new System.Drawing.Size(121, 25);
            this.BTN_STOP.TabIndex = 11;
            this.BTN_STOP.Text = "Stop";
            this.BTN_STOP.UseVisualStyleBackColor = true;
            this.BTN_STOP.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // STR_ACTIVEX_CONTROL_LOG
            // 
            this.STR_ACTIVEX_CONTROL_LOG.AutoSize = true;
            this.STR_ACTIVEX_CONTROL_LOG.Location = new System.Drawing.Point(10, 399);
            this.STR_ACTIVEX_CONTROL_LOG.Name = "STR_ACTIVEX_CONTROL_LOG";
            this.STR_ACTIVEX_CONTROL_LOG.Size = new System.Drawing.Size(116, 12);
            this.STR_ACTIVEX_CONTROL_LOG.TabIndex = 14;
            this.STR_ACTIVEX_CONTROL_LOG.Text = "ActiveX Control Log";
            // 
            // LIST_LOG
            // 
            this.LIST_LOG.FormattingEnabled = true;
            this.LIST_LOG.ItemHeight = 12;
            this.LIST_LOG.Location = new System.Drawing.Point(12, 413);
            this.LIST_LOG.Name = "LIST_LOG";
            this.LIST_LOG.Size = new System.Drawing.Size(749, 196);
            this.LIST_LOG.TabIndex = 13;
            // 
            // CHECK_LISTEN
            // 
            this.CHECK_LISTEN.AutoSize = true;
            this.CHECK_LISTEN.Location = new System.Drawing.Point(18, 49);
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
            this.CHECK_TALK.Location = new System.Drawing.Point(158, 49);
            this.CHECK_TALK.Name = "CHECK_TALK";
            this.CHECK_TALK.Size = new System.Drawing.Size(48, 16);
            this.CHECK_TALK.TabIndex = 15;
            this.CHECK_TALK.Text = "Talk";
            this.CHECK_TALK.UseVisualStyleBackColor = true;
            this.CHECK_TALK.CheckedChanged += new System.EventHandler(this.CHECK_TALK_CheckedChanged);
            // 
            // GROUP_LIVE_CONTROL
            // 
            this.GROUP_LIVE_CONTROL.Controls.Add(this.BTN_STOP);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.BTN_STOP_AUDIO);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.BTN_SEND_AUDIO);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.BTN_PLAY);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.CHECK_TALK);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.CHECK_LISTEN);
            this.GROUP_LIVE_CONTROL.Controls.Add(this.label1);
            this.GROUP_LIVE_CONTROL.Location = new System.Drawing.Point(466, 274);
            this.GROUP_LIVE_CONTROL.Name = "GROUP_LIVE_CONTROL";
            this.GROUP_LIVE_CONTROL.Size = new System.Drawing.Size(295, 109);
            this.GROUP_LIVE_CONTROL.TabIndex = 16;
            this.GROUP_LIVE_CONTROL.TabStop = false;
            this.GROUP_LIVE_CONTROL.Text = "Live Control";
            // 
            // BTN_STOP_AUDIO
            // 
            this.BTN_STOP_AUDIO.Location = new System.Drawing.Point(157, 71);
            this.BTN_STOP_AUDIO.Name = "BTN_STOP_AUDIO";
            this.BTN_STOP_AUDIO.Size = new System.Drawing.Size(121, 25);
            this.BTN_STOP_AUDIO.TabIndex = 11;
            this.BTN_STOP_AUDIO.Text = "Stop Audio";
            this.BTN_STOP_AUDIO.UseVisualStyleBackColor = true;
            this.BTN_STOP_AUDIO.Click += new System.EventHandler(this.BTN_STOP_AUDIO_Click);
            // 
            // BTN_SEND_AUDIO
            // 
            this.BTN_SEND_AUDIO.Location = new System.Drawing.Point(18, 71);
            this.BTN_SEND_AUDIO.Name = "BTN_SEND_AUDIO";
            this.BTN_SEND_AUDIO.Size = new System.Drawing.Size(121, 25);
            this.BTN_SEND_AUDIO.TabIndex = 11;
            this.BTN_SEND_AUDIO.Text = "Send Audio";
            this.BTN_SEND_AUDIO.UseVisualStyleBackColor = true;
            this.BTN_SEND_AUDIO.Click += new System.EventHandler(this.BTN_SEND_AUDIO_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(143, 114);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(0, 12);
            this.label1.TabIndex = 1;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.CHECKBOX_SUNAPI);
            this.groupBox1.Controls.Add(this.EDIT_HTTPPORT);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.BTN_DISCONNECT);
            this.groupBox1.Controls.Add(this.BTN_CONNECT);
            this.groupBox1.Controls.Add(this.COMBO_MODELLIST);
            this.groupBox1.Controls.Add(this.EDIT_PW);
            this.groupBox1.Controls.Add(this.EDIT_ID);
            this.groupBox1.Controls.Add(this.EDIT_PORT);
            this.groupBox1.Controls.Add(this.EDIT_IP);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Location = new System.Drawing.Point(466, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(295, 255);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Connection Information";
            // 
            // CHECKBOX_SUNAPI
            // 
            this.CHECKBOX_SUNAPI.Location = new System.Drawing.Point(86, 54);
            this.CHECKBOX_SUNAPI.Name = "CHECKBOX_SUNAPI";
            this.CHECKBOX_SUNAPI.Size = new System.Drawing.Size(78, 24);
            this.CHECKBOX_SUNAPI.TabIndex = 20;
            this.CHECKBOX_SUNAPI.Text = "SUNAPI";
            this.CHECKBOX_SUNAPI.UseVisualStyleBackColor = true;
            // 
            // EDIT_HTTPPORT
            // 
            this.EDIT_HTTPPORT.Location = new System.Drawing.Point(86, 135);
            this.EDIT_HTTPPORT.Name = "EDIT_HTTPPORT";
            this.EDIT_HTTPPORT.Size = new System.Drawing.Size(193, 21);
            this.EDIT_HTTPPORT.TabIndex = 16;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 140);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(63, 12);
            this.label4.TabIndex = 15;
            this.label4.Text = "HTTP Port";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 59);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(51, 12);
            this.label5.TabIndex = 12;
            this.label5.Text = "Protocol";
            // 
            // BTN_DISCONNECT
            // 
            this.BTN_DISCONNECT.Location = new System.Drawing.Point(158, 224);
            this.BTN_DISCONNECT.Name = "BTN_DISCONNECT";
            this.BTN_DISCONNECT.Size = new System.Drawing.Size(121, 25);
            this.BTN_DISCONNECT.TabIndex = 11;
            this.BTN_DISCONNECT.Text = "Disconnect";
            this.BTN_DISCONNECT.UseVisualStyleBackColor = true;
            this.BTN_DISCONNECT.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // BTN_CONNECT
            // 
            this.BTN_CONNECT.Location = new System.Drawing.Point(18, 224);
            this.BTN_CONNECT.Name = "BTN_CONNECT";
            this.BTN_CONNECT.Size = new System.Drawing.Size(121, 25);
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
            this.COMBO_MODELLIST.Size = new System.Drawing.Size(193, 20);
            this.COMBO_MODELLIST.TabIndex = 10;
            // 
            // EDIT_PW
            // 
            this.EDIT_PW.Location = new System.Drawing.Point(86, 189);
            this.EDIT_PW.Name = "EDIT_PW";
            this.EDIT_PW.Size = new System.Drawing.Size(193, 21);
            this.EDIT_PW.TabIndex = 9;
            this.EDIT_PW.UseSystemPasswordChar = true;
            // 
            // EDIT_ID
            // 
            this.EDIT_ID.Location = new System.Drawing.Point(86, 162);
            this.EDIT_ID.Name = "EDIT_ID";
            this.EDIT_ID.Size = new System.Drawing.Size(193, 21);
            this.EDIT_ID.TabIndex = 8;
            // 
            // EDIT_PORT
            // 
            this.EDIT_PORT.Location = new System.Drawing.Point(86, 108);
            this.EDIT_PORT.Name = "EDIT_PORT";
            this.EDIT_PORT.Size = new System.Drawing.Size(193, 21);
            this.EDIT_PORT.TabIndex = 7;
            // 
            // EDIT_IP
            // 
            this.EDIT_IP.Location = new System.Drawing.Point(86, 81);
            this.EDIT_IP.Name = "EDIT_IP";
            this.EDIT_IP.Size = new System.Drawing.Size(193, 21);
            this.EDIT_IP.TabIndex = 6;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(13, 194);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(23, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "PW";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 167);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(16, 12);
            this.label7.TabIndex = 3;
            this.label7.Text = "ID";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(12, 113);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(69, 12);
            this.label8.TabIndex = 2;
            this.label8.Text = "Device Port";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(12, 33);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(40, 12);
            this.label9.TabIndex = 0;
            this.label9.Text = "Model";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(12, 86);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(16, 12);
            this.label10.TabIndex = 1;
            this.label10.Text = "IP";
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(730, 389);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(31, 22);
            this.axXnsSdkDevice.TabIndex = 1;
            this.axXnsSdkDevice.Visible = false;
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            // 
            // axXnsSdkWindow
            // 
            this.axXnsSdkWindow.Enabled = true;
            this.axXnsSdkWindow.Location = new System.Drawing.Point(12, 13);
            this.axXnsSdkWindow.Name = "axXnsSdkWindow";
            this.axXnsSdkWindow.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow.OcxState")));
            this.axXnsSdkWindow.Size = new System.Drawing.Size(439, 357);
            this.axXnsSdkWindow.TabIndex = 0;
            // 
            // ListenTalkForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(773, 621);
            this.Controls.Add(this.GROUP_LIVE_CONTROL);
            this.Controls.Add(this.STR_ACTIVEX_CONTROL_LOG);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Controls.Add(this.axXnsSdkWindow);
            this.Name = "ListenTalkForm";
            this.Text = "ListenTalk";
            this.Load += new System.EventHandler(this.ListenTalkForm_Load);
            this.GROUP_LIVE_CONTROL.ResumeLayout(false);
            this.GROUP_LIVE_CONTROL.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow;
        private AxXNSSDKDEVICELib.AxXnsSdkDevice axXnsSdkDevice;
        private System.Windows.Forms.Button BTN_PLAY;
        private System.Windows.Forms.Button BTN_STOP;
        private System.Windows.Forms.Label STR_ACTIVEX_CONTROL_LOG;
        private System.Windows.Forms.ListBox LIST_LOG;
        private System.Windows.Forms.CheckBox CHECK_LISTEN;
        private System.Windows.Forms.CheckBox CHECK_TALK;
        private System.Windows.Forms.GroupBox GROUP_LIVE_CONTROL;
        private System.Windows.Forms.Button BTN_STOP_AUDIO;
        private System.Windows.Forms.Button BTN_SEND_AUDIO;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox EDIT_HTTPPORT;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button BTN_DISCONNECT;
        private System.Windows.Forms.Button BTN_CONNECT;
        private System.Windows.Forms.ComboBox COMBO_MODELLIST;
        private System.Windows.Forms.TextBox EDIT_PW;
        private System.Windows.Forms.TextBox EDIT_ID;
        private System.Windows.Forms.TextBox EDIT_PORT;
        private System.Windows.Forms.TextBox EDIT_IP;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.CheckBox CHECKBOX_SUNAPI;
    }
}

