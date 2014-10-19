// MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFC.h"
#include "MFCDlg.h"
#include "HoverButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
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

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCDlg dialog

CMFCDlg::CMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCDlg::IDD, pParent)
{
	m_bOK=FALSE;
	//{{AFX_DATA_INIT(CMFCDlg)
	m_Radio = -1;
	m_Distribute = FALSE;
	m_Shuxue = FALSE;
	m_English = FALSE;
	m_Network = FALSE;
	m_int=0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CMFCDlg::~CMFCDlg()
{
		delete m_pToolTipCtrl;

}
void CMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMFCDlg)
	DDX_Control(pDX, IDC_TREE1, m_treeCtrl);
	DDX_Control(pDX, IDC_LIST1, m_listCtrlView);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Radio(pDX, IDC_WULI_RADIO, m_Radio);
	DDX_Check(pDX, IDC_CK_DISTRIBUTE, m_Distribute);
	DDX_Check(pDX, IDC_CK_SHUXUE, m_Shuxue);
	DDX_Check(pDX, IDC_CK_ENGLISH, m_English);
	DDX_Check(pDX, IDC_CK_NETWORK, m_Network);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH, m_ShockwaveFlash);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMFCDlg, CDialog)
	//{{AFX_MSG_MAP(CMFCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_WM_HSCROLL()
	ON_WM_CANCELMODE()
	ON_NOTIFY(NM_CLICK, IDC_TREE1, OnClickTree1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, OnRclickTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_OPENSWF, OnOpenswf)
	ON_BN_CLICKED(IDC_CLOSESWF, OnCloseswf)
	ON_BN_CLICKED(IDC_PLAYSWF2, OnPlayswf2)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDB_EXIT,OnExit)
	ON_BN_CLICKED(IDB_HELP,OnHelp)
	ON_BN_CLICKED(IDB_MINIMIZE,OnMinimize)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCDlg message handlers

BOOL CMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ShowWindow(SW_SHOWMAXIMIZED);
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
//	SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_bg.LoadBitmap(IDB_BITMAP1);//���ر���ͼƬ
	//m_bg.LoadBitmap(IDB_BACKGROUND1);
	//m_pToolTipCtrl->EnableToolTips(TRUE);
//	m_pToolTipCtrl->Activate(TRUE);

	m_ShockwaveFlash.SetBackgroundColor((long)RGB(100,255,100));//ΪFlash������ñ���ɫ

	CBitmap m_tmp;
	BITMAP Bmp;
	m_tmp.LoadBitmap(IDB_EXIT1);
	m_tmp.GetBitmap(&Bmp);
	m_Exit.Create(NULL,BS_OWNERDRAW,CRect(0,0,Bmp.bmWidth,Bmp.bmHeight),this,IDB_EXIT);
	m_Exit.ShowWindow(SW_SHOW);
	m_Exit.MoveWindow(1400,0,Bmp.bmWidth,Bmp.bmHeight);
	m_Exit.LoadBitmaps(IDB_EXIT1,
		NULL,
		IDB_EXIT2,
		IDB_EXIT1);
	m_tmp.DeleteObject();
//	m_pToolTipCtrl->AddTool(&m_Exit,"�ر�");

	m_tmp.LoadBitmap(IDB_HELP1);
	m_tmp.GetBitmap(&Bmp);
	m_Help.Create(NULL,BS_OWNERDRAW,CRect(0,0,Bmp.bmWidth,Bmp.bmHeight),this,IDB_HELP);
	m_Help.ShowWindow(SW_SHOW);
	m_Help.MoveWindow(1375,0,Bmp.bmWidth,Bmp.bmWidth,Bmp.bmHeight);
	m_Help.LoadBitmaps(IDB_HELP1,
		NULL,
		IDB_HELP2,
		IDB_HELP1);
	m_tmp.DeleteObject();
	//m_pToolTipCtrl->AddTool(&m_Help,"����");

	m_tmp.LoadBitmap(IDB_MINIMIZE1);
	m_tmp.GetBitmap(&Bmp);
	m_Minimize.Create(NULL,BS_OWNERDRAW,CRect(0,0,Bmp.bmWidth,Bmp.bmHeight),this,IDB_MINIMIZE);
	m_Minimize.ShowWindow(SW_SHOW);
	m_Minimize.MoveWindow(1346,0,Bmp.bmWidth,Bmp.bmHeight);
	m_Minimize.LoadBitmaps(IDB_MINIMIZE1,
		NULL,
		IDB_MINIMIZE2,
		IDB_MINIMIZE1);
	m_tmp.DeleteObject();
