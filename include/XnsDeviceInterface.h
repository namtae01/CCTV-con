#pragma once

#include "XnsMediaInterface.h"

#define STR_LEN_NAME				127	
#define STR_LEN_ID					 63	
#define STR_LEN_PSWD				 41	
#define STR_LEN_PTZ_NAME			 41	
#define STR_LEN_IP					 16	
#define STR_LEN_MAC					 13
#define STR_LEN_DOMAIN				255		
#define STR_LEN_URL					255	
#define STR_LEN_DDNSID				 21	
#define STR_LEN_VERSION				128	
#define STR_LEN_DESCRIPTION			255	
#define STR_LEN_PHONE				 63	
#define STR_LEN_ADDRESS				255	
#define STR_LEN_PATH				512
#define STR_LEN_LINK_STATUS			512

#define  WM_RECEIVE_DEVICEEVENT			WM_USER + 101
#define  WM_RECEIVE_WINDOWEVENT			WM_USER + 102
enum
{
	XDEVICE_STATUS_DISCONNECTED = 0,
	XDEVICE_STATUS_CONNECTED,
};

enum
{
	XCTL_ALL = 0xFFFF,
	XCTL_DVR = 0x01,
	XCTL_NETCAM = 0x02,
	XCTL_ENCODER = 0x04,
	XCTL_CAMERA = 0x08,
	XCTL_VIDEO = 0x10,
	XCTL_ALARM = 0x20,
	XCTL_SENSOR = 0x40,
	XCTL_ALARM_BEEP = 0x80,
	XCTL_NVR = 0x100,
	XCTL_SUNAPI_NVR = 0x0200,
	XCTL_SUNAPI_DVR = 0x0400,
	XCTL_TEXT = 0x0800,
};

enum
{
	XADDRESS_IP = 1,
	XADDRESS_URL,
	XADDRESS_SSDDNS,
	XADDRESS_S1DDNS,
	XADDRESS_IPOLISDDNS,
};

enum
{
	XCAMERA_STATUS = 1,
	XRECORDING_STATUS,
	XLISTEN_STATUS,
	XTALK_STATUS,
	XALARM_STATUS,
	XLOCALREC_STATUS,
	XTEXT_STATUS,
};

enum
{
	XCAMERA_STATUS_MASK = 0x00000001,
	XRECORDING_STATUS_MASK = 0x00000002,
	XLISTEN_STATUS_MASK = 0x00000004,
	XTALK_STATUS_MASK = 0x00000008,
	XALARM_STATUS_MASK = 0x00000010,
	XLOCALREC_STATUS_MASK = 0x00000020,
	XTEXT_STATUS_MASK = 0x00000040,
};

enum
{
	XCAM_STATUS_ON = 0x00000001,
	XCAM_STATUS_SIGNAL = 0x00000002,
	XCAM_STATUS_COVERT1 = 0x00000004,
	XCAM_STATUS_COVERT2 = 0x00000008,
	XCAM_STATUS_ACTIVATED = 0x00000010,
};

enum
{
	XLISTEN_STATUS_LIVE = 0x00000001,
	XLISTEN_STATUS_PLAYBACK = 0x00000002,
};

enum
{
	XTEXT_STATUS_ON = 0x00000001,
};

// --> hh3.kim : ADD IV EVENT
// IV TYPE
enum
{
	XIV_TYPE_PASSING		= 0x00000001,
	XIV_TYPE_ENTERING		= 0x00000010,
	XIV_TYPE_EXITING		= 0x00000020,
	XIV_TYPE_APPEARING		= 0x00000040,
	XIV_TYPE_DISAPPERING	= 0x00000080,
	XIV_TYPE_SCENE_CHANGE	= 0x00000100,
};
// <-- hh3.kim : ADD IV EVENT

enum
{
	XVCODEC_UNKNOWN = 0,
	XVCODEC_MJPEG,
	XVCODEC_MPEG4,
	XVCODEC_H264,
	XVCODEC_H265,
};

