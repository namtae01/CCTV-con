namespace Event
{
    partial class EventForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EventForm));
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.axXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.GROUP_CONNECTION_INFO = new System.Windows.Forms.GroupBox();
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
            this.LIST_LOG = new System.Windows.Forms.ListBox();
            this.STR_ACTIVEX_CONTROL_LOG = new System.Windows.Forms.Label();
            this.TAB_ALARM_EVENT = new System.Windows.Forms.TabControl();
            this.TABPAGE_ALARM = new System.Windows.Forms.TabPage();
            this.LIST_ALARM = new System.Windows.Forms.ListBox();
            this.TABPAGE_MOTION = new System.Windows.Forms.TabPage();
            this.LIST_MOTION = new System.Windows.Forms.ListBox();
            this.TABPAGE_INTELIGENT_VIDEO = new System.Windows.Forms.TabPage();
            this.LIST_INTELIGENT_VIDEO = new System.Windows.Forms.ListBox();
            this.TABPAGE_VIDEO_LOSS = new System.Windows.Forms.TabPage();
            this.LIST_VIDEO_LOSS = new System.Windows.Forms.ListBox();
            this.TABPAGE_SYSTEM_LOG = new System.Windows.Forms.TabPage();
            this.LIST_SYSTEM_LOG = new System.Windows.Forms.ListBox();
            this.TABPAGE_DEVICE_LOG = new System.Windows.Forms.TabPage();
            this.LIST_DEVICE_LOG = new System.Windows.Forms.ListBox();
            this.TABPAGE_ALL = new System.Windows.Forms.TabPage();
            this.LIST_ALL = new System.Windows.Forms.ListBox();
            this.CHECKBOX_ALARM_BEEP_ON = new System.Windows.Forms.CheckBox();
            this.BTN_EVENT_LOG_CLEAR = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).BeginInit();
            this.GROUP_CONNECTION_INFO.SuspendLayout();
            this.TAB_ALARM_EVENT.SuspendLayout();
            this.TABPAGE_ALARM.SuspendLayout();
            this.TABPAGE_MOTION.SuspendLayout();
            this.TABPAGE_INTELIGENT_VIDEO.SuspendLayout();
            this.TABPAGE_VIDEO_LOSS.SuspendLayout();
            this.TABPAGE_SYSTEM_LOG.SuspendLayout();
            this.TABPAGE_DEVICE_LOG.SuspendLayout();
            this.TABPAGE_ALL.SuspendLayout();
            this.SuspendLayout();
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(409, 247);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(29, 20);
            this.axXnsSdkDevice.TabIndex = 0;
            this.axXnsSdkDevice.Visible = false;
            this.axXnsSdkDevice.OnIvOccurEvent += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnIvOccurEventEventHandler(this.axXnsSdkDevice_OnIvOccurEvent);
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            this.axXnsSdkDevice.OnControlStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnControlStatusChangedEventHandler(this.axXnsSdkDevice_OnControlStatusChanged);
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            this.axXnsSdkDevice.OnAlarmOutControlFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnAlarmOutControlFailedEventHandler(this.axXnsSdkDevice_OnAlarmOutControlFailed);
            this.axXnsSdkDevice.OnMotionEvent += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnMotionEventEventHandler(this.axXnsSdkDevice_OnMotionEvent);
            this.axXnsSdkDevice.OnControlLocalNameChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnControlLocalNameChangedEventHandler(this.axXnsSdkDevice_OnControlLocalNameChanged);
            this.axXnsSdkDevice.OnSensorEvent += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnSensorEventEventHandler(this.axXnsSdkDevice_OnSensorEvent);
            this.axXnsSdkDevice.OnPasswordChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnPasswordChangedEventHandler(this.axXnsSdkDevice_OnPasswordChanged);
            this.axXnsSdkDevice.OnVideoLossEvent += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnVideoLossEventEventHandler(this.axXnsSdkDevice_OnVideoLossEvent);
            this.axXnsSdkDevice.OnControlRemoteNameChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnControlRemoteNameChangedEventHandler(this.axXnsSdkDevice_OnControlRemoteNameChanged);
            // 
            // axXnsSdkWindow
            // 
            this.axXnsSdkWindow.Enabled = true;
            this.axXnsSdkWindow.Location = new System.Drawing.Point(17, 13);
            this.axXnsSdkWindow.Name = "axXnsSdkWindow";
            this.axXnsSdkWindow.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow.OcxState")));
            this.axXnsSdkWindow.Size = new System.Drawing.Size(377, 236);
            this.axXnsSdkWindow.TabIndex = 1;
            // 
            // GROUP_CONNECTION_INFO
            // 
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
            this.GROUP_CONNECTION_INFO.Location = new System.Drawing.Point(409, 13);
            this.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO";
            this.GROUP_CONNECTION_INFO.Size = new System.Drawing.Size(248, 236);
            this.GROUP_CONNECTION_INFO.TabIndex = 4;
            this.GROUP_CONNECTION_INFO.TabStop = false;
            this.GROUP_CONNECTION_INFO.Text = "Connection Information";
            // 
            // BTN_PLAY
            // 
            this.BTN_PLAY.Location = new System.Drawing.Point(14, 203);
            this.BTN_PLAY.Name = "BTN_PLAY";
            this.BTN_PLAY.Size = new System.Drawing.Size(106, 25);
            this.BTN_PLAY.TabIndex = 11;
            this.BTN_PLAY.Text = "Play";
            this.BTN_PLAY.UseVisualStyleBackColor = true;
            this.BTN_PLAY.Click += new System.EventHandler(this.BTN_PLAY_Click);
            // 
            // BTN_STOP
            // 
            this.BTN_STOP.Location = new System.Drawing.Point(128, 203);
            this.BTN_STOP.Name = "BTN_STOP";
            this.BTN_STOP.Size = new System.Drawing.Size(106, 25);
            this.BTN_STOP.TabIndex = 11;
            this.BTN_STOP.Text = "Stop";
            this.BTN_STOP.UseVisualStyleBackColor = true;
            this.BTN_STOP.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // BTN_DISCONNECT
            // 
            this.BTN_DISCONNECT.Location = new System.Drawing.Point(128, 172);
            this.BTN_DISCONNECT.Name = "BTN_DISCONNECT";
            this.BTN_DISCONNECT.Size = new System.Drawing.Size(106, 25);
            this.BTN_DISCONNECT.TabIndex = 11;
            this.BTN_DISCONNECT.Text = "Disconnect";
            this.BTN_DISCONNECT.UseVisualStyleBackColor = true;
            this.BTN_DISCONNECT.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // BTN_CONNECT
            // 
            this.BTN_CONNECT.Location = new System.Drawing.Point(14, 172);
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
            this.COMBO_MODELLIST.Size = new System.Drawing.Size(148, 20);
            this.COMBO_MODELLIST.TabIndex = 10;
            // 
            // EDIT_PW
            // 
            this.EDIT_PW.Location = new System.Drawing.Point(86, 137);
            this.EDIT_PW.Name = "EDIT_PW";
            this.EDIT_PW.Size = new System.Drawing.Size(148, 21);
            this.EDIT_PW.TabIndex = 9;
            this.EDIT_PW.UseSystemPasswordChar = true;
            // 
            // EDIT_ID
            // 
            this.EDIT_ID.Location = new System.Drawing.Point(86, 110);
            this.EDIT_ID.Name = "EDIT_ID";
            this.EDIT_ID.Size = new System.Drawing.Size(148, 21);
            this.EDIT_ID.TabIndex = 8;
            // 
            // EDIT_PORT
            // 
            this.EDIT_PORT.Location = new System.Drawing.Point(86, 83);
            this.EDIT_PORT.Name = "EDIT_PORT";
            this.EDIT_PORT.Size = new System.Drawing.Size(148, 21);
            this.EDIT_PORT.TabIndex = 7;
            // 
            // EDIT_IP
            // 
            this.EDIT_IP.Location = new System.Drawing.Point(86, 56);
            this.EDIT_IP.Name = "EDIT_IP";
            this.EDIT_IP.Size = new System.Drawing.Size(148, 21);
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
            // STR_IPADDRESS
            // 
            this.STR_IPADDRESS.AutoSize = true;
            this.STR_IPADDRESS.Location = new System.Drawing.Point(12, 59);
            this.STR_IPADDRESS.Name = "STR_IPADDRESS";
            this.STR_IPADDRESS.Size = new System.Drawing.Size(68, 12);
            this.STR_IPADDRESS.TabIndex = 1;
            this.STR_IPADDRESS.Text = "IP           : ";
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
            // LIST_LOG
            // 
            this.LIST_LOG.FormattingEnabled = true;
            this.LIST_LOG.ItemHeight = 12;
            this.LIST_LOG.Location = new System.Drawing.Point(17, 270);
            this.LIST_LOG.Name = "LIST_LOG";
            this.LIST_LOG.Size = new System.Drawing.Size(640, 88);
            this.LIST_LOG.TabIndex = 5;
            // 
            // STR_ACTIVEX_CONTROL_LOG
            // 
            this.STR_ACTIVEX_CONTROL_LOG.AutoSize = true;
            this.STR_ACTIVEX_CONTROL_LOG.Location = new System.Drawing.Point(15, 255);
            this.STR_ACTIVEX_CONTROL_LOG.Name = "STR_ACTIVEX_CONTROL_LOG";
            this.STR_ACTIVEX_CONTROL_LOG.Size = new System.Drawing.Size(116, 12);
            this.STR_ACTIVEX_CONTROL_LOG.TabIndex = 10;
            this.STR_ACTIVEX_CONTROL_LOG.Text = "ActiveX Control Log";
            // 
            // TAB_ALARM_EVENT
            // 
            this.TAB_ALARM_EVENT.Controls.Add(this.TABPAGE_ALARM);
            this.TAB_ALARM_EVENT.Controls.Add(this.TABPAGE_MOTION);
            this.TAB_ALARM_EVENT.Controls.Add(this.TABPAGE_INTELIGENT_VIDEO);
            this.TAB_ALARM_EVENT.Controls.Add(this.TABPAGE_VIDEO_LOSS);
            this.TAB_ALARM_EVENT.Controls.Add(this.TABPAGE_SYSTEM_LOG);
            this.TAB_ALARM_EVENT.Controls.Add(this.TABPAGE_DEVICE_LOG);
            this.TAB_ALARM_EVENT.Controls.Add(this.TABPAGE_ALL);
            this.TAB_ALARM_EVENT.Location = new System.Drawing.Point(17, 369);
            this.TAB_ALARM_EVENT.Name = "TAB_ALARM_EVENT";
            this.TAB_ALARM_EVENT.SelectedIndex = 0;
            this.TAB_ALARM_EVENT.Size = new System.Drawing.Size(640, 303);
            this.TAB_ALARM_EVENT.TabIndex = 11;
            // 
            // TABPAGE_ALARM
            // 
            this.TABPAGE_ALARM.Controls.Add(this.LIST_ALARM);
            this.TABPAGE_ALARM.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_ALARM.Name = "TABPAGE_ALARM";
            this.TABPAGE_ALARM.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_ALARM.Size = new System.Drawing.Size(632, 277);
            this.TABPAGE_ALARM.TabIndex = 0;
            this.TABPAGE_ALARM.Text = "Alarm";
            this.TABPAGE_ALARM.UseVisualStyleBackColor = true;
            // 
            // LIST_ALARM
            // 
            this.LIST_ALARM.FormattingEnabled = true;
            this.LIST_ALARM.ItemHeight = 12;
            this.LIST_ALARM.Location = new System.Drawing.Point(-4, -2);
            this.LIST_ALARM.Name = "LIST_ALARM";
            this.LIST_ALARM.Size = new System.Drawing.Size(640, 280);
            this.LIST_ALARM.TabIndex = 0;
            // 
            // TABPAGE_MOTION
            // 
            this.TABPAGE_MOTION.Controls.Add(this.LIST_MOTION);
            this.TABPAGE_MOTION.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_MOTION.Name = "TABPAGE_MOTION";
            this.TABPAGE_MOTION.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_MOTION.Size = new System.Drawing.Size(632, 277);
            this.TABPAGE_MOTION.TabIndex = 1;
            this.TABPAGE_MOTION.Text = "Motion";
            this.TABPAGE_MOTION.UseVisualStyleBackColor = true;
            // 
            // LIST_MOTION
            // 
            this.LIST_MOTION.FormattingEnabled = true;
            this.LIST_MOTION.ItemHeight = 12;
            this.LIST_MOTION.Location = new System.Drawing.Point(-4, -2);
            this.LIST_MOTION.Name = "LIST_MOTION";
            this.LIST_MOTION.Size = new System.Drawing.Size(640, 280);
            this.LIST_MOTION.TabIndex = 13;
            // 
            // TABPAGE_INTELIGENT_VIDEO
            // 
            this.TABPAGE_INTELIGENT_VIDEO.Controls.Add(this.LIST_INTELIGENT_VIDEO);
            this.TABPAGE_INTELIGENT_VIDEO.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_INTELIGENT_VIDEO.Name = "TABPAGE_INTELIGENT_VIDEO";
            this.TABPAGE_INTELIGENT_VIDEO.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_INTELIGENT_VIDEO.Size = new System.Drawing.Size(632, 277);
            this.TABPAGE_INTELIGENT_VIDEO.TabIndex = 2;
            this.TABPAGE_INTELIGENT_VIDEO.Text = "Inteligent Video";
            this.TABPAGE_INTELIGENT_VIDEO.UseVisualStyleBackColor = true;
            // 
            // LIST_INTELIGENT_VIDEO
            // 
            this.LIST_INTELIGENT_VIDEO.FormattingEnabled = true;
            this.LIST_INTELIGENT_VIDEO.ItemHeight = 12;
            this.LIST_INTELIGENT_VIDEO.Location = new System.Drawing.Point(-4, -2);
            this.LIST_INTELIGENT_VIDEO.Name = "LIST_INTELIGENT_VIDEO";
            this.LIST_INTELIGENT_VIDEO.Size = new System.Drawing.Size(640, 280);
            this.LIST_INTELIGENT_VIDEO.TabIndex = 13;
            // 
            // TABPAGE_VIDEO_LOSS
            // 
            this.TABPAGE_VIDEO_LOSS.Controls.Add(this.LIST_VIDEO_LOSS);
            this.TABPAGE_VIDEO_LOSS.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_VIDEO_LOSS.Name = "TABPAGE_VIDEO_LOSS";
            this.TABPAGE_VIDEO_LOSS.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_VIDEO_LOSS.Size = new System.Drawing.Size(632, 277);
            this.TABPAGE_VIDEO_LOSS.TabIndex = 3;
            this.TABPAGE_VIDEO_LOSS.Text = "Video Loss";
            this.TABPAGE_VIDEO_LOSS.UseVisualStyleBackColor = true;
            // 
            // LIST_VIDEO_LOSS
            // 
            this.LIST_VIDEO_LOSS.FormattingEnabled = true;
            this.LIST_VIDEO_LOSS.ItemHeight = 12;
            this.LIST_VIDEO_LOSS.Location = new System.Drawing.Point(-4, -2);
            this.LIST_VIDEO_LOSS.Name = "LIST_VIDEO_LOSS";
            this.LIST_VIDEO_LOSS.Size = new System.Drawing.Size(637, 280);
            this.LIST_VIDEO_LOSS.TabIndex = 14;
            // 
            // TABPAGE_SYSTEM_LOG
            // 
            this.TABPAGE_SYSTEM_LOG.Controls.Add(this.LIST_SYSTEM_LOG);
            this.TABPAGE_SYSTEM_LOG.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_SYSTEM_LOG.Name = "TABPAGE_SYSTEM_LOG";
            this.TABPAGE_SYSTEM_LOG.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_SYSTEM_LOG.Size = new System.Drawing.Size(632, 277);
            this.TABPAGE_SYSTEM_LOG.TabIndex = 4;
            this.TABPAGE_SYSTEM_LOG.Text = "System Log";
            this.TABPAGE_SYSTEM_LOG.UseVisualStyleBackColor = true;
            // 
            // LIST_SYSTEM_LOG
            // 
            this.LIST_SYSTEM_LOG.FormattingEnabled = true;
            this.LIST_SYSTEM_LOG.ItemHeight = 12;
            this.LIST_SYSTEM_LOG.Location = new System.Drawing.Point(-4, -2);
            this.LIST_SYSTEM_LOG.Name = "LIST_SYSTEM_LOG";
            this.LIST_SYSTEM_LOG.Size = new System.Drawing.Size(637, 280);
            this.LIST_SYSTEM_LOG.TabIndex = 14;
            // 
            // TABPAGE_DEVICE_LOG
            // 
            this.TABPAGE_DEVICE_LOG.Controls.Add(this.LIST_DEVICE_LOG);
            this.TABPAGE_DEVICE_LOG.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_DEVICE_LOG.Name = "TABPAGE_DEVICE_LOG";
            this.TABPAGE_DEVICE_LOG.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_DEVICE_LOG.Size = new System.Drawing.Size(632, 277);
            this.TABPAGE_DEVICE_LOG.TabIndex = 5;
            this.TABPAGE_DEVICE_LOG.Text = "Device Log";
            this.TABPAGE_DEVICE_LOG.UseVisualStyleBackColor = true;
            // 
            // LIST_DEVICE_LOG
            // 
            this.LIST_DEVICE_LOG.FormattingEnabled = true;
            this.LIST_DEVICE_LOG.ItemHeight = 12;
            this.LIST_DEVICE_LOG.Location = new System.Drawing.Point(-4, -2);
            this.LIST_DEVICE_LOG.Name = "LIST_DEVICE_LOG";
            this.LIST_DEVICE_LOG.Size = new System.Drawing.Size(637, 280);
            this.LIST_DEVICE_LOG.TabIndex = 14;
            // 
            // TABPAGE_ALL
            // 
            this.TABPAGE_ALL.Controls.Add(this.LIST_ALL);
            this.TABPAGE_ALL.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_ALL.Name = "TABPAGE_ALL";
            this.TABPAGE_ALL.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_ALL.Size = new System.Drawing.Size(632, 277);
            this.TABPAGE_ALL.TabIndex = 6;
            this.TABPAGE_ALL.Text = "All";
            this.TABPAGE_ALL.UseVisualStyleBackColor = true;
            // 
            // LIST_ALL
            // 
            this.LIST_ALL.FormattingEnabled = true;
            this.LIST_ALL.ItemHeight = 12;
            this.LIST_ALL.Location = new System.Drawing.Point(-4, -2);
            this.LIST_ALL.Name = "LIST_ALL";
            this.LIST_ALL.Size = new System.Drawing.Size(640, 280);
            this.LIST_ALL.TabIndex = 14;
            // 
            // CHECKBOX_ALARM_BEEP_ON
            // 
            this.CHECKBOX_ALARM_BEEP_ON.AutoSize = true;
            this.CHECKBOX_ALARM_BEEP_ON.Location = new System.Drawing.Point(496, 367);
            this.CHECKBOX_ALARM_BEEP_ON.Name = "CHECKBOX_ALARM_BEEP_ON";
            this.CHECKBOX_ALARM_BEEP_ON.Size = new System.Drawing.Size(106, 16);
            this.CHECKBOX_ALARM_BEEP_ON.TabIndex = 12;
            this.CHECKBOX_ALARM_BEEP_ON.Text = "Alarm Beef On";
            this.CHECKBOX_ALARM_BEEP_ON.UseVisualStyleBackColor = true;
            this.CHECKBOX_ALARM_BEEP_ON.CheckedChanged += new System.EventHandler(this.CHECKBOX_ALARM_BEEP_ON_CheckedChanged);
            // 
            // BTN_EVENT_LOG_CLEAR
            // 
            this.BTN_EVENT_LOG_CLEAR.Location = new System.Drawing.Point(608, 363);
            this.BTN_EVENT_LOG_CLEAR.Name = "BTN_EVENT_LOG_CLEAR";
            this.BTN_EVENT_LOG_CLEAR.Size = new System.Drawing.Size(46, 22);
            this.BTN_EVENT_LOG_CLEAR.TabIndex = 13;
            this.BTN_EVENT_LOG_CLEAR.Text = "Clear";
            this.BTN_EVENT_LOG_CLEAR.UseVisualStyleBackColor = true;
            this.BTN_EVENT_LOG_CLEAR.Click += new System.EventHandler(this.BTN_EVENT_LOG_CLEAR_Click);
            // 
            // EventForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(673, 682);
            this.Controls.Add(this.BTN_EVENT_LOG_CLEAR);
            this.Controls.Add(this.CHECKBOX_ALARM_BEEP_ON);
            this.Controls.Add(this.TAB_ALARM_EVENT);
            this.Controls.Add(this.STR_ACTIVEX_CONTROL_LOG);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.GROUP_CONNECTION_INFO);
            this.Controls.Add(this.axXnsSdkWindow);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Name = "EventForm";
            this.Text = "Event";
            this.Load += new System.EventHandler(this.EventForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).EndInit();
            this.GROUP_CONNECTION_INFO.ResumeLayout(false);
            this.GROUP_CONNECTION_INFO.PerformLayout();
            this.TAB_ALARM_EVENT.ResumeLayout(false);
            this.TABPAGE_ALARM.ResumeLayout(false);
            this.TABPAGE_MOTION.ResumeLayout(false);
            this.TABPAGE_INTELIGENT_VIDEO.ResumeLayout(false);
            this.TABPAGE_VIDEO_LOSS.ResumeLayout(false);
            this.TABPAGE_SYSTEM_LOG.ResumeLayout(false);
            this.TABPAGE_DEVICE_LOG.ResumeLayout(false);
            this.TABPAGE_ALL.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxXNSSDKDEVICELib.AxXnsSdkDevice axXnsSdkDevice;
        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow;
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
        private System.Windows.Forms.ListBox LIST_LOG;
        private System.Windows.Forms.Label STR_ACTIVEX_CONTROL_LOG;
        private System.Windows.Forms.TabControl TAB_ALARM_EVENT;
        private System.Windows.Forms.TabPage TABPAGE_ALARM;
        private System.Windows.Forms.TabPage TABPAGE_MOTION;
        private System.Windows.Forms.CheckBox CHECKBOX_ALARM_BEEP_ON;
        private System.Windows.Forms.TabPage TABPAGE_INTELIGENT_VIDEO;
        private System.Windows.Forms.TabPage TABPAGE_VIDEO_LOSS;
        private System.Windows.Forms.TabPage TABPAGE_SYSTEM_LOG;
        private System.Windows.Forms.TabPage TABPAGE_DEVICE_LOG;
        private System.Windows.Forms.TabPage TABPAGE_ALL;
        private System.Windows.Forms.ListBox LIST_ALARM;
        private System.Windows.Forms.ListBox LIST_MOTION;
        private System.Windows.Forms.ListBox LIST_INTELIGENT_VIDEO;
        private System.Windows.Forms.ListBox LIST_VIDEO_LOSS;
        private System.Windows.Forms.ListBox LIST_SYSTEM_LOG;
        private System.Windows.Forms.ListBox LIST_DEVICE_LOG;
        private System.Windows.Forms.ListBox LIST_ALL;
        private System.Windows.Forms.Button BTN_EVENT_LOG_CLEAR;
    }
}

