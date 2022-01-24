#pragma once

// 컴퓨터에서 Microsoft Visual C++를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// 참고: 이 파일의 내용을 수정하지 마십시오. Microsoft Visual C++에서
//  이 클래스를 다시 생성할 때 수정한 내용을 덮어씁니다.

/////////////////////////////////////////////////////////////////////////////
// CXnssdkwindowctrl1 래퍼 클래스입니다.

class CXnssdkwindowctrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CXnssdkwindowctrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xC3F99E59, 0x433D, 0x4A79, { 0xA1, 0x88, 0xB3, 0x6A, 0xCE, 0x8F, 0x78, 0xF8 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 특성입니다.
public:


// 작업입니다.
public:

// _DXnsSdkWindow

// Functions
//

	long Initialize(long hDrawWnd, long hTopWnd)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hDrawWnd, hTopWnd);
		return result;
	}
	long Start(long hMediaSource)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMediaSource);
		return result;
	}
	long Stop()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetDeviceID()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetControlID()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetLastError()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetImageWidth()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetImageHeight()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IsMedia()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long ZoomLevel(long nX, long nY, long nLevel)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nX, nY, nLevel);
		return result;
	}
	long ZoomRate(double lfX, double lfY, double lfWidth, double lfHeight)
	{
		long result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lfX, lfY, lfWidth, lfHeight);
		return result;
	}
	long GetZoomInfo(double * plfX, double * plfY, double * plfWidth, double * plfHeight)
	{
		long result;
		static BYTE parms[] = VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, plfX, plfY, plfWidth, plfHeight);
		return result;
	}
	void ClearZoom()
	{
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DrawRect(long nX, long nY, long nWidth, long nHeight)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nX, nY, nWidth, nHeight);
	}
	void ClearDraw()
	{
		InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetOSDOnOff(long nOSDID, long bOnOff)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nOSDID, bOnOff);
	}
	void SetDateTimeFormat(long nFormatID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nFormatID);
	}
	void SetVolume(long nVolume)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nVolume);
	}
	long GetVolume()
	{
		long result;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SaveSnapshot(LPCTSTR szFile, long nFormat)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szFile, nFormat);
		return result;
	}
	long PrintSnapshot()
	{
		long result;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCursor(long nCursorID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nCursorID);
	}
	void SetSound(long bSound)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bSound);
	}
	void DisplayNoData(long bState)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bState);
	}
	long GetMediaType()
	{
		long result;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long PushMedia(long hMediaData)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMediaData);
		return result;
	}
	void ClearMediaBuffer()
	{
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetPlaySpeed(double dPlaySpeed)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dPlaySpeed);
	}
	double GetPlaySpeed()
	{
		double result;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	long DateToTimet(long nYear, long nMonth, long nDay, long nHour, long nMinute, long nSecond)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nYear, nMonth, nDay, nHour, nMinute, nSecond);
		return result;
	}
	void TimetToDate(long tTime, long * pnYear, long * pnMonth, long * pnDay, long * pnHour, long * pnMinute, long * pnSecond)
	{
		static BYTE parms[] = VTS_I4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, tTime, pnYear, pnMonth, pnDay, pnHour, pnMinute, pnSecond);
	}
	long GetCurrentFrameTime()
	{
		long result;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetFirstFrameTime()
	{
		long result;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void MoveFrameAdvance()
	{
		InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long IsBufferFull()
	{
		long result;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IsBufferEmpty()
	{
		long result;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetBufferSize(long nBufferSize, long nMinRemainingSize)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nBufferSize, nMinRemainingSize);
	}
	long GetBufferSize()
	{
		long result;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetRemainingBufferSize()
	{
		long result;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetInputType(long hMediaData)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMediaData);
		return result;
	}
	long GetFrameType(long hMediaData)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMediaData);
		return result;
	}
	long GetFrameTime(long hMediaData)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMediaData);
		return result;
	}
	long GetFrameSize(long hMediaData)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMediaData);
		return result;
	}
	long GetTimeStamp(long hMediaData)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMediaData);
		return result;
	}
	void SetBrightness(long nValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nValue);
	}
	long GetBrightness()
	{
		long result;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetContrast(long nValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nValue);
	}
	long GetContrast()
	{
		long result;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetDeinterlaceMode(long bMode)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bMode);
	}
	void DrawShape(long nIndex, long nType, long nX, long nY, long nWidth, long nHeight, long nR, long nG, long nB, long nThick)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nIndex, nType, nX, nY, nWidth, nHeight, nR, nG, nB, nThick);
	}
	void SetMotionSearchGrid(long nGridWidth, long nGridHeight, long pGridArray)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nGridWidth, nGridHeight, pGridArray);
	}
	void ShowMotionSearchGrid(long bShow)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShow);
	}
	long SaveSnapshotWithString(LPCTSTR szFile, long nFormat, long bShowCameraName, long bUseLocalName, long bShowDateTime, LPCTSTR szUserNote, long bUseTempSavedImage)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4 ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szFile, nFormat, bShowCameraName, bUseLocalName, bShowDateTime, szUserNote, bUseTempSavedImage);
		return result;
	}
	long PrintSnapshotWithString(long bShowCameraName, long bUseLocalName, long bShowDateTime, LPCTSTR szUserNote, long bUseTempSavedImage)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4 ;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bShowCameraName, bUseLocalName, bShowDateTime, szUserNote, bUseTempSavedImage);
		return result;
	}
	long SaveTempImage()
	{
		long result;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void GetMotionSearchGrid(long pGridArray)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pGridArray);
	}
	void SetCEMode(long bOn)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bOn);
	}
	long GetDeinterlaceMode()
	{
		long result;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetVideoCallbackFunc(long hMediaSource, long pVideoCallbackFunc)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMediaSource, pVideoCallbackFunc);
		return result;
	}
	void SetDefogMode(long bOn)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bOn);
	}
	long SetVideoRawDataReceived(long hMediaSource)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMediaSource);
		return result;
	}
	long SaveSnapShotWithData(long pData, long nDataSize, long nImageWidth, long nImageHeight, LPCTSTR szFile, long nFormat)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4 ;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pData, nDataSize, nImageWidth, nImageHeight, szFile, nFormat);
		return result;
	}
	long UnSetVideoRawDataReceived(long hMediaSource)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMediaSource);
		return result;
	}
	long SetCustomOSD(LPCTSTR szOSDText, long nX, long nY, long nR, long nG, long nB)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szOSDText, nX, nY, nR, nG, nB);
		return result;
	}
	long SetCustomOSDOnOff(long bOnOff)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x41, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bOnOff);
		return result;
	}
	long SetImageFlip(long bHFlip, long bVFlip)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x42, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bHFlip, bVFlip);
		return result;
	}
	long GetVideoPixelFormat()
	{
		long result;
		InvokeHelper(0x43, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}

// Properties
//



};
