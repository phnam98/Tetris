#pragma once
#include "Pieces.h"

class PieceSet
{
protected:
	Piece * pieces[7][4];
public:
	enum { NUM_ROTATIONS = 4, NUM_PIECES = 7 };	
	PieceSet()
	{
		for (int i = 0; i < NUM_PIECES; i++)
			for (int j = 0; j < NUM_ROTATIONS; j++)
				pieces[i][j] = 0;

		POINT pt[NUM_ROTATIONS];
		//Tétrimino I, bleu clair
		pt[0].x = 0;    pt[0].y = 0;
		pt[1].x = 0;    pt[1].y = 1;
		pt[2].x = 0;    pt[2].y = 2;
		pt[3].x = 0;    pt[3].y = 3;
		pieces[0][0] = new Piece(0, 0, RGB(0, 178, 191), pt); 

		// Tétrimino O, jaune
		pt[0].x = 0;    pt[0].y = 0;
		pt[1].x = 1;    pt[1].y = 0;
		pt[2].x = 0;    pt[2].y = 1;
		pt[3].x = 1;    pt[3].y = 1;
		pieces[1][0] = new Piece(1, 0, RGB(255, 255, 0), pt);

		// Tétrimino T, violet
		pt[0].x = 0;    pt[0].y = 0;
		pt[1].x = 1;    pt[1].y = 0;
		pt[2].x = 2;    pt[2].y = 0;
		pt[3].x = 1;    pt[3].y = 1;
		pieces[2][0] = new Piece(2, 0, RGB(93, 12, 123), pt);

		// Tétrimino L, orange
		pt[0].x = 0;    pt[0].y = 0;
		pt[1].x = 1;    pt[1].y = 0;
		pt[2].x = 0;    pt[2].y = 1;
		pt[3].x = 0;    pt[3].y = 2;
		pieces[3][0] = new Piece(3, 0, RGB(230, 130, 24), pt);

		// Tétrimino J, bleu
		pt[0].x = 0;    pt[0].y = 0;
		pt[1].x = 1;    pt[1].y = 0;
		pt[2].x = 1;    pt[2].y = 1;
		pt[3].x = 1;    pt[3].y = 2;
		pieces[4][0] = new Piece(4, 0, RGB(27, 79, 147), pt);

		// Tétrimino Z, rouge
		pt[0].x = 1;    pt[0].y = 0;
		pt[1].x = 2;    pt[1].y = 0;
		pt[2].x = 0;    pt[2].y = 1;
		pt[3].x = 1;    pt[3].y = 1;
		pieces[5][0] = new Piece(5, 0, RGB(255, 0, 0), pt);

		// Tétrimino S, vert
		pt[0].x = 0;    pt[0].y = 0;
		pt[1].x = 1;    pt[1].y = 0;
		pt[2].x = 1;    pt[2].y = 1;
		pt[3].x = 2;    pt[3].y = 1;
		pieces[6][0] = new Piece(6, 0, RGB(120, 200, 80), pt);
		
		rotateTout();
	}
	void rotate(POINT *pt, int nPoints = 4);
	void rotateTout();
	Piece *obtPiece(int id, int rotation) const;
	inline Piece *PieceAuHasard() const
	{
		return obtPiece(rand() % NUM_PIECES, rand() % NUM_ROTATIONS);
	}
	~PieceSet()
	{
		for (int i = 0; i < NUM_PIECES; i++)
			for (int j = 0; j < NUM_ROTATIONS; j++)
				if (pieces[i][j] != 0)
					delete pieces[i][j];
	}
};