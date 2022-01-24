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
            this.GROUP_CONNECTION_INFO = new System.Windows.Forms.GroupBox();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.STR_PROTOCOL = new System.Windows.Forms.Label();
            this.BTN_PLAY = new System.Windows.Forms.Button();
            this.BTN_STOP = new System.Windows.Forms.Button();
            this.BTN_DISCONNECT = new System.Windows.Forms.Button();
            this.BTN_CONNECT = new System.Windows.Forms.Button();
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.CHECKBOX_SUNAPI = new System.Windows.Forms.CheckBox();
            this.EDIT_PW = new System.Windows.Forms.TextBox();
            this.EDIT_ID = new System.Windows.Forms.TextBox();
            this.EDIT_IP = new System.Windows.Forms.TextBox();
            this.COMBO_MODELLIST = new System.Windows.Forms.ComboBox();
            this.EDIT_HTTPPORT = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.EDIT_PORT = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.axXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.GROUP_CONNECTION_INFO.SuspendLayout();
            this.TAB_ALARM_EVENT.SuspendLayout();
            this.TABPAGE_ALARM.SuspendLayout();
            this.TABPAGE_MOTION.SuspendLayout();
            this.TABPAGE_INTELIGENT_VIDEO.SuspendLayout();
            this.TABPAGE_VIDEO_LOSS.SuspendLayout();
            this.TABPAGE_SYSTEM_LOG.SuspendLayout();
            this.TABPAGE_DEVICE_LOG.SuspendLayout();
            this.TABPAGE_ALL.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).BeginInit();
            this.SuspendLayout();
            // 
            // GROUP_CONNECTION_INFO
            // 
            this.GROUP_CONNECTION_INFO.Controls.Add(this.comboBox2);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.comboBox1);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_PROTOCOL);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_PLAY);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_STOP);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_DISCONNECT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_CONNECT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_PW);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_ID);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_PORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_IPADDRESS);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_MODEL);
            this.GROUP_CONNECTION_INFO.Location = new System.Drawing.Point(409, 13);
            this.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO";
            this.GROUP_CONNECTION_INFO.Size = new System.Drawing.Size(302, 274);
            this.GROUP_CONNECTION_INFO.TabIndex = 4;
            this.GROUP_CONNECTION_INFO.TabStop = false;
            this.GROUP_CONNECTION_INFO.Text = "Connection Information";
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Location = new System.Drawing.Point(198, 55);
            this.comboBox2.MaxDropDownItems = 15;
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(98, 20);
            this.comboBox2.TabIndex = 14;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(86, 55);
            this.comboBox1.MaxDropDownItems = 15;
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(98, 20);
            this.comboBox1.TabIndex = 13;
            // 
            // STR_PROTOCOL
            // 
            this.STR_PROTOCOL.AutoSize = true;
            this.STR_PROTOCOL.Location = new System.Drawing.Point(12, 58);
            this.STR_PROTOCOL.Name = "STR_PROTOCOL";
            this.STR_PROTOCOL.Size = new System.Drawing.Size(68, 12);
            this.STR_PROTOCOL.TabIndex = 12;
            this.STR_PROTOCOL.Text = "Model     : ";
            // 
            // BTN_PLAY
            // 
            this.BTN_PLAY.Location = new System.Drawing.Point(22, 242);
            this.BTN_PLAY.Name = "BTN_PLAY";
            this.BTN_PLAY.Size = new System.Drawing.Size(132, 25);
            this.BTN_PLAY.TabIndex = 11;
            this.BTN_PLAY.Text = "Play";
            this.BTN_PLAY.UseVisualStyleBackColor = true;
            this.BTN_PLAY.Click += new System.EventHandler(this.BTN_PLAY_Click);
            // 
            // BTN_STOP
            // 
            this.BTN_STOP.Location = new System.Drawing.Point(164, 242);
            this.BTN_STOP.Name = "BTN_STOP";
            this.BTN_STOP.Size = new System.Drawing.Size(132, 25);
            this.BTN_STOP.TabIndex = 11;
            this.BTN_STOP.Text = "Stop";
            this.BTN_STOP.UseVisualStyleBackColor = true;
            this.BTN_STOP.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // BTN_DISCONNECT
            // 
            this.BTN_DISCONNECT.Location = new System.Drawing.Point(164, 211);
            this.BTN_DISCONNECT.Name = "BTN_DISCONNECT";
            this.BTN_DISCONNECT.Size = new System.Drawing.Size(132, 25);
            this.BTN_DISCONNECT.TabIndex = 11;
            this.BTN_DISCONNECT.Text = "Disconnect";
            this.BTN_DISCONNECT.UseVisualStyleBackColor = true;
            this.BTN_DISCONNECT.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // BTN_CONNECT
            // 
            this.BTN_CONNECT.Location = new System.Drawing.Point(22, 211);
            this.BTN_CONNECT.Name = "BTN_CONNECT";
            this.BTN_CONNECT.Size = new System.Drawing.Size(132, 25);
            this.BTN_CONNECT.TabIndex = 11;
            this.BTN_CONNECT.Text = "Connect";
            this.BTN_CONNECT.UseVisualStyleBackColor = true;
            this.BTN_CONNECT.Click += new System.EventHandler(this.BTN_CONNECT_Click);
            // 
            // STR_PW
            // 
            this.STR_PW.AutoSize = true;
            this.STR_PW.Location = new System.Drawing.Point(13, 172);
            this.STR_PW.Name = "STR_PW";
            this.STR_PW.Size = new System.Drawing.Size(67, 12);
            this.STR_PW.TabIndex = 4;
            this.STR_PW.Text = "PW         : ";
            // 
            // STR_ID
            // 
            this.STR_ID.AutoSize = true;
            this.STR_ID.Location = new System.Drawing.Point(12, 139);
            this.STR_ID.Name = "STR_ID";
            this.STR_ID.Size = new System.Drawing.Size(68, 12);
            this.STR_ID.TabIndex = 3;
            this.STR_ID.Text = "ID           : ";
            // 
            // STR_PORT
            // 
            this.STR_PORT.AutoSize = true;
            this.STR_PORT.Location = new System.Drawing.Point(12, 111);
            this.STR_PORT.Name = "STR_PORT";
            this.STR_PORT.Size = new System.Drawing.Size(68, 12);
            this.STR_PORT.TabIndex = 2;
            this.STR_PORT.Text = "VNP Port : ";
            // 
            // STR_IPADDRESS
            // 
            this.STR_IPADDRESS.AutoSize = true;
            this.STR_IPADDRESS.Location = new System.Drawing.Point(12, 84);
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
            this.LIST_LOG.Location = new System.Drawing.Point(17, 316);
            this.LIST_LOG.Name = "LIST_LOG";
            this.LIST_LOG.Size = new System.Drawing.Size(694, 88);
            this.LIST_LOG.TabIndex = 5;
            // 
            // STR_ACTIVEX_CONTROL_LOG
            // 
            this.STR_ACTIVEX_CONTROL_LOG.AutoSize = true;
            this.STR_ACTIVEX_CONTROL_LOG.Location = new System.Drawing.Point(15, 301);
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
            this.TAB_ALARM_EVENT.Location = new System.Drawing.Point(17, 415);
            this.TAB_ALARM_EVENT.Name = "TAB_ALARM_EVENT";
            this.TAB_ALARM_EVENT.SelectedIndex = 0;
            this.TAB_ALARM_EVENT.Size = new System.Drawing.Size(694, 303);
            this.TAB_ALARM_EVENT.TabIndex = 11;
            // 
            // TABPAGE_ALARM
            // 
            this.TABPAGE_ALARM.Controls.Add(this.LIST_ALARM);
            this.TABPAGE_ALARM.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_ALARM.Name = "TABPAGE_ALARM";
            this.TABPAGE_ALARM.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_ALARM.Size = new System.Drawing.Size(686, 277);
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
            this.LIST_ALARM.Size = new System.Drawing.Size(694, 280);
            this.LIST_ALARM.TabIndex = 0;
            // 
            // TABPAGE_MOTION
            // 
            this.TABPAGE_MOTION.Controls.Add(this.LIST_MOTION);
            this.TABPAGE_MOTION.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_MOTION.Name = "TABPAGE_MOTION";
            this.TABPAGE_MOTION.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_MOTION.Size = new System.Drawing.Size(686, 277);
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
            this.LIST_MOTION.Size = new System.Drawing.Size(690, 280);
            this.LIST_MOTION.TabIndex = 13;
            // 
            // TABPAGE_INTELIGENT_VIDEO
            // 
            this.TABPAGE_INTELIGENT_VIDEO.Controls.Add(this.LIST_INTELIGENT_VIDEO);
            this.TABPAGE_INTELIGENT_VIDEO.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_INTELIGENT_VIDEO.Name = "TABPAGE_INTELIGENT_VIDEO";
            this.TABPAGE_INTELIGENT_VIDEO.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_INTELIGENT_VIDEO.Size = new System.Drawing.Size(686, 277);
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
            this.LIST_INTELIGENT_VIDEO.Size = new System.Drawing.Size(694, 280);
            this.LIST_INTELIGENT_VIDEO.TabIndex = 13;
            // 
            // TABPAGE_VIDEO_LOSS
            // 
            this.TABPAGE_VIDEO_LOSS.Controls.Add(this.LIST_VIDEO_LOSS);
            this.TABPAGE_VIDEO_LOSS.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_VIDEO_LOSS.Name = "TABPAGE_VIDEO_LOSS";
            this.TABPAGE_VIDEO_LOSS.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_VIDEO_LOSS.Size = new System.Drawing.Size(686, 277);
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
            this.LIST_VIDEO_LOSS.Size = new System.Drawing.Size(694, 280);
            this.LIST_VIDEO_LOSS.TabIndex = 14;
            // 
            // TABPAGE_SYSTEM_LOG
            // 
            this.TABPAGE_SYSTEM_LOG.Controls.Add(this.LIST_SYSTEM_LOG);
            this.TABPAGE_SYSTEM_LOG.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_SYSTEM_LOG.Name = "TABPAGE_SYSTEM_LOG";
            this.TABPAGE_SYSTEM_LOG.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_SYSTEM_LOG.Size = new System.Drawing.Size(686, 277);
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
            this.LIST_SYSTEM_LOG.Size = new System.Drawing.Size(694, 280);
            this.LIST_SYSTEM_LOG.TabIndex = 14;
            // 
            // TABPAGE_DEVICE_LOG
            // 
            this.TABPAGE_DEVICE_LOG.Controls.Add(this.LIST_DEVICE_LOG);
            this.TABPAGE_DEVICE_LOG.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_DEVICE_LOG.Name = "TABPAGE_DEVICE_LOG";
            this.TABPAGE_DEVICE_LOG.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_DEVICE_LOG.Size = new System.Drawing.Size(686, 277);
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
            this.LIST_DEVICE_LOG.Size = new System.Drawing.Size(694, 280);
            this.LIST_DEVICE_LOG.TabIndex = 14;
            // 
            // TABPAGE_ALL
            // 
            this.TABPAGE_ALL.Controls.Add(this.LIST_ALL);
            this.TABPAGE_ALL.Location = new System.Drawing.Point(4, 22);
            this.TABPAGE_ALL.Name = "TABPAGE_ALL";
            this.TABPAGE_ALL.Padding = new System.Windows.Forms.Padding(3);
            this.TABPAGE_ALL.Size = new System.Drawing.Size(686, 277);
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
            this.LIST_ALL.Size = new System.Drawing.Size(694, 280);
            this.LIST_ALL.TabIndex = 14;
            // 
            // CHECKBOX_ALARM_BEEP_ON
            // 
            this.CHECKBOX_ALARM_BEEP_ON.AutoSize = true;
            this.CHECKBOX_ALARM_BEEP_ON.Location = new System.Drawing.Point(496, 413);
            this.CHECKBOX_ALARM_BEEP_ON.Name = "CHECKBOX_ALARM_BEEP_ON";
            this.CHECKBOX_ALARM_BEEP_ON.Size = new System.Drawing.Size(106, 16);
            this.CHECKBOX_ALARM_BEEP_ON.TabIndex = 12;
            this.CHECKBOX_ALARM_BEEP_ON.Text = "Alarm Beef On";
            this.CHECKBOX_ALARM_BEEP_ON.UseVisualStyleBackColor = true;
            this.CHECKBOX_ALARM_BEEP_ON.CheckedChanged += new System.EventHandler(this.CHECKBOX_ALARM_BEEP_ON_CheckedChanged);
            // 
            // BTN_EVENT_LOG_CLEAR
            // 
            this.BTN_EVENT_LOG_CLEAR.Location = new System.Drawing.Point(608, 409);
            this.BTN_EVENT_LOG_CLEAR.Name = "BTN_EVENT_LOG_CLEAR";
            this.BTN_EVENT_LOG_CLEAR.Size = new System.Drawing.Size(46, 22);
            this.BTN_EVENT_LOG_CLEAR.TabIndex = 13;
            this.BTN_EVENT_LOG_CLEAR.Text = "Clear";
            this.BTN_EVENT_LOG_CLEAR.UseVisualStyleBackColor = true;
            this.BTN_EVENT_LOG_CLEAR.Click += new System.EventHandler(this.BTN_EVENT_LOG_CLEAR_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.CHECKBOX_SUNAPI);
            this.groupBox1.Controls.Add(this.EDIT_PW);
            this.groupBox1.Controls.Add(this.EDIT_ID);
            this.groupBox1.Controls.Add(this.EDIT_IP);
            this.groupBox1.Controls.Add(this.COMBO_MODELLIST);
            this.groupBox1.Controls.Add(this.EDIT_HTTPPORT);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.button2);
            this.groupBox1.Controls.Add(this.button3);
            this.groupBox1.Controls.Add(this.button4);
            this.groupBox1.Controls.Add(this.EDIT_PORT);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Location = new System.Drawing.Point(409, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(302, 286);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Connection Information";
            // 
            // CHECKBOX_SUNAPI
            // 
            this.CHECKBOX_SUNAPI.Location = new System.Drawing.Point(87, 54);
            this.CHECKBOX_SUNAPI.Name = "CHECKBOX_SUNAPI";
            this.CHECKBOX_SUNAPI.Size = new System.Drawing.Size(78, 24);
            this.CHECKBOX_SUNAPI.TabIndex = 20;
            this.CHECKBOX_SUNAPI.Text = "SUNAPI";
            this.CHECKBOX_SUNAPI.UseVisualStyleBackColor = true;
            // 
            // EDIT_PW
            // 
            this.EDIT_PW.Location = new System.Drawing.Point(86, 189);
            this.EDIT_PW.Name = "EDIT_PW";
            this.EDIT_PW.Size = new System.Drawing.Size(210, 21);
            this.EDIT_PW.TabIndex = 18;
            this.EDIT_PW.UseSystemPasswordChar = true;
            // 
            // EDIT_ID
            // 
            this.EDIT_ID.Location = new System.Drawing.Point(86, 162);
            this.EDIT_ID.Name = "EDIT_ID";
            this.EDIT_ID.Size = new System.Drawing.Size(210, 21);
            this.EDIT_ID.TabIndex = 17;
            // 
            // EDIT_IP
            // 
            this.EDIT_IP.Location = new System.Drawing.Point(86, 81);
            this.EDIT_IP.Name = "EDIT_IP";
            this.EDIT_IP.Size = new System.Drawing.Size(210, 21);
            this.EDIT_IP.TabIndex = 14;
            // 
            // COMBO_MODELLIST
            // 
            this.COMBO_MODELLIST.FormattingEnabled = true;
            this.COMBO_MODELLIST.Location = new System.Drawing.Point(86, 29);
            this.COMBO_MODELLIST.MaxDropDownItems = 15;
            this.COMBO_MODELLIST.Name = "COMBO_MODELLIST";
            this.COMBO_MODELLIST.Size = new System.Drawing.Size(210, 20);
            this.COMBO_MODELLIST.TabIndex = 14;
            // 
            // EDIT_HTTPPORT
            // 
            this.EDIT_HTTPPORT.Location = new System.Drawing.Point(86, 135);
            this.EDIT_HTTPPORT.Name = "EDIT_HTTPPORT";
            this.EDIT_HTTPPORT.Size = new System.Drawing.Size(210, 21);
            this.EDIT_HTTPPORT.TabIndex = 16;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 139);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(63, 12);
            this.label7.TabIndex = 15;
            this.label7.Text = "HTTP Port";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 59);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(51, 12);
            this.label1.TabIndex = 12;
            this.label1.Text = "Protocol";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(22, 251);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(132, 25);
            this.button1.TabIndex = 11;
            this.button1.Text = "Play";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.BTN_PLAY_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(164, 251);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(132, 25);
            this.button2.TabIndex = 11;
            this.button2.Text = "Stop";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(164, 220);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(132, 25);
            this.button3.TabIndex = 11;
            this.button3.Text = "Disconnect";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(22, 220);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(132, 25);
            this.button4.TabIndex = 11;
            this.button4.Text = "Connect";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.BTN_CONNECT_Click);
            // 
            // EDIT_PORT
            // 
            this.EDIT_PORT.Location = new System.Drawing.Point(86, 108);
            this.EDIT_PORT.Name = "EDIT_PORT";
            this.EDIT_PORT.Size = new System.Drawing.Size(210, 21);
            this.EDIT_PORT.TabIndex = 7;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 193);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(23, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "PW";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 166);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(16, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "ID";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 112);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 12);
            this.label4.TabIndex = 2;
            this.label4.Text = "Device Port";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 85);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(16, 12);
            this.label5.TabIndex = 1;
            this.label5.Text = "IP";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 32);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(40, 12);
            this.label6.TabIndex = 0;
            this.label6.Text = "Model";
            // 
            // axXnsSdkWindow
            // 
            this.axXnsSdkWindow.Enabled = true;
            this.axXnsSdkWindow.Location = new System.Drawing.Point(17, 13);
            this.axXnsSdkWindow.Name = "axXnsSdkWindow";
            this.axXnsSdkWindow.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow.OcxState")));
            this.axXnsSdkWindow.Size = new System.Drawing.Size(377, 267);
            this.axXnsSdkWindow.TabIndex = 1;
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(365, 290);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(29, 20);
            this.axXnsSdkDevice.TabIndex = 0;
            this.axXnsSdkDevice.Visible = false;
            this.axXnsSdkDevice.OnControlLocalNameChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnControlLocalNameChangedEventHandler(this.axXnsSdkDevice_OnControlLocalNameChanged);
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            this.axXnsSdkDevice.OnControlStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnControlStatusChangedEventHandler(this.axXnsSdkDevice_OnControlStatusChanged);
            this.axXnsSdkDevice.OnMotionEvent += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnMotionEventEventHandler(this.axXnsSdkDevice_OnMotionEvent);
            this.axXnsSdkDevice.OnSensorEvent += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnSensorEventEventHandler(this.axXnsSdkDevice_OnSensorEvent);
            this.axXnsSdkDevice.OnVideoLossEvent += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnVideoLossEventEventHandler(this.axXnsSdkDevice_OnVideoLossEvent);
            this.axXnsSdkDevice.OnPasswordChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnPasswordChangedEventHandler(this.axXnsSdkDevice_OnPasswordChanged);
            this.axXnsSdkDevice.OnAlarmOutControlFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnAlarmOutControlFailedEventHandler(this.axXnsSdkDevice_OnAlarmOutControlFailed);
            this.axXnsSdkDevice.OnControlRemoteNameChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnControlRemoteNameChangedEventHandler(this.axXnsSdkDevice_OnControlRemoteNameChanged);
            this.axXnsSdkDevice.OnIvOccurEvent += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnIvOccurEventEventHandler(this.axXnsSdkDevice_OnIvOccurEvent);
            this.axXnsSdkDevice.OnVideoFrameInfoReceived += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnVideoFrameInfoReceivedEventHandler(this.axXnsSdkDevice_OnVideoFrameInfoReceived);
            // 
            // EventForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(723, 731);
            this.Controls.Add(this.BTN_EVENT_LOG_CLEAR);
            this.Controls.Add(this.CHECKBOX_ALARM_BEEP_ON);
            this.Controls.Add(this.TAB_ALARM_EVENT);
            this.Controls.Add(this.STR_ACTIVEX_CONTROL_LOG);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.GROUP_CONNECTION_INFO);
            this.Controls.Add(this.axXnsSdkWindow);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Name = "EventForm";
            this.Text = "Event";
            this.Load += new System.EventHandler(this.EventForm_Load);
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
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
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
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label STR_PROTOCOL;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox EDIT_HTTPPORT;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.CheckBox CHECKBOX_SUNAPI;
       }
}

