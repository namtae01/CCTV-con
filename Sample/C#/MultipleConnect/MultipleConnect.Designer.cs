namespace MultipleConnect
{
    partial class MultipleConnectForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MultipleConnectForm));
            this.GROUP_CONNECTION_INFO = new System.Windows.Forms.GroupBox();
            this.CHECKBOX_SUNAPI = new System.Windows.Forms.CheckBox();
            this.EDIT_HTTPPORT = new System.Windows.Forms.TextBox();
            this.STR_HTTPPORT = new System.Windows.Forms.Label();
            this.STR_PROTOCOL = new System.Windows.Forms.Label();
            this.COMBO_MODELLIST = new System.Windows.Forms.ComboBox();
            this.EDIT_PW = new System.Windows.Forms.TextBox();
            this.EDIT_ID = new System.Windows.Forms.TextBox();
            this.BTN_REMOVE = new System.Windows.Forms.Button();
            this.BTN_ADD = new System.Windows.Forms.Button();
            this.EDIT_PORT = new System.Windows.Forms.TextBox();
            this.EDIT_IP = new System.Windows.Forms.TextBox();
            this.STR_PW = new System.Windows.Forms.Label();
            this.STR_ID = new System.Windows.Forms.Label();
            this.STR_PORT = new System.Windows.Forms.Label();
            this.STR_IPADDRESS = new System.Windows.Forms.Label();
            this.STR_MODEL = new System.Windows.Forms.Label();
            this.BTN_DISCONNECT = new System.Windows.Forms.Button();
            this.BTN_CONNECT = new System.Windows.Forms.Button();
            this.GROUP_LIVE = new System.Windows.Forms.GroupBox();
            this.BTN_STOP = new System.Windows.Forms.Button();
            this.BTN_PLAY = new System.Windows.Forms.Button();
            this.LIST_LOG = new System.Windows.Forms.ListBox();
            this.STR_STATUS = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.STR_DEVICE1 = new System.Windows.Forms.Label();
            this.STR_DEVICE2 = new System.Windows.Forms.Label();
            this.STR_DEVICE3 = new System.Windows.Forms.Label();
            this.STR_DEVICE4 = new System.Windows.Forms.Label();
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.axXnsSdkWindow4 = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.axXnsSdkWindow3 = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.axXnsSdkWindow2 = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.axXnsSdkWindow1 = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
            this.LISTVIEW_DEVICE = new System.Windows.Forms.ListView();
            this.No = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Model = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.IP = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Port = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ID = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PW = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.GROUP_CONNECTION_INFO.SuspendLayout();
            this.GROUP_LIVE.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow1)).BeginInit();
            this.SuspendLayout();
            // 
            // GROUP_CONNECTION_INFO
            // 
            this.GROUP_CONNECTION_INFO.Controls.Add(this.CHECKBOX_SUNAPI);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_HTTPPORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_HTTPPORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_PROTOCOL);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.COMBO_MODELLIST);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_PW);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_ID);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_REMOVE);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.BTN_ADD);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_PORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.EDIT_IP);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_PW);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_ID);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_PORT);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_IPADDRESS);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_MODEL);
            this.GROUP_CONNECTION_INFO.Location = new System.Drawing.Point(420, 12);
            this.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO";
            this.GROUP_CONNECTION_INFO.Size = new System.Drawing.Size(359, 262);
            this.GROUP_CONNECTION_INFO.TabIndex = 3;
            this.GROUP_CONNECTION_INFO.TabStop = false;
            this.GROUP_CONNECTION_INFO.Text = "Connection Information";
            // 
            // CHECKBOX_SUNAPI
            // 
            this.CHECKBOX_SUNAPI.Location = new System.Drawing.Point(101, 54);
            this.CHECKBOX_SUNAPI.Name = "CHECKBOX_SUNAPI";
            this.CHECKBOX_SUNAPI.Size = new System.Drawing.Size(78, 24);
            this.CHECKBOX_SUNAPI.TabIndex = 22;
            this.CHECKBOX_SUNAPI.Text = "SUNAPI";
            this.CHECKBOX_SUNAPI.UseVisualStyleBackColor = true;
            // 
            // EDIT_HTTPPORT
            // 
            this.EDIT_HTTPPORT.Location = new System.Drawing.Point(101, 135);
            this.EDIT_HTTPPORT.Name = "EDIT_HTTPPORT";
            this.EDIT_HTTPPORT.Size = new System.Drawing.Size(239, 21);
            this.EDIT_HTTPPORT.TabIndex = 17;
            // 
            // STR_HTTPPORT
            // 
            this.STR_HTTPPORT.AutoSize = true;
            this.STR_HTTPPORT.Location = new System.Drawing.Point(12, 140);
            this.STR_HTTPPORT.Name = "STR_HTTPPORT";
            this.STR_HTTPPORT.Size = new System.Drawing.Size(63, 12);
            this.STR_HTTPPORT.TabIndex = 16;
            this.STR_HTTPPORT.Text = "HTTP Port";
            // 
            // STR_PROTOCOL
            // 
            this.STR_PROTOCOL.AutoSize = true;
            this.STR_PROTOCOL.Location = new System.Drawing.Point(12, 59);
            this.STR_PROTOCOL.Name = "STR_PROTOCOL";
            this.STR_PROTOCOL.Size = new System.Drawing.Size(51, 12);
            this.STR_PROTOCOL.TabIndex = 14;
            this.STR_PROTOCOL.Text = "Protocol";
            // 
            // COMBO_MODELLIST
            // 
            this.COMBO_MODELLIST.FormattingEnabled = true;
            this.COMBO_MODELLIST.Location = new System.Drawing.Point(101, 29);
            this.COMBO_MODELLIST.MaxDropDownItems = 15;
            this.COMBO_MODELLIST.Name = "COMBO_MODELLIST";
            this.COMBO_MODELLIST.Size = new System.Drawing.Size(239, 20);
            this.COMBO_MODELLIST.TabIndex = 10;
            // 
            // EDIT_PW
            // 
            this.EDIT_PW.Location = new System.Drawing.Point(101, 189);
            this.EDIT_PW.Name = "EDIT_PW";
            this.EDIT_PW.Size = new System.Drawing.Size(239, 21);
            this.EDIT_PW.TabIndex = 9;
            this.EDIT_PW.UseSystemPasswordChar = true;
            // 
            // EDIT_ID
            // 
            this.EDIT_ID.Location = new System.Drawing.Point(101, 162);
            this.EDIT_ID.Name = "EDIT_ID";
            this.EDIT_ID.Size = new System.Drawing.Size(239, 21);
            this.EDIT_ID.TabIndex = 8;
            // 
            // BTN_REMOVE
            // 
            this.BTN_REMOVE.Location = new System.Drawing.Point(192, 224);
            this.BTN_REMOVE.Name = "BTN_REMOVE";
            this.BTN_REMOVE.Size = new System.Drawing.Size(148, 23);
            this.BTN_REMOVE.TabIndex = 13;
            this.BTN_REMOVE.Text = "REMOVE";
            this.BTN_REMOVE.UseVisualStyleBackColor = true;
            this.BTN_REMOVE.Click += new System.EventHandler(this.BTN_REMOVE_Click);
            // 
            // BTN_ADD
            // 
            this.BTN_ADD.Location = new System.Drawing.Point(15, 224);
            this.BTN_ADD.Name = "BTN_ADD";
            this.BTN_ADD.Size = new System.Drawing.Size(148, 23);
            this.BTN_ADD.TabIndex = 13;
            this.BTN_ADD.Text = "ADD";
            this.BTN_ADD.UseVisualStyleBackColor = true;
            this.BTN_ADD.Click += new System.EventHandler(this.BTN_ADD_Click);
            // 
            // EDIT_PORT
            // 
            this.EDIT_PORT.Location = new System.Drawing.Point(101, 108);
            this.EDIT_PORT.Name = "EDIT_PORT";
            this.EDIT_PORT.Size = new System.Drawing.Size(239, 21);
            this.EDIT_PORT.TabIndex = 7;
            // 
            // EDIT_IP
            // 
            this.EDIT_IP.Location = new System.Drawing.Point(101, 81);
            this.EDIT_IP.Name = "EDIT_IP";
            this.EDIT_IP.Size = new System.Drawing.Size(239, 21);
            this.EDIT_IP.TabIndex = 6;
            // 
            // STR_PW
            // 
            this.STR_PW.AutoSize = true;
            this.STR_PW.Location = new System.Drawing.Point(13, 193);
            this.STR_PW.Name = "STR_PW";
            this.STR_PW.Size = new System.Drawing.Size(47, 12);
            this.STR_PW.TabIndex = 4;
            this.STR_PW.Text = "PW      ";
            // 
            // STR_ID
            // 
            this.STR_ID.AutoSize = true;
            this.STR_ID.Location = new System.Drawing.Point(12, 167);
            this.STR_ID.Name = "STR_ID";
            this.STR_ID.Size = new System.Drawing.Size(48, 12);
            this.STR_ID.TabIndex = 3;
            this.STR_ID.Text = "ID        ";
            // 
            // STR_PORT
            // 
            this.STR_PORT.AutoSize = true;
            this.STR_PORT.Location = new System.Drawing.Point(12, 113);
            this.STR_PORT.Name = "STR_PORT";
            this.STR_PORT.Size = new System.Drawing.Size(69, 12);
            this.STR_PORT.TabIndex = 2;
            this.STR_PORT.Text = "Device Port";
            // 
            // STR_IPADDRESS
            // 
            this.STR_IPADDRESS.AutoSize = true;
            this.STR_IPADDRESS.Location = new System.Drawing.Point(12, 86);
            this.STR_IPADDRESS.Name = "STR_IPADDRESS";
            this.STR_IPADDRESS.Size = new System.Drawing.Size(60, 12);
            this.STR_IPADDRESS.TabIndex = 1;
            this.STR_IPADDRESS.Text = "IP           ";
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
            // BTN_DISCONNECT
            // 
            this.BTN_DISCONNECT.Location = new System.Drawing.Point(195, 32);
            this.BTN_DISCONNECT.Name = "BTN_DISCONNECT";
            this.BTN_DISCONNECT.Size = new System.Drawing.Size(147, 25);
            this.BTN_DISCONNECT.TabIndex = 12;
            this.BTN_DISCONNECT.Text = "Disconnect";
            this.BTN_DISCONNECT.UseVisualStyleBackColor = true;
            this.BTN_DISCONNECT.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // BTN_CONNECT
            // 
            this.BTN_CONNECT.Location = new System.Drawing.Point(15, 32);
            this.BTN_CONNECT.Name = "BTN_CONNECT";
            this.BTN_CONNECT.Size = new System.Drawing.Size(148, 25);
            this.BTN_CONNECT.TabIndex = 11;
            this.BTN_CONNECT.Text = "Connect";
            this.BTN_CONNECT.UseVisualStyleBackColor = true;
            this.BTN_CONNECT.Click += new System.EventHandler(this.BTN_CONNECT_Click);
            // 
            // GROUP_LIVE
            // 
            this.GROUP_LIVE.Controls.Add(this.BTN_DISCONNECT);
            this.GROUP_LIVE.Controls.Add(this.BTN_STOP);
            this.GROUP_LIVE.Controls.Add(this.BTN_CONNECT);
            this.GROUP_LIVE.Controls.Add(this.BTN_PLAY);
            this.GROUP_LIVE.Location = new System.Drawing.Point(420, 477);
            this.GROUP_LIVE.Name = "GROUP_LIVE";
            this.GROUP_LIVE.Size = new System.Drawing.Size(359, 110);
            this.GROUP_LIVE.TabIndex = 4;
            this.GROUP_LIVE.TabStop = false;
            this.GROUP_LIVE.Text = "Live Control";
            // 
            // BTN_STOP
            // 
            this.BTN_STOP.Location = new System.Drawing.Point(194, 71);
            this.BTN_STOP.Name = "BTN_STOP";
            this.BTN_STOP.Size = new System.Drawing.Size(148, 25);
            this.BTN_STOP.TabIndex = 16;
            this.BTN_STOP.Text = "Stop";
            this.BTN_STOP.UseVisualStyleBackColor = true;
            this.BTN_STOP.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // BTN_PLAY
            // 
            this.BTN_PLAY.Location = new System.Drawing.Point(15, 71);
            this.BTN_PLAY.Name = "BTN_PLAY";
            this.BTN_PLAY.Size = new System.Drawing.Size(148, 25);
            this.BTN_PLAY.TabIndex = 15;
            this.BTN_PLAY.Text = "Play";
            this.BTN_PLAY.UseVisualStyleBackColor = true;
            this.BTN_PLAY.Click += new System.EventHandler(this.BTN_PLAY_Click);
            // 
            // LIST_LOG
            // 
            this.LIST_LOG.FormattingEnabled = true;
            this.LIST_LOG.ItemHeight = 12;
            this.LIST_LOG.Location = new System.Drawing.Point(14, 391);
            this.LIST_LOG.Name = "LIST_LOG";
            this.LIST_LOG.Size = new System.Drawing.Size(389, 196);
            this.LIST_LOG.TabIndex = 5;
            // 
            // STR_STATUS
            // 
            this.STR_STATUS.AutoSize = true;
            this.STR_STATUS.Location = new System.Drawing.Point(11, 367);
            this.STR_STATUS.Name = "STR_STATUS";
            this.STR_STATUS.Size = new System.Drawing.Size(65, 12);
            this.STR_STATUS.TabIndex = 14;
            this.STR_STATUS.Text = "Status Log";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 15;
            this.label1.Text = "Status Log";
            // 
            // STR_DEVICE1
            // 
            this.STR_DEVICE1.AutoSize = true;
            this.STR_DEVICE1.Location = new System.Drawing.Point(12, 16);
            this.STR_DEVICE1.Name = "STR_DEVICE1";
            this.STR_DEVICE1.Size = new System.Drawing.Size(63, 12);
            this.STR_DEVICE1.TabIndex = 15;
            this.STR_DEVICE1.Text = "1st Device";
            // 
            // STR_DEVICE2
            // 
            this.STR_DEVICE2.AutoSize = true;
            this.STR_DEVICE2.Location = new System.Drawing.Point(210, 16);
            this.STR_DEVICE2.Name = "STR_DEVICE2";
            this.STR_DEVICE2.Size = new System.Drawing.Size(67, 12);
            this.STR_DEVICE2.TabIndex = 15;
            this.STR_DEVICE2.Text = "2nd Device";
            // 
            // STR_DEVICE3
            // 
            this.STR_DEVICE3.AutoSize = true;
            this.STR_DEVICE3.Location = new System.Drawing.Point(12, 184);
            this.STR_DEVICE3.Name = "STR_DEVICE3";
            this.STR_DEVICE3.Size = new System.Drawing.Size(64, 12);
            this.STR_DEVICE3.TabIndex = 15;
            this.STR_DEVICE3.Text = "3rd Device";
            // 
            // STR_DEVICE4
            // 
            this.STR_DEVICE4.AutoSize = true;
            this.STR_DEVICE4.Location = new System.Drawing.Point(210, 184);
            this.STR_DEVICE4.Name = "STR_DEVICE4";
            this.STR_DEVICE4.Size = new System.Drawing.Size(63, 12);
            this.STR_DEVICE4.TabIndex = 15;
            this.STR_DEVICE4.Text = "4th Device";
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(376, 362);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(27, 17);
            this.axXnsSdkDevice.TabIndex = 7;
            this.axXnsSdkDevice.Visible = false;
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            // 
            // axXnsSdkWindow4
            // 
            this.axXnsSdkWindow4.Enabled = true;
            this.axXnsSdkWindow4.Location = new System.Drawing.Point(212, 199);
            this.axXnsSdkWindow4.Name = "axXnsSdkWindow4";
            this.axXnsSdkWindow4.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow4.OcxState")));
            this.axXnsSdkWindow4.Size = new System.Drawing.Size(192, 144);
            this.axXnsSdkWindow4.TabIndex = 0;
            // 
            // axXnsSdkWindow3
            // 
            this.axXnsSdkWindow3.Enabled = true;
            this.axXnsSdkWindow3.Location = new System.Drawing.Point(14, 199);
            this.axXnsSdkWindow3.Name = "axXnsSdkWindow3";
            this.axXnsSdkWindow3.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow3.OcxState")));
            this.axXnsSdkWindow3.Size = new System.Drawing.Size(192, 144);
            this.axXnsSdkWindow3.TabIndex = 0;
            // 
            // axXnsSdkWindow2
            // 
            this.axXnsSdkWindow2.Enabled = true;
            this.axXnsSdkWindow2.Location = new System.Drawing.Point(212, 31);
            this.axXnsSdkWindow2.Name = "axXnsSdkWindow2";
            this.axXnsSdkWindow2.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow2.OcxState")));
            this.axXnsSdkWindow2.Size = new System.Drawing.Size(192, 144);
            this.axXnsSdkWindow2.TabIndex = 0;
            // 
            // axXnsSdkWindow1
            // 
            this.axXnsSdkWindow1.Enabled = true;
            this.axXnsSdkWindow1.Location = new System.Drawing.Point(14, 31);
            this.axXnsSdkWindow1.Name = "axXnsSdkWindow1";
            this.axXnsSdkWindow1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow1.OcxState")));
            this.axXnsSdkWindow1.Size = new System.Drawing.Size(192, 144);
            this.axXnsSdkWindow1.TabIndex = 0;
            // 
            // LISTVIEW_DEVICE
            // 
            this.LISTVIEW_DEVICE.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.No,
            this.Model,
            this.IP,
            this.Port,
            this.ID,
            this.PW});
            this.LISTVIEW_DEVICE.Font = new System.Drawing.Font("굴림", 7.5F);
            this.LISTVIEW_DEVICE.FullRowSelect = true;
            this.LISTVIEW_DEVICE.GridLines = true;
            this.LISTVIEW_DEVICE.Location = new System.Drawing.Point(420, 296);
            this.LISTVIEW_DEVICE.MultiSelect = false;
            this.LISTVIEW_DEVICE.Name = "LISTVIEW_DEVICE";
            this.LISTVIEW_DEVICE.Size = new System.Drawing.Size(359, 166);
            this.LISTVIEW_DEVICE.TabIndex = 16;
            this.LISTVIEW_DEVICE.UseCompatibleStateImageBehavior = false;
            this.LISTVIEW_DEVICE.View = System.Windows.Forms.View.Details;
            this.LISTVIEW_DEVICE.ItemSelectionChanged += new System.Windows.Forms.ListViewItemSelectionChangedEventHandler(this.LISTVIEW_DEVICE_ItemSelectionChanged);
            // 
            // No
            // 
            this.No.Text = "No";
            this.No.Width = 25;
            // 
            // Model
            // 
            this.Model.Text = "Model";
            this.Model.Width = 50;
            // 
            // IP
            // 
            this.IP.Text = "IP";
            this.IP.Width = 80;
            // 
            // Port
            // 
            this.Port.Text = "Port";
            this.Port.Width = 40;
            // 
            // ID
            // 
            this.ID.Text = "ID";
            this.ID.Width = 70;
            // 
            // PW
            // 
            this.PW.Text = "PW";
            this.PW.Width = 83;
            // 
            // MultipleConnectForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(791, 599);
            this.Controls.Add(this.LISTVIEW_DEVICE);
            this.Controls.Add(this.STR_DEVICE4);
            this.Controls.Add(this.STR_DEVICE3);
            this.Controls.Add(this.STR_DEVICE2);
            this.Controls.Add(this.STR_DEVICE1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.STR_STATUS);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.GROUP_LIVE);
            this.Controls.Add(this.GROUP_CONNECTION_INFO);
            this.Controls.Add(this.axXnsSdkWindow4);
            this.Controls.Add(this.axXnsSdkWindow3);
            this.Controls.Add(this.axXnsSdkWindow2);
            this.Controls.Add(this.axXnsSdkWindow1);
            this.Name = "MultipleConnectForm";
            this.Text = "MultipleConnect";
            this.Load += new System.EventHandler(this.MultipleConnectForm_Load);
            this.GROUP_CONNECTION_INFO.ResumeLayout(false);
            this.GROUP_CONNECTION_INFO.PerformLayout();
            this.GROUP_LIVE.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow1;
        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow2;
        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow3;
        private AxXNSSDKWINDOWLib.AxXnsSdkWindow axXnsSdkWindow4;
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
        private System.Windows.Forms.GroupBox GROUP_LIVE;
        private System.Windows.Forms.Button BTN_STOP;
        private System.Windows.Forms.Button BTN_PLAY;
        private System.Windows.Forms.Button BTN_ADD;
        private System.Windows.Forms.ListBox LIST_LOG;
        private AxXNSSDKDEVICELib.AxXnsSdkDevice axXnsSdkDevice;
        private System.Windows.Forms.Label STR_STATUS;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label STR_DEVICE1;
        private System.Windows.Forms.Label STR_DEVICE2;
        private System.Windows.Forms.Label STR_DEVICE3;
        private System.Windows.Forms.Label STR_DEVICE4;
        private System.Windows.Forms.Button BTN_REMOVE;
        private System.Windows.Forms.ListView LISTVIEW_DEVICE;
        private System.Windows.Forms.ColumnHeader No;
        private System.Windows.Forms.ColumnHeader Model;
        private System.Windows.Forms.ColumnHeader IP;
        private System.Windows.Forms.ColumnHeader Port;
        private System.Windows.Forms.ColumnHeader ID;
        private System.Windows.Forms.ColumnHeader PW;
        private System.Windows.Forms.TextBox EDIT_HTTPPORT;
        private System.Windows.Forms.Label STR_HTTPPORT;
        private System.Windows.Forms.Label STR_PROTOCOL;
        private System.Windows.Forms.CheckBox CHECKBOX_SUNAPI;
    }
}