// Unit Cap (For Device and Control)
// Caution! MAX Cap is 100 (MAX_CAPAPBILITY Defined)
enum
{
	XCTL_CAP_NONE = 0,
	XCTL_CAP_SW_UPLOAD,
	XCTL_CAP_CFG_IMPORT,
	XCTL_CAP_CFG_EXPORT,
	XCTL_CAP_CONN_FORCED,
	XCTL_CAP_MEDIA_AUTHORITY,
	XCTL_CAP_FSPEED1,
	XCTL_CAP_FSPEED2,
	XCTL_CAP_FSPEED4,
	XCTL_CAP_FSPEED8,
	XCTL_CAP_FSPEED16,			//10
	XCTL_CAP_FSPEED32,
	XCTL_CAP_FSPEED64,
	XCTL_CAP_BSPEED1,
	XCTL_CAP_BSPEED2,
	XCTL_CAP_BSPEED4,
	XCTL_CAP_BSPEED8,
	XCTL_CAP_BSPEED16,
	XCTL_CAP_BSPEED32,
	XCTL_CAP_BSPEED64,
	XCTL_CAP_FSSPEED1,			//20
	XCTL_CAP_FSSPEED2,
	XCTL_CAP_FSSPEED4,
	XCTL_CAP_FSSPEED8,
	XCTL_CAP_FSSPEED16,
	XCTL_CAP_FSSPEED32,
	XCTL_CAP_FSSPEED64,
	XCTL_CAP_BSSPEED1,
	XCTL_CAP_BSSPEED2,
	XCTL_CAP_BSSPEED4,
	XCTL_CAP_BSSPEED8,			//30
	XCTL_CAP_BSSPEED16,
	XCTL_CAP_BSSPEED32,
	XCTL_CAP_BSSPEED64,
	XCTL_CAP_SEEK,
	XCTL_CAP_FSTEP,
	XCTL_CAP_BSTEP,
	XCTL_CAP_LIVE,
	XCTL_CAP_PLAYBACK,
	XCTL_CAP_BACKUP,
	XCTL_CAP_SEARCH,			//40
	XCTL_CAP_LISTEN,
	XCTL_CAP_TALK,
	XCTL_CAP_CAM_MENU,
	XCTL_CAP_PTZ_PAN,
	XCTL_CAP_PTZ_TILT,
	XCTL_CAP_PTZ_ZOOM,
	XCTL_CAP_PTZ_SPEED,
	XCTL_CAP_PTZ_PRESET,
	XCTL_CAP_PTZ_PRESET_SVR,
	XCTL_CAP_PTZ_AUTOPAN,		//50
	XCTL_CAP_PTZ_SCAN,
	XCTL_CAP_PTZ_PATTERN,
	XCTL_CAP_PTZ_SWING,
	XCTL_CAP_PTZ_TOUR,
	XCTL_CAP_PTZ_POWER,		
	XCTL_CAP_PTZ_FREE_MOVE,
	XCTL_CAP_PTZ_SPEED_ZOOM,
	XCTL_CAP_CAM_IRIS,
	XCTL_CAP_CAM_FOCUS,
	XCTL_CAP_CAM_BRIGHTNESS,	//60
	XCTL_CAP_CAM_CONTRAST,		
	XCTL_CAP_ALARM_ONOFF,
	XCTL_CAP_DVR_EVENT_RESET,
	XCTL_CAP_DVR_MANUAL_REC_CONTROL,
	XCTL_CAP_DVR_REC_STATUS,
	XCTL_CAP_MOTION_SEARCH,				// Smart Search Added

	// --> hh3.kim : ADD AREA ZOOM FUNCTIONS
	XCTL_CAP_PTZ_AREA_ZOOM,

	// --> hh3.kim : ADD PTZ GET/SET FUNCTIONS  0
	XCTL_CAP_PTZ_GET_POS,
	XCTL_CAP_PTZ_SET_POS,
	XCTL_CAP_OVERLAP_TRACK_SEARCH,		//70, //+ jeongguc.kang <2011.10.19> 중복구간 추가
	XCTL_CAP_POS_SEARCH,				//+ jeongguc.kang <2011.10.20> Search Pos 추가

	// hh3.kim : PTZ GET/SET POS SPEED
	XCTL_CAP_PTZ_GET_POS_SPEED,
	XCTL_CAP_PTZ_SET_POS_SPEED,

	XCTL_CAP_POWER_RESTART,

	XCTL_CAP_BANDWIDTH,					//+ jeongguc.kang <2012.04.18> banamex 프로젝트 관련 bandwidth 커맨드 추가
	XCTL_CAP_SHUT_DOWN,
	XCTL_CAP_GET_PERMISSION,
	XCTL_CAP_SET_PERMISSION,
	XCTL_CAP_DIVIDE_VIDEO_AUDIO,
	XCTL_CAP_TRACKING,					
	XCTL_CAP_FACE_DETECTION,				// <2014.10.21>
	XCTL_CAP2_AUDIO_DETECTION,				// <2014.10.21>
	XCTL_CAP2_ADVANCED_MOTION_DETECTION,	// <2014.10.21>
	XCTL_CAP3_RTP_METADATA,
	XCTL_CAP_DEVICE_LOG_BACKUP,				//+ jungkoo.kang <2015.03.05> Log backup 기능 추가

	//20150714
	XCTL_CAP_PTZ_GET_POS_NORMALIZE,
	XCTL_CAP_PTZ_SET_POS_NORMALIZE,
	XCTL_CAP_CAM_MULTIPROFILE,

