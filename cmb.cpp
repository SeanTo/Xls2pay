#include "StdAfx.h"
#include "cmb.h"

////////////////////////////////////////////////////////////////////////////////
#ifdef _USE_CMB_

const CString CMB::m_CITY_00[] = {
	_T("----"),
	_T("����"), _T("0010"),
	_T("�Ϻ�"), _T("0021"),
	_T("���"), _T("0022"),
	_T("����"), _T("0023"),
// 	_T("���"), _T("0852"),
};

const CString CMB::m_CITY_01[] = {
	_T("����"),
	_T("�Ϸ�"), _T("0551")
};

const CString CMB::m_CITY_02[] = {
	_T("����"),
	_T("����"), _T("0591"),
	_T("Ȫ��"), _T("0595"),
	_T("����"), _T("0592")
};

const CString CMB::m_CITY_03[] = {
	_T("����"),
	_T("����"), _T("0931")
};

const CString CMB::m_CITY_04[] = {
	_T("�㶫"),
	_T("��ݸ"), _T("0769"),
	_T("��ɽ"), _T("0757"),
	_T("����"), _T("0020"),
	_T("����"), _T("0755")
};

// const CString CMB::m_CITY_05[] = {
// 	_T("����"),
// };
// 
// const CString CMB::m_CITY_06[] = {
// 	_T("����"),
// };
// 
// const CString CMB::m_CITY_07[] = {
// 	_T("����"),
// };
// 
// const CString CMB::m_CITY_08[] = {
// 	_T("�ӱ�"),
// };

const CString CMB::m_CITY_09[] = {
	_T("����"),
	_T("֣��"), _T("0371")
};

const CString CMB::m_CITY_10[] = {
    _T("������"),
	_T("������"), _T("0451")
};

const CString CMB::m_CITY_11[] = {
    _T("����"),
	_T("��ʯ"), _T("0714"),
	_T("�人"), _T("0027"),
	_T("�˲�"), _T("0717")
};

const CString CMB::m_CITY_12[] = {
    _T("����"),
	_T("��ɳ"), _T("0731"),
	_T("��̶"), _T("0732")
};

// const CString CMB::m_CITY_13[] = {
//	_T("����"),
// };

const CString CMB::m_CITY_14[] = {
    _T("����"),
    _T("����"), _T("0519"),
	_T("����"), _T("0514"),
	_T("�Ͼ�"), _T("0024"),
	_T("��ͨ"), _T("0513"),
	_T("����"), _T("0512"),
	_T("����"), _T("0510"),
	_T("����"), _T("0514"),
	_T("����"), _T("0510")
};

const CString CMB::m_CITY_15[] = {
    _T("����"),
	_T("�ϲ�"), _T("0791")
};

const CString CMB::m_CITY_16[] = {
    _T("����"),
	_T("����"), _T("0411"),
	_T("����"), _T("0415"),
	_T("��˳"), _T("0413"),
	_T("�̽�"), _T("0427"),
	_T("����"), _T("0024")
};

const CString CMB::m_CITY_17[] = {
    _T("���ɹ�"),
	_T("���ͺ���"), _T("0471")
};

// const CString CMB::m_CITY_18[] = {
// 	_T("����"),
// };
// 
// const CString CMB::m_CITY_19[] = {
// 	_T("�ຣ"),
// };

const CString CMB::m_CITY_20[] = {
    _T("ɽ��"),
	_T("����"), _T("0531"),
	_T("�ൺ"), _T("0532"),
	_T("����"), _T("0536"),
	_T("��̨"), _T("0535")
};

const CString CMB::m_CITY_21[] = {
    _T("ɽ��"),
	_T("̫ԭ"), _T("0351")
};

const CString CMB::m_CITY_22[] = {
    _T("����"),
	_T("����"), _T("0029")
};

const CString CMB::m_CITY_23[] = {
    _T("�Ĵ�"),
	_T("�ɶ�"), _T("0028")
};

// const CString CMB::m_CITY_24[] = {
// 	_T("����"),
// };

const CString CMB::m_CITY_25[] = {
    _T("�½�"),
	_T("��³ľ��"), _T("0991")
};

const CString CMB::m_CITY_26[] = {
    _T("����"),
	_T("����"), _T("0871")
};

const CString CMB::m_CITY_27[] = {
    _T("�㽭"),
	_T("����"), _T("0571"),
	_T("����"), _T("0573"),
	_T("��"), _T("0579"),
	_T("����"), _T("0574"),
	_T("��"), _T("0577"),
	_T("����"), _T("0575"),
	_T("̨��"), _T("0576"),
	_T("����"), _T("0577")
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
	_T("ת��������"),
	_T("ת���˺�"),
	_T("ת������"),
	_T("���˽��"),
	_T("�տ�������"),
	_T("�տ�ʡ��"),
	_T("�տ����"),
	_T("�л���"),
	_T("�տ����"),
	_T("�տ������"),
	_T("�տ��˺�"),
	_T("��ע"),
	_T("����")
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
	_T("����"), _T("0010"),
	_T("�Ϻ�"), _T("0021"),
	_T("���"), _T("0022"),
	_T("����"), _T("0023"),
	_T("���"), _T("0852"),
	_T("��ɳ"), _T("0731"),
	_T("����"), _T("0519"),
	_T("�ɶ�"), _T("0028"),
	_T("����"), _T("0411"),
	_T("����"), _T("0415"),
	_T("��ݸ"), _T("0769"),
	_T("��ɽ"), _T("0757"),
	_T("����"), _T("0591"),
	_T("��˳"), _T("0413"),
	_T("����"), _T("0020"),
	_T("������"), _T("0451"),
	_T("����"), _T("0571"),
	_T("�Ϸ�"), _T("0551"),
	_T("���ͺ���"), _T("0471"),
	_T("��ʯ"), _T("0714"),
	_T("����"), _T("0531"),
	_T("����"), _T("0573"),
	_T("��"), _T("0579"),
	_T("����"), _T("0514"),
	_T("����"), _T("0871"),
	_T("����"), _T("0931"),
	_T("�ϲ�"), _T("0791"),
	_T("�Ͼ�"), _T("0024"),
	_T("��ͨ"), _T("0513"),
	_T("����"), _T("0574"),
	_T("�̽�"), _T("0427"),
	_T("�ൺ"), _T("0532"),
	_T("Ȫ��"), _T("0595"),
	_T("��"), _T("0577"),
	_T("����"), _T("0575"),
	_T("����"), _T("0755"),
	_T("����"), _T("0024"),
	_T("����"), _T("0512"),
	_T("̨��"), _T("0576"),
	_T("̫ԭ"), _T("0351"),
	_T("����"), _T("0536"),
	_T("����"), _T("0577"),
	_T("��³ľ��"), _T("0991"),
	_T("����"), _T("0510"),
	_T("�人"), _T("0027"),
	_T("����"), _T("0029"),
	_T("����"), _T("0592"),
	_T("��̶"), _T("0732"),
	_T("��̨"), _T("0535"),
	_T("����"), _T("0514"),
	_T("�˲�"), _T("0717"),
	_T("����"), _T("0510"),
	_T("֣��"), _T("0371")
};
*/
