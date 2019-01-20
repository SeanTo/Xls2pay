/*
 *  initialize sample
 *  Add a ListCtrl in .rc file and add a CListCtrl variable for ListCtrl
 *	include header ListCtrlEx.h
 *  modify type of variable to CListCtrlEx
 *  then ...
 */
/*
void InitListCtrl()
{
	m_List.SetExtendedStyle(m_List.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES / *| LVS_EX_CHECKBOXES* / );
	
	// 列表头
	m_List.InsertColumn(0, "项目", LVCFMT_LEFT, 80);
	m_List.InsertColumn(1, "值", LVCFMT_LEFT, 48);
	
	m_List.SetReadOnlyColumn(0);	// readonly column 0
	m_List.SetValidCharsColumn(_T("0123456789"), 2, 1);
	
	int iCount = 0;
	for(int i = 0; i < CMB::SECT_NUM; ++i)
	{
		m_List.InsertItem(iCount, _T("abc") );
		m_List.SetItemText(iCount, 1, _T("123");
		++iCount;
	}
}
*/

#if !defined(AFX_EDITLISTCTRL_H__B26FE6EC_7377_4DA6_BEC1_E3C656DACFB8__INCLUDED_)
#define AFX_EDITLISTCTRL_H__B26FE6EC_7377_4DA6_BEC1_E3C656DACFB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditListCtrl.h : header file
//

#define _USE_COMBOBOX_

#define WM_USER_EDIT_END WM_USER+1001
#define WM_USER_COMB_END WM_USER+1002
#define MAX_RESTRICT_COLUMNS 100

#define CTRL_C	0x3
#define CTRL_V	0x16
#define CTRL_X	0x18

/////////////////////////////////////////////////////////////////////////////
#ifdef _USE_COMBOBOX_

class CListCtrlCombo : public CComboBox
{
// Construction
public:
	friend class CListCtrlEx;

// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEdit)
	public:
	//}}AFX_VIRTUAL
// 	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	// Implementation
public:
	virtual ~CListCtrlCombo();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg void OnSelchange();
		
private:
	CListCtrlCombo();

private:
	BOOL	m_bExchange;
};

#endif // _USE_COMBOBOX_
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////

class CListCtrlEdit : public CEdit
{
// Construction
public:
	friend class CListCtrlEx;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	DWORD	m_dwData;
	BOOL	m_bExchange;
	CString	m_strValidChars;
	UINT	m_nLen;
	CString	m_str;

private:
	CListCtrlEdit();
	void  SetCtrlData(DWORD dwData);
	DWORD GetCtrlData();
	void  LimitChars(const CString str, const UINT nLen = 0) { m_strValidChars = str; m_nLen = nLen; }
};


/////////////////////////////////////////////////////////////////////////////


class CListCtrlEx : public CListCtrl
{
// Construction
public:
	CListCtrlEx();

// Attributes
public:
	void SetValidCharsColumn(const CString str, UINT nLen = 0, int iCol = -1);
	void SetReadOnlyColumn(int iCol,  BOOL bReadonly = TRUE);
	
// Operations
public:
	BOOL HitTestEx(CPoint &pt, int &iRow, int &iCol, BOOL bScreen = FALSE);
	int  GetCurSel() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEx)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	//}}AFX_MSG
	afx_msg void OnEditEnd(WPARAM, LPARAM lParam = FALSE);
	DECLARE_MESSAGE_MAP()

private:
	CString	m_strValidChars[MAX_RESTRICT_COLUMNS];
	UINT	m_nValidLength[MAX_RESTRICT_COLUMNS];
	BOOL	m_bReadOnlyColumns[MAX_RESTRICT_COLUMNS];
	
	int		m_nItem;
	int		m_nSub;
	CListCtrlEdit	m_edit;

	void ShowEdit(BOOL bShow, int nItem, int nIndex, CRect rc/*=CRect(0,0,0,0)*/);
	
#ifdef  _USE_COMBOBOX_
	CListCtrlCombo m_cmb;
	void ShowComb(BOOL bShow, int nItem, int nIndex, CRect rc/*=CRect(0,0,0,0)*/, CStringArray *arr=NULL);
#endif

	BOOL Key_Shift(int &nItem, int &nSub);
	BOOL Key_Ctrl(int &nItem, int &nSub);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLISTCTRL_H__B26FE6EC_7377_4DA6_BEC1_E3C656DACFB8__INCLUDED_)
