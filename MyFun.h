#ifndef __MY_FUN_H__
#define __MY_FUN_H__

#include "winbase.h"
#include "string"
using std::string;

namespace MyFun
{
	// ��������
	VOID SortArray(CUIntArray &arr, BOOL bAsc = TRUE);
	// ��ӡ����ǰ�� iSt - iEnd ֮���Ԫ��
	CString PrintArray(const CUIntArray &arr, int iSt = 0, int iEnd = -1, const CString strSeparator = _T(""), const CString strFmt = _T("%d"));
	// �ų������ظ���
	int ExcludeSame(CUIntArray &arr, BOOL bOrder = TRUE);
	// �ų��ַ����ظ���
	int ExcludeSame(CString &str);
	// �ų��ַ��������еĿմ�
	int ExcludeNull(CStringArray &arr);
	
	// �ַ���ת��ֵ(����)����
	int Str2Sum(const CString &str, CUIntArray &arrSum, BOOL bConti = TRUE, int iMax = 27);
	// ��ֵ(����)ת�ַ���
	CString Sum2Str(const CUIntArray &arrSum, BOOL bTwo = FALSE, BOOL bConti = TRUE);

	// �ַ���ת��׺�
	int Str2Num(const CString &ss, CUIntArray &arr);
	// ��׺�ת�ַ���
	CString& Num2Str(const CUIntArray &arr, CString &str, const CString &sFmt = _T("%03d ") );

	// �������飬���� num �������Ҳ������� -1
	int FindArrayIndex(const CUIntArray &arr, int num, int st = 0, int end = -1);
	inline BOOL FindArray(const CUIntArray &arr, int num, int st = 0, int ed = -1)
	{
		return -1 != FindArrayIndex(arr, num, st, ed);
	}

	// �����ַ���st-end��Χ���ҵ� n ���� �����ţ����򷵻� -1
	int FindNumIndexInStr(int n, const CString &str, int end = -1, int st = 0);
	inline BOOL FindNumInStr(int n, const CString &str, int end = -1, int st = 0)
	{
		return -1 != FindNumIndexInStr(n, str, end, st);
	}

	// ����
	inline BOOL IsLeapYear(UINT nYear) {
		ASSERT(nYear > 0);
		return !(nYear % 4) && (nYear % 100) || !(nYear % 400);
	}
};

#endif // __MY_FUN_H__