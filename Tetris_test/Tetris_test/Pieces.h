#pragma once
#include <windows.h>

class Piece
{
protected:
	POINT *corps;
	int nPoints, largeur, hauteur, ID, rotation;
	COLORREF couleur;
public:
	Piece(int pieceId, int pieceRotation, COLORREF pieceColor, const POINT *pt, int numPoints = 4) : ID(pieceId), rotation(pieceRotation), nPoints(numPoints), couleur(pieceColor), largeur(0), hauteur(0)
	{
		POINT bottomLeft = pt[0];
		for (int i = 1; i < nPoints; i++)
		{
			bottomLeft.x = min(pt[i].x, bottomLeft.x);
			bottomLeft.y = min(pt[i].y, bottomLeft.y);
		}
		this->corps = new POINT[nPoints];
		for (int i = 0; i < nPoints; i++)
		{
			this->corps[i].x = pt[i].x - bottomLeft.x;
			this->corps[i].y = pt[i].y - bottomLeft.y;
			largeur = max((int)corps[i].x + 1, largeur);
			hauteur = max((int)corps[i].y + 1, hauteur);
		}
	}
	int	obtLargeur() const 
	{ 
		return this->largeur; 
	}
	int obtHauteur() const 
	{ 
		return this->hauteur; 
	}
	int obtNPoints() const 
	{ 
		return nPoints; 
	}
	int obtID() const 
	{ 
		return this->ID; 
	}
	int obtRotation() const 
	{ 
		return rotation; 
	}
	COLORREF obtCouleur() const 
	{ 
		return this->couleur; 
	}
	void obtCorps(POINT *apt) const;
	bool pointVeri(int x, int y) const;
	int obtBas(POINT *apt) const;
	int obtGauche(POINT *apt) const;
	int obtDroite(POINT *apt) const;
	~Piece()
	{
		if (corps)
			delete[] corps;
	}
};