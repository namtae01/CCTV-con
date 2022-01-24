namespace PlayBack
{
    partial class PlayBackForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PlayBackForm));
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
            this.STR_IPADDRESS = new System.Windows.Forms.Label();
            this.STR_MODEL = new System.Windows.Forms.Label();
            this.BTN_CHECK_CALENDAR = new System.Windows.Forms.Button();
            this.GROUP_RECORD_FILE = new System.Windows.Forms.GroupBox();
            this.MONTH_CALENDAR = new System.Windows.Forms.MonthCalendar();
            this.LISTBOX_RECORD_FILE = new System.Windows.Forms.ListBox();
            this.GROUP_PLAY_RECORD_FILE = new System.Windows.Forms.GroupBox();
            this.STR_TIME = new System.Windows.Forms.Label();
            this.COMBO_SPEED = new System.Windows.Forms.ComboBox();
            this.BTN_NPLAY = new System.Windows.Forms.Button();
            this.BTN_PLAY = new System.Windows.Forms.Button();
            this.BTN_STOP = new System.Windows.Forms.Button();
            this.BTN_REWARD = new System.Windows.Forms.Button();
            this.BTN_NREWARD = new System.Windows.Forms.Button();
            this.TRACKBAR_PLAY = new System.Windows.Forms.TrackBar();
            this.LIST_LOG = new System.Windows.Forms.ListBox();
            this.STR_STATUS_MESSAGE = new System.Windows.Forms.Label();
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.axXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.EDIT_HTTPPORT = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.CHECKBOX_SUNAPI = new System.Windows.Forms.CheckBox();
            this.label4 = new System.Windows.Forms.Label();
            this.GROUP_CONNECTION_INFO.SuspendLayout();
            this.GROUP_RECORD_FILE.SuspendLayout();
            this.GROUP_PLAY_RECORD_FILE.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TRACKBAR_PLAY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).BeginInit();
            this.SuspendLayout();
            // 
            // GROUP_CONNECTION_INFO
            // 
            this.GROUP_CONNECTION_INFO.Controls.Add(this.CHECKBOX_SUNAPI);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.label4);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_HTTPPORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.label1);
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
            this.GROUP_CONNECTION_INFO.Location = new System.Drawing.Point(511, 12);
            this.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO";
            this.GROUP_CONNECTION_INFO.Size = new System.Drawing.Size(248, 264);
            this.GROUP_CONNECTION_INFO.TabIndex = 3;
            this.GROUP_CONNECTION_INFO.TabStop = false;
            this.GROUP_CONNECTION_INFO.Text = "Connection Information";
            // 
            // BTN_DISCONNECT
            // 
            this.BTN_DISCONNECT.Location = new System.Drawing.Point(144, 222);
            this.BTN_DISCONNECT.Name = "BTN_DISCONNECT";
            this.BTN_DISCONNECT.Size = new System.Drawing.Size(90, 25);
            this.BTN_DISCONNECT.TabIndex = 12;
            this.BTN_DISCONNECT.Text = "DisConnect";
            this.BTN_DISCONNECT.UseVisualStyleBackColor = true;
            this.BTN_DISCONNECT.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // BTN_CONNECT
            // 
            this.BTN_CONNECT.Location = new System.Drawing.Point(14, 222);
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
            this.COMBO_MODELLIST.Size = new System.Drawing.Size(148, 20);
            this.COMBO_MODELLIST.TabIndex = 10;
            // 
            // EDIT_PW
            // 
            this.EDIT_PW.Location = new System.Drawing.Point(86, 186);
            this.EDIT_PW.Name = "EDIT_PW";
            this.EDIT_PW.Size = new System.Drawing.Size(148, 21);
            this.EDIT_PW.TabIndex = 9;
            this.EDIT_PW.UseSystemPasswordChar = true;
            // 
            // EDIT_ID
            // 
            this.EDIT_ID.Location = new System.Drawing.Point(86, 159);
            this.EDIT_ID.Name = "EDIT_ID";
            this.EDIT_ID.Size = new System.Drawing.Size(148, 21);
            this.EDIT_ID.TabIndex = 8;
            // 
            // EDIT_PORT
            // 
            this.EDIT_PORT.Location = new System.Drawing.Point(86, 105);
            this.EDIT_PORT.Name = "EDIT_PORT";
            this.EDIT_PORT.Size = new System.Drawing.Size(148, 21);
            this.EDIT_PORT.TabIndex = 7;
            // 
            // EDIT_IP
            // 
            this.EDIT_IP.Location = new System.Drawing.Point(86, 78);
            this.EDIT_IP.Name = "EDIT_IP";
            this.EDIT_IP.Size = new System.Drawing.Size(148, 21);
            this.EDIT_IP.TabIndex = 6;
            // 
            // STR_PW
            // 
            this.STR_PW.AutoSize = true;
            this.STR_PW.Location = new System.Drawing.Point(13, 195);
            this.STR_PW.Name = "STR_PW";
            this.STR_PW.Size = new System.Drawing.Size(23, 12);
            this.STR_PW.TabIndex = 4;
            this.STR_PW.Text = "PW";
            // 
            // STR_ID
            // 
            this.STR_ID.AutoSize = true;
            this.STR_ID.Location = new System.Drawing.Point(12, 162);
            this.STR_ID.Name = "STR_ID";
            this.STR_ID.Size = new System.Drawing.Size(16, 12);
            this.STR_ID.TabIndex = 3;
            this.STR_ID.Text = "ID";
            // 
            // STR_PORT
            // 
            this.STR_PORT.AutoSize = true;
            this.STR_PORT.Location = new System.Drawing.Point(12, 108);
            this.STR_PORT.Name = "STR_PORT";
            this.STR_PORT.Size = new System.Drawing.Size(69, 12);
            this.STR_PORT.TabIndex = 2;
            this.STR_PORT.Text = "Device Port";
            // 
            // STR_IPADDRESS
            // 
            this.STR_IPADDRESS.AutoSize = true;
            this.STR_IPADDRESS.Location = new System.Drawing.Point(12, 81);
            this.STR_IPADDRESS.Name = "STR_IPADDRESS";
            this.STR_IPADDRESS.Size = new System.Drawing.Size(16, 12);
            this.STR_IPADDRESS.TabIndex = 1;
            this.STR_IPADDRESS.Text = "IP";
            // 
            // STR_MODEL
            // 
            this.STR_MODEL.AutoSize = true;
            this.STR_MODEL.Location = new System.Drawing.Point(12, 32);
            this.STR_MODEL.Name = "STR_MODEL";
            this.STR_MODEL.Size = new System.Drawing.Size(40, 12);
            this.STR_MODEL.TabIndex = 0;
            this.STR_MODEL.Text = "Model";
            // 
            // BTN_CHECK_CALENDAR
            // 
            this.BTN_CHECK_CALENDAR.Location = new System.Drawing.Point(15, 20);
            this.BTN_CHECK_CALENDAR.Name = "BTN_CHECK_CALENDAR";
            this.BTN_CHECK_CALENDAR.Size = new System.Drawing.Size(221, 25);
            this.BTN_CHECK_CALENDAR.TabIndex = 4;
            this.BTN_CHECK_CALENDAR.Text = "Check Calendar";
            this.BTN_CHECK_CALENDAR.UseVisualStyleBackColor = true;
            this.BTN_CHECK_CALENDAR.Click += new System.EventHandler(this.BTN_CHECK_CALENDAR_Click);
            // 
            // GROUP_RECORD_FILE
            // 
            this.GROUP_RECORD_FILE.Controls.Add(this.MONTH_CALENDAR);
            this.GROUP_RECORD_FILE.Controls.Add(this.BTN_CHECK_CALENDAR);
            this.GROUP_RECORD_FILE.Location = new System.Drawing.Point(511, 282);
            this.GROUP_RECORD_FILE.Name = "GROUP_RECORD_FILE";
            this.GROUP_RECORD_FILE.Size = new System.Drawing.Size(248, 233);
            this.GROUP_RECORD_FILE.TabIndex = 5;
            this.GROUP_RECORD_FILE.TabStop = false;
            this.GROUP_RECORD_FILE.Text = "Record File";
            // 
            // MONTH_CALENDAR
            // 
            this.MONTH_CALENDAR.Location = new System.Drawing.Point(16, 57);
            this.MONTH_CALENDAR.Name = "MONTH_CALENDAR";
            this.MONTH_CALENDAR.TabIndex = 6;
            this.MONTH_CALENDAR.DateSelected += new System.Windows.Forms.DateRangeEventHandler(this.MONTH_CALENDAR_DateSelected);
            // 
            // LISTBOX_RECORD_FILE
            // 
            this.LISTBOX_RECORD_FILE.FormattingEnabled = true;
            this.LISTBOX_RECORD_FILE.ItemHeight = 12;
            this.LISTBOX_RECORD_FILE.Location = new System.Drawing.Point(17, 22);
            this.LISTBOX_RECORD_FILE.Name = "LISTBOX_RECORD_FILE";
            this.LISTBOX_RECORD_FILE.Size = new System.Drawing.Size(220, 100);
            this.LISTBOX_RECORD_FILE.TabIndex = 6;
            this.LISTBOX_RECORD_FILE.DoubleClick += new System.EventHandler(this.LISTBOX_RECORD_FILE_DoubleClick);
            // 
            // GROUP_PLAY_RECORD_FILE
            // 
            this.GROUP_PLAY_RECORD_FILE.Controls.Add(this.STR_TIME);
            this.GROUP_PLAY_RECORD_FILE.Controls.Add(this.COMBO_SPEED);
            this.GROUP_PLAY_RECORD_FILE.Controls.Add(this.BTN_NPLAY);
            this.GROUP_PLAY_RECORD_FILE.Controls.Add(this.BTN_PLAY);
            this.GROUP_PLAY_RECORD_FILE.Controls.Add(this.BTN_STOP);
            this.GROUP_PLAY_RECORD_FILE.Controls.Add(this.BTN_REWARD);
            this.GROUP_PLAY_RECORD_FILE.Controls.Add(this.BTN_NREWARD);
            this.GROUP_PLAY_RECORD_FILE.Controls.Add(this.TRACKBAR_PLAY);
            this.GROUP_PLAY_RECORD_FILE.Controls.Add(this.LISTBOX_RECORD_FILE);
            this.GROUP_PLAY_RECORD_FILE.Location = new System.Drawing.Point(511, 521);
            this.GROUP_PLAY_RECORD_FILE.Name = "GROUP_PLAY_RECORD_FILE";
            this.GROUP_PLAY_RECORD_FILE.Size = new System.Drawing.Size(248, 234);
            this.GROUP_PLAY_RECORD_FILE.TabIndex = 7;
            this.GROUP_PLAY_RECORD_FILE.TabStop = false;
            this.GROUP_PLAY_RECORD_FILE.Text = "Play Record File";
            // 
            // STR_TIME
            // 
            this.STR_TIME.AutoSize = true;
            this.STR_TIME.Location = new System.Drawing.Point(188, 137);
            this.STR_TIME.Name = "STR_TIME";
            this.STR_TIME.Size = new System.Drawing.Size(49, 12);
            this.STR_TIME.TabIndex = 14;
            this.STR_TIME.Text = "00:00:00";
            // 
            // COMBO_SPEED
            // 
            this.COMBO_SPEED.FormattingEnabled = true;
            this.COMBO_SPEED.Location = new System.Drawing.Point(17, 202);
            this.COMBO_SPEED.Name = "COMBO_SPEED";
            this.COMBO_SPEED.Size = new System.Drawing.Size(220, 20);
            this.COMBO_SPEED.TabIndex = 13;
            this.COMBO_SPEED.SelectedIndexChanged += new System.EventHandler(this.COMBO_SPEED_SelectedIndexChanged);
            // 
            // BTN_NPLAY
            // 
            this.BTN_NPLAY.Location = new System.Drawing.Point(196, 169);
            this.BTN_NPLAY.Name = "BTN_NPLAY";
            this.BTN_NPLAY.Size = new System.Drawing.Size(41, 27);
            this.BTN_NPLAY.TabIndex = 12;
            this.BTN_NPLAY.Text = ">|";
            this.BTN_NPLAY.UseVisualStyleBackColor = true;
            this.BTN_NPLAY.Click += new System.EventHandler(this.BTN_NPLAY_Click);
            // 
            // BTN_PLAY
            // 
            this.BTN_PLAY.Location = new System.Drawing.Point(152, 169);
            this.BTN_PLAY.Name = "BTN_PLAY";
            this.BTN_PLAY.Size = new System.Drawing.Size(41, 27);
            this.BTN_PLAY.TabIndex = 12;
            this.BTN_PLAY.Text = ">";
            this.BTN_PLAY.UseVisualStyleBackColor = true;
            this.BTN_PLAY.Click += new System.EventHandler(this.BTN_PLAY_Click);
            // 
            // BTN_STOP
            // 
            this.BTN_STOP.Location = new System.Drawing.Point(107, 169);
            this.BTN_STOP.Name = "BTN_STOP";
            this.BTN_STOP.Size = new System.Drawing.Size(41, 27);
            this.BTN_STOP.TabIndex = 12;
            this.BTN_STOP.Text = "||";
            this.BTN_STOP.UseVisualStyleBackColor = true;
            this.BTN_STOP.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // BTN_REWARD
            // 
            this.BTN_REWARD.Location = new System.Drawing.Point(62, 169);
            this.BTN_REWARD.Name = "BTN_REWARD";
            this.BTN_REWARD.Size = new System.Drawing.Size(41, 27);
            this.BTN_REWARD.TabIndex = 12;
            this.BTN_REWARD.Text = "<";
            this.BTN_REWARD.UseVisualStyleBackColor = true;
            this.BTN_REWARD.Click += new System.EventHandler(this.BTN_REWARD_Click);
            // 
            // BTN_NREWARD
            // 
            this.BTN_NREWARD.Location = new System.Drawing.Point(17, 169);
            this.BTN_NREWARD.Name = "BTN_NREWARD";
            this.BTN_NREWARD.Size = new System.Drawing.Size(41, 27);
            this.BTN_NREWARD.TabIndex = 12;
            this.BTN_NREWARD.Text = "|<";
            this.BTN_NREWARD.UseVisualStyleBackColor = true;
            this.BTN_NREWARD.Click += new System.EventHandler(this.BTN_NREWARD_Click);
            // 
            // TRACKBAR_PLAY
            // 
            this.TRACKBAR_PLAY.Location = new System.Drawing.Point(9, 128);
            this.TRACKBAR_PLAY.Name = "TRACKBAR_PLAY";
            this.TRACKBAR_PLAY.Size = new System.Drawing.Size(181, 45);
            this.TRACKBAR_PLAY.TabIndex = 7;
            this.TRACKBAR_PLAY.MouseCaptureChanged += new System.EventHandler(this.TRACKBAR_PLAY_MouseCaptureChanged);
            // 
            // LIST_LOG
            // 
            this.LIST_LOG.FormattingEnabled = true;
            this.LIST_LOG.ItemHeight = 12;
            this.LIST_LOG.Location = new System.Drawing.Point(12, 406);
            this.LIST_LOG.Name = "LIST_LOG";
            this.LIST_LOG.Size = new System.Drawing.Size(483, 340);
            this.LIST_LOG.TabIndex = 8;
            // 
            // STR_STATUS_MESSAGE
            // 
            this.STR_STATUS_MESSAGE.AutoSize = true;
            this.STR_STATUS_MESSAGE.Location = new System.Drawing.Point(12, 391);
            this.STR_STATUS_MESSAGE.Name = "STR_STATUS_MESSAGE";
            this.STR_STATUS_MESSAGE.Size = new System.Drawing.Size(97, 12);
            this.STR_STATUS_MESSAGE.TabIndex = 9;
            this.STR_STATUS_MESSAGE.Text = "Status Message";
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(435, 381);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(60, 24);
            this.axXnsSdkDevice.TabIndex = 1;
            this.axXnsSdkDevice.Visible = false;
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            this.axXnsSdkDevice.OnSearchCalendar += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnSearchCalendarEventHandler(this.axXnsSdkDevice_OnSearchCalendar);
            this.axXnsSdkDevice.OnSearchDay += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnSearchDayEventHandler(this.axXnsSdkDevice_OnSearchDay);
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            // 
            // axXnsSdkWindow
            // 
            this.axXnsSdkWindow.Enabled = true;
            this.axXnsSdkWindow.Location = new System.Drawing.Point(12, 12);
            this.axXnsSdkWindow.Name = "axXnsSdkWindow";
            this.axXnsSdkWindow.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow.OcxState")));
            this.axXnsSdkWindow.Size = new System.Drawing.Size(483, 368);
            this.axXnsSdkWindow.TabIndex = 0;
            this.axXnsSdkWindow.OnFrameTimeChanged += new AxXNSSDKWINDOWLib._DXnsSdkWindowEvents_OnFrameTimeChangedEventHandler(this.axXnsSdkWindow_OnFrameTimeChanged);
            // 
            // EDIT_HTTPPORT
            // 
            this.EDIT_HTTPPORT.Location = new System.Drawing.Point(86, 132);
            this.EDIT_HTTPPORT.Name = "EDIT_HTTPPORT";
            this.EDIT_HTTPPORT.Size = new System.Drawing.Size(148, 21);
            this.EDIT_HTTPPORT.TabIndex = 14;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 135);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 12);
            this.label1.TabIndex = 13;
            this.label1.Text = "Http Port";
            // 
            // CHECKBOX_SUNAPI
            // 
            this.CHECKBOX_SUNAPI.Location = new System.Drawing.Point(86, 52);
            this.CHECKBOX_SUNAPI.Name = "CHECKBOX_SUNAPI";
            this.CHECKBOX_SUNAPI.Size = new System.Drawing.Size(78, 24);
            this.CHECKBOX_SUNAPI.TabIndex = 27;
            this.CHECKBOX_SUNAPI.Text = "SUNAPI";
            this.CHECKBOX_SUNAPI.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 57);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(63, 12);
            this.label4.TabIndex = 26;
            this.label4.Text = "Protocol   ";
            // 
            // PlayBackForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(770, 760);
            this.Controls.Add(this.STR_STATUS_MESSAGE);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.GROUP_PLAY_RECORD_FILE);
            this.Controls.Add(this.GROUP_RECORD_FILE);
            this.Controls.Add(this.GROUP_CONNECTION_INFO);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Controls.Add(this.axXnsSdkWindow);
            this.Name = "PlayBackForm";
            this.Text = "PlayBack";
            this.Load += new System.EventHandler(this.PlayBackForm_Load);
            this.GROUP_CONNECTION_INFO.ResumeLayout(false);
            this.GROUP_CONNECTION_INFO.PerformLayout();
            this.GROUP_RECORD_FILE.ResumeLayout(false);
            this.GROUP_PLAY_RECORD_FILE.ResumeLayout(false);
            this.GROUP_PLAY_RECORD_FILE.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TRACKBAR_PLAY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow;
        private AxXNSSDKDEVICELib.AxXnsSdkDevice axXnsSdkDevice;
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
        private System.Windows.Forms.Button BTN_CHECK_CALENDAR;
        private System.Windows.Forms.GroupBox GROUP_RECORD_FILE;
        private System.Windows.Forms.MonthCalendar MONTH_CALENDAR;
        private System.Windows.Forms.ListBox LISTBOX_RECORD_FILE;
        private System.Windows.Forms.GroupBox GROUP_PLAY_RECORD_FILE;
        private System.Windows.Forms.ListBox LIST_LOG;
        private System.Windows.Forms.Label STR_STATUS_MESSAGE;
        private System.Windows.Forms.TrackBar TRACKBAR_PLAY;
        private System.Windows.Forms.Button BTN_NREWARD;
        private System.Windows.Forms.Button BTN_PLAY;
        private System.Windows.Forms.Button BTN_STOP;
        private System.Windows.Forms.Button BTN_REWARD;
        private System.Windows.Forms.Button BTN_NPLAY;
        private System.Windows.Forms.ComboBox COMBO_SPEED;
        private System.Windows.Forms.Label STR_TIME;
        private System.Windows.Forms.TextBox EDIT_HTTPPORT;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox CHECKBOX_SUNAPI;
        private System.Windows.Forms.Label label4;
    }
}

