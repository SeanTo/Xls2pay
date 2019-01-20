#include "StdAfx.h"
#include "cmb.h"

////////////////////////////////////////////////////////////////////////////////
#ifdef _USE_CMB_

const CString CMB::m_CITY_00[] = {
	_T("----"),
	_T("北京"), _T("0010"),
	_T("上海"), _T("0021"),
	_T("天津"), _T("0022"),
	_T("重庆"), _T("0023"),
// 	_T("香港"), _T("0852"),
};

const CString CMB::m_CITY_01[] = {
	_T("安徽"),
	_T("合肥"), _T("0551")
};

const CString CMB::m_CITY_02[] = {
	_T("福建"),
	_T("福州"), _T("0591"),
	_T("泉州"), _T("0595"),
	_T("厦门"), _T("0592")
};

const CString CMB::m_CITY_03[] = {
	_T("甘肃"),
	_T("兰州"), _T("0931")
};

const CString CMB::m_CITY_04[] = {
	_T("广东"),
	_T("东莞"), _T("0769"),
	_T("佛山"), _T("0757"),
	_T("广州"), _T("0020"),
	_T("深圳"), _T("0755")
};

// const CString CMB::m_CITY_05[] = {
// 	_T("广西"),
// };
// 
// const CString CMB::m_CITY_06[] = {
// 	_T("贵州"),
// };
// 
// const CString CMB::m_CITY_07[] = {
// 	_T("海南"),
// };
// 
// const CString CMB::m_CITY_08[] = {
// 	_T("河北"),
// };

const CString CMB::m_CITY_09[] = {
	_T("河南"),
	_T("郑州"), _T("0371")
};

const CString CMB::m_CITY_10[] = {
    _T("黑龙江"),
	_T("哈尔滨"), _T("0451")
};

const CString CMB::m_CITY_11[] = {
    _T("湖北"),
	_T("黄石"), _T("0714"),
	_T("武汉"), _T("0027"),
	_T("宜昌"), _T("0717")
};

const CString CMB::m_CITY_12[] = {
    _T("湖南"),
	_T("长沙"), _T("0731"),
	_T("湘潭"), _T("0732")
};

// const CString CMB::m_CITY_13[] = {
//	_T("吉林"),
// };

const CString CMB::m_CITY_14[] = {
    _T("江苏"),
    _T("常州"), _T("0519"),
	_T("江都"), _T("0514"),
	_T("南京"), _T("0024"),
	_T("南通"), _T("0513"),
	_T("苏州"), _T("0512"),
	_T("无锡"), _T("0510"),
	_T("扬州"), _T("0514"),
	_T("宜兴"), _T("0510")
};

const CString CMB::m_CITY_15[] = {
    _T("江西"),
	_T("南昌"), _T("0791")
};

const CString CMB::m_CITY_16[] = {
    _T("辽宁"),
	_T("大连"), _T("0411"),
	_T("丹东"), _T("0415"),
	_T("抚顺"), _T("0413"),
	_T("盘锦"), _T("0427"),
	_T("沈阳"), _T("0024")
};

const CString CMB::m_CITY_17[] = {
    _T("内蒙古"),
	_T("呼和浩特"), _T("0471")
};

// const CString CMB::m_CITY_18[] = {
// 	_T("宁夏"),
// };
// 
// const CString CMB::m_CITY_19[] = {
// 	_T("青海"),
// };

const CString CMB::m_CITY_20[] = {
    _T("山东"),
	_T("济南"), _T("0531"),
	_T("青岛"), _T("0532"),
	_T("淮坊"), _T("0536"),
	_T("烟台"), _T("0535")
};

const CString CMB::m_CITY_21[] = {
    _T("山西"),
	_T("太原"), _T("0351")
};

const CString CMB::m_CITY_22[] = {
    _T("陕西"),
	_T("西安"), _T("0029")
};

const CString CMB::m_CITY_23[] = {
    _T("四川"),
	_T("成都"), _T("0028")
};

// const CString CMB::m_CITY_24[] = {
// 	_T("西藏"),
// };

const CString CMB::m_CITY_25[] = {
    _T("新疆"),
	_T("乌鲁木齐"), _T("0991")
};

const CString CMB::m_CITY_26[] = {
    _T("云南"),
	_T("昆明"), _T("0871")
};

const CString CMB::m_CITY_27[] = {
    _T("浙江"),
	_T("杭州"), _T("0571"),
	_T("嘉兴"), _T("0573"),
	_T("金华"), _T("0579"),
	_T("宁波"), _T("0574"),
	_T("瑞安"), _T("0577"),
	_T("绍兴"), _T("0575"),
	_T("台州"), _T("0576"),
	_T("温州"), _T("0577")
};

const CString* CMB::m_PTR[] = {
	m_CITY_00,
	m_CITY_01,
	m_CITY_02,
	m_CITY_03,
	m_CITY_04,
	NULL,
	NULL,
	NULL,
	NULL,
	m_CITY_09,
	m_CITY_10,
	m_CITY_11,
	m_CITY_12,
	NULL,
	m_CITY_14,
	m_CITY_15,
	m_CITY_16,
	m_CITY_17,
	NULL,
	NULL,
	m_CITY_20,
	m_CITY_21,
	m_CITY_22,
	m_CITY_23,
	NULL,
	m_CITY_25,
	m_CITY_26,
	m_CITY_27
};

