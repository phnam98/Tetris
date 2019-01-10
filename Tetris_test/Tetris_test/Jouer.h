#pragma once
#include "Draw.h"
#include "PieceSet.h"
#include <windows.h>
#include <ctime>

class Niveau
{
protected:
	COLORREF **tableau1;    
	Dessiner &dess;      
	PieceSet pieceSet;   
	Piece *actuel;      
	Piece *suivant;     
	int largeur, hauteur;        
	int X, Y;            
	int vitesse, point;          
	double TempsDer;   
	double TempsAct;          
public:
	Niveau(Dessiner &dess, int largeur = 10, int hauteur = 20) : dess(dess), largeur(largeur), hauteur(hauteur), TempsDer(0.0), vitesse(500), point(-1)
	{
		srand(time(0));
		tableau1 = new COLORREF*[largeur];
		for (int i = 0; i < largeur; i++)
		{
			tableau1[i] = new COLORREF[hauteur];
			for (int j = 0; j < hauteur; j++)
				tableau1[i][j] = RGB(0, 0, 0);
		}
		this->actuel = 0;
		this->suivant = pieceSet.PieceAuHasard();
	}
	bool placer(int x, int y, const Piece &piece);
	void effacer(const Piece& piece);
	int effacerLignes();
	void pieceAuHasard();
	bool venirBas() const;
	bool venirGauche() const;
	bool venirDroite() const;
	bool coverture(const Piece &piece, int x, int y) const;
	void dessinerTableau_p1() const;
	void dessinerTableau_p2() const;
	bool tourner();
	bool deplacer(int x, int y);
	void MAJTemps_p1();
	void MAJTemps_p2();
	bool GameOver();
	void dessinerVit_p1() const;
	void dessinerPoint_p1() const;
	void dessinerPiece_p1() const;
	void dessinerVit_p2() const;
	void dessinerPoint_p2() const;
	void dessinerPiece_p2() const;
	~Niveau()
	{
		for (int i = 0; i < largeur; i++)
			delete[] tableau1[i];
		delete[] tableau1;
	}
};