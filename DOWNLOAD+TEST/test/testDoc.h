// testDoc.h : interface de la classe CtestDoc
//


#pragma once

class CtestDoc : public CDocument
{
protected: // cr�ation � partir de la s�rialisation uniquement
	CtestDoc();
	DECLARE_DYNCREATE(CtestDoc)

// Attributs
public:

// Op�rations
public:

// Substitutions
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Impl�mentation
public:
	virtual ~CtestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions g�n�r�es de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
};


