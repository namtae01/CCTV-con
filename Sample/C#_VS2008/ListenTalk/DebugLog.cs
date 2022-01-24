using System.Windows.Forms;

namespace ListenTalk
{
    public partial class ListenTalkForm
    {
        //------------------------------------------------------------ ActiveX SDK Device Control Log
        private void WLOGD(string strFunc, string strMsg, int nRet, string strRet)
        {
            //[XnsSdkWindow] Function() Message (%d)[Message]
            string strMessage = "[XnsSdkDevice] ";
            int cnt = LIST_LOG.Items.Count;

            LIST_LOG.Items.Add(strMessage + " " + strFunc + " " + strMsg + " " + "(" + nRet.ToString() + ") " + "[" + strRet + "]");
            LIST_LOG.SetSelected(cnt, true);
        }

        private void WLOGD(string strMsg, int nRet, string strRet)
        {
            //[XnsSdkDevice] Message (%d)[Message]
            string strMessage = "[XnsSdkDevice] ";
            int cnt = LIST_LOG.Items.Count;

            LIST_LOG.Items.Add(strMessage + " " + strMsg + " " + "(" + nRet.ToString() + ") " + "[" + strRet + "]");
            LIST_LOG.SetSelected(cnt, true);
        }

        private void WLOGD(string strFunc, string strMsg, int nRet)
        {
            //[XnsSdkWindow] Function() [Message = %d]
            string strMessage = "[XnsSdkDevice] ";
            int cnt = LIST_LOG.Items.Count;

            LIST_LOG.Items.Add(strMessage + " " + strFunc + " [" + strMsg + " = " + nRet.ToString() + "]");
            LIST_LOG.SetSelected(cnt, true);
        }

        private void WLOGD(int nRet, string strRet)
        {
            //[XnsSdkDevice] (%d)[Message]
            string strMessage = "[XnsSdkDevice] ";
            int cnt = LIST_LOG.Items.Count;

            LIST_LOG.Items.Add(strMessage + "(" + nRet.ToString() + ") " + "[" + strRet + "]");
            LIST_LOG.SetSelected(cnt, true);
        }

        private void WLOGD(string strMsg, int nRet)
        {
            //[XnsSdkDevice] [Message = %d]
            string strMessage = "[XnsSdkDevice] ";
            int cnt = LIST_LOG.Items.Count;

            LIST_LOG.Items.Add(strMessage + "[" + strMsg + " = " + nRet.ToString() + "]");
            LIST_LOG.SetSelected(cnt, true);
        }

        private void WLOGD(string strRet)
        {
            //[XnsSdkDevice] Message
            string strMessage = "[XnsSdkDevice] ";
            int cnt = LIST_LOG.Items.Count;

            LIST_LOG.Items.Add(strMessage + strRet);
            LIST_LOG.SetSelected(cnt, true);
        }



        //------------------------------------------------------------ ActiveX SDK Window Control Log
        private void WLOGW(string strFunc, string strMsg, int nRet, string strRet)
        {
            //[XnsSdkWindow] Function() Message (%d)[Message]
            string strMessage = "[XnsSdkWindow] ";
            int cnt = LIST_LOG.Items.Count;

            LIST_LOG.Items.Add(strMessage + " " + strFunc + " " + strMsg + " " + "(" + nRet.ToString() + ") " + "[" + strRet + "]");
            LIST_LOG.SetSelected(cnt, true);
        }

        private void WLOGW(string strMsg, int nRet, string strRet)
        {
            //[XnsSdkWindow] Message (%d)[Message]
            string strMessage = "[XnsSdkWindow] ";
            int cnt = LIST_LOG.Items.Count;

            LIST_LOG.Items.Add(strMessage + " " + strMsg + " " + "(" + nRet.ToString() + ") " + "[" + strRet + "]");
            LIST_LOG.SetSelected(cnt, true);
        }

        private void WLOGW(string strFunc, string strMsg, int nRet)
        {
            //[XnsSdkWindow] Function() [Message = %d]
            string strMessage = "[XnsSdkWindow] ";
            int cnt = LIST_LOG.Items.Count;

            LIST_LOG.Items.Add(strMessage + " " + strFunc + " [" + strMsg + " = " + nRet.ToString() + "]");
            LIST_LOG.SetSelected(cnt, true);
        }

        private void WLOGW(int nRet, string strRet)
        {
            //[XnsSdkWindow] (%d)[Message]
            string strMessage = "[XnsSdkWindow] ";
            int cnt = LIST_LOG.Items.Count;

            LIST_LOG.Items.Add(strMessage + "(" + nRet.ToString() + ") " + "[" + strRet + "]");
            LIST_LOG.SetSelected(cnt, true);
        }

        private void WLOGW(string strMsg, int nRet)
        {
            //[XnsSdkWindow] [Message = %d]
            string strMessage = "[XnsSdkWindow] ";
            int cnt = LIST_LOG.Items.Count;

            LIST_LOG.Items.Add(strMessage + "[" + strMsg + " = " + nRet.ToString() + "]");
            LIST_LOG.SetSelected(cnt, true);
        }

        private void WLOGW(string strRet)
        {
            //[XnsSdkWindow] Message
            string strMessage = "[XnsSdkWindow] ";
            int cnt = LIST_LOG.Items.Count;

            LIST_LOG.Items.Add(strMessage + strRet);
            LIST_LOG.SetSelected(cnt, true);
        }


        //------------------------------------------------------------ Message Box
        private void ERROR_BOX(string strFunc, string strMsg, int nRet, string strRet)
        {
            //[INFO] Function() Message (%d)[Message]
            string strMessage = "[INFO] ";
            string strError;

            strError = strMessage + " " + strFunc + " " + strMsg + " " + "(" + nRet.ToString() + ") " + "[" + strRet + "]";
            MessageBox.Show(strError);
        }

        private void ERROR_BOX(string strMsg, int nRet, string strRet)
        {
            //[INFO] Message (%d)[Message]
            string strMessage = "[INFO] ";
            string strError;

            strError = strMessage + " " + strMsg + " " + "(" + nRet.ToString() + ") " + "[" + strRet + "]";
            MessageBox.Show(strError);
        }

        private void ERROR_BOX(string strFunc, string strMsg, int nRet)
        {
            //[XnsSdkWindow] Function() [Message = %d]
            string strMessage = "[INFO] ";
            string strError;

            strError = strMessage + " " + strFunc + " [" + strMsg + " = " + nRet.ToString() + "]";
            MessageBox.Show(strError);
        }

        private void ERROR_BOX(int nRet, string strRet)
        {
            //[INFO] (%d)[Message]
            string strMessage = "[INFO] ";
            string strError;

            strError = strMessage + "(" + nRet.ToString() + ") " + "[" + strRet + "]";
            MessageBox.Show(strError);
        }

        private void ERROR_BOX(string strMsg, int nRet)
        {
            //[INFO] [Message = %d]
            string strMessage = "[INFO] ";
            string strError;

            strError = strMessage + "[" + strMsg + " = " + nRet.ToString() + "]";
            MessageBox.Show(strError);
        }

        private void ERROR_BOX(string strRet)
        {
            //[INFO] [Message]
            string strMessage = "[INFO] ";
            string strError;

            strError = strMessage + strRet;
            MessageBox.Show(strError);
        }
    }
}