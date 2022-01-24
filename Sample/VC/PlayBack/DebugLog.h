#include "PlayBackDlg.h"

// Macro for OutputDebugString()
#define DBG_LOG(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("(%S:%d)"), __FUNCTION__, __LINE__);	\
	strMessage.AppendFormat(__VA_ARGS__);\
	OutputDebugString(strMessage);\
}while(0);

// Macro for AfxMessageBox()
#define ERROR_BOX(...) do{\
	CString strMessage = _T("");\
	strMessage.Format(__VA_ARGS__);\
	AfxMessageBox(strMessage);\
}while(0);

// Macro for EditText control (Device control)
#define WLOGD(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("[XnsSdkDevice] "));\
	strMessage.AppendFormat(__VA_ARGS__);\
	long nLen = m_ctrlEditLog.GetWindowTextLength(); \
	m_ctrlEditLog.SetFocus(); \
	m_ctrlEditLog.SetSel(nLen, nLen); \
	m_ctrlEditLog.ReplaceSel(strMessage+_T("\n")); \
}while(0);

// Macro for EditText control (Window control)
#define WLOGW(...) do{\
	CString strMessage = _T("");\
	strMessage.AppendFormat(_T("[XnsSdkWindow] "));\
	strMessage.AppendFormat(__VA_ARGS__);\
	long nLen = m_ctrlEditLog.GetWindowTextLength(); \
	m_ctrlEditLog.SetFocus(); \
	m_ctrlEditLog.SetSel(nLen, nLen); \
	m_ctrlEditLog.ReplaceSel(strMessage+_T("\n")); \
}while(0);

