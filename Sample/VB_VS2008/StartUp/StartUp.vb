'///////////////////////////////////////////////////////////////////////////////////
'// Copyright(c) 2011 by Samsung Techwin, Inc.
'//
'// This software is copyrighted by, and is the sole property of Samsung Techwin.
'// All rights, title, ownership, or other interests in the software remain the
'// property of Samsung Techwin. This software may only be used in accordance with
'// the corresponding license agreement. Any unauthorized use, duplication,
'// transmission, distribution, or disclosure of this software is expressly
'// forbidden.
'//
'// This Copyright notice may not be removed or modified without prior written
'// consent of Samsung Techwin.
'//
'// Samsung Techwin reserves the right to modify this software without notice.
'//
'// Samsung Techwin, Inc.
'// KOREA
'// http://www.samsungtechwin.co.kr
'///////////////////////////////////////////////////////////////////////////////////
'// @ File Name :		 StartUp.vb
'// @ File Description : StartUp Form Source Code File. 
'//						 Define the entire function.
'///////////////////////////////////////////////////////////////////////////////////

Public Class StartUp

    Private Sub StartUp_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Initializes the DLL files. 
        ' For this, XnsActiveX library requires config.xml, device.xml, 
        ' and xns.xml files and the DLL file list should be mentioned 
        ' in Xns.xml file. The path of the DLL file can not exceed 512 bytes
        ' in length. The XnsActiveX library searches for xns.xml using 
        ' XnsSDKDevice.ocx installed in "{$SDK path}\Config" folder.
        ' -----------------------------------------------------------------------
        AxXnsSdkDevice.Initialize()

        ' [ XNS ACTIVEX HELP ]
        ' -----------------------------------------------------------------------
        ' Initializes the XnsSdkWindow control. 
        ' Namely, this will specify the window handle in order to display 
        ' images on the screen. 
        ' -----------------------------------------------------------------------
        AxXnsSdkWindow.Initialize(0, 0)
    End Sub

End Class