	XCTL_CAP_TEXT,
	XCTL_CAP_SEARCH_TEXT_CALENDAR,
	XCTL_CAP_NTP_MANAGEMENT,

	XCTL_CAP_THERMAL,
	XCTL_CAP2_GET_VIDEO_INFO_EX2,
	XCTL_CAP2_SET_VIDEO_INFO_EX
};

// Unit Cap Mask (For Control, not Device)
enum
{
	XCTL_CAP_SW_UPLOAD_MASK					= 0x00000001,
	XCTL_CAP_CFG_IMPORT_MASK				= 0x00000002,
	XCTL_CAP_CFG_EXPORT_MASK				= 0x00000004,
	XCTL_CAP_CONN_FORCED_MASK				= 0x00000008,
	XCTL_CAP_MEDIA_AUTHORITY_MASK			= 0x00000010,
	XCTL_CAP_PLAY_CONTROL_MASK				= 0x00000020,
	XCTL_CAP_LIVE_MASK						= 0x00000040,
	XCTL_CAP_PLAYBACK_MASK					= 0x00000080,
	XCTL_CAP_BACKUP_MASK					= 0x00000100,
	XCTL_CAP_SEARCH_MASK					= 0x00000200,
	XCTL_CAP_LISTEN_MASK					= 0x00000400,
	XCTL_CAP_TALK_MASK						= 0x00000800,
	XCTL_CAP_PTZ_MASK						= 0x00001000,
	XCTL_CAP_ALARM_ONOFF_MASK				= 0x00002000,
	XCTL_CAP_DVR_EVENT_RESET_MASK			= 0x00004000,
	XCTL_CAP_DVR_MANUAL_REC_CONTROL_MASK	= 0x00008000,
	XCTL_CAP_DVR_REC_STATUS_MASK			= 0x00010000,
	XCTL_CAP_MOTION_SEARCH_MASK				= 0x00020000,
	XCTL_CAP_OVERLAP_TRACK_SEARCH_MASK		= 0x00040000,	//+ jeongguc.kang <2011.10.19> 중복 구간 추가
	XCTL_CAP_POS_SEARCH_MASK				= 0x00080000,		//+ jeongguc.kang <2011.10.20> Search Pos 추가
	XCTL_CAP_POWER_RESTART_MASK				= 0x00100000,
	XCTL_CAP_BANDWIDTH_MASK					= 0x00200000,	//+ jeongguc.kang <2012.04.18> banamex 프로젝트 관련 Get Bandwidth 추가
	XCTL_CAP_SHUT_DOWN_MASK					= 0x00400000,	//+ jungkoo.kang Gucci PJT 추가
	XCTL_CAP_GET_PERMISSION_MASK			= 0x00800000,	//+ jungkoo.kang Gucci PJT 추가
	XCTL_CAP_SET_PERMISSION_MASK			= 0x01000000,	//+ jungkoo.kang Gucci PJT 추가
	XCTL_CAP_DIVIDE_VIDEO_AUDIO_MASK		= 0x02000000,
	XCTL_CAP3_RTP_METADATA_MASK				= 0x04000000,
	XCTL_CAP_DEVICE_LOG_BACKUP_MASK			= 0x08000000,	//+ jungkoo.kang <2015.03.05> Log backup 기능 추가
	XCTL_CAP_TEXT_MASK						= 0x10000000,
	XCTL_CAP_SEARCH_TEXT_CALENDAR_MASK		= 0x20000000,
	XCTL_CAP_NTP_MANAGEMENT_MASK			= 0x40000000,
	XCTL_CAP_THERMAL_MASK					= 0x80000000,
};

