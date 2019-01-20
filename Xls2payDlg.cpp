// Xls2payDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Xls2pay.h"
#include "Xls2payDlg.h"
#include "HyperLink.h"

#include "AreaCode.h"
#include "cmb.h"
// #include "afx.inl"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define for if(1) for

#define MAX_TOTAL_SHEET 255


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
	CHyperLink lnkHomeAuthor;
	CHyperLink lnkHomePage;
	
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	lnkHomeAuthor.Attach(GetDlgItem(IDC_STATIC_AUTHOR)->GetSafeHwnd());
	lnkHomeAuthor.SetLink(_T("By：醉书生"), _T("https://seanto.github.io/"), TRUE);
	
	lnkHomePage.Attach(GetDlgItem(IDC_STATIC_HOME)->GetSafeHwnd());
	lnkHomePage.SetLink(_T("BUG反馈"), _T("https://github.com/SeanTo/Xls2pay/issues"), TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXls2payDlg dialog

CXls2payDlg::CXls2payDlg(CWnd* pParent /*=NULL*/) : CDialog(CXls2payDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXls2payDlg)
	m_strPay = _T("");
	m_strXls = _T("接受拖放 xls 文件...");
	m_strTip = _T("");
	m_bRename = FALSE;
	m_bSelType = FALSE;
	m_bAutoFix = FALSE;
	m_bCheck = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	///////////////////////////////////////////////////////
	m_strCode.Empty();
	m_strAcc.Empty();
	m_strAccount.Empty();
	m_strTmpFile.Empty();
	m_pSheet = NULL;

	pApp = (CXls2payApp*)AfxGetApp();
	m_bIsLarge = TRUE;

#ifdef __EXPERT_VER__
	m_bCheck = TRUE;

	m_strTip = CString(_T("1.输入/打开/拖放 指定xls文件\r\n"))
		+ _T("2.视需要勾选相应选项\r\n")
		+ _T("3.点 [读取] 按钮\r\n")
		+ _T("4.选择表单(默认已选中第1个)\r\n")
		+ _T("5.查看摘要，如无错误，[保存]\r\n\r\n")
		+ _T("**[字段检查]、[自动纠错] 可选\r\n")
		+ _T("  如招行PAY格式变化，或新增支行，可不选\r\n")
		+ _T("**[转账类型]、[常用账号] 可选\r\n")
		+ _T("  选中后将忽略表格中相应的字段\r\n")
		+ _T("  城市-地区号联动，根据习惯选一个即可\r\n")
		;
#else
	m_strTip = CString(_T("个人版要求 xls 遵循固定的PAY格式(见示例PAY.XLS)\r\n"))
		+ _T("个人版免费使用！接受单位专有xls格式定制。\r\n")
		+ _T("\r\n专业版特色：\r\n")
		+ _T("1.支持自定格式xls，兼容专有格式账务报表\r\n")
		+ _T("2.自动枚举xls内部表单 (个人版只转换第1个表单)\r\n")
		+ _T("3.字段合法性检查 (个人版只负责转换)\r\n")
		+ _T("4.关联字段自动纠错\r\n")
		+ _T("5.格式化和固定字段可不必输入 (如币种)\r\n")
		+ _T("*.可直接编辑xls生成PAY文件 (需特别定制)\r\n")
		+ _T("  本身就是个增强的电子表格工具，格式化输入。")
		;
#endif
}

void CXls2payDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXls2payDlg)
	DDX_Control(pDX, IDC_LIST_CONFIG, m_List);
	DDX_Control(pDX, IDC_CMB_PROV0, m_cmbProv0);
	DDX_Control(pDX, IDC_CMB_CODE0, m_cmbCode0);
	DDX_Control(pDX, IDC_CMB_CITY0, m_cmbCity0);
	DDX_Control(pDX, IDC_CMB_PROV, m_cmbProv);
	DDX_Control(pDX, IDC_CMB_CODE, m_cmbCode);
	DDX_Control(pDX, IDC_CMB_CITY, m_cmbCity);
	DDX_Control(pDX, IDC_CMB_TYPE, m_cmbType);
	DDX_Control(pDX, IDC_CMB_ACCOUNT, m_cmbAcc);
	DDX_Control(pDX, IDC_CMB_SHEET, m_cmbSheet);
	DDX_Text(pDX, IDC_EDIT_PAY, m_strPay);
	DDX_Text(pDX, IDC_EDIT_XLS, m_strXls);
	DDX_Text(pDX, IDC_EDIT_TIP, m_strTip);
	DDX_Check(pDX, IDC_CHK_RENAME, m_bRename);
	DDX_Check(pDX, IDC_CHK_SEL_TYPE, m_bSelType);
	DDX_Check(pDX, IDC_CHK_AUTOFIX, m_bAutoFix);
	DDX_Check(pDX, IDC_CHK_CHECK, m_bCheck);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXls2payDlg, CDialog)
	//{{AFX_MSG_MAP(CXls2payDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PAY, OnBtnPay)
	ON_BN_CLICKED(IDC_BTN_XLS, OnBtnXls)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_CBN_SELCHANGE(IDC_CMB_SHEET, OnSelchangeCmbSheet)
	ON_BN_CLICKED(IDC_CHK_SEL_TYPE, OnChkSelType)
	ON_BN_CLICKED(IDC_BTN_CONFIG, OnBtnConfig)
	ON_CBN_SELCHANGE(IDC_CMB_CITY, OnSelchangeCmbCity)
	ON_CBN_SELCHANGE(IDC_CMB_CODE, OnSelchangeCmbCode)
	ON_CBN_SELCHANGE(IDC_CMB_ACCOUNT, OnSelendcancelCmbAccount)
	ON_CBN_SELCHANGE(IDC_CMB_TYPE, OnSelchangeCmbType)
	ON_BN_CLICKED(IDC_CHK_CHECK, OnChkCheck)
	ON_CBN_SELCHANGE(IDC_CMB_PROV, OnSelchangeCmbProv)
	ON_CBN_SELCHANGE(IDC_CMB_CITY0, OnSelchangeCmbCity0)
	ON_CBN_SELCHANGE(IDC_CMB_CODE0, OnSelchangeCmbCode0)
	ON_CBN_SELCHANGE(IDC_CMB_PROV0, OnSelchangeCmbProv0)
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
END_MESSAGE_MAP()
// 	ON_WM_DROPFILES(WM_DROPFILES, OnDropFiles)

