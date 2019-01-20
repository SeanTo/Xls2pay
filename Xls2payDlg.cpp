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
	lnkHomeAuthor.SetLink(_T("By��������"), _T("https://seanto.github.io/"), TRUE);
	
	lnkHomePage.Attach(GetDlgItem(IDC_STATIC_HOME)->GetSafeHwnd());
	lnkHomePage.SetLink(_T("BUG����"), _T("https://github.com/SeanTo/Xls2pay/issues"), TRUE);
	
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
	m_strXls = _T("�����Ϸ� xls �ļ�...");
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

	m_strTip = CString(_T("1.����/��/�Ϸ� ָ��xls�ļ�\r\n"))
		+ _T("2.����Ҫ��ѡ��Ӧѡ��\r\n")
		+ _T("3.�� [��ȡ] ��ť\r\n")
		+ _T("4.ѡ���(Ĭ����ѡ�е�1��)\r\n")
		+ _T("5.�鿴ժҪ�����޴���[����]\r\n\r\n")
		+ _T("**[�ֶμ��]��[�Զ�����] ��ѡ\r\n")
		+ _T("  ������PAY��ʽ�仯��������֧�У��ɲ�ѡ\r\n")
		+ _T("**[ת������]��[�����˺�] ��ѡ\r\n")
		+ _T("  ѡ�к󽫺��Ա������Ӧ���ֶ�\r\n")
		+ _T("  ����-����������������ϰ��ѡһ������\r\n")
		;
#else
	m_strTip = CString(_T("���˰�Ҫ�� xls ��ѭ�̶���PAY��ʽ(��ʾ��PAY.XLS)\r\n"))
		+ _T("���˰����ʹ�ã����ܵ�λר��xls��ʽ���ơ�\r\n")
		+ _T("\r\nרҵ����ɫ��\r\n")
		+ _T("1.֧���Զ���ʽxls������ר�и�ʽ���񱨱�\r\n")
		+ _T("2.�Զ�ö��xls�ڲ��� (���˰�ֻת����1����)\r\n")
		+ _T("3.�ֶκϷ��Լ�� (���˰�ֻ����ת��)\r\n")
		+ _T("4.�����ֶ��Զ�����\r\n")
		+ _T("5.��ʽ���͹̶��ֶοɲ������� (�����)\r\n")
		+ _T("*.��ֱ�ӱ༭xls����PAY�ļ� (���ر���)\r\n")
		+ _T("  ������Ǹ���ǿ�ĵ��ӱ�񹤾ߣ���ʽ�����롣")
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
	SetWindowText(_T("xls2pay 1.0 רҵ�� - ��������ת�˸�ʽ�Զ�ת�� for ����"));
	
	// �����˺�
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

	// ת������
	m_cmbType.SetCurSel(0);

	// ȫ�����С�����
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

	// ���г��С�����
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

	// �����б�
	InitListCtrl();

#else

	SetWindowText(_T("xls2pay 1.0 ���˰� - ��������ת�˸�ʽ�Զ�ת�� for ����"));

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

	// �ļ�����Ŀ
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
	
	//for(int i = 0; i < DropCount; i++)
	int i = 0;
	{
		// ��i���ļ����ֽ���
		int iNameSize = DragQueryFile(hDropInfo, i, NULL, 0);

		// �����ļ�����������
		DragQueryFile(hDropInfo, i, buf, iNameSize+1);
		
		// ��ȡ�ļ���
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
	
	CString str = WND::SelectFile( TRUE, _T("xls"), _T("Excel����ļ�(*.xls)|*.xls||") );
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
	
	// �� xls �ļ�
	if( ! m_Excel.Load(m_strXls) )
	{
		m_strTip = _T("���ļ�����! \r\n���� xls �ļ�����Ϊֻ��...");
		UpdateData(FALSE);
		return;
	}

	// ö�ٱ���
	WND::ClearComboBox(m_cmbSheet);
	if( m_Excel.GetSheetList(/ *m_Excel, * /m_cmbSheet) == 0)
	{
		m_strTip = _T("ö�ٴ���!\r\n�޷���ȡ xls �ڲ�����...");
		UpdateData(FALSE);
		return;
	}
		
	GetDlgItem(IDC_CMB_SHEET)->EnableWindow(TRUE);
	
	// Ĭ��ѡ���1����
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
		strFileName = WND::SelectFile(FALSE, _T("txt"), _T("�ı��ļ�(*.TXT)|*.txt|����ת��(*.PAY)|*.pay||"), strFileName );
		
		if( strFileName.IsEmpty() )
			return;
	}

	if( WND::IsExistFile(m_strTmpFile) )
	{
		::CopyFile(m_strTmpFile, strFileName, FALSE);
		AfxMessageBox(_T("�ļ��ѱ�����:\n") + strFileName);
	}
	else if( Convert(TRUE) )
	{
		CopyFile(m_strTmpFile, strFileName, FALSE);
		AfxMessageBox( _T("�ѱ��浽�ļ�:\n") + strFileName );
	}
	else
		AfxMessageBox( _T("д���ļ�ʧ��!\n") + strFileName );
}

