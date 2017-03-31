//Programme : ClassRegistre


#include <windows.h>
#include "resource.h"

#include "initialisation.h"
#include "registre.h"



//Prototype des fonctions utilisées pour les accès a la base de registre
void OpenKey(char *lBase, char *lChemin, char *lNom);
void ChangeVal(char *lBase, char * lChemin, char *lNom, char *lVal, char *lType);
void CreateOpenKey(char *lBase, char *lChemin);
void AddValue(char *lBase, char *lChemin, char *lNom, char *lNewVal, char *lType);
void DelKey(char *lBase, char *lChemin);
void DelValue(char *lBase, char *lChemin, char *lNom);


HINSTANCE	hinst;
HWND		hDlg,
			hValeur, 
			hBase, hChemin, hNom, hNewVal, hRegType,
			hBase2, hChemin2, hNom2, hNewVal2, hRegType2;


LRESULT CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int nShowCmd)


{
 	// TODO: Place code here.
		
	hinst = hInstance;

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC) DlgProc); //Permet de charger la fenetre ou se trouve les controls ( graphique )

	return 0;

}

LRESULT CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char *tBase = new char[50];
	char *tChemin = new char[500];
	char *tNom = new char[50];
	char *tVal = new char[50];
	char *tType = new char[50];
	
	char *TabType[] = {"REG_NONE","REG_SZ","REG_BINARY","REG_DWORD",
					  "REG_DWORD_BIG_ENDIAN","REG_LINK","REG_MULTI_SZ"};

	char *TabBase[] = {"HKEY_CURRENT_USER","HKEY_USERS","HKEY_LOCAL_MACHINE",
					   "HKEY_CURRENT_CONFIG","HKEY_CLASSES_ROOT","HKEY_DYN_DATA"};

	switch(msg)
	{
	case WM_INITDIALOG:
		hDlg = hwnd;
		SetClassLong(hwnd, GCL_HICON, (LONG) LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON1))); //Permet de charger l'icone 
		
		hValeur = GetDlgItem(hwnd,IDC_VALEUR);

		hBase = GetDlgItem(hwnd,IDC_BASE);
		hChemin = GetDlgItem(hwnd,IDC_CHEMIN);
		hNom = GetDlgItem(hwnd,IDC_NOM);
		hNewVal = GetDlgItem(hwnd,IDC_NVAL);
		hRegType = GetDlgItem(hwnd,IDC_REGTYPE);
		
		hBase2 = GetDlgItem(hwnd,IDC_BASE2);
		hChemin2 = GetDlgItem(hwnd,IDC_CHEMIN2);
		hNom2 = GetDlgItem(hwnd,IDC_NOM2);
		hNewVal2 = GetDlgItem(hwnd,IDC_NVAL2);
		hRegType2 = GetDlgItem(hwnd,IDC_REGTYPE2);
		

		InitComboType(hBase,TabBase, 6,0);

		InitComboType(hBase2,TabBase, 6, 0);

		InitComboType(hRegType,TabType, 7, 0);
		
		InitComboType(hRegType2,TabType, 7, 0);

		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_OUVRIRCLE:;
			GetWindowText(hBase,tBase,50);
			GetWindowText(hChemin,tChemin,500);
			GetWindowText(hNom,tNom,50);

			OpenKey(tBase,tChemin,tNom);
			break;
		
		case IDC_MODIFIERVAL:
			GetWindowText(hBase,tBase,50);
			GetWindowText(hChemin,tChemin,500);
			GetWindowText(hNom,tNom,50);
			GetWindowText(hNewVal,tVal,50);
			GetWindowText(hRegType,tType,50);
			
			ChangeVal(tBase,tChemin,tNom,tVal,tType);
			break;

		case IDC_CREERCLE:
			GetWindowText(hBase2,tBase,50);
			GetWindowText(hChemin2,tChemin,500);
			
			CreateOpenKey(tBase,tChemin);
			break;

		case IDC_AJOUTERVAL:
			GetWindowText(hBase2,tBase,50);
			GetWindowText(hChemin2,tChemin,500);
			GetWindowText(hNom2,tNom,50);
			GetWindowText(hNewVal2,tVal,50);
			GetWindowText(hRegType2,tType,50);
			
			AddValue(tBase,tChemin,tNom,tVal,tType);
			break;

		case IDC_SUPRCLE:
			GetWindowText(hBase2,tBase,50);
			GetWindowText(hChemin2,tChemin,500);

			DelKey(tBase,tChemin);
			break;

		case IDC_SUPRVALEUR:
			GetWindowText(hBase2,tBase,50);
			GetWindowText(hChemin2,tChemin,500);
			GetWindowText(hNom2,tNom,50);	

			DelValue(tBase,tChemin,tNom);
			break;

		}
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	default:
		return(FALSE);

	}

	return(TRUE);

}


//Dans cette partie du code il y a les fonctions et procédures dont on va se servir
//Je les ai crée dans le cadre de mon programme, mais elle ne change en rien l'utilisation
//de la class... Tout ca pour dire que tout le code exterieurs a la classe n'est la qu'à
//titre d'exemple d'utilisation de la class... Il se peut donc que pour certains d'entre vous
//tout se code parraissent "illisible" !!!


void OpenKey(char *lBase, char *lChemin, char *lNom)
{
	HKEY hCle = 0;
	Registre t;
	char *valeur = new char;
	bool resultat;

	if(t.OuvrirCle(lBase, lChemin, &hCle)) 
	{	
		valeur = t.LireValeur(hCle,lNom,&resultat);
		if(resultat)
			SetWindowText(hValeur,valeur);
		t.FermerCle(hCle);
	}
}

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
			MessageBox(hDlg,"La clé indiquée n'est pas valide! Veuillez verifier le nom avant de poursuivre!","Registre", MB_OK | MB_ICONSTOP);
		t.FermerCle(hCle);
	}
	else
		MessageBox(hDlg,"La clé indiquée n'est pas valide! Veuillez verifier les chemins et base avant de poursuivre!","Registre", MB_OK | MB_ICONSTOP);	
}

void CreateOpenKey(char *lBase, char *lChemin)
{
	HKEY hCle=0;
	Registre t;

	t.CreerCle(lBase,lChemin,&hCle);

}

void AddValue(char *lBase, char *lChemin, char *lNom, char *lNewVal, char *lType)
{
	HKEY hCle=0;
	Registre t;
	bool resultat;
	
	t.GestionErreur = false;

	if(t.OuvrirCle(lBase, lChemin, &hCle))
	{	
		t.LireValeur(hCle,lNom,&resultat);
		if(!resultat)
			t.EcrireValeur(hCle,lNom,lNewVal,lType);
		else
			MessageBox(hDlg,"La valeur indiquée existe déjà! Veuillez choisir un nom différent avant de poursuivre!","Registre", MB_OK | MB_ICONSTOP);
		t.FermerCle(hCle);
	}
	else
		MessageBox(hDlg,"La clé indiquée n'est pas valide! Veuillez verifier les chemins et base avant de poursuivre!","Registre", MB_OK | MB_ICONSTOP);	

}

void DelKey(char *lBase, char *lChemin)
{
	Registre t;

	t.SupprimerCle(lBase,lChemin);
}

void DelValue(char *lBase, char *lChemin, char *lNom)
{
	Registre t;

	t.SupprimerValeur(lBase,lChemin,lNom);
}