/////////////////////////////////////////////////////////////////////////////
// CXls2payDlg message handlers

BOOL CXls2payDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	DragAcceptFiles();

#ifdef __EXPERT_VER__
	SetWindowText(_T("xls2pay 1.0 专业版 - 网银批量转账格式自动转换 for 招行"));
	
	// 常用账号
// 	m_arrPreAcc.Add( _T("0755-88888888") );
// 	m_arrPreAcc.Add( _T("0027-1234567812345678") );
// 	m_arrPreAcc.Add( _T("0027*12345678") );
// 	m_arrPreAcc.Add( _T("0010-1234567") );
// 	
// 	for(int i = 0; i < m_arrPreAcc.GetSize(); ++i )
// 	{
// 		if( _T('-') == m_arrPreAcc[i].Left(5)[4]
// 			&& CMB::IsCode( m_arrPreAcc[i].Left(4) )
// 			&& CMB::IsAccount( m_arrPreAcc[i].Right(m_arrPreAcc[i].GetLength()-5), 8 ) )
// 		{
// 			m_cmbAcc.AddString( m_arrPreAcc[i] );
// 		}
// 	}
// 	if(m_cmbAcc.GetCount() > 0)
// 	{
// 		m_cmbAcc.SetCurSel(0);
// 		UpdateData(FALSE);
// 	}

	// 转账类型
	m_cmbType.SetCurSel(0);

	// 全国城市、区号
	for(int i = 0; i < AAC::PROV_NUM; ++i)
	{
		if(AAC::GetNum(i) > 0)
		{
			m_cmbProv0.AddString( AAC::GetProvince(i) );		
			for(int j = 0; j < AAC::GetNum(i); ++j)
				m_cmbCode0.AddString( AAC::GetCode(i, j) );
		}
	}
	SelectCity0(0, 0);

	// 招行城市、区号
	for(int i = 0; i < CMB::PROV_NUM; ++i)
	{
		if(CMB::GetNum(i) > 0)
		{
			m_cmbProv.AddString( CMB::GetProvince(i) );		
			for(int j = 0; j < CMB::GetNum(i); ++j)
				m_cmbCode.AddString( CMB::GetCode(i, j) );
		}
	}

	CString str;
	m_cmbAcc.GetWindowText(str);
	
	if(!str.IsEmpty())
	{
		int x = CMB::FindCode(str.Left(4));
		int y = x % 100;
		x /= 100;
		SelectCity(x, y);
	}
	else
		SelectCity(0, 0);

	// 配置列表
	InitListCtrl();

#else

	SetWindowText(_T("xls2pay 1.0 个人版 - 网银批量转账格式自动转换 for 招行"));

	GetDlgItem(IDC_CHK_CHECK)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHK_AUTOFIX)->EnableWindow(FALSE);

	GetDlgItem(IDC_CHK_SEL_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHK_SEL_ACC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CONFIG)->EnableWindow(FALSE);

	GetDlgItem(IDC_CHK_CHECK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHK_AUTOFIX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHK_SEL_TYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHK_SEL_ACC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_CONFIG)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_CMB_TYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMB_CITY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMB_CODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMB_ACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMB_SHEET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_TIP1)->ShowWindow(SW_HIDE);
// 	GetDlgItem(IDC_STATIC_TIP2)->ShowWindow(SW_HIDE);
// 	GetDlgItem(IDC_STATIC_TIP3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TIP4)->ShowWindow(SW_HIDE);
	

	CRect rc;
	GetWindowRect(&rc);
	rc.bottom -= 60;
	MoveWindow(&rc);

