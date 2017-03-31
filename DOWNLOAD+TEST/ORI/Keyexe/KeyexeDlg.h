// KeyexeDlg.h : header file
//
//	Disclaimer
//	----------
//	THIS SOFTWARE AND THE ACCOMPANYING FILES ARE DISTRIBUTED "AS IS" AND WITHOUT
//	ANY WARRANTIES WHETHER EXPRESSED OR IMPLIED. NO REPONSIBILITIES FOR POSSIBLE
//	DAMAGES OR EVEN FUNCTIONALITY CAN BE TAKEN. THE USER MUST ASSUME THE ENTIRE
//	RISK OF USING THIS SOFTWARE.
//
//	Terms of use
//	------------
//	THIS SOFTWARE IS FREE FOR PERSONAL USE OR FREEWARE APPLICATIONS.
//	IF YOU USE THIS SOFTWARE IN COMMERCIAL OR SHAREWARE APPLICATIONS YOU
//	ARE GENTLY ASKED TO SEND ONE LICENCED COPY OF YOUR APPLICATION(S)
//	TO THE AUTHOR. IF YOU WANT TO PAY SOME MONEY INSTEAD, CONTACT ME BY
//	EMAIL. YOU ARE REQUESTED TO CONTACT ME BEFORE USING THIS SOFTWARE
//	IN YOUR SHAREWARE/COMMERCIAL APPLICATION.
//
//	Contact info:
//	Site: http://bizkerala.hypermart.net
//	Email: anoopt@gmx.net
//----------------------------------------------------------------------------------
//
//	Usage Instructions: See Readme.txt for Both 'Keyexe' & 'Keydll3' projects.
//
//----------------------------------------------------------------------------------
#if !defined(AFX_KEYEXEDLG_H__B3F7C9DA_EBA6_4D11_9E8F_5DF9697FE4B0__INCLUDED_)
#define AFX_KEYEXEDLG_H__B3F7C9DA_EBA6_4D11_9E8F_5DF9697FE4B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKeyexeDlg dialog

class CKeyexeDlg : public CDialog
{
// Construction
public:
	afx_msg LRESULT processkey(WPARAM w,LPARAM l);//Keystroke message handler
	CKeyexeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKeyexeDlg)
	enum { IDD = IDD_KEYEXE_DIALOG };
	CButton	m_hook;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyexeDlg)
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
	bool bShift;

	// Generated message map functions
	//{{AFX_MSG(CKeyexeDlg)
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

#endif // !defined(AFX_KEYEXEDLG_H__B3F7C9DA_EBA6_4D11_9E8F_5DF9697FE4B0__INCLUDED_)