// XNS Command Match
enum	// Query
{
	XQRY_CONNECT = 1,
	XQRY_CONNECT_NONBLOCK,
	XQRY_DISCONNECT,
	XQRY_RECONNECT,
	XQRY_ACQUIRE_MEDIA_AUTHIRITY,
	XQRY_RELEASE_MEDIA_AUTHORITY,
	XQRY_OPEN_MEDIA,
	XQRY_CLOSE_MEDIA,
	XQRY_PLAY_MEDIA,
	XQRY_PAUSE_MEDIA,
	XQRY_SEEK_MEDIA,
	XQRY_FRAMEAD_MEDIA,
	XQRY_SEARCH_CALENDAR,
	XQRY_SEARCH_DAY,
	XQRY_TALK,
	XQRY_LISTEN,
	XQRY_SEND_AUDIO,
	XQRY_ALARM,
	XQRY_CONTROL_PTZ,	
	XQRY_CONTROL_PTZ_FREE_MOVE,
	XQRY_CONTROL_PTZ_SPEED_ZOOMIN,
	XQRY_CONTROL_PTZ_SPEED_ZOOMOUT,
	XQRY_CONTROL_PPTZ,
	XQRY_CONTROL_MENU,
	XQRY_EXECUTE_HPTZ,
	XQRY_GET_PRESET_LIST,
	XQRY_SET_PRESET,
	XQRY_DELETE_PRESET,
	XQRY_DELETE_PRESET_ALL,
	XQRY_UPLOAD_SW,
	XQRY_IMPORT_CFG,
	XQRY_EXPORT_CFG,
	XQRY_LOCALREC_START,
	XQRY_LOCALREC_STOP,
	XQRY_BACKUP_START,
	XQRY_BACKUP_STOP,
	XQRY_OPEN_STREAM,
	XQRY_CLOSE_STREAM,
	XQRY_REOPEN_ALL_STREAM,
	XQRY_SUSPEND_ALL_STREAM,
	XQRY_RESUME_ALL_STREAM,
	XQRY_SUSPEND_STREAM,
	XQRY_RESUME_STREAM,
	XQRY_DVR_EVENT_RESET,
	XQRY_DVR_RECORDING,
	XQRY_GET_MOTION_GRID,
	XQRY_MOTION_SEARCH,
	XQRY_SEND_SERIAL_DATA,

	// --> hh3.kim : ADD AREA ZOOM FUNCTIONS
	XQRY_AREA_ZOOM,
	XQRY_ZOOM_1X,
	// <-- hh3.kim : ADD AREA ZOOM FUNCTIONS

	// --> hh3.kim : ADD PTZ GET/SET FUNCTIONS  0
	XQRY_GET_PTZ_POS,
	XQRY_SET_PTZ_POS,
	// --> hh3.kim : ADD PTZ GET/SET FUNCTIONS  1
	XQRY_SEARCH_OVERLAP,	//+ jeongguc.kang <2011.10.19> 중복구간 추가
	//XQRY_SEARCH_POS,		//+ jeongguc.kang <2011.10.20> Search POS 추가
	//XQRY_CANCEL_POS,		//+ jeongguc.kang <2011.10.20> Cancel Pos 추가

	// hh3.kim : PTZ_POS+SPEED, POWER RESTART
	XQRY_GET_PTZ_POS_SPEED,
	XQRY_SET_PTZ_POS_SPEED,
	XQRY_POWER_RESTART,

	// hh3.kim : get hptz list
	XQRY_GET_HPTZ_LIST,
	
	//+ jeongguc.kang <2012.04.18> banamex 프로젝트 관련 bandwidth 커맨드 추가
	XQRY_GET_BANDWIDTH,
	XQRY_SET_BANDWIDTH,
	//+

	XQRY_GET_START_RECORDING_TIME,	//+ jungkoo.kang <2012.11.30> banamex 프로젝트 관련 GetRecordingTime API 추가
	XQRY_GET_END_RECORDING_TIME,	//+ jungkoo.kang <2012.11.30> banamex 프로젝트 관련 GetRecordingTime API 추가

	XQRY_SEND_AUDIO_2,
	XQRY_SHUT_DOWN,
	XQRY_GET_PERMISSION_CAPACITY,
	XQRY_GET_PERMISSION,
	XQRY_SET_PERMISSION,
	XQRY_CHANGE_DEVICE_ADMIN_PASSWORD,
	XQRY_LOG_BACKUP,		//+ jungkoo.kang <2015.03.05> Log backup 기능 추가

	XQRY_GET_PTZ_POS_NORMALIZE,	//20150714
	XQRY_SET_PTZ_POS_NORMALIZE,

	XQRY_SEARCH_TEXT_CALENDAR,
	XQRY_SEARCH_TEXT,
	XQRY_CANCEL_SEARCH_TEXT,
	XQRY_OPEN_TEXT,
	XQRY_CLOSE_TEXT,

	XQRY_GET_NTP_INFO,
	XQRY_SET_NTP_INFO,
	
	XQRY_GET_TEMPERATURE,
	XQRY_SET_THERMALALARM,
	XQRY_GET_THERMALALARM,

	XQRY_GET_RESOLUTIONCOUNT,
	XQRY_GET_RESOLUTIONINFO,
	XQRY_SET_RESOLUTIONINFO
};