#endif

	BOOL m_bIsLarge = TRUE;
	ShowConfig();

	CRect rect;
	m_cmbCode.GetWindowRect(&rect);

	rect.OffsetRect(-3, -44);
	rect.bottom += 100;
	
	pCmb = new CComboBox;
	pCmb->Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST, rect, this, 4000);

	CFont tpFont;
	tpFont.CreateStockObject(DEFAULT_GUI_FONT);
	pCmb->SetFont(&tpFont);
	tpFont.DeleteObject();

	pCmb->AddString("true");
	pCmb->AddString("false");
	for(int i = 0; i < 10; ++i)
		pCmb->AddString("test");
	pCmb->SetCurSel(0);

	pCmb->ShowWindow(SW_SHOW);
	pCmb->EnableWindow(TRUE);

	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXls2payDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXls2payDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXls2payDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXls2payDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

void CXls2payDlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR buf[MAX_PATH];

	// 文件的数目
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
	
	//for(int i = 0; i < DropCount; i++)
	int i = 0;
	{
		// 第i个文件名字节数
		int iNameSize = DragQueryFile(hDropInfo, i, NULL, 0);

		// 复制文件名到缓冲区
		DragQueryFile(hDropInfo, i, buf, iNameSize+1);
		
		// 获取文件名
		CString str = CString(buf);
		if( str.GetLength() > 4 )
		{
			CString ss = str.Right(4);
			ss.MakeLower();
			if( _T(".xls") == ss )
			{
				m_strXls = str;
				if( ReadInfo() )
				{
					// #ifndef __EXPERT_VER__
					m_cmbSheet.SetCurSel(0);
					OnSelchangeCmbSheet();
					// #endif
				}
			}
		}
		UpdateData(FALSE);
	}

	::DragFinish(hDropInfo);
// 	CDialog::OnDropFiles(hDropInfo);
}

void CXls2payDlg::OnBtnXls() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString str = WND::SelectFile( TRUE, _T("xls"), _T("Excel表格文件(*.xls)|*.xls||") );
	if( !str.IsEmpty() )
	{
		m_strXls = str;
		if( ReadInfo() )
		{
// #ifndef __EXPERT_VER__
			m_cmbSheet.SetCurSel(0);
			OnSelchangeCmbSheet();
// #endif
		}
	}
	
	UpdateData(FALSE);
}

void CXls2payDlg::OnBtnPay() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString str = WND::SelectDirectory( GetSafeHwnd() );
	
	if( ! str.IsEmpty() )
	{
		str.TrimRight(_T("\\"));
		str += CString(_T("\\"));
		m_strPay = str;
		GetPayName();
	}
	
	UpdateData(FALSE);
}

void CXls2payDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	ReadInfo();

	CleanTempFile();
	
/*
	if( ! IsExcelFile(m_strXls) )
		return;
	
	// 打开 xls 文件
	if( ! m_Excel.Load(m_strXls) )
	{
		m_strTip = _T("打开文件错误! \r\n可能 xls 文件属性为只读...");
		UpdateData(FALSE);
		return;
	}

	// 枚举表名
	WND::ClearComboBox(m_cmbSheet);
	if( m_Excel.GetSheetList(/ *m_Excel, * /m_cmbSheet) == 0)
	{
		m_strTip = _T("枚举错误!\r\n无法读取 xls 内部表单名...");
		UpdateData(FALSE);
		return;
	}
		
	GetDlgItem(IDC_CMB_SHEET)->EnableWindow(TRUE);
	
	// 默认选择第1个表单
	m_cmbSheet.SetCurSel(0);
	OnSelchangeCmbSheet();
*/

	UpdateData(FALSE);
}

void CXls2payDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString strFileName = m_strPay;
	
	if( m_bRename )
	{
		strFileName = strFileName.Left( strFileName.GetLength() - 4 );
		strFileName = WND::SelectFile(FALSE, _T("txt"), _T("文本文件(*.TXT)|*.txt|批量转账(*.PAY)|*.pay||"), strFileName );
		
		if( strFileName.IsEmpty() )
			return;
	}

	if( WND::IsExistFile(m_strTmpFile) )
	{
		::CopyFile(m_strTmpFile, strFileName, FALSE);
		AfxMessageBox(_T("文件已保存至:\n") + strFileName);
	}
	else if( Convert(TRUE) )
	{
		CopyFile(m_strTmpFile, strFileName, FALSE);
		AfxMessageBox( _T("已保存到文件:\n") + strFileName );
	}
	else
		AfxMessageBox( _T("写入文件失败!\n") + strFileName );
}

