namespace MetaData
{
    partial class MetaDataForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MetaDataForm));
            this.GROUP_CONNECTION_INFO = new System.Windows.Forms.GroupBox();
            this.EDIT_HTTPPORT = new System.Windows.Forms.TextBox();
            this.STR_HTTPPORT = new System.Windows.Forms.Label();
            this.STR_PROTOCOL = new System.Windows.Forms.Label();
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
            this.GROUP_LIVE = new System.Windows.Forms.GroupBox();
            this.BTN_STOP = new System.Windows.Forms.Button();
            this.BTN_START = new System.Windows.Forms.Button();
            this.BTN_MEDIACLOSE = new System.Windows.Forms.Button();
            this.BTN_MEDIAOPEN = new System.Windows.Forms.Button();
            this.STR_STATUS = new System.Windows.Forms.Label();
            this.LIST_LOG = new System.Windows.Forms.ListBox();
            this.axXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.label1 = new System.Windows.Forms.Label();
            this.LIST_META_DATA = new System.Windows.Forms.ListBox();
            this.CHECKBOX_SUNAPI = new System.Windows.Forms.CheckBox();
            this.GROUP_CONNECTION_INFO.SuspendLayout();
            this.GROUP_LIVE.SuspendLayout();
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
            this.GROUP_CONNECTION_INFO.Location = new System.Drawing.Point(462, 12);
            this.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO";
            this.GROUP_CONNECTION_INFO.Size = new System.Drawing.Size(280, 271);
            this.GROUP_CONNECTION_INFO.TabIndex = 3;
            this.GROUP_CONNECTION_INFO.TabStop = false;
            this.GROUP_CONNECTION_INFO.Text = "Connection Information";
            // 
            // EDIT_HTTPPORT
            // 
            this.EDIT_HTTPPORT.Location = new System.Drawing.Point(85, 135);
            this.EDIT_HTTPPORT.Name = "EDIT_HTTPPORT";
            this.EDIT_HTTPPORT.Size = new System.Drawing.Size(188, 21);
            this.EDIT_HTTPPORT.TabIndex = 17;
            // 
            // STR_HTTPPORT
            // 
            this.STR_HTTPPORT.AutoSize = true;
            this.STR_HTTPPORT.Location = new System.Drawing.Point(9, 140);
            this.STR_HTTPPORT.Name = "STR_HTTPPORT";
            this.STR_HTTPPORT.Size = new System.Drawing.Size(63, 12);
            this.STR_HTTPPORT.TabIndex = 16;
            this.STR_HTTPPORT.Text = "HTTP Port";
            // 
            // STR_PROTOCOL
            // 
            this.STR_PROTOCOL.AutoSize = true;
            this.STR_PROTOCOL.Location = new System.Drawing.Point(9, 59);
            this.STR_PROTOCOL.Name = "STR_PROTOCOL";
            this.STR_PROTOCOL.Size = new System.Drawing.Size(51, 12);
            this.STR_PROTOCOL.TabIndex = 13;
            this.STR_PROTOCOL.Text = "Protocol";
            // 
            // BTN_DISCONNECT
            // 
            this.BTN_DISCONNECT.Location = new System.Drawing.Point(148, 229);
            this.BTN_DISCONNECT.Name = "BTN_DISCONNECT";
            this.BTN_DISCONNECT.Size = new System.Drawing.Size(118, 29);
            this.BTN_DISCONNECT.TabIndex = 12;
            this.BTN_DISCONNECT.Text = "Disconnect";
            this.BTN_DISCONNECT.UseVisualStyleBackColor = true;
            this.BTN_DISCONNECT.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // BTN_CONNECT
            // 
            this.BTN_CONNECT.Location = new System.Drawing.Point(18, 229);
            this.BTN_CONNECT.Name = "BTN_CONNECT";
            this.BTN_CONNECT.Size = new System.Drawing.Size(118, 29);
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
            this.COMBO_MODELLIST.Sorted = true;
            this.COMBO_MODELLIST.TabIndex = 10;
            // 
            // EDIT_PW
            // 
            this.EDIT_PW.Location = new System.Drawing.Point(86, 191);
            this.EDIT_PW.Name = "EDIT_PW";
            this.EDIT_PW.Size = new System.Drawing.Size(188, 21);
            this.EDIT_PW.TabIndex = 9;
            this.EDIT_PW.UseSystemPasswordChar = true;
            // 
            // EDIT_ID
            // 
            this.EDIT_ID.Location = new System.Drawing.Point(86, 164);
            this.EDIT_ID.Name = "EDIT_ID";
            this.EDIT_ID.Size = new System.Drawing.Size(188, 21);
            this.EDIT_ID.TabIndex = 8;
            // 
            // EDIT_PORT
            // 
            this.EDIT_PORT.HideSelection = false;
            this.EDIT_PORT.Location = new System.Drawing.Point(85, 108);
            this.EDIT_PORT.Name = "EDIT_PORT";
            this.EDIT_PORT.Size = new System.Drawing.Size(188, 21);
            this.EDIT_PORT.TabIndex = 7;
            // 
            // EDIT_IP
            // 
            this.EDIT_IP.Location = new System.Drawing.Point(85, 81);
            this.EDIT_IP.Name = "EDIT_IP";
            this.EDIT_IP.Size = new System.Drawing.Size(188, 21);
            this.EDIT_IP.TabIndex = 6;
            // 
            // STR_PW
            // 
            this.STR_PW.AutoSize = true;
            this.STR_PW.Location = new System.Drawing.Point(11, 196);
            this.STR_PW.Name = "STR_PW";
            this.STR_PW.Size = new System.Drawing.Size(23, 12);
            this.STR_PW.TabIndex = 4;
            this.STR_PW.Text = "PW";
            // 
            // STR_ID
            // 
            this.STR_ID.AutoSize = true;
            this.STR_ID.Location = new System.Drawing.Point(10, 168);
            this.STR_ID.Name = "STR_ID";
            this.STR_ID.Size = new System.Drawing.Size(16, 12);
            this.STR_ID.TabIndex = 3;
            this.STR_ID.Text = "ID";
            // 
            // STR_PORT
            // 
            this.STR_PORT.AutoSize = true;
            this.STR_PORT.Location = new System.Drawing.Point(9, 112);
            this.STR_PORT.Name = "STR_PORT";
            this.STR_PORT.Size = new System.Drawing.Size(69, 12);
            this.STR_PORT.TabIndex = 2;
            this.STR_PORT.Text = "Device Port";
            // 
            // STR_IPADDRESS
            // 
            this.STR_IPADDRESS.AutoSize = true;
            this.STR_IPADDRESS.Location = new System.Drawing.Point(9, 86);
            this.STR_IPADDRESS.Name = "STR_IPADDRESS";
            this.STR_IPADDRESS.Size = new System.Drawing.Size(16, 12);
            this.STR_IPADDRESS.TabIndex = 1;
            this.STR_IPADDRESS.Text = "IP";
            // 
            // STR_MODEL
            // 
            this.STR_MODEL.AutoSize = true;
            this.STR_MODEL.Location = new System.Drawing.Point(10, 32);
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
            this.GROUP_LIVE.Location = new System.Drawing.Point(456, 289);
            this.GROUP_LIVE.Name = "GROUP_LIVE";
            this.GROUP_LIVE.Size = new System.Drawing.Size(286, 103);
            this.GROUP_LIVE.TabIndex = 4;
            this.GROUP_LIVE.TabStop = false;
            this.GROUP_LIVE.Text = "Live Control";
            // 
            // BTN_STOP
            // 
            this.BTN_STOP.Location = new System.Drawing.Point(152, 59);
            this.BTN_STOP.Name = "BTN_STOP";
            this.BTN_STOP.Size = new System.Drawing.Size(120, 29);
            this.BTN_STOP.TabIndex = 16;
            this.BTN_STOP.Text = "Stop";
            this.BTN_STOP.UseVisualStyleBackColor = true;
            this.BTN_STOP.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // BTN_START
            // 
            this.BTN_START.Location = new System.Drawing.Point(18, 59);
            this.BTN_START.Name = "BTN_START";
            this.BTN_START.Size = new System.Drawing.Size(118, 29);
            this.BTN_START.TabIndex = 15;
            this.BTN_START.Text = "Start";
            this.BTN_START.UseVisualStyleBackColor = true;
            this.BTN_START.Click += new System.EventHandler(this.BTN_START_Click);
            // 
            // BTN_MEDIACLOSE
            // 
            this.BTN_MEDIACLOSE.Location = new System.Drawing.Point(152, 24);
            this.BTN_MEDIACLOSE.Name = "BTN_MEDIACLOSE";
            this.BTN_MEDIACLOSE.Size = new System.Drawing.Size(120, 29);
            this.BTN_MEDIACLOSE.TabIndex = 14;
            this.BTN_MEDIACLOSE.Text = "Media Close";
            this.BTN_MEDIACLOSE.UseVisualStyleBackColor = true;
            this.BTN_MEDIACLOSE.Click += new System.EventHandler(this.BTN_MEDIACLOSE_Click);
            // 
            // BTN_MEDIAOPEN
            // 
            this.BTN_MEDIAOPEN.Location = new System.Drawing.Point(18, 24);
            this.BTN_MEDIAOPEN.Name = "BTN_MEDIAOPEN";
            this.BTN_MEDIAOPEN.Size = new System.Drawing.Size(118, 29);
            this.BTN_MEDIAOPEN.TabIndex = 13;
            this.BTN_MEDIAOPEN.Text = "Media Open";
            this.BTN_MEDIAOPEN.UseVisualStyleBackColor = true;
            this.BTN_MEDIAOPEN.Click += new System.EventHandler(this.BTN_MEDIAOPEN_Click);
            // 
            // STR_STATUS
            // 
            this.STR_STATUS.AutoSize = true;
            this.STR_STATUS.Location = new System.Drawing.Point(12, 401);
            this.STR_STATUS.Name = "STR_STATUS";
            this.STR_STATUS.Size = new System.Drawing.Size(65, 12);
            this.STR_STATUS.TabIndex = 15;
            this.STR_STATUS.Text = "Status Log";
            // 
            // LIST_LOG
            // 
            this.LIST_LOG.FormattingEnabled = true;
            this.LIST_LOG.HorizontalScrollbar = true;
            this.LIST_LOG.ItemHeight = 12;
            this.LIST_LOG.Location = new System.Drawing.Point(7, 432);
            this.LIST_LOG.Name = "LIST_LOG";
            this.LIST_LOG.Size = new System.Drawing.Size(349, 160);
            this.LIST_LOG.TabIndex = 14;
            // 
            // axXnsSdkWindow
            // 
            this.axXnsSdkWindow.Enabled = true;
            this.axXnsSdkWindow.Location = new System.Drawing.Point(12, 12);
            this.axXnsSdkWindow.Name = "axXnsSdkWindow";
            this.axXnsSdkWindow.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow.OcxState")));
            this.axXnsSdkWindow.Size = new System.Drawing.Size(438, 380);
            this.axXnsSdkWindow.TabIndex = 1;
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(141, 401);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(67, 21);
            this.axXnsSdkDevice.TabIndex = 0;
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            this.axXnsSdkDevice.OnNewMedia += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnNewMediaEventHandler(this.axXnsSdkDevice_OnNewMedia);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(366, 401);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(105, 12);
            this.label1.TabIndex = 17;
            this.label1.Text = "Support MetaData";
            // 
            // LIST_META_DATA
            // 
            this.LIST_META_DATA.FormattingEnabled = true;
            this.LIST_META_DATA.HorizontalScrollbar = true;
            this.LIST_META_DATA.ItemHeight = 12;
            this.LIST_META_DATA.Location = new System.Drawing.Point(368, 432);
            this.LIST_META_DATA.Name = "LIST_META_DATA";
            this.LIST_META_DATA.Size = new System.Drawing.Size(374, 160);
            this.LIST_META_DATA.TabIndex = 16;
            // 
            // CHECKBOX_SUNAPI
            // 
            this.CHECKBOX_SUNAPI.Location = new System.Drawing.Point(86, 54);
            this.CHECKBOX_SUNAPI.Name = "CHECKBOX_SUNAPI";
            this.CHECKBOX_SUNAPI.Size = new System.Drawing.Size(78, 24);
            this.CHECKBOX_SUNAPI.TabIndex = 28;
            this.CHECKBOX_SUNAPI.Text = "SUNAPI";
            this.CHECKBOX_SUNAPI.UseVisualStyleBackColor = true;
            // 
            // MetaDataForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(752, 605);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.LIST_META_DATA);
            this.Controls.Add(this.STR_STATUS);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.GROUP_LIVE);
            this.Controls.Add(this.GROUP_CONNECTION_INFO);
            this.Controls.Add(this.axXnsSdkWindow);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Name = "MetaDataForm";
            this.Text = "MetaData";
            this.Load += new System.EventHandler(this.MetaDataForm_Load);
            this.GROUP_CONNECTION_INFO.ResumeLayout(false);
            this.GROUP_CONNECTION_INFO.PerformLayout();
            this.GROUP_LIVE.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxXNSSDKDEVICELib.AxXnsSdkDevice axXnsSdkDevice;
        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow;
        private System.Windows.Forms.GroupBox GROUP_CONNECTION_INFO;
        private System.Windows.Forms.TextBox EDIT_HTTPPORT;
        private System.Windows.Forms.Label STR_HTTPPORT;
        private System.Windows.Forms.Label STR_PROTOCOL;
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
        private System.Windows.Forms.GroupBox GROUP_LIVE;
        private System.Windows.Forms.Button BTN_STOP;
        private System.Windows.Forms.Button BTN_START;
        private System.Windows.Forms.Button BTN_MEDIACLOSE;
        private System.Windows.Forms.Button BTN_MEDIAOPEN;
        private System.Windows.Forms.Label STR_STATUS;
        private System.Windows.Forms.ListBox LIST_LOG;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox LIST_META_DATA;
        private System.Windows.Forms.CheckBox CHECKBOX_SUNAPI;
    }
}

