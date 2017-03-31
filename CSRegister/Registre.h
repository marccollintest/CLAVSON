/****
 * Class : Registre
 * Auteur: Shell
 * Date : 24/08/2004
 * Commentaires : Cette page de code contient la "class" permettant l'edition de la base de registre
 ***/

#include "RegistreErreur.h"

class Registre
{
	int returnValue;
	DWORD dwLen;
	LPBYTE dwKeyEn;
	
	HKEY ChoisirBase(char *base);
	unsigned long ChoisirType(char *type);
	

public:
	Registre();
	~Registre();

	bool GestionErreur;
	
	bool OuvrirCle(char *base, char *chemin, HKEY *hCle);
	char *LireValeur(HKEY hCle, char *nom, bool *OpRes);
	bool EcrireValeur(HKEY hCle, char *nom, char *valeur, char *type);
	bool CreerCle(char *base, char *chemin, HKEY *hCle);
	bool SupprimerCle(char *base, char *chemin);
	bool SupprimerValeur(char *base, char *chemin, char *nom);
	bool FermerCle(HKEY hCle);
		
};


Registre::Registre()
{
	dwKeyEn = NULL;
	dwLen = 0;
}

Registre::~Registre()
{
	delete dwKeyEn;
}

HKEY Registre::ChoisirBase(char *base)
{
	HKEY tBase=0;
	
	if(strcmp(base,"HKEY_CURRENT_USER")==0)
		tBase = HKEY_CURRENT_USER;	
	else if(strcmp(base,"HKEY_USERS")==0)
		tBase = HKEY_USERS;
	else if(strcmp(base,"HKEY_LOCAL_MACHINE")==0)
		tBase = HKEY_LOCAL_MACHINE;
	else if(strcmp(base,"HKEY_CURRENT_CONFIG")==0)
		tBase = HKEY_CURRENT_CONFIG;
	else if(strcmp(base,"HKEY_CLASSES_ROOT")==0)
		tBase = HKEY_CLASSES_ROOT;

	return tBase;
}

unsigned long Registre::ChoisirType(char *type)
{
	unsigned long hResType=0;
	
	if(strcmp(type,"REG_NONE")==0)
		hResType = REG_NONE;	
	else if(strcmp(type,"REG_SZ")==0)
		hResType = REG_SZ;
	else if(strcmp(type,"REG_BINARY")==0)
		hResType = REG_BINARY;
	else if(strcmp(type,"REG_DWORD")==0)
		hResType = REG_DWORD;
	else if(strcmp(type,"REG_DWORD_BIG_ENDIAN")==0)
		hResType = REG_DWORD_BIG_ENDIAN;
	else if(strcmp(type,"REG_LINK")==0)
		hResType = REG_LINK;
	else if(strcmp(type,"REG_MULTI_SZ")==0)
		hResType = REG_MULTI_SZ;

	return hResType;
}

bool Registre::OuvrirCle(char *base, char *chemin, HKEY *hCle)
{
	HKEY hTempCle=0;

	//Ouvre la clef ou se trouve la valeur
	returnValue = RegOpenKey(ChoisirBase(base), chemin, &hTempCle);
    if (returnValue != ERROR_SUCCESS)
    {
		if(GestionErreur)
			OnRegError(ERR_CLECHEMIN);
		return false;
	}
	
	*hCle = hTempCle;
	
	return 	true;
}

char *Registre::LireValeur(HKEY hCle, char *nom, bool *OpRes)
{
	
	//On recupere la taille de la clé dans un premier temps pour connaitre la taille du buffer que l'on va devoir spécifié
	returnValue = RegQueryValueEx(hCle, nom, NULL, NULL, NULL, &dwLen);
	//On alloue la taille nécéssaire pour éviter les dépassement de caaciter qui risqueraient décrassé d'aure varaible de la mémoire
    dwKeyEn = new BYTE[dwLen];
	//Maintenant on lit la valeur de la clé en spécifiant la taille du buffer
	returnValue = RegQueryValueEx(hCle, nom, NULL, NULL, dwKeyEn, &dwLen);

	if(returnValue != ERROR_SUCCESS)
    {
		*OpRes = false;
		if(GestionErreur)
			OnRegError(ERR_NOM);
		return "Erreur!";
	}
	*OpRes = true;
	return (char*)dwKeyEn; //on retourne le résultat a l'aide d'un CAST
}

bool Registre::EcrireValeur(HKEY hCle, char *nom, char *valeur, char *type)
{
	returnValue = RegSetValueEx(hCle,nom,NULL,ChoisirType(type),(PBYTE)valeur,strlen(valeur));
	if(returnValue != ERROR_SUCCESS)
    {
		if(GestionErreur)
			OnRegError(ERR_ECRIRE);
		return false;
	}

	return true;
}

bool Registre::CreerCle(char *base, char *chemin, HKEY *hCle)
{
	HKEY hTempCle=0;
	
	returnValue = RegCreateKey(ChoisirBase(base),chemin,&hTempCle);
	if(returnValue != ERROR_SUCCESS)
    {
		if(GestionErreur)
			OnRegError(ERR_CREERCLE);
		return false;
	}
	
	*hCle = hTempCle;

	return true;
}

bool Registre::SupprimerCle(char *base, char *chemin)
{
	returnValue = RegDeleteKey(ChoisirBase(base),chemin);
	if(returnValue != ERROR_SUCCESS)
    {
		if(GestionErreur)
			OnRegError(ERR_SUPRCLE);
		return false;
	}
	return true;
}

bool Registre::SupprimerValeur(char *base, char *chemin, char *nom)
{
	HKEY hTempCle=0;		
	
	if(!OuvrirCle(base,chemin,&hTempCle))
		return false;

	returnValue = RegDeleteValue(hTempCle,nom);
	if(returnValue != ERROR_SUCCESS)
	{
		if(GestionErreur)
			OnRegError(ERR_SUPRVAL);
		return false;
	}

	return true;
}

bool Registre::FermerCle(HKEY hCle)
{
	returnValue = RegCloseKey(hCle);
	if(returnValue != ERROR_SUCCESS)
    {
		if(GestionErreur)
			OnRegError(ERR_FERMER);
		return false;
	}

	return true;
}
