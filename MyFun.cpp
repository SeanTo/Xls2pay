#include "stdafx.h"
#include "tlhelp32.h"
#include "MyFun.h"

/*
 *	数组排序，bAsc = TRUE 为升序、FALSE 为降序
 */
VOID MyFun::SortArray(CUIntArray &arr, BOOL bAsc /* = TRUE */)
{
	int len = arr.GetSize();

	if(len < 2)
		return;
	
	int k, num;
	for(int i = 0; i < (len- 1); ++i)
	{
		k = i;
		for(int j = i + 1; j < len; ++j)
		{
			if(bAsc)
			{
				if(arr[k] > arr[j])
					k = j;
			}
			else
			{
				if(arr[k] < arr[j])
					k = j;
			}
		}
		
		if(k > i)
		{
			num = arr[i];
			arr[i] = arr[k];
			arr[k] = num;
		}
	}
}

/*
 * 打印数组前面 iSt - iEnd 之间的元素
 */
CString MyFun::PrintArray(const CUIntArray &arr, int iSt /* = 0 */, int iEnd /*= -1*/,
						   const CString strSeparator /* = _T("") */,
						   const CString strFmt/* = _T("%d")*/ )
{
	CString str = _T("");
	CString ss;
	
	int iCount = arr.GetSize();
	if(0 == iCount)
		return str;

	if(-1 == iEnd || iEnd > iCount)
		iEnd = iCount;
	
	for(int i = iSt; i < iEnd; ++i)
	{
		ss.Format(strFmt, arr[i]);
		str += ss + strSeparator;
	}
	str = str.Mid( 0, str.GetLength() - strSeparator.GetLength() );
	
	return str;
}

/*
 *	在数组中查找 num
 *  找到返回索引号，否则返回 -1
 */
int MyFun::FindArrayIndex(const CUIntArray &arr, int num, int st /* = 0 */, int end /* = -1 */)
{
	int iCount = arr.GetSize();
	if(0 == iCount)
		return -1;
	
	if(-1 == end || end > iCount)
		end = iCount;
	
	for(int i = st; i < end; ++i)
	{
		if(num == arr[i])
		{
			return i;
		}
	}
	
	return -1;
}

/*
 * 在 str 中查找数字 n
 * 找到返回索引，否则返回 -1
 */
int MyFun::FindNumIndexInStr(int n, const CString &str, int end/* = -1*/, int st /*= 0*/)
{
	ASSERT(0 <= n && n <= 9);

	TCHAR ch = _T('0') + n;
	int len = str.Find(ch, st);
	
	return (-1 != len) && (len < end || -1 == end) ? len : -1;
}

/*
 * 字符串转和值(两码)数组
 */
int MyFun::Str2Sum(const CString &str, CUIntArray &arrSum, BOOL bConti /* = TRUE */, int iMax /* = 27 */)
{
	arrSum.RemoveAll();
	
	if(str.IsEmpty())
		return 0;
	
	CString st = str;
	st.TrimLeft();
		
	while( !st.IsEmpty() && !_istdigit(st.GetAt(st.GetLength() - 1)) )
		st.Delete(st.GetLength() - 1);
	
	CString sDigit = _T("0123456789");
	if(0 == st.GetLength() || -1 == st.FindOneOf(sDigit))
		return 0;
	
	int iDigit = 0, iSepar = 0;
	int i = 0;
	int n = 0;
	int num = iMax + 1;
	BOOL bContinue = FALSE;
	
	CString ss;
	while( 0 < st.GetLength() )
	{
		iDigit = st.FindOneOf(sDigit);
		
		if(-1 != iDigit)
		{
			st = st.Mid(iDigit);
			ss = st.SpanIncluding(sDigit);
			st = st.Mid(ss.GetLength());
			ss = ss.Left(2);
			
			num = _ttoi(ss);
			
			if(iMax >= num && ! MyFun::FindArray(arrSum, num))
			{
				
				n = arrSum.GetSize();

				if(!bContinue || 0 == n)
				{
					arrSum.Add(num);
				}
				else
				{
					if((UINT)num > arrSum[n - 1])
					{
						for(int i = arrSum[n - 1] + 1; i <= num; ++i)
						{
							arrSum.Add(i);
						}
					}
					else
					{
						arrSum.Add(num);
					}
					
					bContinue = FALSE;
				}
			}
			
			st.TrimLeft();
			if(bConti)
			{
				if(0 < st.GetLength() && st.GetAt(0) == _T('-'))
				{
					bContinue = TRUE;
				}
			}
		}
	}
	
	if(0 < n)
	{
		SortArray(arrSum);
	}
	
	return arrSum.GetSize();
}

