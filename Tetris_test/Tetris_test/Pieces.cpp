#include "Pieces.h"
#include <iostream>

using namespace std;

void Piece::obtCorps(POINT *pt) const
{
	for (int i = 0; i < nPoints; i++)
		pt[i] = corps[i];
}

bool Piece::pointVeri(int x, int y) const
{
	for (int i = 0; i < 4; i++)
	{
		if (corps[i].x == x && corps[i].y == y)
			return true;
	}
	return false;
}

int Piece::obtBas(POINT *pt) const
{
	int i = 0;
	for (int x = 0; x < largeur; x++)
	{
		for (int y = 0; y < hauteur; y++)
		{
			if (pointVeri(x, y))
			{
				pt[i].x = x;
				pt[i].y = y;
				i++;
				break;
			}
		}
	}
	return i;
}

int Piece::obtGauche(POINT *pt) const
{
	int i = 0;
	for (int y = 0; y < hauteur; y++)
	{
		for (int x = 0; x < hauteur; x++)
		{
			if (pointVeri(x, y))
			{
				pt[i].x = x;
				pt[i].y = y;
				i++;
				break;
			}
		}
	}
	return i;
}

int Piece::obtDroite(POINT *pt) const
{
	int i = 0;
	for (int y = 0; y < hauteur; y++)
	{
		for (int x = largeur - 1; x >= 0; x--)
		{
			if (pointVeri(x, y))
			{
				pt[i].x = x;
				pt[i].y = y;
				i++;
				break;
			}
		}
	}
	return i;
}
