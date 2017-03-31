=================================================================================================
    BIBLIOTH�QUE MICROSOFT FOUNDATION CLASS : Vue d'ensemble du projet test
=================================================================================================

AppWizard a cr�� cette application test � votre attention. Cette application
explique les principes fondamentaux de l'utilisation des classes MFC (Microsoft Foundation Class)
et constitue �galement un point de d�part pour �crire votre propre application.

Ce fichier fait la synth�se des diff�rents �l�ments contenus dans chacun des fichiers qui constituent
votre application test.

test.vcproj
    Il s'agit du fichier projet principal pour les projets VC++ g�n�r�s � l'aide d'un Assistant Application.
    Ce fichier contient des informations sur la version de Visual C++ qui a �t� utilis�e pour g�n�rer
    le fichier ainsi que des informations relatives aux plates-formes, configurations et fonctionnalit�s
    s�lectionn�es dans l'Assistant Application.

test.h
    Il s'agit du fichier d'en-t�te principal pour l'application. Il comporte
    d'autres en-t�tes de projet sp�cifiques (notamment Resource.h) et d�clare la
    classe d'application CtestApp.

test.cpp
    Il s'agit du fichier source principal pour l'application. Il contient la classe
    d'application CtestApp.

test.rc
    Ce fichier dresse la liste de toutes les ressources Microsoft Windows utilis�es
    par le programme, telles que les ic�nes, bitmaps et curseurs qui sont stock�s
    dans le sous-r�pertoire RES. Vous pouvez modifier ce fichier directement dans Microsoft
    Visual C++. Vos ressources projet se trouvent dans 1036.

res\test.ico
    Il s'agit du fichier ic�ne utilis� en tant qu'ic�ne de l'application. Cette ic�ne
    est incluse dans le fichier de ressources principal test.rc.

res\test.rc2
    Ce fichier contient les ressources qui ne sont pas modifi�es par Microsoft 
    Visual C++. Vous devez y placer toutes les ressources non modifiables par
    l'�diteur de ressources.
/////////////////////////////////////////////////////////////////////////////

Pour la fen�tre frame principale :
    Le projet a une interface MFC standard.
MainFrm.h, MainFrm.cpp
    Ces fichiers contiennent la classe de frames CMainFrame, d�riv�e de
    CMDIFrameWnd et qui contr�le toutes les fonctionnalit�s des frames MDI.
res\Toolbar.bmp
    Ce fichier bitmap permet de cr�er des images en mosa�que pour la barre d'outils.
    La barre d'outils et la barre d'�tat initiales sont cr��es dans la classe CMainFrame.
    �ditez cette bitmap de barre d'outils dans l'�diteur de ressources, puis
    mettez � jour le tableau IDR_MAINFRAME TOOLBAR dans test.rc pour ajouter
    des boutons de barre d'outils.
/////////////////////////////////////////////////////////////////////////////

Pour la fen�tre frame enfant :

ChildFrm.h, ChildFrm.cpp
    Ces fichiers d�finissent et impl�mentent la classe CChildFrame, qui
    prend en charge les fen�tres enfants dans une application MDI.

/////////////////////////////////////////////////////////////////////////////

AppWizard cr�e un type de document et une vue :

testDoc.h, testDoc.cpp - le document
    Ces fichiers contiennent votre classe CtestDoc. �ditez-les pour ajouter vos
    propres donn�es de document et pour impl�menter l'enregistrement et le chargement de fichier
    (via CtestDoc::Serialize).
testView.h, testView.cpp - la vue du document
    Ces fichiers contiennent votre classe CtestView.
    Les objets CtestView servent � afficher les objets CtestDoc.
res\testDoc.ico
    Il s'agit du fichier ic�ne utilis� en tant qu'ic�ne des fen�tres enfants MDI
    pour la classe CtestDoc. Cette ic�ne est incluse dans le fichier de
    ressources principal test.rc.
/////////////////////////////////////////////////////////////////////////////

Autres fonctionnalit�s :

Contr�les ActiveX
    L'application offre la prise en charge des contr�les ActiveX.

Prise en charge de l'aper�u avant impression et de l'impression
    AppWizard a g�n�r� le code requis pour g�rer les commandes Impression, Configuration de l'impression et
    Aper�u avant impression en appelant des fonctions membres de la classe CView � partir de la biblioth�que MFC.
/////////////////////////////////////////////////////////////////////////////

Autres fichiers standard :

StdAfx.h, StdAfx.cpp
    Ces fichiers servent � g�n�rer un fichier d'en-t�te pr�compil� (PCH),
    appel� test.pch, et un fichier de types pr�compil�s StdAfx.obj.

Resource.h
    Il s'agit du fichier d'en-t�te standard, qui d�finit les ID des nouvelles ressources.
    Ce fichier est lu et mis � jour par Microsoft Visual C++.

/////////////////////////////////////////////////////////////////////////////

Autres remarques :

AppWizard utilise "TODO:" pour vous signaler les parties du code source
que vous devez ajouter ou personnaliser.

Si votre application utilise MFC dans une DLL partag�e et que la langue de cette
application n'est pas la m�me que celle utilis�e par le syst�me d'exploitation, vous
devez copier les ressources localis�es MFC70XXX.DLL correspondantes (situ�es sur le
CD-ROM Microsoft Visual C++ dans le r�pertoire Win\System) dans le r�pertoire system
ou system32 de votre ordinateur, puis renommer MFC70XXX.DLL en MFCLOC.DLL. ("XXX" est
l'abr�viation de la langue. Par exemple, MFC70DEU.DLL contient les ressources en allemand.)
Si vous ne copiez pas la version localis�e des ressources, certains �l�ments d'interface de
votre application seront affich�s dans la langue du syst�me d'exploitation.

/////////////////////////////////////////////////////////////////////////////
