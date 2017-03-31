#include "stdafx.h"
#include <MMSystem.h>
#include <stdio.h>
#include "CS_dll.h"
#include "resource.h"

#pragma data_seg(".HOOKDATA")//Shared data among all instances.
HHOOK hook = NULL;
HWND hwnd = NULL;
bool bShift = false;
char buffer[20];

#pragma data_seg()

#pragma comment(linker, "/SECTION:.HOOKDATA,RWS")//linker directive

HINSTANCE hinstance = NULL;

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
	hook = NULL;

    return TRUE;
}


CS_DLL_API void installhook(HWND h)
{
	hook = NULL;
	hwnd = h;
	hook = SetWindowsHookEx(WH_KEYBOARD,hookproc,hinstance,NULL);
	if(hook==NULL)
		MessageBox(NULL,"Unable to install hook","Error!",MB_OK);
}

CS_DLL_API void removehook()
{
	if (!UnhookWindowsHookEx(hook))
	{
//		MessageBox("Error during unhook");
	}
}

CS_DLL_API LRESULT CALLBACK hookproc(int ncode,WPARAM wparam,LPARAM lparam)
{
	if(ncode>=0)
	{
		//if((lparam & 0x80000000) == 0x00000000)//Check whether key was pressed(not released).
		{
			Processkey(wparam,lparam);//Send info to app Window.
		}
	}
	return ( CallNextHookEx(hook,ncode,wparam,lparam) );//pass control to next hook in the hook chain.
}

LRESULT Processkey(WPARAM w, LPARAM l)//This block processes the keystroke info.
{
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
	}

	
	if((l & 0x80000000) == 0x00000000)//Check whether key was pressed(not released).
	{
		PlayResource(buffer);
	}
	return 0L;
}
/*
LRESULT CKeyexeDlg::processkey(WPARAM w, LPARAM l)//This block processes the keystroke info.
{
	GetKeyNameText(l,buffer,20);
	_strlwr(buffer);
	if(strlen(buffer)>1)
	{
		subst("maj","<SHIFT>");
		subst("maj droite","<SHIFT>");
		subst("tab","<TAB>");
		subst("space"," ");
		subst("backspace","<BACKSPACE>");
		subst("delete","<DEL>");
		subst("left","<LEFT>");
		subst("down","<DOWN>");
		subst("up","<UP>");
		subst("right","<RIGHT>");
		subst("num /","/");
		subst("num *","*");
		subst("num -","-");
		subst("maj droite&","1");
		subst("num 0","0");
		subst("num 1","1");
		subst("num 2","2");
		subst("num 3","3");
		subst("num 4","4");
		subst("num 5","5");
		subst("num 6","6");
		subst("num 7","7");
		subst("num 8","8");
		subst("num 9","9");
		subst("num +","+");
		subst("num enter","<ENTER>");
		subst("num del","<DEL>");
		subst("esc","<ESC>");
		subst("enter","<ENTER>");
		subst("caps lock","<CAPSLOCK>");
		subst("num lock","<NUMLOCK>");
		subst("scroll lock","<SCROLLLOCK>");
		subst("ctrl","<CTRL>");
		subst("alt","<ALT>");
		subst("right ctrl","<CTRL>");
		subst("right alt","<ALT>");
		subst("pause","<PAUSE>");
		subst("insert","<INSERT>");
		subst("home","<HOME>");
		subst("end","<END>");
		subst("page up","<PGUP>");
		subst("page down","<PGDN>");
		subst("f1","<F1>");
		subst("f2","<F2>");
		subst("f3","<F3>");
		subst("f4","<F4>");
		subst("f5","<F5>");
		subst("f6","<F6>");
		subst("f7","<F7>");
		subst("f8","<F8>");
		subst("f9","<F9>");
		subst("f10","<F10>");
		subst("f11","<F11>");
		subst("f12","<F12>");
	}
	if (strcmp(buffer,"<SHIFT>")==0)
	{
		bShift = !bShift;
	}

	if (bShift)
	{
		subst("&","1");
		subst("é","2");
		subst("\"","3");
		subst("'","4");
		subst("(","5");
		subst("-","6");
		subst("è","7");
		subst("_","8");
		subst("ç","9");
		subst("à","0");
	}

	if (strcmp(buffer,"<SHIFT>")!=0)
	{

		diskfile->Write(buffer,strlen(buffer));
		if(keycount>50)
		{
			diskfile->Flush();
			keycount = 0;
		}
	}
	return 0L;
}
*/
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
