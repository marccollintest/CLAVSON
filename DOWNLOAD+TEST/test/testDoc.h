// testDoc.h : interface de la classe CtestDoc
//


#pragma once

class CtestDoc : public CDocument
{
protected: // création à partir de la sérialisation uniquement
	CtestDoc();
	DECLARE_DYNCREATE(CtestDoc)

// Attributs
public:

// Opérations
public:

// Substitutions
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implémentation
public:
	virtual ~CtestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
};