BOOL CXls2payDlg::ReadAccount()
{
	m_arrAcc.RemoveAll();
	m_cmbAcc.ResetContent();

	// 读取表格
	CString code, acc;
	for(size_t i = 0; i < m_pSheet->GetTotalRows(); ++i)
	{
		code = m_pSheet->Cell(i, (size_t)pApp->m_iCol[0])->GetStr();
#ifdef __EXPERT_VER__
		EMFC::Trim(code);
#endif
		if( !CMB::IsCode(code) )
			continue;
		
		acc = m_pSheet->Cell(i, (size_t)pApp->m_iCol[1])->GetStr();
#ifdef __EXPERT_VER__
		EMFC::Trim(acc);
#endif		
		if( !CMB::IsAccount(acc, 8) )
			continue;
		
		acc = code + _T("-") + acc;
		if( !EMFC::IsInArray(acc, m_arrAcc) )
		{
			m_arrAcc.Add(acc);
			m_cmbAcc.AddString(acc);
#ifndef __EXPERT_VER__
			break;
#endif
		}
	}

	if( m_cmbAcc.GetCount() > 0 )
	{
		m_cmbAcc.SetCurSel(0);
		UpdateData(FALSE);

		m_cmbAcc.GetWindowText(acc);
		m_strCode = acc.Left(4);
		m_strAcc  = acc.Mid(5);
		GetPayName();
	}
	GetDlgItem(IDC_CMB_ACCOUNT)->EnableWindow(m_cmbAcc.GetCount() > 0);

	UpdateData(FALSE);
	return TRUE;
}

BOOL CXls2payDlg::IsExcelFile(const CString strXls)
{
	if(strXls.GetLength() <= 4 )
		return FALSE;

	CString str = strXls.Right(4);
	str.MakeLower();
	if( _T(".xls") != str )
	{
		AfxMessageBox( _T("请指定 xls 文件!") );
		return FALSE;
	}
	
	if( ! WND::IsExistFile(m_strXls) )
	{
		AfxMessageBox( _T("找不到 xls 文件:\n") + strXls );
		return FALSE;
	}
	
	return TRUE;
}

void CXls2payDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CleanTempFile();
	
	CDialog::OnCancel();
}

void CXls2payDlg::CleanTempFile()
{
	if( WND::IsExistFile(m_strTmpFile) )
		::DeleteFile(m_strTmpFile);
}

void CXls2payDlg::OnChkCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if( !m_bCheck )
		m_bAutoFix = m_bCheck;
	GetDlgItem(IDC_CHK_AUTOFIX)->EnableWindow(m_bCheck);
	UpdateData(FALSE);
}

void CXls2payDlg::OnChkSelType() 
{
	// TODO: Add your control notification handler code here
#ifdef __EXPERT_VER__
	UpdateData(TRUE);
	GetDlgItem(IDC_CMB_TYPE)->EnableWindow(m_bSelType);

	CleanTempFile();
#endif
}

/*
void CXls2payDlg::OnChkSelAcc() 
{
	// TODO: Add your control notification handler code here
#ifdef __EXPERT_VER__

	UpdateData(TRUE);
	GetDlgItem(IDC_CMB_PROV)->EnableWindow(m_bSelAcc);
	GetDlgItem(IDC_CMB_CITY)->EnableWindow(m_bSelAcc);
	GetDlgItem(IDC_CMB_CODE)->EnableWindow(m_bSelAcc);
	GetDlgItem(IDC_CMB_ACCOUNT)->EnableWindow(m_bSelAcc);
#endif
}
*/

void CXls2payDlg::OnBtnConfig() 
{
	// TODO: Add your control notification handler code here
	ShowConfig();
}

// 全国省
void CXls2payDlg::OnSelchangeCmbProv0() 
{
	// TODO: Add your control notification handler code here
#ifdef __EXPERT_VER__
	CString str;
	m_cmbProv0.GetWindowText(str);
	int x = AAC::FindProvince(str);
// 	AfxMessageBox(MyDT::Int2Str(x) + MyDT::Int2Str(m_cmbProv0.GetCurSel()));
	SelectCity0(x, 0);
#endif
}

// 全国城市
void CXls2payDlg::OnSelchangeCmbCity0() 
{
	// TODO: Add your control notification handler code here
#ifdef __EXPERT_VER__
	CString str;
	m_cmbCity0.GetWindowText(str);
	
	int x = AAC::FindCity(str);
	int y = x % 100;
	x /= 100;

	m_cmbCode0.SelectString(0, AAC::GetCode(x, y) );
#endif
}

// 全国区号
void CXls2payDlg::OnSelchangeCmbCode0() 
{
	// TODO: Add your control notification handler code here
#ifdef __EXPERT_VER__
	CString str;
	m_cmbCode0.GetWindowText(str);
	
	int x = AAC::FindCode(str);
	int y = x % 100;
	x /= 100;

	SelectCity0(x, y);
#endif
}

// 招行省
void CXls2payDlg::OnSelchangeCmbProv() 
{
	// TODO: Add your control notification handler code here
#ifdef __EXPERT_VER__
	CString str;
	m_cmbProv.GetWindowText(str);
	int x = CMB::FindProvince(str);
	SelectCity(x, 0);
#endif
}

