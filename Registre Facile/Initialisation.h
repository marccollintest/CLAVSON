//Fichier : Initialisation.h
//Date : 21/08/2003
//Créateur : Shell
//Commentaires : Fichier contenant les fonctions d'initialisations, qui vont permettre
//				 d'initialiser les composants du programme aux valeurs souhaités (ComboBox & OptionButton)



//Définition des prototypes des fonctions
bool InitComboType(HWND hCombo, char *TabVal[], unsigned int TabSize, unsigned int InitComboElt);
bool InitRadioButton(HWND hButton);




bool InitComboType(HWND hCombo, char *TabVal[], unsigned int TabSize, unsigned int InitComboElt=-1)
{
	unsigned int i;
	
	for(i=0;i<TabSize;i++)
		SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM) (LPCSTR) TabVal[i]);
	
	SendMessage(hCombo, CB_SETCURSEL, (WPARAM) InitComboElt , NULL);

	return true;
}