// testDoc.cpp : impl�mentation de la classe CtestDoc
//

#include "stdafx.h"
#include "test.h"

#include "testDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestDoc

IMPLEMENT_DYNCREATE(CtestDoc, CDocument)

BEGIN_MESSAGE_MAP(CtestDoc, CDocument)
END_MESSAGE_MAP()


// construction ou destruction de CtestDoc

CtestDoc::CtestDoc()
{
	// TODO : ajoutez ici le code d'une construction unique

}

CtestDoc::~CtestDoc()
{
}

BOOL CtestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO : ajoutez ici le code de r�initialisation
	// (les documents SDI r�utiliseront ce document)

	return TRUE;
}




// s�rialisation de CtestDoc

void CtestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO�: ajoutez ici le code de stockage
	}
	else
	{
		// TODO�: ajoutez ici le code de chargement
	}
}


// diagnostics pour CtestDoc

#ifdef _DEBUG
void CtestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CtestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// commandes pour CtestDoc