BOOL CXls2payDlg::ReadAccount()
{
	m_arrAcc.RemoveAll();
	m_cmbAcc.ResetContent();

	// ��ȡ���
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
		AfxMessageBox( _T("��ָ�� xls �ļ�!") );
		return FALSE;
	}
	
	if( ! WND::IsExistFile(m_strXls) )
	{
		AfxMessageBox( _T("�Ҳ��� xls �ļ�:\n") + strXls );
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

// ȫ��ʡ
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

// ȫ������
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

// ȫ������
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

// ����ʡ
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

// ���г���
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

// ��������
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
 *	ѡ��ת������
 */
void CXls2payDlg::OnSelchangeCmbType() 
{
	// TODO: Add your control notification handler code here
	CleanTempFile();
}

/*
 *	ѡ�����˺�
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
 *	ѡ���
 */
void CXls2payDlg::OnSelchangeCmbSheet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	// ��ʼ����ָ��
	m_pSheet = m_Excel.GetWorksheet( (size_t)m_cmbSheet.GetCurSel() );
	
	ReadAccount();
	// ת��

// 	Convert();
	UpdateData(FALSE);
}

BOOL CXls2payDlg::Convert(BOOL bSave)
{
	UpdateData(TRUE);

	// ��ȡת���˺�
	if( !ReadAccount() )
		return FALSE;

	return TRUE;

	// ������ʱ�ļ�
	m_strTmpFile = m_strPay.Mid( 0, m_strPay.GetLength()-4 ) + _T(".tmp");
	CStdioFile fout(m_strTmpFile, CFile::modeCreate | CFile::modeWrite | CFile::typeText );
	if( !fout && bSave)
	{
		m_strTip = _T("д�ļ�����!\r\n") + m_strPay;
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
			// ���ؿ����к�
			iTotalRows = i;
			break;
		}

		money = atof(s[3]);
		dTotalMoney += money;

#ifdef __EXPERT_VER__
		if( m_bCheck )
		{
			// ת��������(0)
// 			if( !m_bSelAcc )
			{
// 				if( !s[0].IsEmpty() && s[0] != m_strCode )
// 				{
// 					str.Format( _T("\r\n%8d: ת�������� -> ["), (int)(i+1) );
// 					strErr += str + s[0] + _T("]\t\t(��ƥ��)");
// 					continue;
// 				}
// 				
// 				// ת���˺�(1)
// 				if( !s[1].IsEmpty() && s[1] != m_strAcc )
// 				{
// 					str.Format( _T("\r\n%8d: ת���˺�   -> ["), (int)(i+1) );
// 					strErr += str + s[1] + _T("]\t(��ƥ��)");
// 					continue;
// 				}
			}
			s[0] = m_strCode;
			s[1] = m_strAcc;
			n[0] = 4;
			n[1] = s[1].GetLength();
			
			// ת������(2)
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
					str.Format( _T("\r\n%8d: ת������   -> ["), (int)(i+1) );
					strErr +=str + s[2] +  _T("]\t\t(TRF1|TRF2|TRF3|TRT1|TRT2|TRT3)");
					continue;
				}
			}
			bIsSame		= CMB::IsSameCity(iInd1);
			bIsCmb		= CMB::IsCmbChina(iInd1);
			bIsSameCmb	= CMB::IsCmbSame(iInd1);
			bIsCmbPer	= CMB::IsCmbPer(iInd1);

			// ת�˽��(3)
			bOK = EMFC::IsFloat(s[3], &iInd2); 
			if( !bOK || 2 != iInd2)
			{
				str.Format( _T("\r\n%8d: ת�˽��   -> ["), (int)(i+1) );
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
					strErr += str + s[3] + _T("]\t(��ֵ��2λС��)");
					continue;
				}
			}
			
			// �տ���(4)
			if( n[4] < 4 || n[4] > 48 )
			{
				str.Format( _T("\r\n%8d: �տ������� -> ["), (int)(i+1) );
				strErr += str + s[4] + _T("]\t\t(2-24����)");
				continue;
			}
			
			// �տ�ʡ��(5)
			iInd1 = AAC::FindProvince(s[5]);
			if( n[5] > 0 && (n[5] < 4 || n[5] > 20 || iInd1 <= 0) )
			{
				if( m_bAutoFix && 0 == AAC::FindCity(s[5])%100 )
				{
					str.Format( _T("\r\n%8d: �տ�ʡ��   -> ["), (int)(i+1) );
					strFix += str + s[5] + _T("]\t\tɾ��");
					s[5].Empty();
					n[5] = 0;
				}
				else
				{
					str.Format( _T("\r\n%8d: �տ�ʡ��   -> ["), (int)(i+1) );
					strErr += str + s[5] + _T("]\t\t(ʡ����ֱϽ��ʡ��)");
					continue;
				}
			}
			
			// �տ�������(6)
			iInd1 = CMB::FindCity(s[6]);
			iInd2 = AAC::FindCity(s[6]);
			if( n[6] < 4 || n[6] > 16 || -1 == iInd1 && -1 == iInd2 )
			{
				str.Format( _T("\r\n%8d: �տ�������  -> ["), (int)(i+1) );
				strErr += str + s[6] + _T("]\t\t(����֧�ֵĳ�������2-8��)");
				continue;
			}
			
			// ���غ�׺(7)
			if( m_bAutoFix )
			{
				s[7].Empty();
				n[7] = 0;
			}
			else if( n[7] > 0 && (_T("��") != s[7] && _T("��") != s[7]) )
			{
				str.Format( _T("\r\n%8d: ���غ�׺   -> ["), (int)(i+1) );
				strErr += str + s[7] + _T("]\t\t(��/�أ����)");
				continue;
			}
			
			// �տ����(8)
			if(n[8] < 8 || n[8] > 48 || bIsCmb && -1 == s[8].Find(_T("��������")))
			{
				str.Format( _T("\r\n%8d: �տ���� -> ["), (int)(i+1) );
				if(m_bAutoFix && bIsCmbPer)
				{
					strFix += str + s[8] + _T("]\t\t[��������](���и����˻�)");
					s[8] = _T("��������");
					n[8] = s[8].GetLength();
				}
				else
				{
					if(n[8] < 8 || n[8] > 48)
						strErr += str + s[8] + _T("]\t\t(4-24��)");
					else
						strErr += str + s[8] + _T("]\t\t(�뺬[��������])");
					continue;
				}
			}
			
			// �տ������(9)
			iInd1 = CMB::FindCode(s[9]);
			iInd2 = AAC::FindCode(s[9]);
			if(     bIsCmb && (4 != n[9] || !CMB::IsCode(s[9]))
				|| !bIsCmb && (0 != n[9]) )
			{
				str.Format( _T("\r\n%8d: �տ������ -> ["), (int)(i+1) );
				if(m_bAutoFix && (bIsSame || !bIsCmb))
				{
					if( bIsSame )
					{
						strFix += str + s[9] + _T("]\t\t[") + s[0] + _T("](ͬ��)");
						s[9] = s[0];
						n[9] = n[0];
					}
					else if( !bIsCmb )
					{
						strFix += str + s[9] + _T("]\t\tɾ��(����)");
						s[9].Empty();
						n[9] = 0;
					}
				}
				else
				{
					if( bIsCmb )
						strErr += str + s[9] + _T("]\t\t(����4λ����)");
					else
						strErr += str + s[9] + _T("]\t\t(��������)");
					continue;
				}
			}
			
			// �տ��˺�(10)
			bOK = n[10] >= 8 && n[10] <= 19 && EMFC::IsNumber(s[10]);
			if( !bOK
				||  bIsCmb && !CMB::IsAccount(s[10], -1, s[9])
				|| !bIsCmb && !CMB::IsAccountOther(s[10]) )
			{
				str.Format( _T("\r\n%8d: �տ��˺�   -> ["), (int)(i+1) );

				if( !bOK)
				{
					strErr += str + s[10] + _T("]\t(���֣�8/12/15/16/19λ)");
				}
				else
				{
					if( bIsCmb )
					{
						if( 12 != n[10] )
							strErr += str + s[10] + _T("]\t(���У�8/12/16λ)");
						else
							strErr += str + s[10] + _T("]\t(���У����Ų�ƥ��)");
					}
					else
						strErr += str + s[10] + _T("]\t(���У�15/16/19λ)");
				}
				continue;
			}
			
			// ��ע(11)
			if( n[11] > 17 )
			{
				str.Format( _T("\r\n%8d: ת�˱�ע   -> ["), (int)(i+1) );
				if(m_bAutoFix)
				{
					strFix += str + s[11] + _T("]\t�ض�[") + s[11].Left(14) + _T("...]");
					s[11] = s[11].Left(14) + _T("...");
					n[11] = 17;
				}
				else
				{
					strErr += str + s[11] + _T("] (0-17��)");
					continue;
				}
			}
			
			// ����(12)
			if(m_bAutoFix)
			{
				s[12] = _T("10");	// ���̶ֹ�
				n[12] = 2;
			}

			// �����ֶ�
			if( bIsSameCmb )	// ͬ������
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
					str.Format( _T("\r\n%8d: ������Ϣ   -> [ͬ������:"), (int)(i+1) );
					strErr += str + s[0] + _T("=>")
						+ (0 == n[5] ? _T("[  ]") : s[5]) + _T("-") 
						+ s[6] +  _T("-")
						+ s[9]
						+ _T("] (��ƥ��)");
					continue;
				}
			}
			else if( !bIsSame && bIsCmb )	// �������
			{
// 				iProv = CMB::FindCode(s[9]);
// 				iCity = CMB::FindCity(s[6]);
// 				if( n[9] == n[0]
// 					|| iCity % 100 != CMB::FindCode(s[9])
// 					|| iCity/100 != iProv )
// 				{
// 					str.Format( _T("\r\n%8d: �տ���Ϣ   -> [�������:"), (int)(i+1) );
// 					strErr += str + s[0] + _T("->") + s[5] + _T("-") + s[6] +  _T("-") + s[9]
// 						+ _T("] (��ƥ��)");
// 					continue;
// 				}
			}
			else if( bIsSame && !bIsCmb )	// ͬ������
			{

			}
			else	// �������
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

	str.Format(_T("\r\n�ۼƱ���: %d\r\n�ۼƽ��: %.2lf"), iTotalRows-1, dTotalMoney);
	m_strTip = CString(_T("ת���˺�: "))
		+ m_strCode + (12 == m_strAcc.GetLength() ? m_strAcc.Right(8) : m_strAcc)
		+ str;

