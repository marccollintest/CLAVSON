#include "stdafx.h"
#include "CS_exe.h"
#include "CS_exeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool AjouterIcone (HWND hWnd, bool bOn );
bool EnleverIcone ();
bool MettreTexte (char *texte);
bool AfficherMenu ();

/*** Autres ***/
#define MYWM_NOTIFYICON		(WM_USER+2)

HINSTANCE hInstance;
NOTIFYICONDATA icone;
bool IconeExiste;
POINT position_souris;
HMENU hMenu;
HMENU hMenuPopup;
HWND hDlg;


/////////////////////////////////////////////////////////////////////////////
// CCS_EXEApp

BEGIN_MESSAGE_MAP(CCS_EXEApp, CWinApp)
	//{{AFX_MSG_MAP(CCS_EXEApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCS_EXEApp construction

CCS_EXEApp::CCS_EXEApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCS_EXEApp object

CCS_EXEApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCS_EXEApp initialization

BOOL CCS_EXEApp::InitInstance()
{

//	Enable3dControls();			// Call this when using MFC in a shared DLL

	CCS_EXEDlg dlg;
	m_pMainWnd = &dlg;
	AjouterIcone(NULL  ,false);
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


bool AjouterIcone (HWND hWnd,bool bOn )
{
	int ResShell;
	if (IconeExiste)
	{
		EnleverIcone();
	}
	icone.hWnd = hWnd;

	if (bOn )
	{
		icone.hIcon = LoadIcon((HINSTANCE) GetModuleHandle (NULL), MAKEINTRESOURCE(IDI_ICONE_ON));
	}
	else
	{
		icone.hIcon = LoadIcon((HINSTANCE) GetModuleHandle (NULL), MAKEINTRESOURCE(IDI_ICONE_OFF));
	}

	ResShell = Shell_NotifyIcon(NIM_ADD, &icone);
	if(ResShell)
	{
		IconeExiste = true;
		return true;
	}
	else
		return false;
}//AjouterIcone

bool EnleverIcone ()
{
	int ResShell;
	ResShell = Shell_NotifyIcon(NIM_DELETE, &icone);
	if(ResShell)
	{
		IconeExiste = false;
		return true;
	}
	else
		return false;
}//EnleverIcone
bool AfficherMenu ()
{
	//=============================================================================
	// Affichage et traitement du menu associé à L'icone
	//=============================================================================
	GetCursorPos(&position_souris);
	hMenu = LoadMenu((HINSTANCE) GetModuleHandle (NULL), MAKEINTRESOURCE(IDR_MENU));
	hMenuPopup = GetSubMenu(hMenu, 0);
	if (hMenuPopup == NULL)
	{
		MessageBox(NULL, TEXT("hMenuPopup est NULL"), TEXT("ERREUR"), NULL);
		exit(0);
	}

	SetForegroundWindow(hDlg);	// Permet d'éviter un bug windows : si on ne clique sur aucun choix du menu, il s'en va tout seul

	// On appelle le menu, on demande que la valeur cliquée soit retournée (TPM_RETURNCMD)
	DWORD selection;
	selection = TrackPopupMenu(hMenuPopup, TPM_NONOTIFY|TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RETURNCMD, position_souris.x + 85, position_souris.y - 10, 0, hDlg, NULL);
    // Exemple de menu possible avec cas différents
	switch (selection)
	{
		case ID_ON:
			AjouterIcone(hDlg,true);
			break;
		case ID_OFF:
			AjouterIcone(hDlg,false);
			break;
		case ID_APROPOS_DE:
//			DialogBox((HINSTANCE) GetModuleHandle (NULL), MAKEINTRESOURCE(IDD_ABOUT), NULL, APDDialogProc);
			break;
		case IDCANCEL:
			EnleverIcone();
			DestroyWindow(hDlg);
			PostQuitMessage(0);
			break;
	}

	return true;
}//AfficherMenu