// 招行城市
void CXls2payDlg::OnSelchangeCmbCity() 
{
	// TODO: Add your control notification handler code here
#ifdef __EXPERT_VER__
	CString str;
	m_cmbCity.GetWindowText(str);

	int x = CMB::FindCity(str);
	int y = x % 100;
	x /= 100;

	m_cmbCode.SelectString(0, CMB::GetCode(x, y) );
#endif
}

// 招行区号
void CXls2payDlg::OnSelchangeCmbCode() 
{
	// TODO: Add your control notification handler code here
#ifdef __EXPERT_VER__
	CString str;
	m_cmbCode.GetWindowText(str);
	
	int x = CMB::FindCode(str);
	int y = x % 100;
	x /= 100;

// 	AfxMessageBox(MyDT::Int2Str(x) + MyDT::Int2Str(y));
	SelectCity(x, y);
#endif
}

/*
 *	选择转账类型
 */
void CXls2payDlg::OnSelchangeCmbType() 
{
	// TODO: Add your control notification handler code here
	CleanTempFile();
}

/*
 *	选择常用账号
 */
void CXls2payDlg::OnSelendcancelCmbAccount() 
{
	// TODO: Add your control notification handler code here
#ifdef __EXPERT_VER__
	CString str;
	m_cmbAcc.GetWindowText(str);
	
	if( !str.IsEmpty() )
	{
		m_strCode = str.Left(4);
		m_strAcc  = str.Right(str.GetLength()-5);
		GetPayName();

		int x = CMB::FindCode( str.Left(4) );
		int y = x % 100;
		x /= 100;
		
		SelectCity(x, y);
	}
#endif
}

/*
 *	选择表单
 */
void CXls2payDlg::OnSelchangeCmbSheet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	// 初始化表单指针
	m_pSheet = m_Excel.GetWorksheet( (size_t)m_cmbSheet.GetCurSel() );
	
	ReadAccount();
	// 转换

// 	Convert();
	UpdateData(FALSE);
}

