using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;
using System.Threading;

using System.Media;
using HANDLE = System.IntPtr;

namespace ListenTalk
{
    public partial class ListenTalkForm
    {
        // WaveInOpen
        [DllImport("winmm.dll")]
        private static extern uint waveInOpen(ref IntPtr HwaveIn, uint deviceId,
           ref WAVEFORMATEX wfx, IntPtr dwCallBack, uint dwInstance, uint dwFlags);

        // WaveInAddBuffer
        [DllImport("winmm.dll", EntryPoint = "waveInAddBuffer", SetLastError = true)]
        public static extern uint waveInAddBuffer(IntPtr hwi, ref WAVEHDR pwh, uint cbwh);

        // WaveInPrepareHeader
        [DllImport("winmm.dll", SetLastError = true)]
        public static extern MMRESULT waveInPrepareHeader(IntPtr hwi, ref WAVEHDR pwh, uint cbwh);

        // WaveInUnPrepareHeader
        [DllImport("winmm.dll", SetLastError = true)]
        static extern MMRESULT waveInUnprepareHeader(IntPtr hwi, ref WAVEHDR pwh, uint cbwh);

        // CreateEvent
        [DllImport("kernel32.dll")]
        static extern IntPtr CreateEvent(IntPtr lpEventAttributes, bool bManualReset, bool bInitialState, string lpName);

        // WaveInStart
        [DllImport("winmm.dll", SetLastError = true)]
        static extern uint waveInStart(IntPtr hwi);

        // WaveInStop
        [DllImport("winmm.dll", SetLastError = true)]
        static extern uint waveInStop(IntPtr hwi);

        // WaveInReset
        [DllImport("winmm.dll", SetLastError = true)]
        static extern uint waveInReset(IntPtr hwi);

        // WaveInClose
        [DllImport("winmm.dll", SetLastError = true)]
        static extern uint waveInClose(IntPtr hwi);

        // WaitForSingleObject
        [DllImport("kernel32.dll", SetLastError = true)]
        static extern UInt32 WaitForSingleObject(IntPtr hHandle, UInt32 dwMilliseconds);


        [StructLayout(LayoutKind.Sequential)]
        struct WAVEFORMATEX
        {
            public ushort wFormatTag;
            public ushort nChannels;
            public uint nSamplesPerSec;
            public uint nAvgBytesPerSec;
            public ushort nBlockAlign;
            public ushort wBitsPerSample;
            public ushort cbSize;
        }

        public enum MMRESULT : uint
        {
            MMSYSERR_NOERROR = 0,
            MMSYSERR_ERROR = 1,
            MMSYSERR_BADDEVICEID = 2,
            MMSYSERR_NOTENABLED = 3,
            MMSYSERR_ALLOCATED = 4,
            MMSYSERR_INVALHANDLE = 5,
            MMSYSERR_NODRIVER = 6,
            MMSYSERR_NOMEM = 7,
            MMSYSERR_NOTSUPPORTED = 8,
            MMSYSERR_BADERRNUM = 9,
            MMSYSERR_INVALFLAG = 10,
            MMSYSERR_INVALPARAM = 11,
            MMSYSERR_HANDLEBUSY = 12,
            MMSYSERR_INVALIDALIAS = 13,
            MMSYSERR_BADDB = 14,
            MMSYSERR_KEYNOTFOUND = 15,
            MMSYSERR_READERROR = 16,
            MMSYSERR_WRITEERROR = 17,
            MMSYSERR_DELETEERROR = 18,
            MMSYSERR_VALNOTFOUND = 19,
            MMSYSERR_NODRIVERCB = 20,
            WAVERR_BADFORMAT = 32,
            WAVERR_STILLPLAYING = 33,
            WAVERR_UNPREPARED = 34
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct WAVEHDR
        {
            public IntPtr lpData; // pointer to locked data buffer
            public uint dwBufferLength; // length of data buffer
            public uint dwBytesRecorded; // used for input only
            public IntPtr dwUser; // for client's use
        //    public WaveHdrFlags dwFlags; // assorted flags (see defines)
            public uint dwLoops; // loop control counter
            public IntPtr lpNext; // PWaveHdr, reserved for driver
            public IntPtr reserved; // reserved for driver
        }

        [Flags]
        enum WaveHdrFlags : uint
        {
            WHDR_DONE = 1,
            WHDR_PREPARED = 2,
            WHDR_BEGINLOOP = 4,
            WHDR_ENDLOOP = 8,
            WHDR_INQUEUE = 16
        }

        public enum MMSYSERR : uint
        {
            // Add MMSYSERR's here!

            MMSYSERR_BASE = 0x0000,
            MMSYSERR_NOERROR = 0x0000,
            MMSYSERR_ERROR = (MMSYSERR_BASE + 1),  /* unspecified error */
            MMSYSERR_BADDEVICEID = (MMSYSERR_BASE + 2),  /* device ID out of range */
            MMSYSERR_NOTENABLED = (MMSYSERR_BASE + 3),  /* driver failed enable */
            MMSYSERR_ALLOCATED = (MMSYSERR_BASE + 4),  /* device already allocated */
            MMSYSERR_INVALHANDLE = (MMSYSERR_BASE + 5),  /* device handle is invalid */
            MMSYSERR_NODRIVER = (MMSYSERR_BASE + 6),  /* no device driver present */
            MMSYSERR_NOMEM = (MMSYSERR_BASE + 7),  /* memory allocation error */
            MMSYSERR_NOTSUPPORTED = (MMSYSERR_BASE + 8),  /* function isn't supported */
            MMSYSERR_BADERRNUM = (MMSYSERR_BASE + 9),  /* error value out of range */
            MMSYSERR_INVALFLAG = (MMSYSERR_BASE + 10), /* invalid flag passed */
            MMSYSERR_INVALPARAM = (MMSYSERR_BASE + 11), /* invalid parameter passed */
            MMSYSERR_HANDLEBUSY = (MMSYSERR_BASE + 12), /* handle being used */
            MMSYSERR_INVALIDALIAS = (MMSYSERR_BASE + 13), /* specified alias not found */
            MMSYSERR_BADDB = (MMSYSERR_BASE + 14), /* bad registry database */
            MMSYSERR_KEYNOTFOUND = (MMSYSERR_BASE + 15), /* registry key not found */
            MMSYSERR_READERROR = (MMSYSERR_BASE + 16), /* registry read error */
            MMSYSERR_WRITEERROR = (MMSYSERR_BASE + 17), /* registry write error */
            MMSYSERR_DELETEERROR = (MMSYSERR_BASE + 18), /* registry delete error */
            MMSYSERR_VALNOTFOUND = (MMSYSERR_BASE + 19), /* registry value not found */
            MMSYSERR_NODRIVERCB = (MMSYSERR_BASE + 20), /* driver does not call */
            MMSYSERR_MOREDATA = (MMSYSERR_BASE + 21), /* more data to be returned */
            MMSYSERR_LASTERROR = (MMSYSERR_BASE + 21), /* last error in range */
        }

        [Flags]
        enum WaveInOpenFlags : uint
        {
            CALLBACK_NULL = 0,
            CALLBACK_FUNCTION = 0x30000,
            CALLBACK_EVENT = 0x50000,
            CALLBACK_WINDOW = 0x10000,
            CALLBACK_THREAD = 0x20000,
            WAVE_FORMAT_QUERY = 1,
            WAVE_MAPPED = 4,
            WAVE_FORMAT_DIRECT = 8
        }
    
    }
}