enum	// Response or Event
{	
	XEVT_DEVICE_DETECTED = 1,
	XEVT_CONNECT_FAILED,
	XEVT_SEARCH_CALENDAR,
	XEVT_SEARCH_DAY,
	XEVT_PRESET_LIST,
	XEVT_UPLOAD_SW_PROGRESS,
	XEVT_IMPORT_CFG_PROGRESS,
	XEVT_EXPORT_CFG_PROGRESS,
	XEVT_MOTION,
	XEVT_SENSOR,
	XEVT_VIDEOLOSS,
	XEVT_HDD_FAIL,
	XEVT_HDD_FULL,
	// hh3.kim : XEVT_PASSWORD_CNAHGED --> XEVT_PASSWORD_CHANGED
	XEVT_PASSWORD_CHANGED,
	XEVT_FAN_BROKEN,
	// hh3.kim : XEVT_DEVICE_STATUS_CAHGED --> XEVT_DEVICE_STATUS_CHANGED
	XEVT_DEVICE_STATUS_CHANGED,
	XEVT_CONTROL_LOCAL_NAME_CHANGED,
	XEVT_CONTROL_REMOTE_NAME_CHANGED,
	// hh3.kim : XEVT_CONTROL_STATUS_CAHGED --> XEVT_CONTROL_STATUS_CHANGED
	XEVT_CONTROL_STATUS_CHANGED,
	// hh3.kim : XEVT_CONTROL_CAPABILITY_CAHGED --> XEVT_CONTROL_CAPABILITY_CHANGED
	XEVT_CONTROL_CAPABILITY_CHANGED,	
	XEVT_BACKUP_PROGRESS,
	XEVT_PTZ_CONTROL_FAILED,
	XEVT_ALARM_OUT_CONTROL_FAILED,
	XEVT_NEW_MEDIA,
	XEVT_GET_MOTION_GRID,
	XEVT_MOTION_SEARCH,
	XEVT_TALK_FAILED,
	XEVT_CALLBACK_EVENT,
	XEVT_SEND_SERIAL_DATA,

	// --> hh3.kim : ADD IV EVENT
	XEVT_IV_OCCUR,
	XEVT_GET_PTZ_POS,

	XEVT_AREA_ZOOM_MOVING,		//+ jeongguc.kang <2011.09.29>
	XEVT_SEARCH_OVERLAP,		//+ jeongguc.kang <2011.10.19> 중복 구간 추가
	XEVT_SEARCH_POS_LIST,		//+ jeongguc.kang <2011.10.20> Search Pos 추가
	XEVT_END_SEARCH_POS,

	// hh3.kim : GET_PTZ_POS + SPEED
	XEVT_GET_PTZ_POS_SPEED,
	XEVT_POWER_RESTART,
	
	// hh3.kim : HPTZ LIST
	XEVT_HPTZ_LIST,
	XEVT_DEVICE_INSTALLED,	// hh3.kim <2011-03-28> 디바이스 인스톨 이벤트
	
	XEVT_GET_BANDWIDTH,			//+ jeongguc.kang <2012.04.18> banamex 프로젝트 관련 Get Bandwidth 이벤트 추가
	XEVT_RECORDING_ERROR,		//+ jeongguc.kang <2012.04.18> banamex 프로젝트 관련 Recording Error 이벤트 추가
	XEVT_FAN_STATUS_CHANGED,	//+ jeongguc.kang <2012.07.07> banamex 프로젝트 관련 Fan Status Changed 이벤트 추가

	XEVT_VIDEO_FRAME_INFO_RECEIVED, //+ hh3.kim <2012-10-24> 프레임 정보 이벤트 추가 (iPOLiS Device Manager 대응)
	XEVT_HDD_NUM_CHANGED,		//+ jungkoo.kang <2012.11.27> OnHDDNumChanged 이벤트 추가
	XEVT_GET_START_RECORDING_TIME,	//+ jungkoo.kang <2012.11.30> banamex 프로젝트 관련 GetRecordingTime API 추가
	XEVT_GET_END_RECORDING_TIME,	//+ jungkoo.kang <2012.11.30> banamex 프로젝트 관련 GetRecordingTime API 추가
	XEVT_RECORDING_STATUS_CHANGED,	//+ jungkoo.kang <2013.02.26> 저장장치의 레코딩 시작/종료 이벤트 추가
	XEVT_NTP_SERVER_CONN_FAILED,	//+ jungkoo.kang <2013.04.11> banamex 프로젝트 관련 시간 동기화 필요 이벤트 추가
	XEVT_CPU_HIGH_CONSUMPTION,		//+ jungkoo.kang <2013.04.11> banamex 프로젝트 관련 CPU 성능 이벤트 추가
	XEVT_RAM_HIGH_CONSUMPTION,		//+ jungkoo.kang <2013.04.11> banamex 프로젝트 관련 RAM 성능 이벤트 추가
	XEVT_VIDEOLOSS_END,				//+ jungkoo.kang <2013.04.11> banamex 프로젝트 관련 VideoLoss End 이벤트 추가

	XEVT_SHUT_DOWN,
	XEVT_GET_PERMISSION_CAPACITY,
	XEVT_GET_PERMISSION,
	XEVT_SET_PERMISSION,

