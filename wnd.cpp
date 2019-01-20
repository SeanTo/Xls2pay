#include "stdafx.h"
#include "wnd.h"

////////////////////////////////////////////////////////////////////////////////
#ifdef  _USE_WND_

#include "tlhelp32.h"

BOOL WND::IsCharDown(int ch)
{
	if( _istlower(ch) )
		ch = toupper(ch);
	
	if( ch >= _T('A') && ch <= _T('Z') || ch >= _T('0') && ch <= _T('9') )
		return GetKeyState(ch) < 0;
	
	return FALSE;
}

CString WND::GetAbsPath(BOOL bIsTemp/* == FALSE*/)
{
	TCHAR tszBuf[MAX_PATH];

	if( bIsTemp)
		::GetTempPath(MAX_PATH, tszBuf);
	else
		::GetModuleFileName(NULL, tszBuf, MAX_PATH);
	
	CString str(tszBuf);
	str.TrimRight(_T('\\'));
	str += _T(_T("\\"));

	return str;
}

CString WND::GetExeName()
{
	TCHAR tszBuf[MAX_PATH + 1];
	GetModuleFileName(NULL, tszBuf, MAX_PATH);
	
	CString str(tszBuf);
	str = str.Mid(str.ReverseFind(_T('\\')) + 1);
	return str;
}

/*
 *	���������ʹ��ڱ�����Ҵ��ڣ����������ᵽǰ̨
 */
VOID WND::ActiveWindow(LPCTSTR lpszClassName, LPCTSTR lpszWindowName /* = NULL */)
{
	// �����ڵ���ǰ̨
	CWnd *pWnd = CWnd::FindWindow(lpszClassName, lpszWindowName);
	
	if(pWnd != NULL)
	{
		pWnd->SetForegroundWindow();
		pWnd->ShowWindow(SW_SHOW);
		pWnd->ShowWindow(SW_RESTORE);
		
//		CWnd* pWndPopup = pWnd->GetLastActivePopup();
//		if(pWnd != pWndPopup)
//			pWndPopup->SetForegroundWindow();
	}
}

/*
 *	���� pctsExeName ָ���Ŀ�ִ�г����Ƿ�����
 *  ��������ʱ�������н��̵� PID�����򷵻� -1
 *  ��Ҫͷ�ļ� tlhelp32.h
 */
DWORD WND::FindAppProcessID(LPCTSTR pctsExeName)
{
	HANDLE handle=::CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	
	PROCESSENTRY32 Info;
	Info.dwSize = sizeof(PROCESSENTRY32);
	
	if(::Process32First(handle, &Info))
	{
		CString ss = _T("");
		do{
			ss = Info.szExeFile;
			if( !ss.CompareNoCase(pctsExeName) )
			{
				::CloseHandle(handle);
				return Info.th32ProcessID;
			}
		}
		while(::Process32Next(handle, &Info));
		
		::CloseHandle(handle);
	}
	
	return -1;
}

// void WND::ClearComboBox(CComboBox &cmb, int hode/* = 0*/)
// {
// 	int iCnt = cmb.GetCount();
// 	
// 	for(int i = iCnt - 1; i >= hode; --i)
// 		cmb.DeleteString(i);
// }

/*
 *	ʾ�� SelectDirectory( GetSafeHwnd() );
 */
CString WND::SelectDirectory(HWND hWnd/* = NULL*/)
{
	CString str = _T("");
	TCHAR		buf[MAX_PATH + 1];
	TCHAR		path[MAX_PATH + 1];
	lstrcpy(path, _T(""));
	
	BROWSEINFO	m_pbi;
	::ZeroMemory( &m_pbi, sizeof(BROWSEINFO) );
	m_pbi.hwndOwner			= hWnd;
	m_pbi.pidlRoot			= NULL;
	m_pbi.pszDisplayName	= buf;
	m_pbi.lpszTitle			= _T("ѡ����Ŀ¼");
	m_pbi.ulFlags			= BIF_RETURNONLYFSDIRS;
    
	ITEMIDLIST *idl =  SHBrowseForFolder(&m_pbi);
	if( idl )
	{
		SHGetPathFromIDList(idl, buf);
		str = CString(buf);
	}
	
	return str;
}

/*
 *  ʾ��
 *	SelectFile(FALSE, _T("txt"), _T("�ı��ļ�(*.TXT)|*.txt|����ת��(*.PAY)|*.pay||"), strFileName );
 */
CString WND::SelectFile(BOOL bIsOpen, LPCTSTR szExt, LPCTSTR szFilter, LPCTSTR szPath)
{
	CString str = szPath;
	TCHAR tszFile[MAX_PATH + 1] = { _T('\0') };
	
	if( ! str.IsEmpty() )
		lstrcpy(tszFile, str);
	
	CFileDialog dlg(bIsOpen, szExt, szPath,NULL, szFilter, NULL);
	
	if( IDOK == dlg.DoModal() )
		str = dlg.GetPathName();
	else
		str.Empty();
	
	return str;
}

#endif // _USE_WND_
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#ifdef _USE_EMFC_

CString EMFC::STL2MFC(string ss)
{
	CString str;
	str.Format(_T("%s"), ss.c_str());
	return str;
}

CString EMFC::STL2MFC(char* ss)
{
	CString str;
	str.Format(_T("%s"), ss);
	return str;
}

string EMFC::MFC2STL(CString str)
{
	string ss;
	ss.append(str.GetBuffer(str.GetLength()));
	str.ReleaseBuffer();
	return ss;
}

