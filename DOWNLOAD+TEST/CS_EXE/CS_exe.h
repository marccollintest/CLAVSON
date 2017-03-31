#if !defined(AFX_CS_EXE_H__BBACFDD1_07F3_46EE_A2CA_1D3E6D61A28A__INCLUDED_)
#define AFX_CS_EXE_H__BBACFDD1_07F3_46EE_A2CA_1D3E6D61A28A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCS_EXEApp:
// See CS_EXE.cpp for the implementation of this class
//

class CCS_EXEApp : public CWinApp
{
public:
	CCS_EXEApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCS_EXEApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCS_EXEApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CS_EXE_H__BBACFDD1_07F3_46EE_A2CA_1D3E6D61A28A__INCLUDED_)
