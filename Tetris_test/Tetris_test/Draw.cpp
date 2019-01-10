#include "Draw.h"

void Dessiner::dessinerBloc(int x, int y, COLORREF couleur)
{
	HBRUSH hBrush = CreateSolidBrush(couleur);
	rect.left = x;
	rect.right = x + 1;
	rect.top = y;
	rect.bottom = y + 1;
	FillRect(hdc, &rect, hBrush);
	MoveToEx(hdc, x, y + 1, NULL);
	LineTo(hdc, x, y);
	LineTo(hdc, x + 1, y);
	DeleteObject(hBrush);
}

void Dessiner::dessinerInterface()
{
	rect.top = this->hauteur;
	rect.left = this->largeur;
	rect.bottom = this->hauteur - 12;
	rect.right = this->largeur + 6;
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hdc, &rect, hBrush);

	rect.top = this->hauteur;
	rect.left = this->largeur + 16;
	rect.bottom = this->hauteur - 12;
	rect.right = this->largeur + 22;
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hdc, &rect, hBrush);

	rect.top = this->hauteur - 13;
	rect.left = this->largeur;
	rect.bottom = this->hauteur - 20;
	rect.right = this->largeur + 6;
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hdc, &rect, hBrush);
	TextOut(hdc, largeur + 1, hauteur - 16, TEXT("JOUEUR Nb. 1"), 12);

	rect.top = this->hauteur - 13;
	rect.left = this->largeur + 16;
	rect.bottom = this->hauteur - 20;
	rect.right = this->largeur + 22;
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hdc, &rect, hBrush);
	TextOut(hdc, largeur + 17, hauteur - 16, TEXT("JOUEUR Nb. 2"), 12);
	
	DeleteObject(hBrush);
}

void Dessiner::dessinerTexte(const TCHAR *Texte, int x, int y) const
{
	TextOut(hdc, x, y, Texte, lstrlen(Texte));
}

void Dessiner::dessinerPiece(Piece &piece, int x, int y)
{
	TCHAR szBuffer[] = TEXT("Pièce suivante:");
	TextOut(hdc, x, y -1 , szBuffer, lstrlen(szBuffer));
	COLORREF color = piece.obtCouleur();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (piece.pointVeri(i, j))
				dessinerBloc(i + x, j + y, color);
			else
				dessinerBloc(i + x, j + y, RGB(0, 0, 0));
		}
	}
}

void Dessiner::dessinerPoint(int pt, int x, int y) const
{
	TCHAR szBuffer[20];
	int point = wsprintf(szBuffer, TEXT("Point: %10d"), pt);
	TextOut(hdc, x, y, szBuffer, point);
	SetBkMode(hdc, OPAQUE);
}

void Dessiner::dessinerVit(int vitesse, int x, int y) const
{
	TCHAR szBuffer[20];
	int vit = wsprintf(szBuffer, TEXT("Vitesse: %6d"), vitesse);
	TextOut(hdc, x, y, szBuffer, vit);
	SetBkMode(hdc, OPAQUE);
}
