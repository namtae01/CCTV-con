#pragma once

enum
{
	XINPUT_VIDEO = 1,
	XINPUT_AUDIO,
	XINPUT_METADATA,
};

enum
{
	XFRAME_UNKNOWN = 0,
	XFRAME_IVOP,
	XFRAME_PVOP,
	XFRAME_BVOP,
	XFRAME_END,
	XFRAME_BACKUP_FAIL = 7	//+ jungkoo.kang <2012.12.03> Banamex 프로젝트 관련 백업실패 고려하도록 수정
};

typedef enum
{
	XVIDEO_PIXEL_UNKNOWN			= 0x0000, // Unknown
	XVIDEO_PIXEL_R555				= 0x0002, // 16Bit, R555
	XVIDEO_PIXEL_R565				= 0x0003, // 16Bit, R565
	XVIDEO_PIXEL_BGR24				= 0x0004, // 24Bit
	XVIDEO_PIXEL_BGR32				= 0x0005, // 32Bit, Non Alpha Channel
	XVIDEO_PIXEL_BGRA				= 0x0006, // 32Bit, with Alpha Channel

	// YUV Case (0x0101 ~ 0x01FF)
	XVIDEO_PIXEL_YV12				= 0x0101, // 12Bit, YV12
} XVIDEO_PIXEL_FORMAT;

enum
{
	XTIME_UTC = 0,
	XTIME_LOCAL,
};

enum
{	
	XMEVT_DEVICE_STATUS_CHANGED = 1,
	XMEVT_CONTROL_LOCAL_NAME_CHANGED,
	XMEVT_CONTROL_REMOTE_NAME_CHANGED,
	XMEVT_CONTROL_STATUS_CHANGED,
	XMEVT_CONTROL_CAPABILITY_CHANGED,
	XMEVT_CONNECT_OVER,
	XMEVT_PLAYBACK_PLAYING,
	XMEVT_PLAYBACK_PAUSING,
	XMEVT_PLAYBACK_SEEKING,
	XMEVT_PLAYBACK_FRAMEADVANCING,
	XMEVT_PLAYBACK_END,
	XMEVT_MEDIASUORCE_RELEASING,
};

class IXnsMediaEventHandler
{
public:
	virtual void			OnXnsMediaEvent( long nEventID , ... ) = 0;
};

class IXnsMedia
{
public:
	virtual long			GetInputType() = 0;
	virtual long			GetCodecType() = 0;
	virtual unsigned long	GetTimeStamp() = 0;
	virtual long			GetFrameSequence() = 0;
	virtual long			GetFrameTime( long nType ) = 0;
	virtual long			GetFrameType() = 0;
	virtual long			GetIGroupCount() = 0;
	virtual long			GetPGroupCount() = 0;
	virtual BOOL			IsAudioSrouce() = 0;
	virtual BOOL			IsVideoLoss() = 0;
	virtual BOOL			IsAlarm() = 0;
	virtual BOOL			IsMotion() = 0;
	virtual long			GetImageWidth() = 0;
	virtual long			GetImageHeight() = 0;	
	virtual long			GetFrameSize() = 0;
	virtual unsigned char*	GetFrameData() = 0;
	virtual long			GetRecTime() = 0;
	virtual long			GetAudioChannel() = 0;
	virtual long			GetAudioSampleRate() = 0;
	virtual long			GetAudioBits() = 0;
	virtual long			GetFrameRate() = 0;
	virtual BOOL			IsMediaLiveType() = 0;
};

class IXnsMediaSource
{
public:	
	virtual long			GetDeviceID() = 0;
	virtual long			GetControlID() = 0;
	virtual long			GetMediaType() = 0;
	virtual long			GetStartTime() = 0;
	virtual long			GetEndTime() = 0;
	virtual long			GetDeviceStatus() = 0;
	virtual BOOL			GetPlayBackStatus() = 0;
	virtual BOOL			IsUserFull() = 0;
	virtual const char*		GetControlLocalName() = 0;
	virtual const char*		GetControlRemoteName() = 0;
	virtual long			GetControlStatus( long nStatusID ) = 0;
	virtual BOOL			GetControlCapability( long nCapabilityID ) = 0;

	virtual long			GetCount() = 0;
	virtual long			GetDataSize() = 0;	
	virtual long			GetMaxCount() = 0;
	virtual long			GetMaxDataSize() = 0;
	virtual void			SetMaxCount( long nMaxCount ) = 0;
	virtual void			SetMaxDataSize( long nMaxDataSize ) = 0;
	
	virtual void			SetXnsMediaEventHandler( IXnsMediaEventHandler *pEventHandler ) = 0;
	virtual IXnsMedia*		GetMedia() = 0;
	virtual void			ReleaseMedia( IXnsMedia* pMedia ) = 0;
	virtual void			Clear() = 0;
};

#ifndef _VIDEO_CALLBACK_FUNC_
typedef void (*CALLBACK_FUNC)(long hMediaSource, long nWidth, long nHeight, long nFrameSize, unsigned char* pVideo);
typedef void (*CALLBACK_FUNC_EX)(long hMediaSource, long nWidth, long nHeight, long nFrameSize, unsigned char* pVideo, void *pInstance);
#define _VIDEO_CALLBACK_FUNC_
#endif
