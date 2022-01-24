namespace BackupEx
{
    partial class BackupSearch
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.dateTimePicker_Date = new System.Windows.Forms.DateTimePicker();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.dateTimePicker_StartTime = new System.Windows.Forms.DateTimePicker();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.dateTimePicker_EndTime = new System.Windows.Forms.DateTimePicker();
            this.PROGRESSBAR = new System.Windows.Forms.ProgressBar();
            this.BTN_START = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.RADIO_SEC = new System.Windows.Forms.RadioButton();
            this.RADIO_REC = new System.Windows.Forms.RadioButton();
            this.label1 = new System.Windows.Forms.Label();
            this.SPIN_CH = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SPIN_CH)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.dateTimePicker_Date);
            this.groupBox1.Location = new System.Drawing.Point(11, 11);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(170, 51);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Select Day";
            // 
            // dateTimePicker_Date
            // 
            this.dateTimePicker_Date.Location = new System.Drawing.Point(6, 20);
            this.dateTimePicker_Date.Name = "dateTimePicker_Date";
            this.dateTimePicker_Date.Size = new System.Drawing.Size(157, 21);
            this.dateTimePicker_Date.TabIndex = 0;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.dateTimePicker_StartTime);
            this.groupBox2.Location = new System.Drawing.Point(11, 68);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(170, 51);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Start Time";
            // 
            // dateTimePicker_StartTime
            // 
            this.dateTimePicker_StartTime.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.dateTimePicker_StartTime.Location = new System.Drawing.Point(6, 20);
            this.dateTimePicker_StartTime.Name = "dateTimePicker_StartTime";
            this.dateTimePicker_StartTime.Size = new System.Drawing.Size(157, 21);
            this.dateTimePicker_StartTime.TabIndex = 0;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.dateTimePicker_EndTime);
            this.groupBox3.Location = new System.Drawing.Point(11, 125);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(170, 51);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "End Time";
            // 
            // dateTimePicker_EndTime
            // 
            this.dateTimePicker_EndTime.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.dateTimePicker_EndTime.Location = new System.Drawing.Point(6, 20);
            this.dateTimePicker_EndTime.Name = "dateTimePicker_EndTime";
            this.dateTimePicker_EndTime.Size = new System.Drawing.Size(157, 21);
            this.dateTimePicker_EndTime.TabIndex = 0;
            // 
            // PROGRESSBAR
            // 
            this.PROGRESSBAR.Location = new System.Drawing.Point(11, 183);
            this.PROGRESSBAR.Name = "PROGRESSBAR";
            this.PROGRESSBAR.Size = new System.Drawing.Size(228, 35);
            this.PROGRESSBAR.TabIndex = 3;
            // 
            // BTN_START
            // 
            this.BTN_START.Location = new System.Drawing.Point(245, 183);
            this.BTN_START.Name = "BTN_START";
            this.BTN_START.Size = new System.Drawing.Size(85, 34);
            this.BTN_START.TabIndex = 4;
            this.BTN_START.Text = "Start";
            this.BTN_START.UseVisualStyleBackColor = true;
            this.BTN_START.Click += new System.EventHandler(this.BTN_START_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.groupBox5);
            this.groupBox4.Controls.Add(this.label1);
            this.groupBox4.Controls.Add(this.SPIN_CH);
            this.groupBox4.Location = new System.Drawing.Point(187, 11);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(142, 164);
            this.groupBox4.TabIndex = 5;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Setting";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.RADIO_SEC);
            this.groupBox5.Controls.Add(this.RADIO_REC);
            this.groupBox5.Location = new System.Drawing.Point(8, 57);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(128, 97);
            this.groupBox5.TabIndex = 2;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "File Format";
            // 
            // RADIO_SEC
            // 
            this.RADIO_SEC.AutoSize = true;
            this.RADIO_SEC.Location = new System.Drawing.Point(41, 62);
            this.RADIO_SEC.Name = "RADIO_SEC";
            this.RADIO_SEC.Size = new System.Drawing.Size(48, 16);
            this.RADIO_SEC.TabIndex = 1;
            this.RADIO_SEC.Text = "SEC";
            this.RADIO_SEC.UseVisualStyleBackColor = true;
            this.RADIO_SEC.CheckedChanged += new System.EventHandler(this.RADIO_SEC_CheckedChanged);
            // 
            // RADIO_REC
            // 
            this.RADIO_REC.AutoSize = true;
            this.RADIO_REC.Checked = true;
            this.RADIO_REC.Location = new System.Drawing.Point(41, 29);
            this.RADIO_REC.Name = "RADIO_REC";
            this.RADIO_REC.Size = new System.Drawing.Size(48, 16);
            this.RADIO_REC.TabIndex = 0;
            this.RADIO_REC.TabStop = true;
            this.RADIO_REC.Text = "REC";
            this.RADIO_REC.UseVisualStyleBackColor = true;
            this.RADIO_REC.CheckedChanged += new System.EventHandler(this.RADIO_REC_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(21, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "Ch";
            // 
            // SPIN_CH
            // 
            this.SPIN_CH.Location = new System.Drawing.Point(33, 19);
            this.SPIN_CH.Maximum = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.SPIN_CH.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.SPIN_CH.Name = "SPIN_CH";
            this.SPIN_CH.Size = new System.Drawing.Size(99, 21);
            this.SPIN_CH.TabIndex = 0;
            this.SPIN_CH.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 223);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(156, 12);
            this.label2.TabIndex = 6;
            this.label2.Text = "File Name : C:\\BackupEx";
            // 
            // BackupSearch
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(337, 240);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.BTN_START);
            this.Controls.Add(this.PROGRESSBAR);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "BackupSearch";
            this.Text = "BackupSearch";
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SPIN_CH)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.DateTimePicker dateTimePicker_Date;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.DateTimePicker dateTimePicker_StartTime;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.DateTimePicker dateTimePicker_EndTime;
        public System.Windows.Forms.ProgressBar PROGRESSBAR;
        public System.Windows.Forms.Button BTN_START;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown SPIN_CH;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.RadioButton RADIO_SEC;
        private System.Windows.Forms.RadioButton RADIO_REC;
    }
}