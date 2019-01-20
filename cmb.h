#ifndef _CMB_H_
#define _CMB_H_

#include "wnd.h"

#define _USE_CMB_

////////////////////////////////////////////////////////////////////////////////
#ifdef _USE_CMB_

// ����֧�ֳ�������
class CMB
{
public:
	enum { PROV_NUM = 28, TYPE_NUM = 6, SECT_NUM = 13 };

public:
	// �ֶ���
	static const CString& GetSect(int x) { ASSERT(x>=0 && x<=SECT_NUM); return m_SECT[x]; }

	// ��ʡ������
	static const int GetNum(int x) { ASSERT(x>=0 && x<=PROV_NUM); return m_NUM[x]; }
	
	// ʡ��
	static const CString GetProvince(int x)
	{
		ASSERT(x>=0 && x<PROV_NUM);
		return(0 == GetNum(x)) ? m_strNul : GetPtr(x)[0];
	}

	// ������
	static const CString& GetCity(int x, int y)
	{
		ASSERT(x>=0 && x<PROV_NUM);
		return (0 == GetNum(x)) ? m_strNul : GetPtr(x)[(y<<1)+1];
	}
	static const CString& GetCity(int ind) { return GetCity(ind/100, ind%100); }

	// ����
	static const CString& GetCode(int x, int y)
	{
		ASSERT(x>=0 && x<PROV_NUM);
		return (0 == GetNum(x)) ? m_strNul : GetPtr(x)[(y<<1)+2];
	}
	static const CString& GetCode(int ind) { return GetCode(ind/100, ind%100); }
	
	// �жϸ���ʡ�����С����Ŵ��Ƿ�֧��
	static BOOL IsCity(const CString &str) { return -1 != FindCity(str); }
	static BOOL IsCode(const CString &str) { return -1 != FindCode(str); }
	
	// ���Ҹ���ʡ�����С����Ŵ�������δ�ҵ����� -1
	static const int FindProvince(const CString &str);
	static const int FindCity(const CString &str);
	static const int FindCode(const CString &str);

	// �˺�
	static BOOL IsAccount(const CString &str, int en = -1, const CString &strCode = _T(""));
	static BOOL IsAccountOther(const CString &str);
	
private:
	// ��ʡ�����ַ
	static const CString* GetPtr(int x) { return m_PTR[x]; }

private:
	static const CString m_CITY_00[];
	static const CString m_CITY_01[];
	static const CString m_CITY_02[];
	static const CString m_CITY_03[];
	static const CString m_CITY_04[];
	static const CString m_CITY_05[];
	static const CString m_CITY_06[];
	static const CString m_CITY_07[];
	static const CString m_CITY_08[];
	static const CString m_CITY_09[];
	static const CString m_CITY_10[];
	static const CString m_CITY_11[];
	static const CString m_CITY_12[];
	static const CString m_CITY_13[];
	static const CString m_CITY_14[];
	static const CString m_CITY_15[];
	static const CString m_CITY_16[];
	static const CString m_CITY_17[];
	static const CString m_CITY_18[];
	static const CString m_CITY_19[];
	static const CString m_CITY_20[];
	static const CString m_CITY_21[];
	static const CString m_CITY_22[];
	static const CString m_CITY_23[];
	static const CString m_CITY_24[];
	static const CString m_CITY_25[];
	static const CString m_CITY_26[];
	static const CString m_CITY_27[];
	
	static const CString* m_PTR[];
	static const int m_NUM[];

	static const CString m_SECT[];
	
public:
	static const CString GetPayName(const CString strAcc) { return _T("BATCH-") + strAcc + _T("-") + MyDT::Today(_T("")) + _T(".PAY"); }

	static const CString GetType(int x) { ASSERT(x>=0 && x<=TYPE_NUM); return m_TYPE[x]; }
	static BOOL IsType(const CString &str) { return -1 != FindType(str); }
	static int FindType(const CString &str) { return EMFC::FindArray(str, m_TYPE, TYPE_NUM); }

public:
	// ����
	static BOOL IsCmbChina(int x) { return 0==x || 1==x || 3==x || 4==x; }
	static BOOL IsCmbChina(const CString &str) { return IsCmbChina(FindType(str)); }
	// ͬ������
	static BOOL IsCmbSame(int x) { return 0==x || 1==x; }
	static BOOL IsCmbSame(const CString &str) { return IsCmbSame(FindType(str)); }
	// ���и����˻�
	static BOOL IsCmbPer(int x) { return 0 == x; }
	static BOOL IsCmbPer(const CString &str) { return IsCmbPer(FindType(str)); }
	// ͬ��ת��
	static BOOL IsSameCity(int x) { return x>=0 && x<=2; }
	static BOOL IsSameCity(const CString &str) { return IsSameCity(FindType(str)); }

private:
	static const CString m_TYPE[];
	static const CString m_strNul;
};

#endif // _USE_CMB_
////////////////////////////////////////////////////////////////////////////////

#endif	// _CMB_H_
