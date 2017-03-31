/***
 *** Projet 76 - WRC
 ***
 *** Version : 0.1
 *** Date de dernière modification : 07/01/2004
 ***
 ***/

/*** Inclusions ***/
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "resource.h"

/*** Prototypes ***/
BOOL CALLBACK DialogProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK APDDialogProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
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

/***[ WinMain ]**********************************************************************************************/

int WINAPI WinMain (HINSTANCE _hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	hInstance = _hInstance;

	// Initialisation de la structure NOTIFYICONDATA
    icone.cbSize = sizeof(icone);						// On alloue la taille nécessaire pour la structure
    icone.uID = IDI_ICONE_ON;							// On lui donne un ID
    icone.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;	// On lui indique les champs valables
	// On lui dit qu'il devra "écouter" son environement (clique de souris, etc)
    icone.uCallbackMessage = MYWM_NOTIFYICON;
    icone.hIcon = LoadIcon(NULL, NULL);					// On ne load aucune icone pour le moment
    icone.szTip[0] = '\0';								// Le tooltip par défaut, soit rien
	IconeExiste = false;								//On dit qu'il n'y a pas d'icone(logique au début de l'appli!)

	hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_CS_EXE_DIALOG), NULL, DialogProc);
    icone.hWnd = hDlg;
	ShowWindow (hDlg, SW_HIDE);
	AjouterIcone(hDlg,true);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (hDlg || IsDialogMessage(hDlg, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

/***[ DialogProc ]**********************************************************************************************/

BOOL CALLBACK DialogProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG :
			SendMessage (hWnd, WM_SETICON, WPARAM (ICON_SMALL), LPARAM (LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICONE_ON))));
			SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
			return TRUE;

		case WM_SYSCOMMAND :
			switch (LOWORD(wParam))
			{
				case SC_MINIMIZE :
					if (IsWindowVisible(hWnd))
						ShowWindow(hWnd, SW_HIDE);
					return TRUE;
			}
			break;

		case WM_COMMAND :
			break;

		case MYWM_NOTIFYICON :
			switch (lParam)
			{
				//case WM_LBUTTONDBLCLK :
				//	if (wParam==IDI_ICONE)
				//	{
				//		if (!IsWindowVisible(hWnd))
				//			ShowWindow(hWnd, SW_NORMAL);
				//		else
				//			ShowWindow(hWnd, SW_HIDE);
				//	}
				//	break;
				case WM_RBUTTONUP :
					if (wParam==IDI_ICONE_ON)
						AfficherMenu();
					return true;
					break;
			}
			break;

	}
	return FALSE;
}

BOOL CALLBACK APDDialogProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG :
			//ID
//			AjouterIcone_on(hWnd);
//			SendMessage (hWnd, WM_SETICON, WPARAM (ICON_SMALL), LPARAM (LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICONE_ON))));
//			return TRUE;

		case WM_COMMAND :
			switch (LOWORD(wParam))
			{
				case IDOK:
					EndDialog(hWnd, 0);
					return TRUE;
			}
			break;
	}
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
