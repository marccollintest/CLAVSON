// testView.cpp : impl�mentation de la classe CtestView
//

#include "stdafx.h"
#include "test.h"

#include "testDoc.h"
#include "testView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestView

IMPLEMENT_DYNCREATE(CtestView, CView)

BEGIN_MESSAGE_MAP(CtestView, CView)
	// Commandes d'impression standard
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// construction ou destruction�de CtestView

CtestView::CtestView()
{
	// TODO : ajoutez ici le code d'une construction

}

CtestView::~CtestView()
{
}

BOOL CtestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO : Changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// dessin de CtestView

void CtestView::OnDraw(CDC* /*pDC*/)
{
	CtestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO : ajoutez ici le code de dessin pour les donn�es natives
}


// impression de CtestView

BOOL CtestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// pr�paration par d�faut
	return DoPreparePrinting(pInfo);
}

void CtestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO : ajoutez une initialisation suppl�mentaire avant l'impression
}

void CtestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO : ajoutez un nettoyage apr�s l'impression
}


// diagnostics pour CtestView

#ifdef _DEBUG
void CtestView::AssertValid() const
{
	CView::AssertValid();
}

void CtestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestDoc* CtestView::GetDocument() const // la version non d�bogu�e est en ligne
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestDoc)));
	return (CtestDoc*)m_pDocument;
}
#endif //_DEBUG


// gestionnaires de messages pour CtestView
