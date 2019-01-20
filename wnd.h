#ifndef _WND_H_
#define _WND_H_

#include "string"
using std::string;

#define _USE_WND_
#define _USE_EMFC_
#define _USE_DATE_

////////////////////////////////////////////////////////////////////////////////
#ifdef  _USE_WND_

class WND
{
public:
	// �ж��ļ���Ŀ¼�Ƿ����
	static inline BOOL IsExistFile(const CString &strFile) { return GetFileAttributes(strFile) != 0xFFFFFFFF; }
	
	// �����Ƽ��Ƿ���
	static inline BOOL IsCtrlDown() { return GetKeyState(VK_CONTROL) < 0; }
	static inline BOOL IsShiftDown() { return GetKeyState(VK_SHIFT) < 0; }
	static inline BOOL IsAltDown() { return GetKeyState(VK_MENU) < 0; }
	
	// ����ַ����Ƿ񰴼���(A-Z��0-9)
	static BOOL IsCharDown(int ch);
	
	// Ŀ¼
	static CString GetAbsPath(BOOL bIsTemp=FALSE);
	static CString GetExeName();

	// �����ᵽǰ̨
	static VOID ActiveWindow(LPCTSTR lpszClassName, LPCTSTR lpszWindowName=NULL); 
	
	// �����������еĿ�ִ�г���
	static DWORD FindAppProcessID(LPCTSTR pctsExeName);

	// �ؼ�
public:
	// ��������б��
// 	static void ClearComboBox(CComboBox &cmb, int hode = 0);
	// �򿪶Ի���
	static CString SelectDirectory(HWND hWnd=NULL);
	static CString SelectFile(BOOL bIsOpen, LPCTSTR strExt=NULL, LPCTSTR szFilter=_T("�����ļ�(*.*)|*.*"), LPCTSTR  szPath=_T("") );
	
};

#endif	// _USE_WND_
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#ifdef _USE_EMFC_

#include "afxtempl.h"

class EMFC
{
public:
	// MFC-STL ��ת��
	static CString STL2MFC(string ss);
	static CString STL2MFC(char* ss);
	static string MFC2STL(CString str);
	// �����ж�
	static BOOL IsNumber(const CString &str, const CString &ss = _T(""));
	static BOOL IsFloat(const CString &str, int *pNum=NULL);
// 	static BOOL IsFloat(const CString &str, int l=11, int r=2);
	// �����ַ�
	static CString& Trim(CString &str, const CString &sf=_T("^�� "));

public:
	// �����ظ��ַ�
	static int ExcludeSame(CString &str);
	// �ų������ظ���
	static int ExcludeSame(CUIntArray &arr, BOOL bOrder = TRUE);
	// �ų��ַ��������еĿմ�
	static int ExcludeNull(CStringArray &arr);

public:
	// ��ӡ����ǰ�� st - end(����) ֮���Ԫ��
 	static CString PrintArray(const CUIntArray &arr, int iSt=0, int iEnd=-1, const CString strSeparator=_T(""), const CString strFmt=_T("%d"));

	// ��������
public:
	template <typename T>
	static void SortArray(T arr[], int n, BOOL bAsc=TRUE)
	{
		if(n <= 1)
			return;

		T k, num;
		for(int i = 0; i < n-1; ++i)
		{
			k = i;
			for(int j = i + 1; j < n; ++j)
			{
				if( bAsc && arr[k]>arr[j] || !bAsc && arr[k]<arr[j] )
					k = j;
			}
			
			if(k > i)
			{
				num = arr[i];
				arr[i] = arr[k];
				arr[k] = num;
			}
		}
	}

	static void SortArray(CUIntArray &arr, BOOL bAsc=TRUE);


	// �������
public:

	template <typename T>
	static int  FindArray(const T e, const T arr[], int end, int st=0)
	{
		for(int i = st; i < end; ++i)
		{
			if( e == arr[i] )
				return i;
		}
		return -1;
	}
	
	template <typename T>
	static BOOL IsInArray(const T e, const T arr[], int end, int st=0) { return -1 != FindArray(e, arr, end, st); }

	template <typename T>
	static int  FindArray(const T e, const CArray<T, T> &arr, int end=-1, int st=0)
	{
		if(end < 0)	
			end = arr.GetSize();

		for(int i = st; i < end; ++i)
		{
			if( e == arr[i] )
				return i;
		}
		return -1;
	}
	
	template <typename T>
	static BOOL IsInArray(const T e, const CArray<T, T> &arr, int end=-1, int st=0) { return -1 != FindArray(e, arr, end, st); }
	
	static int  FindArray(const UINT e, const CUIntArray &arr, int end=-1, int st=0);
	static BOOL IsInArray(const UINT e, const CUIntArray &arr, int end=-1, int st=0) { return -1 != FindArray((UINT)e, arr, end, st); }
	
	static int  FindArray(const CString &e, const CStringArray &arr, int end=-1, int st=0);
	static BOOL IsInArray(const CString &e, const CStringArray &arr, int end=-1, int st=0) { return -1 != FindArray(e, arr, end, st); }
	
	static int  FindArray(TCHAR ch, const CString &str, int end = -1, int st = 0);
	static BOOL IsInArray(TCHAR ch, const CString &str, int end = -1, int st = 0) { return -1 != FindArray(ch, str, end, st); }

	static int  FindArray(int n, const CString &str, int end = -1, int st = 0) { return -1 != FindArray(_T('0')+n, str, end, st); }
	static BOOL IsInArray(int n, const CString &str, int end = -1, int st = 0) { return -1 != FindArray(_T('0')+n, str, end, st); }
};


#endif // _USE_EMFC_
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#ifdef _USE_DATE_

class MyDT
{
public:
	static void SetNow() { day = CTime::GetCurrentTime(); }

public:
	static int Year()	{ return day.GetYear(); }
	static int Mon()	{ return day.GetMonth(); }
	static int Day()	{ return day.GetDay(); }
	static int Week()	{ return day.GetDayOfWeek() - 1; }

	static int Hour()	{ return day.GetHour(); }
	static int Min()	{ return day.GetMinute(); }
	static int Sec()	{ return day.GetSecond(); }

	static CString Week(LPCTSTR szWeek[]) { return NULL!=szWeek ? szWeek[Week()] : m_WEEK[Week()]; }

	static CString Int2Str(int iNum, LPCTSTR szFmt = _T("%d") )
	{
		CString str;
		str.Format(szFmt, iNum);
		return str;
	}

public:
	// ����
	static BOOL IsLeapYear(int nYear)
	{
		ASSERT(nYear > 0);
		return 0 == (nYear%4) && 0 != (nYear%100) || 0 == (nYear%400);
	}

	static CString Today(LPCTSTR ss=_T("-"))
	{
		CString str;
		str.Format( _T("%04d%s%02d%s%02d"), day.GetYear(), ss, day.GetMonth(), ss, day.GetDay() );
		return str;
	}

	static CString Now(LPCTSTR ss=_T(":"))
	{
		CString str;
		str.Format( _T("%02d%s%02d%s%02d"), day.GetHour(), ss, day.GetMinute(), ss, day.GetSecond() );
		return str;
	}

public:
	static CTime day;

public:
	static const CString m_WEEK[];
};

#endif // _USE_DATE_
////////////////////////////////////////////////////////////////////////////////

#endif // _WND_H_
