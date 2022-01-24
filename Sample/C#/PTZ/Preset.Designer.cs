namespace PTZ
{
    partial class Preset
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
            this.LISTVIEW = new System.Windows.Forms.ListView();
            this.COMBO_INDEX = new System.Windows.Forms.ComboBox();
            this.EIDT_PRESET_NAME = new System.Windows.Forms.TextBox();
            this.BTN_SAVE = new System.Windows.Forms.Button();
            this.BTN_DELETEALL = new System.Windows.Forms.Button();
            this.BTN_DELETE = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // LISTVIEW
            // 
            this.LISTVIEW.FullRowSelect = true;
            this.LISTVIEW.Location = new System.Drawing.Point(12, 10);
            this.LISTVIEW.Name = "LISTVIEW";
            this.LISTVIEW.Size = new System.Drawing.Size(327, 398);
            this.LISTVIEW.TabIndex = 0;
            this.LISTVIEW.UseCompatibleStateImageBehavior = false;
            this.LISTVIEW.DoubleClick += new System.EventHandler(this.LISTVIEW_DoubleClick);
            // 
            // COMBO_INDEX
            // 
            this.COMBO_INDEX.FormattingEnabled = true;
            this.COMBO_INDEX.Items.AddRange(new object[] {
            "None",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15",
            "16",
            "17",
            "18",
            "19",
            "20"});
            this.COMBO_INDEX.Location = new System.Drawing.Point(12, 414);
            this.COMBO_INDEX.Name = "COMBO_INDEX";
            this.COMBO_INDEX.Size = new System.Drawing.Size(58, 20);
            this.COMBO_INDEX.TabIndex = 1;
            // 
            // EIDT_PRESET_NAME
            // 
            this.EIDT_PRESET_NAME.Location = new System.Drawing.Point(76, 414);
            this.EIDT_PRESET_NAME.Name = "EIDT_PRESET_NAME";
            this.EIDT_PRESET_NAME.Size = new System.Drawing.Size(170, 21);
            this.EIDT_PRESET_NAME.TabIndex = 2;
            // 
            // BTN_SAVE
            // 
            this.BTN_SAVE.Location = new System.Drawing.Point(252, 414);
            this.BTN_SAVE.Name = "BTN_SAVE";
            this.BTN_SAVE.Size = new System.Drawing.Size(86, 21);
            this.BTN_SAVE.TabIndex = 3;
            this.BTN_SAVE.Text = "Save";
            this.BTN_SAVE.UseVisualStyleBackColor = true;
            this.BTN_SAVE.Click += new System.EventHandler(this.BTN_SAVE_Click);
            // 
            // BTN_DELETEALL
            // 
            this.BTN_DELETEALL.Location = new System.Drawing.Point(252, 441);
            this.BTN_DELETEALL.Name = "BTN_DELETEALL";
            this.BTN_DELETEALL.Size = new System.Drawing.Size(86, 20);
            this.BTN_DELETEALL.TabIndex = 4;
            this.BTN_DELETEALL.Text = "Delete All";
            this.BTN_DELETEALL.UseVisualStyleBackColor = true;
            this.BTN_DELETEALL.Click += new System.EventHandler(this.BTN_DELETEALL_Click);
            // 
            // BTN_DELETE
            // 
            this.BTN_DELETE.Location = new System.Drawing.Point(160, 441);
            this.BTN_DELETE.Name = "BTN_DELETE";
            this.BTN_DELETE.Size = new System.Drawing.Size(86, 20);
            this.BTN_DELETE.TabIndex = 5;
            this.BTN_DELETE.Text = "Delete";
            this.BTN_DELETE.UseVisualStyleBackColor = true;
            this.BTN_DELETE.Click += new System.EventHandler(this.BTN_DELETE_Click);
            // 
            // Preset
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(351, 473);
            this.Controls.Add(this.BTN_DELETE);
            this.Controls.Add(this.BTN_DELETEALL);
            this.Controls.Add(this.BTN_SAVE);
            this.Controls.Add(this.EIDT_PRESET_NAME);
            this.Controls.Add(this.COMBO_INDEX);
            this.Controls.Add(this.LISTVIEW);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Preset";
            this.Text = "Preset Form";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView LISTVIEW;
        private System.Windows.Forms.ComboBox COMBO_INDEX;
        private System.Windows.Forms.TextBox EIDT_PRESET_NAME;
        private System.Windows.Forms.Button BTN_SAVE;
        private System.Windows.Forms.Button BTN_DELETEALL;
        private System.Windows.Forms.Button BTN_DELETE;

    }
}