	XEVT_TRACKING_CHANGED,					// mj.shim <2014.10.15> Tracking Event
	XEVT_FACE_DETECTION_CHANGED,			// mj.shim <2014.10.15> Face Detection Event
	XEVT_AUDIO_DETECTION_CHANGED,			// mj.shim <2014.10.17> Audio Detection Event
	XEVT_AMD_CHANGED,						// mj.shim <2014.10.17> AMD Event
	XEVT_SYSTEM_CHANGED,					// mj.shim <2014.10.17> System Event

	XEVT_HDD_HIGH_TEMPERATURE,		//+ jungkoo.kang <2014.11.06> banamex 프로젝트 브랜치 머지

	XEVT_CHANGE_DEVICE_ADMIN_PASSWORD,		// mj.shim <2015.01.29> security user update event (change password)

	//+ jungkoo.kang <2015.03.05> Log backup 기능 추가
	XEVT_DEVICE_LOG_BACKUP,
	XEVT_DEVICE_LOG_BACKUP_END,

	XEVT_GET_PTZ_POS_NORMALIZE,
	XEVT_TEXT_OCCUR,
	XEVT_SEARCH_TEXT_CALENDAR,
	XEVT_SEARCH_TEXT_LIST,
	XEVT_END_SEARCH_TEXT,

	XEVT_GET_NTP_INFO,
	XEVT_SET_NTP_INFO,

	XEVT_GET_TEMPERATURE,
	XEVT_GET_THERMALALARM,
	XEVT_GET_RESOLUTIONCOUNT
};

//  mj.shim <2014.10.15> SubEvent
enum 
{
	XEVT_TRACKING_OCCUR = 1,
	XEVT_TRACKING_START,		//사용안함
	XEVT_TRACKING_END,			//사용안함
	
	XEVT_FACE_DETECTION_OCCUR,
	XEVT_FACE_DETECTION_START,	//사용안함
	XEVT_FACE_DETECTION_END,	//사용안함
	
	XEVT_AUDIO_DETECTION_OCCUR,				//  mj.shim <2014.10.17> Audio Detection Event
	XEVT_AUDIO_DETECTION_START,	//사용안함
	XEVT_AUDIO_DETECTION_END,	//사용안함

	XEVT_AMD_ROI_MOTION_DETECTION_START,	//  mj.shim <2014.10.17> AMD Event
	XEVT_AMD_ROI_MOTION_DETECTION_STOP,
	XEVT_AMD_LIB_LOAD_FAILED,
	XEVT_AMD_LOW_FPS_START,
	XEVT_AMD_LOW_FPS_END,
	XEVT_AMD_DSP_DISPLAY_START,
	XEVT_AMD_DSP_DISPLAY_FAIL,
	XEVT_AMD_DSP_VA_START,
	XEVT_AMD_DSP_VA_FAIL,

	XEVT_PROFILE_ADD,							// mj.shim <2014.10.17> System Event
	XEVT_PROFILE_CHANGED,
	XEVT_PROFILE_REMOVED,
	XEVT_BEING_UPDATED,
	XEVT_RECORD_FILTERING_START,
	XEVT_RECORD_FILTERING_STOP,
	XEVT_BATTERY_FAIL,
	XEVT_NETWORK_TRAFFIC_STATUS_OVERFLOW,
	XEVT_NETWORK_TRAFFIC_STATUS_RELEASE,
	XEVT_UPGRADE_LOG,
	XEVT_OVERWRITE_DECODING,
	XEVT_RAID_MODE_ENABLE,
	XEVT_RAID_MODE_DISABLE,
	XEVT_RAID_SETUP_CHANGE,
	XEVT_RAID_BUILD_CANCEL,
	XEVT_RAID_BUILD_FAIL,
	XEVT_RAID_REBUILDING_START,
	XEVT_RAID_REBUILDING_END,
	XEVT_RAID_REBUILDING_FAIL,
	XEVT_RAID_DEGRADED,
	XEVT_RAID_FAIL,
	XEVT_ISCSI_CONNECTED,
	XEVT_ISCSI_DISCONNECTED,
	XEVT_RECORDING_FRAME_DROP,
	XEVT_DUAL_SMPS_FAILURE,
	XEVT_DUAL_SMPS_RECOVERED,
	XEVT_INTERNAL_HDD_CONNECTED,
	XEVT_INTERNAL_HDD_DISCONNECTED,
	XEVT_USB_HDD_CONNECTED,
	XEVT_USB_HDD_DISCONNECTED,
	XEVT_BACKUP_START,
	XEVT_BACKUP_END,
	XEVT_ALARM_RESET,
	XEVT_RAID_DEVICE_ADD,
	XEVT_RAID_DEVICE_ADD_FAIL,
	XEVT_RAID_REC_RESTRICTION,

};

