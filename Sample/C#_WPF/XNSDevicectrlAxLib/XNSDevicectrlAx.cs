using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace XNSDevicectrlAxLib
{
    public partial class XNSDevicectrlAx : UserControl
    {
        public XNSDevicectrlAx()
        {
            InitializeComponent();
        }

        private void axXnsSdkDevice1_OnConnectFailed(object sender, AxXNSSDKDEVICELib._DXnsSdkDeviceEvents_OnConnectFailedEvent e)
        {
            Debug.WriteLine("Connect Fail " + e.nDeviceID);
        }
    }
}