BOOL CXls2payDlg::Convert(BOOL bSave)
{
	UpdateData(TRUE);

	// 读取转出账号
	if( !ReadAccount() )
		return FALSE;

	return TRUE;

	// 创建临时文件
	m_strTmpFile = m_strPay.Mid( 0, m_strPay.GetLength()-4 ) + _T(".tmp");
	CStdioFile fout(m_strTmpFile, CFile::modeCreate | CFile::modeWrite | CFile::typeText );
	if( !fout && bSave)
	{
		m_strTip = _T("写文件错误!\r\n") + m_strPay;
		UpdateData(FALSE);
		return FALSE;
	}
	
#ifdef __EXPERT_VER__
	CString strErr = _T("");
	CString strFix = _T("");
	int iInd1 = -1, iInd2 = -1;
	BOOL bIsSame = FALSE, bIsCmb = FALSE, bIsSameCmb = FALSE, bIsCmbPer = FALSE, bOK = FALSE;
	int iProv = -1, iCity = -1, iCode = -1;
// 	CString strProv = _T(""), strCity = _T(""), strCode = _T(""), strAcc;

// 	m_cmbProv.GetWindowText(strProv);
// 	m_cmbCity.GetWindowText(strCity);
// 	m_cmbCode.GetWindowText(strCode);

// 	if(m_cmbAcc.GetCount() > 0)
// 		m_cmbAcc.GetWindowText(strAcc);
#endif
	
	CString str;
	CString strLine, s[13];
	int n[13];
	BOOL bIsNullLine;

	int iTotalRows = m_pSheet->GetTotalRows();
	double dTotalMoney = 0.0, dValidMoney = 0.0, money = 0.0;
	int iCount = 0;

	for(size_t i = 1; i < iTotalRows; ++i)
	{
		bIsNullLine = TRUE;
		for(size_t j = 0; j < 13; ++j)
		{
			s[j] = m_pSheet->Cell(i, (size_t)pApp->m_iCol[j] )->GetStr();
#ifdef __EXPERT_VER__
			EMFC::Trim(s[j]);
#endif
			n[j] = s[j].GetLength();
			bIsNullLine &= (0 == n[j]);
		}
		if( bIsNullLine )
		{
			// 返回空行行号
			iTotalRows = i;
			break;
		}

		money = atof(s[3]);
		dTotalMoney += money;

#ifdef __EXPERT_VER__
		if( m_bCheck )
		{
			// 转出地区号(0)
// 			if( !m_bSelAcc )
			{
// 				if( !s[0].IsEmpty() && s[0] != m_strCode )
// 				{
// 					str.Format( _T("\r\n%8d: 转出地区号 -> ["), (int)(i+1) );
// 					strErr += str + s[0] + _T("]\t\t(不匹配)");
// 					continue;
// 				}
// 				
// 				// 转出账号(1)
// 				if( !s[1].IsEmpty() && s[1] != m_strAcc )
// 				{
// 					str.Format( _T("\r\n%8d: 转出账号   -> ["), (int)(i+1) );
// 					strErr += str + s[1] + _T("]\t(不匹配)");
// 					continue;
// 				}
			}
			s[0] = m_strCode;
			s[1] = m_strAcc;
			n[0] = 4;
			n[1] = s[1].GetLength();
			
			// 转账类型(2)
			if( m_bSelType )
			{
				iInd1 = m_cmbType.GetCurSel();
				s[2] = CMB::GetType( iInd1 );
				n[2] = 4;
			}
			else
			{
				iInd1 = CMB::FindType(s[2]);
				if( 4 != n[2] || -1 == iInd1 )
				{
					str.Format( _T("\r\n%8d: 转账类型   -> ["), (int)(i+1) );
					strErr +=str + s[2] +  _T("]\t\t(TRF1|TRF2|TRF3|TRT1|TRT2|TRT3)");
					continue;
				}
			}
			bIsSame		= CMB::IsSameCity(iInd1);
			bIsCmb		= CMB::IsCmbChina(iInd1);
			bIsSameCmb	= CMB::IsCmbSame(iInd1);
			bIsCmbPer	= CMB::IsCmbPer(iInd1);

			// 转账金额(3)
			bOK = EMFC::IsFloat(s[3], &iInd2); 
			if( !bOK || 2 != iInd2)
			{
				str.Format( _T("\r\n%8d: 转账金额   -> ["), (int)(i+1) );
				iInd2 = s[3].Find(_T('.'));

				if( m_bAutoFix && bOK && 2 != iInd2 )
				{
					strFix += str + s[3] + _T("]\t[");

					s[3].Format(_T("%.2lf"), money );
					n[3] = s[3].GetLength();

					strFix += s[3] + _T("]");
				}
				else
				{
					strErr += str + s[3] + _T("]\t(数值，2位小数)");
					continue;
				}
			}
			
			// 收款人(4)
			if( n[4] < 4 || n[4] > 48 )
			{
				str.Format( _T("\r\n%8d: 收款人姓名 -> ["), (int)(i+1) );
				strErr += str + s[4] + _T("]\t\t(2-24个字)");
				continue;
			}
			
			// 收款省名(5)
			iInd1 = AAC::FindProvince(s[5]);
			if( n[5] > 0 && (n[5] < 4 || n[5] > 20 || iInd1 <= 0) )
			{
				if( m_bAutoFix && 0 == AAC::FindCity(s[5])%100 )
				{
					str.Format( _T("\r\n%8d: 收款省名   -> ["), (int)(i+1) );
					strFix += str + s[5] + _T("]\t\t删除");
					s[5].Empty();
					n[5] = 0;
				}
				else
				{
					str.Format( _T("\r\n%8d: 收款省名   -> ["), (int)(i+1) );
					strErr += str + s[5] + _T("]\t\t(省名，直辖市省略)");
					continue;
				}
			}
			
			// 收款市县名(6)
			iInd1 = CMB::FindCity(s[6]);
			iInd2 = AAC::FindCity(s[6]);
			if( n[6] < 4 || n[6] > 16 || -1 == iInd1 && -1 == iInd2 )
			{
				str.Format( _T("\r\n%8d: 收款市县名  -> ["), (int)(i+1) );
				strErr += str + s[6] + _T("]\t\t(银行支持的城市名，2-8字)");
				continue;
			}
			
			// 市县后缀(7)
			if( m_bAutoFix )
			{
				s[7].Empty();
				n[7] = 0;
			}
			else if( n[7] > 0 && (_T("市") != s[7] && _T("县") != s[7]) )
			{
				str.Format( _T("\r\n%8d: 市县后缀   -> ["), (int)(i+1) );
				strErr += str + s[7] + _T("]\t\t(市/县，或空)");
				continue;
			}
			
			// 收款开户行(8)
			if(n[8] < 8 || n[8] > 48 || bIsCmb && -1 == s[8].Find(_T("招商银行")))
			{
				str.Format( _T("\r\n%8d: 收款开户行 -> ["), (int)(i+1) );
				if(m_bAutoFix && bIsCmbPer)
				{
					strFix += str + s[8] + _T("]\t\t[招商银行](招行个人账户)");
					s[8] = _T("招商银行");
					n[8] = s[8].GetLength();
				}
				else
				{
					if(n[8] < 8 || n[8] > 48)
						strErr += str + s[8] + _T("]\t\t(4-24字)");
					else
						strErr += str + s[8] + _T("]\t\t(须含[招商银行])");
					continue;
				}
			}
			
			// 收款地区号(9)
			iInd1 = CMB::FindCode(s[9]);
			iInd2 = AAC::FindCode(s[9]);
			if(     bIsCmb && (4 != n[9] || !CMB::IsCode(s[9]))
				|| !bIsCmb && (0 != n[9]) )
			{
				str.Format( _T("\r\n%8d: 收款地区号 -> ["), (int)(i+1) );
				if(m_bAutoFix && (bIsSame || !bIsCmb))
				{
					if( bIsSame )
					{
						strFix += str + s[9] + _T("]\t\t[") + s[0] + _T("](同城)");
						s[9] = s[0];
						n[9] = n[0];
					}
					else if( !bIsCmb )
					{
						strFix += str + s[9] + _T("]\t\t删除(他行)");
						s[9].Empty();
						n[9] = 0;
					}
				}
				else
				{
					if( bIsCmb )
						strErr += str + s[9] + _T("]\t\t(招行4位区号)");
					else
						strErr += str + s[9] + _T("]\t\t(他行留空)");
					continue;
				}
			}
			
			// 收款账号(10)
			bOK = n[10] >= 8 && n[10] <= 19 && EMFC::IsNumber(s[10]);
			if( !bOK
				||  bIsCmb && !CMB::IsAccount(s[10], -1, s[9])
				|| !bIsCmb && !CMB::IsAccountOther(s[10]) )
			{
				str.Format( _T("\r\n%8d: 收款账号   -> ["), (int)(i+1) );

				if( !bOK)
				{
					strErr += str + s[10] + _T("]\t(数字，8/12/15/16/19位)");
				}
				else
				{
					if( bIsCmb )
					{
						if( 12 != n[10] )
							strErr += str + s[10] + _T("]\t(招行：8/12/16位)");
						else
							strErr += str + s[10] + _T("]\t(招行：区号不匹配)");
					}
					else
						strErr += str + s[10] + _T("]\t(他行：15/16/19位)");
				}
				continue;
			}
			
			// 备注(11)
			if( n[11] > 17 )
			{
				str.Format( _T("\r\n%8d: 转账备注   -> ["), (int)(i+1) );
				if(m_bAutoFix)
				{
					strFix += str + s[11] + _T("]\t截短[") + s[11].Left(14) + _T("...]");
					s[11] = s[11].Left(14) + _T("...");
					n[11] = 17;
				}
				else
				{
					strErr += str + s[11] + _T("] (0-17字)");
					continue;
				}
			}
			
			// 币种(12)
			if(m_bAutoFix)
			{
				s[12] = _T("10");	// 币种固定
				n[12] = 2;
			}

			// 关联字段
			if( bIsSameCmb )	// 同城招行
			{
				iProv = CMB::FindCode(s[0]);
				iCode = iCity = iProv % 100;
				iProv /= 100;
				if( n[9] != n[0]
					|| CMB::FindCode(s[9])%100 != iCode
 					|| CMB::FindCity(s[6])%100 != iCity
					|| !(0==n[5] && 0==iProv) && !(0!=n[5] && CMB::FindProvince(s[5])==iProv)
					)
				{
					str.Format( _T("\r\n%8d: 关联信息   -> [同城招行:"), (int)(i+1) );
					strErr += str + s[0] + _T("=>")
						+ (0 == n[5] ? _T("[  ]") : s[5]) + _T("-") 
						+ s[6] +  _T("-")
						+ s[9]
						+ _T("] (不匹配)");
					continue;
				}
			}
			else if( !bIsSame && bIsCmb )	// 异地招行
			{
// 				iProv = CMB::FindCode(s[9]);
// 				iCity = CMB::FindCity(s[6]);
// 				if( n[9] == n[0]
// 					|| iCity % 100 != CMB::FindCode(s[9])
// 					|| iCity/100 != iProv )
// 				{
// 					str.Format( _T("\r\n%8d: 收款信息   -> [异地招行:"), (int)(i+1) );
// 					strErr += str + s[0] + _T("->") + s[5] + _T("-") + s[6] +  _T("-") + s[9]
// 						+ _T("] (不匹配)");
// 					continue;
// 				}
			}
			else if( bIsSame && !bIsCmb )	// 同城他行
			{

			}
			else	// 异地他行
			{

			}
			
		}
#endif //__EXPERT_VER__

		dValidMoney += money;
		++iCount;

		if( fout )
		{
			strLine = _T("");
			for(int i = 0; i < 12; ++i)
			{
				strLine += s[i] + _T(" ;");
			}
			strLine += s[12];
			fout.WriteString(strLine + _T("\n"));
		}
	}
	if( fout )
		fout.Close();

	str.Format(_T("\r\n累计笔数: %d\r\n累计金额: %.2lf"), iTotalRows-1, dTotalMoney);
	m_strTip = CString(_T("转出账号: "))
		+ m_strCode + (12 == m_strAcc.GetLength() ? m_strAcc.Right(8) : m_strAcc)
		+ str;

#ifdef __EXPERT_VER__
	if( m_bCheck )
	{
		str.Format(_T("\r\n有效笔数: %d\r\n有效金额: %.2lf"), iCount, dValidMoney);
		m_strTip += str;
		
		if( !strErr.IsEmpty() )
		{
			m_strTip += CString(_T("\r\n======================================================="))
				+ _T("\r\n错误行号: 错误字段   ->\t[字段内容]\t(原因)")
				+ _T("\r\n-------------------------------------------------------")
				+ strErr;
		}

		if( m_bAutoFix )
		{
			m_strTip += CString(_T("\r\n*******************************************************"))
				+ _T("\r\n纠错行号: 字段       ->\t[内容]\t\t操作/[结果]")
				+ strFix
				+ _T("\r\n  所有行: 市县后缀   ->\t\t\t删除")
				+ _T("\r\n  所有行: 币种       ->\t\t\t[10]")
				;
		}
	}
#endif //__EXPERT_VER__

	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);
	UpdateData(FALSE);

	return ( WND::IsExistFile(m_strTmpFile) && iCount > 0);
}

