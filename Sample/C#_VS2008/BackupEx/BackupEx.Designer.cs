namespace BackupEx
{
    partial class BackupExDlg
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BackupExDlg));
            this.axXnsSdkDevice = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            this.axXnsSdkWindow = new AxXNSSDKWINDOWLib.AxXnsSdkWindow();
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
            this.GROUP_LIVE = new System.Windows.Forms.GroupBox();
            this.BTN_STOP = new System.Windows.Forms.Button();
            this.BTN_START = new System.Windows.Forms.Button();
            this.BTN_MEDIACLOSE = new System.Windows.Forms.Button();
            this.BTN_MEDIAOPEN = new System.Windows.Forms.Button();
            this.LIST_LOG = new System.Windows.Forms.ListBox();
            this.STR_STATUS = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.BTN_REC_PLAY = new System.Windows.Forms.Button();
            this.BTN_BACKUP = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).BeginInit();
            this.GROUP_CONNECTION_INFO.SuspendLayout();
            this.GROUP_LIVE.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // axXnsSdkDevice
            // 
            this.axXnsSdkDevice.Enabled = true;
            this.axXnsSdkDevice.Location = new System.Drawing.Point(598, 357);
            this.axXnsSdkDevice.Name = "axXnsSdkDevice";
            this.axXnsSdkDevice.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice.OcxState")));
            this.axXnsSdkDevice.Size = new System.Drawing.Size(87, 15);
            this.axXnsSdkDevice.TabIndex = 0;
            this.axXnsSdkDevice.OnDeviceStatusChanged += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnDeviceStatusChangedEventHandler(this.axXnsSdkDevice_OnDeviceStatusChanged);
            this.axXnsSdkDevice.OnBackupProgress += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnBackupProgressEventHandler(this.axXnsSdkDevice_OnBackupProgress);
            this.axXnsSdkDevice.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice_OnConnectFailed);
            // 
            // axXnsSdkWindow
            // 
            this.axXnsSdkWindow.Enabled = true;
            this.axXnsSdkWindow.Location = new System.Drawing.Point(12, 12);
            this.axXnsSdkWindow.Name = "axXnsSdkWindow";
            this.axXnsSdkWindow.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkWindow.OcxState")));
            this.axXnsSdkWindow.Size = new System.Drawing.Size(440, 339);
            this.axXnsSdkWindow.TabIndex = 1;
            this.axXnsSdkWindow.OnMediaOff += new System.EventHandler(this.axXnsSdkWindow_OnMediaOff);
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
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_IPADDRESS);
            this.GROUP_CONNECTION_INFO.Controls.Add(this.STR_MODEL);
            this.GROUP_CONNECTION_INFO.Location = new System.Drawing.Point(458, 12);
            this.GROUP_CONNECTION_INFO.Name = "GROUP_CONNECTION_INFO";
            this.GROUP_CONNECTION_INFO.Size = new System.Drawing.Size(228, 199);
            this.GROUP_CONNECTION_INFO.TabIndex = 2;
            this.GROUP_CONNECTION_INFO.TabStop = false;
            this.GROUP_CONNECTION_INFO.Text = "Connection Information";
            // 
            // BTN_DISCONNECT
            // 
            this.BTN_DISCONNECT.Location = new System.Drawing.Point(120, 172);
            this.BTN_DISCONNECT.Name = "BTN_DISCONNECT";
            this.BTN_DISCONNECT.Size = new System.Drawing.Size(90, 21);
            this.BTN_DISCONNECT.TabIndex = 12;
            this.BTN_DISCONNECT.Text = "DisConnect";
            this.BTN_DISCONNECT.UseVisualStyleBackColor = true;
            this.BTN_DISCONNECT.Click += new System.EventHandler(this.BTN_DISCONNECT_Click);
            // 
            // BTN_CONNECT
            // 
            this.BTN_CONNECT.Location = new System.Drawing.Point(14, 172);
            this.BTN_CONNECT.Name = "BTN_CONNECT";
            this.BTN_CONNECT.Size = new System.Drawing.Size(90, 21);
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
            this.COMBO_MODELLIST.Size = new System.Drawing.Size(124, 20);
            this.COMBO_MODELLIST.TabIndex = 10;
            // 
            // EDIT_PW
            // 
            this.EDIT_PW.Location = new System.Drawing.Point(86, 137);
            this.EDIT_PW.Name = "EDIT_PW";
            this.EDIT_PW.Size = new System.Drawing.Size(124, 21);
            this.EDIT_PW.TabIndex = 9;
            this.EDIT_PW.UseSystemPasswordChar = true;
            // 
            // EDIT_ID
            // 
            this.EDIT_ID.Location = new System.Drawing.Point(86, 110);
            this.EDIT_ID.Name = "EDIT_ID";
            this.EDIT_ID.Size = new System.Drawing.Size(124, 21);
            this.EDIT_ID.TabIndex = 8;
            // 
            // EDIT_PORT
            // 
            this.EDIT_PORT.Location = new System.Drawing.Point(86, 83);
            this.EDIT_PORT.Name = "EDIT_PORT";
            this.EDIT_PORT.Size = new System.Drawing.Size(124, 21);
            this.EDIT_PORT.TabIndex = 7;
            // 
            // EDIT_IP
            // 
            this.EDIT_IP.Location = new System.Drawing.Point(86, 56);
            this.EDIT_IP.Name = "EDIT_IP";
            this.EDIT_IP.Size = new System.Drawing.Size(124, 21);
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
            // GROUP_LIVE
            // 
            this.GROUP_LIVE.Controls.Add(this.BTN_STOP);
            this.GROUP_LIVE.Controls.Add(this.BTN_START);
            this.GROUP_LIVE.Controls.Add(this.BTN_MEDIACLOSE);
            this.GROUP_LIVE.Controls.Add(this.BTN_MEDIAOPEN);
            this.GROUP_LIVE.Location = new System.Drawing.Point(458, 217);
            this.GROUP_LIVE.Name = "GROUP_LIVE";
            this.GROUP_LIVE.Size = new System.Drawing.Size(228, 76);
            this.GROUP_LIVE.TabIndex = 3;
            this.GROUP_LIVE.TabStop = false;
            this.GROUP_LIVE.Text = "Live Control";
            // 
            // BTN_STOP
            // 
            this.BTN_STOP.Location = new System.Drawing.Point(118, 45);
            this.BTN_STOP.Name = "BTN_STOP";
            this.BTN_STOP.Size = new System.Drawing.Size(91, 20);
            this.BTN_STOP.TabIndex = 16;
            this.BTN_STOP.Text = "Stop";
            this.BTN_STOP.UseVisualStyleBackColor = true;
            this.BTN_STOP.Click += new System.EventHandler(this.BTN_STOP_Click);
            // 
            // BTN_START
            // 
            this.BTN_START.Location = new System.Drawing.Point(13, 45);
            this.BTN_START.Name = "BTN_START";
            this.BTN_START.Size = new System.Drawing.Size(89, 20);
            this.BTN_START.TabIndex = 15;
            this.BTN_START.Text = "Start";
            this.BTN_START.UseVisualStyleBackColor = true;
            this.BTN_START.Click += new System.EventHandler(this.BTN_START_Click);
            // 
            // BTN_MEDIACLOSE
            // 
            this.BTN_MEDIACLOSE.Location = new System.Drawing.Point(118, 20);
            this.BTN_MEDIACLOSE.Name = "BTN_MEDIACLOSE";
            this.BTN_MEDIACLOSE.Size = new System.Drawing.Size(91, 19);
            this.BTN_MEDIACLOSE.TabIndex = 14;
            this.BTN_MEDIACLOSE.Text = "Media Close";
            this.BTN_MEDIACLOSE.UseVisualStyleBackColor = true;
            this.BTN_MEDIACLOSE.Click += new System.EventHandler(this.BTN_MEDIACLOSE_Click);
            // 
            // BTN_MEDIAOPEN
            // 
            this.BTN_MEDIAOPEN.Location = new System.Drawing.Point(13, 20);
            this.BTN_MEDIAOPEN.Name = "BTN_MEDIAOPEN";
            this.BTN_MEDIAOPEN.Size = new System.Drawing.Size(89, 19);
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
            this.LIST_LOG.Size = new System.Drawing.Size(673, 160);
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
            this.groupBox1.Controls.Add(this.BTN_REC_PLAY);
            this.groupBox1.Controls.Add(this.BTN_BACKUP);
            this.groupBox1.Location = new System.Drawing.Point(458, 299);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(227, 51);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Backup";
            // 
            // BTN_REC_PLAY
            // 
            this.BTN_REC_PLAY.Location = new System.Drawing.Point(118, 20);
            this.BTN_REC_PLAY.Name = "BTN_REC_PLAY";
            this.BTN_REC_PLAY.Size = new System.Drawing.Size(91, 20);
            this.BTN_REC_PLAY.TabIndex = 18;
            this.BTN_REC_PLAY.Text = "Rec Play";
            this.BTN_REC_PLAY.UseVisualStyleBackColor = true;
            this.BTN_REC_PLAY.Click += new System.EventHandler(this.BTN_REC_PLAY_Click);
            // 
            // BTN_BACKUP
            // 
            this.BTN_BACKUP.Location = new System.Drawing.Point(13, 20);
            this.BTN_BACKUP.Name = "BTN_BACKUP";
            this.BTN_BACKUP.Size = new System.Drawing.Size(89, 20);
            this.BTN_BACKUP.TabIndex = 17;
            this.BTN_BACKUP.Text = "Backup";
            this.BTN_BACKUP.UseVisualStyleBackColor = true;
            this.BTN_BACKUP.Click += new System.EventHandler(this.BTN_BACKUP_Click);
            // 
            // BackupExDlg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(697, 551);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.axXnsSdkDevice);
            this.Controls.Add(this.STR_STATUS);
            this.Controls.Add(this.LIST_LOG);
            this.Controls.Add(this.GROUP_LIVE);
            this.Controls.Add(this.GROUP_CONNECTION_INFO);
            this.Controls.Add(this.axXnsSdkWindow);
            this.Name = "BackupExDlg";
            this.Text = "BackupEx";
            this.Load += new System.EventHandler(this.BackupExDlg_Load);
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkWindow)).EndInit();
            this.GROUP_CONNECTION_INFO.ResumeLayout(false);
            this.GROUP_CONNECTION_INFO.PerformLayout();
            this.GROUP_LIVE.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
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
        private System.Windows.Forms.TextBox EDIT_PORT;
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
        private System.Windows.Forms.Button BTN_REC_PLAY;
        private System.Windows.Forms.Button BTN_BACKUP;
    }
}

