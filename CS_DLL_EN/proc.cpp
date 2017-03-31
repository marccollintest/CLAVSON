#include <stdafx.h>

#define XP_NOERROR              0
#define XP_ERROR                1
#define MAXCOLNAME				25
#define MAXNAME					25
#define MAXTEXT					255

#ifdef __cplusplus
extern "C" {
#endif

RETCODE __declspec(dllexport) xp_proc(SRV_PROC *srvproc);

#ifdef __cplusplus
}
#endif

RETCODE __declspec(dllexport) xp_proc(SRV_PROC *srvproc)
{

    DBSMALLINT i = 0;
    DBCHAR colname[MAXCOLNAME];
	DBCHAR spName[MAXNAME];
	DBCHAR spText[MAXTEXT];

	// Nom de cette procédure
	_snprintf(spName, MAXNAME, "xp_proc");


	//Envoyer un message texte
	_snprintf(spText, MAXTEXT, "Exemple de procédure stockée étendue %s", spName);
	srv_sendmsg(
		srvproc,
		SRV_MSG_INFO,
		0,
		(DBTINYINT)0,
		(DBTINYINT)0,
		NULL,
		0,
		0,
		spText,
		SRV_NULLTERM);


	//Définir les noms de colonne
    _snprintf(colname, MAXCOLNAME, "ID");
    srv_describe(srvproc, 1, colname, SRV_NULLTERM, SRVINT2, sizeof(DBSMALLINT), SRVINT2, sizeof(DBSMALLINT), 0);

    _snprintf(colname, MAXCOLNAME, "spName");
    srv_describe(srvproc, 2, colname, SRV_NULLTERM, SRVCHAR, MAXNAME, SRVCHAR, 0, NULL);

    _snprintf(colname, MAXTEXT, "Texte");
    srv_describe(srvproc, 3, colname, SRV_NULLTERM, SRVCHAR, MAXTEXT, SRVCHAR, 0, NULL);


	// Met à jour le champ 2 "spName", même valeur pour toutes les lignes
    srv_setcoldata(srvproc, 2, spName);
    srv_setcollen(srvproc, 2, static_cast<int>(strlen(spName)));


	// Envoie plusieurs lignes de données
    for (i = 0; i < 3; i++) {

		// Met à jour le champ 1 "ID"
		srv_setcoldata(srvproc, 1, &i);

		// Met à jour le champ 3 "Texte"
		_snprintf(spText, MAXTEXT, "%d) Exemple de jeu de lignes généré par la procédure stockée étendue %s", i, spName);

		srv_setcoldata(srvproc, 3, spText);
        srv_setcollen(srvproc, 3, static_cast<int>(strlen(spText)));

		// Envoie l'intégralité de la ligne
        srv_sendrow(srvproc);
    }

  
	// Retourne maintenant le nombre de lignes traitées
	srv_senddone(srvproc, SRV_DONE_MORE | SRV_DONE_COUNT, (DBUSMALLINT)0, (DBINT)i);

	return XP_NOERROR ;
}

