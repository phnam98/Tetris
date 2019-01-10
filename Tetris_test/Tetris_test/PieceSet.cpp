#include "PieceSet.h"

Piece *PieceSet::obtPiece(int id, int rotation) const
{
	if (id >= NUM_PIECES || id < 0 || rotation >= NUM_ROTATIONS || rotation < 0)
		return NULL;
	return pieces[id][rotation];
}

void PieceSet::rotate(POINT* pt, int nPoints)
{
	int tmp;
	for (int i = 0; i < nPoints; i++)
	{
		tmp = pt[i].x;
		pt[i].x = -pt[i].y;
		pt[i].y = tmp;
	}
}

void PieceSet::rotateTout()
{
	POINT pt[NUM_ROTATIONS];
	for (int i = 0; i < NUM_PIECES; i++)
	{
		pieces[i][0]->obtCorps(pt);
		for (int j = 1; j < NUM_ROTATIONS; j++)
		{
			rotate(pt);
			if (pieces[i][j] != 0)
				delete pieces[i][j];
			pieces[i][j] = new Piece(i, j, pieces[i][0]->obtCouleur(), pt);
		}
	}
}
