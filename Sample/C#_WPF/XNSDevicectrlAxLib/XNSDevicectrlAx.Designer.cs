﻿namespace XNSDevicectrlAxLib
{
    partial class XNSDevicectrlAx
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

        #region 구성 요소 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(XNSDevicectrlAx));
            this.axXnsSdkDevice1 = new AxXNSSDKDEVICELib.AxXnsSdkDevice();
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice1)).BeginInit();
            this.SuspendLayout();
            // 
            // axXnsSdkDevice1
            // 
            this.axXnsSdkDevice1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.axXnsSdkDevice1.Enabled = true;
            this.axXnsSdkDevice1.Location = new System.Drawing.Point(0, 0);
            this.axXnsSdkDevice1.Name = "axXnsSdkDevice1";
            this.axXnsSdkDevice1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axXnsSdkDevice1.OcxState")));
            this.axXnsSdkDevice1.Size = new System.Drawing.Size(47, 43);
            this.axXnsSdkDevice1.TabIndex = 0;
            this.axXnsSdkDevice1.OnConnectFailed += new AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEventHandler(this.axXnsSdkDevice1_OnConnectFailed);
            // 
            // XNSDevicectrlAx
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.axXnsSdkDevice1);
            this.Name = "XNSDevicectrlAx";
            this.Size = new System.Drawing.Size(47, 43);
            ((System.ComponentModel.ISupportInitialize)(this.axXnsSdkDevice1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private AxXNSSDKDEVICELib.AxXnsSdkDevice axXnsSdkDevice1;
    }
}
