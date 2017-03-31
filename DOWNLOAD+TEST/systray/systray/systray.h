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
#ifndef SYSTRAY_HEADER  // Éviter les intrusions multiples ...
#define SYSTRAY_HEADER

#include <windows.h>
#include <string.h>

// Message qui sera envoyé à la fenêtre ...
#ifndef WM_SYSTRAYMSG
 #define WM_SYSTRAYMSG (13524)
#endif

class SysTray
{

	private:

		HWND  h_Handle;  // Handle de l'objet auquel on attribut l'icone
		char  c_Tip[64];  // ToolTipText (Bulle d'aide)
		NOTIFYICONDATA nid;
		int SysTray_ID;  // Identificateur de l'icon dans le systray

	public:

		SysTray();  // créateur
		~SysTray();  // destructeur

		int AddIcon(const char *path);  // Ajouter une icone dans le systray
		int RemoveIcon();  // Enlever une icone du systray
		int ModifyIcon(const char *path);  // Modifier l'icone du systray

	public:

		void Handle(HWND hWnd);  // Handle de l'objet auquel on attribut l'icone
		HWND Handle();  // Même chose ...

		void Tip(const char *tip);  // ToolTipText (Bulle d'aide)
		char* Tip();  // ...

		void Id(const int id);  // Identificateur ...
		int Id();  // ...

};

#endif
