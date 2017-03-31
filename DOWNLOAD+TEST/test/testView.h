// testView.h : interface de la classe CtestView
//


#pragma once


class CtestView : public CView
{
protected: // création à partir de la sérialisation uniquement
	CtestView();
	DECLARE_DYNCREATE(CtestView)

// Attributs
public:
	CtestDoc* GetDocument() const;

// Opérations
public:

// Substitutions
	public:
	virtual void OnDraw(CDC* pDC);  // substitué pour dessiner cette vue
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implémentation
public:
	virtual ~CtestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // version de débogage dans testView.cpp
inline CtestDoc* CtestView::GetDocument() const
   { return reinterpret_cast<CtestDoc*>(m_pDocument); }
#endif

