// test.h : fichier d'en-tête principal pour l'application test
//
#pragma once

#ifndef __AFXWIN_H__
	#error inclut 'stdafx.h' avant d'inclure ce fichier pour PCH
#endif

#include "resource.h"       // symboles principaux


// CtestApp :
// Consultez test.cpp pour l'implémentation de cette classe
//

class CtestApp : public CWinApp
{
public:
	CtestApp();


// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CtestApp theApp;
