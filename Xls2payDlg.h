// Xls2payDlg.h : header file
//

#if !defined(AFX_XLS2PAYDLG_H__B7F154A7_5553_4159_A860_B59C31038515__INCLUDED_)
#define AFX_XLS2PAYDLG_H__B7F154A7_5553_4159_A860_B59C31038515__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Xls2pay.h"

#include "wnd.h"
#include "ListCtrlEx.h"
#include "ExcelVC6.h"
using namespace YExcel;

/////////////////////////////////////////////////////////////////////////////
// CXls2payDlg dialog

class CXls2payDlg : public CDialog
{
	// Construction
public:
	CXls2payDlg(CWnd* pParent = NULL);	// standard constructor
	CComboBox *pCmb;
	
	// Dialog Data
	//{{AFX_DATA(CXls2payDlg)
	enum { IDD = IDD_XLS2PAY_DIALOG };
	CListCtrlEx	m_List;
	CComboBox	m_cmbProv0;
	CComboBox	m_cmbCode0;
	CComboBox	m_cmbCity0;
	CComboBox	m_cmbProv;
	CComboBox	m_cmbCode;
	CComboBox	m_cmbCity;
	CComboBox	m_cmbType;
	CComboBox	m_cmbAcc;
	CComboBox	m_cmbSheet;
	CString	m_strPay;
	CString	m_strXls;
	CString	m_strTip;
	BOOL	m_bRename;
	BOOL	m_bSelType;
	BOOL	m_bAutoFix;
	BOOL	m_bCheck;
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXls2payDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	HICON m_hIcon;
	
	// Generated message map functions
	//{{AFX_MSG(CXls2payDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnPay();
	afx_msg void OnBtnXls();
	virtual void OnOK();
	afx_msg void OnAbout();
	afx_msg void OnBtnSave();
	afx_msg void OnSelchangeCmbSheet();
	virtual void OnCancel();
	afx_msg void OnChkSelType();
	afx_msg void OnBtnConfig();
	afx_msg void OnSelchangeCmbCity();
	afx_msg void OnSelchangeCmbCode();
	afx_msg void OnSelendcancelCmbAccount();
	afx_msg void OnSelchangeCmbType();
	afx_msg void OnChkCheck();
	afx_msg void OnSelchangeCmbProv();
	afx_msg void OnSelchangeCmbCity0();
	afx_msg void OnSelchangeCmbCode0();
	afx_msg void OnSelchangeCmbProv0();
	//}}AFX_MSG
	afx_msg void OnDropFiles(HDROP hDropInfo);
	DECLARE_MESSAGE_MAP()
		
private:
	void InitListCtrl();
	void ShowConfig();
	void SelectCity0(int x, int y);
	BOOL ReadInfo();
	void	SelectCity(int x, int y);
	void	GetPayName();
	BOOL	IsExcelFile(const CString strXls);
	void	CleanTempFile();
	BOOL	ReadAccount();
	BOOL	Convert(BOOL bSave = FALSE);

	CXls2payApp *pApp;
	CExcel	m_Excel;
	CExcelSheet *m_pSheet;

	CString	m_strTmpFile;
	CString	m_strCode;
	CString	m_strAcc;
	CString m_strAccount;

	BOOL	m_bIsLarge;
	CStringArray m_arrAcc;
	
#ifdef __EXPERT_VER__
	CStringArray m_arrPreAcc;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XLS2PAYDLG_H__B7F154A7_5553_4159_A860_B59C31038515__INCLUDED_)