// ���ִ�
BOOL EMFC::IsNumber(const CString &str, const CString &ss/* = _T("")*/)
{
	if( str.IsEmpty() )
		return FALSE;
	
	CString strDigit = _T("1234567890") + ss;
	
	for(int i = 0; i < str.GetLength(); ++i)
	{
		if( !IsInArray( str.GetAt(i), strDigit) )
			return FALSE;
	}
	
	return TRUE;
}

// ������
BOOL EMFC::IsFloat(const CString &str, int *pNum/* = NULL*/)
{
	int iDot = str.ReverseFind(_T('.'));
	if(-1 == iDot)
		return FALSE;

	int iLen = str.GetLength();
	if(NULL != pNum)
		*pNum = iLen - iDot - 1;

	if( !IsNumber(str.Left(iDot)) || !IsNumber(str.Right(iLen-iDot-1)) )
		return FALSE;
	
	return TRUE;
}

// ������
// BOOL EMFC::IsFloat(const CString &str, int l/*=11*/, int r/*=2*/)
// {
// 	int iLen = str.GetLength();
// 	if(iLen > l + 1 + r || iLen < 2 + r)
// 		return FALSE;
// 	
// 	if( !IsNumber(str.Right(r)) || !IsNumber(str.Left(iLen-1-r)) || _T('.') != str.Right(1+r)[0] )
// 		return FALSE;
// 	
// 	return TRUE;
// }

/*
 *	�����ַ�
 */
CString& EMFC::Trim(CString &str, const CString &sf/* =_T */)
{
	if(sf.IsEmpty())
		return str;

	for(int i = 0; i < sf.GetLength(); ++i)
		str.Replace( sf.GetAt(i), _T(' '));
	
	str.Replace(_T(" "), _T(""));
	return str;
}

/*
 * �����ظ��ַ�
 */
int EMFC::ExcludeSame(CString &str)
{
	int i = str.GetLength() - 1;
	if( i < 1)
		return i;
	
	int n;
	while(i > 0)
	{
		n = str.Find(str.GetAt(i));
		if( -1 != n && n < i )
			str.Delete(i);
		
		--i;
	}
	
	return str.GetLength();
}

/*
 *	���������е��ظ���
 */
int EMFC::ExcludeSame(CUIntArray &arr, BOOL bOrder /*= TRUE*/)
{
	int i = arr.GetSize() - 1;

	if(i < 1)
		return i;

	int n;
	while(i > 0)
	{
		if( FindArray(arr[i], arr, 0, i) )
			arr.RemoveAt(i);
		else if( !bOrder )
		{
			n = (arr[i] % 10) * 10 + arr[i] / 10 % 10;

			if( FindArray(n, arr, 0, i) )
				arr.RemoveAt(i);
		}
		
		--i;
	}

	return arr.GetSize();
}

/*
 *	���������еĿմ�
 */
int EMFC::ExcludeNull(CStringArray &arr)
{
	int i = arr.GetSize() - 1;
	
	while(i > 0)
	{
		if( arr[i].IsEmpty() )
			arr.RemoveAt(i);
		
		--i;
	}
	
	return arr.GetSize();
}

/*
 * ��ӡ����ǰ�� iSt - iEnd(����) ֮���Ԫ��
 */
CString EMFC::PrintArray(const CUIntArray &arr,
						 int iSt /* = 0 */, int iEnd /*= -1*/,
						 const CString strSeparator /* = _T("") */,
						 const CString strFmt/* = _T("%d")*/ )
{
	CString str = _T("");
	int iCount = arr.GetSize();
	if(0 == iCount)
		return str;

	if(iEnd < 0 || iEnd > iCount)
		iEnd = iCount;
	
	CString ss;
	for(int i = iSt; i < iEnd; ++i)
	{
		ss.Format(strFmt, arr[i]);
		if( iSt == i)
			str = ss;
		else
			str += ss + strSeparator;
	}
// 	str = str.Left(str.GetLength() - strSeparator.GetLength() );
	
	return str;
}

/*
 *	��������bAsc = TRUE Ϊ����FALSE Ϊ����
 */
VOID EMFC::SortArray(CUIntArray &arr, BOOL bAsc /* = TRUE */)
{
	int len = arr.GetSize();
	if(len < 2)
		return;
	
	int k, num;
	for(int i = 0; i < (len - 1); ++i)
	{
		k = i;
		for(int j = i + 1; j < len; ++j)
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

int EMFC::FindArray(const UINT e, const CUIntArray &arr, int end/*=-1*/, int st/*=0*/)
{
	if(end < 0 || end > arr.GetSize())
		end = arr.GetSize();
	
	for(int i = st; i < end; ++i)
	{
		if( e == arr[i] )
			return i;
	}
	return -1;
}

int EMFC::FindArray(const CString &e, const CStringArray &arr, int end/*=-1*/, int st/*=0*/)
{
	if(end < 0 || end > arr.GetSize())
		end = arr.GetSize();
	
	for(int i = st; i < end; ++i)
	{
		if( e == arr[i] )
			return i;
	}
	return -1;
}

/*
 * �� str �в������� n
 * �ҵ��������������򷵻� -1
 */
int EMFC::FindArray(TCHAR ch, const CString &str, int end/* = -1*/, int st /*= 0*/)
{
	int len = str.Find(ch, st);
	return (-1 != len) && (len < end || -1 == end) ? len : -1;
}

#endif // _USE_EMFC_
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#ifdef _USE_DATE_

CTime MyDT::day = CTime::GetCurrentTime();

const CString MyDT::m_WEEK[] = {
	_T("������"), _T("����һ"), _T("���ڶ�"), _T("������"), _T("������"), _T("������"), _T("������")
};

#endif // _USE_DATE_
////////////////////////////////////////////////////////////////////////////////
