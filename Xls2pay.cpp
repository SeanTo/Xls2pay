// Xls2pay.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Xls2pay.h"
#include "Xls2payDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXls2payApp

BEGIN_MESSAGE_MAP(CXls2payApp, CWinApp)
	//{{AFX_MSG_MAP(CXls2payApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXls2payApp construction

CXls2payApp::CXls2payApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	for(int i = 0; i < 13; ++i)
		m_iCol[i] = i;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXls2payApp object

CXls2payApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXls2payApp initialization

BOOL CXls2payApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CXls2payDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
