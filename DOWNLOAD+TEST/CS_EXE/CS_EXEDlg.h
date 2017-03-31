#if !defined(AFX_CS_EXEDLG_H__B3F7C9DA_EBA6_4D11_9E8F_5DF9697FE4B0__INCLUDED_)
#define AFX_CS_EXEDLG_H__B3F7C9DA_EBA6_4D11_9E8F_5DF9697FE4B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCS_EXEDlg dialog

class CCS_EXEDlg : public CDialog
{
// Construction
public:
	afx_msg LRESULT processkey(WPARAM w,LPARAM l);//Keystroke message handler
	CCS_EXEDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCS_EXEDlg)
	enum { IDD = IDD_CS_EXE_DIALOG };
	CButton	m_hook;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCS_EXEDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void subst(const char* src, const char* dest);
	HICON m_hIcon;

	bool hooked;//to check whether hook is installed or not.
	CFile* diskfile;//To write keystrokes to disk.
	char buffer[20];//To hold keystroke info.
	UINT keycount;//Used to avoid disk writes for each keystroke.

	// Generated message map functions
	//{{AFX_MSG(CCS_EXEDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHook();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CS_EXEDLG_H__B3F7C9DA_EBA6_4D11_9E8F_5DF9697FE4B0__INCLUDED_)
