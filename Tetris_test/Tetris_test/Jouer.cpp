#include "Jouer.h"
#include <timeapi.h>
#include <ctime>

void Niveau::dessinerTableau_p1() const
{
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			dess.dessinerBloc(i, j, tableau1[i][j]);
}

void Niveau::dessinerTableau_p2() const
{
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			dess.dessinerBloc(i + 16, j, tableau1[i][j]);
}

void Niveau::dessinerVit_p1() const
{
	dess.dessinerVit((500 - vitesse) / 2, largeur + 1, 11);
}

void Niveau::dessinerVit_p2() const
{
	dess.dessinerVit((500 - vitesse) / 2, largeur + 17, 11);
}

void Niveau::dessinerPoint_p1() const
{
	dess.dessinerPoint(point, largeur + 1, 10);
}

void Niveau::dessinerPoint_p2() const
{
	dess.dessinerPoint(point, largeur + 17, 10);
}

void Niveau::dessinerPiece_p1() const
{
	dess.dessinerPiece(*suivant, largeur + 1, 13);
}

void Niveau::dessinerPiece_p2() const
{
	dess.dessinerPiece(*suivant, largeur + 17, 13);
}

void Niveau::MAJTemps_p1()
{
	TempsAct = timeGetTime();
	if (TempsAct - TempsDer < vitesse)
		return;
	if (actuel == NULL || !deplacer(0, -1))
	{
		int lignes = effacerLignes();
		vitesse = max(vitesse - 2 * lignes, 100);
		point += 1 + lignes * lignes * 5;
		pieceAuHasard();
		dessinerPoint_p1();
		dessinerVit_p1();
		dessinerPiece_p1();
	}
	TempsDer = timeGetTime();
}

void Niveau::MAJTemps_p2()
{
	TempsAct = timeGetTime();
	if (TempsAct - TempsDer < vitesse)
		return;
	if (actuel == NULL || !deplacer(0, -1))
	{
		int lignes = effacerLignes();
		vitesse = max(vitesse - 2 * lignes, 100);
		point += 1 + lignes * lignes * 5;
		pieceAuHasard();
		dessinerPoint_p2();
		dessinerVit_p2();
		dessinerPiece_p2();
	}
	TempsDer = timeGetTime();
}

bool Niveau::tourner()
{
	Piece *tmp = this->actuel;
	int disX = max(X + actuel->obtHauteur() - largeur, 0);
	int rotation = (actuel->obtRotation() + 1) % PieceSet::NUM_ROTATIONS;
	effacer(*actuel);
	actuel = pieceSet.obtPiece(actuel->obtID(), rotation);
	if (placer(X - disX, Y, *actuel))
		return true;
	actuel = tmp;
	placer(X, Y, *actuel);
	return false;
}

bool Niveau::placer(int x, int y, const Piece &piece)
{
	if (x + piece.obtLargeur() > largeur || coverture(piece, x, y))
		return false;
	X = x;
	Y = y;
	POINT pt[4];
	piece.obtCorps(pt);
	COLORREF color = piece.obtCouleur();
	for (int i = 0; i < 4; i++)
	{
		if (y + pt[i].y > hauteur - 1)
			continue;
		tableau1[x + pt[i].x][y + pt[i].y] = color;
	}
	return true;
}

bool Niveau::deplacer(int x, int y)
{
	if (X + x < 0 || Y + y < 0 ||
		X + actuel->obtLargeur() + x > largeur)
		return false;
	if (x < 0 && venirGauche())
		return false;
	if (x > 0 && venirDroite())
		return false;
	if (y < 0 && venirBas())
		return false;
	effacer(*actuel);
	return placer(X + x, Y + y, *actuel);
}

void Niveau::effacer(const Piece &piece)
{
	POINT pt[4];
	int x, y;
	piece.obtCorps(pt);
	for (int i = 0; i < 4; i++) {
		x = X + pt[i].x;
		y = Y + pt[i].y;
		if (x > largeur - 1 || y > hauteur - 1)
			continue;
		tableau1[X + pt[i].x][Y + pt[i].y] = RGB(0, 0, 0);
	}
}

int Niveau::effacerLignes()
{
	bool isComplete;
	int Lignes = 0;

	for (int i = 0; i < hauteur; i++)
	{
		for (int j = 0; j < largeur; j++)
		{
			if (tableau1[j][i] == RGB(0, 0, 0))
			{
				isComplete = false;
				break;
			}
			if (j == largeur - 1)
				isComplete = true;
		}
		if (isComplete)
		{
			for (int j = 0; j < largeur; j++)
				tableau1[j][i] = RGB(0, 0, 0);
			for (int k = i; k < hauteur - 1; k++)
			{
				for (int m = 0; m < largeur; m++)
					tableau1[m][k] = tableau1[m][k + 1];
			}
			i = -1;
			Lignes++;
		}
	}
	return Lignes;
}

void Niveau::pieceAuHasard()
{
	actuel = suivant;
	suivant = pieceSet.PieceAuHasard();
	placer(3, hauteur - 1, *actuel);
}

bool Niveau::venirBas() const
{
	POINT pt[4];
	int x, y;
	int n = actuel->obtBas(pt);
	for (int i = 0; i < n; i++)
	{
		x = X + pt[i].x;
		y = Y + pt[i].y;
		if (y < hauteur && (y == 0 || tableau1[x][y - 1] != RGB(0, 0, 0)))
			return true;
	}
	return false;
}

bool Niveau::venirGauche() const
{
	POINT pt[4];
	int x, y;
	int n = actuel->obtGauche(pt);
	for (int i = 0; i < n; i++)
	{
		x = X + pt[i].x;
		y = Y + pt[i].y;
		if (y > hauteur - 1)
			continue;
		if (x == 0 || tableau1[x - 1][y] != RGB(0, 0, 0))
			return true;
	}
	return false;
}

bool Niveau::venirDroite() const
{
	POINT pt[4];
	int x, y;
	int n = actuel->obtDroite(pt);
	for (int i = 0; i < n; i++)
	{
		x = X + pt[i].x;
		y = Y + pt[i].y;
		if (y > hauteur - 1)
			continue;
		if (x == largeur - 1 || tableau1[x + 1][y] != RGB(0, 0, 0))
			return true;
	}
	return false;
}

bool Niveau::coverture(const Piece &piece, int x, int y) const
{
	POINT pt[4];
	int tmpX, tmpY;
	piece.obtCorps(pt);
	for (int i = 0; i < 4; i++)
	{
		tmpX = pt[i].x + x;
		tmpY = pt[i].y + y;
		if (tmpX > largeur - 1 || tmpY > hauteur - 1)
			continue;
		if (tableau1[tmpX][tmpY] != RGB(0, 0, 0))
			return true;
	}
	return false;
}

bool Niveau::GameOver()
{
	if (actuel)
		effacer(*actuel);
	for (int i = 0; i < largeur; i++) {
		if (tableau1[i][hauteur - 1]) {
			if (actuel) 
				placer(X, Y, *actuel);
			return true;
		}
	}
	if (actuel != 0)
		placer(X, Y, *actuel);
	return false;
}


