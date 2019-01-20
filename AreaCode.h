#ifndef _AREA_CODE_H_
#define _AREA_CODE_H_

#define _USE_AAC_

////////////////////////////////////////////////////////////////////////////////
#ifdef _USE_AAC_

// 全区城市区号
class AAC
{
public:
	enum { PROV_NUM = 28 };

	// 各省城市数
	static const int GetNum(int x) { ASSERT(x>=0 && x<PROV_NUM); return m_NUM[x]; }

	// 省名
	static const CString& GetProvince(int x) { ASSERT(x>=0 && x<PROV_NUM); return GetPtr(x)[0]; }
	// 城市名
	static const CString& GetCity(int x, int y) { ASSERT(x>=0 && x<PROV_NUM); return GetPtr(x)[(y<<1)+1]; }
	static const CString& GetCity(int ind) { return GetCity(ind/100, ind%100); }
	// 区号
	static const CString& GetCode(int x, int y) { ASSERT(x>=0 && x<PROV_NUM); return GetPtr(x)[(y<<1)+2]; }
	static const CString& GetCode(int ind) { return GetCode(ind/100, ind%100); }
	
	// 判断给定省、城市、区号串是否支持
	static BOOL IsProvince(const CString &str) { return -1 != FindProvince(str); }
	static BOOL IsCity(const CString &str) { return -1 != FindCity(str); }
	static BOOL IsCode(const CString &str) { return -1 != FindCode(str); }

	// 查找给定省、城市、区号串索引，未找到返回 -1
	static const int FindProvince(const CString &str);
	static const int FindCity(const CString &str);
	static const int FindCode(const CString &str);

private:
	
	// 各省数组地址
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
};

#endif // _USE_AAC_
////////////////////////////////////////////////////////////////////////////////

#endif	// _AREA_CODE_H_
