/**********************************************


			 SysTray



	Cr�� par NitRic le 21 D�cembre 2002

	En cas de probl�me avec ce code,
	�crivez-moi �:



		NitRic28@Hotmail.com


	Note:

		Ce code � �t� cr�� et test�
		avec Microsoft Visual C++ 6
		seulement. Le bon fonctionnement
		de ce code avec d'autres
		compilateurs n'est donc pas
		garantie.



**********************************************/
#include "systray.h"

SysTray::SysTray(){}  // contructeur ...
SysTray::~SysTray(){}  // destructeur ...

/*************************************/
/*  Ajouter une icone dans           */
/*  le SysTray                       */

/*************************************/
int SysTray::AddIcon(const char *path)
{

BOOL retval = FALSE;  // Valeur de retour
HICON hIcon;  // Handle de l'icone
int len = 0;  // Longeur de la chaine (ToolTipText -> "Bulle d'aide")

	// Charge l'icone
	hIcon = (HICON)LoadImage(NULL, path, IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE,
		LR_DEFAULTSIZE|LR_LOADFROMFILE);

	// Initialise la cr�ation du 'SysTray' ...
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = h_Handle;  // Handle de l'objet qui va recevoir les messages ...
	nid.uCallbackMessage = WM_SYSTRAYMSG;  // Message � envoyer � l'objet ...
	nid.uID = SysTray_ID;  // Identificateur ...
	nid.hIcon = (HICON)hIcon;  // Icone ...
	nid.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;  // Flags(Options) ...

	// Pour le tooltiptext (bulle d'aide)
	len = strlen(c_Tip);
	if (c_Tip) {  // Si des caract�res sont pr�sent dans c_Tip ...
		strncpy(nid.szTip, c_Tip, len);  // L'envoie dans la structure ...
		nid.szTip[len] = 0;  // Ajoute la caract�re null de fin de chaine ...
	}
	else {  // Aucun caract�re alors pas de tooltiptext (bulle d'aide) ...
		nid.szTip[0] = 0;
	}

	// Ajoute l'icone dans le systray
	retval = Shell_NotifyIcon(NIM_ADD, &nid); 
 
	// D�truit l'icone qui � �t� charger en m�moire plus t�t
	if (hIcon) {
		DestroyIcon(hIcon);
	}

	// Renvoie le r�sultat(r�ussite ou �chec)
	return retval;

}

/*************************************/
/*  Enlever l'icone du SysTray       */

/*************************************/
int SysTray::RemoveIcon()

{

BOOL retval = FALSE;  // Valeur de retour
 
	// Enl�ve l'icone du systray ...
	retval = Shell_NotifyIcon(NIM_DELETE, &nid); 
	return retval;   // Renvoie le r�sultat ...

}

/*************************************/
/*  Modifier l'icone du SysTray      */

/*************************************/
int SysTray::ModifyIcon(const char *path)
{

BOOL retval = FALSE;  // Valeur de retour
HICON hIcon;  // Handle de la nouvelle icone ...

	// Charge la nouvelle icone ...
	hIcon = (HICON)LoadImage(NULL, path, IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE,
		LR_DEFAULTSIZE|LR_LOADFROMFILE);

	// L'envoie dans la structure ...
	nid.hIcon = (HICON)hIcon;

	// Modifie l'icone du systray ...
	retval = Shell_NotifyIcon(NIM_MODIFY, &nid);
	
	// Supprime l'icone de la m�moire ...
	if (hIcon) {
		DestroyIcon(hIcon);
	}

	return retval;  // Renvoie le r�sultat (r�ussite ou �chec)

}


/*************************************/
/*  Identificateur                   */

/*************************************/
void SysTray::Id(const int id)
{

	SysTray_ID = id;  // Sp�cifie l'identificateur ...

}

int SysTray::Id()
{

	return SysTray_ID;  // Renvoie l'identificateur ...

}

/*************************************/
/*  Handle de la fen�tre             */
/*  qui va recevoir les messages     */

/*************************************/
void SysTray::Handle(HWND hWnd)
{

	h_Handle = hWnd;  // Sp�cifie le Handle ...

}

HWND SysTray::Handle()
{

	return h_Handle;  // Renvoie le Handle ...

}

/*************************************/
/*  ToolTipText(Bulle d'aide)        */

/*************************************/
void SysTray::Tip(const char *tip)
{

	strncpy(c_Tip, tip, 63);  // Sp�cifie le tooltiptext (bulle d'aide) ...

}

char* SysTray::Tip()
{

	return c_Tip;  // Renvoie le tooltiptext (bulle d'aide) ...

}