//	m_pToolTipCtrl->AddTool(&m_Minimize,"��С��");

	m_Slider.SetRange(0,100);//���û���ķ�Χ
	m_Slider.SetTicFreq(10);//���û���ÿ���ٵ�λ��һ���̶�
	m_Slider.SetPageSize(30);//���ð���PageDown��PageUp��ťʱ�������
	m_Slider.SetLineSize(20);//���û������Ҽ�ͷ�������
	m_Slider.SetPos(50);//���û��鵱ǰλ��
	m_int=m_Slider.GetPos();//��ó���տ�ʼ����ʱ���������ڵ�λ��

	m_listCtrlView.ModifyStyle(LVS_SORTASCENDING | LVS_SORTDESCENDING,0);
	m_listCtrlView.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
    /*LV_COLUMN comn;//LV_COLUMN�ṹ����LVCOLUMN�ṹ����һ���ģ������໥�滻
	comn.pszText ="ƥ�����";
	comn.mask =LVCF_TEXT;//��ʱpszText��Ч
	m_listCtrlView.InsertColumn(0,&comn);
	m_listCtrlView.SetColumnWidth(0,80);
    
	comn.pszText ="����";
	comn.mask = LVCF_TEXT;
	m_listCtrlView.InsertColumn(1,&comn);
	m_listCtrlView.SetColumnWidth(1,80);*/
	LVCOLUMN lvColumn;//��Ҫ�����б�ؼ��е����ԣ�������-��ʽ-�鿴�����鿴���޸�Ϊ������ʽ
	char Header[5][10]={"ƥ�����","����","��С","�޸�����","��ϸ��Ϣ"};
	for(int i=0;i<5;i++)
		
	{
		lvColumn.mask=LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH|LVCF_FMT;
		lvColumn.fmt=LVCFMT_LEFT;//���뷽ʽ
		lvColumn.iSubItem=i;//������
		lvColumn.pszText=Header[i];//��ͷ�ı�
		lvColumn.cx=100;//�����п�
		m_listCtrlView.InsertColumn(i,&lvColumn);//�����в��뵽�б�ؼ���
	}
	m_listCtrlView.SetColumnWidth(3,200);//�������п������һ��
	
	CTime time=::GetCurrentTime();
	CString strTime=time.Format("%Y/%m/%d");
	
	m_listCtrlView.InsertItem(0,"����");//��������
	m_listCtrlView.SetItemText(0,1,"����");
	m_listCtrlView.SetItemText(0,2,"4KB");
	m_listCtrlView.SetItemText(0,3,strTime);
	m_listCtrlView.SetItemText(0,4,"�׶�����");

	m_listCtrlView.InsertItem(1,"�Ϻ�");
	m_listCtrlView.SetItemText(1,1,"��չ");
	m_listCtrlView.SetItemText(1,2,"2MB");
	m_listCtrlView.SetItemText(1,3,strTime);
	m_listCtrlView.SetItemText(1,4,"�Ϻ���������");

	m_listCtrlView.InsertItem(2,"����");
	m_listCtrlView.SetItemText(2,1,"����");
	m_listCtrlView.SetItemText(2,2,"2KB");
	m_listCtrlView.SetItemText(2,3,strTime);
	m_listCtrlView.SetItemText(2,4,"���ھ�ҵ����");

	m_listCtrlView.InsertItem(3,"����");
	m_listCtrlView.SetItemText(3,1,"��ݸ");
	m_listCtrlView.SetItemText(3,2,"6KB");
	m_listCtrlView.SetItemText(3,3,strTime);
	m_listCtrlView.SetItemText(3,4,"��ݸ�������㶮��");
	
	m_listCtrlView.InsertItem(4,"����");
	m_listCtrlView.SetItemText(4,1,"��ɳ");
	m_listCtrlView.SetItemText(4,2,"4KB");
	m_listCtrlView.SetItemText(4,3,strTime);
	m_listCtrlView.SetItemText(4,4,"������̶ҽ���¹�");

	m_listCtrlView.InsertItem(5,"����");
	m_listCtrlView.SetItemText(5,1,"�ϲ�");
	m_listCtrlView.SetItemText(5,2,"12KB");
	m_listCtrlView.SetItemText(5,3,strTime);
	m_listCtrlView.SetItemText(5,4,"���������");

	m_listCtrlView.InsertItem(6,"����");
	m_listCtrlView.SetItemText(6,1,"�Ͼ�");
	m_listCtrlView.SetItemText(6,2,"1KB");
	m_listCtrlView.SetItemText(6,3,strTime);
	m_listCtrlView.SetItemText(6,4,"�Ͼ��õط���");

	m_listCtrlView.InsertItem(7,"�㽭");
	m_listCtrlView.SetItemText(7,1,"����");
	m_listCtrlView.SetItemText(7,2,"2KB");
	m_listCtrlView.SetItemText(7,3,strTime);
	m_listCtrlView.SetItemText(7,4,"����IT��ҵ����");

	m_listCtrlView.InsertItem(8,"����");
	m_listCtrlView.SetItemText(8,1,"����");
	m_listCtrlView.SetItemText(8,2,"8KB");
	m_listCtrlView.SetItemText(8,3,strTime);
	m_listCtrlView.SetItemText(8,4,"������ѧ��ӭ��");
	
	m_listCtrlView.InsertItem(9,"����");
	m_listCtrlView.SetItemText(9,1,"����");
	m_listCtrlView.SetItemText(9,2,"16KB");
	m_listCtrlView.SetItemText(9,3,strTime);
	m_listCtrlView.SetItemText(9,4,"���ݴ�ѧʱ985��");
	m_listCtrlView.ShowWindow(TRUE);
	
	m_List.ModifyStyle(LVS_SORTDESCENDING | LVS_SORTASCENDING,0);
	m_List.AddString("hello");
	m_List.AddString("world");
	m_List.AddString("birthday");
	m_List.AddString("success");
	m_List.AddString("come on");
	m_List.SetCurSel(0);//�����б��ʼ��һ������ѡ��״̬

	m_pToolTipCtrl=new CToolTipCtrl;//�����ؼ�������ʾ�ؼ�����ʾ��ʾ��Ϣ
	if(!m_pToolTipCtrl->Create(this,TTS_ALWAYSTIP))
	{
		TRACE("Uable to Create ToolTip\n");
		return FALSE;
	}
	CMFCApp *pApp=(CMFCApp *)AfxGetApp();//����ͼ���б�
	Cil1.Create(16,16,ILC_COLOR,2,2);
	
	Cil1.Add(pApp->LoadIcon(IDI_ICON1));
	Cil1.Add(pApp->LoadIcon(IDI_ICON2));
	  
	m_treeCtrl.SetImageList(&Cil1,TVSIL_NORMAL); //����ͼ���б�
	//m_treeCtrl.SetImageList(&Cil2,TVSIL_NORMAL);//�˳�����Cil2û���õ�

	DWORD dwStyles=GetWindowLong(m_treeCtrl.m_hWnd,GWL_STYLE);//��ȡ������ԭ���
	dwStyles|=TVS_EDITLABELS|TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT;
	SetWindowLong(m_treeCtrl.m_hWnd,GWL_STYLE,dwStyles);//���÷��
	m_treeCtrl.ModifyStyle(LVS_SORTASCENDING|LVS_SORTDESCENDING,0);
	HTREEITEM hRoot,hRoot1,hItem,hItem1,hSubItem,hSubItem1;
	//hItem = m_treeCtrl.InsertItem("Parent1",0,1,TVI_ROOT);
	hItem = m_treeCtrl.InsertItem("IT��̳",0,1,TVI_ROOT);
	
	hRoot = hItem;//������ڵ���
	//hSubItem = m_treeCtrl.InsertItem("child1",0,1,hItem);

		hSubItem = m_treeCtrl.InsertItem("����ģ��",0,1,hItem);

	//hSubItem = m_treeCtrl.InsertItem("child2",0,1,hItem,hSubItem);//��child1�����child2

		hSubItem = m_treeCtrl.InsertItem("�ο�ģ��",0,1,hItem,hSubItem);

	//hSubItem = m_treeCtrl.InsertItem("child3",0,1,hItem,hSubItem);//��child2�������child3

		hSubItem = m_treeCtrl.InsertItem("���û�ע��",0,1,hItem,hSubItem);
	
	//hItem = m_treeCtrl.InsertItem("Parent2",0,1,TVI_ROOT,hItem);//�µĸ��ڵ�����ڵ�ͬ��

		hItem = m_treeCtrl.InsertItem("��̨ά��",0,1,TVI_ROOT,hItem);//�µĸ��ڵ�����ڵ�ͬ��

	//hItem = m_treeCtrl.InsertItem("Parent3",0,1,TVI_ROOT,hItem);//�µĸ��ڵ�
	
		hItem = m_treeCtrl.InsertItem("����",0,1,TVI_ROOT,hItem);//�µĸ��ڵ�����ڵ�ͬ��

	
		hItem1=m_treeCtrl.InsertItem("����Աģ��",1,0,TVI_ROOT);
		hRoot1=hItem1;
		hSubItem1=m_treeCtrl.InsertItem("C++/MFCģ��",1,0,hItem1);
		hSubItem1=m_treeCtrl.InsertItem("C����ģ��",1,0,hItem1,hSubItem1);

		hItem1=m_treeCtrl.InsertItem("��Ƹ��Ϣ",1,0,TVI_ROOT,hItem1);
		hItem1=m_treeCtrl.InsertItem("��̳���ط�����",1,0,TVI_ROOT,hItem1);
		m_treeCtrl.Expand(hRoot1,TVE_EXPAND);
		
	m_treeCtrl.Expand(hRoot,TVE_EXPAND);//չ����״�ؼ����нڵ�
	CRect r;
	m_treeCtrl.GetItemRect(hRoot,&r,TRUE);
	m_pToolTipCtrl->AddTool(&m_treeCtrl,"TreeCtrl Item Info",&r,IDC_TREE1);
	
	memset(title,0,255);
	//GetPrivateProfileString("��������","���������","Ģ���ؼ����Գ���",m_strTitle.GetBuffer(255),255,".\\Mogu.ini");//������ⲻ�ʺ���CString����Ӧ��char����
	GetPrivateProfileString("��������","���������","Ģ���ؼ����Գ���",title,255,".\\Mogu.ini");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCDlg::OnPaint() 
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
	////////////////////////////////////////���Ի��򴴽�����ͼƬ
	CDC *hDC=GetDC();
	CDC m_DC;
	CRect rect;
	m_DC.CreateCompatibleDC(hDC);
	m_DC.SelectObject(&m_bg);
	GetClientRect(rect);
	hDC->BitBlt(0,0,rect.Width(),rect.Height(),&m_DC,0,0,SRCCOPY);
	//hDC->StretchBlt(0,0,rect.Width(),rect.Height(),&m_DC,0,0,rect.Width(),rect.Height(),SRCCOPY);
	ReleaseDC(hDC);
	/////////////////////////////////////////�������ļ��ж�ȡ����������ݣ�����ʾ��Ӧ�ó��������ڵ����Ͻ�λ��
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont(120,"����",NULL);
	CFont *pOldFont=dc.SelectObject(&font);
	dc.SetTextColor(RGB(0,0,0));
	dc.SetBkMode(TRANSPARENT);
	//MessageBox(m_strTitle);
	//dc.TextOut(5,5,m_strTitle);
	dc.TextOut(5,5,title);
	dc.SelectObject(pOldFont);
	
	m_Exit.RedrawWindow();
	m_Help.RedrawWindow();
	m_Minimize.RedrawWindow();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMFCDlg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	if(!m_bOK)
	{
		
		UpdateData(TRUE);//�Լ��������ǻ�ÿؼ�����ֵ��ע�ⲻҪ����UpdateData(TRUE)����
		if(m_Shuxue)
		{
			GetDlgItem(IDC_CK_SHUXUE)->GetWindowText(m_strShuxue);
			//	MessageBox(m_strShuxue,"ѡ����Ϣ",MB_OKCANCEL);
			m_List.AddString(m_strShuxue);
		}
		if(m_Distribute)
		{
			GetDlgItem(IDC_CK_DISTRIBUTE)->GetWindowText(m_strDistribute);
			//	MessageBox(m_strDistribute,"ѡ����Ϣ",MB_OKCANCEL);
			m_List.AddString(m_strDistribute);
		}
		if(m_English)
		{
			GetDlgItem(IDC_CK_ENGLISH)->GetWindowText(m_strEnglish);
			//	MessageBox(m_strEnglish,"ѡ����Ϣ",MB_OKCANCEL);
			m_List.AddString(m_strEnglish);
		}
		if(m_Network)
		{
			GetDlgItem(IDC_CK_NETWORK)->GetWindowText(m_strNetwork);
			//	MessageBox(m_strNetwork,"ѡ����Ϣ",MB_OKCANCEL);
			m_List.AddString(m_strNetwork);
		}
		switch(m_Radio)
		{
		case 0:
			GetDlgItemText(IDC_WULI_RADIO,m_strRadio);
			//	MessageBox(m_strRadio,"רҵ��Ϣ",MB_OKCANCEL);
			break;
		case 1:
			GetDlgItemText(IDC_IT_RADIO,m_strRadio);
			//	MessageBox(m_strRadio,"רҵ��Ϣ",MB_OKCANCEL);
			break;
		case 2:
			GetDlgItemText(IDC_DIANQI_RADIO,m_strRadio);
			//	MessageBox(m_strRadio,"רҵ��Ϣ",MB_OKCANCEL);
			break;
		default:
			break;
		}
		m_List.AddString(m_strRadio);
		CString m_strSlider;
		m_strSlider.Format("��ǰSliderֵΪ:%d",m_int);
		m_List.AddString(m_strSlider);
		m_bOK=TRUE;
	}

}

void CMFCDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) //���ڻ�õ�ǰ�����ֵ�����ڻ�����û����Ӧ���黬������Ϣ��Ӧ�����ģ��������ǿ��������������WM_HSCROLL��Ϣ���ڴ˺����д������´����û���ĵ�ǰλ��
{
	// TODO: Add your message handler code here and/or call default
	CSliderCtrl *pSlider=(CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	m_int=pSlider->GetPos();//�����껬������֮��Ļ�������λ�õ�ֵ
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMFCDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

BOOL CMFCDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pToolTipCtrl)
	{
		m_pToolTipCtrl->RelayEvent(pMsg);
	}

	if(pMsg->message==WM_KEYDOWN)//�����ȼ����
	{
		switch(pMsg->wParam)
		{
		case 'L':
			if(::GetKeyState(VK_CONTROL)<0)
			{
				MessageBox("��ϼ� Ctrl+L ������");
			}
			break;
		case 'K':
			if(::GetKeyState(VK_SHIFT)<0)
			{
				MessageBox("��ϼ� Shift+K ������");
			}
			break;
		case VK_RETURN:
			OnExit();
			return 0;
			break;
		case VK_ESCAPE:
			OnExit();
			return 0;
			break;
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CMFCDlg::OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult) //���ؼ������������¼���Ӧ����
{
	// TODO: Add your control notification handler code here
	
	CPoint curPoint;
    UINT nFlags;//��ȡ�������ڴ�item�ı��
    HTREEITEM hItem;
	CString strItem;
    GetCursorPos(&curPoint); //��ǰ������
    m_treeCtrl.ScreenToClient(&curPoint); //��Ļ����ת��ΪTREE������
    hItem = m_treeCtrl.HitTest(curPoint, &nFlags); //�����Ƿ���ITEM

    if(hItem && (TVHT_ONITEM & nFlags)) //�ж��Ƿ���HTREEITEM
    {
		MessageBox("���ؼ��ڵ���Ӧ�����������¼�");
		//m_CurItem=m_treeCtrl.GetSelectedItem();
    }

	*pResult = 0;
}

void CMFCDlg::OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult) //���ؼ�����Ҽ������¼���Ӧ����
{
	// TODO: Add your control notification handler code here
	CPoint curPoint;
	UINT nFlags;
	HTREEITEM hItem;
	GetCursorPos(&curPoint);
	m_treeCtrl.ScreenToClient(&curPoint);//����Ļ����ת��ΪTREE������
	hItem=m_treeCtrl.HitTest(curPoint,&nFlags);
	if(hItem&&(TVHT_ONITEM&nFlags))
	{
		MessageBox("���ؼ��ڵ�����Ҽ������¼�");
	//	m_CurItem=m_treeCtrl.GetSelectedItem();
		
	}
	*pResult = 0;
}

void CMFCDlg::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)//
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	
	
	pNMTreeView->itemNew.iImage;
	pNMTreeView->itemOld.iImage;
	if(pNMTreeView->itemOld.iImage)
	{
		MessageBox("����һ���ڵ�ת�Ƶ�����һ���ڵ�");
	}
	*pResult = 0;
}
void CMFCDlg::OnExit()
{
	DestroyWindow();
}
void CMFCDlg::OnHelp()
{
	MessageBox("��������СĢ���������\n\n��ϵ��ʽ:13547946476646\n\n�־Ͷ���������ѧ��ϢѧԺ","���οؼ�����",MB_OK);
}
void CMFCDlg::OnMinimize()
{
	ShowWindow(SW_SHOWMINIMIZED);
}

void CMFCDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) //��Ӧ�б�ؼ������¼�
{
	// TODO: Add your control notification handler code here
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	//MessageBox(pNMTreeView->itemNew.pszText);
	char Text[255];
	m_listCtrlView.GetItemText(0,0,Text,255);
	MessageBox(Text);
	*pResult = 0;
}

void CMFCDlg::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

HBRUSH CMFCDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd==this)//�ػ�����
	{
		
		//return m_Brush;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CMFCDlg::OnOpenswf() 
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE,"*.txt","MFC",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"SWF Files(*.swf)|*.swf|All Files(*.*)|*.*||",this);
	if(IDOK==fileDlg.DoModal())
	{
		CString fullPath=fileDlg.GetPathName();
		m_ShockwaveFlash.LoadMovie(0,fullPath);
		m_ShockwaveFlash.StopPlay();
	}
}

void CMFCDlg::OnCloseswf() 
{
	// TODO: Add your control notification handler code here
	m_ShockwaveFlash.SetFrameNum(0);
	m_ShockwaveFlash.StopPlay();
	//m_ShockwaveFlash.Rewind();//���������ص�ӰƬ�ĵ�һ֡����ֹͣ����
	//m_ShockwaveFlash.Back();//ӰƬ����һ֡������ֹͣ����
}

void CMFCDlg::OnPlayswf2() 
{
	// TODO: Add your control notification handler code here
	m_ShockwaveFlash.SetLoop(TRUE);//����Ϊѭ������
	m_ShockwaveFlash.SetWMode("TRANSPARENT");//����͸������ģʽ�����ӰƬ����͸����Ƭ�Σ��ŵ�����ʱ���Ϳ��Կ����ؼ�����ı���
	m_ShockwaveFlash.Play();
}
