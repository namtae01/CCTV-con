using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using XNSSAMPLELOGLib;

namespace XNSSAMPLELOGLib
{
    public class DebugLog
    {
        private ListBox LIST_LOG;

        public DebugLog(ListBox box)
        {
            LIST_LOG = box;
        }
        
        delegate void SetTextCallback(string text);

        //------------------------------------------------------------ ActiveX SDK Device Control Log
        public void WLOGD(string strFunc, string strMsg, int nRet, string strRet)
        {
            //[XnsSdkWindow] Function() Message (%d)[Message]
            string strMessage = "[XnsSdkDevice] ";
            if (LIST_LOG.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WLOGD);
                LIST_LOG.Invoke(d, new object[] {strFunc, strMsg, nRet, strRet });
            }
            else
            {
                int cnt = LIST_LOG.Items.Count;
                LIST_LOG.Items.Add(strMessage + " " + strFunc + " " + strMsg + " " + "(" + nRet.ToString() + ") " + "[" + strRet + "]");
                LIST_LOG.SetSelected(cnt, true);
            }
        }

        public void WLOGD(string strMsg, int nRet, string strRet)
        {
            //[XnsSdkDevice] Message (%d)[Message]
            string strMessage = "[XnsSdkDevice] ";
            if (LIST_LOG.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WLOGD);
                LIST_LOG.Invoke(d, new object[] {strMsg, nRet, strRet});
            }
            else
            {
                int cnt = LIST_LOG.Items.Count;
                LIST_LOG.Items.Add(strMessage + " " + strMsg + " " + "(" + nRet.ToString() + ") " + "[" + strRet + "]");
                LIST_LOG.SetSelected(cnt, true);
            }
        }

        public void WLOGD(string strFunc, string strMsg, int nRet)
        {
            //[XnsSdkWindow] Function() [Message = %d]
            string strMessage = "[XnsSdkDevice] ";
            if (LIST_LOG.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WLOGD);
                LIST_LOG.Invoke(d, new object[] { strFunc, strMsg, nRet });
            }
            else
            {
                int cnt = LIST_LOG.Items.Count;
                LIST_LOG.Items.Add(strMessage + " " + strFunc + " [" + strMsg + " = " + nRet.ToString() + "]");
                LIST_LOG.SetSelected(cnt, true);
            }
        }

        public void WLOGD(int nRet, string strRet)
        {
            //[XnsSdkDevice] (%d)[Message]
            string strMessage = "[XnsSdkDevice] ";
            if (LIST_LOG.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WLOGD);
                LIST_LOG.Invoke(d, new object[] {nRet, strRet});
            }
            else
            {
                int cnt = LIST_LOG.Items.Count;
                LIST_LOG.Items.Add(strMessage + "(" + nRet.ToString() + ") " + "[" + strRet + "]");
                LIST_LOG.SetSelected(cnt, true);
            }
        }

        public void WLOGD(string strMsg, int nRet)
        {
            //[XnsSdkDevice] [Message = %d]
            string strMessage = "[XnsSdkDevice] ";
            if (LIST_LOG.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WLOGD);
                LIST_LOG.Invoke(d, new object[] { strMsg, nRet });
            }
            else
            {
                int cnt = LIST_LOG.Items.Count;
                LIST_LOG.Items.Add(strMessage + "[" + strMsg + " = " + nRet.ToString() + "]");
                LIST_LOG.SetSelected(cnt, true);
            }
        }

        public void WLOGD(string strRet)
        {
            //[XnsSdkDevice] Message
            string strMessage = "[XnsSdkDevice] ";
            if (LIST_LOG.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WLOGD);
                LIST_LOG.Invoke(d, new object[] { strRet });
            }
            else
            {
                int cnt = LIST_LOG.Items.Count;
                LIST_LOG.Items.Add(strMessage + strRet);
                LIST_LOG.SetSelected(cnt, true);
            }            
        }

        //------------------------------------------------------------ ActiveX SDK Window Control Log
        public void WLOGW(string strFunc, string strMsg, int nRet, string strRet)
        {
            //[XnsSdkWindow] Function() Message (%d)[Message]
            string strMessage = "[XnsSdkWindow] ";
            if (LIST_LOG.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WLOGW);
                LIST_LOG.Invoke(d, new object[] { strFunc, strMsg, nRet, strRet });
            }
            else
            {
                int cnt = LIST_LOG.Items.Count;
                LIST_LOG.Items.Add(strMessage + " " + strFunc + " " + strMsg + " " + "(" + nRet.ToString() + ") " + "[" + strRet + "]");
                LIST_LOG.SetSelected(cnt, true);
            }
        }

        public void WLOGW(string strMsg, int nRet, string strRet)
        {
            //[XnsSdkWindow] Message (%d)[Message]
            string strMessage = "[XnsSdkWindow] ";
            if (LIST_LOG.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WLOGW);
                LIST_LOG.Invoke(d, new object[] { strMsg, nRet, strRet });
            }
            else
            {
                int cnt = LIST_LOG.Items.Count;
                LIST_LOG.Items.Add(strMessage + " " + strMsg + " " + "(" + nRet.ToString() + ") " + "[" + strRet + "]");
                LIST_LOG.SetSelected(cnt, true);
            }
        }

        public void WLOGW(string strFunc, string strMsg, int nRet)
        {
            //[XnsSdkWindow] Function() [Message = %d]
            string strMessage = "[XnsSdkWindow] ";
            if (LIST_LOG.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WLOGW);
                LIST_LOG.Invoke(d, new object[] { strFunc, strMsg, nRet });
            }
            else
            {
                int cnt = LIST_LOG.Items.Count;
                LIST_LOG.Items.Add(strMessage + " " + strFunc + " [" + strMsg + " = " + nRet.ToString() + "]");
                LIST_LOG.SetSelected(cnt, true);
            }            
        }

        public void WLOGW(int nRet, string strRet)
        {
            //[XnsSdkWindow] (%d)[Message]
            string strMessage = "[XnsSdkWindow] ";
            if (LIST_LOG.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WLOGW);
                LIST_LOG.Invoke(d, new object[] { nRet, strRet });
            }
            else
            {
                int cnt = LIST_LOG.Items.Count;
                LIST_LOG.Items.Add(strMessage + "(" + nRet.ToString() + ") " + "[" + strRet + "]");
                LIST_LOG.SetSelected(cnt, true);
            }
        }

        public void WLOGW(string strMsg, int nRet)
        {
            //[XnsSdkWindow] [Message = %d]
            string strMessage = "[XnsSdkWindow] ";
            if (LIST_LOG.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WLOGW);
                LIST_LOG.Invoke(d, new object[] { strMsg, nRet });
            }
            else
            {
                int cnt = LIST_LOG.Items.Count;
                LIST_LOG.Items.Add(strMessage + "[" + strMsg + " = " + nRet.ToString() + "]");
                LIST_LOG.SetSelected(cnt, true);
            }
        }

        public void WLOGW(string strRet)
        {
            //[XnsSdkWindow] Message
            string strMessage = "[XnsSdkWindow] ";
            if (LIST_LOG.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WLOGW);
                LIST_LOG.Invoke(d, new object[] { strRet });
            }
            else
            {
                int cnt = LIST_LOG.Items.Count;
                LIST_LOG.Items.Add(strMessage + strRet);
                LIST_LOG.SetSelected(cnt, true);
            }
        }


        //------------------------------------------------------------ Message Box
        public void ERROR_BOX(string strFunc, string strMsg, int nRet, string strRet)
        {
            //[INFO] Function() Message (%d)[Message]
            string strMessage = "[INFO] ";
            string strError;

            strError = strMessage + " " + strFunc + " " + strMsg + " " + "(" + nRet.ToString() + ") " + "[" + strRet + "]";
            MessageBox.Show(strError);
        }

        public void ERROR_BOX(string strMsg, int nRet, string strRet)
        {
            //[INFO] Message (%d)[Message]
            string strMessage = "[INFO] ";
            string strError;

            strError = strMessage + " " + strMsg + " " + "(" + nRet.ToString() + ") " + "[" + strRet + "]";
            MessageBox.Show(strError);
        }

        public void ERROR_BOX(string strFunc, string strMsg, int nRet)
        {
            //[XnsSdkWindow] Function() [Message = %d]
            string strMessage = "[INFO] ";
            string strError;

            strError = strMessage + " " + strFunc + " [" + strMsg + " = " + nRet.ToString() + "]";
            MessageBox.Show(strError);
        }

        public void ERROR_BOX(int nRet, string strRet)
        {
            //[INFO] (%d)[Message]
            string strMessage = "[INFO] ";
            string strError;

            strError = strMessage + "(" + nRet.ToString() + ") " + "[" + strRet + "]";
            MessageBox.Show(strError);
        }

        public void ERROR_BOX(string strMsg, int nRet)
        {
            //[INFO] [Message = %d]
            string strMessage = "[INFO] ";
            string strError;

            strError = strMessage + "[" + strMsg + " = " + nRet.ToString() + "]";
            MessageBox.Show(strError);
        }

        public void ERROR_BOX(string strRet)
        {
            //[INFO] [Message]
            string strMessage = "[INFO] ";
            string strError;

            strError = strMessage + strRet;
            MessageBox.Show(strError);
        }
    }
}
