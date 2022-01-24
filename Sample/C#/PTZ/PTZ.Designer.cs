namespace PTZ
{
    partial class PTZDlg
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PTZDlg));
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.axXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.GROUP_CONNECTION_INFO = new System.Windows.Forms.GroupBox();
            this.EDIT_PORT = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.BTN_DISCONNECT = new System.Windows.Forms.Button();
            this.BTN_CONNECT = new System.Windows.Forms.Button();
            this.COMBO_MODELLIST = new System.Windows.Forms.ComboBox();
            this.EDIT_PW = new System.Windows.Forms.TextBox();
            this.EDIT_ID = new System.Windows.Forms.TextBox();
            this.EDIT_HTTPPORT = new System.Windows.Forms.TextBox();
            this.EDIT_IP = new System.Windows.Forms.TextBox();
            this.STR_PW = new System.Windows.Forms.Label();
            this.STR_ID = new System.Windows.Forms.Label();
            this.STR_PORT = new System.Windows.Forms.Label();
            this.STR_IPADDRESS = new System.Windows.Forms.Label();
            this.STR_MODEL = new System.Windows.Forms.Label();
            this.GROUP_LIVE = new System.Windows.Forms.GroupBox();
            this.BTN_STOP = new System.Windows.Forms.Button();
            this.BTN_START = new System.Windows.Forms.Button();
            this.BTN_MEDIACLOSE = new System.Windows.Forms.Button();
            this.BTN_MEDIAOPEN = new System.Windows.Forms.Button();
            this.LIST_LOG = new System.Windows.Forms.ListBox();
            this.STR_STATUS = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.CHECK_MENU = new System.Windows.Forms.CheckBox();
            this.BTN_CANCEL = new System.Windows.Forms.Button();
            this.BTN_ENTER = new System.Windows.Forms.Button();
            this.BTN_RIGHT = new System.Windows.Forms.Button();
            this.BTN_LEFT = new System.Windows.Forms.Button();
            this.BTN_DOWN = new System.Windows.Forms.Button();
            this.BTN_UP = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.COMBO_SCAN = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.TRACKBAR_PTZ_SPEED = new System.Windows.Forms.TrackBar();
            this.BTN_PTZ_ZOOMIN = new System.Windows.Forms.Button();
            this.BTN_PTZ_ZOOMOUT = new System.Windows.Forms.Button();
            this.BTN_PTZ_DOWNRIGHT = new System.Windows.Forms.Button();
            this.BTN_PTZ_DOWNLEFT = new System.Windows.Forms.Button();
            this.BTN_PTZ_DOWN = new System.Windows.Forms.Button();
            this.BTN_PTZ_LEFT = new System.Windows.Forms.Button();
            this.BTN_PTZ_RIGHT = new System.Windows.Forms.Button();
            this.BTN_PTZ_STOP = new System.Windows.Forms.Button();
            this.BTN_PTZ_UPLEFT = new System.Windows.Forms.Button();
            this.BTN_PTZ_UPRIGHT = new System.Windows.Forms.Button();
            this.BTN_PTZ_UP = new System.Windows.Forms.Button();
            this.EDIT_PTZ_SPEED = new System.Windows.Forms.TextBox();
            this.EDIT_PTZ_ZOOM = new System.Windows.Forms.TextBox();
            this.EDIT_PTZ_TILT = new System.Windows.Forms.TextBox();
            this.EDIT_PTZ_PAN = new System.Windows.Forms.TextBox();
            this.BTN_SETPTZS = new System.Windows.Forms.Button();
            this.BTN_SETPTZ = new System.Windows.Forms.Button();
            this.BTN_GETPTZS = new System.Windows.Forms.Button();
            this.BTN_GETPTZ = new System.Windows.Forms.Button();
            this.BTN_ZOOM1X = new System.Windows.Forms.Button();
            this.CHECK_AREAZOOM = new System.Windows.Forms.CheckBox();
            this.BTN_RESTART = new System.Windows.Forms.Button();
            this.BTN_PRESET = new System.Windows.Forms.Button();
            this.COMBO_AUTOPAN = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.CHECKBOX_SUNAPI = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).BeginInit();
            this.GROUP_CONNECTION_INFO.SuspendLayout();
            this.GROUP_LIVE.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TRACKBAR_PTZ_SPEED)).BeginInit();
            this.SuspendLayout();
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(365, 357);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(87, 15);
            this.axXnsSdkDevice.TabIndex = 0;
            this.axXnsSdkDevice.Visible = false;
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            this.axXnsSdkDevice.OnGetPresetList += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnGetPresetListEventHandler(this.axXnsSdkDevice_OnGetPresetList);
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            this.axXnsSdkDevice.OnPtzControlFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnPtzControlFailedEventHandler(this.axXnsSdkDevice_OnPtzControlFailed);
            this.axXnsSdkDevice.OnGetPtzPos += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnGetPtzPosEventHandler(this.axXnsSdkDevice_OnGetPtzPos);
            this.axXnsSdkDevice.OnGetPtzPosSpeed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnGetPtzPosSpeedEventHandler(this.axXnsSdkDevice_OnGetPtzPosSpeed);
            this.axXnsSdkDevice.OnPowerRestart += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnPowerRestartEventHandler(this.axXnsSdkDevice_OnPowerRestart);
            // 
            // axXnsSdkWindow
            // 
            this.axXnsSdkWindow.Enabled = true;
            this.axXnsSdkWindow.Location = new System.Drawing.Point(12, 12);
            this.axXnsSdkWindow.Name = "axXnsSdkWindow";
            this.axXnsSdkWindow.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow.OcxState")));
            this.axXnsSdkWindow.Size = new System.Drawing.Size(440, 339);
            this.axXnsSdkWindow.TabIndex = 1;
            this.axXnsSdkWindow.OnLButtonDown += new AxXNSSDKWINDOWLib._DXnsSdkWindowEvents_OnLButtonDownEventHandler(this.axXnsSdkWindow_OnLButtonDown);
            this.axXnsSdkWindow.OnLButtonUp += new AxXNSSDKWINDOWLib._DXnsSdkWindowEvents_OnLButtonUpEventHandler(this.axXnsSdkWindow_OnLButtonUp);
            this.axXnsSdkWindow.OnMouseMove += new AxXNSSDKWINDOWLib._DXnsSdkWindowEvents_OnMouseMoveEventHandler(this.axXnsSdkWindow_OnMouseMove);
            // 
            // GROUP_CONNECTION_INFO
            // 
            this.GROUP_CONNECTION_INFO.Controls.Add(this.CHECKBOX_SUNAPI);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_PORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.label5);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.label4);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_DISCONNECT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_CONNECT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.COMBO_MODELLIST);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_PW);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_ID);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_HTTPPORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_IP);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_PW);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_ID);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_PORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_IPADDRESS);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_MODEL);
            this.GROUP_CONNECTION_INFO.Location = new System.Drawing.Point(458, 12);
            this.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO";
            this.GROUP_CONNECTION_INFO.Size = new System.Drawing.Size(280, 245);
            this.GROUP_CONNECTION_INFO.TabIndex = 2;
            this.GROUP_CONNECTION_INFO.TabStop = false;
            this.GROUP_CONNECTION_INFO.Text = "Connection Information";
            // 
            // EDIT_PORT
            // 
            this.EDIT_PORT.Location = new System.Drawing.Point(86, 107);
            this.EDIT_PORT.Name = "EDIT_PORT";
            this.EDIT_PORT.Size = new System.Drawing.Size(188, 21);
            this.EDIT_PORT.TabIndex = 17;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 112);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(77, 12);
            this.label5.TabIndex = 16;
            this.label5.Text = "Device Port  ";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 58);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(63, 12);
            this.label4.TabIndex = 13;
            this.label4.Text = "Protocol   ";
            // 
            // BTN_DISCONNECT
            // 
            this.BTN_DISCONNECT.Location = new System.Drawing.Point(159, 216);
            this.BTN_DISCONNECT.Name = "BTN_DISCONNECT";
            this.BTN_DISCONNECT.Size = new System.Drawing.Size(115, 21);
            this.BTN_DISCONNECT.TabIndex = 12;
            this.BTN_DISCONNECT.Text = "DisConnect";
            this.BTN_DISCONNECT.UseVisualStyleBackColor = true;
            this.BTN_DISCONNECT.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // BTN_CONNECT
            // 
            this.BTN_CONNECT.Location = new System.Drawing.Point(29, 216);
            this.BTN_CONNECT.Name = "BTN_CONNECT";
            this.BTN_CONNECT.Size = new System.Drawing.Size(115, 21);
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
            this.COMBO_MODELLIST.Size = new System.Drawing.Size(188, 20);
            this.COMBO_MODELLIST.TabIndex = 10;
            // 
            // EDIT_PW
            // 
            this.EDIT_PW.Location = new System.Drawing.Point(86, 188);
            this.EDIT_PW.Name = "EDIT_PW";
            this.EDIT_PW.Size = new System.Drawing.Size(188, 21);
            this.EDIT_PW.TabIndex = 9;
            this.EDIT_PW.UseSystemPasswordChar = true;
            // 
            // EDIT_ID
            // 
            this.EDIT_ID.Location = new System.Drawing.Point(86, 161);
            this.EDIT_ID.Name = "EDIT_ID";
            this.EDIT_ID.Size = new System.Drawing.Size(188, 21);
            this.EDIT_ID.TabIndex = 8;
            // 
            // EDIT_HTTPPORT
            // 
            this.EDIT_HTTPPORT.Location = new System.Drawing.Point(86, 134);
            this.EDIT_HTTPPORT.Name = "EDIT_HTTPPORT";
            this.EDIT_HTTPPORT.Size = new System.Drawing.Size(188, 21);
            this.EDIT_HTTPPORT.TabIndex = 7;
            // 
            // EDIT_IP
            // 
            this.EDIT_IP.Location = new System.Drawing.Point(86, 80);
            this.EDIT_IP.Name = "EDIT_IP";
            this.EDIT_IP.Size = new System.Drawing.Size(188, 21);
            this.EDIT_IP.TabIndex = 6;
            // 
            // STR_PW
            // 
            this.STR_PW.AutoSize = true;
            this.STR_PW.Location = new System.Drawing.Point(13, 193);
            this.STR_PW.Name = "STR_PW";
            this.STR_PW.Size = new System.Drawing.Size(63, 12);
            this.STR_PW.TabIndex = 4;
            this.STR_PW.Text = "PW          ";
            // 
            // STR_ID
            // 
            this.STR_ID.AutoSize = true;
            this.STR_ID.Location = new System.Drawing.Point(12, 166);
            this.STR_ID.Name = "STR_ID";
            this.STR_ID.Size = new System.Drawing.Size(64, 12);
            this.STR_ID.TabIndex = 3;
            this.STR_ID.Text = "ID            ";
            // 
            // STR_PORT
            // 
            this.STR_PORT.AutoSize = true;
            this.STR_PORT.Location = new System.Drawing.Point(12, 139);
            this.STR_PORT.Name = "STR_PORT";
            this.STR_PORT.Size = new System.Drawing.Size(63, 12);
            this.STR_PORT.TabIndex = 2;
            this.STR_PORT.Text = "HTTP Port";
            // 
            // STR_IPADDRESS
            // 
            this.STR_IPADDRESS.AutoSize = true;
            this.STR_IPADDRESS.Location = new System.Drawing.Point(12, 85);
            this.STR_IPADDRESS.Name = "STR_IPADDRESS";
            this.STR_IPADDRESS.Size = new System.Drawing.Size(64, 12);
            this.STR_IPADDRESS.TabIndex = 1;
            this.STR_IPADDRESS.Text = "IP            ";
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
            // GROUP_LIVE
            // 
            this.GROUP_LIVE.Controls.Add(this.BTN_STOP);
            this.GROUP_LIVE.Controls.Add(this.BTN_START);
            this.GROUP_LIVE.Controls.Add(this.BTN_MEDIACLOSE);
            this.GROUP_LIVE.Controls.Add(this.BTN_MEDIAOPEN);
            this.GROUP_LIVE.Location = new System.Drawing.Point(458, 263);
            this.GROUP_LIVE.Name = "GROUP_LIVE";
            this.GROUP_LIVE.Size = new System.Drawing.Size(280, 75);
            this.GROUP_LIVE.TabIndex = 3;
            this.GROUP_LIVE.TabStop = false;
            this.GROUP_LIVE.Text = "Live Control";
            // 
            // BTN_STOP
            // 
            this.BTN_STOP.Location = new System.Drawing.Point(158, 47);
            this.BTN_STOP.Name = "BTN_STOP";
            this.BTN_STOP.Size = new System.Drawing.Size(116, 19);
            this.BTN_STOP.TabIndex = 16;
            this.BTN_STOP.Text = "Stop";
            this.BTN_STOP.UseVisualStyleBackColor = true;
            this.BTN_STOP.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // BTN_START
            // 
            this.BTN_START.Location = new System.Drawing.Point(30, 47);
            this.BTN_START.Name = "BTN_START";
            this.BTN_START.Size = new System.Drawing.Size(114, 19);
            this.BTN_START.TabIndex = 15;
            this.BTN_START.Text = "Start";
            this.BTN_START.UseVisualStyleBackColor = true;
            this.BTN_START.Click += new System.EventHandler(this.BTN_START_Click);
            // 
            // BTN_MEDIACLOSE
            // 
            this.BTN_MEDIACLOSE.Location = new System.Drawing.Point(158, 20);
            this.BTN_MEDIACLOSE.Name = "BTN_MEDIACLOSE";
            this.BTN_MEDIACLOSE.Size = new System.Drawing.Size(116, 21);
            this.BTN_MEDIACLOSE.TabIndex = 14;
            this.BTN_MEDIACLOSE.Text = "Media Close";
            this.BTN_MEDIACLOSE.UseVisualStyleBackColor = true;
            this.BTN_MEDIACLOSE.Click += new System.EventHandler(this.BTN_MEDIACLOSE_Click);
            // 
            // BTN_MEDIAOPEN
            // 
            this.BTN_MEDIAOPEN.Location = new System.Drawing.Point(30, 20);
            this.BTN_MEDIAOPEN.Name = "BTN_MEDIAOPEN";
            this.BTN_MEDIAOPEN.Size = new System.Drawing.Size(114, 21);
            this.BTN_MEDIAOPEN.TabIndex = 13;
            this.BTN_MEDIAOPEN.Text = "Media Open";
            this.BTN_MEDIAOPEN.UseVisualStyleBackColor = true;
            this.BTN_MEDIAOPEN.Click += new System.EventHandler(this.BTN_MEDIAOPEN_Click);
            // 
            // LIST_LOG
            // 
            this.LIST_LOG.FormattingEnabled = true;
            this.LIST_LOG.ItemHeight = 12;
            this.LIST_LOG.Location = new System.Drawing.Point(12, 379);
            this.LIST_LOG.Name = "LIST_LOG";
            this.LIST_LOG.Size = new System.Drawing.Size(440, 328);
            this.LIST_LOG.TabIndex = 4;
            // 
            // STR_STATUS
            // 
            this.STR_STATUS.AutoSize = true;
            this.STR_STATUS.Location = new System.Drawing.Point(12, 361);
            this.STR_STATUS.Name = "STR_STATUS";
            this.STR_STATUS.Size = new System.Drawing.Size(65, 12);
            this.STR_STATUS.TabIndex = 13;
            this.STR_STATUS.Text = "Status Log";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.CHECK_MENU);
            this.groupBox1.Controls.Add(this.BTN_CANCEL);
            this.groupBox1.Controls.Add(this.BTN_ENTER);
            this.groupBox1.Controls.Add(this.BTN_RIGHT);
            this.groupBox1.Controls.Add(this.BTN_LEFT);
            this.groupBox1.Controls.Add(this.BTN_DOWN);
            this.groupBox1.Controls.Add(this.BTN_UP);
            this.groupBox1.Location = new System.Drawing.Point(458, 344);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(280, 100);
            this.groupBox1.TabIndex = 17;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "OSD Menu Cotrol";
            // 
            // CHECK_MENU
            // 
            this.CHECK_MENU.AutoSize = true;
            this.CHECK_MENU.Location = new System.Drawing.Point(161, 74);
            this.CHECK_MENU.Name = "CHECK_MENU";
            this.CHECK_MENU.Size = new System.Drawing.Size(97, 16);
            this.CHECK_MENU.TabIndex = 19;
            this.CHECK_MENU.Text = "Menu On/Off";
            this.CHECK_MENU.UseVisualStyleBackColor = true;
            this.CHECK_MENU.CheckedChanged += new System.EventHandler(this.CHECK_MENU_CheckedChanged);
            // 
            // BTN_CANCEL
            // 
            this.BTN_CANCEL.Location = new System.Drawing.Point(161, 47);
            this.BTN_CANCEL.Name = "BTN_CANCEL";
            this.BTN_CANCEL.Size = new System.Drawing.Size(113, 21);
            this.BTN_CANCEL.TabIndex = 18;
            this.BTN_CANCEL.Text = "Cancel";
            this.BTN_CANCEL.UseVisualStyleBackColor = true;
            this.BTN_CANCEL.Click += new System.EventHandler(this.BTN_CANCEL_Click);
            // 
            // BTN_ENTER
            // 
            this.BTN_ENTER.Location = new System.Drawing.Point(161, 20);
            this.BTN_ENTER.Name = "BTN_ENTER";
            this.BTN_ENTER.Size = new System.Drawing.Size(113, 21);
            this.BTN_ENTER.TabIndex = 17;
            this.BTN_ENTER.Text = "Enter";
            this.BTN_ENTER.UseVisualStyleBackColor = true;
            this.BTN_ENTER.Click += new System.EventHandler(this.BTN_ENTER_Click);
            // 
            // BTN_RIGHT
            // 
            this.BTN_RIGHT.Location = new System.Drawing.Point(103, 48);
            this.BTN_RIGHT.Name = "BTN_RIGHT";
            this.BTN_RIGHT.Size = new System.Drawing.Size(37, 21);
            this.BTN_RIGHT.TabIndex = 16;
            this.BTN_RIGHT.Text = "▷";
            this.BTN_RIGHT.UseVisualStyleBackColor = true;
            this.BTN_RIGHT.Click += new System.EventHandler(this.BTN_RIGHT_Click);
            // 
            // BTN_LEFT
            // 
            this.BTN_LEFT.Location = new System.Drawing.Point(17, 48);
            this.BTN_LEFT.Name = "BTN_LEFT";
            this.BTN_LEFT.Size = new System.Drawing.Size(37, 21);
            this.BTN_LEFT.TabIndex = 15;
            this.BTN_LEFT.Text = "◁";
            this.BTN_LEFT.UseVisualStyleBackColor = true;
            this.BTN_LEFT.Click += new System.EventHandler(this.BTN_LEFT_Click);
            // 
            // BTN_DOWN
            // 
            this.BTN_DOWN.Location = new System.Drawing.Point(60, 48);
            this.BTN_DOWN.Name = "BTN_DOWN";
            this.BTN_DOWN.Size = new System.Drawing.Size(37, 21);
            this.BTN_DOWN.TabIndex = 14;
            this.BTN_DOWN.Text = "▽";
            this.BTN_DOWN.UseVisualStyleBackColor = true;
            this.BTN_DOWN.Click += new System.EventHandler(this.BTN_DOWN_Click);
            // 
            // BTN_UP
            // 
            this.BTN_UP.Location = new System.Drawing.Point(60, 21);
            this.BTN_UP.Name = "BTN_UP";
            this.BTN_UP.Size = new System.Drawing.Size(37, 21);
            this.BTN_UP.TabIndex = 13;
            this.BTN_UP.Text = "△";
            this.BTN_UP.UseVisualStyleBackColor = true;
            this.BTN_UP.Click += new System.EventHandler(this.BTN_UP_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.COMBO_SCAN);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.TRACKBAR_PTZ_SPEED);
            this.groupBox2.Controls.Add(this.BTN_PTZ_ZOOMIN);
            this.groupBox2.Controls.Add(this.BTN_PTZ_ZOOMOUT);
            this.groupBox2.Controls.Add(this.BTN_PTZ_DOWNRIGHT);
            this.groupBox2.Controls.Add(this.BTN_PTZ_DOWNLEFT);
            this.groupBox2.Controls.Add(this.BTN_PTZ_DOWN);
            this.groupBox2.Controls.Add(this.BTN_PTZ_LEFT);
            this.groupBox2.Controls.Add(this.BTN_PTZ_RIGHT);
            this.groupBox2.Controls.Add(this.BTN_PTZ_STOP);
            this.groupBox2.Controls.Add(this.BTN_PTZ_UPLEFT);
            this.groupBox2.Controls.Add(this.BTN_PTZ_UPRIGHT);
            this.groupBox2.Controls.Add(this.BTN_PTZ_UP);
            this.groupBox2.Controls.Add(this.EDIT_PTZ_SPEED);
            this.groupBox2.Controls.Add(this.EDIT_PTZ_ZOOM);
            this.groupBox2.Controls.Add(this.EDIT_PTZ_TILT);
            this.groupBox2.Controls.Add(this.EDIT_PTZ_PAN);
            this.groupBox2.Controls.Add(this.BTN_SETPTZS);
            this.groupBox2.Controls.Add(this.BTN_SETPTZ);
            this.groupBox2.Controls.Add(this.BTN_GETPTZS);
            this.groupBox2.Controls.Add(this.BTN_GETPTZ);
            this.groupBox2.Controls.Add(this.BTN_ZOOM1X);
            this.groupBox2.Controls.Add(this.CHECK_AREAZOOM);
            this.groupBox2.Controls.Add(this.BTN_RESTART);
            this.groupBox2.Controls.Add(this.BTN_PRESET);
            this.groupBox2.Controls.Add(this.COMBO_AUTOPAN);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Location = new System.Drawing.Point(458, 450);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(280, 317);
            this.groupBox2.TabIndex = 20;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "OSD Menu Cotrol";
            // 
            // COMBO_SCAN
            // 
            this.COMBO_SCAN.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.COMBO_SCAN.FormattingEnabled = true;
            this.COMBO_SCAN.Items.AddRange(new object[] {
            "None",
            "Auto Scan [1]",
            "Auto Scan [2]",
            "Auto Scan [3]",
            "Auto Scan [4]",
            "Auto Scan [5]"});
            this.COMBO_SCAN.Location = new System.Drawing.Point(84, 20);
            this.COMBO_SCAN.Name = "COMBO_SCAN";
            this.COMBO_SCAN.Size = new System.Drawing.Size(190, 20);
            this.COMBO_SCAN.TabIndex = 1;
            this.COMBO_SCAN.SelectedIndexChanged += new System.EventHandler(this.COMBO_SCAN_SelectedIndexChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(46, 271);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 36;
            this.label3.Text = "Speed";
            // 
            // TRACKBAR_PTZ_SPEED
            // 
            this.TRACKBAR_PTZ_SPEED.Location = new System.Drawing.Point(84, 267);
            this.TRACKBAR_PTZ_SPEED.Maximum = 100;
            this.TRACKBAR_PTZ_SPEED.Minimum = 1;
            this.TRACKBAR_PTZ_SPEED.Name = "TRACKBAR_PTZ_SPEED";
            this.TRACKBAR_PTZ_SPEED.Size = new System.Drawing.Size(123, 45);
            this.TRACKBAR_PTZ_SPEED.TabIndex = 35;
            this.TRACKBAR_PTZ_SPEED.Value = 50;
            this.TRACKBAR_PTZ_SPEED.MouseCaptureChanged += new System.EventHandler(this.TRACKBAR_PTZ_SPEED_MouseCaptureChanged);
            // 
            // BTN_PTZ_ZOOMIN
            // 
            this.BTN_PTZ_ZOOMIN.Location = new System.Drawing.Point(213, 262);
            this.BTN_PTZ_ZOOMIN.Name = "BTN_PTZ_ZOOMIN";
            this.BTN_PTZ_ZOOMIN.Size = new System.Drawing.Size(37, 21);
            this.BTN_PTZ_ZOOMIN.TabIndex = 34;
            this.BTN_PTZ_ZOOMIN.Text = "+";
            this.BTN_PTZ_ZOOMIN.UseVisualStyleBackColor = true;
            this.BTN_PTZ_ZOOMIN.Click += new System.EventHandler(this.BTN_PTZ_ZOOMIN_Click);
            // 
            // BTN_PTZ_ZOOMOUT
            // 
            this.BTN_PTZ_ZOOMOUT.Location = new System.Drawing.Point(213, 287);
            this.BTN_PTZ_ZOOMOUT.Name = "BTN_PTZ_ZOOMOUT";
            this.BTN_PTZ_ZOOMOUT.Size = new System.Drawing.Size(37, 21);
            this.BTN_PTZ_ZOOMOUT.TabIndex = 33;
            this.BTN_PTZ_ZOOMOUT.Text = "-";
            this.BTN_PTZ_ZOOMOUT.UseVisualStyleBackColor = true;
            this.BTN_PTZ_ZOOMOUT.Click += new System.EventHandler(this.BTN_PTZ_ZOOMOUT_Click);
            // 
            // BTN_PTZ_DOWNRIGHT
            // 
            this.BTN_PTZ_DOWNRIGHT.Location = new System.Drawing.Point(170, 240);
            this.BTN_PTZ_DOWNRIGHT.Name = "BTN_PTZ_DOWNRIGHT";
            this.BTN_PTZ_DOWNRIGHT.Size = new System.Drawing.Size(37, 21);
            this.BTN_PTZ_DOWNRIGHT.TabIndex = 32;
            this.BTN_PTZ_DOWNRIGHT.Text = "↘";
            this.BTN_PTZ_DOWNRIGHT.UseVisualStyleBackColor = true;
            this.BTN_PTZ_DOWNRIGHT.Click += new System.EventHandler(this.BTN_PTZ_DOWNRIGHT_Click);
            // 
            // BTN_PTZ_DOWNLEFT
            // 
            this.BTN_PTZ_DOWNLEFT.Location = new System.Drawing.Point(84, 240);
            this.BTN_PTZ_DOWNLEFT.Name = "BTN_PTZ_DOWNLEFT";
            this.BTN_PTZ_DOWNLEFT.Size = new System.Drawing.Size(37, 21);
            this.BTN_PTZ_DOWNLEFT.TabIndex = 31;
            this.BTN_PTZ_DOWNLEFT.Text = "↙";
            this.BTN_PTZ_DOWNLEFT.UseVisualStyleBackColor = true;
            this.BTN_PTZ_DOWNLEFT.Click += new System.EventHandler(this.BTN_PTZ_DOWNLEFT_Click);
            // 
            // BTN_PTZ_DOWN
            // 
            this.BTN_PTZ_DOWN.Location = new System.Drawing.Point(127, 240);
            this.BTN_PTZ_DOWN.Name = "BTN_PTZ_DOWN";
            this.BTN_PTZ_DOWN.Size = new System.Drawing.Size(37, 21);
            this.BTN_PTZ_DOWN.TabIndex = 30;
            this.BTN_PTZ_DOWN.Text = "↓";
            this.BTN_PTZ_DOWN.UseVisualStyleBackColor = true;
            this.BTN_PTZ_DOWN.Click += new System.EventHandler(this.BTN_PTZ_DOWN_Click);
            // 
            // BTN_PTZ_LEFT
            // 
            this.BTN_PTZ_LEFT.Location = new System.Drawing.Point(84, 213);
            this.BTN_PTZ_LEFT.Name = "BTN_PTZ_LEFT";
            this.BTN_PTZ_LEFT.Size = new System.Drawing.Size(37, 21);
            this.BTN_PTZ_LEFT.TabIndex = 29;
            this.BTN_PTZ_LEFT.Text = "←";
            this.BTN_PTZ_LEFT.UseVisualStyleBackColor = true;
            this.BTN_PTZ_LEFT.Click += new System.EventHandler(this.BTN_PTZ_LEFT_Click);
            // 
            // BTN_PTZ_RIGHT
            // 
            this.BTN_PTZ_RIGHT.Location = new System.Drawing.Point(170, 213);
            this.BTN_PTZ_RIGHT.Name = "BTN_PTZ_RIGHT";
            this.BTN_PTZ_RIGHT.Size = new System.Drawing.Size(37, 21);
            this.BTN_PTZ_RIGHT.TabIndex = 28;
            this.BTN_PTZ_RIGHT.Text = "→";
            this.BTN_PTZ_RIGHT.UseVisualStyleBackColor = true;
            this.BTN_PTZ_RIGHT.Click += new System.EventHandler(this.BTN_PTZ_RIGHT_Click);
            // 
            // BTN_PTZ_STOP
            // 
            this.BTN_PTZ_STOP.Location = new System.Drawing.Point(127, 213);
            this.BTN_PTZ_STOP.Name = "BTN_PTZ_STOP";
            this.BTN_PTZ_STOP.Size = new System.Drawing.Size(37, 21);
            this.BTN_PTZ_STOP.TabIndex = 27;
            this.BTN_PTZ_STOP.Text = "||";
            this.BTN_PTZ_STOP.UseVisualStyleBackColor = true;
            this.BTN_PTZ_STOP.Click += new System.EventHandler(this.BTN_PTZ_STOP_Click);
            // 
            // BTN_PTZ_UPLEFT
            // 
            this.BTN_PTZ_UPLEFT.Location = new System.Drawing.Point(84, 186);
            this.BTN_PTZ_UPLEFT.Name = "BTN_PTZ_UPLEFT";
            this.BTN_PTZ_UPLEFT.Size = new System.Drawing.Size(37, 21);
            this.BTN_PTZ_UPLEFT.TabIndex = 26;
            this.BTN_PTZ_UPLEFT.Text = "↖";
            this.BTN_PTZ_UPLEFT.UseVisualStyleBackColor = true;
            this.BTN_PTZ_UPLEFT.Click += new System.EventHandler(this.BTN_PTZ_UPLEFT_Click);
            // 
            // BTN_PTZ_UPRIGHT
            // 
            this.BTN_PTZ_UPRIGHT.Location = new System.Drawing.Point(170, 186);
            this.BTN_PTZ_UPRIGHT.Name = "BTN_PTZ_UPRIGHT";
            this.BTN_PTZ_UPRIGHT.Size = new System.Drawing.Size(37, 21);
            this.BTN_PTZ_UPRIGHT.TabIndex = 25;
            this.BTN_PTZ_UPRIGHT.Text = "↗";
            this.BTN_PTZ_UPRIGHT.UseVisualStyleBackColor = true;
            this.BTN_PTZ_UPRIGHT.Click += new System.EventHandler(this.BTN_PTZ_UPRIGHT_Click);
            // 
            // BTN_PTZ_UP
            // 
            this.BTN_PTZ_UP.Location = new System.Drawing.Point(127, 186);
            this.BTN_PTZ_UP.Name = "BTN_PTZ_UP";
            this.BTN_PTZ_UP.Size = new System.Drawing.Size(37, 21);
            this.BTN_PTZ_UP.TabIndex = 20;
            this.BTN_PTZ_UP.Text = "↑";
            this.BTN_PTZ_UP.UseVisualStyleBackColor = true;
            this.BTN_PTZ_UP.Click += new System.EventHandler(this.BTN_PTZ_UP_Click);
            // 
            // EDIT_PTZ_SPEED
            // 
            this.EDIT_PTZ_SPEED.Location = new System.Drawing.Point(204, 159);
            this.EDIT_PTZ_SPEED.Name = "EDIT_PTZ_SPEED";
            this.EDIT_PTZ_SPEED.Size = new System.Drawing.Size(39, 21);
            this.EDIT_PTZ_SPEED.TabIndex = 24;
            this.EDIT_PTZ_SPEED.Text = "0";
            // 
            // EDIT_PTZ_ZOOM
            // 
            this.EDIT_PTZ_ZOOM.Location = new System.Drawing.Point(148, 159);
            this.EDIT_PTZ_ZOOM.Name = "EDIT_PTZ_ZOOM";
            this.EDIT_PTZ_ZOOM.Size = new System.Drawing.Size(42, 21);
            this.EDIT_PTZ_ZOOM.TabIndex = 24;
            this.EDIT_PTZ_ZOOM.Text = "0";
            // 
            // EDIT_PTZ_TILT
            // 
            this.EDIT_PTZ_TILT.Location = new System.Drawing.Point(96, 159);
            this.EDIT_PTZ_TILT.Name = "EDIT_PTZ_TILT";
            this.EDIT_PTZ_TILT.Size = new System.Drawing.Size(44, 21);
            this.EDIT_PTZ_TILT.TabIndex = 23;
            this.EDIT_PTZ_TILT.Text = "0";
            // 
            // EDIT_PTZ_PAN
            // 
            this.EDIT_PTZ_PAN.Location = new System.Drawing.Point(48, 159);
            this.EDIT_PTZ_PAN.Name = "EDIT_PTZ_PAN";
            this.EDIT_PTZ_PAN.Size = new System.Drawing.Size(40, 21);
            this.EDIT_PTZ_PAN.TabIndex = 13;
            this.EDIT_PTZ_PAN.Text = "0";
            // 
            // BTN_SETPTZS
            // 
            this.BTN_SETPTZS.Location = new System.Drawing.Point(195, 106);
            this.BTN_SETPTZS.Name = "BTN_SETPTZS";
            this.BTN_SETPTZS.Size = new System.Drawing.Size(79, 22);
            this.BTN_SETPTZS.TabIndex = 22;
            this.BTN_SETPTZS.Text = "Set PTZS";
            this.BTN_SETPTZS.UseVisualStyleBackColor = true;
            this.BTN_SETPTZS.Click += new System.EventHandler(this.BTN_SETPTZ2_Click);
            // 
            // BTN_SETPTZ
            // 
            this.BTN_SETPTZ.Location = new System.Drawing.Point(195, 129);
            this.BTN_SETPTZ.Name = "BTN_SETPTZ";
            this.BTN_SETPTZ.Size = new System.Drawing.Size(79, 22);
            this.BTN_SETPTZ.TabIndex = 22;
            this.BTN_SETPTZ.Text = "Set PTZ";
            this.BTN_SETPTZ.UseVisualStyleBackColor = true;
            this.BTN_SETPTZ.Click += new System.EventHandler(this.BTN_SETPTZ_Click);
            // 
            // BTN_GETPTZS
            // 
            this.BTN_GETPTZS.Location = new System.Drawing.Point(109, 106);
            this.BTN_GETPTZS.Name = "BTN_GETPTZS";
            this.BTN_GETPTZS.Size = new System.Drawing.Size(74, 22);
            this.BTN_GETPTZS.TabIndex = 21;
            this.BTN_GETPTZS.Text = "Get PTZS";
            this.BTN_GETPTZS.UseVisualStyleBackColor = true;
            this.BTN_GETPTZS.Click += new System.EventHandler(this.BTN_GETPTZ2_Click);
            // 
            // BTN_GETPTZ
            // 
            this.BTN_GETPTZ.Location = new System.Drawing.Point(109, 129);
            this.BTN_GETPTZ.Name = "BTN_GETPTZ";
            this.BTN_GETPTZ.Size = new System.Drawing.Size(74, 22);
            this.BTN_GETPTZ.TabIndex = 21;
            this.BTN_GETPTZ.Text = "Get PTZ";
            this.BTN_GETPTZ.UseVisualStyleBackColor = true;
            this.BTN_GETPTZ.Click += new System.EventHandler(this.BTN_GETPTZ_Click);
            // 
            // BTN_ZOOM1X
            // 
            this.BTN_ZOOM1X.Location = new System.Drawing.Point(31, 119);
            this.BTN_ZOOM1X.Name = "BTN_ZOOM1X";
            this.BTN_ZOOM1X.Size = new System.Drawing.Size(66, 32);
            this.BTN_ZOOM1X.TabIndex = 20;
            this.BTN_ZOOM1X.Text = "Zoom 1X";
            this.BTN_ZOOM1X.UseVisualStyleBackColor = true;
            this.BTN_ZOOM1X.Click += new System.EventHandler(this.BTN_ZOOM1X_Click);
            // 
            // CHECK_AREAZOOM
            // 
            this.CHECK_AREAZOOM.AutoSize = true;
            this.CHECK_AREAZOOM.Location = new System.Drawing.Point(15, 97);
            this.CHECK_AREAZOOM.Name = "CHECK_AREAZOOM";
            this.CHECK_AREAZOOM.Size = new System.Drawing.Size(87, 16);
            this.CHECK_AREAZOOM.TabIndex = 20;
            this.CHECK_AREAZOOM.Text = "Area Zoom";
            this.CHECK_AREAZOOM.UseVisualStyleBackColor = true;
            this.CHECK_AREAZOOM.CheckedChanged += new System.EventHandler(this.CHECK_AREAZOOM_CheckedChanged);
            // 
            // BTN_RESTART
            // 
            this.BTN_RESTART.Location = new System.Drawing.Point(159, 71);
            this.BTN_RESTART.Name = "BTN_RESTART";
            this.BTN_RESTART.Size = new System.Drawing.Size(115, 20);
            this.BTN_RESTART.TabIndex = 17;
            this.BTN_RESTART.Text = "Restart";
            this.BTN_RESTART.UseVisualStyleBackColor = true;
            this.BTN_RESTART.Click += new System.EventHandler(this.BTN_RESTART_Click);
            // 
            // BTN_PRESET
            // 
            this.BTN_PRESET.Location = new System.Drawing.Point(30, 71);
            this.BTN_PRESET.Name = "BTN_PRESET";
            this.BTN_PRESET.Size = new System.Drawing.Size(115, 20);
            this.BTN_PRESET.TabIndex = 17;
            this.BTN_PRESET.Text = "Preset";
            this.BTN_PRESET.UseVisualStyleBackColor = true;
            this.BTN_PRESET.Click += new System.EventHandler(this.BTN_PRESET_Click);
            // 
            // COMBO_AUTOPAN
            // 
            this.COMBO_AUTOPAN.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.COMBO_AUTOPAN.FormattingEnabled = true;
            this.COMBO_AUTOPAN.Items.AddRange(new object[] {
            "None",
            "Auto Pan [1]",
            "Auto Pan [2]",
            "Auto Pan [3]",
            "Auto Pan [4]"});
            this.COMBO_AUTOPAN.Location = new System.Drawing.Point(84, 45);
            this.COMBO_AUTOPAN.Name = "COMBO_AUTOPAN";
            this.COMBO_AUTOPAN.Size = new System.Drawing.Size(190, 20);
            this.COMBO_AUTOPAN.TabIndex = 1;
            this.COMBO_AUTOPAN.SelectedIndexChanged += new System.EventHandler(this.COMBO_AUTOPAN_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(68, 12);
            this.label2.TabIndex = 13;
            this.label2.Text = "Auto Pan : ";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 12);
            this.label1.TabIndex = 13;
            this.label1.Text = "Scan       :";
            // 
            // CHECKBOX_SUNAPI
            // 
            this.CHECKBOX_SUNAPI.Location = new System.Drawing.Point(86, 53);
            this.CHECKBOX_SUNAPI.Name = "CHECKBOX_SUNAPI";
            this.CHECKBOX_SUNAPI.Size = new System.Drawing.Size(78, 24);
            this.CHECKBOX_SUNAPI.TabIndex = 25;
            this.CHECKBOX_SUNAPI.Text = "SUNAPI";
            this.CHECKBOX_SUNAPI.UseVisualStyleBackColor = true;
            // 
            // PTZDlg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(749, 776);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Controls.Add(this.STR_STATUS);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.GROUP_LIVE);
            this.Controls.Add(this.GROUP_CONNECTION_INFO);
            this.Controls.Add(this.axXnsSdkWindow);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "PTZDlg";
            this.Text = "PTZ";
            this.Load += new System.EventHandler(this.PTZDlg_Load);
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).EndInit();
            this.GROUP_CONNECTION_INFO.ResumeLayout(false);
            this.GROUP_CONNECTION_INFO.PerformLayout();
            this.GROUP_LIVE.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TRACKBAR_PTZ_SPEED)).EndInit();
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
        private System.Windows.Forms.TextBox EDIT_HTTPPORT;
        private System.Windows.Forms.TextBox EDIT_IP;
        private System.Windows.Forms.Button BTN_CONNECT;
        private System.Windows.Forms.Button BTN_DISCONNECT;
        private System.Windows.Forms.GroupBox GROUP_LIVE;
        private System.Windows.Forms.Button BTN_MEDIACLOSE;
        private System.Windows.Forms.Button BTN_MEDIAOPEN;
        private System.Windows.Forms.Button BTN_STOP;
        private System.Windows.Forms.Button BTN_START;
        private System.Windows.Forms.ListBox LIST_LOG;
        private System.Windows.Forms.Label STR_STATUS;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button BTN_RIGHT;
        private System.Windows.Forms.Button BTN_LEFT;
        private System.Windows.Forms.Button BTN_DOWN;
        private System.Windows.Forms.Button BTN_UP;
        private System.Windows.Forms.CheckBox CHECK_MENU;
        private System.Windows.Forms.Button BTN_CANCEL;
        private System.Windows.Forms.Button BTN_ENTER;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox CHECK_AREAZOOM;
        private System.Windows.Forms.Button BTN_PRESET;
        private System.Windows.Forms.ComboBox COMBO_AUTOPAN;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox EDIT_PTZ_ZOOM;
        private System.Windows.Forms.TextBox EDIT_PTZ_TILT;
        private System.Windows.Forms.TextBox EDIT_PTZ_PAN;
        private System.Windows.Forms.Button BTN_SETPTZ;
        private System.Windows.Forms.Button BTN_GETPTZ;
        private System.Windows.Forms.Button BTN_ZOOM1X;
        private System.Windows.Forms.Button BTN_PTZ_ZOOMIN;
        private System.Windows.Forms.Button BTN_PTZ_ZOOMOUT;
        private System.Windows.Forms.Button BTN_PTZ_DOWNRIGHT;
        private System.Windows.Forms.Button BTN_PTZ_DOWNLEFT;
        private System.Windows.Forms.Button BTN_PTZ_DOWN;
        private System.Windows.Forms.Button BTN_PTZ_LEFT;
        private System.Windows.Forms.Button BTN_PTZ_RIGHT;
        private System.Windows.Forms.Button BTN_PTZ_STOP;
        private System.Windows.Forms.Button BTN_PTZ_UPLEFT;
        private System.Windows.Forms.Button BTN_PTZ_UPRIGHT;
        private System.Windows.Forms.Button BTN_PTZ_UP;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TrackBar TRACKBAR_PTZ_SPEED;
        private System.Windows.Forms.ComboBox COMBO_SCAN;
        private System.Windows.Forms.TextBox EDIT_PTZ_SPEED;
        private System.Windows.Forms.Button BTN_SETPTZS;
        private System.Windows.Forms.Button BTN_GETPTZS;
        private System.Windows.Forms.Button BTN_RESTART;
        private System.Windows.Forms.TextBox EDIT_PORT;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox CHECKBOX_SUNAPI;
    }
}