const int CMB::m_NUM[] = {
	(sizeof(m_CITY_00) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_01) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_02) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_03) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_04) / sizeof(CString) - 1) >> 1,
	0,
	0,
	0,
	0,
	(sizeof(m_CITY_09) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_10) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_11) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_12) / sizeof(CString) - 1) >> 1,
	0,
	(sizeof(m_CITY_14) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_15) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_16) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_17) / sizeof(CString) - 1) >> 1,
	0,
	0,
	(sizeof(m_CITY_20) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_21) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_22) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_23) / sizeof(CString) - 1) >> 1,
	0,
	(sizeof(m_CITY_25) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_26) / sizeof(CString) - 1) >> 1,
	(sizeof(m_CITY_27) / sizeof(CString) - 1) >> 1
};

const CString CMB::m_SECT[] = {
	_T("转出地区号"),
	_T("转出账号"),
	_T("转账类型"),
	_T("收账金额"),
	_T("收款人姓名"),
	_T("收款省名"),
	_T("收款城市"),
	_T("市或县"),
	_T("收款开户行"),
	_T("收款地区号"),
	_T("收款账号"),
	_T("备注"),
	_T("币种")
};

////////////////////////////////////////////////////////////////////////////////

const CString CMB::m_TYPE[] = {
	_T("TRF1"), _T("TRF2"), _T("TRF3"), _T("TRT1"), _T("TRT2"), _T("TRT3")
};

const CString CMB::m_strNul = _T("");

////////////////////////////////////////////////////////////////////////////////

const int CMB::FindProvince(const CString &str)
{
	for(int i = 0; i < PROV_NUM; ++i)
	{
		if(0 == GetNum(i))
			continue;
		if( -1 != str.Find( GetProvince(i) ) )
			return i;
	}
	return -1;
}

const int CMB::FindCity(const CString &str)
{
	for(int i = 0; i < PROV_NUM; ++i)
	{
		if( 0 == GetNum(i) )
			continue;

		for(int j = 0; j < GetNum(i); ++j)
		{
			if( -1 != str.Find( GetCity(i, j) ) )
				return i * 100 + j;
		}
	}
	return -1;	
}

const int CMB::FindCode(const CString &str)
{
	for(int i = 0; i < PROV_NUM; ++i)
	{
		if( 0 == GetNum(i) )
			continue;

		for(int j = 0; j < GetNum(i); ++j)
		{
			if( str == GetCode(i, j) )
				return i * 100 + j;
		}
	}
	return -1;
}

BOOL CMB::IsAccount(const CString &str, int en/* = -1*/, const CString &strCode/* = _T("")*/)
{
	const int iLen = str.GetLength();
	if(    en < 0 && (iLen != 8 && iLen != 12 && iLen != 16)
		|| en > 0 && (iLen != en && iLen != 16) )
		return FALSE;

	if( !EMFC::IsNumber(str) )
		return FALSE;

	if( 12 == iLen )
	{
		if( strCode.IsEmpty() && !IsCode(str.Left(4))
			|| !strCode.IsEmpty() && strCode != str.Left(4) )
			return FALSE;
	}

	return TRUE;
}

BOOL CMB::IsAccountOther(const CString &str)
{
	const int iLen = str.GetLength();
	if( iLen != 15 && iLen != 16 && iLen != 19)
		return FALSE;

	return TRUE;
}

#endif // _USE_CMB_
////////////////////////////////////////////////////////////////////////////////

/*
const CString STR_CMB_CITY[][2] = {
	_T("北京"), _T("0010"),
	_T("上海"), _T("0021"),
	_T("天津"), _T("0022"),
	_T("重庆"), _T("0023"),
	_T("香港"), _T("0852"),
	_T("长沙"), _T("0731"),
	_T("常州"), _T("0519"),
	_T("成都"), _T("0028"),
	_T("大连"), _T("0411"),
	_T("丹东"), _T("0415"),
	_T("东莞"), _T("0769"),
	_T("佛山"), _T("0757"),
	_T("福州"), _T("0591"),
	_T("抚顺"), _T("0413"),
	_T("广州"), _T("0020"),
	_T("哈尔滨"), _T("0451"),
	_T("杭州"), _T("0571"),
	_T("合肥"), _T("0551"),
	_T("呼和浩特"), _T("0471"),
	_T("黄石"), _T("0714"),
	_T("济南"), _T("0531"),
	_T("嘉兴"), _T("0573"),
	_T("金华"), _T("0579"),
	_T("江都"), _T("0514"),
	_T("昆明"), _T("0871"),
	_T("兰州"), _T("0931"),
	_T("南昌"), _T("0791"),
	_T("南京"), _T("0024"),
	_T("南通"), _T("0513"),
	_T("宁波"), _T("0574"),
	_T("盘锦"), _T("0427"),
	_T("青岛"), _T("0532"),
	_T("泉州"), _T("0595"),
	_T("瑞安"), _T("0577"),
	_T("绍兴"), _T("0575"),
	_T("深圳"), _T("0755"),
	_T("沈阳"), _T("0024"),
	_T("苏州"), _T("0512"),
	_T("台州"), _T("0576"),
	_T("太原"), _T("0351"),
	_T("淮坊"), _T("0536"),
	_T("温州"), _T("0577"),
	_T("乌鲁木齐"), _T("0991"),
	_T("无锡"), _T("0510"),
	_T("武汉"), _T("0027"),
	_T("西安"), _T("0029"),
	_T("厦门"), _T("0592"),
	_T("湘潭"), _T("0732"),
	_T("烟台"), _T("0535"),
	_T("扬州"), _T("0514"),
	_T("宜昌"), _T("0717"),
	_T("宜兴"), _T("0510"),
	_T("郑州"), _T("0371")
};
*/
