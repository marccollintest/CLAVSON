#include <windows.h>
#include <stdio.h>
#include "systray.h"

#define ID_STATIC1 100  // Identificateur du Static

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

HWND hWnd;  // Handle de la fenêtre ...
SysTray *st;  // D'après vous ?

// Entré du programme ...
int WINAPI WinMain(HINSTANCE FirstInstance, HINSTANCE PrevInstance, LPSTR CmdLine, int CmdShow)
{

MSG msg;
WNDCLASSEX wc;

	// Création de la classe pour la petite fenêtre ...
      wc.hInstance = FirstInstance;  // instance du prog
      wc.lpszClassName = "NitRic_SysTray";  // nom de la classe
      wc.lpfnWndProc = WinProc;  // procedure pour gérer les messages
      wc.style = CS_DBLCLKS;  // style !?
      wc.cbSize = sizeof(WNDCLASSEX);
      wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);  // grosse icone
      wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);  // petite icone
      wc.hCursor = LoadCursor(NULL, IDC_ARROW);  // curseur
      wc.lpszMenuName = NULL;  // un tit menu!?
      wc.cbClsExtra = 0;  // ...
      wc.cbWndExtra = 0;  // ...
      wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);  // couleur de fond de la fenêtre ...

	// enregistre la classe, essaie du moin =P
      if (!RegisterClassEx(&wc))
      {  // erreur :(

            MessageBox(NULL, "Erreur lors de l'enregistrement de la classe.", "Erreur", MB_OK);
            return 0;

      }

	// Crée la fenêtre ...
      hWnd = CreateWindowEx(0, "NitRic_SysTray", "System Tray", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            300, 150, HWND_DESKTOP, NULL, FirstInstance, NULL);

      if (hWnd == NULL)
      {  // Ca na pas fonctionner :(

            MessageBox(NULL, "Erreur lors de la création de la fenêtre.", "Erreur", MB_OK);
            return 0;

      }

	// Crée un static ...
      HWND lblhWnd1 = CreateWindowEx(0, "STATIC", NULL, WS_VISIBLE|WS_CHILD, 10, 10,
            220, 13, hWnd, (HMENU)ID_STATIC1, FirstInstance, NULL);


      if (lblhWnd1 == NULL)
      {  //  Sniff .... :(

            MessageBox(hWnd, "Erreur lors de la création de l'objet Static.", "Erreur", MB_OK);
            return 0;

      }

	// Affiche et met à jour la fenêtre
      ShowWindow(hWnd, SW_SHOW);
      UpdateWindow(hWnd);

      // Change la polices du Label
      SendMessage(lblhWnd1, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));

      // Envoie du texte dans le Label
      SetWindowText(lblhWnd1, "Ho la jolie petite icone dans le system tray! ;)");

	// Met à jour le static ...
      UpdateWindow(lblhWnd1);

	// Création de la petite icone dans le systray !
	st = new SysTray;  // déclare une nouvelle instance de la classe
	st->Handle(hWnd);  // handle de la fenêtre
	st->Id(1979);  // identificateur
	st->Tip("Voilà une jolie icone!\0");  // tooltiptext (bulle d'aide)
	if (st->AddIcon("icon.ico") == FALSE) {  // ajoute l'icone
		// erreur :(
		MessageBox(hWnd, "Erreur lors de la création de l'icon. SysTray", "Error", MB_OK);
	}

      while (GetMessage(&msg, NULL, 0, 0))
      {

            TranslateMessage(&msg);
            DispatchMessage(&msg);

      }

      return msg.wParam;

}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

static mousemove_count = 0;  // compter le nombre de fois que le curseur à bouger au dessus de l'icone ...
char message[50];  // message qui va être affiche dans la barre des titre de la fenêtre ...

      switch (msg)
      {

		case WM_CREATE:  // création de la fenêtre ...
	
			break;

            case WM_DESTROY:  // destruction de la fenêtre

                  PostQuitMessage(0);
                  break;

            case WM_CLOSE:  // fermeture de la fenêtre

			st->RemoveIcon();  //  enlève l'icone du systray
			delete st;  // l'ibère la mémoire ...
                  DestroyWindow(hwnd);  // détruit la fenêtre
                  break;

            case WM_COMMAND:

                  break;

		case WM_SYSTRAYMSG:  // Attention! Attention! Message provenant de notre icone !!!
				if ((UINT)lParam == WM_LBUTTONDOWN) {  // Un clique du boutton gauche
					MessageBox(hWnd, "Bouton gauche.", "Clique", MB_OK);
				}
				else if ((UINT)lParam == WM_RBUTTONDOWN) {  // Un clique du boutton droit
					MessageBox(hWnd, "Bouton droit.", "Clique", MB_OK);
				}
				else if ((UINT)lParam == WM_MBUTTONDOWN) {  // Un clique du boutton du centre
					MessageBox(hWnd, "Bouton du centre.", "Clique", MB_OK);
				}
				else if ((UINT)lParam == WM_MOUSEMOVE) {  // Le curseur à bouger !!!
					mousemove_count++;  // Incrémente le nombre de fois que le curseur à bouger
					sprintf(message, "Mouse Move %d", mousemove_count);  // Copie le tout dans 'message'
					SetWindowText(hWnd, message);  // Et l'affiche dans la barre de titre de la fenêtre
				}
			break;

            default:

                  return DefWindowProc(hwnd, msg, wParam, lParam);
                  break;

      }

      return 0;

}



/**********************************************


			 SysTray



	Créé par NitRic le 21 Décembre 2002

	En cas de problème avec ce code,
	écrivez-moi à:



		NitRic28@Hotmail.com


	Note:

		Ce code à été créé et testé
		avec Microsoft Visual C++ 6
		seulement. Le bon fonctionnement
		de ce code avec d'autres
		compilateurs n'est donc pas
		garantie.



**********************************************/