enum
{
	XPTZ_UP = 1,
	XPTZ_DOWN,
	XPTZ_LEFT,
	XPTZ_RIGHT,
	XPTZ_UPLEFT,
	XPTZ_UPRIGHT,
	XPTZ_DOWNLEFT,
	XPTZ_DOWNRIGHT,
	XPTZ_ZOOMIN,
	XPTZ_ZOOMOUT,
	XPTZ_STOP,	
	XPTZ_FOCUS_NEAR,
	XPTZ_FOCUS_FAR,
	XPTZ_FOCUS_STOP,
	XPTZ_IRIS_OPEN,	
	XPTZ_IRIS_CLOSE,
};

enum
{
	XMENU_UP = 1,
	XMENU_DOWN,
	XMENU_LEFT,
	XMENU_RIGHT,
	XMENU_ENTER,
	XMENU_ON,
	XMENU_OFF,
	XMENU_CANCEL,
};

enum 
{
	XHPTZ_PRESET = 1,
	XHPTZ_AUTOPAN,
	XHPTZ_SCAN,
	XHPTZ_PATTERN,
	XHPTZ_SWING,		// New HPTZ Command
	XHPTZ_TOUR,		// New HPTZ Command
};

enum
{
	XMEDIA_LIVE = 1,
	XMEDIA_PLAYBACK,
	XMEDIA_BACKUP,
	XMEDIA_METADATA,
	XMEDIA_TEXT_LIVE,
	XMEDIA_TEXT_PLAYBACK,
	XMEDIA_TEXT_BACKUP,
};

enum
{
	XREC_MOTION = 0x01,
	XREC_SENSOR = 0x02,
	XREC_VIDEOLOSS = 0x04,
	XREC_MANUAL = 0x08,
	XREC_CONTINUOS = 0x10,
	XREC_TRACKING = 0x20,
	XREC_FACE_DETECTION = 0x40,
	XREC_AUDIO_DETECTION = 0x80,
	XREC_AMD = 0x100,

	XREC_TYPE_ALL = 0xffff // hh3.kim <2012-04-24> 추가
};

enum
{
	XEVENT_ALL = 0x000000ff,
	XEVENT_SENSOR = 0x00000001,
	XEVENT_MOTION = 0x00000002,
	XEVENT_VIDEOLOSS = 0x00000004,
	// --> hh3.kim : ADD IV EVENT
	XEVENT_IV_OCCUR = 0x00000008,
	
	XEVENT_TRACKING = 0x00000010,			// mj.shim <2014.10.15> Tracking Event
	XEVENT_FACE_DETECTION = 0x00000020,		// mj.shim <2014.10.15> Face Detection Event
	XEVENT_AUDIO_DETECTION = 0x00000040,	// mj.shim <2014.10.17> Audio Detection Event
	XEVENT_AMD = 0x00000080,				// mj.shim <2014.10.17> AMD Event
	XEVENT_SYSTEM = 0x00000100,				// mj.shim <2014.10.17> System Event
	
};


enum {
	XMEDIA_PROTOCOL_TCP	= 0x00,
	XMEDIA_PROTOCOL_UDP,
	XMEDIA_PROTOCOL_MULTICAST,
	XMEDIA_PROTOCOL_TCP_HTTP, 
	XMEDIA_PROTOCOL_TCP_RTSP	
} ;

enum
{
	XDEVICE_PROTOCOL_UNKNOWN			= 0,
	XDEVICE_PROTOCOL_SUNAPI				= 1,
	XDEVICE_PROTOCOL_SVNP				= 2,
	XDEVICE_PROTOCOL_SVP				= 3,	// jungkoo.kang <2014.07.17> NVR, DVR SV프로토콜
};

enum
{
	XTHERMAL_ALARM_UNKNOWN				= 0,
	XTHERMAL_ALARM_ABOVE				= 1,
	XTHERMAL_ALARM_BELOW				= 2,
};

class IXnsDeviceEventHandler
{
public:
	virtual void			OnXnsDeviceEvent( long nEventID , ... ) = 0;
};

class IXnsTimeline
{
public:
	virtual long			GetCameraCount() = 0;
	virtual long			GetTimelineCount( long nCamIndex ) = 0;
	virtual void			GetTimeline( long nCamIndex , long nTlIndex , long nType , long* ptStart , long* ptEnd , long* pnRecType , long* pnRecID ) = 0;
	virtual long			GetTimelineIndex() = 0;
};

class IXnsPresetList
{
public:
	virtual long			GetPresetCount() = 0;
	virtual const char*		GetPreset( long nPresetIndex , long* pnNumber ) = 0;
};

class IXnsPermission
{
public:
	
};