#ifdef __EXPERT_VER__
	if( m_bCheck )
	{
		str.Format(_T("\r\n��Ч����: %d\r\n��Ч���: %.2lf"), iCount, dValidMoney);
		m_strTip += str;
		
		if( !strErr.IsEmpty() )
		{
			m_strTip += CString(_T("\r\n======================================================="))
				+ _T("\r\n�����к�: �����ֶ�   ->\t[�ֶ�����]\t(ԭ��)")
				+ _T("\r\n-------------------------------------------------------")
				+ strErr;
		}

		if( m_bAutoFix )
		{
			m_strTip += CString(_T("\r\n*******************************************************"))
				+ _T("\r\n�����к�: �ֶ�       ->\t[����]\t\t����/[���]")
				+ strFix
				+ _T("\r\n  ������: ���غ�׺   ->\t\t\tɾ��")
				+ _T("\r\n  ������: ����       ->\t\t\t[10]")
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
	
	// PAY �ļ���
	if( m_strPay.IsEmpty() )
		m_strPay = m_strXls;

	m_strPay = m_strPay.Left( m_strPay.ReverseFind(_T('\\')) + 1 );

	if( !m_strCode.IsEmpty() && !m_strAcc.IsEmpty() )
		m_strPay += CMB::GetPayName(m_strAccount);

	m_strTip = _T("ת���˺�: ") + m_strCode + _T("-") + m_strAcc
		+ _T("\r\nĬ���ļ�: ") + CMB::GetPayName(m_strAccount);

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
	
	// �� xls �ļ�
	if( ! m_Excel.Load(m_strXls) )
	{
		m_strTip = _T("���ļ�����! \r\n���� xls �ļ�����Ϊֻ��...");
		UpdateData(FALSE);
		return FALSE;
	}
	
	// ö�ٱ���
	m_cmbSheet.ResetContent();
	int iShees = m_Excel.GetSheetList(m_cmbSheet);
	if( 0 == iShees )
	{
		m_strTip = _T("ö�ٴ���!\r\n�޷���ȡ xls �ڲ�����...");
		UpdateData(FALSE);
		return FALSE;
	}
	else
	{
		m_strTip = _T("��ѡ���");
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
	GetDlgItem(IDC_BTN_CONFIG)->SetWindowText(m_bIsLarge ? _T("<< ����") : _T("���� >>"));
#endif
}

void CXls2payDlg::InitListCtrl()
{
	m_List.SetExtendedStyle(m_List.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES /*| LVS_EX_CHECKBOXES*/ );
	
	// �б�ͷ
	m_List.InsertColumn(0, "�ֶ�/��Ŀ", LVCFMT_LEFT, 80);
	m_List.InsertColumn(1, "������", LVCFMT_LEFT, 48);
	
	// ֻ����
	m_List.SetReadOnlyColumn(0);
	// ���뷶Χ�޶�
	m_List.SetValidCharsColumn(_T("0123456789"), 3, 1);

	int iCount = 0;
	for(int i = 0; i < CMB::SECT_NUM; ++i)
	{
		m_List.InsertItem(iCount, CMB::GetSect(i) );
		m_List.SetItemText(iCount, 1, MyDT::Int2Str(pApp->m_iCol[iCount]+1));
		++iCount;
	}
	m_List.InsertItem(iCount, _T("��ʼ�к�[��]") );
	m_List.SetItemText(iCount, 1, MyDT::Int2Str(2));
}
