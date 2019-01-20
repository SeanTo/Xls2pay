// Xls2pay.h : main header file for the XLS2PAY application
//

#if !defined(AFX_XLS2PAY_H__5BEA8C6E_2D26_445C_884E_C2F457D47009__INCLUDED_)
#define AFX_XLS2PAY_H__5BEA8C6E_2D26_445C_884E_C2F457D47009__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXls2payApp:
// See Xls2pay.cpp for the implementation of this class
//

class CXls2payApp : public CWinApp
{
public:
	CXls2payApp();
	int m_iCol[13];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXls2payApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXls2payApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XLS2PAY_H__5BEA8C6E_2D26_445C_884E_C2F457D47009__INCLUDED_)
