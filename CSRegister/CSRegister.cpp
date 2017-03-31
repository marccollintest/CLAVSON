// CSRegister.cpp : d�finit le point d'entr�e pour l'application.
//

#include "stdafx.h"
#include "CSRegister.h"
#include "Registre.h"
#define MAX_LOADSTRING 100
#define CLE_DEMO "DEMO"

// Variables globales�:
HINSTANCE hInst;								// instance actuelle
TCHAR szTitle[MAX_LOADSTRING];					// Le texte de la barre de titre
TCHAR szWindowClass[MAX_LOADSTRING];			// le nom de la classe de fen�tre principale

// Pr�-d�clarations des fonctions incluses dans ce module de code�:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	Trt_DLG_ENREGISTREMENT(HWND, UINT, WPARAM, LPARAM);

void ChangeVal(char *lBase, char * lChemin, char *lNom, char *lVal, char *lType);
bool controleKey(char* pKey);

HWND		hDlg,
			hValeur;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{

	DialogBox(hInstance, (LPCTSTR)IDD_DLG_ENREGISTREMENT, NULL, (DLGPROC)Trt_DLG_ENREGISTREMENT);

	return 0;
}// WinMain

// Gestionnaire de messages pour la bo�te de dialogue � propos de.
LRESULT CALLBACK Trt_DLG_ENREGISTREMENT(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char tKey[50];

	switch (message)
	{
	case WM_INITDIALOG:
		hDlg = hwnd;
		
		hValeur = GetDlgItem(hwnd,IDC_EDIT_KEY);

		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			if LOWORD(wParam == IDOK)
			{
				GetWindowText(hValeur,tKey,50);
//				MessageBox(hwnd,tKey,"Cl�",MB_OK);
//				openKey("HKEY_LOCAL_MACHINE","SOFTWARE\MCII","CLE");
				if (controleKey(tKey))
				{
					ChangeVal("HKEY_LOCAL_MACHINE","SOFTWARE\\MCII","CLAVSON",tKey,"REG_SZ");
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
				}
				else
				{
					MessageBox(NULL,"D�sol�, mais la cl� fournie n'est pas valide","ClavSon",MB_OK);
					return FALSE;
				}
			}
			else
			{   // CANCEL
				EndDialog(hwnd,0);
				return TRUE;
			}

		}
		break;
	}
	return FALSE;
}//Trt_DLG_ENREGISTREMENT

bool controleKey(char* pKey)
{
	char strbuf[5];
	if (!strncmp(pKey,CLE_DEMO,strlen(CLE_DEMO)))
	{
		return true;
	}
	if (strlen(pKey) != 5)
	{
		return false;
	}
	strncpy(strbuf,pKey,5);
	if (strbuf[2] != 'M')
	{
		return false;
	}
	if (strbuf[4] != 'C')
	{
		return false;
	}

}//controleKey
void ChangeVal(char *lBase, char * lChemin, char *lNom, char *lNewVal, char *lType)
{
	HKEY hCle=0;
	Registre t;
	bool resultat;
	
	t.GestionErreur = false;

	if(t.OuvrirCle(lBase, lChemin, &hCle))
	{	
		t.LireValeur(hCle,lNom,&resultat);
		if(resultat)
			t.EcrireValeur(hCle,lNom,lNewVal,lType);
		else
			MessageBox(hDlg,"Enregistrement impossible, veuillez d�sinstaller et re-installer l'application CAUSE (0002)","Enregistrement", MB_OK | MB_ICONSTOP);
		t.FermerCle(hCle);
	}
	else
		// Le Chemin D'acc�s n'est pas valide HKEY_LOCAL_MACHINE\SOFTWARE\MCII 
		MessageBox(hDlg,"Enregistrement impossible, veuillez d�sinstaller et re-installer l'application CAUSE (0001)","Enregistrement", MB_OK | MB_ICONSTOP);	
}//ChangeVal

