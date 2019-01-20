#ifndef __MY_FUN_H__
#define __MY_FUN_H__

#include "winbase.h"
#include "string"
using std::string;

namespace MyFun
{
	// 数组排序
	VOID SortArray(CUIntArray &arr, BOOL bAsc = TRUE);
	// 打印数组前面 iSt - iEnd 之间的元素
	CString PrintArray(const CUIntArray &arr, int iSt = 0, int iEnd = -1, const CString strSeparator = _T(""), const CString strFmt = _T("%d"));
	// 排除数组重复项
	int ExcludeSame(CUIntArray &arr, BOOL bOrder = TRUE);
	// 排除字符串重复项
	int ExcludeSame(CString &str);
	// 排除字符串数组中的空串
	int ExcludeNull(CStringArray &arr);
	
	// 字符串转和值(两码)数组
	int Str2Sum(const CString &str, CUIntArray &arrSum, BOOL bConti = TRUE, int iMax = 27);
	// 和值(两码)转字符串
	CString Sum2Str(const CUIntArray &arrSum, BOOL bTwo = FALSE, BOOL bConti = TRUE);

	// 字符串转大底号
	int Str2Num(const CString &ss, CUIntArray &arr);
	// 大底号转字符串
	CString& Num2Str(const CUIntArray &arr, CString &str, const CString &sFmt = _T("%03d ") );

	// 查找数组，返回 num 索引，找不到返回 -1
	int FindArrayIndex(const CUIntArray &arr, int num, int st = 0, int end = -1);
	inline BOOL FindArray(const CUIntArray &arr, int num, int st = 0, int ed = -1)
	{
		return -1 != FindArrayIndex(arr, num, st, ed);
	}

	// 查找字符串st-end范围，找到 n 返回 索引号，否则返回 -1
	int FindNumIndexInStr(int n, const CString &str, int end = -1, int st = 0);
	inline BOOL FindNumInStr(int n, const CString &str, int end = -1, int st = 0)
	{
		return -1 != FindNumIndexInStr(n, str, end, st);
	}

	// 闰年
	inline BOOL IsLeapYear(UINT nYear) {
		ASSERT(nYear > 0);
		return !(nYear % 4) && (nYear % 100) || !(nYear % 400);
	}
};

#endif // __MY_FUN_H__