void CXls2payDlg::GetPayName()
{
	int iLen = m_strAcc.GetLength();
	m_strAccount = 16 == iLen ? m_strAcc : (m_strCode + m_strAcc);
	
	// PAY 文件名
	if( m_strPay.IsEmpty() )
		m_strPay = m_strXls;

	m_strPay = m_strPay.Left( m_strPay.ReverseFind(_T('\\')) + 1 );

	if( !m_strCode.IsEmpty() && !m_strAcc.IsEmpty() )
		m_strPay += CMB::GetPayName(m_strAccount);

	m_strTip = _T("转出账号: ") + m_strCode + _T("-") + m_strAcc
		+ _T("\r\n默认文件: ") + CMB::GetPayName(m_strAccount);

	UpdateData(FALSE);
}

void CXls2payDlg::SelectCity0(int x, int y)
{
	ASSERT(x >= 0 && x < AAC::PROV_NUM);
	
	m_cmbCity0.ResetContent();
	
	m_cmbProv0.SelectString(0, AAC::GetProvince(x));
	
	for(int j = 0; j < AAC::GetNum(x); ++j)
		m_cmbCity0.AddString( AAC::GetCity(x, j) );
	
	if( m_cmbCity0.GetCount() > y )
	{
		m_cmbCity0.SetCurSel(y);
		m_cmbCode0.SelectString(0, AAC::GetCode(x, y));
	}
}

