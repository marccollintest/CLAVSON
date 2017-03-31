#include "stdafx.h"
#include "CS_EXE.h"
#include "CS_EXEDlg.h"
#include "..\CS_DLL\CS_DLL.h"//Include this for functions in the DLL.
#include <MMSystem.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



#define WM_KEYSTROKE (WM_USER + 755)//This message is recieved when key is down/up
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
// CCS_EXEDlg dialog

CCS_EXEDlg::CCS_EXEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCS_EXEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCS_EXEDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hooked = false;// Initialize all members here.
//	AjouterIcone((HWND)pParent,false);
}

void CCS_EXEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCS_EXEDlg)
	DDX_Control(pDX, IDOK, m_hook);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCS_EXEDlg, CDialog)
	//{{AFX_MSG_MAP(CCS_EXEDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnHook)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCS_EXEDlg message handlers

BOOL CCS_EXEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
//	AjouterIcone(((HWND)this->m_pParentWnd),false);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCS_EXEDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCS_EXEDlg::OnPaint() 
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
HCURSOR CCS_EXEDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCS_EXEDlg::OnHook()//Install or Remove keyboard Hook.
{
	// TODO: Add your control notification handler code here
	if(hooked==true)
	{
		PlayResource("BYE");
		removehook();
		hooked = false;
		m_hook.SetWindowText("Activer");
	}
	else
	{
		installhook(this->GetSafeHwnd());
		hooked = true;
		m_hook.SetWindowText("Désactiver");
		PlayResource("OK");
	}
	
}

void CCS_EXEDlg::OnCancel() //On exit, do cleanup(Close files, remove hook.).
{
	// TODO: Add extra cleanup here
	if(hooked==true)
	{
		removehook();
	}

	CDialog::OnCancel();
}

//====================================================
