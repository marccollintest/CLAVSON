=========================================================================
    PROC�DURE STOCK�E �TENDUE : vue d'ensemble du projet CS_DLL_EN
========================================================================


AppWizard a cr�� CS_DLL_EN.dll pour vous.  

Ce fichier contient un r�sum� du contenu de chacun des fichiers qui
constituent votre application CS_DLL_EN.

CS_DLL_EN.vcproj
    Il s'agit du fichier projet principal pour les projets VC++ g�n�r�s � l'aide d'un Assistant Application. 
    Il contient les informations sur la version de Visual C++ qui a g�n�r� le fichier et 
    des informations sur les plates-formes, configurations et fonctionnalit�s du projet s�lectionn�es avec
    l'Assistant Application.

CS_DLL_EN.cpp
    Il s'agit du fichier source principal de la DLL.

proc.cpp
    Ce fichier contient la proc�dure stock�e xp_proc

/////////////////////////////////////////////////////////////////////////////
Autres fichiers standard�:

StdAfx.h, StdAfx.cpp
    Ces fichiers sont utilis�s pour g�n�rer un fichier d'en-t�te pr�compil� (PCH) 
    nomm� CS_DLL_EN.pch et un fichier de type pr�compil� nomm� StdAfx.obj.


/////////////////////////////////////////////////////////////////////////////
Autres remarques�:

Apr�s avoir termin� cet Assistant, copiez CS_DLL_EN.dll dans votre r�pertoire 
\Binn SQL Server.

Ajoutez votre nouvelle proc�dure stock�e �tendue � partir d'un projet de donn�es Visual Studio 
ou en utilisant SQL Server Enterprise Manager ou en ex�cutant la commande 
SQL suivante�:
  sp_addextendedproc 'xp_proc', 'CS_DLL_EN.DLL'

Vous pouvez supprimer la proc�dure stock�e �tendue en utilisant la commande SQL�:
  sp_dropextendedproc 'xp_proc'

Vous pouvez lib�rer la DLL du serveur (pour supprimer ou remplacer le fichier), en 
utilisant la commande SQL�:
  DBCC xp_proc(FREE)


/////////////////////////////////////////////////////////////////////////////