class IXnsFileReader
{
public:
	virtual const char*		GetFileName() = 0;
	virtual IXnsMediaSource*GetMediaSource() = 0;
	virtual IXnsTimeline*	GetTimeline() = 0;
	virtual long			Play( double dSpeed ) = 0;
	virtual long			Pause() = 0;

	virtual long			Seek( long tPos ) = 0;
	virtual long			FrameAdvance( long nDelta ) = 0;
};

class IXnsDevice
{
public:	
	virtual long			GetDeviceID() = 0;
	virtual long			GetDeviceStatus() = 0;	
	
	virtual const char*		GetVendorName() = 0;
	virtual const char*		GetModelName() = 0;
	virtual const char*		GetDisplayName() = 0;
	virtual long			GetSetupPageStyle() = 0;
	virtual const char*		GetVersion() = 0;
	virtual long			GetAddressType() = 0;
	virtual const char*		GetIP() = 0;
	virtual const char*		GetMac() = 0;
	virtual const char*		GetURL() = 0;
	virtual const char*		GetDDNSID() = 0;
	virtual long			GetPort() = 0;
	virtual long			GetHttpPort() = 0;
	virtual const char*		GetUserID() = 0;
	virtual const char*		GetPassword() = 0;

	virtual long			IsSunapiProtocol() = 0;
	
	virtual void			SetConnectionInfo( const char* szVendorName , const char* szModelName , long nAddressType , const char* szAddress , long nPort , long nHttpPort , const char* szUserID , const char* szPassword, long nProtocolType, long nMediaProtocolType ) = 0;	
	
	virtual long			GetLatestUpdateTime() = 0;
	virtual long			GetDeviceUTC() = 0;
	virtual long			GetDeviceLocalTime() = 0;
	virtual BOOL			IsEmptyTimeInDST( long tLocal ) = 0;
	virtual BOOL			IsDuplicatedTimeInDST( long tLocal ) = 0;
	virtual long			LocalTimeToDeviceUTC( long tLocal ) = 0;
	virtual long			UTCToDeviceLocalTime( long tUTC ) = 0;
	virtual long			GetDeviceDSTStartUTC( long nYear ) = 0;
	virtual long			GetDeviceDSTEndUTC( long nYear ) = 0;

	virtual long			GetControlCount( long nType ) = 0;	
	virtual long			GetParentControlID( long nControlID ) = 0;
	virtual long			GetControlType( long nControlID ) = 0;
	virtual long			GetControlNumber( long nControlID ) = 0;
	virtual long			GetControlDepth( long nControlID ) = 0;
	virtual const char*		GetControlLocalName( long nControlID ) = 0;
	virtual const char*		GetControlRemoteName( long nControlID ) = 0;
	virtual long			GetControlStatus( long nControlID , long nStatusID ) = 0;
	virtual const char*		GetControlLinkStatus( long nControlID ) = 0;
	virtual BOOL			GetControlCapability( long nControlID , long nCapabilityID ) = 0;
	
	//+ jungkoo.kang <2013.03.21> Video Resolution,FrameRate,Quality,Codec 가져오는 API 추가
	virtual long			GetControlVideoResolution( long nControlID ) = 0;
	virtual long			GetControlVideoFrameRate( long nControlID ) = 0;
	virtual long			GetControlVideoQuality( long nControlID ) = 0;
	virtual const char*		GetControlVideoCodec( long nControlID ) = 0;
	//+

	virtual void			ChangeControlLocalName( long nControlID , const char* szName ) = 0;
	virtual void			ChangeControlRemoteName( long nControlID , const char* szName ) = 0;
	
	virtual long			LoadDeviceProfile() = 0;
	virtual long			SaveDeviceProfile() = 0;
	virtual long			DeleteDeviceProfile() = 0;
	
	virtual BOOL			IsPlaying() = 0;
	virtual BOOL			HasAuthority() = 0;

	virtual long			SendXnsQuery( long nQueryID , ... ) = 0;

	virtual long			SetVideoInfoReceived(long nControlID, long nMediaType, long bFlag) = 0;

	virtual long			GetTalkInfo_Codec(long nControlID) = 0;
	virtual long			GetTalkInfo_SampleRate(long nControlID) = 0;
	virtual long			GetTalkInfo_BitsPerSample(long nControlID) = 0;
	virtual long			GetTalkInfo_Channel(long nControlID) = 0;
	virtual long			GetTalkInfo_PacketSize(long nControlID) = 0;

	virtual long			GetVideoControlID(long nCameraIndex, long nVideoIndex) = 0;
	virtual long			GetResolutionInfo(long nCount, long* nVideoWidth, long* nVideoHeight, long* nVideoFramerate) = 0;

//	virtual long			GetTemperature(long nChannel) = 0;
};