/*
 * 和值(两码)数组转字符串
 */
CString MyFun::Sum2Str(const CUIntArray &arrSum, BOOL bTwo /* = FALSE  */, BOOL bConti /* = TRUE */)
{
	CString str = _T("");
	const int len = arrSum.GetSize();
	
	if(0 == len)
		return str;
	
	CString sFmt = bTwo ? _T("%02d") : _T("%d");
	
	CString ss;
	
	ss.Format(sFmt, arrSum[0]);
	str += ss;

	for(int i = 1, k = 0; i < len; ++i)
	{
		k = 0;

		if(bConti)
		{
			while(i + k < len)
			{
				if( arrSum[i + k] == arrSum[i + k -1] + 1 )
					++k;
				else
					break;
			}
		}
		else
			k = 0;
		
		if(0 == k)
		{
			sFmt = bTwo ? _T(",%02d") : _T(",%d");
			ss.Format(sFmt, arrSum[i]);
			str += ss;
		}
		else
		{
			sFmt = bTwo ? _T(",%02d") : _T("-%d");
			ss.Format(sFmt, arrSum[i + k - 1]);
			str += ss;
			i += k - 1;
			k = 0;
		}
	}
	
	return str;
}

/*
 * 字符串转大底号
 */
int MyFun::Str2Num(const CString &ss, CUIntArray &arr)
{
	arr.RemoveAll();
	
	CString str = ss;
	int len = str.GetLength();

	if(0 == len)
		return 0;

	int B[3], j = 0, num;
		
	for(int i = 0; i < len && arr.GetSize() < 1000; ++i)
	{
		if(_istdigit(str.GetAt(i)))
		{
			B[j++] = str.GetAt(i) - _T('0');
		}
		
		if(3 == j)
		{
			j = 0;
			num = B[0] * 100 + B[1] * 10 + B[2];

			if( !MyFun::FindArray(arr, num) )
				arr.Add(num);
		}
	}
	
	if(0 != j)
	{
		num = B[0];
		for(int i = 1; i < j; ++i)
		{
			num = num * 10 + B[i];
		}

		if( !MyFun::FindArray(arr, num) )
		{
			arr.Add(num);
		}
	}

	return arr.GetSize();
}

/*
 * 大底号转字符串
 */
CString& MyFun::Num2Str(const CUIntArray &arr, CString &str, const CString &sFmt /* = _T("%03d ") */)
{
	str.Empty();

	CString ss = _T("");
	int cnt = arr.GetSize();

	for(int i = 0; i < cnt; ++i)
	{
		ss.Format(sFmt, arr[i]);
		str += ss;
	}

	return str;
}

/*
 * 排除重复项
 */
int MyFun::ExcludeSame(CUIntArray &arr, BOOL bOrder /*= TRUE*/)
{
	int i = arr.GetSize() - 1;

	if(i < 1)
		return i;

	int n;
	while(i > 0)
	{
		if( FindArray(arr, arr[i], 0, i) )
			arr.RemoveAt(i);
		else if( !bOrder )
		{
			n = (arr[i] % 10) * 10 + arr[i] / 10 % 10;

			if( FindArray(arr, n, 0, i) )
				arr.RemoveAt(i);
		}
		
		--i;
	}

	return arr.GetSize();
}

int MyFun::ExcludeSame(CString &str)
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

int MyFun::ExcludeNull(CStringArray &arr)
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

////////////////////////////////////////////////////////////////////
