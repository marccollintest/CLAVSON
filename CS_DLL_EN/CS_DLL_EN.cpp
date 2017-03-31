#include "windows.h"
#include <MMSystem.h>
#include <stdio.h>
#include "../CS_DLL_EN/CS_DLL_EN.h"
#include "resource.h"

#define NBREMAX_FRAPPES 20
#define CLE_DEMO "DEMO"

#pragma data_seg(".HOOKDATA")//Shared data among all instances.
//HHOOK hook = NULL;
HWND hwnd = NULL;
bool bShift = false;
char buffer[20];//To hold keystroke info.
int nNbrefrappes = 0;
bool bDemo = false;

#pragma data_seg()

#pragma comment(linker, "/SECTION:.HOOKDATA,RWS")//linker directive

HINSTANCE hinstance = NULL;
HHOOK hook = NULL;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }

	hinstance = (HINSTANCE)hModule;
//	hook = NULL;

    return TRUE;
}


CS_DLL_API void installhook(HWND h,char* key)
{
	hook = NULL;
	hwnd = h;
	hook = SetWindowsHookEx(WH_KEYBOARD,hookproc,hinstance,NULL);
	if(hook==NULL)
		MessageBox(NULL,"Unable to install hook","Error!",MB_OK);

	if (!strncmp(key,CLE_DEMO,strlen(CLE_DEMO)))
	{
		bDemo = true;
		nNbrefrappes = 0;
	}
	else
	{
		bDemo = false;
	}

}

CS_DLL_API void removehook()
{
	if (hook!=NULL)
	{
		if (!UnhookWindowsHookEx(hook))
		{
//			MessageBox(NULL,"Unable to Desinstall hook","Error!",MB_OK);
		}
	}
}

CS_DLL_API LRESULT CALLBACK hookproc(int ncode,WPARAM wparam,LPARAM lparam)
{
	if(ncode>=0)
	{
		//if((lparam & 0x80000000) == 0x00000000)//Check whether key was pressed(not released).
		{
			TraitelaCle(wparam,lparam);//Send info to app Window.
		}
	}
	return ( CallNextHookEx(hook,ncode,wparam,lparam) );//pass control to next hook in the hook chain.
}


LRESULT TraitelaCle(WPARAM w, LPARAM l)
//======================================================
// C'est ici que ça se passe !!!!
//========================================================

{

	// Contrôle de la Clé pour Désactiver la démonstration
	char strBuffer[50];
	if (bDemo)
	{
		// Désactivation de clavson au bout d'un certain nombre de frappes
		nNbrefrappes++;
		sprintf(strBuffer,"%d",nNbrefrappes);
//		MessageBox(NULL,strBuffer,"Mode Démo",MB_OK);
		if (nNbrefrappes > NBREMAX_FRAPPES)
		{
//			removehook();
			SendMessage(hwnd,WM_SETICON,WM_SETICON,102); // on envoie un message Bizzare à l'appli pour lui dire de s'arrêter
			return false;
		}
	}
	GetKeyNameText(l,buffer,20);
	_strlwr(buffer);
	if(strlen(buffer)>1)
	{
		subst("maj","<SHIFT>");
		subst("maj droite","<SHIFT>");
	}
	if (strcmp(buffer,"<SHIFT>")==0)
	{
		bShift = !bShift;
	}

	if (bShift)
	{
		subst("&","UN");
		subst("é","DEUX");
		subst("\"","TROIS");
		subst("'","QUATRE");
		subst("(","CINQ");
		subst("-","SIX");
		subst("è","SEPT");
		subst("_","HUIT");
		subst("ç","NEUF");
		subst("à","ZERO");
		subst("=","PLUS");
		subst(",","PINTERROGATION");
		subst(";","POINT");
		subst(":","SLASH");
		subst("!","RIEN");
	}
	else
	{
		subst("&","RIEN");
		subst("é","ET");
		subst("\"","RIEN");
		subst("'","APOSTROPHE");
		subst("(","RIEN");
		subst("-","MOINS");
		subst("è","EST");
		subst("_","RIEN");
		subst("ç","CC");
		subst("à","A");
		subst("=","EGAL");
		subst(",","VIRGULE");
		subst(".","POINT");
		subst(":","2POINTS");
		subst(";","PVIRGULE");
		subst("/","SLASH");
		subst("!","PEXCLAMATION");
		subst("?","PINTERROGATION");
	}
	subst("ù","U");
	subst("*","ETOILE");
	subst("1 (pave num.)","UN");
	subst("2 (pave num.)","DEUX");
	subst("3 (pave num.)","TROIS");
	subst("4 (pave num.)","QUATRE");
	subst("5 (pave num.)","CINQ");
	subst("6 (pave num.)","SIX");
	subst("7 (pave num.)","SEPT");
	subst("8 (pave num.)","HUIT");
	subst("9 (pave num.)","NEUF");
	subst("0 (pave num.)","ZERO");
	subst(". (pave num.)","POINT");
	subst("+ (pave num.)","PLUS");
	subst("- (pave num.)","MOINS");
	subst("* (pave num.)","ETOILE");
	subst("/ (pave num.)","SLASH");

	subst("espace","ESPACE");
	if (strcmp(buffer,"<SHIFT>")!=0)
	{
		if((l & 0x80000000) == 0x00000000)//Check whether key was pressed(not released).
		{
			//MessageBox(NULL,buffer,"Key",MB_OK);
			PlayResource(buffer);
		}
		return 0L;
	}
	return 0L;
}//TraiteLaCle

CS_DLL_API LRESULT PlayResource(LPSTR lpName) 
{ 
    BOOL bRtn; 
    LPSTR lpRes; 
    HGLOBAL hRes;
	HRSRC  hResInfo;
 
    // Find the WAVE resource. 
 
    hResInfo = FindResource(hinstance, lpName, "WAVE"); 
    if (hResInfo == NULL)
	{
	       return FALSE; 
	}
    // Load the WAVE resource. 
 
    hRes = LoadResource(hinstance, hResInfo); 
    if (hRes == NULL) 
	{
	       return FALSE; 
	}
 
    // Lock the WAVE resource and play it. 
 
    lpRes = (LPSTR)LockResource(hRes); 
    if (lpRes != NULL) { 
        bRtn = sndPlaySound(lpRes, SND_MEMORY | SND_ASYNC); 
        UnlockResource(hRes); 
    } 
    else 
	{
        bRtn = 0; 
	}
 
    // Free the WAVE resource and return success or failure. 
 
    FreeResource(hRes); 
    return bRtn; 
} 
LRESULT subst(const char *src, const char *dest)//Some key substitutions.
{
	if(strcmp(buffer,src)==0)
		strcpy(buffer,dest);
	return 0;
}

