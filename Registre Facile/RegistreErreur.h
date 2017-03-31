//Headers contenant la Gestion des erreurs du aux accès a la base de registre

extern HWND hDlg;

#define ERR_CLECHEMIN	1
#define ERR_NOM			2
#define ERR_FERMER		3
#define ERR_ECRIRE		4
#define ERR_CREERCLE	5
#define ERR_SUPRCLE		6
#define ERR_SUPRVAL		7


void OnRegError(int nError);

typedef struct 
{
	int numero;
	int style;
	char *description;
	
}Erreur;


void OnRegError(int nError)
{
	Erreur * err = new Erreur[sizeof(Erreur)];
	
	switch (nError)
	{
	case ERR_CLECHEMIN:
		err->numero = 1;
		err->description = "La base et le chemin indiqués n'existe pas ou sont inaccessible!";
		err->style = MB_ICONSTOP;
		break;

	case ERR_NOM:
		err->numero = 2;
		err->description = "Le nom indiqué n'existe pas ou est inaccessible!";
		err->style = MB_ICONSTOP;
		break;
	
	case ERR_FERMER:
		err->numero = 3;
		err->description = "La clé n'a pas pu être fermé!";
		err->style = MB_ICONSTOP;
		break;

	case ERR_ECRIRE:
		err->numero = 4;
		err->description = "La nouvelle valeur n'a pas pu être écrite!";
		err->style = MB_ICONSTOP;
		break;
	
	case ERR_CREERCLE:
		err->numero = 5;
		err->description = "Une erreur s'est produite! La clé n'a pas pu être créé!";
		err->style = MB_ICONSTOP;
		break;

	case ERR_SUPRCLE:
		err->numero = 6;
		err->description = "La clé n'a pas pu être supprimé! Veuillez verifier la base et le chemin indiqué!";
		err->style = MB_ICONSTOP;
		break;
	
	case ERR_SUPRVAL:
		err->numero = 7;
		err->description = "La valeur n'a pa pu être supprimé!\nLe nom de la clé indiqué n'existe pas! Veuillez verifier le nom!";
		err->style = MB_ICONSTOP;
	}
	
	MessageBox(hDlg,err->description,"Registre",err->style);
}
