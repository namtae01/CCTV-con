namespace Startup
{
    public partial class StartupDlg
    {
        public enum XBackupFormat
        {
            BACKUP_SEC = 1,
            BACKUP_REC
        }

        public enum XSnapshotFormat
        {
            SNAPSHOT_BMP = 0,
            SNAPSHOT_JPG
        }

        public enum XOSDType
        {
            OSD_TIME1 = 0x0001,
            OSD_TIME2 = 0x0002,
            OSD_IPS = 0x0004,
            OSD_CAMNAME = 0x0008,
            OSD_SPEED = 0x0010,
            OSD_PTZ = 0x0020,
            OSD_LISTEN = 0x0040,
            OSD_TALK = 0x0080,
            OSD_SENSOR = 0x0100,
            OSD_MOTION = 0x0200,
            OSD_RECORDING = 0x0400,
            OSD_ALL = 0xFFFF
        }

        public enum XMediaType
        {
            XMEDIA_LIVE = 1,
            XMEDIA_PLAYBACK,
            XMEDIA_BACKUP
        };

        public enum XLocalRecordingType
        {
            SEC_WRITTING = 1,
            REC_WRITTING
        }

        public enum XPTZControl
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

        public enum XPTZMenu
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

        public enum XHPTZFunction
        {
            XHPTZ_PRESET = 1,
            XHPTZ_AUTOPAN,
            XHPTZ_SCAN,
            XHPTZ_PATTERN,
        };

        public enum XRecType
        {
            XREC_ALL = 0xFF,
            XREC_MOTION = 0x01,
            XREC_SENSOR = 0x02,
            XREC_VIDEOLOSS = 0x04,
            XREC_MANUAL = 0x08,
            XREC_CONTINUOS = 0x10
        };

        public enum XEventType
        {
            XEVENTTYPE_ALL = 0xFF,
            XEVENTTYPE_ALARM = 0x01,
            XEVENTTYPE_MOTION = 0x02,
            XEVENTTYPE_VIDEOLOSS = 0x04
        };

        public enum XAddressType
        {
            XADDRESS_STATICIP = 1,
            XADDRESS_URL,
            XADDRESS_SSDDNS,
            XADDRESS_S1DDNS
        };

        public enum XErrorCode
        {
            ERR_SUCCESS = 0,
            ERR_UNKNOWN,
            // Initialize
            ERR_INVALID_CFG_FILE,
            ERR_ALREADY_INITIALIZE,
            ERR_NOT_INITIALIZE,
            // Device Connection
            ERR_NOT_SUPPORTED_DEVICE,
            ERR_EXCEED_CONNECTION,
            ERR_NOT_CONNECT,
            ERR_MAC_CONFLICT,
            ERR_INVALID_VERSION,
            ERR_INVALID_MODEL,
            ERR_ALREADY_CONNECT,
            // Login Error
            ERR_INVALID_USERID,
            ERR_WRONG_PASSWORD,
            ERR_ADMIN_CONFLICT,
            ERR_USER_FULL,
            // Query Request
            ERR_XNS_BUSY,
            ERR_BAD_NETWORK,
            ERR_REQUEST_TIME_OUT,
            ERR_INVALID_PARAMETER,
            ERR_NO_PERMISSION,
            ERR_NOT_SUPPORTED_COMMAND,
            // File Transfer
            ERR_INVALID_FILE,
            ERR_UPLOAD_FAIL,
            ERR_IMPORT_FAIL,
            ERR_EXPORT_FAIL,
            ERR_FILE_TRANSFERRING,
            // Media Open
            ERR_MEDIA_ALREADY_OPEND,
            // PTZ Control
            ERR_PTZ_CONFLICT,
            // XnsWindow Error
            ERR_INVALID_OBJID,
            ERR_ALREADY_RUN,
            ERR_MEDIA_NOT_OPENED,
            ERR_MEDIA_PAUSED,
            ERR_MEDIA_PLAYED,
            ERR_MEDIA_DISCONNECTED,
            // File Error
            ERR_FILE_ALREADY_OPEND,
            ERR_FILE_NOT_OPEND,
            ERR_FILE_OPEN,
            ERR_FILE_SEEK,
            ERR_FILE_READ,
            ERR_FILE_WRITE,
            ERR_WRITE_LIMITED,
            ERR_INVALID_FRAME,
            ERR_READ_END,
            ERR_ALREADY_RECORDED,
            ERR_BACKUP_DOING,
            ERR_DISK_FULL,
            ERR_WRITE_EMPTY,
            // DataMan
            ERR_DEVICE_FULL,
            ERR_DEVICE_CONFLICT,
            ERR_GROUP_FULL,
            ERR_GROUP_DEVICE_FULL,
            ERR_GROUP_DEVICE_CONFLICT,
            ERR_GROUP_FAVORITE_FULL,
            ERR_NAME_CONFLICT,
            ERR_USERID_CONFLICT,
            ERR_USERID_FULL,
        };
    }
}