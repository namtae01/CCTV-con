Partial Public Class PlayBack
    Public Function WLOGD(ByVal strRet As String)
        '[XnsSdkDevice] Message
        Dim strMessage As String = "[XnsSdkDevice] "
        Dim cnt As Integer = LIST_LOG.Items.Count

        LIST_LOG.Items.Add(strMessage + strRet)
        LIST_LOG.SetSelected(cnt, True)
    End Function


    Public Function WLOGW(ByVal strRet As String)
        '[XnsSdkWindow] Message
        Dim strMessage As String = "[XnsSdkWindow] "
        Dim cnt As Integer = LIST_LOG.Items.Count

        LIST_LOG.Items.Add(strMessage + strRet)
        LIST_LOG.SetSelected(cnt, True)
    End Function


    Public Function ERROR_BOX(ByVal strRet As String)
        '[INFO] [Message]
        Dim strMessage As String = "[INFO] "
        Dim strError As String

        strError = strMessage + strRet
        MessageBox.Show(strError)
    End Function
End Class
