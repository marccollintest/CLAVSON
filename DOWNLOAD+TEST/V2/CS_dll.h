
#ifdef CS_DLL_EXPORTS
#define CS_DLL_API __declspec(dllexport)
#else
#define CS_DLL_API __declspec(dllimport)
#endif

CS_DLL_API void installhook(HWND h);//Installation du Hook.
CS_DLL_API void removehook();//Desinstallation du Hook.
CS_DLL_API LRESULT CALLBACK hookproc(int ncode,WPARAM wparam,LPARAM lparam);//C'est cette fonction qui est appellée quand on utilse le clavier.
LRESULT Processkey(WPARAM w, LPARAM l);//Triatement de la frappe
CS_DLL_API LRESULT PlayResource(LPSTR lpName);
 LRESULT subst(const char *src, const char *dest);