void CXls2payDlg::SelectCity(int x, int y)
{
	ASSERT(x >= 0 && x < CMB::PROV_NUM);

	m_cmbCity.ResetContent();

	m_cmbProv.SelectString(0, CMB::GetProvince(x));

	for(int j = 0; j < CMB::GetNum(x); ++j)
		m_cmbCity.AddString( CMB::GetCity(x, j) );

	if( m_cmbCity.GetCount() > y )
	{
		m_cmbCity.SetCurSel(y);
		m_cmbCode.SelectString(0, CMB::GetCode(x, y));
	}
}

BOOL CXls2payDlg::ReadInfo()
{
	GetDlgItem(IDC_CMB_SHEET)->EnableWindow(FALSE);
	
	if( ! IsExcelFile(m_strXls) )
		return FALSE;
	
	// 打开 xls 文件
	if( ! m_Excel.Load(m_strXls) )
	{
		m_strTip = _T("打开文件错误! \r\n可能 xls 文件属性为只读...");
		UpdateData(FALSE);
		return FALSE;
	}
	
	// 枚举表名
	m_cmbSheet.ResetContent();
	int iShees = m_Excel.GetSheetList(m_cmbSheet);
	if( 0 == iShees )
	{
		m_strTip = _T("枚举错误!\r\n无法读取 xls 内部表单名...");
		UpdateData(FALSE);
		return FALSE;
	}
	else
	{
		m_strTip = _T("请选择表单");
		m_strPay = m_strXls.Left( m_strXls.ReverseFind(_T('\\')) + 1 );
	}

	GetDlgItem(IDC_CMB_SHEET)->EnableWindow(iShees > 0);
	UpdateData(FALSE);
	return TRUE;
}

void CXls2payDlg::ShowConfig()
{
#ifdef __EXPERT_VER__
	CRect rc;
	GetWindowRect(&rc);
	if(m_bIsLarge)
		rc.right -= 160;
	else
		rc.right += 160;
	MoveWindow(&rc);
	
	m_bIsLarge = !m_bIsLarge;
	GetDlgItem(IDC_BTN_CONFIG)->SetWindowText(m_bIsLarge ? _T("<< 保存") : _T("配置 >>"));
#endif
}

void CXls2payDlg::InitListCtrl()
{
	m_List.SetExtendedStyle(m_List.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES /*| LVS_EX_CHECKBOXES*/ );
	
	// 列表头
	m_List.InsertColumn(0, "字段/项目", LVCFMT_LEFT, 80);
	m_List.InsertColumn(1, "所在列", LVCFMT_LEFT, 48);
	
	// 只读列
	m_List.SetReadOnlyColumn(0);
	// 输入范围限定
	m_List.SetValidCharsColumn(_T("0123456789"), 3, 1);

	int iCount = 0;
	for(int i = 0; i < CMB::SECT_NUM; ++i)
	{
		m_List.InsertItem(iCount, CMB::GetSect(i) );
		m_List.SetItemText(iCount, 1, MyDT::Int2Str(pApp->m_iCol[iCount]+1));
		++iCount;
	}
	m_List.InsertItem(iCount, _T("起始行号[行]") );
	m_List.SetItemText(iCount, 1, MyDT::Int2Str(2));
}
